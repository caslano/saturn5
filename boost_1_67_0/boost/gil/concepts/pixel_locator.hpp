//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_PIXEL_LOCATOR_HPP
#define BOOST_GIL_CONCEPTS_PIXEL_LOCATOR_HPP

#include <boost/gil/concepts/basic.hpp>
#include <boost/gil/concepts/concept_check.hpp>
#include <boost/gil/concepts/fwd.hpp>
#include <boost/gil/concepts/pixel.hpp>
#include <boost/gil/concepts/pixel_dereference.hpp>
#include <boost/gil/concepts/pixel_iterator.hpp>
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

/// \defgroup LocatorNDConcept RandomAccessNDLocatorConcept
/// \ingroup PixelLocatorConcept
/// \brief N-dimensional locator

/// \defgroup Locator2DConcept RandomAccess2DLocatorConcept
/// \ingroup PixelLocatorConcept
/// \brief 2-dimensional locator

/// \defgroup PixelLocator2DConcept PixelLocatorConcept
/// \ingroup PixelLocatorConcept
/// \brief 2-dimensional locator over pixel data

/// \ingroup LocatorNDConcept
/// \brief N-dimensional locator over immutable values
///
/// \code
/// concept RandomAccessNDLocatorConcept<Regular Loc>
/// {
///     typename value_type;        // value over which the locator navigates
///     typename reference;         // result of dereferencing
///     typename difference_type; where PointNDConcept<difference_type>; // return value of operator-.
///     typename const_t;           // same as Loc, but operating over immutable values
///     typename cached_location_t; // type to store relative location (for efficient repeated access)
///     typename point_t  = difference_type;
///
///     static const size_t num_dimensions; // dimensionality of the locator
///     where num_dimensions = point_t::num_dimensions;
///
///     // The difference_type and iterator type along each dimension. The iterators may only differ in
///     // difference_type. Their value_type must be the same as Loc::value_type
///     template <size_t D>
///     struct axis
///     {
///         typename coord_t = point_t::axis<D>::coord_t;
///         typename iterator; where RandomAccessTraversalConcept<iterator>; // iterator along D-th axis.
///         where iterator::value_type == value_type;
///     };
///
///     // Defines the type of a locator similar to this type, except it invokes Deref upon dereferencing
///     template <PixelDereferenceAdaptorConcept Deref>
///     struct add_deref
///     {
///         typename type;
///             where RandomAccessNDLocatorConcept<type>;
///         static type make(const Loc& loc, const Deref& deref);
///     };
///
///     Loc& operator+=(Loc&, const difference_type&);
///     Loc& operator-=(Loc&, const difference_type&);
///     Loc operator+(const Loc&, const difference_type&);
///     Loc operator-(const Loc&, const difference_type&);
///
///     reference operator*(const Loc&);
///     reference operator[](const Loc&, const difference_type&);
///
///     // Storing relative location for faster repeated access and accessing it
///     cached_location_t Loc::cache_location(const difference_type&) const;
///     reference operator[](const Loc&,const cached_location_t&);
///
///     // Accessing iterators along a given dimension at the current location or at a given offset
///     template <size_t D> axis<D>::iterator&       Loc::axis_iterator();
///     template <size_t D> axis<D>::iterator const& Loc::axis_iterator() const;
///     template <size_t D> axis<D>::iterator        Loc::axis_iterator(const difference_type&) const;
/// };
/// \endcode
template <typename Loc>
struct RandomAccessNDLocatorConcept
{
    void constraints()
    {
        gil_function_requires<Regular<Loc>>();

        // TODO: Should these be concept-checked instead of ignored? --mloskot

        using value_type = typename Loc::value_type;
        ignore_unused_variable_warning(value_type{});

        // result of dereferencing
        using reference = typename Loc::reference;
        //ignore_unused_variable_warning(reference{});

        // result of operator-(pixel_locator, pixel_locator)
        using difference_type = typename Loc::difference_type;
        ignore_unused_variable_warning(difference_type{});

        // type used to store relative location (to allow for more efficient repeated access)
        using cached_location_t = typename Loc::cached_location_t;
        ignore_unused_variable_warning(cached_location_t{});

        // same as this type, but over const values
        using const_t = typename Loc::const_t;
        ignore_unused_variable_warning(const_t{});

        // same as difference_type
        using point_t = typename Loc::point_t;
        ignore_unused_variable_warning(point_t{});

        static std::size_t const N = Loc::num_dimensions; ignore_unused_variable_warning(N);

        using first_it_type = typename Loc::template axis<0>::iterator;
        using last_it_type = typename Loc::template axis<N-1>::iterator;
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<first_it_type>>();
        gil_function_requires<boost_concepts::RandomAccessTraversalConcept<last_it_type>>();

        // point_t must be an N-dimensional point, each dimension of which must
        // have the same type as difference_type of the corresponding iterator
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

        difference_type d;
        loc += d;
        loc -= d;
        loc = loc + d;
        loc = loc - d;
        reference r1 = loc[d];  ignore_unused_variable_warning(r1);
        reference r2 = *loc;  ignore_unused_variable_warning(r2);
        cached_location_t cl = loc.cache_location(d);  ignore_unused_variable_warning(cl);
        reference r3 = loc[d];  ignore_unused_variable_warning(r3);

        first_it_type fi = loc.template axis_iterator<0>();
        fi = loc.template axis_iterator<0>(d);
        last_it_type li = loc.template axis_iterator<N-1>();
        li = loc.template axis_iterator<N-1>(d);

        using deref_t = PixelDereferenceAdaptorArchetype<typename Loc::value_type>;
        using dtype = typename Loc::template add_deref<deref_t>::type;
        // TODO: infinite recursion - FIXME?
        //gil_function_requires<RandomAccessNDLocatorConcept<dtype>>();
    }
    Loc loc;
};

