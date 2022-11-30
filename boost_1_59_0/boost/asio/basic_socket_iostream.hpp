//
// basic_socket_iostream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SOCKET_IOSTREAM_HPP
#define BOOST_ASIO_BASIC_SOCKET_IOSTREAM_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <istream>
#include <ostream>
#include <boost/asio/basic_socket_streambuf.hpp>

#if !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

# include <boost/asio/detail/variadic_templates.hpp>

// A macro that should expand to:
//   template <typename T1, ..., typename Tn>
//   explicit basic_socket_iostream(T1 x1, ..., Tn xn)
//     : std::basic_iostream<char>(
//         &this->detail::socket_iostream_base<
//           Protocol, Clock, WaitTraits>::streambuf_)
//   {
//     if (rdbuf()->connect(x1, ..., xn) == 0)
//       this->setstate(std::ios_base::failbit);
//   }
// This macro should only persist within this file.

# define BOOST_ASIO_PRIVATE_CTR_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  explicit basic_socket_iostream(BOOST_ASIO_VARIADIC_BYVAL_PARAMS(n)) \
    : std::basic_iostream<char>( \
        &this->detail::socket_iostream_base< \
          Protocol, Clock, WaitTraits>::streambuf_) \
  { \
    this->setf(std::ios_base::unitbuf); \
    if (rdbuf()->connect(BOOST_ASIO_VARIADIC_BYVAL_ARGS(n)) == 0) \
      this->setstate(std::ios_base::failbit); \
  } \
  /**/

// A macro that should expand to:
//   template <typename T1, ..., typename Tn>
//   void connect(T1 x1, ..., Tn xn)
//   {
//     if (rdbuf()->connect(x1, ..., xn) == 0)
//       this->setstate(std::ios_base::failbit);
//   }
// This macro should only persist within this file.

# define BOOST_ASIO_PRIVATE_CONNECT_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void connect(BOOST_ASIO_VARIADIC_BYVAL_PARAMS(n)) \
  { \
    if (rdbuf()->connect(BOOST_ASIO_VARIADIC_BYVAL_ARGS(n)) == 0) \
      this->setstate(std::ios_base::failbit); \
  } \
  /**/

#endif // !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// A separate base class is used to ensure that the streambuf is initialised
// prior to the basic_socket_iostream's basic_iostream base class.
template <typename Protocol, typename Clock, typename WaitTraits>
class socket_iostream_base
{
protected:
  socket_iostream_base()
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  socket_iostream_base(socket_iostream_base&& other)
    : streambuf_(std::move(other.streambuf_))
  {
  }

  socket_iostream_base(basic_stream_socket<Protocol> s)
    : streambuf_(std::move(s))
  {
  }

  socket_iostream_base& operator=(socket_iostream_base&& other)
  {
    streambuf_ = std::move(other.streambuf_);
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  basic_socket_streambuf<Protocol, Clock, WaitTraits> streambuf_;
};

} // namespace detail

#if !defined(BOOST_ASIO_BASIC_SOCKET_IOSTREAM_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_IOSTREAM_FWD_DECL

// Forward declaration with defaulted arguments.
template <typename Protocol,
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
    typename Clock = boost::posix_time::ptime,
    typename WaitTraits = time_traits<Clock> >
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
    typename Clock = chrono::steady_clock,
    typename WaitTraits = wait_traits<Clock> >
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
class basic_socket_iostream;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_IOSTREAM_FWD_DECL)

/// Iostream interface for a socket.
#if defined(GENERATING_DOCUMENTATION)
template <typename Protocol,
    typename Clock = chrono::steady_clock,
    typename WaitTraits = wait_traits<Clock> >
#else // defined(GENERATING_DOCUMENTATION)
template <typename Protocol, typename Clock, typename WaitTraits>
#endif // defined(GENERATING_DOCUMENTATION)
class basic_socket_iostream
  : private detail::socket_iostream_base<Protocol, Clock, WaitTraits>,
    public std::basic_iostream<char>
{
private:
  // These typedefs are intended keep this class's implementation independent
  // of whether it's using Boost.DateClock, Boost.Chrono or std::chrono.
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
  typedef WaitTraits traits_helper;
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
  typedef detail::chrono_time_traits<Clock, WaitTraits> traits_helper;
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)

