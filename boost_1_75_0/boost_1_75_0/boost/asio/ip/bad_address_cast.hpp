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
WCz6LOhX1fgRwhHKy5E5sCcvgoua2ScZWy/6moxU2kqFCIs7X2JTnFJcsFUJmmV4PpmUAdqpZTmKSojEYKIF3nAOQE82f+ALUaPrUBJjjKSQtNHNSqj7z29GWXY4wqMt7HKFxi+GgxFK5Ox2mMiCutwVt+8mDbos/lLRsz2Jo4Lh2vknrD/ic+qdVmKocaxwy44s5Jtdn7qUTvzXKRacOxck5mR7SOHWLBpoZGf3hLBoHMguMjC7lfhL5S0SS2pH3AKl1yngC0q1qLPgASGftD6FyLuyFJHX4rdvmQoybzLprzNuMhmv8/5I8Y5nG55Q7o6cSoyeFx5oSgX9pTHQES1DZz0mFghywNorjcHT/a6VRVyViXKnBaefY3q7LiraSBw0qpd6ls+BGrq89m6sF+ACRwTsPedoyESJ66Qea+1IeOIyqo7znop+mMDxG9hkERmVyZGT/Yh2gRDx58uv9HZaal6+UWlb3CGsxGlVJnYUWt5UH4GozTxqEUOa0+iJkSHPXRxps/hqmYQOIQEG3PilcVUUA92HYvyb03FdE9avqbwY0nJzMSPk0ebKtAPSfjzOoYRrVbPjiiS/Ex++fn6I4rjEZgvnishsh8/MfoIJebj/Csj3EaiMaBGjSORfj9goPuH/3VHMyMi26kl0xrHa8q9Prq7hC7N6/M28s6fC3dHZ3qB0a6JIcU/Xe5Fnq25brQCVtz4o5fKY
*/