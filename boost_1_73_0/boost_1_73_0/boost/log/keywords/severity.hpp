/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/severity.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c severity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass severity level to the severity logger methods
BOOST_PARAMETER_KEYWORD(tag, severity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_SEVERITY_HPP_INCLUDED_

/* severity.hpp
KvcDoLgr8UNHzl0+Aop7+/7syDnLX4GiD/lvQLH+Qj1zcRvGAaB42uNBjB/op0DfAPpPoDh7/wzod0C/QLmQxy+BDgb6L6C3Av0a6B1AYd5Cc4twSLivYDsC+lug7XANC2gnoMdDgXQGmgb0ZKDpQNOBngr0VKA4a+8FdDHQ3kA3As3GNTKgA4DuBToQ6GtAIQ0uFvBQoJ8CHQb0W6DDgS6FBjkCaB3QkUCfBpoL9M9A80JyjjAK6GGgY4B2h3Y=
*/