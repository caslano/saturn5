// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_MOST_PRECISE_HPP
#define BOOST_GEOMETRY_UTIL_SELECT_MOST_PRECISE_HPP


#include <type_traits>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL

namespace detail { namespace select_most_precise
{


// 0 - void
// 1 - integral
// 2 - floating point
// 3 - non-fundamental
template <typename T>
struct type_priority
    : std::conditional_t
        <
            std::is_void<T>::value,
            std::integral_constant<int, 0>,
            std::conditional_t
                <
                    std::is_fundamental<T>::value,
                    std::conditional_t
                        <
                            std::is_floating_point<T>::value,
                            std::integral_constant<int, 2>,
                            std::integral_constant<int, 1>
                        >,
                    std::integral_constant<int, 3>
                >
        >
{};


template <typename T>
struct type_size
    : std::integral_constant<std::size_t, sizeof(T)>
{};

template <>
struct type_size<void>
    : std::integral_constant<std::size_t, 0>
{};


}} // namespace detail::select_most_precise
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Meta-function to select the most accurate type for
        calculations
    \ingroup utility
    \details select_most_precise classes, compares types on compile time.
    For example, if an addition must be done with a double and an integer, the
        result must be a double.
    If both types are integer, the result can be an integer.
    \note It is different from the "promote" class, already in boost. That
        class promotes e.g. a (one) float to a double. This class selects a
        type from two types. It takes the most accurate, but does not promote
        afterwards.
    \note If the input is a non-fundamental type, it might be a calculation
        type such as a GMP-value or another high precision value. Therefore,
        if one is non-fundamental, that one is chosen.
    \note If both types are non-fundamental, the result is indeterminate and
        currently the first one is chosen.
*/
template <typename ...Types>
struct select_most_precise
{
    typedef void type;
};

template <typename T>
struct select_most_precise<T>
{
    typedef T type;
};

template <typename T1, typename T2>
struct select_most_precise<T1, T2>
{
    static const int priority1 = detail::select_most_precise::type_priority<T1>::value;
    static const int priority2 = detail::select_most_precise::type_priority<T2>::value;
    static const std::size_t size1 = detail::select_most_precise::type_size<T1>::value;
    static const std::size_t size2 = detail::select_most_precise::type_size<T2>::value;

    typedef std::conditional_t
        <
            (priority1 > priority2),
            T1,
            std::conditional_t
                <
                    (priority2 > priority1),
                    T2,
                    std::conditional_t // priority1 == priority2
                        <
                            (priority1 == 0 || priority1 == 3), // both void or non-fundamental
                            T1,
                            std::conditional_t // both fundamental
                                <
                                    (size2 > size1),
                                    T2,
                                    T1
                                >
                        >
                >
        > type;
};

template <typename T1, typename T2, typename ...Types>
struct select_most_precise<T1, T2, Types...>
{
    typedef typename select_most_precise
        <
            typename select_most_precise<T1, T2>::type,
            typename select_most_precise<Types...>::type
        >::type type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_UTIL_SELECT_MOST_PRECISE_HPP

/* select_most_precise.hpp
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
*/