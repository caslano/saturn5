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
w5rn3O/824wp1Jky9QZp00N7E0BcQphjGwzOV8r1K7tBbhMRCMEPEq5cic2g0YAC7/chEHo3PDw+vCiGgJKPRDvwRG8G7ODEiw17BcxgU4h34ixAbBDqO5sehe8rc3d6ZirUqHatQQxra546llJzpqxXle0qsVzLvsOQI2PKDwpPRZC4FPM+o46dTNeNcTJWUAILmUG6SD5Kr6nbcETfalZCZYhUpYHzaE9W2sjIU9UZhR2reyFLpCjr95cgqqj+leze7PpZCccXFMgsPQAVWvO78iDmj6H0EIx9FrT5l+pyvSbnVeQ5Oqp9FQMRk+q7OOyvCCrMG1AYcQqDKGd0dHD84eIjaw82u4PNrd86RbxJ2WkTcEJQA3zLX+0G9qortgr8ST0hPoItXQ3+uMmhoxNFEOFRNdMuU+/QNJsG/hQ9jKsQuQq9nD8UL8sz+CPQpiDNBJsbKnGE5Qyi1JFbKRe8uk3SMHZuVdGB+m9R4K7oP/owopC1SzkfgpSO+A9WYNR9T3WSxrWromvoBV7aXoVvvQqWd8wLI7WgEX7pNsqDv2iJiidRvaQe4bsUhaxDF63+rt6BEkk7cyWCVV3ObEzXY6v5kRoVPpXv6mtWS7JxagTE+NeCxKYts6nxcgMFo8A64bFRPg+Ccirm
*/