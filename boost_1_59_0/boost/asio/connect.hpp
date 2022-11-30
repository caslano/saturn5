//
// connect.hpp
// ~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type = 0);

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
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type = 0);

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
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type = 0);

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
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type = 0);
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
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type = 0);

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
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type = 0);

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
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type = 0);

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
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type = 0);
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
 * is successfully established. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param endpoints A sequence of endpoints.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the connect completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
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
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, typename Protocol::endpoint) @endcode
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
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the socket's @c async_connect operation.
 */
template <typename Protocol, typename Executor, typename EndpointSequence,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectToken,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints,
    BOOST_ASIO_MOVE_ARG(RangeConnectToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type = 0);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use range overload.) Asynchronously establishes a socket
/// connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the connect completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
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
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, Iterator) @endcode
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the socket's @c async_connect operation.
 */
template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type = 0);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately.
 *
 * @param s The socket to be connected. If the socket is already open, it will
 * be closed.
 *
 * @param begin An iterator pointing to the start of a sequence of endpoints.
 *
 * @param end An iterator pointing to the end of a sequence of endpoints.
 *
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the connect completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
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
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, Iterator) @endcode
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
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the socket's @c async_connect operation.
 */
template <typename Protocol, typename Executor, typename Iterator,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin, Iterator end,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor));

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately.
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
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the connect completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
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
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, typename Protocol::endpoint) @endcode
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
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the socket's @c async_connect operation.
 */
template <typename Protocol, typename Executor,
    typename EndpointSequence, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      typename Protocol::endpoint)) RangeConnectToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(RangeConnectToken,
    void (boost::system::error_code, typename Protocol::endpoint))
async_connect(basic_socket<Protocol, Executor>& s,
    const EndpointSequence& endpoints, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(RangeConnectToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<is_endpoint_sequence<
        EndpointSequence>::value>::type = 0);

#if !defined(BOOST_ASIO_NO_DEPRECATED)
/// (Deprecated: Use range overload.) Asynchronously establishes a socket
/// connection by trying each endpoint in a sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately.
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
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the connect completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
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
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, Iterator) @endcode
 *
 * @note This overload assumes that a default constructed object of type @c
 * Iterator represents the end of the sequence. This is a valid assumption for
 * iterator types such as @c boost::asio::ip::tcp::resolver::iterator.
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the socket's @c async_connect operation.
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token
      BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor),
    typename constraint<!is_endpoint_sequence<Iterator>::value>::type = 0);
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

/// Asynchronously establishes a socket connection by trying each endpoint in a
/// sequence.
/**
 * This function attempts to connect a socket to one of a sequence of
 * endpoints. It does this by repeated calls to the socket's @c async_connect
 * member function, once for each endpoint in the sequence, until a connection
 * is successfully established. It is an initiating function for an @ref
 * asynchronous_operation, and always returns immediately.
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
 * @param token The @ref completion_token that will be used to produce a
 * completion handler, which will be called when the connect completes.
 * Potential completion tokens include @ref use_future, @ref use_awaitable,
 * @ref yield_context, or a function object with the correct completion
 * signature. The function signature of the completion handler must be:
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
 * not, the completion handler will not be invoked from within this function.
 * On immediate completion, invocation of the handler will be performed in a
 * manner equivalent to using boost::asio::post().
 *
 * @par Completion Signature
 * @code void(boost::system::error_code, Iterator) @endcode
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
 *
 * @par Per-Operation Cancellation
 * This asynchronous operation supports cancellation for the following
 * boost::asio::cancellation_type values:
 *
 * @li @c cancellation_type::terminal
 *
 * @li @c cancellation_type::partial
 *
 * if they are also supported by the socket's @c async_connect operation.
 */
template <typename Protocol, typename Executor,
    typename Iterator, typename ConnectCondition,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code,
      Iterator)) IteratorConnectToken
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(IteratorConnectToken,
    void (boost::system::error_code, Iterator))
async_connect(basic_socket<Protocol, Executor>& s, Iterator begin,
    Iterator end, ConnectCondition connect_condition,
    BOOST_ASIO_MOVE_ARG(IteratorConnectToken) token
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