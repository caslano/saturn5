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
CK8shr067+3yoLsxZTLP2ySv5vnH6Okwk3H06E8qWO5AZzp4BkqcRfbO0LoqzlNAHejvTX+KiPtLXXInJagn784IopomTQAsKlOLpEab3K6daTkyvkE8FiACUH6fpiGa0N44dRabccAVa3yZjwA1ThyOlcOu2SQsHHHYJJUSYUnaq4vQg0OZMTzH4ZmKZ31WZvtZm1wAZKQllHbpqXFt8LOtOrmX+lkQJYnomxkTEpuaW0tCcb4VUEutkI2al6jjkU17EtFR+N1CYw9Iu1vaZx7u67lkD98pgggToBUHbCziQP6ZA2/lR0eHxefyIjB+SUwPyYHS8bOw/miUQa2fCSe0AMIym0PMSfdzDStTQiojqY1dJYNnvrgIKD73GvTDS7vhxQ8ZsK1A0DrwkPzKx2x9hdzcMf8eYs+CFsar3tsiTTLEtK3CtXsdcjCEUIxw3jEPkvAeAOVb6O7Uzyb4kgot3LVQrelw8JVqwkqSaOErNmrP/btktVA7FGGF/D00v6FBiDxhUHFyXdtReaerxa7Pq1dGkq2OAG8fwMVLzeP8pUrimOv/8v0JFw==
*/