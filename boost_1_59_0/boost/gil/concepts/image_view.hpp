//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_IMAGE_VIEW_HPP
#define BOOST_GIL_CONCEPTS_IMAGE_VIEW_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/pixel.hpp>
#include <boost/gil/concepts/pixel_dereference.hpp>
#include <boost/gil/concepts/pixel_iterator.hpp>
#include <boost/gil/concepts/pixel_locator.hpp>
#include <boost/gil/concepts/point.hpp>
#include <boost/gil/concepts/detail/utility.hpp>

#include <cstddef>
#include <iterator>
#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

namespace boost { namespace gil {

/// \defgroup ImageViewNDConcept ImageViewNDLocatorConcept
/// \ingroup ImageViewConcept
/// \brief N-dimensional range

/// \defgroup ImageView2DConcept ImageView2DLocatorConcept
/// \ingroup ImageViewConcept
/// \brief 2-dimensional range

/// \defgroup PixelImageViewConcept ImageViewConcept
/// \ingroup ImageViewConcept
/// \brief 2-dimensional range over pixel data

/// \ingroup ImageViewNDConcept
/// \brief N-dimensional view over immutable values
///
/// \code
/// concept RandomAccessNDImageViewConcept<Regular View>
/// {
///     typename value_type;
///     typename reference;       // result of dereferencing
///     typename difference_type; // result of operator-(iterator,iterator) (1-dimensional!)
///     typename const_t;  where RandomAccessNDImageViewConcept<View>; // same as View, but over immutable values
///     typename point_t;  where PointNDConcept<point_t>; // N-dimensional point
///     typename locator;  where RandomAccessNDLocatorConcept<locator>; // N-dimensional locator.
///     typename iterator; where RandomAccessTraversalConcept<iterator>; // 1-dimensional iterator over all values
///     typename reverse_iterator; where RandomAccessTraversalConcept<reverse_iterator>;
///     typename size_type;       // the return value of size()
///
///     // Equivalent to RandomAccessNDLocatorConcept::axis
///     template <size_t D> struct axis {
///         typename coord_t = point_t::axis<D>::coord_t;
///         typename iterator; where RandomAccessTraversalConcept<iterator>;   // iterator along D-th axis.
///         where SameType<coord_t, iterator::difference_type>;
///         where SameType<iterator::value_type,value_type>;
///     };
///
///     // Defines the type of a view similar to this type, except it invokes Deref upon dereferencing
///     template <PixelDereferenceAdaptorConcept Deref> struct add_deref {
///         typename type;        where RandomAccessNDImageViewConcept<type>;
///         static type make(const View& v, const Deref& deref);
///     };
///
///     static const size_t num_dimensions = point_t::num_dimensions;
///
///     // Create from a locator at the top-left corner and dimensions
///     View::View(const locator&, const point_type&);
///
///     size_type        View::size()       const; // total number of elements
///     reference        operator[](View, const difference_type&) const; // 1-dimensional reference
///     iterator         View::begin()      const;
///     iterator         View::end()        const;
///     reverse_iterator View::rbegin()     const;
///     reverse_iterator View::rend()       const;
///     iterator         View::at(const point_t&);
///     point_t          View::dimensions() const; // number of elements along each dimension
///     bool             View::is_1d_traversable() const;   // can an iterator over the first dimension visit each value? I.e. are there gaps between values?
///
///     // iterator along a given dimension starting at a given point
///     template <size_t D> View::axis<D>::iterator View::axis_iterator(const point_t&) const;
///
///     reference operator()(View,const point_t&) const;
/// };
/// \endcode
template <typename View>
struct RandomAccessNDImageViewConcept
{
    void constraints()
    {
        gil_function_requires<Regular<View>>();

        using value_type = typename View::value_type;
        using reference = typename View::reference; // result of dereferencing
        using pointer = typename View::pointer;
        using difference_type = typename View::difference_type; // result of operator-(1d_iterator,1d_iterator)
        using const_t = typename View::const_t; // same as this type, but over const values
        using point_t = typename View::point_t; // N-dimensional point
        using locator = typename View::locator; // N-dimensional locator
        using iterator = typename View::iterator;
        using const_iterator = typename View::const_iterator;
        using reverse_iterator = typename View::reverse_iterator;
        using size_type = typename View::size_type;
        static const std::size_t N=View::num_dimensions;

        gil_function_requires<RandomAccessNDLocatorConcept<locator>>();
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<iterator>>();
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<reverse_iterator>>();

        using first_it_type = typename View::template axis<0>::iterator;
        using last_it_type = typename View::template axis<N-1>::iterator;
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<first_it_type>>();
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<last_it_type>>();

//        static_assert(typename std::iterator_traits<first_it_type>::difference_type, typename point_t::template axis<0>::coord_t>::value, "");
//        static_assert(typename std::iterator_traits<last_it_type>::difference_type, typename point_t::template axis<N-1>::coord_t>::value, "");

        // point_t must be an N-dimensional point, each dimension of which must have the same type as difference_type of the corresponding iterator
        gil_function_requires<PointNDConcept<point_t>>();
        static_assert(point_t::num_dimensions == N, "");
        static_assert(std::is_same
            <
                typename std::iterator_traits<first_it_type>::difference_type,
                typename point_t::template axis<0>::coord_t
            >::value, "");
        static_assert(std::is_same
            <
                typename std::iterator_traits<last_it_type>::difference_type,
                typename point_t::template axis<N-1>::coord_t
            >::value, "");

        point_t p;
        locator lc;
        iterator it;
        reverse_iterator rit;
        difference_type d; detail::initialize_it(d); ignore_unused_variable_warning(d);

        View(p,lc); // view must be constructible from a locator and a point

        p = view.dimensions();
        lc = view.pixels();
        size_type sz = view.size(); ignore_unused_variable_warning(sz);
        bool is_contiguous = view.is_1d_traversable();
        ignore_unused_variable_warning(is_contiguous);

        it = view.begin();
        it = view.end();
        rit = view.rbegin();
        rit = view.rend();

        reference r1 = view[d]; ignore_unused_variable_warning(r1); // 1D access
        reference r2 = view(p); ignore_unused_variable_warning(r2); // 2D access

        // get 1-D iterator of any dimension at a given pixel location
        first_it_type fi = view.template axis_iterator<0>(p);
        ignore_unused_variable_warning(fi);
        last_it_type li = view.template axis_iterator<N-1>(p);
        ignore_unused_variable_warning(li);

        using deref_t = PixelDereferenceAdaptorArchetype<typename View::value_type>;
        using dtype = typename View::template add_deref<deref_t>::type;
    }
    View view;
};

/// \ingroup ImageView2DConcept
/// \brief 2-dimensional view over immutable values
///
/// \code
/// concept RandomAccess2DImageViewConcept<RandomAccessNDImageViewConcept View> {
///     where num_dimensions==2;
///
///     typename x_iterator = axis<0>::iterator;
///     typename y_iterator = axis<1>::iterator;
///     typename x_coord_t  = axis<0>::coord_t;
///     typename y_coord_t  = axis<1>::coord_t;
///     typename xy_locator = locator;
///
///     x_coord_t View::width()  const;
///     y_coord_t View::height() const;
///
///     // X-navigation
///     x_iterator View::x_at(const point_t&) const;
///     x_iterator View::row_begin(y_coord_t) const;
///     x_iterator View::row_end  (y_coord_t) const;
///
///     // Y-navigation
///     y_iterator View::y_at(const point_t&) const;
///     y_iterator View::col_begin(x_coord_t) const;
///     y_iterator View::col_end  (x_coord_t) const;
///
///     // navigating in 2D
///     xy_locator View::xy_at(const point_t&) const;
///
///     // (x,y) versions of all methods taking point_t
///     View::View(x_coord_t,y_coord_t,const locator&);
///     iterator View::at(x_coord_t,y_coord_t) const;
///     reference operator()(View,x_coord_t,y_coord_t) const;
///     xy_locator View::xy_at(x_coord_t,y_coord_t) const;
///     x_iterator View::x_at(x_coord_t,y_coord_t) const;
///     y_iterator View::y_at(x_coord_t,y_coord_t) const;
/// };
/// \endcode
template <typename View>
struct RandomAccess2DImageViewConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccessNDImageViewConcept<View>>();
        static_assert(View::num_dimensions == 2, "");

