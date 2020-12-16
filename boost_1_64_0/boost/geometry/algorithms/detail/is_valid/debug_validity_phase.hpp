// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

#ifdef GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct debug_validity_phase
{
    static inline void apply(int)
    {
    }
};

#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Polygon>
struct debug_validity_phase<Polygon, polygon_tag>
{
    static inline void apply(int phase)
    {
        switch (phase)
        {
        case 1:
            std::cout << "checking exterior ring..." << std::endl;
            break;
        case 2:
            std::cout << "checking interior rings..." << std::endl;
            break;
        case 3:
            std::cout << "computing and analyzing turns..." << std::endl;
            break;
        case 4:
            std::cout << "checking if interior rings are inside "
                      << "the exterior ring..." << std::endl;
            break;
        case 5:
            std::cout << "checking connectivity of interior..." << std::endl;
            break;
        }
    }
};
#endif

}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

/* debug_validity_phase.hpp
JaQLZub0SX5DdYHKhaV3G9k2x/Gtym58b6f5GJjb1n3Dv4HsSatg7biJZMdtRtlDmexELetRskW+FzoX3R8yVs5Ce5qBMze+3V4q2u1JkBYefsFwODNP/fIlcVxNDsXeIV8a46Dp87OhLh73Y/eJh4dS5za1TMCVP+Bl+8duy1GZc+7PXA7hwU8MDfYnew9iG+2ckVrh4f69SSs9Do6aTP04E3FlCpqU7usZ6YnUxb9ltcxz7jQ/S+Y4Y8GF0sUxIPHOlXn6Kxq2MaVjoe1+umhjd9vslI03LmiJ4aALq9dWrveH7Ovpd8sH32zV9SWrxq66DnVp2UVK1ngdKhbGpT7k89j3kW43Q1qRYvEj8BCJudwvR/tzt4o8RfHfzNvmcpFFt7I43PPqclHA5wLOr8u9qJYpqmsPKs4++V7DpwtekI+5t9+WqMejIzi3tizIrcHqDQUwce8U+Ji8f0fcg307HxjsSzhvwfbLnDtbF2YyZclWXiXayoDkyyCGMky28e8Y5naf3tszNGQec6e4RiQO1Q0b16jIw69t8FuVuQj1/vVin/0ApIvFBB0SrAoWG7MYeEgEbX/3b6c1NSlBfK3r4aQ7A0e+wuAnNju4Nw98gRteLz5RPUrLPpLN8ZHuM7INef4+K/PIx9WPy/hw2qMBPGX7qDJ1BrthW4XgUvm9U/TbU26906fj6dsuFOoljWOpTPJzVBwmbFHWtVNPA1kvZrO0LYuyzLPlv5bsR+KJc7gVmcvbYFp3MeUCZo7HCNHWDX6I47UgMjvofdJZY4PDtHS2VoTuVxRLCU6UHo73hS7xuOg0Fc2uRRhOXtVxoLDyuNRghcBZv3iUkcNd33BHR8Dvm380x7DWgLeKPjLk9vlYztOwffeWY0wJJl9PMHi5UoObghqxa7z+ryL54E+RXcfWvHHQuEPdiB/CUIzO2EI+7ICyd6pUyOaF9SSfw9eTnizEwf1UB/w3PmjNsnd8r1vq4X4eBA7Pw1M2+zhf03oaxwcrw5lg0nsH8axmn4MZkfJBHK7PpwvpxPdSPFPghDh3X7iY1aNncx7LjZgXmxPK63O88O7bHs/T/kwblPqPPdltOC8QOGU4OFaYY/cvC5wKJMfXWF7scuhrWRm/xOXgCfuJAq2Z+PiC6ejvoT6exNHKj78F9ooYD45+KLdj47lnp4uD9ymos314vQ71QV8F8Yg8KJdSrZLFASDV19cAH5VUCqoZOALD/NlrDQa3ymUCurP+9SD3M2FnkWjdYTOO8WP11eJvIZzXJbr/mHDHfrnero1zkEHz9YDDRoVKJgtdwYK6ZWbOpn8dYDDHUDd/1xMu5u8GB5fz9/44BxkW//RpCq+kuc/kfuKjmwnnafByulFzMshosm/6Rv3AYBLKZqJSmnHs+5OAzWSm897H8blpzTERD2FdtPjnYvhwrH583uBYidOlClYh/n1fBE4khFfVSrUiPLub9+r8l4EjzEXCzDJxvipysMto3+YVOW7f6Rsix/Vl35Q50L1aMD/Omuu3ZQ5UUOq/fEfm8G07C3wfHi21986KHPt2CM3/Eo+bnekf0vuzMo/6faysb5a5Tr/0JzIHFcfiukXmRcprMfOdMsdRHv/mX8p8VCDj/VrmeXcPfQLq9mx7oW7d7lJ4h9hTcDmdEqfhfhzM+kr9uCUt0vjkt5FPmYVZV9iaOpwcOai2vbM3WTc1e/vfvPmz2zf7HLILdu4NeKCneFqNjJ/190nzZvdh30e6/yOkGUtP6Af6HN4P/JMQB++L/hXwnP9dFr8D24Y4vuh1FP3dxar/fo9Ypk1bmppsYdDWJdpnD3gG8ss5fM3rOMDVvRX6JhsrP17LzX0KRn4=
*/