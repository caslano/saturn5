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
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
*/