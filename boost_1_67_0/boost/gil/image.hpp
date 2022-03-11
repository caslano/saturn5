//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IMAGE_HPP
#define BOOST_GIL_IMAGE_HPP

#include <boost/gil/algorithm.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/metafunctions.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <boost/assert.hpp>
#include <boost/core/exchange.hpp>

#include <cstddef>
#include <memory>
#include <utility>
#include <type_traits>

namespace boost { namespace gil {

////////////////////////////////////////////////////////////////////////////////////////
/// \ingroup ImageModel PixelBasedModel
/// \brief container interface over image view. Models ImageConcept, PixelBasedConcept
///
/// A 2D container whose elements are pixels. It is templated over the pixel type, a boolean
/// indicating whether it should be planar, and an optional allocator.
///
/// Note that its element type does not have to be a pixel. \p image can be instantiated with any Regular element,
/// in which case it models the weaker RandomAccess2DImageConcept and does not model PixelBasedConcept
///
/// When recreating an image of the same or smaller size the memory will be reused if possible.
///
////////////////////////////////////////////////////////////////////////////////////////

template< typename Pixel, bool IsPlanar = false, typename Alloc=std::allocator<unsigned char> >
class image
{
public:
#if defined(BOOST_NO_CXX11_ALLOCATOR)
    using allocator_type = typename Alloc::template rebind<unsigned char>::other;
#else
    using allocator_type = typename std::allocator_traits<Alloc>::template rebind_alloc<unsigned char>;
#endif
    using view_t = typename view_type_from_pixel<Pixel, IsPlanar>::type;
    using const_view_t = typename view_t::const_t;
    using point_t = typename view_t::point_t;
    using coord_t = typename view_t::coord_t;
    using value_type = typename view_t::value_type;
    using x_coord_t = coord_t;
    using y_coord_t = coord_t;

    const point_t&          dimensions()            const { return _view.dimensions(); }
    x_coord_t               width()                 const { return _view.width(); }
    y_coord_t               height()                const { return _view.height(); }

    explicit image(std::size_t alignment=0,
                   const Alloc alloc_in = Alloc()) :
        _memory(nullptr), _align_in_bytes(alignment), _alloc(alloc_in), _allocated_bytes( 0 ) {}

    // Create with dimensions and optional initial value and alignment
    image(const point_t& dimensions,
          std::size_t alignment=0,
          const Alloc alloc_in = Alloc()) : _memory(nullptr), _align_in_bytes(alignment), _alloc(alloc_in)
                                          , _allocated_bytes( 0 )
    {
        allocate_and_default_construct(dimensions);
    }

    image(x_coord_t width, y_coord_t height,
          std::size_t alignment=0,
          const Alloc alloc_in = Alloc()) : _memory(nullptr), _align_in_bytes(alignment), _alloc(alloc_in)
                                          , _allocated_bytes( 0 )
    {
        allocate_and_default_construct(point_t(width,height));
    }

    image(const point_t& dimensions,
          const Pixel& p_in,
          std::size_t alignment = 0,
          const Alloc alloc_in = Alloc())  : _memory(nullptr), _align_in_bytes(alignment), _alloc(alloc_in)
                                           , _allocated_bytes( 0 )
    {
        allocate_and_fill(dimensions, p_in);
    }

    image(x_coord_t width, y_coord_t height,
          const Pixel& p_in,
          std::size_t alignment = 0,
          const Alloc alloc_in = Alloc())  : _memory(nullptr), _align_in_bytes(alignment), _alloc(alloc_in)
                                           , _allocated_bytes ( 0 )
    {
        allocate_and_fill(point_t(width,height),p_in);
    }

    image(const image& img) : _memory(nullptr), _align_in_bytes(img._align_in_bytes), _alloc(img._alloc)
                            , _allocated_bytes( img._allocated_bytes )
    {
        allocate_and_copy(img.dimensions(),img._view);
    }

    template <typename P2, bool IP2, typename Alloc2>
    image(const image<P2,IP2,Alloc2>& img) : _memory(nullptr), _align_in_bytes(img._align_in_bytes), _alloc(img._alloc)
                                           , _allocated_bytes( img._allocated_bytes )
    {
       allocate_and_copy(img.dimensions(),img._view);
    }

    // TODO Optimization: use noexcept (requires _view to be nothrow copy constructible)
    image(image&& img) :
      _view(img._view),
      _memory(img._memory),
      _align_in_bytes(img._align_in_bytes),
      _alloc(std::move(img._alloc)),
      _allocated_bytes(img._allocated_bytes)
    {
        img._view = view_t();
        img._memory = nullptr;
        img._align_in_bytes = 0;
        img._allocated_bytes = 0;
    }

    image& operator=(const image& img)
    {
        if (dimensions() == img.dimensions())
            copy_pixels(img._view,_view);
        else
        {
            image tmp(img);
            swap(tmp);
        }
        return *this;
    }

    template <typename Img>
    image& operator=(const Img& img)
    {
        if (dimensions() == img.dimensions())
            copy_pixels(img._view,_view);
        else
        {
            image tmp(img);
            swap(tmp);
        }
        return *this;
    }

  private:
      using propagate_allocators = std::true_type;
      using no_propagate_allocators = std::false_type;