        // TODO: This executes the requirements for RandomAccessNDLocatorConcept again. Fix it to improve compile time
        gil_function_requires<RandomAccess2DLocatorConcept<typename View::locator>>();

        using dynamic_x_step_t = typename dynamic_x_step_type<View>::type;
        using dynamic_y_step_t = typename dynamic_y_step_type<View>::type;
        using transposed_t = typename transposed_type<View>::type;
        using x_iterator = typename View::x_iterator;
        using y_iterator = typename View::y_iterator;
        using x_coord_t = typename View::x_coord_t;
        using y_coord_t = typename View::y_coord_t;
        using xy_locator = typename View::xy_locator;

        x_coord_t xd = 0; ignore_unused_variable_warning(xd);
        y_coord_t yd = 0; ignore_unused_variable_warning(yd);
        x_iterator xit;
        y_iterator yit;
        typename View::point_t d;

        View(xd, yd, xy_locator()); // constructible with width, height, 2d_locator

        xy_locator lc = view.xy_at(xd, yd);
        lc = view.xy_at(d);

        typename View::reference r = view(xd, yd);
        ignore_unused_variable_warning(r);
        xd = view.width();
        yd = view.height();

        xit = view.x_at(d);
        xit = view.x_at(xd,yd);
        xit = view.row_begin(xd);
        xit = view.row_end(xd);

