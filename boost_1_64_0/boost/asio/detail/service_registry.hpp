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
zvKl/OXmTRdfjeHi+sPUnz9Mvso4w+Yre72NdW/PVUjX29ITTRH7tQZOe1F2F3pJDXmLYXpYc9iJYt9qXGL4HN9YYo0VOeJ/g1HL81W5VhwZzvmBfCNZ8xP97zSWGiPp5jO+LW4j5dRVisVn9ZX1taUlBbponPzFOOy9J20sPimz98kKzdXg+kRZIxyDdrpzBO7mVXPTcFnCaW3cZ6I+P4U9I7qei4xkV/2yLKVeSUOZPN+ikbIQvii06t6VTxcP3Dwa//Cu4xDM9eSBxAwHD1RWSe/i0bdYZdFF6M/BqbQ4W84Wt3jSoJbEPg3zmzHN9kE6bJzVvlLFvs2zDyJfMMz2ZvsbTZck9gWwdxP7NdFzWer3eon/bOyOjBN+yDScvML4yL+63ddI3AF5i5xrzJyPrxZ7PyNF/M0ymWPE4b/OdG/v4W7HLfNy4aerhCbVkilWiX2QxOFTcTDdflB0pHtStLvoWnPQF5wcJX0n5I34cHIgHF8RPyiyu2y2v8yUuGdgH00cZdqo73n2o8ms965Cm2dM0uHhFlUWVh9rxGpH7C/jYvSxiU30sakx+tiMJvrYTHcf65rD7hmrE3U3w29h+zrkbF+rcFK3uKimJNb4zTbWvpsKs4Tty4xjWLNtSdNlWfqPRImnyrstsV9uKzSr2LbMOAY227Y0XT9rHthG4mn0HNtTVFmIf62jPTEOpx5I0sn95TU2r/STsKNhb2OdTfr7YN3P/mNw82cIuM7pySP5TfBIYQweWdYEj1Q3MQ4/PV4n6mLVFxHjx4J3dNmpQxschQ3OsaLOMpF2hJTNObB/LvYJvhRf0Jqb+hxz05lWmJ7WWPuW2Bf6uvraRe0XSSMPJnbXZw/GYM57P9a7PzQ6WHqUJ8WvAbJEED45rvWqwxJ3pnNPCePq6xtntJZ4TqO+7LjQTvbFmgv+VsK1px2zjO4eOgHqAN5VfrAlc178pcQ93PcrI5frvHa6e4NurtGLc2i3+xzuwTuWFD137CJ0cY61Z+rg2d56i/9inv3zWflOMeqMz9EfDkX/+/RY5DtH7y8JLI2fEj9DdbmYnJVhpUvNyVI7w9p4DX61U1tiIvTZkbp7SyZbL9/6GUaJVbG+Lzr8feMwsuRYOvzfRunwSbMlx9ThN26L0uGTZncOdfgdVkfr8ElzNMfU4a9bKufKYT+SQx0+3KJ0+DRpLKue4zk3jmv8NCEwUCbGnvNi0k8bb82LfZHz4jTYETxq3vhRC/b5cH2MZ9jdZ5UDcm5D2hxlcXv/T+RZ0+BEvk/OOd5KmKc6Qy7rIX1A2dDagvEL5gwpmDxn4ezJ88fnTZ6kx4pr5BxHRWndsqoSx1oRw/XlPDtirYF8u1to0tgfMAz3Q3RuL2fcKp1rui+J/wTv86LsH+4XmouMto6zgj9VZ2M66TMyn7XgbIw517lGzl848sZypW7btcafM8m7/HJ6ustv+py8yVMnz2+q7BCm+bLLExqWHcM0VXYrejZfdvN6RpfdL/6jZafHn+wpfHuOZXct12gPseyqV2bLJRzc5+xYp12Z7Uz/MaHfiDqwzlYyjmTnOm2ls+/8h/hn2rIKyzXWmnz/XrLPSsYKuRNC7Atjrs0PF/+zhH6Zi957jX6C+A/kmn/sNfq5QpfBNX/nfgLKHTHn/5HrIixDyhxcT7Z0S4X22fUs022Z7TbEdMuy3YaabtmWm6Rd6nwQ67x8qk7QvazzO2C6gM+29zLrfHhB8RLnGgjuiamw2gjpOlpz7gfFfrlRLOOyud5A+UeXLcNcD2kvVcskwkP1tTXw60oeekBobjKUjDAUZjJMg61TYhzJ7Ov1+v3JFvbT9plrnZdk190ATCvbT0A=
*/