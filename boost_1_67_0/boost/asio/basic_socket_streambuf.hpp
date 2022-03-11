//
// basic_socket_streambuf.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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