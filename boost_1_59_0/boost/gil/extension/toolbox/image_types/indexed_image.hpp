//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_INDEXED_IMAGE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_IMAGE_TYPES_INDEXED_IMAGE_HPP

#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>

#include <boost/gil/image.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/virtual_locator.hpp>
#include <boost/gil/detail/is_channel_integral.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <memory>

namespace boost { namespace gil {

template< typename Locator >
struct get_pixel_type_locator
{
    using type = mp11::mp_if
        <
            typename is_bit_aligned<typename Locator::value_type>::type,
            typename Locator::reference,
            typename Locator::value_type
        >;
};

// used for virtual locator
template< typename IndicesLoc
        , typename PaletteLoc
        >
struct indexed_image_deref_fn_base
{
    using indices_locator_t = IndicesLoc;
    using palette_locator_t = PaletteLoc;
    //using index_t = typename get_pixel_type_locator<indices_locator_t>::type;

    using const_t = indexed_image_deref_fn_base<IndicesLoc, PaletteLoc>;
    using value_type = typename PaletteLoc::value_type;
    using reference = value_type;
    using const_reference = value_type;
    using argument_type = point_t;
    using result_type = reference;

    static const bool is_mutable = false;

    indexed_image_deref_fn_base() {}

    indexed_image_deref_fn_base( const indices_locator_t& indices_loc
                               , const palette_locator_t& palette_loc
                               )
    : _indices_loc( indices_loc )
    , _palette_loc( palette_loc )
    {}

    void set_indices( const indices_locator_t& indices_loc ) { _indices_loc = indices_loc; }
    void set_palette( const palette_locator_t& palette_loc ) { _palette_loc = palette_loc; }

    const indices_locator_t& indices() const { return _indices_loc; }
    const palette_locator_t& palette() const { return _palette_loc; }

protected:

    indices_locator_t _indices_loc;
    palette_locator_t _palette_loc;
};


// used for virtual locator
template< typename IndicesLoc
        , typename PaletteLoc
        , typename Enable = void // there is specialization for integral indices
        >
struct indexed_image_deref_fn : indexed_image_deref_fn_base< IndicesLoc
                                                           , PaletteLoc
                                                           >
{
    using base_t = indexed_image_deref_fn_base
        <
            IndicesLoc,
            PaletteLoc
        >;

    indexed_image_deref_fn()
    : base_t()
    {}

    indexed_image_deref_fn( const typename base_t::indices_locator_t& indices_loc
                          , const typename base_t::palette_locator_t& palette_loc
                          )
    : base_t( indices_loc
            , palette_loc
            )
    {}

    typename base_t::result_type operator()( const point_t& p ) const
    {
        return * this->_palette_loc.xy_at( at_c<0>( *this->_indices_loc.xy_at( p )), 0 );
    }
};


template <typename IndicesLoc, typename PaletteLoc>
struct indexed_image_deref_fn
<
    IndicesLoc,
    PaletteLoc,
    typename std::enable_if
    <
        detail::is_channel_integral<typename IndicesLoc::value_type>::value
    >::type
> : indexed_image_deref_fn_base<IndicesLoc, PaletteLoc>
{
    using base_t = indexed_image_deref_fn_base<IndicesLoc, PaletteLoc>;

    indexed_image_deref_fn() : base_t() {}

    indexed_image_deref_fn(
        typename base_t::indices_locator_t const& indices_loc,
        typename base_t::palette_locator_t const& palette_loc)
        : base_t(indices_loc, palette_loc)
    {
    }

    typename base_t::result_type operator()(point_t const& p) const
    {
        return *this->_palette_loc.xy_at(*this->_indices_loc.xy_at(p), 0);
    }
};

template< typename IndicesLoc
        , typename PaletteLoc
        >
struct indexed_image_locator_type
{
    using type = virtual_2d_locator
        <
            indexed_image_deref_fn<IndicesLoc, PaletteLoc>,
            false
        >;
};

template< typename Locator > // indexed_image_locator_type< ... >::type
class indexed_image_view : public image_view< Locator >
{
public:

    using deref_fn_t = typename Locator::deref_fn_t;
    using indices_locator_t = typename deref_fn_t::indices_locator_t;
    using palette_locator_t = typename deref_fn_t::palette_locator_t;

    using const_t = indexed_image_view<Locator>;

    using indices_view_t = image_view<indices_locator_t>;
    using palette_view_t = image_view<palette_locator_t>;

    indexed_image_view()
    : image_view< Locator >()
    , _num_colors( 0 )
    {}

    indexed_image_view( const point_t& dimensions
                      , std::size_t    num_colors
                      , const Locator& locator
                      )
    : image_view< Locator >( dimensions, locator )
    , _num_colors( num_colors )
    {}

    template< typename IndexedView >
    indexed_image_view( const IndexedView& iv )
    : image_view< Locator >( iv )
    , _num_colors( iv._num_colors )
    {}

    std::size_t num_colors() const { return _num_colors; }


    const indices_locator_t& indices() const { return get_deref_fn().indices(); }
    const palette_locator_t& palette() const { return get_deref_fn().palette(); }

    indices_view_t get_indices_view() const { return indices_view_t(this->dimensions(), indices() );}
    palette_view_t get_palette_view() const { return palette_view_t(point_t(num_colors(), 1), palette());}

private:

