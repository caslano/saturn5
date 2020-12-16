//
// ip/resolver_base.hpp
// ~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/socket_types.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_base class is used as a base for the basic_resolver class
/// templates to provide a common place to define the flag constants.
class resolver_base
{
public:
#if defined(GENERATING_DOCUMENTATION)
  /// A bitmask type (C++ Std [lib.bitmask.types]).
  typedef unspecified flags;

  /// Determine the canonical name of the host specified in the query.
  static const flags canonical_name = implementation_defined;

  /// Indicate that returned endpoint is intended for use as a locally bound
  /// socket endpoint.
  static const flags passive = implementation_defined;

  /// Host name should be treated as a numeric string defining an IPv4 or IPv6
  /// address and no name resolution should be attempted.
  static const flags numeric_host = implementation_defined;

  /// Service name should be treated as a numeric string defining a port number
  /// and no name resolution should be attempted.
  static const flags numeric_service = implementation_defined;

  /// If the query protocol family is specified as IPv6, return IPv4-mapped
  /// IPv6 addresses on finding no IPv6 addresses.
  static const flags v4_mapped = implementation_defined;

  /// If used with v4_mapped, return all matching IPv6 and IPv4 addresses.
  static const flags all_matching = implementation_defined;

  /// Only return IPv4 addresses if a non-loopback IPv4 address is configured
  /// for the system. Only return IPv6 addresses if a non-loopback IPv6 address
  /// is configured for the system.
  static const flags address_configured = implementation_defined;
#else
  enum flags
  {
    canonical_name = BOOST_ASIO_OS_DEF(AI_CANONNAME),
    passive = BOOST_ASIO_OS_DEF(AI_PASSIVE),
    numeric_host = BOOST_ASIO_OS_DEF(AI_NUMERICHOST),
    numeric_service = BOOST_ASIO_OS_DEF(AI_NUMERICSERV),
    v4_mapped = BOOST_ASIO_OS_DEF(AI_V4MAPPED),
    all_matching = BOOST_ASIO_OS_DEF(AI_ALL),
    address_configured = BOOST_ASIO_OS_DEF(AI_ADDRCONFIG)
  };

  // Implement bitmask operations as shown in C++ Std [lib.bitmask.types].

  friend flags operator&(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) & static_cast<unsigned int>(y));
  }

  friend flags operator|(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) | static_cast<unsigned int>(y));
  }

  friend flags operator^(flags x, flags y)
  {
    return static_cast<flags>(
        static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y));
  }

  friend flags operator~(flags x)
  {
    return static_cast<flags>(~static_cast<unsigned int>(x));
  }

  friend flags& operator&=(flags& x, flags y)
  {
    x = x & y;
    return x;
  }

  friend flags& operator|=(flags& x, flags y)
  {
    x = x | y;
    return x;
  }

  friend flags& operator^=(flags& x, flags y)
  {
    x = x ^ y;
    return x;
  }
#endif

protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_BASE_HPP

/* resolver_base.hpp
4ey8TSDc25L+57S8TFkaPfTNUj4ZZn/GfWKvZPZOrOxNtJ0Qkz2sycuHk0RP1YOJMWx9PJL/EfbPS9EwywjzPGGYP3Mw0dMkdL86ldtp4l46t65xHzJxL70lXNznY2+G/R2unXcx72FuI+9pyXyXVmJwi+xe1tHHcqVtbtd5WtXH2B9ptRXYy/EQv7kGses1iNvbkOvM6GsfMePB5toQ90zjbtq/0bWi/eCu7aeGjvbKevzTbz6yvjcs6s6P5oF+omxaRXlJoXYVQX3F1HLHuLiG6Wf0hfuJ/R5Xzb1hRhjZLqbtdRH7Z2p3WZtT5TqX9v++tNUxOQN7BPbD6gt170gOe1eagB7cKIkrzrTbCWKfoXZ/3KdL+PRYO3whPWhgH8kzRH6uK9tahQxuJkxvZBxhZPYk59Vwl0i40DDaD+l+qXpdTZXKMPlPF9mVYfNfaen5pFYDOoWT5Xyp1kjaME1R2t2u9r79Jack+VjegrW+tU0WKDt28LknECge4/NXGW23+cdot3mOfb1Ia9B8zdWmHWv7wG1tcDuW+qNesZt6Ne2Y8sVdy1fba09tr7lxgT2AGmBo2tJe81uY9qoNNVI7VVliCG2Xxs/0Ex/UYU8l1d0IyXPfQJ6D9Kkn69zlR2Poq+Fd8At7XZ6aeZiCfmdoPsy9ea/Il8dovjR8v9B8Gb+Zpq3+U+wjYnSvf37Pma2b2ei91h9mmlwXZdg/EXuXmMmuicjgRv23biPzX6SNU+9mfzzC2dEZHfwjEvZ8SWuJiTs/eB9UPXepibeL5CVZ/EvNHqlDWvquq1NUnzYFt2da+tLRzKrvc8P2nrgVeGdZw4PnBWh+RqXZ/m1NXu4Ue1zgmqNMtJc1zxuvSrpnx/j3l0Jm+gztO/Lwf1PO2Z6U1TNzhDIk3pZmjydL93jy61i/9gNfftJIZWDu9lS7Ksw8u/sl3i/VruWj6xTliXwlmxRNKSidEegHd8l5G0qchb69wu0TG/9xct7mgbU98OcuwXUoz3Pqf9T1inUJ+wGkiNxA7W8Rs5JVrktrmcPr2m05ZUqMTGawjCPNJsmE88m9K3LTnOcq8fv3dfi/wvXZ25L7rJgPOwffe9Pp35a0QbeB35dC3I05gmzPDr7frZE7rbGEMeYj/MvU7WPz2/SvRn47+pNZTQJ+X+hzwU2pPntMOh0E/p9o2g6mBfgpbj1Iw2ealrehv+/NOsa8X+o+qL+tCtP3rHT2t9onc11iN9e5hF1r3OV6NTpnDSSstAfjNlDc/HVPn2fcpK5N/50nbqZua4TH3cw9D96Tf5vOf7oR47XX/UoP7Q+nFJVL27he+rciZ7+u8t1NH/ehL3y4/hDZ4LlN74u9wqrZH1qOuU3viMzFYi82cZwats9riv0t8S8We4mR76j+7Czf1rbHhPaBGn6k+NcLkY/X+wF9hHnG+Sbd17+35rqItd9b8Z+FmYwpxdj3sdl1WH/Bv3YK5UtdFZn2lFOjPeXVaE+Whp0Y3J6C6jkxKfTeXUhi1rWtWc963vD1jHzE+zd+wffvvx/H/VvzHPH+bfZxlv+UOaaDMjcVd0c+aOUshDR/3nS2eeMpJtKziIY53cz1iWln2/eiM+UyfaDL9IHk0YQZpnZWm5IwDcK9N5v7o1tkXrB2UOrafjWensHzTfQ996j4/QGdLHfwvVOvhTiJ70LdR92fhiyrGxLx5v2R60nXU/lG4tvHOvpe3/xn7bvbJfv77LrNMckL7utMmzN9iz5H5oe+JwXVYWZTjVn3Z/wrptDWXz0lXB1Kqwypw5b6HNZXwjxlJTH35grMBquR1q8/vgy952ldSreo9Wlk0qyWeq/vIvb98l59I2YHJVo=
*/