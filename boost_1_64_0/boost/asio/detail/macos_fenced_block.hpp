//
// detail/macos_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__MACH__) && defined(__APPLE__)

#include <libkern/OSAtomic.h>
#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class macos_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit macos_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit macos_fenced_block(full_t)
  {
    OSMemoryBarrier();
  }

  // Destructor.
  ~macos_fenced_block()
  {
    OSMemoryBarrier();
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__MACH__) && defined(__APPLE__)

#endif // BOOST_ASIO_DETAIL_MACOS_FENCED_BLOCK_HPP

/* macos_fenced_block.hpp
wWdI2h0A2a1fyqXaf3sXjlk+d/CRkTa9KA17u1E8xeUU2kL5ghRPU8iVWfeH8Rb0nSfoL+fB6bTKHYOb0A1NBZmm/awHA0kgpkBk4ttqpWVuCFlHRq6KSjBJIcCOROlYRidlG5wdN1K0LNe3XNBkX96AYnGMvAPaokHleLaH4TX99To4XD466HgkTJytkk6uAac27EtKYA7AxKetU64ugW+WqogiW/AMBAvbWP8Tv9/VIEEcVoDQzwFQF1499Cd6PeYXoi979meJmM4zYRXOEQ/ny5b/KVj8TMlI/G1p6KV7sv+pNUuOC+dkHQkLkTChyZtjleio54BN76jSRXDMr4qv9AdoN5VVqUf6Boqqr0OobYr5rvFQlJhDucJkbOTvbkqtXtLwEN15vxFrcb5RRZT7q2mMysj3tZ2dW7tqEgHDgXjHjH0/uVMJJ/hKI65Pe7ZdC8UuVPGBeq36Dyo7WcP2VQ+kDL62OtUN4h51KovRKZ+YNSI/sy6IKY8yP8EgkofI5v5DZk165hu0QpBLvlj7J0aaXaGwiSKi+jSY26xInjkiUBEeKNPCPA==
*/