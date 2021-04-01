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
0Hb3pCju6it+AZA95dVioCcW+VRSGVBs0fxJVWoskfg1lNArssYS1HLFCxjoTsZ5QSXSOAUskEVfrqRKa1HRvwtpTm1DDJVLDEUCu1fPHsh/KYaq1uoPgjlC1gfrCfymy1NqBqbjjnaxM5m8s8gy7S3/lSibuCtBUiFjNtOxWYPrD0DKW3aIVOhJPzpnhTUj0PFXP4AEbAxwVhUrUvC953hLN6VbKVPpra/VlKAKRC2nWrNTYShfbMQ3bGOkS6RKcSy6n0LBjfvpCNwC0pul9uyT8mvP5HHbgm5Um18b0MBxoO3d2ON7gzV8oK1Vqu+huG+v0ztKxBqiTKPVzNm+AbxWwVouwZzm2q9dUZ/iy0fdMRB2rJ3iuaLSHKn5Be96WsXMgNip4gUCxiBk4l6C1i88CzMDxhwpQZf4LVdRE7kDSOWJINwzLgsQJWlv23RG/xCFI19fzstiUXo9sn/rE04+DdIhxws4b9jd/49ZcrIc7T6q9GB1XeJmoqkiIKrshTPVTsHw7WTrmw7KjtaLK2rjqTpMAsydl8Skk3BKKRm8zc5UGjlMHg5EcA==
*/