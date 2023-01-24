//
// detail/impl/service_registry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_SERVICE_REGISTRY_HPP
#define BOOST_ASIO_DETAIL_IMPL_SERVICE_REGISTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Service>
Service& service_registry::use_service()
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  factory_type factory = &service_registry::create<Service, execution_context>;
  return *static_cast<Service*>(do_use_service(key, factory, &owner_));
}

template <typename Service>
Service& service_registry::use_service(io_context& owner)
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  factory_type factory = &service_registry::create<Service, io_context>;
  return *static_cast<Service*>(do_use_service(key, factory, &owner));
}

template <typename Service>
void service_registry::add_service(Service* new_service)
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  return do_add_service(key, new_service);
}

template <typename Service>
bool service_registry::has_service() const
{
  execution_context::service::key key;
  init_key<Service>(key, 0);
  return do_has_service(key);
}

template <typename Service>
inline void service_registry::init_key(
    execution_context::service::key& key, ...)
{
  init_key_from_id(key, Service::id);
}

#if !defined(BOOST_ASIO_NO_TYPEID)
template <typename Service>
void service_registry::init_key(execution_context::service::key& key,
    typename enable_if<
      is_base_of<typename Service::key_type, Service>::value>::type*)
{
  key.type_info_ = &typeid(typeid_wrapper<Service>);
  key.id_ = 0;
}

template <typename Service>
void service_registry::init_key_from_id(execution_context::service::key& key,
    const service_id<Service>& /*id*/)
{
  key.type_info_ = &typeid(typeid_wrapper<Service>);
  key.id_ = 0;
}
#endif // !defined(BOOST_ASIO_NO_TYPEID)

template <typename Service, typename Owner>
execution_context::service* service_registry::create(void* owner)
{
  return new Service(*static_cast<Owner*>(owner));
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_SERVICE_REGISTRY_HPP

/* service_registry.hpp
xl9pRHRYzaZwmRdQlfI2v2g2St/WrqtSeDJc7lidx3fVQvmTCzttmwovRs5c4N4bLCmh+rz9jWmwbIhc9McF5ii+0+lNBzNgbe/gBusvKD96q7fuHZwFPRX3bvbtb2FJmXxZW/w0G8a39e+R3Qf5D9/2Xu6qECZ0Xll9zATl91T6PR23HAhcpdCZ0jG2pHy+tvkOyoXQHzd3bL3fDcVXHlPxPhfidQ9qdjZB5Z/ybJ7O9TzwD7jxeF2ioiXleDZeeUk+JGeO9Z/pjNLjqR/V1S2A4LMql1rDR1pSoguJusICyFvcGnSbN9CSap6h3313IfT4Ftg8bIOhJaX4iupOF4Fgk31TqZ4pys8V2Pe+CPbXjXdvuY/Ka7L/QN6pYnAY1lvBrRHVj4usody0EpiwOig8pgblfwXzvf+3EujDq9PW2z8K1Ufp7R+hL0Hj8l7ns7UaltQ+re0nJ5RC6YDHYLYKtUf3geczP5SC3Zm9pWsPDEDpPyt8euQVxHvsbb/wSx2FTwhRHfUaCtUmOJYamaH2Lpe7lf8afvYUGdsVj0Dx+bjmer+BGIdjnydG/aKp8KEeaupvobje/NzmLCOU/9NnU+68BY9kVXUVq66ovVKv+hmUQVD5qVkeRv0sqVe8haobyiAWwtFwRvVlMbJmNlMGeXvzzu5/3MOSmjH0/EelcqhRthrk/lLTksqPzDOdWw4JeeE3dE6h/nJF
*/