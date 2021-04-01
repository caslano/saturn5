/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   expressions/formatters/auto_newline.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains implementation of formatter for inserting a newline, unless there is already one inserted.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/manipulators/auto_newline.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Formatter for inserting a newline character, unless the last character
 * inserted into the stream is already a newline.
 */
using boost::log::auto_newline;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

/* auto_newline.hpp
RXg7vF5+jiYRvLbPFnUW+qdtHHOn10PrI0ovlg5N67ATB2NQoCOytY8f0a8ICec9uTTUZC5N+jsK1fTszADSG+qYis58YF2JWyrj8rJbRm/9Kru2MWYoMXUTd9dahVGWHCbXIGHlTICwiyZvELX5e9Pa1rxhHzisyOC7Ws1wF6fPvyVL3cKKpgH8p8aPb5WqCejqtdPcTynqvvWSElhNX2U1FJQTeH1BDpA0h/LYEWn+iMFBtWqEek+0eNYYh8buPqd5lfMle7AiwgMt0to5iiycE99YtKfYkNWQ+wx1mHi7GFlW7xfzg+tS3PykTKYo512JS5VJzOfMVwyPxxlD9jEDDL/4dBjR+i8rIKyao9CjbRPVX+oAoMgImJ0TkcGIhJw/ViUui3a1H2DI7QnZLZ8kOdIL4pSXndpx+GGI5Q74R3WCKf0JqKMauzUyGzHjtSDykEppFAzqPtb1sU5ZXYQ8z2hSWylrua3q7Ftbph3fQGMrxJDBcqfsy6RwQ4sTUmNZTn3jO5Y2kdb+nimfI2hmk8kueTWjY2yseCvxdIMLS8zhCSHU4ohBGg==
*/