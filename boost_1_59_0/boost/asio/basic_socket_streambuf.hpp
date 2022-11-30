//
// basic_socket_streambuf.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BASIC_SOCKET_STREAMBUF_HPP
#define BOOST_ASIO_BASIC_SOCKET_STREAMBUF_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_NO_IOSTREAM)

#include <streambuf>
#include <vector>
#include <boost/asio/basic_socket.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/throw_error.hpp>
#include <boost/asio/io_context.hpp>

#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
# include <boost/asio/detail/deadline_timer_service.hpp>
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
# include <boost/asio/steady_timer.hpp>
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)

#if !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

# include <boost/asio/detail/variadic_templates.hpp>

// A macro that should expand to:
//   template <typename T1, ..., typename Tn>
//   basic_socket_streambuf* connect(T1 x1, ..., Tn xn)
//   {
//     init_buffers();
//     typedef typename Protocol::resolver resolver_type;
//     resolver_type resolver(socket().get_executor());
//     connect_to_endpoints(
//         resolver.resolve(x1, ..., xn, ec_));
//     return !ec_ ? this : 0;
//   }
// This macro should only persist within this file.

# define BOOST_ASIO_PRIVATE_CONNECT_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  basic_socket_streambuf* connect(BOOST_ASIO_VARIADIC_BYVAL_PARAMS(n)) \
  { \
    init_buffers(); \
    typedef typename Protocol::resolver resolver_type; \
    resolver_type resolver(socket().get_executor()); \
    connect_to_endpoints( \
        resolver.resolve(BOOST_ASIO_VARIADIC_BYVAL_ARGS(n), ec_)); \
    return !ec_ ? this : 0; \
  } \
  /**/

#endif // !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// A separate base class is used to ensure that the io_context member is
// initialised prior to the basic_socket_streambuf's basic_socket base class.
class socket_streambuf_io_context
{
protected:
  socket_streambuf_io_context(io_context* ctx)
    : default_io_context_(ctx)
  {
  }

  shared_ptr<io_context> default_io_context_;
};

// A separate base class is used to ensure that the dynamically allocated
// buffers are constructed prior to the basic_socket_streambuf's basic_socket
// base class. This makes moving the socket is the last potentially throwing
// step in the streambuf's move constructor, giving the constructor a strong
// exception safety guarantee.
class socket_streambuf_buffers
{
protected:
  socket_streambuf_buffers()
    : get_buffer_(buffer_size),
      put_buffer_(buffer_size)
  {
  }

  enum { buffer_size = 512 };
  std::vector<char> get_buffer_;
  std::vector<char> put_buffer_;
};

} // namespace detail

#if !defined(BOOST_ASIO_BASIC_SOCKET_STREAMBUF_FWD_DECL)
#define BOOST_ASIO_BASIC_SOCKET_STREAMBUF_FWD_DECL

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
class basic_socket_streambuf;

#endif // !defined(BOOST_ASIO_BASIC_SOCKET_STREAMBUF_FWD_DECL)

/// Iostream streambuf for a socket.
#if defined(GENERATING_DOCUMENTATION)
template <typename Protocol,
    typename Clock = chrono::steady_clock,
    typename WaitTraits = wait_traits<Clock> >
#else // defined(GENERATING_DOCUMENTATION)
template <typename Protocol, typename Clock, typename WaitTraits>
#endif // defined(GENERATING_DOCUMENTATION)
class basic_socket_streambuf
  : public std::streambuf,
    private detail::socket_streambuf_io_context,
    private detail::socket_streambuf_buffers,
#if defined(BOOST_ASIO_NO_DEPRECATED) || defined(GENERATING_DOCUMENTATION)
    private basic_socket<Protocol>
#else // defined(BOOST_ASIO_NO_DEPRECATED) || defined(GENERATING_DOCUMENTATION)
    public basic_socket<Protocol>
