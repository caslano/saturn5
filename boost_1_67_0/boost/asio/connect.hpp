//
// connect.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_CONNECT_HPP
#define BOOST_ASIO_CONNECT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

namespace detail
{
  char (&has_iterator_helper(...))[2];

  template <typename T>
  char has_iterator_helper(T*, typename T::iterator* = 0);

  template <typename T>
  struct has_iterator_typedef
  {
    enum { value = (sizeof((has_iterator_helper)((T*)(0))) == 1) };
  };
} // namespace detail

/// Type trait used to determine whether a type is an endpoint sequence that can
/// be used with with @c connect and @c async_connect.
template <typename T>
struct is_endpoint_sequence
{
#if defined(GENERATING_DOCUMENTATION)
  /// The value member is true if the type may be used as an endpoint sequence.
  static const bool value;
#else
  enum
  {
    value = detail::has_iterator_typedef<T>::value
  };
#endif
};

/**
 * @defgroup connect boost::asio::connect
 *
 * @brief The @c connect function is a composed operation that establishes a
 * socket connection by trying each endpoint in a sequence.
 */
/*@{*/

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @returns The successfully connected endpoint.
 *
 * @throws boost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is boost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 * boost::asio::connect(s, r.resolve(q)); @endcode
 */
template <typename Protocol, typename Executor, typename EndpointSequence>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type* = 0);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to boost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, the successfully connected endpoint. Otherwise, a
 * default-constructed endpoint.
 *
 * @par Example
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 * boost::system::error_code ec;
 * boost::asio::connect(s, r.resolve(q), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * } @endcode
 */
template <typename Protocol, typename Executor, typename EndpointSequence>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, boost::system::error_code& ec,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type* = 0);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use range overload.) Establishes a socket connection by trying
/// each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws boost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is boost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 */
template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type* = 0);

/// (Deprecated: Use range overload.) Establishes a socket connection by trying
/// each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to boost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 */
template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, boost::system::error_code& ec,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type* = 0);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @returns An iterator denoting the successfully connected endpoint.
 *
 * @throws boost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is boost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::results_type e = r.resolve(q);
 * tcp::socket s(my_context);
 * boost::asio::connect(s, e.begin(), e.end()); @endcode
 */
template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, Iterator end);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to boost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @par Example
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::results_type e = r.resolve(q);
 * tcp::socket s(my_context);
 * boost::system::error_code ec;
 * boost::asio::connect(s, e.begin(), e.end(), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * } @endcode
 */
template <typename Protocol, typename Executor, typename Iterator>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, Iterator end, boost::system::error_code& ec);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @returns The successfully connected endpoint.
 *
 * @throws boost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is boost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   bool operator()(
 *       const boost::system::error_code& ec,
 *       const::tcp::endpoint& next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next << std::endl;
 *     return true;
 *   }
 * }; @endcode
 * It would be used with the boost::asio::connect function as follows:
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 * tcp::endpoint e = boost::asio::connect(s,
 *     r.resolve(q), my_connect_condition());
 * std::cout << "Connected to: " << e << std::endl; @endcode
 */
template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type* = 0);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to boost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, the successfully connected endpoint. Otherwise, a
 * default-constructed endpoint.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   bool operator()(
 *       const boost::system::error_code& ec,
 *       const::tcp::endpoint& next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next << std::endl;
 *     return true;
 *   }
 * }; @endcode
 * It would be used with the boost::asio::connect function as follows:
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 * boost::system::error_code ec;
 * tcp::endpoint e = boost::asio::connect(s,
 *     r.resolve(q), my_connect_condition(), ec);
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   std::cout << "Connected to: " << e << std::endl;
 * } @endcode
 */
template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition>
typename Protocol::endpoint connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    boost::system::error_code& ec,
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type* = 0);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use range overload.) Establishes a socket connection by trying
/// each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @throws boost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is boost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, ConnectCondition connect_condition,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type* = 0);

/// (Deprecated: Use range overload.) Establishes a socket connection by trying
/// each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to boost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    ConnectCondition connect_condition, boost::system::error_code& ec,
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type* = 0);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @returns An iterator denoting the successfully connected endpoint.
 *
 * @throws boost::system::system_error Thrown on failure. If the sequence is
 * empty, the associated @c error_code is boost::asio::error::not_found.
 * Otherwise, contains the error from the last connection attempt.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   bool operator()(
 *       const boost::system::error_code& ec,
 *       const::tcp::endpoint& next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next << std::endl;
 *     return true;
 *   }
 * }; @endcode
 * It would be used with the boost::asio::connect function as follows:
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::results_type e = r.resolve(q);
 * tcp::socket s(my_context);
 * tcp::resolver::results_type::iterator i = boost::asio::connect(
 *     s, e.begin(), e.end(), my_connect_condition());
 * std::cout << "Connected to: " << i->endpoint() << std::endl; @endcode
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition);

/// Establishes a socket connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c connect member
 * function, once for each endpoint in the sequence, until a connection is
 * successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @param ec Set to indicate what error occurred, if any. If the sequence is
 * empty, set to boost::asio::error::not_found. Otherwise, contains the error
 * from the last connection attempt.
 *
 * @returns On success, an iterator denoting the successfully connected
 * endpoint. Otherwise, the end iterator.
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   bool operator()(
 *       const boost::system::error_code& ec,
 *       const::tcp::endpoint& next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next << std::endl;
 *     return true;
 *   }
 * }; @endcode
 * It would be used with the boost::asio::connect function as follows:
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::resolver::results_type e = r.resolve(q);
 * tcp::socket s(my_context);
 * boost::system::error_code ec;
 * tcp::resolver::results_type::iterator i = boost::asio::connect(
 *     s, e.begin(), e.end(), my_connect_condition());
 * if (ec)
 * {
 *   // An error occurred.
 * }
 * else
 * {
 *   std::cout << "Connected to: " << i->endpoint() << std::endl;
 * } @endcode
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition>
Iterator connect(basic_socket<Protocol, Executor>& s,
    Iterator begin, Iterator end, ConnectCondition connect_condition,
    boost::system::error_code& ec);

