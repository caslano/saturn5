/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_assign.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that assigns the received value to the bound object.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that assigns its second operand to the first one
struct assign_fun
{
    typedef void result_type;

    template< typename LeftT, typename RightT >
    void operator() (LeftT& assignee, RightT const& val) const
    {
        assignee = val;
    }
};

template< typename AssigneeT >
BOOST_FORCEINLINE binder1st< assign_fun, AssigneeT& > bind_assign(AssigneeT& assignee)
{
    return binder1st< assign_fun, AssigneeT& >(assign_fun(), assignee);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_ASSIGN_HPP_INCLUDED_

/* bind_assign.hpp
nG2yBn7I8sbJpQnbznr6FILrzNnm/IiYgIWzZOrxcM+nXYiYebqsrgMtugnK8LE5fEwGJwX2Izynj9+bAgpLvf+gzGAypsIP0/HOeanR3NCvinkXPbQlqhO42crSNtoYOzw85EZzZ5k0s1ZwE9d6x6vZ729/+Y+/5yu54nJkXOUluQKb3s4QXxMovTsgGnl+lG6uqi2vs2VgGTIiWHMsfCEOiJOsdjAvv8plwLgaQJezv6otY6B1++kL8/w4E+f169KeRPyNLmMsBdKdgPQNL7wJAAzAmDAaH5EOr08TFMglOdJxb92dgeq7qWufbVt7yv8D3tteLOu525PpM/6Yu+TIPoZVX2tNDqLpIznfBtuIj7bhO51qu9NeLXMbVBoKIKTTh60ujvBHH4jlD4J5GScyt0g4h/IyesnMdzpm6ZyH6OShz19j5I/pdVJLH4SzAyk9laf3lsWp54BUkVa+o0ZS4OcYHqam/EU29Oaj5Iwc+fz4IcNoZ9Rv4RPBGSPlJTGUPTWVUq01OaoYtJbMaOyNUknJVGbu1heUGU+11ChJD/Een0iJeZAcyA3RMr4nwxLnTpPMUyySqvEpyItSIkjhAYH8raJt7GzJ7Wyj+Zz1tLMtIkbqISJ56yhp8YsGlEAb+QtDBc/KxfZa
*/