/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/capacity.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c capacity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue capacity to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, capacity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

/* capacity.hpp
qUo5QNMDZZ7kSL/8ECrwqhINZ2sYw1T1kPCeXEyA0DeoNyFfcFPe/YZ6KnJVyQzx+gHFcqBOePH7IxroE3ZICssO8OoHFOTgSGV3cXX0YuNaiY8/MR7L8FyZ06J7KLQw7j9R99xTS8PWXzPlhgu5snxpkpop18jbvFDRQRlx1rxyqxES04C180Qhlyvxl6qWKY4Diq2hXUQauO1VLe0AFLeupgEtBtopIvcVdwa6BOiJQLHv7gJ0M9CuqpaeDHQ=
*/