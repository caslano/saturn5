/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   25.07.2012
 *
 * The header contains implementation of a log record placeholder in template expressions.
 */

#ifndef BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

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
 * Log record placeholder type in formatter template expressions.
 */
typedef phoenix::expression::argument< 1 >::type record_type;

/*!
 * Log record placeholder in formatter template expressions.
 */
const record_type record = {};

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_RECORD_HPP_INCLUDED_

/* record.hpp
0yXwrPqw7p69JpFrppvx8ARtilzZLOU6hT852dxt05L7ZGWoha93v39pli0oC2xJ2oZ6LSZOea4NI9qFY+tDi7AIZ4LGKzvS5juasnjbES7Wm9fg4uib2Etcucjia5LAmccILHIoSaV4opNBlTP2eqYAvlLHLOSHBUeOMny7Yrk9Sryifm6ntMiAFr5OAag6zNvlSRswZz9w+/+GyemFMm7uRmlDPHL0pU1q2tjvdJg/O1ZtR8zuN1f5UPpCkjCXFbYCoyP00gvteHAcuoCRrO5CFFzx/Arn4JkGS0OMpXvEX+xfDPFb512sv5rq9FHevO//kKPYtEsBvlKqn0BkFQJIpqkGK17VJSk6srB/0SH9TEe99eFuGcRondk9FBXYBxr7jcNmeacqAhk6GTTceenIFUrWOhpVS7bZtvjlFmxX2rY/FvxMjR+8JhpfQGCZd+Qi2EfoxRQfTbTXlQ2XujZ2U5XQWlozCDcuwppbh4farypyzKvGMcT3Y+xue1lif2apxtuEDwrTmk/0/t8en7TFP7vPfL3Hs4Vo6v1Sh6/148Se+/lef8fxrH4XIHUqTTjFNyOzPoOViVnFZ6uvxHomRn7MLMo796TqtR+1yGU3v051yyqcPVXrutV7R4+qF9XqY31lD7Ur9fHl
*/