#endif // defined(BOOST_ASIO_NO_DEPRECATED) || defined(GENERATING_DOCUMENTATION)
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

  /// Construct a basic_socket_streambuf without establishing a connection.
  basic_socket_streambuf()
    : detail::socket_streambuf_io_context(new io_context),
      basic_socket<Protocol>(*default_io_context_),
      expiry_time_(max_expiry_time())
  {
    init_buffers();
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Construct a basic_socket_streambuf from the supplied socket.
  explicit basic_socket_streambuf(basic_stream_socket<protocol_type> s)
    : detail::socket_streambuf_io_context(0),
      basic_socket<Protocol>(std::move(s)),
      expiry_time_(max_expiry_time())
  {
    init_buffers();
  }

  /// Move-construct a basic_socket_streambuf from another.
  basic_socket_streambuf(basic_socket_streambuf&& other)
    : detail::socket_streambuf_io_context(other),
      basic_socket<Protocol>(std::move(other.socket())),
      ec_(other.ec_),
      expiry_time_(other.expiry_time_)
  {
    get_buffer_.swap(other.get_buffer_);
    put_buffer_.swap(other.put_buffer_);
    setg(other.eback(), other.gptr(), other.egptr());
    setp(other.pptr(), other.epptr());
    other.ec_ = boost::system::error_code();
    other.expiry_time_ = max_expiry_time();
    other.init_buffers();
  }

  /// Move-assign a basic_socket_streambuf from another.
  basic_socket_streambuf& operator=(basic_socket_streambuf&& other)
  {
    this->close();
    socket() = std::move(other.socket());
    detail::socket_streambuf_io_context::operator=(other);
    ec_ = other.ec_;
    expiry_time_ = other.expiry_time_;
    get_buffer_.swap(other.get_buffer_);
    put_buffer_.swap(other.put_buffer_);
    setg(other.eback(), other.gptr(), other.egptr());
    setp(other.pptr(), other.epptr());
    other.ec_ = boost::system::error_code();
    other.expiry_time_ = max_expiry_time();
    other.put_buffer_.resize(buffer_size);
    other.init_buffers();
    return *this;
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor flushes buffered data.
  virtual ~basic_socket_streambuf()
  {
    if (pptr() != pbase())
      overflow(traits_type::eof());
  }

  /// Establish a connection.
  /**
   * This function establishes a connection to the specified endpoint.
   *
   * @return \c this if a connection was successfully established, a null
   * pointer otherwise.
   */
  basic_socket_streambuf* connect(const endpoint_type& endpoint)
  {
    init_buffers();
    ec_ = boost::system::error_code();
    this->connect_to_endpoints(&endpoint, &endpoint + 1);
    return !ec_ ? this : 0;
  }

#if defined(GENERATING_DOCUMENTATION)
  /// Establish a connection.
  /**
   * This function automatically establishes a connection based on the supplied
   * resolver query parameters. The arguments are used to construct a resolver
   * query object.
   *
   * @return \c this if a connection was successfully established, a null
   * pointer otherwise.
   */
  template <typename T1, ..., typename TN>
  basic_socket_streambuf* connect(T1 t1, ..., TN tn);
#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
  template <typename... T>
  basic_socket_streambuf* connect(T... x)
  {
    init_buffers();
    typedef typename Protocol::resolver resolver_type;
    resolver_type resolver(socket().get_executor());
    connect_to_endpoints(resolver.resolve(x..., ec_));
    return !ec_ ? this : 0;
  }
#else
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CONNECT_DEF)
#endif

  /// Close the connection.
  /**
   * @return \c this if a connection was successfully established, a null
   * pointer otherwise.
   */
  basic_socket_streambuf* close()
  {
    sync();
    socket().close(ec_);
    if (!ec_)
      init_buffers();
    return !ec_ ? this : 0;
  }

  /// Get a reference to the underlying socket.
  basic_socket<Protocol>& socket()
  {
    return *this;
  }

  /// Get the last error associated with the stream buffer.
  /**
   * @return An \c error_code corresponding to the last error from the stream
   * buffer.
   */
  const boost::system::error_code& error() const
  {
    return ec_;
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use error().) Get the last error associated with the stream
  /// buffer.
  /**
   * @return An \c error_code corresponding to the last error from the stream
   * buffer.
   */
  const boost::system::error_code& puberror() const
  {
    return error();
  }

  /// (Deprecated: Use expiry().) Get the stream buffer's expiry time as an
  /// absolute time.
  /**
   * @return An absolute time value representing the stream buffer's expiry
   * time.
   */
  time_point expires_at() const
  {
    return expiry_time_;
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

  /// Get the stream buffer's expiry time as an absolute time.
  /**
   * @return An absolute time value representing the stream buffer's expiry
   * time.
   */
  time_point expiry() const
  {
    return expiry_time_;
  }

  /// Set the stream buffer's expiry time as an absolute time.
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
    expiry_time_ = expiry_time;
  }

  /// Set the stream buffer's expiry time relative to now.
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
    expiry_time_ = traits_helper::add(traits_helper::now(), expiry_time);
  }