      template <class Alloc2>
      using choose_pocma = typename std::conditional<
          // TODO: Use std::allocator_traits<Allocator>::is_always_equal if available
          std::is_empty<Alloc2>::value,
          std::true_type,
          typename std::allocator_traits<Alloc2>::propagate_on_container_move_assignment::type
      >::type;

      static void exchange_memory(image& lhs, image& rhs)
      {
          lhs._memory = boost::exchange(rhs._memory, nullptr);
          lhs._align_in_bytes = boost::exchange(rhs._align_in_bytes, 0);
          lhs._allocated_bytes = boost::exchange(rhs._allocated_bytes, 0);
          lhs._view = boost::exchange(rhs._view, image::view_t{});
      };

      void move_assign(image& img, propagate_allocators) noexcept {
          // non-sticky allocator, can adopt the memory, fast
          destruct_pixels(_view);
          this->deallocate();
          this->_alloc = img._alloc;
          exchange_memory(*this, img);
      }

      void move_assign(image& img, no_propagate_allocators) {
          if (_alloc == img._alloc) {
              // allocator stuck to the rhs, but it's equivalent of ours, we can still adopt the memory
              destruct_pixels(_view);
              this->deallocate();
              exchange_memory(*this, img);
          } else {
              // cannot propagate the allocator and cannot adopt the memory
              if (img._memory)
              {
                  allocate_and_copy(img.dimensions(), img._view);
                  destruct_pixels(img._view);
                  img.deallocate();
                  img._view = image::view_t{};
              }
              else
              {
                  destruct_pixels(this->_view);
                  this->deallocate();
                  this->_view = view_t{};
              }
          }
      }

  public:
      // TODO: Use noexcept(noexcept(move_assign(img, choose_pocma<allocator_type>{})))
      // But https://gcc.gnu.org/bugzilla/show_bug.cgi?id=52869 prevents it (fixed in GCC > 9)
      image& operator=(image&& img) {
          if (this != std::addressof(img))
              // Use rebinded alloc to choose pocma
              move_assign(img, choose_pocma<allocator_type>{});

          return *this;
      }

    ~image()
    {
        destruct_pixels(_view);
        deallocate();
    }

    Alloc&       allocator() { return _alloc; }
    Alloc const& allocator() const { return _alloc; }

    void swap(image& img) // required by MutableContainerConcept
    {
        using std::swap;
        swap(_align_in_bytes,  img._align_in_bytes);
        swap(_memory,          img._memory);
        swap(_view,            img._view);
        swap(_alloc,           img._alloc);
        swap(_allocated_bytes, img._allocated_bytes );
    }

    /////////////////////
    // recreate
    /////////////////////

    // without Allocator
    void recreate(const point_t& dims, std::size_t alignment = 0)
    {
        if (dims == _view.dimensions() && _align_in_bytes == alignment)
            return;

        _align_in_bytes = alignment;

        if (_allocated_bytes >= total_allocated_size_in_bytes(dims))
        {
            destruct_pixels(_view);
            create_view(dims, std::integral_constant<bool, IsPlanar>());
            default_construct_pixels(_view);
        }
        else
        {
            image tmp(dims, alignment);
            swap(tmp);
        }
    }

    void recreate(x_coord_t width, y_coord_t height, std::size_t alignment = 0)
    {
        recreate(point_t(width, height), alignment);
    }

    void recreate(const point_t& dims, const Pixel& p_in, std::size_t alignment = 0)
    {
        if (dims == _view.dimensions() && _align_in_bytes == alignment)
            return;

        _align_in_bytes = alignment;

        if (_allocated_bytes >= total_allocated_size_in_bytes(dims))
        {
            destruct_pixels(_view);
            create_view(dims, typename std::integral_constant<bool, IsPlanar>());
            uninitialized_fill_pixels(_view, p_in);
        }
        else
        {
            image tmp(dims, p_in, alignment);
            swap(tmp);
        }
    }

    void recreate( x_coord_t width, y_coord_t height, const Pixel& p_in, std::size_t alignment = 0 )
    {
        recreate( point_t( width, height ), p_in, alignment );
    }

    // with Allocator
    void recreate(const point_t& dims, std::size_t alignment, const Alloc alloc_in)
    {
        if (dims == _view.dimensions() && _align_in_bytes == alignment && alloc_in == _alloc)
            return;

        _align_in_bytes = alignment;

        if (_allocated_bytes >= total_allocated_size_in_bytes(dims))
        {
            destruct_pixels(_view);
            create_view(dims, std::integral_constant<bool, IsPlanar>());
            default_construct_pixels(_view);
        }
        else
        {
            image tmp(dims, alignment, alloc_in);
            swap(tmp);
        }
    }

    void recreate(x_coord_t width, y_coord_t height, std::size_t alignment, const Alloc alloc_in)
    {
        recreate(point_t(width, height), alignment, alloc_in);
    }

    void recreate(const point_t& dims, const Pixel& p_in, std::size_t alignment, const Alloc alloc_in)
    {
        if (dims == _view.dimensions() && _align_in_bytes == alignment && alloc_in == _alloc)
            return;

        _align_in_bytes = alignment;

        if (_allocated_bytes >= total_allocated_size_in_bytes(dims))
        {
            destruct_pixels(_view);
            create_view(dims, std::integral_constant<bool, IsPlanar>());
            uninitialized_fill_pixels(_view, p_in);
        }
        else
        {
            image tmp(dims, p_in, alignment, alloc_in);
            swap(tmp);
        }
    }

