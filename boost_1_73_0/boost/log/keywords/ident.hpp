/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ident.hpp
 * \author Andrey Semashev
 * \date   22.10.2012
 *
 * The header contains the \c ident keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing process identification string to the \c openlog call
BOOST_PARAMETER_KEYWORD(tag, ident)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

/* ident.hpp
3D9EtrYVkszaWYNxfj6BFdgDqMfTbpgBH4scOBXRFiYtHv4dBLeQW8GVrBWpvRvj+/C/qR78W/hcIenLQvj58DmEv1GjfEFvRfwuh3/20HBmt9yqHHJyTa7J9VddI2tfEa7eCUdv307QXW218dBddtllV1/zkPHR33XZldZeZ9fV11hzrbXXWXe99Teo79Xwg72zW+TyzpYbZnbHR93WWNLFgr89dmfy48kXhvFjofszkhqt
*/