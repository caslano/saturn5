//
// execution_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_CONTEXT_HPP
#define BOOST_ASIO_EXECUTION_CONTEXT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <cstddef>
#include <stdexcept>
#include <typeinfo>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

class execution_context;
class io_context;

#if !defined(GENERATING_DOCUMENTATION)
template <typename Service> Service& use_service(execution_context&);
template <typename Service> Service& use_service(io_context&);
template <typename Service> void add_service(execution_context&, Service*);
template <typename Service> bool has_service(execution_context&);
#endif // !defined(GENERATING_DOCUMENTATION)

namespace detail { class service_registry; }

/// A context for function object execution.
/**
 * An execution context represents a place where function objects will be
 * executed. An @c io_context is an example of an execution context.
 *
 * @par The execution_context class and services
 *
 * Class execution_context implements an extensible, type-safe, polymorphic set
 * of services, indexed by service type.
 *
 * Services exist to manage the resources that are shared across an execution
 * context. For example, timers may be implemented in terms of a single timer
 * queue, and this queue would be stored in a service.
 *
 * Access to the services of an execution_context is via three function
 * templates, use_service(), add_service() and has_service().
 *
 * In a call to @c use_service<Service>(), the type argument chooses a service,
 * making available all members of the named type. If @c Service is not present
 * in an execution_context, an object of type @c Service is created and added
 * to the execution_context. A C++ program can check if an execution_context
 * implements a particular service with the function template @c
 * has_service<Service>().
 *
 * Service objects may be explicitly added to an execution_context using the
 * function template @c add_service<Service>(). If the @c Service is already
 * present, the service_already_exists exception is thrown. If the owner of the
 * service is not the same object as the execution_context parameter, the
 * invalid_service_owner exception is thrown.
 *
 * Once a service reference is obtained from an execution_context object by
 * calling use_service(), that reference remains usable as long as the owning
 * execution_context object exists.
 *
 * All service implementations have execution_context::service as a public base
 * class. Custom services may be implemented by deriving from this class and
 * then added to an execution_context using the facilities described above.
 *
 * @par The execution_context as a base class
 *
 * Class execution_context may be used only as a base class for concrete
 * execution context types. The @c io_context is an example of such a derived
 * type.
 *
 * On destruction, a class that is derived from execution_context must perform
 * <tt>execution_context::shutdown()</tt> followed by
 * <tt>execution_context::destroy()</tt>.
 *
 * This destruction sequence permits programs to simplify their resource
 * management by using @c shared_ptr<>. Where an object's lifetime is tied to
 * the lifetime of a connection (or some other sequence of asynchronous
 * operations), a @c shared_ptr to the object would be bound into the handlers
 * for all asynchronous operations associated with it. This works as follows:
 *
 * @li When a single connection ends, all associated asynchronous operations
 * complete. The corresponding handler objects are destroyed, and all @c
 * shared_ptr references to the objects are destroyed.
 *
 * @li To shut down the whole program, the io_context function stop() is called
 * to terminate any run() calls as soon as possible. The io_context destructor
 * calls @c shutdown() and @c destroy() to destroy all pending handlers,
 * causing all @c shared_ptr references to all connection objects to be
 * destroyed.
 */
class execution_context
  : private noncopyable
{
public:
  class id;
  class service;

public:
  /// Constructor.
  BOOST_ASIO_DECL execution_context();

  /// Destructor.
  BOOST_ASIO_DECL ~execution_context();

protected:
  /// Shuts down all services in the context.
  /**
   * This function is implemented as follows:
   *
   * @li For each service object @c svc in the execution_context set, in
   * reverse order of the beginning of service object lifetime, performs @c
   * svc->shutdown().
   */
  BOOST_ASIO_DECL void shutdown();

  /// Destroys all services in the context.
  /**
   * This function is implemented as follows:
   *
   * @li For each service object @c svc in the execution_context set, in
   * reverse order * of the beginning of service object lifetime, performs
   * <tt>delete static_cast<execution_context::service*>(svc)</tt>.
   */
  BOOST_ASIO_DECL void destroy();

public:
  /// Fork-related event notifications.
  enum fork_event
  {
    /// Notify the context that the process is about to fork.
    fork_prepare,

    /// Notify the context that the process has forked and is the parent.
    fork_parent,

    /// Notify the context that the process has forked and is the child.
    fork_child
  };

  /// Notify the execution_context of a fork-related event.
  /**
   * This function is used to inform the execution_context that the process is
   * about to fork, or has just forked. This allows the execution_context, and
   * the services it contains, to perform any necessary housekeeping to ensure
   * correct operation following a fork.
   *
   * This function must not be called while any other execution_context
   * function, or any function associated with the execution_context's derived
   * class, is being called in another thread. It is, however, safe to call
   * this function from within a completion handler, provided no other thread
   * is accessing the execution_context or its derived class.
   *
   * @param event A fork-related event.
   *
   * @throws boost::system::system_error Thrown on failure. If the notification
   * fails the execution_context object should no longer be used and should be
   * destroyed.
   *
   * @par Example
   * The following code illustrates how to incorporate the notify_fork()
   * function:
   * @code my_execution_context.notify_fork(execution_context::fork_prepare);
   * if (fork() == 0)
   * {
   *   // This is the child process.
   *   my_execution_context.notify_fork(execution_context::fork_child);
   * }
   * else
   * {
   *   // This is the parent process.
   *   my_execution_context.notify_fork(execution_context::fork_parent);
   * } @endcode
   *
   * @note For each service object @c svc in the execution_context set,
   * performs <tt>svc->notify_fork();</tt>. When processing the fork_prepare
   * event, services are visited in reverse order of the beginning of service
   * object lifetime. Otherwise, services are visited in order of the beginning
   * of service object lifetime.
   */
  BOOST_ASIO_DECL void notify_fork(fork_event event);

  /// Obtain the service object corresponding to the given type.
  /**
   * This function is used to locate a service object that corresponds to the
   * given service type. If there is no existing implementation of the service,
   * then the execution_context will create a new instance of the service.
   *
   * @param e The execution_context object that owns the service.
   *
   * @return The service interface implementing the specified service type.
   * Ownership of the service interface is not transferred to the caller.
   */
  template <typename Service>
  friend Service& use_service(execution_context& e);

  /// Obtain the service object corresponding to the given type.
  /**
   * This function is used to locate a service object that corresponds to the
   * given service type. If there is no existing implementation of the service,
   * then the io_context will create a new instance of the service.
   *
   * @param ioc The io_context object that owns the service.
   *
   * @return The service interface implementing the specified service type.
   * Ownership of the service interface is not transferred to the caller.
   *
   * @note This overload is preserved for backwards compatibility with services
   * that inherit from io_context::service.
   */
  template <typename Service>
  friend Service& use_service(io_context& ioc);

#if defined(GENERATING_DOCUMENTATION)

  /// Creates a service object and adds it to the execution_context.
  /**
   * This function is used to add a service to the execution_context.
   *
   * @param e The execution_context object that owns the service.
   *
   * @param args Zero or more arguments to be passed to the service
   * constructor.
   *
   * @throws boost::asio::service_already_exists Thrown if a service of the
   * given type is already present in the execution_context.
   */
  template <typename Service, typename... Args>
  friend Service& make_service(execution_context& e, Args&&... args);

#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Service, typename... Args>
  friend Service& make_service(execution_context& e,
      BOOST_ASIO_MOVE_ARG(Args)... args);

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Service>
  friend Service& make_service(execution_context& e);

#define BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF(n) \
  template <typename Service, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  friend Service& make_service(execution_context& e, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)); \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF)
