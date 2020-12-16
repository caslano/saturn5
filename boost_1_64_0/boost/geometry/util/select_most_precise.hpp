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
joOL6/5F7qcc1KON/VhEvd37Kfe9Ccczgevp1XTGoZdoZ86zPMbXzHeor4V+fIV2hP59pL/ufUIQ1x3O/50f089ew7or7TLuXjjNdYt2PTad+80unkfmqve4+h2jnmv4vpCVfrGU6+I52ucz3q9w37avgOs7+7mymu0cov8wzvTxZ1x/gf1h/oP3U5917PfzrI9+s5tx7iTOS7dIPq7Du/g7TibrjY7iOXcfz20PMx7ZOR4sH+s+j2+hfuyfw33O4Dyez3U/eivz0x+m0B8u+fB+DuXE3lvvpd/Z6BfRqlxyCf1oA/2b91UhjOuTuJ6ci6S+c/h7fTvX7UuMX4wrJ6nHLuqRzHLbxlP/hdw/P8fz0ynGE/rX/KHs78M8z43hevkc+xnD331u4Xt9z3Cc7Lw3KaAdeB6JtdJ/p/Kel/Fz8Fr2131PyLhx7heSAgfPz8GcTxmME3G8d3Tv3zs4bx+nfd3v6XDdOVFPvRu4nnJdPs/9ssfrXK9TlB/tKuXvnMEe3A+x/6xnAM9n2bPpT/k8L9DvT41ivIvnPRXH61WOY5773o7ze+jf6A8cx5C7uF+mvRN+wHwt/D2W9zKbqfeJhzn+XA+zuR6e+oDraSn9wP0eHp9f5fMCys+xn9mcb5MyGTd4j+bXn/u2CbwP4v1A7Fn4t+RfwPsexrsQjvfREo4P438C/eXMBfo979kO+LP+YOZbyfcYXJR/ynWGdj7N+bm3hvVF4XdhaX8Q93WcrwNSuO5x3Idnclx5jzFuCX/n5TgNdd9XPcS4T/tORD+9kUa7950LuT66eC+7mPtbjkMf2rmAds7mOFx6kfMzlufROO6j/sp1cxbnRxHHi7/vOmK5Pqj4j/Y4f3n+mcL5tIP7lgvu+1LO05HTVT7HQOrBeLeSvxdH30M/mM73gy5z3ip7Ynz5O0ou7ZbIc3AU/dyP8zOBv+PFMD/9fvkA6stzSyzLHaCeIbwH3sZx8mAcHLOKv1Plc/zc+2DeRy2XdU7SqUrvEyVcZ15knOf7nBemcdxmsj/IP0r0pl4HeA8WfZb7lnspd+u1mXEhCeVEDv/2knF6n+P2Jn/feZj+nsf4TD9cxHg1pYPnzi08J7l/P13Kc/ditsv15fBdHMe32c7dnGfu3xE47nnxHvzdkufe97he0h/GjaafxfP3KOpxmPcmW5N4ruH58CT9Kq+A48f91rFz9Ocu7he5L/K28h7G7XcctxMtnAc8F45xx6sJvN9135cf4H4omev1Su5f6C8J8zlfOhkH5tBet/VSKf3tHL9vWcT1yJ9xegx/lx3B9Z7vjZ9Yzd+H1rv3bdz3/IDzYhD3gYy7y2nfPrwn6sd9fDzs4y3tv0p5MPfdIdzPhXAdSeb764t5TmO8GMl4sZXxwo9xeTjfzxr6FuML/Xaw+318+m0mf9/wnsX13sZz7EKeV7hfil1Hv+T7FefpN+teor6cT1cfoR93cf3hOMevpx3PstyTqt/JD9Ef7mL79NcBUaq/x93vS3Pf68C8vDZ/5jNen6I9ajg/2H6fLo6fe13mPUGI+3dprlsOxudLB2gv931yO+tzMp49z98x3PGAv/dn0v/HWDn/3e8hcx9nZ32xvIfy4DyN3UZ7UY/N85RdVxfyfeSZ9Cfa4wz3dQc3Mp79gr8r/YXzMc2D9qb9R3J/MJj7ixT26zDLRXMf1MZ1PYb3Y18wLnK9neL+fTeH+ti4Dkx1/27Oelj+PO1tX0i/pZ9ceJn3Q1G0UyrXHb4f4TFL/Z65k+evc49znnNebh7I9f056mdVcWwd43YBz4dnWJ/Dfb8bwPuVxXx/4Gme96oZ7/9Me7xIfWjP1clcN+18f8Of83ku77k=
*/