/// \ingroup Locator2DConcept
/// \brief 2-dimensional locator over immutable values
///
/// \code
/// concept RandomAccess2DLocatorConcept<RandomAccessNDLocatorConcept Loc>
/// {
///     where num_dimensions==2;
///     where Point2DConcept<point_t>;
///
///     typename x_iterator = axis<0>::iterator;
///     typename y_iterator = axis<1>::iterator;
///     typename x_coord_t  = axis<0>::coord_t;
///     typename y_coord_t  = axis<1>::coord_t;
///
///     // Only available to locators that have dynamic step in Y
///     //Loc::Loc(const Loc& loc, y_coord_t);
///
///     // Only available to locators that have dynamic step in X and Y
///     //Loc::Loc(const Loc& loc, x_coord_t, y_coord_t, bool transposed=false);
///
///     x_iterator&       Loc::x();
///     x_iterator const& Loc::x() const;
///     y_iterator&       Loc::y();
///     y_iterator const& Loc::y() const;
///
///     x_iterator Loc::x_at(const difference_type&) const;
///     y_iterator Loc::y_at(const difference_type&) const;
///     Loc Loc::xy_at(const difference_type&) const;
///
///     // x/y versions of all methods that can take difference type
///     x_iterator        Loc::x_at(x_coord_t, y_coord_t) const;
///     y_iterator        Loc::y_at(x_coord_t, y_coord_t) const;
///     Loc               Loc::xy_at(x_coord_t, y_coord_t) const;
///     reference         operator()(const Loc&, x_coord_t, y_coord_t);
///     cached_location_t Loc::cache_location(x_coord_t, y_coord_t) const;
///
///     bool      Loc::is_1d_traversable(x_coord_t width) const;
///     y_coord_t Loc::y_distance_to(const Loc& loc2, x_coord_t x_diff) const;
/// };
/// \endcode
template <typename Loc>
struct RandomAccess2DLocatorConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccessNDLocatorConcept<Loc>>();
        static_assert(Loc::num_dimensions == 2, "");

        using dynamic_x_step_t = typename dynamic_x_step_type<Loc>::type;
        using dynamic_y_step_t = typename dynamic_y_step_type<Loc>::type;
        using transposed_t = typename transposed_type<Loc>::type;

        using cached_location_t = typename Loc::cached_location_t;
        gil_function_requires<Point2DConcept<typename Loc::point_t>>();

        using x_iterator = typename Loc::x_iterator;
        using y_iterator = typename Loc::y_iterator;
        using x_coord_t = typename Loc::x_coord_t;
        using y_coord_t = typename Loc::y_coord_t;

        x_coord_t xd = 0; ignore_unused_variable_warning(xd);
        y_coord_t yd = 0; ignore_unused_variable_warning(yd);

        typename Loc::difference_type d;
        typename Loc::reference r=loc(xd,yd);  ignore_unused_variable_warning(r);

        dynamic_x_step_t loc2(dynamic_x_step_t(), yd);
        dynamic_x_step_t loc3(dynamic_x_step_t(), xd, yd);

        using dynamic_xy_step_transposed_t = typename dynamic_y_step_type
            <
                typename dynamic_x_step_type<transposed_t>::type
            >::type;
        dynamic_xy_step_transposed_t loc4(loc, xd,yd,true);

        bool is_contiguous = loc.is_1d_traversable(xd);
        ignore_unused_variable_warning(is_contiguous);

        loc.y_distance_to(loc, xd);

        loc = loc.xy_at(d);
        loc = loc.xy_at(xd, yd);

        x_iterator xit = loc.x_at(d);
        xit = loc.x_at(xd, yd);
        xit = loc.x();

        y_iterator yit = loc.y_at(d);
        yit = loc.y_at(xd, yd);
        yit = loc.y();

        cached_location_t cl = loc.cache_location(xd, yd);
        ignore_unused_variable_warning(cl);
    }
    Loc loc;
};

