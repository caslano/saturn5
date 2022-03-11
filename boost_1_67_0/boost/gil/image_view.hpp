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