        yit = view.y_at(d);
        yit = view.y_at(xd,yd);
        yit = view.col_begin(xd);
        yit = view.col_end(xd);
    }
    View view;
};

/// \brief GIL view as Collection.
///
/// \see https://www.boost.org/libs/utility/Collection.html
///
template <typename View>
struct CollectionImageViewConcept
{
    void constraints()
    {
        using value_type = typename View::value_type;
        using iterator = typename View::iterator;
        using const_iterator =  typename View::const_iterator;
        using reference = typename View::reference;
        using const_reference = typename View::const_reference;
        using pointer = typename View::pointer;
        using difference_type = typename View::difference_type;
        using size_type=  typename View::size_type;

        iterator i;
        i = view1.begin();
        i = view2.end();

        const_iterator ci;
        ci = view1.begin();
        ci = view2.end();

        size_type s;
        s = view1.size();
        s = view2.size();
        ignore_unused_variable_warning(s);

        view1.empty();

        view1.swap(view2);
    }
    View view1;
    View view2;
};

/// \brief GIL view as ForwardCollection.
///
/// \see https://www.boost.org/libs/utility/Collection.html
///
template <typename View>
struct ForwardCollectionImageViewConcept
{
    void constraints()
    {
        gil_function_requires<CollectionImageViewConcept<View>>();

        using reference = typename View::reference;
        using const_reference = typename View::const_reference;

        reference r = view.front();
        ignore_unused_variable_warning(r);

        const_reference cr = view.front();
        ignore_unused_variable_warning(cr);
    }
    View view;
};

/// \brief GIL view as ReversibleCollection.
///
/// \see https://www.boost.org/libs/utility/Collection.html
///
template <typename View>
struct ReversibleCollectionImageViewConcept
{
    void constraints()
    {
        gil_function_requires<CollectionImageViewConcept<View>>();

        using reverse_iterator = typename View::reverse_iterator;
        using reference = typename View::reference;
        using const_reference = typename View::const_reference;

        reverse_iterator i;
        i = view.rbegin();
        i = view.rend();

        reference r = view.back();
        ignore_unused_variable_warning(r);

        const_reference cr = view.back();
        ignore_unused_variable_warning(cr);
    }
    View view;
};

/// \ingroup PixelImageViewConcept
/// \brief GIL's 2-dimensional view over immutable GIL pixels
/// \code
/// concept ImageViewConcept<RandomAccess2DImageViewConcept View>
/// {
///     where PixelValueConcept<value_type>;
///     where PixelIteratorConcept<x_iterator>;
///     where PixelIteratorConcept<y_iterator>;
///     where x_coord_t == y_coord_t;
///
///     typename coord_t = x_coord_t;
///
///     std::size_t View::num_channels() const;
/// };
/// \endcode
template <typename View>
struct ImageViewConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccess2DImageViewConcept<View>>();

        // TODO: This executes the requirements for RandomAccess2DLocatorConcept again. Fix it to improve compile time
        gil_function_requires<PixelLocatorConcept<typename View::xy_locator>>();

        static_assert(std::is_same<typename View::x_coord_t, typename View::y_coord_t>::value, "");

        using coord_t = typename View::coord_t; // 1D difference type (same for all dimensions)
        std::size_t num_chan = view.num_channels(); ignore_unused_variable_warning(num_chan);
    }
    View view;
};

