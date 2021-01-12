/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/rotation_size.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c rotation_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ROTATION_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ROTATION_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass maximum log file size to the file sink
BOOST_PARAMETER_KEYWORD(tag, rotation_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ROTATION_SIZE_HPP_INCLUDED_

/* rotation_size.hpp
rP61NfA+wr9yeJr+nsD7Cv8msC/oHwJsy/EmpS/fP4CPFPK4FPhkIY+bgTdcQYwngN+Q71/Arwv8HvD7sv8Efj5JH3SOwHhdtg/A28v6ALy5bO+B3xO4CLyO0CcP2BL9uw88lcCHAH8i2wvgmYgZk1/gz4X/DcDPCHwf8LNy/AT8nBw/AR8qx5fAO4j2wDoS+ifHC8CfCWwDLynkszrwbDL/wOcInAdeStYH4E0P6rcfewIv
*/