#if !defined(BOOST_ASIO_NO_DEPRECATED)
  /// (Deprecated: Use expiry().) Get the stream buffer's expiry time relative
  /// to now.
  /**
   * @return A relative time value representing the stream buffer's expiry time.
   */
  duration expires_from_now() const
  {
    return traits_helper::subtract(expires_at(), traits_helper::now());
  }

  /// (Deprecated: Use expires_after().) Set the stream buffer's expiry time
  /// relative to now.
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
    expiry_time_ = traits_helper::add(traits_helper::now(), expiry_time);
  }
#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

protected:
  int_type underflow()
  {
#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
    ec_ = boost::asio::error::operation_not_supported;
    return traits_type::eof();
#else // defined(BOOST_ASIO_WINDOWS_RUNTIME)
    if (gptr() != egptr())
      return traits_type::eof();

    for (;;)
    {
      // Check if we are past the expiry time.
      if (traits_helper::less_than(expiry_time_, traits_helper::now()))
      {
        ec_ = boost::asio::error::timed_out;
        return traits_type::eof();
      }

      // Try to complete the operation without blocking.
      if (!socket().native_non_blocking())
        socket().native_non_blocking(true, ec_);
      detail::buffer_sequence_adapter<mutable_buffer, mutable_buffer>
        bufs(boost::asio::buffer(get_buffer_) + putback_max);
      detail::signed_size_type bytes = detail::socket_ops::recv(
          socket().native_handle(), bufs.buffers(), bufs.count(), 0, ec_);

      // Check if operation succeeded.
      if (bytes > 0)
      {
        setg(&get_buffer_[0], &get_buffer_[0] + putback_max,
            &get_buffer_[0] + putback_max + bytes);
        return traits_type::to_int_type(*gptr());
      }

      // Check for EOF.
      if (bytes == 0)
      {
        ec_ = boost::asio::error::eof;
        return traits_type::eof();
      }

      // Operation failed.
      if (ec_ != boost::asio::error::would_block
          && ec_ != boost::asio::error::try_again)
        return traits_type::eof();

      // Wait for socket to become ready.
      if (detail::socket_ops::poll_read(
            socket().native_handle(), 0, timeout(), ec_) < 0)
        return traits_type::eof();
    }
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)
  }

  int_type overflow(int_type c)
  {
#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
    ec_ = boost::asio::error::operation_not_supported;
    return traits_type::eof();
#else // defined(BOOST_ASIO_WINDOWS_RUNTIME)
    char_type ch = traits_type::to_char_type(c);

    // Determine what needs to be sent.
    const_buffer output_buffer;
    if (put_buffer_.empty())
    {
      if (traits_type::eq_int_type(c, traits_type::eof()))
        return traits_type::not_eof(c); // Nothing to do.
      output_buffer = boost::asio::buffer(&ch, sizeof(char_type));
    }
    else
    {
      output_buffer = boost::asio::buffer(pbase(),
          (pptr() - pbase()) * sizeof(char_type));
    }

    while (output_buffer.size() > 0)
    {
      // Check if we are past the expiry time.
      if (traits_helper::less_than(expiry_time_, traits_helper::now()))
      {
        ec_ = boost::asio::error::timed_out;
        return traits_type::eof();
      }

      // Try to complete the operation without blocking.
      if (!socket().native_non_blocking())
        socket().native_non_blocking(true, ec_);
      detail::buffer_sequence_adapter<
        const_buffer, const_buffer> bufs(output_buffer);
      detail::signed_size_type bytes = detail::socket_ops::send(
          socket().native_handle(), bufs.buffers(), bufs.count(), 0, ec_);

      // Check if operation succeeded.
      if (bytes > 0)
      {
        output_buffer += static_cast<std::size_t>(bytes);
        continue;
      }

      // Operation failed.
      if (ec_ != boost::asio::error::would_block
          && ec_ != boost::asio::error::try_again)
        return traits_type::eof();

      // Wait for socket to become ready.
      if (detail::socket_ops::poll_write(
            socket().native_handle(), 0, timeout(), ec_) < 0)
        return traits_type::eof();
    }

    if (!put_buffer_.empty())
    {
      setp(&put_buffer_[0], &put_buffer_[0] + put_buffer_.size());

      // If the new character is eof then our work here is done.
      if (traits_type::eq_int_type(c, traits_type::eof()))
        return traits_type::not_eof(c);

      // Add the new character to the output buffer.
      *pptr() = ch;
      pbump(1);
    }

    return c;
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)
  }

  int sync()
  {
    return overflow(traits_type::eof());
  }

  std::streambuf* setbuf(char_type* s, std::streamsize n)
  {
    if (pptr() == pbase() && s == 0 && n == 0)
    {
      put_buffer_.clear();
      setp(0, 0);
      sync();
      return this;
    }

    return 0;
  }