namespace detail {

/// \tparam View Models RandomAccessNDImageViewConcept
template <typename View>
struct RandomAccessNDImageViewIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<detail::RandomAccessNDLocatorIsMutableConcept<typename View::locator>>();

        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept<typename View::iterator>>();

        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept
            <
                typename View::reverse_iterator
            >>();

        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept
            <
                typename View::template axis<0>::iterator
            >>();

        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept
            <
                typename View::template axis<View::num_dimensions - 1>::iterator
            >>();

        typename View::difference_type diff;
        initialize_it(diff);
        ignore_unused_variable_warning(diff);

        typename View::point_t pt;
        typename View::value_type v;
        initialize_it(v);

        view[diff] = v;
        view(pt) = v;
    }
    View view;
};

/// \tparam View Models RandomAccessNDImageViewConcept
template <typename View>
struct RandomAccess2DImageViewIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<detail::RandomAccessNDImageViewIsMutableConcept<View>>();
        typename View::x_coord_t xd = 0; ignore_unused_variable_warning(xd);
        typename View::y_coord_t yd = 0; ignore_unused_variable_warning(yd);
        typename View::value_type v; initialize_it(v);
        view(xd, yd) = v;
    }
    View view;
};

/// \tparam View Models ImageViewConcept
template <typename View>
struct PixelImageViewIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<detail::RandomAccess2DImageViewIsMutableConcept<View>>();
    }
};

} // namespace detail

/// \ingroup ImageViewNDConcept
/// \brief N-dimensional view over mutable values
///
/// \code
/// concept MutableRandomAccessNDImageViewConcept<RandomAccessNDImageViewConcept View>
/// {
///     where Mutable<reference>;
/// };
/// \endcode
template <typename View>
struct MutableRandomAccessNDImageViewConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccessNDImageViewConcept<View>>();
        gil_function_requires<detail::RandomAccessNDImageViewIsMutableConcept<View>>();
    }
};

/// \ingroup ImageView2DConcept
/// \brief 2-dimensional view over mutable values
///
/// \code
/// concept MutableRandomAccess2DImageViewConcept<RandomAccess2DImageViewConcept View>
///     : MutableRandomAccessNDImageViewConcept<View> {};
/// \endcode
template <typename View>
struct MutableRandomAccess2DImageViewConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccess2DImageViewConcept<View>>();
        gil_function_requires<detail::RandomAccess2DImageViewIsMutableConcept<View>>();
    }
};

/// \ingroup PixelImageViewConcept
/// \brief GIL's 2-dimensional view over mutable GIL pixels
///
/// \code
/// concept MutableImageViewConcept<ImageViewConcept View>
///     : MutableRandomAccess2DImageViewConcept<View> {};
/// \endcode
template <typename View>
struct MutableImageViewConcept
{
    void constraints()
    {
        gil_function_requires<ImageViewConcept<View>>();
        gil_function_requires<detail::PixelImageViewIsMutableConcept<View>>();
    }
};

/// \brief Returns whether two views are compatible
///
/// Views are compatible if their pixels are compatible.
/// Compatible views can be assigned and copy constructed from one another.
///
/// \tparam V1 Models ImageViewConcept
/// \tparam V2 Models ImageViewConcept
///
template <typename V1, typename V2>
struct views_are_compatible
    : pixels_are_compatible<typename V1::value_type, typename V2::value_type>
{
};

/// \ingroup ImageViewConcept
/// \brief Views are compatible if they have the same color spaces and compatible channel values.
///
/// Constness and layout are not important for compatibility.
///
/// \code
/// concept ViewsCompatibleConcept<ImageViewConcept V1, ImageViewConcept V2>
/// {
///     where PixelsCompatibleConcept<V1::value_type, P2::value_type>;
/// };
/// \endcode
template <typename V1, typename V2>
struct ViewsCompatibleConcept
{
    void constraints()
    {
        static_assert(views_are_compatible<V1, V2>::value, "");
    }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* image_view.hpp
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
*/