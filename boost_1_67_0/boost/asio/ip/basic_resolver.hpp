//
// ip/basic_resolver.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_type_requirements.hpp>
#include <boost/asio/detail/io_object_impl.hpp>
#include <boost/asio/detail/non_const_lvalue.hpp>
#include <boost/asio/detail/string_view.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/executor.hpp>
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
template <typename InternetProtocol, typename Executor = executor>
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
    : impl_(ex)
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
      typename enable_if<
        is_convertible<ExecutionContext&, execution_context&>::value
      >::type* = 0)
    : impl_(context)
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
   * endpoint entries.
   *
   * @param q A query object that determines what endpoints will be returned.
   *
   * @param handler The handler to be called when the resolve operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveHandler,
      void (boost::system::error_code, results_type))
  async_resolve(const query& q,
      BOOST_ASIO_MOVE_ARG(ResolveHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return boost::asio::async_initiate<ResolveHandler,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), handler, q);
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
   * @param handler The handler to be called when the resolve operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
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
        results_type)) ResolveHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveHandler,
      void (boost::system::error_code, results_type))
  async_resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service,
      BOOST_ASIO_MOVE_ARG(ResolveHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_resolve(host, service, resolver_base::flags(),
        BOOST_ASIO_MOVE_CAST(ResolveHandler)(handler));
  }

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
   * @param resolve_flags A set of flags that determine how name resolution
   * should be performed. The default flags are suitable for communication with
   * remote hosts. See the @ref resolver_base documentation for the set of
   * available flags.
   *
   * @param handler The handler to be called when the resolve operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
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
        results_type)) ResolveHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveHandler,
      void (boost::system::error_code, results_type))
  async_resolve(BOOST_ASIO_STRING_VIEW_PARAM host,
      BOOST_ASIO_STRING_VIEW_PARAM service,
      resolver_base::flags resolve_flags,
      BOOST_ASIO_MOVE_ARG(ResolveHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    basic_resolver_query<protocol_type> q(static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);

    return boost::asio::async_initiate<ResolveHandler,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), handler, q);
  }

  /// Asynchronously perform forward resolution of a query to a list of entries.
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
   * @param handler The handler to be called when the resolve operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
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
        results_type)) ResolveHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveHandler,
      void (boost::system::error_code, results_type))
  async_resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      BOOST_ASIO_MOVE_ARG(ResolveHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return async_resolve(protocol, host, service, resolver_base::flags(),
        BOOST_ASIO_MOVE_CAST(ResolveHandler)(handler));
  }

  /// Asynchronously perform forward resolution of a query to a list of entries.
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
   * @param handler The handler to be called when the resolve operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
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
        results_type)) ResolveHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveHandler,
      void (boost::system::error_code, results_type))
  async_resolve(const protocol_type& protocol,
      BOOST_ASIO_STRING_VIEW_PARAM host, BOOST_ASIO_STRING_VIEW_PARAM service,
      resolver_base::flags resolve_flags,
      BOOST_ASIO_MOVE_ARG(ResolveHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    basic_resolver_query<protocol_type> q(
        protocol, static_cast<std::string>(host),
        static_cast<std::string>(service), resolve_flags);

    return boost::asio::async_initiate<ResolveHandler,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), handler, q);
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
   * endpoint entries.
   *
   * @param e An endpoint object that determines what endpoints will be
   * returned.
   *
   * @param handler The handler to be called when the resolve operation
   * completes. Copies will be made of the handler as required. The function
   * signature of the handler must be:
   * @code void handler(
   *   const boost::system::error_code& error, // Result of operation.
   *   resolver::results_type results // Resolved endpoints as a range.
   * ); @endcode
   * Regardless of whether the asynchronous operation completes immediately or
   * not, the handler will not be invoked from within this function. On
   * immediate completion, invocation of the handler will be performed in a
   * manner equivalent to using boost::asio::post().
   *
   * A successful resolve operation is guaranteed to pass a non-empty range to
   * the handler.
   */
  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
        results_type)) ResolveHandler
          BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(executor_type)>
  BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ResolveHandler,
      void (boost::system::error_code, results_type))
  async_resolve(const endpoint_type& e,
      BOOST_ASIO_MOVE_ARG(ResolveHandler) handler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(executor_type))
  {
    return boost::asio::async_initiate<ResolveHandler,
      void (boost::system::error_code, results_type)>(
        initiate_async_resolve(this), handler, e);
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
          self_->impl_.get_implementation(), q, handler2.value,
          self_->impl_.get_implementation_executor());
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