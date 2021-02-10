/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   stream.hpp
 * \author Andrey Semashev
 * \date   24.07.2012
 *
 * The header contains implementation of a stream placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_

#include <boost/phoenix/core/argument.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Stream placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 2 >::type stream_type;

/*!
 * Stream placeholder in formatter template expressions.
 */
const stream_type stream = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_EXPRESSIONS_ATTR_HPP_INCLUDED_)
#include <boost/log/detail/attr_output_impl.hpp>
#endif

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_STREAM_HPP_INCLUDED_

/* stream.hpp
Ezwn9DNxksM9evwiCrl6BGQWgQuCbH9OlEFZECLTFxJj64V4YqirpuT5Hl5hXLrZdIFk2eGJAqHncPA8Es+laaJtJDXV7XgySeYvruSpZ07Y4alEQQHSDeYQ6bLFksbom85WZMMFQlIm0ViGogRcta63ZiyN/PtmHOXFU3YB21fWoAufhZKouTjb1YHGk0df+SSjj002C9x5Ch+eWHv4C6x26IzopLStnikZOj/3B50RHp3Clkz9QrPRN3vN+8ku7RNvYNVDptIbXlAKg1wsI3GPUpH6cqaRtfVlVOj0gAm6h6DlLgaokIgAZ2AkOlrIW6kknybbVynMC7R+3xO39Wt/T+vs97+nH9hFB6R5Tg3vQ0gJyrWbawz2y1hxF4yAfIkMEgujuh1/Dk909PFELDbDnonRM862MRR7Zuj9N05nHw9uxUNdxj2AhbVm9uUkxY2FmVeY86kRcdEKjQxkfcLapwtYdZyKIpARRQqhQMyKXB7FPPSn5eJn8j6rNhB7taCn/q714w8fxOAUkyKHgjGwTpc2Zl6Tkc+WGRl8V5oWhwZofy2FHXw/jPoo+h/oX7yibYDmpvov0u6O5loqTyl/BVFQQEHIaqJ2JiUQkeRqZqJTV3rGQZtJK+eEVsSX02Ws84ZNB0mPszTS
*/