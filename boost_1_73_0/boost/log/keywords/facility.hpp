/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/facility.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c facility keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass syslog facility that emits log records
BOOST_PARAMETER_KEYWORD(tag, facility)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

/* facility.hpp
/Yc0mUgf2UMMHJuDgbhzY79fIsDjTSoifI3hVA0vWIpLe5fATRTii77aJyEG6cbOo1lW2goORt7bvX32nflXw7abvgjLJxjgXtin1e6yZiKyaQdX3avtHzrzP3JepssukT57AaG03tFmz6BGstzQPjhYvhvw4S9Lsp60WDE33sRefRW9P0SbzxMbLFax91L1aWZj51KtqN3QDgjxqOkw30bNxxO9pBwWdNurakMQJK4VUe5a
*/