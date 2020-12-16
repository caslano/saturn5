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
Zrbj4+Nm1Fkts9rD+9Iq80SY02jtOxSJgtU2q9rMLjd6thvxkRVmpo0H/PYpWCJZLpjHb8J1aPwx08YfYhcsuo5QFiFdkpDOUde7uep6zzNGsAQhT1XPTOc/GDv/Uez1jOnmFziWFu1ONp7ZT3u/fYkY6lMftOg2u9mAxei7Teh5HNY/v/gzeyKO18ysrplZ/7w7MBzt975ZfcKO1/TJ7TuI3WVWTay6lRtX2I66bmNWvVk658uXP6L92ppV83S61f6qTlXE0N2sfmbl7PDSFIi5LtSsqrM81+fb2wDtTvZFet1KF344GmUZbJzPCgwNOIw8I8yqJLMfRlepjmt5sjmsPjO2vtoE5aS9wCuxdBva1JiGNiLjfaJiucN2aQ9xlGWY0faX/3EO2m+40Vz+2y9g/iS7z6yI9bIZsY+gczizyDGf5kB8I80qjNn3DWL/1J9HofiYfTikeC/ER1YFprXtphooC1kUsy83bk3Sn9cw2vjdo/EtJO0jO51MuhW7XfsfyHO0WX3D0t2JGlgeMdCmtqHMCn/SfjViGEPnW2YRIy78jrKQBTLrUflUQeRJVpFZ903VamE8kLF6oW/srbRgLh9rrM+7dRxL0O6CBXxiVvVY7FkPTM+KOWRc8jwB69Pv8R/oE+PNarCJ9aXhwzqjnBPomTDeDq2/q4j6nGiMb1KLtJncRv9hVuuY/esrWyTyJCvOLOTkrO9Qlsn0/B2zXo/DyiG+KUbrtisjngl2TaVv4LEY5k+63RBt9KmxXsrm25UF5ZxhVu1ZnkVLmfRvL5G1hBnP04lkHzNrcmL8L5iXYszKxI534c8f9WeJ/0lzAUtX4vx9rHtiZhrzXF5mNcZmwGd0/oMZz38usjIwj/MK2SfMZjvDv8d8TR86fMxs19kyEYjhc2Odfbb9a/Qlxxyz9vMULOeBtnpfog00zjCLbtqrNtLRB+HyszyfZj1WWP42gPc99DEeFpjpjqhuF3q0DkYbkRWAGdc9fgvNyg5LeZca5STzls5F9pKVpXDhoDJo2y+9p1O0H35dZl2fdfpN2isf8ZE1ZFbs3vl1iGExzQXMVg2+MhL1SbaH2ciKQf+ELTGrOsw+fsdhwTxPVo3ZsZHpce53LjVr9/JgV9oMQLq4FclrdtjA+HQNUc6VZlWaWZ5CSwNQn2RNmLW42vl75EnWiNnMNNW+Rp6rqF8ze3RoWSbMS2T0ng1szPCyOBdHrzVrV/+waccrZkE6smzMihSL2Yu+5GGjo5ZNR9uuo3U5s7nTy2xBnZHlYTarzzcn0O5kWZidjt1SCOUky8fsjLnkStQLGS9L3f73UGcJHjb2HwtnoG3JKvA62zlyDOaXOLPKyuzCxz3uoo087NjJXcUxR5Lx+DpNHqF/844sN7NfbBbUdRxZZpjxvZcEMh7Dyyv17iMGspLMMu4tNxkxrDeWc970Ch8jBjLerycEPRiG8zRZWxsrS8itnEi3xdhGRfP/Q19Dk9VkVrpo8CT0JbKizEoO/i0RMZDxdqhfvekgxLDVrDYwm3j6HeTpt82YbvZHi8ehnGQ1mPkHVH6B+Miq8jorNbkPyuKR54p8u8NRlu1m9RUvy8T4a+jzO8xqKrNMN36MQtuS8Tx/7dlOX8+TleRz1rzARBzvX3R+YLZ3zdDZGCselua6Xf+uJFkfZlV7rM2HuXyn0VqnXb4T5SQrzuzDTB9hfkkkY/VJ18lt9Pedvjer1vx4D042Rl2TBTDbtKF4HPIk4/XScvqH01DOeI+2/XV9GsROxvNc1LXcSxyPzMnsH8NyvkJdk/E661xn+D0cb5fRFqRLh7WGi4wfr8QPUzagrsn4eC9bPf0D1CcZ7/M3/lk=
*/