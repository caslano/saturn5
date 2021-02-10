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
n9zL9/3z296g77qOKPFpknns2lyVJfPG5OCUUsMR+7gqRTxPDceNglicnohOU5BoQbl+cISW2YtpHxDJDO1vwr3a0osWUmO/oeW/VJfFDNkSKolMDtgcxAkYQd28yMRJSVPspY46nc4xT8k1DuMwa6wp6uQuxJUjOu3mGhFsnmY/X+cP/EORQEMuIPIH+/gilARUKykmtCVCdxdoCOCmkpqCFXcchVc5nmb02E1SNwhlAwtFMdUpybOdEgv6pT0JM/OwO3gnXpzoB8bOZQ5KL0wh9fxpozLLQ9+nWfxyduH+7ax/cdV9XdObRQXD1tcf1o/N0zt0OffH27h0z0affs6qNOMRfqgS7uDSve5eD4aftnCrPH+EF4K+O+yfGdzawqw64RFu7/vv+oOPfXdwQ/myhVt1wiPcrs5Gt1t40PA2SsCkh4TfQrGI72N0S09w02hw/q67TWjxMOcyNkXcFG5H1LUNxZ4y8Q8sUQwlJlxV09IiJcJJTI0f71u4ftgcttmj5/6o/X+y5DdkOYe3zk3kI2fk+VT69wLViBqDOWEO4DsFAqGHVXr3naLvWzIwh2m1X19LU594aZR2qedobAFYnXXYbrmmnLJd1QQorSa26uBSuZEc6xbBlE7RomZls67RHec+dmGoJNuM
*/