//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IMAGE_VIEW_HPP
#define BOOST_GIL_IMAGE_VIEW_HPP

#include <boost/gil/dynamic_step.hpp>
#include <boost/gil/iterator_from_2d.hpp>

#include <boost/assert.hpp>

#include <cstddef>
#include <iterator>

namespace boost { namespace gil {

////////////////////////////////////////////////////////////////////////////////////////
/// \class image_view
/// \ingroup ImageViewModel PixelBasedModel
/// \brief A lightweight object that interprets memory as a 2D array of pixels. Models ImageViewConcept,PixelBasedConcept,HasDynamicXStepTypeConcept,HasDynamicYStepTypeConcept,HasTransposedTypeConcept
///
/// Image view consists of a pixel 2D locator (defining the mechanism for navigating in 2D)
/// and the image dimensions.
///
/// Image views to images are what ranges are to STL containers. They are lightweight objects,
/// that don't own the pixels. It is the user's responsibility that the underlying data remains
/// valid for the lifetime of the image view.
///
/// Similar to iterators and ranges, constness of views does not extend to constness of pixels.
/// A const \p image_view does not allow changing its location in memory (resizing, moving) but does
/// not prevent one from changing the pixels. The latter requires an image view whose value_type
/// is const.
///
/// Images have interfaces consistent with STL 1D random access containers, so they can be used
/// directly in STL algorithms like:
/// \code
///  std::fill(img.begin(), img.end(), red_pixel);
/// \endcode
///
/// In addition, horizontal, vertical and 2D random access iterators are provided.
///
/// Note also that \p image_view does not require that its element type be a pixel. It could be
/// instantiated with a locator whose \p value_type models only \p Regular. In this case the image
/// view models the weaker RandomAccess2DImageViewConcept, and does not model PixelBasedConcept.
/// Many generic algorithms don't require the elements to be pixels.
///
////////////////////////////////////////////////////////////////////////////////////////
template <typename Loc>     // Models 2D Pixel Locator
class image_view
{
public:
    // aliases required by ConstRandomAccessNDImageViewConcept
    static const std::size_t num_dimensions=2;
    using value_type = typename Loc::value_type;
    using reference = typename Loc::reference;       // result of dereferencing
    using coord_t = typename Loc::coord_t;      // 1D difference type (same for all dimensions)
    using difference_type = coord_t; // result of operator-(1d_iterator,1d_iterator)
    using point_t = typename Loc::point_t;
    using locator = Loc;
    using const_t = image_view<typename Loc::const_t>;      // same as this type, but over const values
    template <std::size_t D> struct axis
    {
        using coord_t = typename Loc::template axis<D>::coord_t; // difference_type along each dimension
        using iterator = typename Loc::template axis<D>::iterator; // 1D iterator type along each dimension
    };
    using iterator = iterator_from_2d<Loc>;       // 1D iterator type for each pixel left-to-right inside top-to-bottom
    using const_iterator = typename const_t::iterator;  // may be used to examine, but not to modify values
    using const_reference = typename const_t::reference; // behaves as a const reference
    using pointer = typename std::iterator_traits<iterator>::pointer; // behaves as a pointer to the value type
    using reverse_iterator = std::reverse_iterator<iterator>;
    using size_type = std::size_t;

    // aliases required by ConstRandomAccess2DImageViewConcept
    using xy_locator = locator;
    using x_iterator = typename xy_locator::x_iterator;     // pixel iterator along a row
    using y_iterator = typename xy_locator::y_iterator;     // pixel iterator along a column
    using x_coord_t = typename xy_locator::x_coord_t;
    using y_coord_t = typename xy_locator::y_coord_t;

    template <typename Deref>
    struct add_deref
    {
        using type = image_view<typename Loc::template add_deref<Deref>::type>;
        static type make(image_view<Loc> const& view, Deref const& d)
        {
            return type(view.dimensions(), Loc::template add_deref<Deref>::make(view.pixels(), d));
        }
    };

    image_view() : _dimensions(0,0) {}
    image_view(image_view const& img_view)
        : _dimensions(img_view.dimensions()), _pixels(img_view.pixels())
    {}

    template <typename View>
    image_view(View const& view) : _dimensions(view.dimensions()), _pixels(view.pixels()) {}

    template <typename L2>
    image_view(point_t const& dims, L2 const& loc) : _dimensions(dims), _pixels(loc) {}

    template <typename L2>
    image_view(coord_t width, coord_t height, L2 const& loc)
        : _dimensions(x_coord_t(width), y_coord_t(height)), _pixels(loc)
    {}

    template <typename View>
    image_view& operator=(View const& view)
    {
        _pixels = view.pixels();
        _dimensions = view.dimensions();
        return *this;
    }

