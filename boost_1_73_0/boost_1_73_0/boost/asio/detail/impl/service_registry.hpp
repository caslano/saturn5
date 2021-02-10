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
UEsDBAoAAAAIAC1nSlJN8m9G1wAAAEEBAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvaGVhZC5kVVQFAAG2SCRgTY8xbsMwDEV3neJ3r3MAb0WawAEyBEiAzKpEWQIk0ZDoBu7pa2koOnDgB/n4eOU8j/Ckrbp7LjLioiaKy4i9fcGyWRNlQciOwTlu6lZY2HCsI6bH44Zzq8v1pI5aaOay7TiRBa5ViKSGYVBnEuMhnvopKrWz3jphqFS+W+RIy1qojxlOSWeL6fTxiZcPfTtUrJWqEsZMgsx7lGd8rfIPDXbQf+IHPD3ltmb3k9C5+3Lpyt3vXZm1RNhQl6i32kktRw0/hOYQdRUktsEFoyXsGAmJ+gcH9QtQSwMECgAAAAgALWdKUpRugF7rAwAA0wcAACYACQBjdXJsLW1hc3Rlci9kb2NzL2NtZGxpbmUtb3B0cy9oZWFkZXIuZFVUBQABtkgkYG1VXW/cRgx8319B3EM/gNO5QBEEUIMibuDWKQrDSFw0BfyyJ1GnhaWluru6s/59hyvpzg7yYB+8Rw6H5HD8l/hDSS3bmoP53EpIJd2a64DHd/Pr1fvGdfyrueVuKOnexkjVGJP0S9YP8UdKQpHDERD3QZJU0kXAPDzcmw82
*/