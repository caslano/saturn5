/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/overflow_policy.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c overflow_policy keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue overflow policy to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, overflow_policy)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_

/* overflow_policy.hpp
rOWQKMPEM3LnjG4R+ZRTqxVdW8Qfqha6TqRPLsqmzdKOBZ6nyOKZxIzbvOIG+XnlWXSOOVK2Wby2DsPK50M3949WD3GypyMRDvCI4In+tZycQK4r880uXyFv0JvOOOANgtUKjLZKCdQUvzqwt1WTz7pWS/NDDPUDsueBiTLvelmuKm+58sN8DXbA5gSXwkcLfaQmrHXv24jbkNs+tGH7JKsA9EnHm94aoGbphRZIhrOMMozrFKRZJJiHLMzlFW2HKyqUlYBPa71Vxt7psw/Cj6HbuHMA/FQosNiusgDZ0gbZRG4T7eOgrdz+CGE6y7yG+/WW1GrTD3cazuHgnMwK70GxLtCXJtYuGuCeYHra57975LG3oD+0hWFCH6+ANLMkgdQtJrC7xd4QhfutXrgDC0mgxZZ1wRqhSYjfMZjDXBSa1QZYwIZ11g46AYjhvmfgwXLGaxDT6mw3K1TqKfR4Y6f555UM76RiVOp0nvnn4QGyAyo6pstKFJj9p3ip2sGpwcPhnDJXhJctjd95j85eKJvjvkZT9DAalPyDPlT1V7RheFako0QTZhupD9a19rZjUQCQ1YXCRUQVzeljs7XDwJvXNkWflQnWzSrdKnYXvg+RC5YLcx1BG84yKva7kL6LPq/tjT4K2I+ctivkS8RL1EuESxSv5ysSyc+eQ6/WwlR9d919r0FoweFB4cGyQSKiF2rr+H3G20h9uO/i
*/