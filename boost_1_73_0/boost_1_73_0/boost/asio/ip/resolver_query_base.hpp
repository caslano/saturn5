//
// ip/resolver_query_base.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP
#define BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/ip/resolver_base.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

/// The resolver_query_base class is used as a base for the
/// basic_resolver_query class templates to provide a common place to define
/// the flag constants.
class resolver_query_base : public resolver_base
{
protected:
  /// Protected destructor to prevent deletion through this type.
  ~resolver_query_base()
  {
  }
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_RESOLVER_QUERY_BASE_HPP

/* resolver_query_base.hpp
gjLfVX+GdEey5GQToaBan3Bt13M4Jrd0oeATNtD8UBbjECFd0eUysXPptDd6zF4+2DhTJAWTxQI4QAV8e306maiL0+np9SBMLqumEFKaWVfn+oFsFUCzlFPXwrCfzFpplaqap5vheAr1QY60Akwlm566i4wmMqV0Q0eE9AW9QK4R1kKUGPq5WXi+DZhL5508Xr5TbHOKNXvwZgOsnWCat4y/QVcYGnGQheM/1y6kiVB7t6m6SNXbVPG0cV9mHR0+/S7gwk6PoY5umYL8NRGpI3V0EZ589+P3PzwPS/W0qFMzvFaILLE7R7clIAhcP7ZEQrZt6MkCKe0CK8kkZHtjhzMBaQv0jFjCQ0thAd9agvyOp29Qhi8rHFsH/v7IpOhJNpwNwtfyoqTgANASTggxmBT2PlaenelQCbc1QiGoMeobTGmuvoogpq9U3/HVZMosA/GGhJ/QUHonPb5QUW4fgSNVKJLuuEikxUKdt0lz6Or7OXv/2E93SHSkutRv06Z1bcwcHhfVNoeytIxw9Y39N9SqhqUIDWyLdrb/2Asbc7B3lbP73iCDmW4GfXMQj9UbsxQmKdbiDrrhQ4xmJZMz2gV4DuO5O/6R04ro6W95GUQDUUy+F8o3M3U4dDAfc7UOJ9zSCclbgklyFRmL
*/