    image_view& operator=(image_view const& view)
    {
        // TODO: Self-assignment protection?
        _pixels = view.pixels();
        _dimensions = view.dimensions();
        return *this;
    }

    template <typename View>
    bool operator==(View const &view) const
    {
        return pixels() == view.pixels() && dimensions() == view.dimensions();
    }

    template <typename View>
    bool operator!=(View const& view) const
    {
        return !(*this == view);
    }

    template <typename L2>
    friend void swap(image_view<L2> &lhs, image_view<L2> &rhs);

    /// \brief Exchanges the elements of the current view with those of \a other
    ///       in constant time.
    ///
    /// \note Required by the Collection concept
    /// \see  https://www.boost.org/libs/utility/Collection.html
    void swap(image_view<Loc>& other)
    {
        using boost::gil::swap;
        swap(*this, other);
    }

    auto dimensions() const -> point_t const&
    {
        return _dimensions;
    }

    auto pixels() const -> locator const&
    {
        return _pixels;
    }

    auto width() const -> x_coord_t
    {
        return dimensions().x;
    }

    auto height() const -> y_coord_t
    {
        return dimensions().y;
    }

    auto num_channels() const -> std::size_t
    {
        return gil::num_channels<value_type>::value;
    }

    bool is_1d_traversable() const
    {
        return _pixels.is_1d_traversable(width());
    }

    /// \brief Returns true if the view has no elements, false otherwise.
    ///
    /// \note Required by the Collection concept
    /// \see  https://www.boost.org/libs/utility/Collection.html
    bool empty() const
    {
        return !(width() > 0 && height() > 0);
    }

    /// \brief Returns a reference to the first element in raster order.
    ///
    /// \note Required by the ForwardCollection, since view model the concept.
    /// \see  https://www.boost.org/libs/utility/Collection.html
    auto front() const -> reference
    {
        BOOST_ASSERT(!empty());
        return *begin();
    }

    /// \brief Returns a reference to the last element in raster order.
    ///
    /// \note Required by the ForwardCollection, since view model the concept.
    /// \see  https://www.boost.org/libs/utility/Collection.html
    auto back() const -> reference
    {
        BOOST_ASSERT(!empty());
        return *rbegin();
    }

    //\{@
    /// \name 1D navigation
    auto size() const -> size_type
    {
        return width() * height();
    }

    auto begin() const -> iterator
    {
        return iterator(_pixels, _dimensions.x);
    }

    auto end() const -> iterator
    {
        // potential performance problem!
        return begin() + static_cast<difference_type>(size());
    }

    auto rbegin() const -> reverse_iterator
    {
        return reverse_iterator(end());
    }

    auto rend() const -> reverse_iterator
    {
        return reverse_iterator(begin());
    }

    auto operator[](difference_type i) const -> reference
    {
        BOOST_ASSERT(i < static_cast<difference_type>(size()));
        return begin()[i]; // potential performance problem!
    }

    auto at(difference_type i) const -> iterator
    {
        // UB if the specified increment advances non-incrementable iterator (i.e. past-the-end)
        BOOST_ASSERT(i < static_cast<difference_type>(size()));
        return begin() + i;
    }

    auto at(point_t const& p) const -> iterator
    {
        // UB if the specified coordinates advance non-incrementable iterator (i.e. past-the-end)
        BOOST_ASSERT(0 <= p.x && p.x < width());
        BOOST_ASSERT(0 <= p.y && p.y < height());
        return begin() + p.y * width() + p.x;
    }

    auto at(x_coord_t x, y_coord_t y) const -> iterator
    {
        // UB if the specified coordinates advance non-incrementable iterator (i.e. past-the-end)
        BOOST_ASSERT(0 <= x && x < width());
        BOOST_ASSERT(0 <= y && y < height());
        return begin() + y * width() + x;
    }
    //\}@

    //\{@
    /// \name 2-D navigation
    auto operator()(point_t const& p) const -> reference
    {
        BOOST_ASSERT(0 <= p.x && p.x < width());
        BOOST_ASSERT(0 <= p.y && p.y < height());
        return _pixels(p.x, p.y);
    }

    auto operator()(x_coord_t x, y_coord_t y) const -> reference
    {
        BOOST_ASSERT(0 <= x && x < width());
        BOOST_ASSERT(0 <= y && y < height());
        return _pixels(x, y);
    }

    template <std::size_t D>
    auto axis_iterator(point_t const& p) const -> typename axis<D>::iterator
    {
        // Allow request for iterators from inclusive range of [begin, end]
        BOOST_ASSERT(0 <= p.x && p.x <= width());
        BOOST_ASSERT(0 <= p.y && p.y <= height());
        return _pixels.template axis_iterator<D>(p);
    }

