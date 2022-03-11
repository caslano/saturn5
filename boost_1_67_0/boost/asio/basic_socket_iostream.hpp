//
// basic_socket_iostream.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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