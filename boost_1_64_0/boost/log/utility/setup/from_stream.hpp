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
bOpEw3/zM/77wXtIp2H90m0MrGcHN+YH84pXuF9ChkO1SC7ROjoNG+zWgILDQEUX2Q7U5VxTJExS717WN+Hlo/Ke2sTkKVfcR4C+wB7JAZypYrjju7yz5raSbGl9CoKimcZyWa9HzBmaPYmuEZJP1p03VZDBIcvrXrOZiaTSYPUCuivAsDe2hrmHfskGuvpOyz4Rk2zHJee7f8yYN8mdc9+G4T5KFYrIbzFs/OXeo9AVo7tnq7lKullSdS3EMAMTnMbutYtYVHIPPcNdEa4iNABIbUdPdcUvZ0X7kF5iE9IANzZN0wx8eM9/a32Tw9RpcF/SCJrB/0o3UJz7UantOYFSYFrLtSX6tFmO2BCShxrAajZmKpksONczFDYPD2rofjr06ceADx67O9XdPv3OrbJABHmuek0DyeIMeV527XvsqoCAlwwtIFg+s+YbIJEAF061c8dcx6e9woRD/Ygk7kQVUCsrV/6aM3AEl1YLn94Yo/vmfPZjsIq6kSCqYam8WqhGftWEHnhda7Iw++HTa/f9R5lY8OD/Japvis+7Ea6ptqck7Q3OYbSkgw==
*/