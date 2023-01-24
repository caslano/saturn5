/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   begins_with.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a predicate for checking if the provided string begins with a substring.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BEGINS_WITH_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BEGINS_WITH_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The \c begins_with functor
struct begins_with_fun
{
    typedef bool result_type;

    template< typename T, typename U >
    bool operator() (T const& left, U const& right) const
    {
        typedef typename T::const_iterator left_iterator;
        typedef typename U::const_iterator right_iterator;

        left_iterator left_it = left.begin(), left_end = left.end();
        right_iterator right_it = right.begin(), right_end = right.end();
        for (; left_it != left_end && right_it != right_end; ++left_it, ++right_it)
        {
            if (*left_it != *right_it)
                break;
        }
        return right_it == right_end;
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BEGINS_WITH_HPP_INCLUDED_

/* begins_with.hpp
ccP1b8auKECia0n3Cg5ybJZwVmqh+9M7Pd9XkhDI3fi/RZZgrXYgNHuZd/FzGF3coH0NKAehKbMGocB3QuiIwuNXifV8+01Dvri3hQ+xNl9n0oc8MjYxsbGGqv7RZYqmfPPFiiYSqmgCX0m2srWxUDDl4fqcrfEusFRgSL45NDc3NjYUe3F5tX85YSnAHsCBr5MttiFGJw0BwYAgq5qPfiIj5G9/hhon/EtDFNRD+LWp8VkeEKs5+oTlUoGFGe+skphR+eDr6JObhGntCmtc09jIbNPRhvy74GJ0bOfu0m6tZ2Ridjf4bVbQTSSr0ADX/Xnw+cHqjG609xSm2ocs17FCQ7iypAq8v+UrpSzH0+95FlOIrv3N2LFzvM6seTft0uq2fYDQdsCET/lPL93NuGrFACl0WlEIcTJiw5y+ihSdKE9XACmusDU4q6FuXKriut78g8EKmaw9Li+i6mnuPChLxSDOdcQzqGjk0xbOiR/h5hd8zgHXkmjutJCQjuCj1l25GNdJcYGCkYvGhz91S5q6iwnNUvqonEQNdWx0UU1bNzGpwrASliuNHACwNHngsVsC3vtSfAAZm2y9fT7wLjgu3DTgiJbQm6Jkd3FRHMbMVLi+BkC9NKAXo72/ICgI0d8bQcfp2ULtpQICHtJVqDr3Bu/P6EzxA8eLFh0GcV2eySHGPT9u+NEi88jNFWKdd+9O2IhuhCj302Kc
*/