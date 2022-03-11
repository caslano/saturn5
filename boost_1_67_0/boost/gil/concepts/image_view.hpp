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