    void recreate(x_coord_t width, y_coord_t height, const Pixel& p_in, std::size_t alignment, const Alloc alloc_in )
    {
        recreate(point_t(width, height), p_in, alignment, alloc_in);
    }

    view_t       _view;      // contains pointer to the pixels, the image size and ways to navigate pixels
private:
    unsigned char* _memory;
    std::size_t    _align_in_bytes;
    allocator_type _alloc;

    std::size_t _allocated_bytes;

    void allocate_and_default_construct(point_t const& dimensions)
    {
        try
        {
            allocate_(dimensions, std::integral_constant<bool, IsPlanar>());
            default_construct_pixels(_view);
        }
        catch (...) { deallocate(); throw; }
    }

    void allocate_and_fill(const point_t& dimensions, Pixel const& p_in)
    {
        try
        {
            allocate_(dimensions, std::integral_constant<bool, IsPlanar>());
            uninitialized_fill_pixels(_view, p_in);
        }
        catch(...) { deallocate(); throw; }
    }

    template <typename View>
    void allocate_and_copy(const point_t& dimensions, View const& v)
    {
        try
        {
            allocate_(dimensions, std::integral_constant<bool, IsPlanar>());
            uninitialized_copy_pixels(v, _view);
        }
        catch(...) { deallocate(); throw; }
    }

    void deallocate()
    {
        if (_memory && _allocated_bytes > 0)
            _alloc.deallocate(_memory, _allocated_bytes);
    }

    std::size_t is_planar_impl(
        std::size_t const size_in_units,
        std::size_t const channels_in_image,
        std::true_type) const
    {
        return size_in_units * channels_in_image;
    }

    std::size_t is_planar_impl(
        std::size_t const size_in_units,
        std::size_t const,
        std::false_type) const
    {
        return size_in_units;
    }

    std::size_t total_allocated_size_in_bytes(point_t const& dimensions) const
    {
        using x_iterator = typename view_t::x_iterator;

        // when value_type is a non-pixel, like int or float, num_channels< ... > doesn't work.
        constexpr std::size_t _channels_in_image =
            std::conditional
            <
                is_pixel<value_type>::value,
                num_channels<view_t>,
                std::integral_constant<std::size_t, 1>
            >::type::value;

        std::size_t size_in_units = is_planar_impl(
            get_row_size_in_memunits(dimensions.x) * dimensions.y,
            _channels_in_image,
            std::integral_constant<bool, IsPlanar>());

        // return the size rounded up to the nearest byte
        return ( size_in_units + byte_to_memunit< x_iterator >::value - 1 )
            / byte_to_memunit<x_iterator>::value
            + ( _align_in_bytes > 0 ? _align_in_bytes - 1 : 0 ); // add extra padding in case we need to align the first image pixel
    }

    std::size_t get_row_size_in_memunits(x_coord_t width) const {   // number of units per row
        std::size_t size_in_memunits = width*memunit_step(typename view_t::x_iterator());
        if (_align_in_bytes>0) {
            std::size_t alignment_in_memunits=_align_in_bytes*byte_to_memunit<typename view_t::x_iterator>::value;
            return align(size_in_memunits, alignment_in_memunits);
        }
        return size_in_memunits;
    }

    void allocate_(point_t const& dimensions, std::false_type)
    {
        // if it throws and _memory!=0 the client must deallocate _memory
        _allocated_bytes = total_allocated_size_in_bytes(dimensions);
        _memory=_alloc.allocate( _allocated_bytes );

        unsigned char* tmp=(_align_in_bytes>0) ? (unsigned char*)align((std::size_t)_memory,_align_in_bytes) : _memory;
        _view=view_t(dimensions,typename view_t::locator(typename view_t::x_iterator(tmp), get_row_size_in_memunits(dimensions.x)));

        BOOST_ASSERT(_view.width() == dimensions.x);
        BOOST_ASSERT(_view.height() == dimensions.y);
    }

    void allocate_(point_t const& dimensions, std::true_type)
    {
        // if it throws and _memory!=0 the client must deallocate _memory
        std::size_t row_size=get_row_size_in_memunits(dimensions.x);
        std::size_t plane_size=row_size*dimensions.y;

        _allocated_bytes = total_allocated_size_in_bytes( dimensions );

        _memory = _alloc.allocate( _allocated_bytes );

        unsigned char* tmp=(_align_in_bytes>0) ? (unsigned char*)align((std::size_t)_memory,_align_in_bytes) : _memory;
        typename view_t::x_iterator first;
        for (std::size_t i = 0; i < num_channels<view_t>::value; ++i)
        {
            dynamic_at_c(first, i) = (typename channel_type<view_t>::type*)tmp;
            memunit_advance(dynamic_at_c(first, i), static_cast<std::ptrdiff_t>(plane_size * i));
        }
        _view=view_t(dimensions, typename view_t::locator(first, row_size));

        BOOST_ASSERT(_view.width() == dimensions.x);
        BOOST_ASSERT(_view.height() == dimensions.y);
    }

