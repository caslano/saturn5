/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/block_size.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c block_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, block_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

/* block_size.hpp
oBG7pjpbVEXlNW5xi9ZHs313OYqvWSMrP/ECN+doEKM8WCBjbJAvL2Ur760CXXlN7HWmjASCOSX+XSe5Qu8b1YXrCuwY/C+pwHhEizEobkLiwsXTnHGb51Fsh6PtOfEKu84IiPFjYeNC/DKF9VYLMH2AYl91JtB8lAy0AOjZQGcB7Qe0FOg5QFcCPRcoWtxZQLHPPA/oo0Czgb4EtD/QPwIdABTzO0g5mO/mSnS3o3teiW1gzD8ZSON601HfUjU=
*/