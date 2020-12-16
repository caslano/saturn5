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
qlI3vnnyJdIq8JF6KBt1xmTs6TGHZOeFKJdLQqjjhwMAYA/9XvxQb7hGDbz4wIB7Bmtx6NbKNG3KIQZbj5tDxWpxey7tCdLuknF/5PqaA69MOamV9UCU5fAesLqX9BU3XpQUmyue5nQrZ9NbrMTjvFL8x9JPdewukSMdbCA6cvH5uQXJ5SWZIAzLb5/CDbmoBPS2DNereX4mbJitazivLv2o6KSAQtXn8Hor2rGx0AmmGho7tMEvxJb6wEu4sLq3wqij8x5m4hmNuFWn82xnMZOMBKUgfom28WXv54Fa3ZlUrNhK5QTddIQAwECU8pGsfMeCC3JdYbqvGgtU2JuV29CHnhMIeT7yqA6ewM0TvTPHNfGsTbvLbLO/+AAABkwA/E5s/eBV2IHzvrN7Xq/i0ynkY1hb6oYFCmjTWT/MZZtn3Z1b/eTtJ+qCyQSs9hg/a7v3rYaq5v2EikOxrZGEXcXpXRg+4fslzt79QuGnGligMBl0/tjbJ33d8axm17WiE41sTillvnWiIPRMMOI/VNKJXctItpegTve4WdaNQcMXC7iMtPBme4qRRQIZTYdTYcGVH+9ozkTQjD2amTDhO2TNklDXIFPQ82b3aBl1e34oepbdJf20BjVn3eNSFJxsV6W7ykYCx6pGDlmdPSQcafn2aUGVAsc1T5/BzEQjXcuz4ccMALoo77Z/dA+IP5dghtoL6T2+dDQY/ngPycH6bw/nTkajikcCxP4abfMW7uduhZl6eNzadSvuXUeDvTsWKViQPzk31WCMj+OuM9myHyDvlWqj823eO23ubx8AAH3L8yHRP3mWhs0TiSLX68csWBNaNhKN840hFO1BkZnWW+0nQ2U/ANT/2vM9qoltCLJt8vcAaB3TK96SPSn01BWrGXqxG/wFAwBM6J3Ud7I/22vQ35gbU9RJHLPfiIAX32sozX/SeajGsKLbWTdufOkBoNK8HhgjzruX+HT2keqpmKZOMz3Nmo58kvcilqeNrkZIc01qLVVX9TwgMXsq43ng8gP+FRkx06Q4Y5JuY5r1Ps5Gv1JiEU02WP1+1/g7+qDI2+2pZmWTp6LtpTzNpuiT7blLR23evzChUCiRd6ZewPdcxSRmToMJROee+9oh3Nub3HA2geIivYQbzZknA7m/ow8ZQp8HaAuUV1n5WjPSpTmvPr9UFtkmYzOYaRRnGU0q6lo4MJgkUMcFDwqsbx4Qfff4OvOM9LeXN3NLeq8jJcZpydiqZt+FfXa1DE/qbp7zzS69FaxSwPPIumA2Co9DR1blmP7rfaVRQZbV2uXh+rLM9XIAbdRNJO0zS2Lkhn45kpOjrbTH59CuP8yp/139tsm/Rtxh93nK3ZzKfKWvWOhoTcMXc1V2plAvD8GJdxHnPx3nZGY/NFa5IJLBJmn5acEwgAXXl03drIFWMIq1pFnyBrhY9q6oz7sF9uRX+h1E6PemnjebUcI0iJWMk8Hl+ZvgghRsjbju0EXfpjrI/PYoW1ab9UGWePQ79Sq7lE+RsXYWYLCebX6RIsHg/+n4sxEx/mBs4sIsOothYZqjL0x7ihz5rUV37YliyWXz1VngxaG7l+nzOCJZYZhUgcr264e9dT6a2epLjnWOdvSPy5NPtebQH5VPTmhO//TSdR9a6yZd2r/EPyepkrfpq0q/nXE1BSDwJ/r/hFuV5/G5KobR6jXDRPFp9zTViz2pCjhFlefmwgxCLlkWDku2MUD8seKn/OD7XNmfyi1fCatrNGAp7vBHd55Y3CesHvFCRETRe488lVhTy56DltX6B6R7FP5Ef2qE/llfNHpSP2RVCZviRd24cMnRVugTXQcjNTM1sSzlIVsVNx8tXJdVNk4=
*/