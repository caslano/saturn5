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
/nhyKotDCYGm1EkcLuJ6UtbJkoOQFqxgkU2LYmxJ8VKHLUnQoPGt6ZRYwB8ihvIxU2MDgRDSjclcyHbreFMuGx2sGJrWu+xeqnTdSX+/SeQSaZvsTTyjqdCYyrCzpTriHHpg37DOpeL85kTIU2XitLbGcVMrQgqT8ROlO9+ZMgxteJgI002ryWG2psqTuJ2CJjBKv5c1Qf7QgabqeIdNXFTUZfLURqO8dyCPG9MFEhxJ0VvdLl52X4WQyoSQ1Vh4Y2mB6zGlfXgqC8EE1qaYn5IFiE/WuvUnddUgu5wJLQF/fA2BUWrplUByr60CRm6FzxG499ZDSFytLPe9fFwA69AQ9kimmNv4SIcO3ugjOV9M+I5nTZyTLpNzO+qyz04kMxlhJsu4J6xVeGg0WUq/EhcQku6xN6HuOM9m5JueHd37wS31ROwYU4SRyVLWf3+Mz4MEKBkoVbUtM+k1CUXpjK6byzWzWeI8SCl2HD7HfLNvFqhvyB6kq2WHXO8eeJXufWkrd5x/jUFnFIABvkQJmeiRJRGHdgx/uE0tME5lAblyZCPXSX5sRInHRrZTI2+lQ91od/vvY8OKhxWDpla02kHtVDpsR+n1jIuhNjq/4L5YQjSZA1xPYNtGhY0xrsXWlG5WRPAhn88DsQIM
*/