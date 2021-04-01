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
PZho25mLqXfLfDwL8Plq783xIlszHWb4p7X0pYLJokSN60LB94LXFfNkTyfFHnkUdNC62yfjdFZdNyF1mZ8hNPK188fedBlvHPKMzEtYHklvBSnWQgXj8qoR1nDzoSEj4LZ+eobeItjvLm9xoq3VZOICOFB1pirgJMSQnY05YPo+zQPyfJocxH6McofWrCRjjoEsCG5zd5QJvVRqMjn55JV2QipS87ikaTHzS6Bdt8bdJfCcmMRI1mXkTWTLBFkWw8ltcokFRArmZA/Wgb7cvXiS4a76iaf5rC/lH5N/wzi1fpMTKhLHpEewnOJti4HPjsVwUMGRsy507QffOFXwYfTTqhYfPWnKfjWAhDTjdjPhNea/GdeXjTFTPh/nUMPmlLau7n82BdhmYS8gJOs6kZA4wDKz8PBe88Ov2/accMT6GwZ92DEy37eyx30mNwHKmcSKzZXRJp6GaEQkDMFoPWDYmdBsPBcpKv18OLb8FW+wQjeHFaeV2QgQ3bsFm31RoRi7WbKF13zE3cIQrv8fukNbUQrlm8Xy5wHM6rgazPlJmcEQXVJ0opcu8Q==
*/