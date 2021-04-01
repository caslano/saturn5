//
// detail/gcc_hppa_fenced_block.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP
#define BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class gcc_hppa_fenced_block
  : private noncopyable
{
public:
  enum half_t { half };
  enum full_t { full };

  // Constructor for a half fenced block.
  explicit gcc_hppa_fenced_block(half_t)
  {
  }

  // Constructor for a full fenced block.
  explicit gcc_hppa_fenced_block(full_t)
  {
    barrier();
  }

  // Destructor.
  ~gcc_hppa_fenced_block()
  {
    barrier();
  }

private:
  static void barrier()
  {
    // This is just a placeholder and almost certainly not sufficient.
    __asm__ __volatile__ ("" : : : "memory");
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(__GNUC__) && (defined(__hppa) || defined(__hppa__))

#endif // BOOST_ASIO_DETAIL_GCC_HPPA_FENCED_BLOCK_HPP

/* gcc_hppa_fenced_block.hpp
RNPCOrMhrfMnkmlPppvG2MTeqsq39+KgnD5BW1tIr5B9ob1j9PGPJcUdkzKm6A0ewsRSiy7uawR/0xSOn05AWL7yGZyCQflgTBKWAN3GRnK3Lod3xDhldkX1Qd6cIKF9PfOvo3s9t3QN6t63KrIK3bz1s05QP3SkLPJgEiGKvSUvdjouz4jq2N8J1Ms/8wI3JuzYEcmy2BBb43NQdGR6As1ICnhn2+XJG4gNcaTj7hL+xQAqgQDQ3wEhly2bVrf0n+nuqIrHJaWghbPEi4LvZ/vPhikV7U+amHp5cvzGlHhKJAD5lYvj4bEBToRZ4gAIqXYtRSp4LX3b+y3z76TFM5zqU5qi7twUODyFJyKmaj3vNNW6jCT0vaA8+QGV1ltV+E/ascRirHN4z7ek9LoxSFxuuc3H7GPo0RwQP6NJrsrfyuwiU71iucSPlmunfXztU5bfK9FXXzJe/pgkbrZH56JRyB72YPVeNPsZ21ZMtKnvdyf0d269pymh9Z8y01pRbfNtB5cWLqEv/MOa+3VtpgDcqVOb0cUOqz6CH615bnDtEuJZcZRcMjim/w==
*/