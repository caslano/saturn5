//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_ERROR_HPP
#define BOOST_BEAST_ERROR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>

namespace boost {
namespace beast {

/// The type of error code used by the library
using error_code = boost::system::error_code;

/// The type of system error thrown by the library
using system_error = boost::system::system_error;

/// The type of error category used by the library
using error_category = boost::system::error_category;

/// A function to return the generic error category used by the library
#if BOOST_BEAST_DOXYGEN
error_category const&
generic_category();
#else
using boost::system::generic_category;
#endif

/// A function to return the system error category used by the library
#if BOOST_BEAST_DOXYGEN
error_category const&
system_category();
#else
using boost::system::system_category;
#endif

/// The type of error condition used by the library
using error_condition = boost::system::error_condition;

/// The set of constants used for cross-platform error codes
#if BOOST_BEAST_DOXYGEN
enum errc{};
#else
namespace errc = boost::system::errc;
#endif

//------------------------------------------------------------------------------

/// Error codes returned from library operations
enum class error
{
    /** The socket was closed due to a timeout

        This error indicates that a socket was closed due to a
        a timeout detected during an operation.

        Error codes with this value will compare equal to @ref condition::timeout.
    */
    timeout = 1
};

/// Error conditions corresponding to sets of library error codes.
enum class condition
{
    /** The operation timed out

        This error indicates that an operation took took too long.
    */
    timeout = 1
};

} // beast
} // boost

#include <boost/beast/core/impl/error.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/core/impl/error.ipp>
#endif

#endif

/* error.hpp
xvTV7RUyuv5pq1Bvs88I+uEjlPs2xcf059iqIee2jx729kXevDhfLKzYNjydPhvU33/UnIDfnFbtO6Ld/Udzps1e6ztpdJdiiSUxqY/rqetsV/yW9r6LhaNGK+yTAfqPLXo49bsMq57+FkvY6ae9pWZco37Ij/v+v765UWcglWn+r5SG8O8N3MnU3NjQgd7Uw/TaG1onefT5LD1UFEwwNCoKGxmNQwIqQQQKjAgG5hd0Y7thgEBQggE6mKhpNLZxTcvvWtgot0UtHYUqJUcqi+UVXZvli9o2+KCoSVUVq53MNxAwa/vb2x73n5ee3dsywO5UjvPJVCaL+UzO22tMZmtUATKYICRjNnRRFqE/yEGdfy0QAALvRhD3zM3PgY3s/XPPI1NnekyVikU1CVcsS6RQwQqzUilMqtpgDC0mQoOJRDyT/o+jk9Nd49jr4J+j4/ANhuiNwowRaquwB4Ky5yTdJ6h0N9E6B8vo+z6uUFRAv68bhu3oV0W7rkzT8Ocwa1ypyQGzXB658MOmKwY0NHGWEAU+WOlQ8+ENUl7KDSpk0F1YGEmkd9gF/TUEcoIrteAaEioIp2Okf0cJsr88YX9ekNHUGOHYDD1pdHTqdVRGAahaCKEMuxoYvaDIc6AT+10/Z5P3r5BRfk3Q35fa1uDBYMrfObviJNOrAh2+7aJE9kr2lwQVgE0K3aJEAV/waWb3uVDM7VTEuRY+
*/