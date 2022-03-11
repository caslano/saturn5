//
// detail/service_registry.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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