/// \ingroup PixelLocator2DConcept
/// \brief GIL's 2-dimensional locator over immutable GIL pixels
/// \code
/// concept PixelLocatorConcept<RandomAccess2DLocatorConcept Loc>
/// {
///     where PixelValueConcept<value_type>;
///     where PixelIteratorConcept<x_iterator>;
///     where PixelIteratorConcept<y_iterator>;
///     where x_coord_t == y_coord_t;
///
///     typename coord_t = x_coord_t;
/// };
/// \endcode
template <typename Loc>
struct PixelLocatorConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccess2DLocatorConcept<Loc>>();
        gil_function_requires<PixelIteratorConcept<typename Loc::x_iterator>>();
        gil_function_requires<PixelIteratorConcept<typename Loc::y_iterator>>();
        using coord_t = typename Loc::coord_t;
        static_assert(std::is_same<typename Loc::x_coord_t, typename Loc::y_coord_t>::value, "");
    }
    Loc loc;
};

namespace detail {

/// \tparam Loc Models RandomAccessNDLocatorConcept
template <typename Loc>
struct RandomAccessNDLocatorIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept
            <
                typename Loc::template axis<0>::iterator
            >>();
        gil_function_requires<detail::RandomAccessIteratorIsMutableConcept
            <
                typename Loc::template axis<Loc::num_dimensions-1>::iterator
            >>();

        typename Loc::difference_type d; initialize_it(d);
        typename Loc::value_type v; initialize_it(v);
        typename Loc::cached_location_t cl = loc.cache_location(d);
        *loc = v;
        loc[d] = v;
        loc[cl] = v;
    }
    Loc loc;
};

// \tparam Loc Models RandomAccess2DLocatorConcept
template <typename Loc>
struct RandomAccess2DLocatorIsMutableConcept
{
    void constraints()
    {
        gil_function_requires<detail::RandomAccessNDLocatorIsMutableConcept<Loc>>();
        typename Loc::x_coord_t xd = 0; ignore_unused_variable_warning(xd);
        typename Loc::y_coord_t yd = 0; ignore_unused_variable_warning(yd);
        typename Loc::value_type v; initialize_it(v);
        loc(xd, yd) = v;
    }
    Loc loc;
};

} // namespace detail

/// \ingroup LocatorNDConcept
/// \brief N-dimensional locator over mutable pixels
///
/// \code
/// concept MutableRandomAccessNDLocatorConcept<RandomAccessNDLocatorConcept Loc>
/// {
///     where Mutable<reference>;
/// };
/// \endcode
template <typename Loc>
struct MutableRandomAccessNDLocatorConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccessNDLocatorConcept<Loc>>();
        gil_function_requires<detail::RandomAccessNDLocatorIsMutableConcept<Loc>>();
    }
};

/// \ingroup Locator2DConcept
/// \brief 2-dimensional locator over mutable pixels
///
/// \code
/// concept MutableRandomAccess2DLocatorConcept<RandomAccess2DLocatorConcept Loc>
///     : MutableRandomAccessNDLocatorConcept<Loc> {};
/// \endcode
template <typename Loc>
struct MutableRandomAccess2DLocatorConcept
{
    void constraints()
    {
        gil_function_requires<RandomAccess2DLocatorConcept<Loc>>();
        gil_function_requires<detail::RandomAccess2DLocatorIsMutableConcept<Loc>>();
    }
};

/// \ingroup PixelLocator2DConcept
/// \brief GIL's 2-dimensional locator over mutable GIL pixels
///
/// \code
/// concept MutablePixelLocatorConcept<PixelLocatorConcept Loc>
///     : MutableRandomAccess2DLocatorConcept<Loc> {};
/// \endcode
template <typename Loc>
struct MutablePixelLocatorConcept
{
    void constraints()
    {
        gil_function_requires<PixelLocatorConcept<Loc>>();
        gil_function_requires<detail::RandomAccess2DLocatorIsMutableConcept<Loc>>();
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

/* pixel_locator.hpp
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
*/