public:
  /// The protocol type.
  typedef Protocol protocol_type;

  /// The endpoint type.
  typedef typename Protocol::endpoint endpoint_type;

  /// The clock type.
  typedef Clock clock_type;

#if defined(GENERATING_DOCUMENTATION)
  /// (Deprecated: Use time_point.) The time type.
  typedef typename WaitTraits::time_type time_type;

  /// The time type.
  typedef typename WaitTraits::time_point time_point;

  /// (Deprecated: Use duration.) The duration type.
  typedef typename WaitTraits::duration_type duration_type;

  /// The duration type.
  typedef typename WaitTraits::duration duration;
#else
# if !defined(BOOST_ASIO_NO_DEPRECATED)
  typedef typename traits_helper::time_type time_type;
  typedef typename traits_helper::duration_type duration_type;
# endif // !defined(BOOST_ASIO_NO_DEPRECATED)
  typedef typename traits_helper::time_type time_point;
  typedef typename traits_helper::duration_type duration;
#endif

  /// Construct a basic_socket_iostream without establishing a connection.
  basic_socket_iostream()
    : std::basic_iostream<char>(
        &this->detail::socket_iostream_base<
          Protocol, Clock, WaitTraits>::streambuf_)
  {
    this->setf(std::ios_base::unitbuf);
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Construct a basic_socket_iostream from the supplied socket.
  explicit basic_socket_iostream(basic_stream_socket<protocol_type> s)
    : detail::socket_iostream_base<
        Protocol, Clock, WaitTraits>(std::move(s)),
      std::basic_iostream<char>(
        &this->detail::socket_iostream_base<
          Protocol, Clock, WaitTraits>::streambuf_)
  {
    this->setf(std::ios_base::unitbuf);
  }

#if defined(BOOST_ASIO_HAS_STD_IOSTREAM_MOVE) \
  || defined(GENERATING_DOCUMENTATION)
  /// Move-construct a basic_socket_iostream from another.
  basic_socket_iostream(basic_socket_iostream&& other)
    : detail::socket_iostream_base<
        Protocol, Clock, WaitTraits>(std::move(other)),
      std::basic_iostream<char>(std::move(other))
  {
    this->set_rdbuf(&this->detail::socket_iostream_base<
          Protocol, Clock, WaitTraits>::streambuf_);
  }

  /// Move-assign a basic_socket_iostream from another.
  basic_socket_iostream& operator=(basic_socket_iostream&& other)
  {
    std::basic_iostream<char>::operator=(std::move(other));
    detail::socket_iostream_base<
        Protocol, Clock, WaitTraits>::operator=(std::move(other));
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_STD_IOSTREAM_MOVE)
       //   || defined(GENERATING_DOCUMENTATION)
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

#if defined(GENERATING_DOCUMENTATION)
  /// Establish a connection to an endpoint corresponding to a resolver query.
  /**
   * This constructor automatically establishes a connection based on the
   * supplied resolver query parameters. The arguments are used to construct
   * a resolver query object.
   */
  template <typename T1, ..., typename TN>
  explicit basic_socket_iostream(T1 t1, ..., TN tn);
#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename... T>
  explicit basic_socket_iostream(T... x)
    : std::basic_iostream<char>(
        &this->detail::socket_iostream_base<
          Protocol, Clock, WaitTraits>::streambuf_)
  {
    this->setf(std::ios_base::unitbuf);
    if (rdbuf()->connect(x...) == 0)
      this->setstate(std::ios_base::failbit);
  }
#else
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CTR_DEF)
#endif

