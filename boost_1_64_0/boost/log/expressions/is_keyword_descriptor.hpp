/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   is_keyword_descriptor.hpp
 * \author Andrey Semashev
 * \date   14.07.2012
 *
 * The header contains attribute keyword descriptor detection trait.
 */

#ifndef BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_

#include <boost/mpl/bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Base class for keyword descriptors. All keyword descriptors must derive from this class to support the \c is_keyword_descriptor trait.
 */
struct keyword_descriptor
{
#ifndef BOOST_LOG_DOXYGEN_PASS
    typedef void _is_boost_log_keyword_descriptor;
#endif // BOOST_LOG_DOXYGEN_PASS
};

/*!
 * The metafunction detects if the type \c T is a keyword descriptor
 */
template< typename T, typename VoidT = void >
struct is_keyword_descriptor :
    public mpl::false_
{
};

#ifndef BOOST_LOG_DOXYGEN_PASS
template< typename T >
struct is_keyword_descriptor< T, typename T::_is_boost_log_keyword_descriptor > :
    public mpl::true_
{
};
#endif

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_IS_KEYWORD_DESCRIPTOR_HPP_INCLUDED_

/* is_keyword_descriptor.hpp
38rm0+oz0rUyvZUnmF5vGVgcFbwG8T781oVKr1mSOCidZi3idbmh1yKuO8F0e9/BXmq0KUS8eym+hN/6kOmW5WnNO+hInD675Z25uqaorpNVxM33I4voEIuPyxQ7cMC6ta14/zo5YxJ/IvHSr9wnUO/p0Y4cfTX9acgrpCthqi39Zst08+5tbb58aDyudV9jqXPkek+uuzb7FOED7VMZXVrOr6W+EbeYgP1VA9/t0Vr59FM99FU9ZDerB/Nut0oXxNVkj2YT3LeWrfjpFVIf2SdJH4H79pp0iE7menWilUe843s3f00clc3ppLDxd5PTvFlTCuflz5o72Wmlfir99HNH4BgOmy7w37Z32Jb/O4LHJph3Izs2eB/81/Bf12z+qZNC/MYmwXVTQ641T7xt3xO/7gR00NKe+IPUdvtmrPldNszpw/fHVGO7lfyegxs22XzO7WsntZjWQPsy8ZEuiU/qMMJrHfa/uSbQs1tc3MeVvnzt7SW//UHuXc4lVxUs+1Lbbaqf9hpCJ8tG2tyaQFoA5HetCHYjLbLOhfdbEw6yrHMxVO1mw2AszIAJcARMhSPhQDgKmnVPckOueyJ2RQ/nwmg4zxeOb7HQ66zM13ALYHtY4BeusplwizTcYg13gS8c3ySh14Mp0nDFsAO8yM8uVq/hCi3rFpyi+uoNk2Ga6qkvzID94Cg4CGbC02ABHAgvVHfzXPT962t5Lmfofc6EXeBYvd8Y2AOeBdPU3ewLrfH1s8Q3QeM7W+ObpPFNhD3hObCvuhu9a3zxFv1NwZ+/nXmqv941XBdLuDwNNwMmwZkaboCpz0i3PocIv723UyIaw3WDu4nwwK7/bvtheO7/p29D/F/Yg/bzZEOMfyzWyUSKkHpkN3IISX481slGKpFtyL7HwzbFf7N3JoBRVGcAnk1CSMiCIQkQIkfCfUQNIdxBwn2IgICIZwgkgWhIQg7UihoUFSvV1OJRSi0qWttipRVbrFSjtRatVaxorWLFetRabFNFxaPab/799+3s7izZCLXXjv58mZn33rx7Z9773/9iR+yIHbEjdsSO2BE7YkfsiB2x4z/1+FLm/6uP3v7/8TmWWbPLZ7Ac5+s4aYP9t73nU6GMt5fmVxT7bQDIevWGw+z9jx8z/3ZA9tGqqXHON50g98uxkxona6GSjJ9jA/MMIeGkydxE8H5aBXJ/iTXAdX1usP9KmfeUdWNmjf1Fcj/TsaaqOmhvnRK979+Ho4PuC8aon4n3OHFzltFRmEoCE3Is7oavdfWGzpHqnEODzI+UmPlC8oxzzTOueYVcM+nvLPEhzlzTOAft9VUTtB57V3xgvrgDcibyCs9s9pVtRX5pcNnWRC5b9WP2jI68hjXEbS+Tv4E9483aVklXQCckdbztL8XkaTvyc0q3gN4HiDzvHLROsCR472mNK9fk+b00/0L3e23S+fW1HsKDF8P9hFc0XvOr2s4v93XAmXC+uCv3nOJp75aHhOOah2bd+bfkfm/PX60ct3w1/jvofpek1uyhc6fcS/fcz2qWZ5iRkDzlytUnSvsK2m9G/bJor9Z+vFlTfqbG345fgymfwJ4218n94z3taHcfE0dpT+YZPa1elFsi7vZl+yZKNiE2E3PsMoxunxnC0n1lotlTXNdV6r4ypCusDWzW4bRXCDQdvgTtNpA3wZSpaxvopflaJO6e8ExmxdAlyCFmK+Z4TnUrXw3TlK/p/7K0fkyX+494xuF7NfINT7L2J36/3w8qbxNeoMzyLYfOSU6R2BjRc2It5xlWmpZni/jv7XmPeDtsjZjy3Cf3vZ67uPuSlWvK86cSTh8r2AZJoA/uDDuLm0n8DPUmPK6Z519sZXA=
*/