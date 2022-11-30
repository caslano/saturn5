//
// ip/basic_resolver.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IP_BASIC_RESOLVER_HPP
#define BOOST_ASIO_IP_BASIC_RESOLVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <string>
#include <boost/asio/any_io_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/basic_resolver_results.hpp>
#include <boost/asio/ip/resolver_base.hpp>
#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
# include <boost/asio/detail/winrt_resolver_service.hpp>
#else
# include <boost/asio/detail/resolver_service.hpp>
#endif

#if defined(BOOST_ASIO_HAS_MOVE)
# include <utility>
#endif // defined(BOOST_ASIO_HAS_MOVE)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ip {

#if !defined(BOOST_ASIO_IP_BASIC_RESOLVER_FWD_DECL)
#define BOOST_ASIO_IP_BASIC_RESOLVER_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename InternetProtocol, typename Executor = any_io_executor>
class basic_resolver;

#endif // !defined(BOOST_ASIO_IP_BASIC_RESOLVER_FWD_DECL)

/// Provides endpoint resolution functionality.
/**
 * The basic_resolver class template provides the ability to resolve a query
 * to a list of endpoints.
 *
 * @par Thread Safety
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 */
template <typename InternetProtocol, typename Executor>
class basic_resolver
  : public resolver_base
{
public:
  /// The type of the executor associated with the object.
  typedef Executor executor_type;

  /// Rebinds the resolver type to another executor.
  template <typename Executor1>
  struct rebind_executor
  {
    /// The resolver type when rebound to the specified executor.
    typedef basic_resolver<InternetProtocol, Executor1> other;
  };

  /// The protocol type.
  typedef InternetProtocol protocol_type;

  /// The endpoint type.
  typedef typename InternetProtocol::endpoint endpoint_type;

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated.) The query type.
  typedef basic_resolver_query<InternetProtocol> query;

  /// (Deprecated.) The iterator type.
  typedef basic_resolver_iterator<InternetProtocol> iterator;
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// The results type.
  typedef basic_resolver_results<InternetProtocol> results_type;

  /// Construct with executor.
  /**
   * This constructor creates a basic_resolver.
   *
   * @param ex The I/O executor that the resolver will use, by default, to
   * dispatch handlers for any asynchronous operations performed on the
   * resolver.
   */
  explicit basic_resolver(const executor_type& ex)
    : impl_(0, ex)
  {
  }

  /// Construct with execution context.
  /**
   * This constructor creates a basic_resolver.
   *
   * @param context An execution context which provides the I/O executor that
   * the resolver will use, by default, to dispatch handlers for any
   * asynchronous operations performed on the resolver.
   */
  template <typename ExecutionContext>
  explicit basic_resolver(ExecutionContext& context,
      typename constraint<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type = 0)
    : impl_(0, 0, context)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_resolver from another.
  /**
   * This constructor moves a resolver from one object to another.
   *
   * @param other The other basic_resolver object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_resolver(const executor_type&) constructor.
   */
  basic_resolver(basic_resolver&& other)
    : impl_(std::move(other.impl_))
  {
  }

  // All resolvers have access to each other's implementations.
  template <typename InternetProtocol1, typename Executor1>
  friend class basic_resolver;

  /// Move-construct a basic_resolver from another.
  /**
   * This constructor moves a resolver from one object to another.
   *
   * @param other The other basic_resolver object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_resolver(const executor_type&) constructor.
   */
  template <typename Executor1>
  basic_resolver(basic_resolver<InternetProtocol, Executor1>&& other,
      typename constraint<
          is_convertible<Executor1, Executor>::value
      >::type = 0)
    : impl_(std::move(other.impl_))
  {
  }

  /// Move-assign a basic_resolver from another.
  /**
   * This assignment operator moves a resolver from one object to another.
   * Cancels any outstanding asynchronous operations associated with the target
   * object.
   *
   * @param other The other basic_resolver object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_resolver(const executor_type&) constructor.
   */
  basic_resolver& operator=(basic_resolver&& other)
  {
    impl_ = std::move(other.impl_);
    return *this;
  }

  /// Move-assign a basic_resolver from another.
  /**
   * This assignment operator moves a resolver from one object to another.
   * Cancels any outstanding asynchronous operations associated with the target
   * object.
   *
   * @param other The other basic_resolver object from which the move will
   * occur.
   *
   * @note Following the move, the moved-from object is in the same state as if
   * constructed using the @c basic_resolver(const executor_type&) constructor.
   */
  template <typename Executor1>
  typename constraint<
    is_convertible<Executor1, Executor>::value,
    basic_resolver&
  >::type operator=(basic_resolver<InternetProtocol, Executor1>&& other)
  {
    basic_resolver tmp(std::move(other));
    impl_ = std::move(tmp.impl_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destroys the resolver.
  /**
   * This function destroys the resolver, cancelling any outstanding
   * asynchronous wait operations associated with the resolver as if by calling
   * @c cancel.
   */
  ~basic_resolver()
  {
  }

  /// Get the executor associated with the object.
  executor_type get_executor() BOOST_ASIO_NOEXCEPT
  {
    return impl_.get_executor();
  }

  /// Cancel any asynchronous operations that are waiting on the resolver.
  /**
   * This function forces the completion of any pending asynchronous
   * operations on the host resolver. The handler for each cancelled operation
   * will be invoked with the boost::asio::error::operation_aborted error code.
   */
  void cancel()
  {
    return impl_.get_service().cancel(impl_.get_implementation());
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use overload with separate host and service parameters.)
  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve a query into a list of endpoint entries.
   *
   * @param q A query object that determines what endpoints will be returned.
   *
   * @returns A range object representing the list of endpoint entries. A
   * successful call to this function is guaranteed to return a non-empty
   * range.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  results_type resolve(const query& q)
  {
    boost::system::error_code ec;
    results_type r = impl_.get_service().resolve(
        impl_.get_implementation(), q, ec);
    boost::asio::detail::throw_error(ec, "resolve");
    return r;
  }

  /// (Deprecated: Use overload with separate host and service parameters.)
  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve a query into a list of endpoint entries.
   *
   * @param q A query object that determines what endpoints will be returned.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns A range object representing the list of endpoint entries. An
   * empty range is returned if an error occurs. A successful call to this
   * function is guaranteed to return a non-empty range.
   */
  results_type resolve(const query& q, boost::system::error_code& ec)
  {
    return impl_.get_service().resolve(impl_.get_implementation(), q, ec);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @returns A range object representing the list of endpoint entries. A
   * successful call to this function is guaranteed to return a non-empty
   * range.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service)
  {
    return resolve(host, service, resolver_base::flags());
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns A range object representing the list of endpoint entries. An
   * empty range is returned if an error occurs. A successful call to this
   * function is guaranteed to return a non-empty range.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service, boost::system::error_code& ec)
  {
    return resolve(host, service, resolver_base::flags(), ec);
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @returns A range object representing the list of endpoint entries. A
   * successful call to this function is guaranteed to return a non-empty
   * range.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service, resolver_base::flags resolve_flags)
  {
    boost::system::error_code ec;
    basic_resolver_query<protocol_type> q(static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);
    results_type r = impl_.get_service().resolve(
        impl_.get_implementation(), q, ec);
    boost::asio::detail::throw_error(ec, "resolve");
    return r;
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns A range object representing the list of endpoint entries. An
   * empty range is returned if an error occurs. A successful call to this
   * function is guaranteed to return a non-empty range.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service, resolver_base::flags resolve_flags,
      boost::system::error_code& ec)
  {
    basic_resolver_query<protocol_type> q(static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);
    return impl_.get_service().resolve(impl_.get_implementation(), q, ec);
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @returns A range object representing the list of endpoint entries. A
   * successful call to this function is guaranteed to return a non-empty
   * range.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service)
  {
    return resolve(protocol, host, service, resolver_base::flags());
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns A range object representing the list of endpoint entries. An
   * empty range is returned if an error occurs. A successful call to this
   * function is guaranteed to return a non-empty range.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      boost::system::error_code& ec)
  {
    return resolve(protocol, host, service, resolver_base::flags(), ec);
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @returns A range object representing the list of endpoint entries. A
   * successful call to this function is guaranteed to return a non-empty
   * range.
   *
   * @throws boost::system::system_error Thrown on failure.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      resolver_base::flags resolve_flags)
  {
    boost::system::error_code ec;
    basic_resolver_query<protocol_type> q(
        protocol, static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);
    results_type r = impl_.get_service().resolve(
        impl_.get_implementation(), q, ec);
    boost::asio::detail::throw_error(ec, "resolve");
    return r;
  }

  /// Perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns A range object representing the list of endpoint entries. An
   * empty range is returned if an error occurs. A successful call to this
   * function is guaranteed to return a non-empty range.
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  results_type resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      resolver_base::flags resolve_flags, boost::system::error_code& ec)
  {
    basic_resolver_query<protocol_type> q(
        protocol, static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);
    return impl_.get_service().resolve(impl_.get_implementation(), q, ec);
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use overload with separate host and service parameters.)
  /// Asynchronously perform forward resolution of a query to a list of entries.
  /**
   * This function is used to asynchronously resolve a query into a list of
   * endpoint entries. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param q A query object that determines what endpoints will be returned.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the resolve completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, results_type) @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveToken,
      void (boost::system::error_code, results_type))
  async_resolve(const query& q,
      BOOST_ASIO_MOVE_ARG(ResolveToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return boost::asio::async_initiate<ResolveToken,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), token, q);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Asynchronously perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the resolve completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, results_type) @endcode
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveToken,
      void (boost::system::error_code, results_type))
  async_resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service,
      BOOST_ASIO_MOVE_ARG(ResolveToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_resolve(host, service, resolver_base::flags(),
        BOOST_ASIO_MOVE_CAST(ResolveToken)(token));
  }

  /// Asynchronously perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the resolve completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, results_type) @endcode
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveToken,
      void (boost::system::error_code, results_type))
  async_resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service,
      resolver_base::flags resolve_flags,
      BOOST_ASIO_MOVE_ARG(ResolveToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    basic_resolver_query<protocol_type> q(static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);

    return boost::asio::async_initiate<ResolveToken,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), token, q);
  }

  /// Asynchronously perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the resolve completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, results_type) @endcode
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveToken,
      void (boost::system::error_code, results_type))
  async_resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      BOOST_ASIO_MOVE_ARG(ResolveToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_resolve(protocol, host, service, resolver_base::flags(),
        BOOST_ASIO_MOVE_CAST(ResolveToken)(token));
  }

  /// Asynchronously perform forward resolution of a query to a list of entries.
  /**
   * This function is used to resolve host and service names into a list of
   * endpoint entries. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param protocol A protocol object, normally representing either the IPv4 or
   * IPv6 version of an internet protocol.
   *
   * @param host A string identifying a location. May be a descriptive name or
   * a numeric address string. If an empty string and the passive flag has been
   * specified, the resolved endpoints are suitable for local service binding.
   * If an empty string and passive is not specified, the resolved endpoints
   * will use the loopback address.
   *
   * @param service A string identifying the requested service. This may be a
   * descriptive name or a numeric string corresponding to a port number. May
   * be an empty string, in which case all resolved endpoints will have a port
   * number of 0.
   *
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the resolve completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, results_type) @endcode
   *
   * @note On POSIX systems, host names may be locally defined in the file
   * <tt>/etc/hosts</tt>. On Windows, host names may be defined in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\hosts</tt>. Remote host name
   * resolution is performed using DNS. Operating systems may use additional
   * locations when resolving host names (such as NETBIOS names on Windows).
   *
   * On POSIX systems, service names are typically defined in the file
   * <tt>/etc/services</tt>. On Windows, service names may be found in the file
   * <tt>c:\\windows\\system32\\drivers\\etc\\services</tt>. Operating systems
   * may use additional locations when resolving service names.
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveToken,
      void (boost::system::error_code, results_type))
  async_resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      resolver_base::flags resolve_flags,
      BOOST_ASIO_MOVE_ARG(ResolveToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    basic_resolver_query<protocol_type> q(
        protocol, static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);

    return boost::asio::async_initiate<ResolveToken,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), token, q);
  }

  /// Perform reverse resolution of an endpoint to a list of entries.
  /**
   * This function is used to resolve an endpoint into a list of endpoint
   * entries.
   *
   * @param e An endpoint object that determines what endpoints will be
   * returned.
   *
   * @returns A range object representing the list of endpoint entries. A
   * successful call to this function is guaranteed to return a non-empty
   * range.
   *
   * @throws boost::system::system_error Thrown on failure.
   */
  results_type resolve(const endpoint_type& e)
  {
    boost::system::error_code ec;
    results_type i = impl_.get_service().resolve(
        impl_.get_implementation(), e, ec);
    boost::asio::detail::throw_error(ec, "resolve");
    return i;
  }

  /// Perform reverse resolution of an endpoint to a list of entries.
  /**
   * This function is used to resolve an endpoint into a list of endpoint
   * entries.
   *
   * @param e An endpoint object that determines what endpoints will be
   * returned.
   *
   * @param ec Set to indicate what error occurred, if any.
   *
   * @returns A range object representing the list of endpoint entries. An
   * empty range is returned if an error occurs. A successful call to this
   * function is guaranteed to return a non-empty range.
   */
  results_type resolve(const endpoint_type& e, boost::system::error_code& ec)
  {
    return impl_.get_service().resolve(impl_.get_implementation(), e, ec);
  }

  /// Asynchronously perform reverse resolution of an endpoint to a list of
  /// entries.
  /**
   * This function is used to asynchronously resolve an endpoint into a list of
   * endpoint entries. It is an initiating function for an @ref
   * asynchronous_operation, and always returns immediately.
   *
   * @param e An endpoint object that determines what endpoints will be
   * returned.
   *
   * @param token The @ref completion_token that will be used to produce a
   * completion handler, which will be called when the resolve completes.
   * Potential completion tokens include @ref use_future, @ref use_awaitable,
   * @ref yield_context, or a function object with the correct completion
   * signature. The function signature of the completion handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the completion handler will not be invoked from within this function.
   * On immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   *
   * @par Completion Signature
   * @code void(boost::system::error_code, results_type) @endcode
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveToken
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveToken,
      void (boost::system::error_code, results_type))
  async_resolve(const endpoint_type& e,
      BOOST_ASIO_MOVE_ARG(ResolveToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return boost::asio::async_initiate<ResolveToken,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), token, e);
  }

private:
  // Disallow copying and assignment.
  basic_resolver(const basic_resolver&) BOOST_ASIO_DELETED;
  basic_resolver& operator=(const basic_resolver&) BOOST_ASIO_DELETED;

  class initiate_async_resolve
  {
  public:
    typedef Executor executor_type;

    explicit initiate_async_resolve(basic_resolver* self)
      : self_(self)
    {
    }

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return self_->get_executor();
    }

    template <typename ResolveHandler, typename Query>
    void operator()(BOOST_ASIO_MOVE_ARG(ResolveHandler) handler,
        const Query& q) const
    {
      // If you get an error on the following line it means that your handler
      // does not meet the documented type requirements for a ResolveHandler.
      BOOST_ASIO_RESOLVE_HANDLER_CHECK(
          ResolveHandler, handler, results_type) type_check;

      boost::asio::detail::non_const_lvalue<ResolveHandler> handler2(handler);
      self_->impl_.get_service().async_resolve(
          self_->impl_.get_implementation(), q,
          handler2.value, self_->impl_.get_executor());
    }

  private:
    basic_resolver* self_;
  };

# if defined(BOOST_ASIO_WINDOWS_RUNTIME)
  boost::asio::detail::io_object_impl<
    boost::asio::detail::winrt_resolver_service<InternetProtocol>,
    Executor> impl_;
# else
  boost::asio::detail::io_object_impl<
    boost::asio::detail::resolver_service<InternetProtocol>,
    Executor> impl_;
# endif
};

} // namespace ip
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IP_BASIC_RESOLVER_HPP

/* basic_resolver.hpp
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
*/