    const deref_fn_t& get_deref_fn() const { return this->pixels().deref_fn(); }

private:

    template< typename Locator2 > friend class indexed_image_view;

    std::size_t _num_colors;
};

// build an indexed_image_view from two views
template<typename Index_View, typename Palette_View>
indexed_image_view
<
    typename indexed_image_locator_type
    <
        typename Index_View::locator
        , typename Palette_View::locator
    >::type
>
    view(Index_View iv, Palette_View pv)
{
    using view_t = indexed_image_view
        <
            typename indexed_image_locator_type
                <
                    typename Index_View::locator,
                    typename Palette_View::locator
                >::type
        >;

    using defer_fn_t = indexed_image_deref_fn
        <
            typename Index_View::locator,
            typename Palette_View::locator
        >;

    return view_t(
        iv.dimensions()
        , pv.dimensions().x
        , typename view_t::locator(point_t(0, 0), point_t(1, 1), defer_fn_t(iv.xy_at(0, 0), pv.xy_at(0, 0)))
    );
}

template< typename Index
        , typename Pixel
        , typename IndicesAllocator = std::allocator< unsigned char >
        , typename PalleteAllocator = std::allocator< unsigned char >
        >
class indexed_image
{
public:

    using indices_t = image<Index, false, IndicesAllocator>;
    using palette_t = image<Pixel, false, PalleteAllocator>;

    using indices_view_t = typename indices_t::view_t;
    using palette_view_t = typename palette_t::view_t;

    using indices_const_view_t = typename indices_t::const_view_t;
    using palette_const_view_t = typename palette_t::const_view_t;

    using indices_locator_t = typename indices_view_t::locator;
    using palette_locator_t = typename palette_view_t::locator;

    using locator_t = typename indexed_image_locator_type
        <
            indices_locator_t,
            palette_locator_t
        >::type;

    using x_coord_t = typename indices_t::coord_t;
    using y_coord_t = typename indices_t::coord_t;


    using view_t = indexed_image_view<locator_t>;
    using const_view_t = typename view_t::const_t;

    indexed_image( const x_coord_t   width = 0
                 , const y_coord_t   height = 0
                 , const std::size_t num_colors = 1
                 , const std::size_t indices_alignment = 0
                 , const std::size_t palette_alignment = 0
                 )
    : _indices( width     , height, indices_alignment, IndicesAllocator() )
    , _palette( num_colors,      1, palette_alignment, PalleteAllocator() )
    {
        init( point_t( width, height ), num_colors );
    }

    indexed_image( const point_t&    dimensions
                 , const std::size_t num_colors = 1
                 , const std::size_t indices_alignment = 0
                 , const std::size_t palette_alignment = 0
                 )
    : _indices( dimensions,    indices_alignment, IndicesAllocator() )
    , _palette( num_colors, 1, palette_alignment, PalleteAllocator() )
    {
        init( dimensions, num_colors );
    }

    indexed_image( const indexed_image& img )
    : _indices( img._indices )
    , _palette( img._palette )
    {}

    template <typename Pixel2, typename Index2>
    indexed_image( const indexed_image< Pixel2, Index2 >& img )
    {
        _indices = img._indices;
        _palette = img._palette;
    }

    indexed_image& operator= ( const indexed_image& img )
    {
        _indices = img._indices;
        _palette = img._palette;

        return *this;
    }

    indices_const_view_t get_indices_const_view() const { return static_cast< indices_const_view_t >( _view.get_indices_view()); }
    palette_const_view_t get_palette_const_view() const { return static_cast< palette_const_view_t >( _view.get_palette_view()); }

    indices_view_t get_indices_view() { return _view.get_indices_view(); }
    palette_view_t get_palette_view() { return _view.get_palette_view(); }

public:

    view_t _view;

private:

    void init( const point_t&    dimensions
             , const std::size_t num_colors
             )
    {
        using defer_fn_t = indexed_image_deref_fn
            <
                indices_locator_t,
                palette_locator_t
            >;

        defer_fn_t deref_fn( view( _indices ).xy_at( 0, 0 )
                           , view( _palette ).xy_at( 0, 0 )
                           );

        locator_t locator( point_t( 0, 0 ) // p
                         , point_t( 1, 1 ) // step
                         , deref_fn
                         );

        _view = view_t( dimensions
                      , num_colors
                      , locator
                      );
    }

private:

    indices_t _indices;
    palette_t _palette;
};

template< typename Index
        , typename Pixel
        >
inline
const typename indexed_image< Index, Pixel >::view_t& view( indexed_image< Index, Pixel >& img )
{
    return img._view;
}

template< typename Index
        , typename Pixel
        >
inline
const typename indexed_image< Index, Pixel >::const_view_t const_view( indexed_image< Index, Pixel >& img )
{
    return static_cast< const typename indexed_image< Index, Pixel >::const_view_t>( img._view );
}

// Whole image has one color and all indices are set to 0.
template< typename Locator
        , typename Value
        >
void fill_pixels( const indexed_image_view< Locator >& view
                , const Value&                         value
                )
{
    using view_t = indexed_image_view<Locator>;

    fill_pixels( view.get_indices_view(), typename view_t::indices_view_t::value_type( 0 ));
    *view.get_palette_view().begin() = value;
}

} // namespace gil
} // namespace boost

#endif

/* indexed_image.hpp
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
*/