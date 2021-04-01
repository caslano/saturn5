//
// ip/bad_address_cast.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BAD_ADDRESS_CAST_HPP
#define BOOST_ASIO_IP_BAD_ADDRESS_CAST_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <typeinfo>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// Thrown to indicate a failed address conversion.
class bad_address_cast :
#if defined(BOOST_ASIO_MSVC) && defined(_HAS_EXCEPTIONS) && !_HAS_EXCEPTIONS
  public std::exception
#else
  public std::bad_cast
#endif
{
public:
  /// Default constructor.
  bad_address_cast() {}

  /// Destructor.
  virtual ~bad_address_cast() BOOST_ASIO_NOEXCEPT_OR_NOTHROW {}

  /// Get the message associated with the exception.
  virtual const char* what() const BOOST_ASIO_NOEXCEPT_OR_NOTHROW
  {
    return "bad address cast";
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_ADDRESS_HPP

/* bad_address_cast.hpp
uKKSHChS2LlvFORiRZKTXbsh1mvfiU0D3S+AlAkoc1wJ/W2QvnjvrJQh+gqYtDQNUGN4DKqcPzCUPbGAEBzhY0S8a74UKVBa5citjlaFbjNPV9w407OFY4vjWgBPOIjtqDSgG9OqOCMN1WX1r4RVUdYzU0gNM1MzQ+eX9a36zF3Oi8DInZcJraOAmw31Q5jtuOXe8/LraOPm3meuMAt5FS/7K1P2V25QCdROJAubV5SuZJ/w2QAbGlM/250lDYzKcPWBCfUMzIb1RuRzUAja19oUsOJ9a/LydK9yUIy2GKKevdzO10zQwx7MPQmqpn9bglNxj9mP0JOm7GxzA/nP9aUUkdNuPc468YL6STej8TkAeIrIKkT6nWeWxvKk2pDHhGhBf65sb/fp5txBkgYfB/v7PIadKfF6OrswHv41JWnh7vIn7Niy6cVtyzG7yT/8nZn30u5UEwrXfkQ3DNowxEPwTaBl7zUGLjbq/RiehlGNMpojz6l3YHHvEwQUoPx14HAq0fbKnl8s4bJfJiaT8NsmmNj+nwk8euNPBufNsKv/HmarXjclKHlXCw==
*/