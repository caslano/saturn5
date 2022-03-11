//
// execution_context.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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