    void create_view(point_t const& dims, std::true_type) // is planar
    {
        std::size_t row_size=get_row_size_in_memunits(dims.x);
        std::size_t plane_size=row_size*dims.y;

        unsigned char* tmp = ( _align_in_bytes > 0 ) ? (unsigned char*) align( (std::size_t) _memory
                                                                             ,_align_in_bytes
                                                                             )
                                                     : _memory;
        typename view_t::x_iterator first;

        for (std::size_t i = 0; i < num_channels<view_t>::value; ++i)
        {
            dynamic_at_c(first, i) = (typename channel_type<view_t>::type*)tmp;
            memunit_advance(dynamic_at_c(first, i), static_cast<std::ptrdiff_t>(plane_size * i));
        }

        _view = view_t(dims, typename view_t::locator(first, row_size));

        BOOST_ASSERT(_view.width() == dims.x);
        BOOST_ASSERT(_view.height() == dims.y);
    }

    void create_view(point_t const& dims, std::false_type) // is planar
    {
        unsigned char* tmp = ( _align_in_bytes > 0 ) ? ( unsigned char* ) align( (std::size_t) _memory
                                                                               , _align_in_bytes
                                                                               )
                                                     : _memory;

        _view = view_t( dims
                      , typename view_t::locator( typename view_t::x_iterator( tmp )
                                                , get_row_size_in_memunits( dims.x )
                                                )
                      );

        BOOST_ASSERT(_view.width() == dims.x);
        BOOST_ASSERT(_view.height() == dims.y);
    }
};

template <typename Pixel, bool IsPlanar, typename Alloc>
void swap(image<Pixel, IsPlanar, Alloc>& im1,image<Pixel, IsPlanar, Alloc>& im2)
{
    im1.swap(im2);
}

template <typename Pixel1, bool IsPlanar1, typename Alloc1, typename Pixel2, bool IsPlanar2, typename Alloc2>
bool operator==(const image<Pixel1,IsPlanar1,Alloc1>& im1,const image<Pixel2,IsPlanar2,Alloc2>& im2)
{
    if ((void*)(&im1)==(void*)(&im2)) return true;
    if (const_view(im1).dimensions()!=const_view(im2).dimensions()) return false;
    return equal_pixels(const_view(im1),const_view(im2));
}
template <typename Pixel1, bool IsPlanar1, typename Alloc1, typename Pixel2, bool IsPlanar2, typename Alloc2>
bool operator!=(const image<Pixel1,IsPlanar1,Alloc1>& im1,const image<Pixel2,IsPlanar2,Alloc2>& im2) {return !(im1==im2);}

///@{
/// \name view, const_view
/// \brief Get an image view from an image

/// \ingroup ImageModel

/// \brief Returns the non-constant-pixel view of an image
template <typename Pixel, bool IsPlanar, typename Alloc> inline
const typename image<Pixel,IsPlanar,Alloc>::view_t& view(image<Pixel,IsPlanar,Alloc>& img) { return img._view; }

/// \brief Returns the constant-pixel view of an image
template <typename Pixel, bool IsPlanar, typename Alloc> inline
const typename image<Pixel,IsPlanar,Alloc>::const_view_t const_view(const image<Pixel,IsPlanar,Alloc>& img)
{
    return static_cast<const typename image<Pixel,IsPlanar,Alloc>::const_view_t>(img._view);
}
///@}

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename Pixel, bool IsPlanar, typename Alloc>
struct channel_type<image<Pixel, IsPlanar, Alloc>> : channel_type<Pixel> {};

template <typename Pixel, bool IsPlanar, typename Alloc>
struct color_space_type<image<Pixel, IsPlanar, Alloc>> : color_space_type<Pixel> {};

template <typename Pixel, bool IsPlanar, typename Alloc>
struct channel_mapping_type<image<Pixel, IsPlanar, Alloc>> : channel_mapping_type<Pixel> {};

template <typename Pixel, bool IsPlanar, typename Alloc>
struct is_planar<image<Pixel, IsPlanar, Alloc>> : std::integral_constant<bool, IsPlanar> {};

}}  // namespace boost::gil

#endif