private:
  // Disallow copying and assignment.
  basic_socket_streambuf(const basic_socket_streambuf&) BOOST_ASIO_DELETED;
  basic_socket_streambuf& operator=(
      const basic_socket_streambuf&) BOOST_ASIO_DELETED;

  void init_buffers()
  {
    setg(&get_buffer_[0],
        &get_buffer_[0] + putback_max,
        &get_buffer_[0] + putback_max);

    if (put_buffer_.empty())
      setp(0, 0);
    else
      setp(&put_buffer_[0], &put_buffer_[0] + put_buffer_.size());
  }

  int timeout() const
  {
    int64_t msec = traits_helper::to_posix_duration(
        traits_helper::subtract(expiry_time_,
          traits_helper::now())).total_milliseconds();
    if (msec > (std::numeric_limits<int>::max)())
      msec = (std::numeric_limits<int>::max)();
    else if (msec < 0)
      msec = 0;
    return static_cast<int>(msec);
  }

  template <typename EndpointSequence>
  void connect_to_endpoints(const EndpointSequence& endpoints)
  {
    this->connect_to_endpoints(endpoints.begin(), endpoints.end());
  }

  template <typename EndpointIterator>
  void connect_to_endpoints(EndpointIterator begin, EndpointIterator end)
  {
#if defined(BOOST_ASIO_WINDOWS_RUNTIME)
    ec_ = boost::asio::error::operation_not_supported;
#else // defined(BOOST_ASIO_WINDOWS_RUNTIME)
    if (ec_)
      return;

    ec_ = boost::asio::error::not_found;
    for (EndpointIterator i = begin; i != end; ++i)
    {
      // Check if we are past the expiry time.
      if (traits_helper::less_than(expiry_time_, traits_helper::now()))
      {
        ec_ = boost::asio::error::timed_out;
        return;
      }

      // Close and reopen the socket.
      typename Protocol::endpoint ep(*i);
      socket().close(ec_);
      socket().open(ep.protocol(), ec_);
      if (ec_)
        continue;

      // Try to complete the operation without blocking.
      if (!socket().native_non_blocking())
        socket().native_non_blocking(true, ec_);
      detail::socket_ops::connect(socket().native_handle(),
          ep.data(), ep.size(), ec_);

      // Check if operation succeeded.
      if (!ec_)
        return;

      // Operation failed.
      if (ec_ != boost::asio::error::in_progress
          && ec_ != boost::asio::error::would_block)
        continue;

      // Wait for socket to become ready.
      if (detail::socket_ops::poll_connect(
            socket().native_handle(), timeout(), ec_) < 0)
        continue;

      // Get the error code from the connect operation.
      int connect_error = 0;
      size_t connect_error_len = sizeof(connect_error);
      if (detail::socket_ops::getsockopt(socket().native_handle(), 0,
            SOL_SOCKET, SO_ERROR, &connect_error, &connect_error_len, ec_)
          == detail::socket_error_retval)
        return;

      // Check the result of the connect operation.
      ec_ = boost::system::error_code(connect_error,
          boost::asio::error::get_system_category());
      if (!ec_)
        return;
    }
#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)
  }

  // Helper function to get the maximum expiry time.
  static time_point max_expiry_time()
  {
#if defined(BOOST_ASIO_HAS_BOOST_DATE_TIME) \
  && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
    return boost::posix_time::pos_infin;
#else // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
      // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
    return (time_point::max)();
#endif // defined(BOOST_ASIO_HAS_BOOST_DATE_TIME)
       // && defined(BOOST_ASIO_USE_BOOST_DATE_TIME_FOR_SOCKET_IOSTREAM)
  }

  enum { putback_max = 8 };
  boost::system::error_code ec_;
  time_point expiry_time_;
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#if !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
# undef BOOST_ASIO_PRIVATE_CONNECT_DEF
#endif // !defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#endif // !defined(BOOST_ASIO_NO_IOSTREAM)

#endif // BOOST_ASIO_BASIC_SOCKET_STREAMBUF_HPP

/* basic_socket_streambuf.hpp
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
*/