    auto xy_at(x_coord_t x, y_coord_t y) const -> xy_locator
    {
        // TODO: Are relative locations of neighbors with negative offsets valid? Sampling?
        BOOST_ASSERT(x < width());
        BOOST_ASSERT(y <= height());
        return _pixels + point_t(x, y);
    }

    auto xy_at(point_t const& p) const -> xy_locator
    {
        // TODO: Are relative locations of neighbors with negative offsets valid? Sampling?
        BOOST_ASSERT(p.x < width());
        BOOST_ASSERT(p.y < height());
        return _pixels + p;
    }
    //\}@

    //\{@
    /// \name X navigation
    auto x_at(x_coord_t x, y_coord_t y) const -> x_iterator
    {
        BOOST_ASSERT(0 <= x && x <= width()); // allow request for [begin, end] inclusive
        BOOST_ASSERT(0 <= y && y < height()); // TODO: For empty image/view, shouldn't we accept: row_begin(0) == view.row_end(0) ?
        return _pixels.x_at(x, y);
    }

    auto x_at(point_t const& p) const -> x_iterator
    {
        BOOST_ASSERT(0 <= p.x && p.x <= width()); // allow request for [begin, end] inclusive
        BOOST_ASSERT(0 <= p.y && p.y < height()); // TODO: For empty image/view, shouldn't we accept: row_begin(0) == view.row_end(0) ?
        return _pixels.x_at(p);
    }

    auto row_begin(y_coord_t y) const -> x_iterator
    {
        BOOST_ASSERT(0 <= y && y < height());
        return x_at(0, y);
    }

    auto row_end(y_coord_t y) const -> x_iterator
    {
        BOOST_ASSERT(0 <= y && y < height());
        return x_at(width(), y);
    }
    //\}@

    //\{@
    /// \name Y navigation
    auto y_at(x_coord_t x, y_coord_t y) const -> y_iterator
    {
        BOOST_ASSERT(0 <= x && x < width()); // TODO: For empty image/view, shouldn't we accept: view.col_begin(0) == view.col_end(0) ?
        BOOST_ASSERT(0 <= y && y <= height()); // allow request for [begin, end] inclusive
        return xy_at(x, y).y();
    }

    auto y_at(point_t const& p) const -> y_iterator
    {
        BOOST_ASSERT(0 <= p.x && p.x < width()); // TODO: For empty image/view, shouldn't we accept: view.col_begin(0) == view.col_end(0) ?
        BOOST_ASSERT(0 <= p.y && p.y <= height()); // allow request for [begin, end] inclusive
        return xy_at(p).y();
    }

    auto col_begin(x_coord_t x) const -> y_iterator
    {
        BOOST_ASSERT(0 <= x && x < width());
        return y_at(x, 0);
    }

    auto col_end(x_coord_t x) const -> y_iterator
    {
        BOOST_ASSERT(0 <= x && x < width());
        return y_at(x, height());
    }
    //\}@

private:
    template <typename L2>
    friend class image_view;

    point_t    _dimensions;
    xy_locator _pixels;
};

template <typename L2>
inline void swap(image_view<L2>& x, image_view<L2>& y) {
    using std::swap;
    swap(x._dimensions,y._dimensions);
    swap(x._pixels, y._pixels);            // TODO: Extend further
}

/////////////////////////////
//  PixelBasedConcept
/////////////////////////////

template <typename L>
struct channel_type<image_view<L> > : public channel_type<L> {};

template <typename L>
struct color_space_type<image_view<L> > : public color_space_type<L> {};

template <typename L>
struct channel_mapping_type<image_view<L> > : public channel_mapping_type<L> {};

template <typename L>
struct is_planar<image_view<L> > : public is_planar<L> {};

/////////////////////////////
//  HasDynamicXStepTypeConcept
/////////////////////////////

template <typename L>
struct dynamic_x_step_type<image_view<L>>
{
    using type = image_view<typename gil::dynamic_x_step_type<L>::type>;
};

/////////////////////////////
//  HasDynamicYStepTypeConcept
/////////////////////////////

template <typename L>
struct dynamic_y_step_type<image_view<L>>
{
    using type = image_view<typename gil::dynamic_y_step_type<L>::type>;
};

/////////////////////////////
//  HasTransposedTypeConcept
/////////////////////////////

template <typename L>
struct transposed_type<image_view<L>>
{
    using type = image_view<typename transposed_type<L>::type>;
};

}}  // namespace boost::gil

#endif

/* image_view.hpp
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
*/