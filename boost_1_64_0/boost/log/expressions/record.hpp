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
gR7yNym6BVCxLne0tmXiwz3IX+7h8zy26A4/DXESR4nFvWtLzb75F3HnUTTlT2cOd6O3bPFaLig7tXJvnLxJPRNzUgMVhhHPYeUVDAZcvmEc6FrIsC7EfDch+vED03lLn5lp5s/EmMLpkBYVCR5MDU2aauED4q+9zPavBq3nIXPeQei4Rsq81TIZ/jTVkTRFNTmSbMCeLxnjnsd0r7PjAswAn8VhStLUgASlbyawdJ1qh1AFpTcqTNmB1/REGbtqx2QHmYTbLuWYug1hooiqzkBsBrD4C953Kb7XnpNNlObUlniHOvIDTSSAzAEQgzb343YIGN/qAaNqaS804K4HtLP5nGwTvGZ9wCdEvQUsqCwgA0Ru8WXLSamwXxpe7hUVzfyZDFSIf8+4Ej7Zs0Osxib6annE2lkqvqcl8fakR9wiFfKwg+DP3TVDcS7jc82xLvCoWPsdO7LU0V+GtWraIdsruUxeGg+lONeXzenqdZxEtqzkAltvJUmJJCB8CWjSTOB5xuqmbo/vQ83yZQeSiGvrF5gowrESVET8ewi508ETztBm5L6i7P7eiQ==
*/