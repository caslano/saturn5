//
// detail/service_registry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_SERVICE_REGISTRY_HPP
#define BOOST_ASIO_DETAIL_SERVICE_REGISTRY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <typeinfo>
#include <boost/asio/detail/mutex.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class io_context;

namespace detail {

template <typename T>
class typeid_wrapper {};

class service_registry
  : private noncopyable
{
public:
  // Constructor.
  BOOST_ASIO_DECL service_registry(execution_context& owner);

  // Destructor.
  BOOST_ASIO_DECL ~service_registry();

  // Shutdown all services.
  BOOST_ASIO_DECL void shutdown_services();

  // Destroy all services.
  BOOST_ASIO_DECL void destroy_services();

  // Notify all services of a fork event.
  BOOST_ASIO_DECL void notify_fork(execution_context::fork_event fork_ev);

  // Get the service object corresponding to the specified service type. Will
  // create a new service object automatically if no such object already
  // exists. Ownership of the service object is not transferred to the caller.
  template <typename Service>
  Service& use_service();

  // Get the service object corresponding to the specified service type. Will
  // create a new service object automatically if no such object already
  // exists. Ownership of the service object is not transferred to the caller.
  // This overload is used for backwards compatibility with services that
  // inherit from io_context::service.
  template <typename Service>
  Service& use_service(io_context& owner);

  // Add a service object. Throws on error, in which case ownership of the
  // object is retained by the caller.
  template <typename Service>
  void add_service(Service* new_service);

  // Check whether a service object of the specified type already exists.
  template <typename Service>
  bool has_service() const;

private:
  // Initalise a service's key when the key_type typedef is not available.
  template <typename Service>
  static void init_key(execution_context::service::key& key, ...);

#if !defined(BOOST_ASIO_NO_TYPEID)
  // Initalise a service's key when the key_type typedef is available.
  template <typename Service>
  static void init_key(execution_context::service::key& key,
      typename enable_if<
        is_base_of<typename Service::key_type, Service>::value>::type*);
#endif // !defined(BOOST_ASIO_NO_TYPEID)

  // Initialise a service's key based on its id.
  BOOST_ASIO_DECL static void init_key_from_id(
      execution_context::service::key& key,
      const execution_context::id& id);

#if !defined(BOOST_ASIO_NO_TYPEID)
  // Initialise a service's key based on its id.
  template <typename Service>
  static void init_key_from_id(execution_context::service::key& key,
      const service_id<Service>& /*id*/);
#endif // !defined(BOOST_ASIO_NO_TYPEID)

  // Check if a service matches the given id.
  BOOST_ASIO_DECL static bool keys_match(
      const execution_context::service::key& key1,
      const execution_context::service::key& key2);

  // The type of a factory function used for creating a service instance.
  typedef execution_context::service*(*factory_type)(void*);

  // Factory function for creating a service instance.
  template <typename Service, typename Owner>
  static execution_context::service* create(void* owner);

  // Destroy a service instance.
  BOOST_ASIO_DECL static void destroy(execution_context::service* service);

  // Helper class to manage service pointers.
  struct auto_service_ptr;
  friend struct auto_service_ptr;
  struct auto_service_ptr
  {
    execution_context::service* ptr_;
    ~auto_service_ptr() { destroy(ptr_); }
  };

  // Get the service object corresponding to the specified service key. Will
  // create a new service object automatically if no such object already
  // exists. Ownership of the service object is not transferred to the caller.
  BOOST_ASIO_DECL execution_context::service* do_use_service(
      const execution_context::service::key& key,
      factory_type factory, void* owner);

  // Add a service object. Throws on error, in which case ownership of the
  // object is retained by the caller.
  BOOST_ASIO_DECL void do_add_service(
      const execution_context::service::key& key,
      execution_context::service* new_service);

  // Check whether a service object with the specified key already exists.
  BOOST_ASIO_DECL bool do_has_service(
      const execution_context::service::key& key) const;

  // Mutex to protect access to internal data.
  mutable boost::asio::detail::mutex mutex_;

  // The owner of this service registry and the services it contains.
  execution_context& owner_;

  // The first service in the list of contained services.
  execution_context::service* first_service_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/detail/impl/service_registry.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/detail/impl/service_registry.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_DETAIL_SERVICE_REGISTRY_HPP

/* service_registry.hpp
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
*/