#undef BOOST_ASIO_PRIVATE_MAKE_SERVICE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  /// (Deprecated: Use make_service().) Add a service object to the
  /// execution_context.
  /**
   * This function is used to add a service to the execution_context.
   *
   * @param e The execution_context object that owns the service.
   *
   * @param svc The service object. On success, ownership of the service object
   * is transferred to the execution_context. When the execution_context object
   * is destroyed, it will destroy the service object by performing: @code
   * delete static_cast<execution_context::service*>(svc) @endcode
   *
   * @throws boost::asio::service_already_exists Thrown if a service of the
   * given type is already present in the execution_context.
   *
   * @throws boost::asio::invalid_service_owner Thrown if the service's owning
   * execution_context is not the execution_context object specified by the
   * @c e parameter.
   */
  template <typename Service>
  friend void add_service(execution_context& e, Service* svc);

  /// Determine if an execution_context contains a specified service type.
  /**
   * This function is used to determine whether the execution_context contains a
   * service object corresponding to the given service type.
   *
   * @param e The execution_context object that owns the service.
   *
   * @return A boolean indicating whether the execution_context contains the
   * service.
   */
  template <typename Service>
  friend bool has_service(execution_context& e);

private:
  // The service registry.
  boost::asio::detail::service_registry* service_registry_;
};

/// Class used to uniquely identify a service.
class execution_context::id
  : private noncopyable
{
public:
  /// Constructor.
  id() {}
};

/// Base class for all io_context services.
class execution_context::service
  : private noncopyable
{
public:
  /// Get the context object that owns the service.
  execution_context& context();

protected:
  /// Constructor.
  /**
   * @param owner The execution_context object that owns the service.
   */
  BOOST_ASIO_DECL service(execution_context& owner);

  /// Destructor.
  BOOST_ASIO_DECL virtual ~service();

private:
  /// Destroy all user-defined handler objects owned by the service.
  virtual void shutdown() = 0;

  /// Handle notification of a fork-related event to perform any necessary
  /// housekeeping.
  /**
   * This function is not a pure virtual so that services only have to
   * implement it if necessary. The default implementation does nothing.
   */
  BOOST_ASIO_DECL virtual void notify_fork(
      execution_context::fork_event event);

  friend class boost::asio::detail::service_registry;
  struct key
  {
    key() : type_info_(0), id_(0) {}
    const std::type_info* type_info_;
    const execution_context::id* id_;
  } key_;

  execution_context& owner_;
  service* next_;
};

/// Exception thrown when trying to add a duplicate service to an
/// execution_context.
class service_already_exists
  : public std::logic_error
{
public:
  BOOST_ASIO_DECL service_already_exists();
};

/// Exception thrown when trying to add a service object to an
/// execution_context where the service has a different owner.
class invalid_service_owner
  : public std::logic_error
{
public:
  BOOST_ASIO_DECL invalid_service_owner();
};

namespace detail {

// Special derived service id type to keep classes header-file only.
template <typename Type>
class service_id
  : public execution_context::id
{
};

// Special service base class to keep classes header-file only.
template <typename Type>
class execution_context_service_base
  : public execution_context::service
{
public:
  static service_id<Type> id;

  // Constructor.
  execution_context_service_base(execution_context& e)
    : execution_context::service(e)
  {
  }
};

template <typename Type>
service_id<Type> execution_context_service_base<Type>::id;

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/execution_context.hpp>
#if defined(BOOST_ASIO_HEADER_ONLY)
# include <boost/asio/impl/execution_context.ipp>
#endif // defined(BOOST_ASIO_HEADER_ONLY)

#endif // BOOST_ASIO_EXECUTION_CONTEXT_HPP

/* execution_context.hpp
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
*/