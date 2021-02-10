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
mJ1uHXxRKaNFT1m/nDlsBSDUpDp7i2TSbz1K5e4DHB5sMUUmjOmIV9Msd0FQgnwMD6zdbx9tSTFTdm5/CZVeyzWghiH11eC9Tt7/79wBL+qBfTLzRWEHuAsJrv4TowcCQLzYWUD7428vdyuTZTYEK1bXprqH6xGKWpaStxGu/0YVgp9bTpo/pEUKj9aD7HerX4ktQmRTBE+w7MqsaHKry2aO6MlMoRHCJs8rPoRNwpPHIxWROMSgpHMY1+8dXxRuxjc1LjkrPAPrpDLZAzIKatD+zgGtdG0ACLAJ6SEhF+oKW3FqoHC3K4hF0FIkS2AiC/n6K4taEBBIpmaVTAQWwua3euvt290tCuYWriEaD3fo8aSpRXTukVeKxca8PYcbfxuNrn97f3b+4+XNhX43vh7pCZlR5shSZBvf3hLiJo1DrSSrE1gx5m19Qgl1kLHV03NrSnIEZzLycJa29V2pupvmntXHpfjS6s6ZPcnNVxMnVVVOf3YK10skpS2Dq3EpkrApp0xVu6wpTJWEJ2DjFGO7kD+ufPQPNh9oYGHN5VGkiA2BkMi0RiCGgDilocN6clVz82BZmAq1WYl/6PhcyEV09F+uh3++uLrT7yQ/fLXiU77tYipU2/vJ00RLRLtvu4cgETyCwm19yKaK
*/