/* image.hpp
V9jAXP1C2P5yehhEFMYXAJbjoP4GNnt5aGGAnnNY58vewsblOdJnu3n3QOPgovpljYOeByfdPTBOeOFQoSZNOLabh+yGXmU4SRqnDDukZGXYLrvKcQQWSNKhfyMx7T6lAXH4aPCvzCSPx5QsLmDigAV006EryzLNMtjeriTZCT8ZybXJeOiRCdWzfHQhrHRj/dzslMqr2pQ2R0111WYM8ne3AdlwIZvwaFsQ7w4Bqv7AVIfWWNw7RWeasXetfAnkzA2yMJG/p7EISHm2sTTGfE1PM19TjPmaDmN8YCptzgRd4hTu3X3YtMLv/hjABORb3Ybn+r7i7J3lZAYu9q4bydJ+SCodriCGYlYYdTEjcz+ely2rsOCfAFuqWMzHVvVvGaz6SNFmfR52OPvF+0CMk0ukyCW+LKWboHwmILIMtKQPEsdaU61ej6mqyD78iYSygluRDWWvHDkqxaguNnIMPCwOcXTRm9Z5pp9eg/NXvT0Y0ef30ZWYHDmAFFg4WI9NCGvMDcXrW6H19C524ggjLYNUT9foEafm7QbF+7TPT385hUXyq94udC75DLnbkE/TITM38dxZaeiy6T8BOC+9wc6d8UDSnFyhqflNoeMu4ZGwFTlC2/EsVk2hTYXsvDrYgpO9sRBjVnpwwuLSKOB0x9UAcm3XyDRTrzKnOTbGT2RQOFrEegdwTyK47gILHLtrx2v3CcoHfboj5KoWlz46GaBfA030Nyzo7ec4P1VnfHEHbxWYHbx/EjvA2yO8MtQtPIz6SQW5HrczckMPmzQZkrNo5assHPJ7f42HQx4+hIzMWkC7PEE8I3EkogNJF/r0mbimheX0AvQqdlTKU8UzQOxGsdIpKB/2BfwWNv/GztTdnmS8TRBy1kjTy+mzB0w/WZOegYvZUU5x6Pqf6A8/BTVxOf0e+8Fz+arNkXLaAtUraQNkxoMuNyPCDiLCfrMCA4950OFfrbsh1L3JffzSedHrvKqtUJ5F1400MXXi6jxLJ+5dht7X35Q6yXkVFu4SDHygyH1KrepRhgFFHYlkW6F04CKoshMPFJJxjYWHv4sskKN3IG7VhhheNZo57cp1mIjrUNUjvi19HenX70ZfJrSp+FuciEtHIFuLmwfFE04mHNx3tFMObIQxJFQ1AlnwB8rp8iFG2+Lb8h1+4NcWEZuiATI3ePLZRQ63nxa0M61ACE9kxyMusVNoxggJE0e9PfAaH+VvXsdRQvN0Vk9KMeuQCP12PtAVHqYgBQbwZMOMUaJfx2MNS5ROA+srFh6QXLTjIjudTqXPX2QmAIjNQ5FQdrAPV+88LAhpwKiBCQCEBtCT2oufqINB4D3VAP0FHkP3bnaMLogQxj9MPbpY1zvYUpzEAatVsQA9wjF0dYsRofnHKAPNfbkWTzf+O81m+UST1YYefamf3jXVRK4YkeaT4lgJWHlJpMMXwAizbxgYyVuP7htvN7T+EQaovZTlqeqRS8SLcgoQDSzeyCqCYE5AvgkzZyzM6QgTuBL1MWAZ8UW9gbGkbpu8GCZuLxoFGhhlTM+xNdUnMac4D5NOO8HCMap6wqfkr3pmxNc58KK1zicBNF1zwTA8Vd1CWMCQsxF2duE8Y2e9hh2vistzaLZZT548WueoWUcfWf3eE3YWuy6Ef4svw907JoUH6nhztIxPIUKAgbGl+Z6dLY14IpFRnwZG3eVDghlmF9ycpEuteh11mFa2WLgTtvvJcPsnXKAceLchd9FfTIqfPfN4xckLKxege7NGBMh84RlHezdn4RkD5gDTT1+22eIAhlhXWShS5NsSWL21UABixReBuDcBxH4ThJ7pN/DMOnFNEvbmIsafPN4eudpkedJ1ftr5vLUe7+J6/KEPDc3ee4bN042q1wFFha/hQmKz+WIXsOK9fYmSp7jPXIbxdGdffLcCi9fXMlL5/HhYSIzf6n+Jnxab/UuzYFXqXvHTmzBNF/aNMlT6lAdtjmmQ1fsmnmIYIP7GXzGIA5+wQZBO/Th6wkqd5e5T4it114a63cc3IdN1bc+mXVDJCopEwPTssnhQ5Epgty5PFQ867nlpPC7/K7h+pAuHT/Uh5B3sHClDPLPdlXsRFsnxdjndPGDSCCjbm6siSj5Tj8wjvziDTtmH+ztSUoL+lUvH5iQjBTFHh1ZiKIPD/rpZtBDGZV0itJxAty4bdQzEpSBoXFOhov5GK94YGnvPN3bOMBIhuJYl3vPF9njPF1ua93yD+LnMK0kNlELUu2S7eQR6ja0QZqNcgzqZrTVWjOc4YHvBb2eyDWbHPiYZIelYvg8b3n0ow3EQ9v9tc7lcn7PpM/zeZG2a0pYhttd+ZB7ZKGddIA/JShfzf5Hh3AeAQcXaPxHIq18/xOF1qz12dJeppX1kwtqBdrtaGhPCJ5Lwllz2YjJZregn/phaESUV/QMH7GqVU5baP+PWKZ8V1DlCBbeT9Zy4npdXKZ/lYBRT4/Zp5PAJXduQxF06MXvL/jXDafIcGMDsaXq2tq57pOTx/RiuAoUpWFjJkSonKefJZo6Uxhyl/ertHN4hgOetvFrOw5jIa1f0WhVV3oPB9AthFL25chRy2oe4UAHwm/XV4pm6JHLGURo1W4knAQDknBTfkqqBUsn9nHg/L4vKUM4LbMxTySsnzl06OVuC8W5wcPJsHNRifbq2vpvl/8EcLRax8d7PMSg8WcupG813jqzl1Y08IFl34J2Khn4baBJvCc3MmVDapzlfI5VQm1erORVqb4QnD09xIy9v3Q1IaSkVhtsBiy3wvv2axgbBJk8ghxlOT+jQado09s6wu2b/mrQsfQGr5AK0JtSq5CD9Z5b+SGtm405zEW9MTVHXLIoRb5/BC+GLqNAgsWHwGR6bkXSuBI8cUbMP4pdH298RHCXOv6DGX15mnDTLWRMLdpqPZ0lS6DILlZ+1YGe2eO5wyWrztcTV+MBqm5ymbOWGWY6yE5jpnWid3ec0TrIs4z7Xlfq2ReRYBkROMpHacw9qGyaeLdNKMsp89NYh5Hk88AKDVRWTsW4dp9zLZ7C9wfYP1GjFfDUfh7gZ4z724U7yk6XYCF3offISpc11d1uGzzSCAomcU+xk1yZ3Kub+M1uxPXv3QIaD1Q++tJLZxQnbWuxUi1xSZ4gL4kdmg7grA0Zmm1XilCcZda5A4mz1/6Vs5A11hbqLM5KxC7C4FN4gHVbMTxnbwny5n9zvCuBHQBxtq8NtDYMk8vU2toebF+EeBur3Rm9XC3m1kFPa+HVyfwhMd2aFtn8oOB5wMgvOGgoG4sbjSLQf2O4DWfuZWhHbsZoczn21vdepFbtWKiVRQ2k5ize5tL0x+FFd8AsssbMw1odJH9fZiMYZJpKxn7XyK6QCyCyajOHC2i1OtYRTV/LaOnjh1ZWc8rUfr2EXr577MYtXK1q9++Bwe3MbLFTLxtWyI20nxwgMNuRHl47P9vEkEv+Ii3LWaXIyjLhwYQAUeSO3DLjZ1PaPBHJ4DDfrJ7fEQAdZK57X6j0xMkstdYE2KHynAkoHInYhjOcAjjfFi8J3RQymKI21D3JrlcECtTRalxIqqIRfUsOJNby8Whm0eNt03GNRbYOdMbe9yNzmmcxtltLenVj4+N4x/O0WHqCp+MKRB3n1AZ6UunKP2ktjGAwlfOe/cRM2xICVtBvcLYpRoG1YHENWV0Oq+rXsIbXKBcwR21e51EpeXc8hN1nPw1Os5OXA7g2pwEEmAwcxgIOkctuzGxsmIwd5NZGDaGv2riGv6jmszKXdMoZxNLNBQ3Z8j7vYRa6YtuYrMZVXN9hjwNsq8KKVuiqmrvlKtDcPVe+23uVoPmk3Ih6rnAsA8ka7uj6mbXHHYKXah7mNynABSA7IwylVD4DuJ4QZY5RjVjErAOSIt6AwGR4RJkeB3UkpcXxPGBUmG5kwSflCZIMwAXzvYIx2Bw9QkdfKLoccU0fGY3ZY2q85z5MHEJXqtxh+18OTt6QaoDXFYszDgNYUhlbGmI++yFD0CWLOw9B6FNHK+PHG7oTCB0bQujEBrV6X6lDXZMXYVcjNyJQsZvziCDNOYMNs25ZZfpf/55y4RGFOIPuugv85Fz7yKVPHTBZs6S+4VxkHbjqLdIFqYcRkNWHYoJ4ZWNVPjgXUiiNgswnfuRvNkFUuNM/uwldgFbCNWsxtfJqs47WncTpqabda1adWnQWpr8oHQ4WgVld1V2rP40mZWgVGA4UNfvF/C3v22/EiTFRozkZwFdGmA8i6lD87QX81tN+54EcIu6BMuRleUrHSBFB8yKA0aW3TIH7rXPju+wDD8Mb0qaS9PcqVKNGCXUAvm7RmdjBn2JRBl7DnIPKSdkEIv4hf0BhEJih89/fI97jFnp2gRrXa2VWfC7U/FsI/wDoHkEeuVoZ4Yc89zOaOkYbTnlQhjMHB7gE0obUanqyOgaBoeF2tOiY0/47pDzFxzx+xZ+lB4DFiu/DtryG4diQMSCl+7Ohg0zv4/SKl3ak9gmMRD5sf/RAPShPINOW9Yccr4mFSdUw+hyVTsQlvMT2cXKV4VAgnM174uqcEtITLNoYD1fs6KeTETiGMH6tjsZuzYTvgp/MbgQcfPUHTvF1p3j59PO5JSMD/Z4n3dc9OTgi/fMXohfAfMVIUbPZfwm+RMlxIhoQ9KSyu6yCpOOI+RbxdYlGjEH6EmTRUTBHCD8FrkzeKU23ynkYm/9qd3Ya3X+ngQMvKAVoQ9pxjFxj7xCS5hnjPiqs4OaAcyDC8PWAWiUyiArUJe/AsFUOjYMeFhvVloZj+ldBn+g2hqH5daFCfFxrSrw5d0meGPtWnh/r1KaGL+qTQgD4hdF4fF7qgp4T69KTQJ5v0F5T8RlDrDb981wvoIS2vINejSA2MSvxC1PT/hiaM0NzHnENMDP8Fg7HKA8bfcK8fhvz92B50EI+Sj282ObkVf5V8iaVuasVffVEwJ2es7cD8aOHqiJqyD+uoRZy6FF/wlv4i7WEcgvadx1i8Q4ZWlKVudKq7XGoR7/74T+fRxjuuXHYJPzoA8nndnNfWqS4vaAxNl5H6698D3SxA+6j5DZRpWjGvpnYWcziPjofxw1RGUyfOBrQUR0SM1p4hHfp8xqRCqF0gm2oaxmlIwhg3KiC/arP15SirAehCZhPP0r1gqMk8TKAV3ywQOZAmE1SepIC2DOBgwIkQqyNKOlsMU1PCe6qIhYCyy2WYRxNsU73gykHs9xXYmgpwHrIHBs9YLFsXR8RyazOrWDBIEfA0jvFkCUi/zqHucsJWMEp5Kb1JxxbKJ3z4VMPvcDuQo6SOkxYqD2QZ8jz38VXayhxluSE7VyFGP2MY/cT8lVPLqA1Pg0Q2SGkcXnEWvosXwsxgQ7w04wobkkOZbwMcZYQH4HUefrbS+Wfmiz8sAAYs+dOudNUliyszaseTNPGw3Mci/Z4U5EvlpKvpPQO2/Z9tuOff2lzbowpxnpDbnnsA+Jg6QVvD8/pf0YzFo87cElf7oFNbczALUk7hmYl2V4fd1rQcMdRZyCGdyFONZESEko/PHHYb6j+GrXvoTC+tQIUMLKoLAeLRfojkoYIi06lW8bULNG6qGGmZuj3VPnFBGaenKXdwNm0lr9qBpu4+JLR3c7ntvU9DE8elxhU2KYl0aEtc4sXtBbuzmk/JC90D2iZ7kZ60uqhRtEmD4oXtuaI3JieDXNf5BbLTU+Gs3Y5qU0RPFp656GCtZb62Xbuf1/1atkus4ren5V5Qp2ELs/f7eXVxiwuWhn3JQeOmiF5++w14F1ye5W7Tqu2F0F+h2d+B7dkLvKyXdHIRu2hz9ImXag9bPETLnmJ2cAA6WJk4vZYpWhHfOx06YFiqcAnPjEM6xO8QYmgwieQWu9qjTrE0Q6vvzKqbRrwZLUm5B+0C7DNEu+Ue07++/S4o8mtLkjQFUSv27ajQuIl6SuNy4BWFYkctOiNW7cbmxCEe25Er9tXNj9fdnuFuU93LU+TUwsa8FJiRuhpH+W8wytW86sgtzbD6sQvVIItq4op2TrnffYqxpgCIaNXb7Ulme9OBHLXEpQzC1upHDj2o+bKY4O3TnmUrX9EPQlWe4qnqk9M8PqcQZhdMvH29P0fGf5Og9KDYWAGSoBuZ0CEQ2UykR7VHJ7gAXeJU7CS2ezosf5rhPWt4oyv1crAnSEU/sHVB+zXzi8bs8mTxISc0EPb8xERXEtvqUZtWZheeiegZjc9NQYA2IfxtjHp+Zo2HX+VoF4/Vf0C83eQwiGvIrm8hpWcR9Dj535hku8N9yvDSP7EdfoB3DDrONzVQ3LowM2FPDgsYYZwakCKE32eR+z3oaFK605S2S4wsMLp3IDS8ST8fuqwPgpD5FATLeRA0H4OQ6QVh8z4SBdiennzTywQa9MeJRwyLwRrKx0PBuun0P08bVwQr/WqO+cmrV1qjzD9U2Ps76/MhU9EcbhOU7r78xlSbbcdLrej40k/jpSXxkvQtPLL5Fvrnae07htHYEEuprC1oGsZ+doz306qPzUOY6XTOmC5vsrpcqy41fVE4TvwDJ/p809HbNMw67KA9Uebcf15lXluzYhJzKBbq6fSVU+hgnMLS1TUWqWXsY/ZuKQ8WuCOZHVq2T1Xe6VNL+0A3KQflJMcfaBivHDVOnFNKo4aeDpaWcthwD5z4CL1S6czMf1OfSMo5Is6piM4ZHv+GPE6JZIhdyIKo2CU/SGYg4C+q86ZZ5015s+5UvsXbWC7kiV21fdBysdUybaTMbNEHLTLpb8ESxuN2yGGLmIZeM7oevbNkvUu1k9UuEATS++oMNsjVLuJSPjPAyJYyyB5mFJD6vWvmlOJ4XpUXsHudpq1QsoZ44uOcAPuBPIIfhlTaOf1DNK8/b+xu2LvGbcw5Kk+yAAPQUE6N7nAcKg4fahgEO4fcNsiRcbmlfeR83CIrjaLeV41fksGvgZB1nLiOl7eACcmsr4Z55FW0DWNa/XIws2CfztnSskaFf8OC7MaNU8XPHq8vBIPRrLaH2R1m7dnThgVoIY+HSlB19nrO8otFoR+efJNTH+CgQ/JNtIWFZo3piXFjbB2vQoUyrKCW8da4qk1jbPyIMdYwp7FhvE0ez6wt0EM/SRMT7LJYWn3LGvSRQZX0UZss7VvoYtSea7FsMuYAPHEu7SZ2+U0ar45TN0xEOxfMf7nP8RqaspD1FbBk+/Ebl9oDdnWFPF2cgbYOoBt0W2Z0yamW+QM5Kq+t4moSvolKmGoTIBtN1vlddgmXJ2/nnlH0rPYhR/t7Tseb+iKSCvtAbK+f6bmFq5tW5iunj0XZt3bwrOB5phHzajGndPJNEeRQ2kNZOfghxNoOUsSTape2K0uMqt7Y9sVxSNMRUiZC2hiHJO8YA0VsiNW+SpaJbIxCOIDfy2K6RlR50GVIKcqDTptcQQrEqHyOJrGvB1rWQ4mLVPCaNBEk6gvITXMvtJTxwjPHQdgu8GUxJU5rQm2kl4XQlfILBJX1ou7ie9/ArBonI/qLuZeUc1ntw472D5yOHS5FNEhEnggM2QU7v42HDYD76BMQUSGuvdtpxlX4VW/U8qp1mFaCIUfxqupNZ9Dsi+Fsj5NXdi3SQCOuiGk+TvXF/ozjVF0djSi+DHVi50ombpnvSmnnjdKYfFLNZyN/GJGr84rHkFKhSDxY228GP6rFePTbUsSrNfwCx4IiTtuQwoNq9RBOVU+KGxjZwazSq3bSGTnI74AHY1yp8P02sVPOoW0n46zQPIl+fcZICGpboiRYj9cI95uHyn6ahLfQ8SSzUxpP6mLKuTRV7gFSlXsS4yQ8Dd1yPR4xB/HwtgcgXHgmfsR8G6Seezbx+K3Lp3lf9/lp06eMPlTvaYQuPLOo/QNuLPRxDPpp/Yk44B8+Y13RtxTyl5hdQjrovbMw2OC2YCFi4KpZGFQLM9C8j4OafWz0i1qhwlBOtZ++h1EglXj6jLeSW3NK8As0LnhqLTYeULqoo5CzKbzRUZg8Tt3JdxTOtXUUXjOuo3AeJJd3FC6xKW2FJB3bgUnMo0lce2Sbp+Go0DwO6dR7DGFjCANZrm3iNE5UvT0vsIrD9UlkuNPbzZStzTgeWsFGA2LMT0q7NafGhmNXknFAOdpeNqLrEkakbOVtjVvnNsaHpGxdbouPaaLjpHig9rgBGlQ+tq//kZ5C2JtyZ7ctbOy6F9QHwgNXkPzK4LBUttvxpF1a/yQvjy8zMo9YYeRE7iYd7dFk5YNZ7R+kOJaEcUjY0Kam7Ha0FHHsG1NakdNH5843PzMlNB9CAi/i/w/GrwbCkEoAgENLxb1/XFRl1gA+AzMw6uCMCoqKSkploUaNKOOIjcIgldilkRlJQduMZidrTe9VKkBowLhcp3XfbNfafpG1b721rZWpba2BKKNppWVp6Rbt8rYPjRWli6MQ93vOuXeGYbR9P99/vl8/H5l7zz3Pr/P8Oud5zg8oOs/n6NTBqKh6DOTrs5hDNmWQgBb1w3yhfj6hdrGuNri2vUBX13BK0Ht7lgaHSm10geZr+TenusAM+WSZzwPp5EZ3pG4zxXlXyioDgrnYYauEcauDR8NArR69SqkVP1suMASHIl4gAQdAnq833rQZXfXJ1OFyykGSEoMjBisowsRgY2GOwFjbS3VHF2HXg5SLnTHOt9Gg4Yf6FxqhpuhHDFoWsOupf0Nr/yHPYvcD56E4ENPV9affBP2wd4VymdfQ4pJ+bC+AFe5OZthLutdS4WpxuFTowZud4bYk8o4wUkoi33yFa4REdn4aLCEJIJba9JpU9AyAq2/ku4E9iuwiCK0Fhh77mjgh2Ve4Jg6K0AJNYZmQ7Dr82F6+T6dR7udgrvqLutm9yM3uchhhG2wqSa5fop0gTCRHtbDJdEviQbLd082f4jDjGoOut4FGtci0JqLn9DvW/HyI/M+qjtqS2TOy6rZWBarOUggUH4W3PgYIeHeGQXFReItjgIBnixThQUPkCOqUS+GAnTQAjY/G/nf/JXDA/ioMjfeMicYOXAoH7NcHoO5o7CcuhQO2rz/SFHME9b4YIOAtC4N0UXQoiAECniUMMkThTYwBAt4wFRTueCN2PE+HV+fQPKSuUvcCcNbCFdQXqHRgZCfI356Zejo10tNqxztCvpVrfra0QNdjGQb2vKJsOh2z4Sf7mI4f42NJvLGQPJDvQT9GbXtG0l8=
*/