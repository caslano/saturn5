/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/message_file.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c message_file keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass the name of the file with event resources to the Windows Event Log backend constructor
BOOST_PARAMETER_KEYWORD(tag, message_file)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_MESSAGE_FILE_HPP_INCLUDED_

/* message_file.hpp
17cdeSgbW1mhodGBxlIkA58T3omX+QJipvZfpaVteU7QxRUSb0Pp1FrLjZLsGHYKQD+4Jkq807Sy8rm9VwChT6ONYHyEM8VqszgVph8CnMWgAoTJoq6DgBpnUtARbiyH6/sr6H8huWYw7U1e02f5UINbPbKVw33nazDlUJAQ202PUOR7wfVzY3XWML5dTxTlvrtGmEEsWMxoYTq8xyDFxaikbOf6HV7nkZpau3J0+qI6I75Y2y/ICuor221JBCMWRGJCYfDe1qXiGlE06Iw+bWUNgD/8pnZtJ+rq/mNX2OBJ5A7PQ4xGvtCQn8/7NDcxS+uF/s2PuAaS4aU5XH9X8oYzBViaVwyVBUgqrh3eZHkvyawP+SmFuV1qxXMIGKXdcLIc0zBNseinPoQL7FkOPw7n4pg8VdUHxeiQfJm4fyfgPz9V62Gh//1qJ54erBKxWtn/NNlObVM78/2pzvyM7q7H6yNUL53590qKMDSo0Xdc8Lrq4n8GAk383rX7ySTexgBZhS8o7o+jfCPIRgzPxvGprPo35xkEhrCZAjfxt+LqmDvwRhMUw8uTKQ==
*/