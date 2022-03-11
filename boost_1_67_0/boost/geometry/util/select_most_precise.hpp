// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_MOST_PRECISE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_MOST_PRECISE_HPP

#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_fundamental.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL

namespace detail { namespace select_most_precise
{


// At least one of the types is non-fundamental. Take that one.
// if both are non-fundamental, the type-to-be-selected
// is unknown, it should be defined by explicit specialization.
template <bool Fundamental1, bool Fundamental2, typename T1, typename T2>
struct select_non_fundamental
{
    typedef T1 type;
};

template <typename T1, typename T2>
struct select_non_fundamental<true, false, T1, T2>
{
    typedef T2 type;
};

template <typename T1, typename T2>
struct select_non_fundamental<false, true, T1, T2>
{
    typedef T1 type;
};


// Selection of largest type (e.g. int of <short int,int>
// It defaults takes the first one, if second is larger, take the second one
template <bool SecondLarger, typename T1, typename T2>
struct select_largest
{
    typedef T1 type;
};

template <typename T1, typename T2>
struct select_largest<true, T1, T2>
{
    typedef T2 type;
};



// Selection of floating point and specializations:
// both FP or both !FP does never occur...
template <bool FP1, bool FP2, typename T1, typename T2>
struct select_floating_point
{
    typedef char type;
};


// ... so if ONE but not both of these types is floating point, take that one
template <typename T1, typename T2>
struct select_floating_point<true, false, T1, T2>
{
    typedef T1 type;
};


template <typename T1, typename T2>
struct select_floating_point<false, true, T1, T2>
{
    typedef T2 type;
};


}} // namespace detail::select_most_precise
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Meta-function to select, of two types, the most accurate type for
        calculations
    \ingroup utility
    \details select_most_precise classes, compares two types on compile time.
    For example, if an addition must be done with a double and an integer, the
        result must be a double.
    If both types are integer, the result can be an integer.
    \note It is different from the "promote" class, already in boost. That
        class promotes e.g. a (one) float to a double. This class selects a
        type from two types. It takes the most accurate, but does not promote
        afterwards.
    \note This traits class is completely independant from GGL and might be a
        separate addition to Boost
    \note If the input is a non-fundamental type, it might be a calculation
        type such as a GMP-value or another high precision value. Therefore,
        if one is non-fundamental, that one is chosen.
    \note If both types are non-fundamental, the result is indeterminate and
        currently the first one is chosen.
*/
template <typename T1, typename T2 = void, typename T3 = void>
struct select_most_precise
{
    typedef typename select_most_precise
        <
            typename select_most_precise<T1, T2>::type,
            T3
        >::type type;
};

template <typename T1, typename T2>
struct select_most_precise<T1, T2, void>
{
    static const bool second_larger = sizeof(T2) > sizeof(T1);
    static const bool one_not_fundamental = !
        (boost::is_fundamental<T1>::type::value
          && boost::is_fundamental<T2>::type::value);

    static const bool both_same =
        boost::is_floating_point<T1>::type::value
        == boost::is_floating_point<T2>::type::value;

    typedef typename boost::mpl::if_c
        <
            one_not_fundamental,
            typename detail::select_most_precise::select_non_fundamental
            <
                boost::is_fundamental<T1>::type::value,
                boost::is_fundamental<T2>::type::value,
                T1,
                T2
            >::type,
            typename boost::mpl::if_c
            <
                both_same,
                typename detail::select_most_precise::select_largest
                <
                    second_larger,
                    T1,
                    T2
                >::type,
                typename detail::select_most_precise::select_floating_point
                <
                    boost::is_floating_point<T1>::type::value,
                    boost::is_floating_point<T2>::type::value,
                    T1,
                    T2
                >::type
            >::type
        >::type type;
};

template <typename T1>
struct select_most_precise<T1, void, void>
{
    typedef T1 type;
};

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_SELECT_MOST_PRECISE_HPP

/* select_most_precise.hpp
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
*/