#if defined(GENERATING_DOCUMENTATION)
  /// Establish a connection to an endpoint corresponding to a resolver query.
  /**
   * This function automatically establishes a connection based on the supplied
   * resolver query parameters. The arguments are used to construct a resolver
   * query object.
   */
  template <typename T1, ..., typename TN>
  void connect(T1 t1, ..., TN tn);
#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename... T>
  void connect(T... x)
  {
    if (rdbuf()->connect(x...) == 0)
      this->setstate(std::ios_base::failbit);
  }
#else
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CONNECT_DEF)
#endif

  /// Close the connection.
  void close()
  {
    if (rdbuf()->close() == 0)
      this->setstate(std::ios_base::failbit);
  }

  /// Return a pointer to the underlying streambuf.
  basic_socket_streambuf<Protocol, Clock, WaitTraits>* rdbuf() const
  {
    return const_cast<basic_socket_streambuf<Protocol, Clock, WaitTraits>*>(
        &this->detail::socket_iostream_base<
          Protocol, Clock, WaitTraits>::streambuf_);
  }

  /// Get a reference to the underlying socket.
  basic_socket<Protocol>& socket()
  {
    return rdbuf()->socket();
  }

  /// Get the last error associated with the stream.
  /**
   * @return An \c error_code corresponding to the last error from the stream.
   *
   * @par Example
   * To print the error associated with a failure to establish a connection:
   * @code tcp::iostream s("www.boost.org", "http");
   * if (!s)
   * {
   *   std::cout << "Error: " << s.error().message() << std::endl;
   * } @endcode
   */
  const boost::system::error_code& error() const
  {
    return rdbuf()->error();
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use expiry().) Get the stream's expiry time as an absolute
  /// time.
  /**
   * @return An absolute time value representing the stream's expiry time.
   */
  time_point expires_at() const
  {
    return rdbuf()->expires_at();
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Get the stream's expiry time as an absolute time.
  /**
   * @return An absolute time value representing the stream's expiry time.
   */
  time_point expiry() const
  {
    return rdbuf()->expiry();
  }

  /// Set the stream's expiry time as an absolute time.
  /**
   * This function sets the expiry time associated with the stream. Stream
   * operations performed after this time (where the operations cannot be
   * completed using the internal buffers) will fail with the error
   * boost::asio::error::operation_aborted.
   *
   * @param expiry_time The expiry time to be used for the stream.
   */
  void expires_at(const time_point& expiry_time)
  {
    rdbuf()->expires_at(expiry_time);
  }

  /// Set the stream's expiry time relative to now.
  /**
   * This function sets the expiry time associated with the stream. Stream
   * operations performed after this time (where the operations cannot be
   * completed using the internal buffers) will fail with the error
   * boost::asio::error::operation_aborted.
   *
   * @param expiry_time The expiry time to be used for the timer.
   */
  void expires_after(const duration& expiry_time)
  {
    rdbuf()->expires_after(expiry_time);
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use expiry().) Get the stream's expiry time relative to now.
  /**
   * @return A relative time value representing the stream's expiry time.
   */
  duration expires_from_now() const
  {
    return rdbuf()->expires_from_now();
  }

  /// (Deprecated: Use expires_after().) Set the stream's expiry time relative
  /// to now.
  /**
   * This function sets the expiry time associated with the stream. Stream
   * operations performed after this time (where the operations cannot be
   * completed using the internal buffers) will fail with the error
   * boost::asio::error::operation_aborted.
   *
   * @param expiry_time The expiry time to be used for the timer.
   */
  void expires_from_now(const duration& expiry_time)
  {
    rdbuf()->expires_from_now(expiry_time);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

private:
  // Disallow copying and assignment.
  basic_socket_iostream(const basic_socket_iostream&) BOOST_ASIO_DELETED;
  basic_socket_iostream& operator=(
      const basic_socket_iostream&) BOOST_ASIO_DELETED;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
# undef BOOST_ASIO_PRIVATE_CTR_DEF
# undef BOOST_ASIO_PRIVATE_CONNECT_DEF
#endif // !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_SOCKET_IOSTREAM_HPP

/* basic_socket_iostream.hpp
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
*/