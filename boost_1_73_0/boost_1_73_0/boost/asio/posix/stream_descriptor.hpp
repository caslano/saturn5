//
// posix/stream_descriptor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP
#define BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/posix/basic_stream_descriptor.hpp>

namespace boost {
namespace asio {
namespace posix {

/// Typedef for the typical usage of a stream-oriented descriptor.
typedef basic_stream_descriptor<> stream_descriptor;

} // namespace posix
} // namespace asio
} // namespace boost

#endif // defined(BOOST_ASIO_HAS_POSIX_STREAM_DESCRIPTOR)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_POSIX_STREAM_DESCRIPTOR_HPP

/* stream_descriptor.hpp
47Eci040ZkZJ1v++kr2w3pNtjfT03uc5JD5voM/pZVj2xIxNf63/4eC2WevfOl86LN/dHmO/gV9Ph916v632uwq0LVIAbQVJcMNM7TDpwJ2kc885SQoplg0cD5X74QXPKQ+vu0Biccvl0h0xxgLhmqPJXAuCdAilx0AtYTNf01JE+JAyTKY+zvbqjBt1V3DsSPU8Q43goffSWZ+fpu8dhQ5CYvHERauF+Kz12RZieN79drrm5+4PtClfvDyAfnoegK+XGjOkFmpf8PEzIIfUqM3S+U9fHl+daUQMaOV6cKfFdLZenxaqoa3Y+6w07BROi6+nhXN/O2RgBSTkRS2pM4VmW6vqYH4Zg1Dih4kOZs2tD24sQ8AsCiuopiNu7MUkSApQgywkimX7LmMBfJHsg7loc7qorFF7EzKnjloVgSZpIk6iIzoQB1AgCtGMzCSV/o0sssIexVI/GR5/7Z1idL5OWca5t0D6lxQxjlnMtCY2dnQbISjxxotfOffUzlUtgF4VY6kgvF4dumCZ4ERfBBLjuNMugTWu3H9QSwMECgAAAAgALWdKUmFmTTqIAAAAtAAAADIACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9wcm94eS1zZXJ2aWNlLW5hbWUuZFVU
*/