/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/time_based_rotation.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c time_based_rotation keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass time-based file rotation predicate to the file sink backend
BOOST_PARAMETER_KEYWORD(tag, time_based_rotation)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TIME_BASED_ROTATION_HPP_INCLUDED_

/* time_based_rotation.hpp
3//+97///TPzZoI/SH9z9OXSyNx18mlPg5MhEnU0TsQj6K8PgluOAOfSobHrA5BgVwZJd58xXjuhHvq2gKHOXz+BElJbT0bf+SU62B0O1VU0TaDy6Z6vNFznr5hCGeOKuxhT21AZrKPZ+bCTReIY/EBD3RSKKxCY7G8iWt4dDo3HNGYm+v0QLH896REUbyg3AxmkT4cUBqZWkXDTeLHOP8Vflws7QYbqDzJT3GGwCb1BfAIU
*/