/*@}*/

/**
 * @defgroup async_connect boost::asio::async_connect
 *
 * @brief The @c async_connect function is a composed asynchronous operation
 * that establishes a socket connection by trying each endpoint in a sequence.
 */
/*@{*/

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // boost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const boost::system::error_code& error,
 *
 *   // On success, the successfully connected endpoint.
 *   // Otherwise, a default-constructed endpoint.
 *   const typename Protocol::endpoint& endpoint
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const boost::system::error_code& ec,
 *     tcp::resolver::results_type results)
 * {
 *   if (!ec)
 *   {
 *     boost::asio::async_connect(s, results, connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const boost::system::error_code& ec,
 *     const tcp::endpoint& endpoint)
 * {
 *   // ...
 * } @endcode
 */
template <typename Protocol, typename Executor, typename EndpointSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectHandler,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints,
    BOOST_ASIO_MOVE_ARG(RangeConnectHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type* = 0);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use range overload.) Asynchronously establishes a socket
/// connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // boost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const boost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 */
template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type* = 0);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // boost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const boost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * @code std::vector<tcp::endpoint> endpoints = ...;
 * tcp::socket s(my_context);
 * boost::asio::async_connect(s,
 *     endpoints.begin(), endpoints.end(),
 *     connect_handler);
 *
 * // ...
 *
 * void connect_handler(
 *     const boost::system::error_code& ec,
 *     std::vector<tcp::endpoint>::iterator i)
 * {
 *   // ...
 * } @endcode
 */
template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin, Iterator end,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor));

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // boost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const boost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   bool operator()(
 *       const boost::system::error_code& ec,
 *       const::tcp::endpoint& next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next << std::endl;
 *     return true;
 *   }
 * }; @endcode
 * It would be used with the boost::asio::connect function as follows:
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const boost::system::error_code& ec,
 *     tcp::resolver::results_type results)
 * {
 *   if (!ec)
 *   {
 *     boost::asio::async_connect(s, results,
 *         my_connect_condition(),
 *         connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const boost::system::error_code& ec,
 *     const tcp::endpoint& endpoint)
 * {
 *   if (ec)
 *   {
 *     // An error occurred.
 *   }
 *   else
 *   {
 *     std::cout << "Connected to: " << endpoint << std::endl;
 *   }
 * } @endcode
 */
template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectHandler,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(RangeConnectHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<is_endpoint_sequence<
        EndpointSequence>::value>::type* = 0);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use range overload.) Asynchronously establishes a socket
/// connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // boost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const boost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename enable_if<!is_endpoint_sequence<Iterator>::value>::type* = 0);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param connect_condition A function object that is called prior to each
 * connection attempt. The signature of the function object must be:
 * @code bool connect_condition(
 *     const boost::system::error_code& ec,
 *     const typename Protocol::endpoint& next); @endcode
 * The @c ec parameter contains the result from the most recent connect
 * operation. Before the first connection attempt, @c ec is always set to
 * indicate success. The @c next parameter is the next endpoint to be tried.
 * The function object should return true if the next endpoint should be tried,
 * and false if it should be skipped.
 *
 * @param handler The handler to be called when the connect operation
 * completes. Copies will be made of the handler as required. The function
 * signature of the handler must be:
 * @code void handler(
 *   // Result of operation. if the sequence is empty, set to
 *   // boost::asio::error::not_found. Otherwise, contains the
 *   // error from the last connection attempt.
 *   const boost::system::error_code& error,
 *
 *   // On success, an iterator denoting the successfully
 *   // connected endpoint. Otherwise, the end iterator.
 *   Iterator iterator
 * ); @endcode
 * Regardless of whether the asynchronous operation completes immediately or
 * not, the handler will not be invoked from within this function. On
 * immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Example
 * The following connect condition function object can be used to output
 * information about the individual connection attempts:
 * @code struct my_connect_condition
 * {
 *   bool operator()(
 *       const boost::system::error_code& ec,
 *       const::tcp::endpoint& next)
 *   {
 *     if (ec) std::cout << "Error: " << ec.message() << std::endl;
 *     std::cout << "Trying: " << next << std::endl;
 *     return true;
 *   }
 * }; @endcode
 * It would be used with the boost::asio::connect function as follows:
 * @code tcp::resolver r(my_context);
 * tcp::resolver::query q("host", "service");
 * tcp::socket s(my_context);
 *
 * // ...
 *
 * r.async_resolve(q, resolve_handler);
 *
 * // ...
 *
 * void resolve_handler(
 *     const boost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (!ec)
 *   {
 *     tcp::resolver::iterator end;
 *     boost::asio::async_connect(s, i, end,
 *         my_connect_condition(),
 *         connect_handler);
 *   }
 * }
 *
 * // ...
 *
 * void connect_handler(
 *     const boost::system::error_code& ec,
 *     tcp::resolver::iterator i)
 * {
 *   if (ec)
 *   {
 *     // An error occurred.
 *   }
 *   else
 *   {
 *     std::cout << "Connected to: " << i->endpoint() << std::endl;
 *   }
 * } @endcode
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectHandler
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectHandler,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectHandler) handler
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor));

/*@}*/

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/impl/connect.hpp>

#endif

/* connect.hpp
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
*/