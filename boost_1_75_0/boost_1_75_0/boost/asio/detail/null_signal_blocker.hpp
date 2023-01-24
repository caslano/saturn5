//
// detail/null_signal_blocker.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP
#define BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_HAS_THREADS) \
  || defined(BOOST_ASIO_WINDOWS) \
  || defined(BOOST_ASIO_WINDOWS_RUNTIME) \
  || defined(__CYGWIN__) \
  || defined(__SYMBIAN32__)

#include <boost/asio/detail/noncopyable.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class null_signal_blocker
  : private noncopyable
{
public:
  // Constructor blocks all signals for the calling thread.
  null_signal_blocker()
  {
  }

  // Destructor restores the previous signal mask.
  ~null_signal_blocker()
  {
  }

  // Block all signals for the calling thread.
  void block()
  {
  }

  // Restore the previous signal mask.
  void unblock()
  {
  }
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_HAS_THREADS)
       // || defined(BOOST_ASIO_WINDOWS)
       // || defined(BOOST_ASIO_WINDOWS_RUNTIME)
       // || defined(__CYGWIN__)
       // || defined(__SYMBIAN32__)

#endif // BOOST_ASIO_DETAIL_NULL_SIGNAL_BLOCKER_HPP

/* null_signal_blocker.hpp
jz7ki6hNLYxyH5WCsEcGtYPz4JoXQj3wTWUj6dy+5cyZr5X8VB5malNYu0HQsd4wKX0F91pdhc92p9+DttLJjCt8pLEPNKWY2Wac36Vlth8l0PgSEfbQaCKMkcR0nq+SPGg1VSRk7nRudwbUIb2d1chI4TyfaoAII4htIQiuHEu8erTa1DS9qRW+2Wu+h7zHJuvkzQHyXkdCPJ8IArFidzlBQGrrbzGy4npWj8oK3/jvq2dGpJ7343WapVEGLij3s6rEvVgmiBRu6+RaeX1F1rtgG3Lx/DYQFXMfDkwjhCSNqEj+PipeOE+nwkmAG8mKbGNkgHypfAN5ytQKTfy+Qku0QoXhwS6QeddURqqPjFEfGYKwhgnbHcTh4p8yYVvTX9jKfySH356kt40n9OeSkf1ETLArXtZoRFGY7STdfxu1l/G9jHPPHKKrJ+d5yo76x0hBd43Bk22dRPX6Z+dacKK0/NpSHBEsw50Wz8Dz/sXhwqLSkvQjRfITE1WywKiGRkF/YU2hczn3eTTTBm2cn8Teyb3mQeNYgojMp5+FwiXyry8gVCiYamdzLvIbSI8JkWE2P4zZOzpXs7Qjg0wUNlbahcVe5/TRNd8OamIbtoNMSpm4F4shMKYP1zn39WC+cqJe/DLJwEfEYRYjDgNudMhawmHuGwqvuNKg01uEmQTF9OD0id11UiOk7OkH5737mUSRVEC2cq8l2qGd
*/