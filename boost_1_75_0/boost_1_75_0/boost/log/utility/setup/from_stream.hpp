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
5Lo4Ouk9GEBXnj5+z5oWrwWrML9HnA8tKvTQSThRS+gq2c16jvz8nP/eG0SFgIIsXIayFiezLgcPABiDIDp/eBkb/g21oQT2rr8o5MMZ+gVGHtsEntQObyjJMp+2s1O5nUXhNuEv3LF4AGPXcajvCMZ5/oY/e8D+rshbFG+dT99h9UPel3IW2BMUOEN2V1AGXwSJ/C3Evd4bbXD97Z9H1v8V4vT/lVNg/RenoOHiYOZu+x+agqGMp7B7S3Wb1XoKyeadBRNtCp4M+DuTjNdhZDNOA3PDgeToB666ACYjBZ4arxFhh6mBCXTzr46tMYtZGStTqN/bmi0VPsqGZJSE/BZXMDil7DZAzLIpIg9J/PGx8c3GGmyml9ISeoPUy/6Q538ym5v9kMXBcTJ9XS7ccbruLdi6P8VJfVWC7senI5FO7SkephiPjPkIdWPOnNI5CcoLKv2t8g71uFZurhjPOf/hmyhXIaoqRgXSkn1utvoD/gYgL+j5t+MnsYTUWMRPowLyBxptoXqL6m6fVwQ3x3viHxthdstbOjGvp+6JPvmxQpTEdLQElfy0jxqh0slKcv487bzoCT8baZS5J/f0TutpD1KEbJgFnZEcuDQ7aH3m6op2lHaIwtwzOziXU8l1zY1p3Utv0GpKBKFG2yxPrS9kGNM5Qev3bWqVb11eJDjhb97XAVt9dqT8tuFv3TZpEgWQaAhf2fxN75d2
*/