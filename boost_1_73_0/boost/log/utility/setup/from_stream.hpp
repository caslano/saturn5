/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   from_stream.hpp
 * \author Andrey Semashev
 * \date   22.03.2008
 *
 * The header contains definition of facilities that allows to initialize the library from a
 * settings file.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FROM_STREAM_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FROM_STREAM_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The function initializes the logging library from a stream containing logging settings
 *
 * \param strm Stream, that provides library settings
 *
 * \b Throws: An <tt>std::exception</tt>-based exception if the read data cannot be interpreted as the library settings
 */
template< typename CharT >
BOOST_LOG_SETUP_API void init_from_stream(std::basic_istream< CharT >& strm);

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FROM_STREAM_HPP_INCLUDED_

/* from_stream.hpp
49FB32Fr2OZ+7f7O6+L18gZ7d/lPCD+tV1CA0nEh3TIZ3l75MzOlYqkZCl1j+MZX6hUgYT61sxvlKsNoYYxA82nMXr/QfM46aNevZArVMCnm5rvjUKxqexPYeSNSosgTdDKWO+vB5o+8VD/DH+o/7b8SVsS7sm2iqLEE6eTWkiE1kTLRL7KkTfJMpT6z7Eawuj5a0irtc60l6tE79kKnM4gfiSZGJFEDt8h3Cxdkl1wO619o
*/