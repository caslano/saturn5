//
// ssl/detail/io.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_SSL_DETAIL_IO_HPP
#define BOOST_ASIO_SSL_DETAIL_IO_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/ssl/detail/engine.hpp>
#include <boost/asio/ssl/detail/stream_core.hpp>
#include <boost/asio/write.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace ssl {
namespace detail {

template <typename Stream, typename Operation>
std::size_t io(Stream& next_layer, stream_core& core,
    const Operation& op, boost::system::error_code& ec)
{
  boost::system::error_code io_ec;
  std::size_t bytes_transferred = 0;
  do switch (op(core.engine_, ec, bytes_transferred))
  {
  case engine::want_input_and_retry:

    // If the input buffer is empty then we need to read some more data from
    // the underlying transport.
    if (core.input_.size() == 0)
    {
      core.input_ = boost::asio::buffer(core.input_buffer_,
          next_layer.read_some(core.input_buffer_, io_ec));
      if (!ec)
        ec = io_ec;
    }

    // Pass the new input data to the engine.
    core.input_ = core.engine_.put_input(core.input_);

    // Try the operation again.
    continue;

  case engine::want_output_and_retry:

    // Get output data from the engine and write it to the underlying
    // transport.
    boost::asio::write(next_layer,
        core.engine_.get_output(core.output_buffer_), io_ec);
    if (!ec)
      ec = io_ec;

    // Try the operation again.
    continue;

  case engine::want_output:

    // Get output data from the engine and write it to the underlying
    // transport.
    boost::asio::write(next_layer,
        core.engine_.get_output(core.output_buffer_), io_ec);
    if (!ec)
      ec = io_ec;

    // Operation is complete. Return result to caller.
    core.engine_.map_error_code(ec);
    return bytes_transferred;

  default:

    // Operation is complete. Return result to caller.
    core.engine_.map_error_code(ec);
    return bytes_transferred;

  } while (!ec);

  // Operation failed. Return result to caller.
  core.engine_.map_error_code(ec);
  return 0;
}

template <typename Stream, typename Operation, typename Handler>
class io_op
{
public:
  io_op(Stream& next_layer, stream_core& core,
      const Operation& op, Handler& handler)
    : next_layer_(next_layer),
      core_(core),
      op_(op),
      start_(0),
      want_(engine::want_nothing),
      bytes_transferred_(0),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  io_op(const io_op& other)
    : next_layer_(other.next_layer_),
      core_(other.core_),
      op_(other.op_),
      start_(other.start_),
      want_(other.want_),
      ec_(other.ec_),
      bytes_transferred_(other.bytes_transferred_),
      handler_(other.handler_)
  {
  }

  io_op(io_op&& other)
    : next_layer_(other.next_layer_),
      core_(other.core_),
      op_(BOOST_ASIO_MOVE_CAST(Operation)(other.op_)),
      start_(other.start_),
      want_(other.want_),
      ec_(other.ec_),
      bytes_transferred_(other.bytes_transferred_),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()(boost::system::error_code ec,
      std::size_t bytes_transferred = ~std::size_t(0), int start = 0)
  {
    switch (start_ = start)
    {
    case 1: // Called after at least one async operation.
      do
      {
        switch (want_ = op_(core_.engine_, ec_, bytes_transferred_))
        {
        case engine::want_input_and_retry:

          // If the input buffer already has data in it we can pass it to the
          // engine and then retry the operation immediately.
          if (core_.input_.size() != 0)
          {
            core_.input_ = core_.engine_.put_input(core_.input_);
            continue;
          }

          // The engine wants more data to be read from input. However, we
          // cannot allow more than one read operation at a time on the
          // underlying transport. The pending_read_ timer's expiry is set to
          // pos_infin if a read is in progress, and neg_infin otherwise.
          if (core_.expiry(core_.pending_read_) == core_.neg_infin())
          {
            // Prevent other read operations from being started.
            core_.pending_read_.expires_at(core_.pos_infin());

            // Start reading some data from the underlying transport.
            next_layer_.async_read_some(
                boost::asio::buffer(core_.input_buffer_),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }
          else
          {
            // Wait until the current read operation completes.
            core_.pending_read_.async_wait(BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }

          // Yield control until asynchronous operation completes. Control
          // resumes at the "default:" label below.
          return;

        case engine::want_output_and_retry:
        case engine::want_output:

          // The engine wants some data to be written to the output. However, we
          // cannot allow more than one write operation at a time on the
          // underlying transport. The pending_write_ timer's expiry is set to
          // pos_infin if a write is in progress, and neg_infin otherwise.
          if (core_.expiry(core_.pending_write_) == core_.neg_infin())
          {
            // Prevent other write operations from being started.
            core_.pending_write_.expires_at(core_.pos_infin());

            // Start writing all the data to the underlying transport.
            boost::asio::async_write(next_layer_,
                core_.engine_.get_output(core_.output_buffer_),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }
          else
          {
            // Wait until the current write operation completes.
            core_.pending_write_.async_wait(BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }

          // Yield control until asynchronous operation completes. Control
          // resumes at the "default:" label below.
          return;

        default:

          // The SSL operation is done and we can invoke the handler, but we
          // have to keep in mind that this function might be being called from
          // the async operation's initiating function. In this case we're not
          // allowed to call the handler directly. Instead, issue a zero-sized
          // read so the handler runs "as-if" posted using io_context::post().
          if (start)
          {
            next_layer_.async_read_some(
                boost::asio::buffer(core_.input_buffer_, 0),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));

            // Yield control until asynchronous operation completes. Control
            // resumes at the "default:" label below.
            return;
          }
          else
          {
            // Continue on to run handler directly.
            break;
          }
        }

        default:
        if (bytes_transferred == ~std::size_t(0))
          bytes_transferred = 0; // Timer cancellation, no data transferred.
        else if (!ec_)
          ec_ = ec;

        switch (want_)
        {
        case engine::want_input_and_retry:

          // Add received data to the engine's input.
          core_.input_ = boost::asio::buffer(
              core_.input_buffer_, bytes_transferred);
          core_.input_ = core_.engine_.put_input(core_.input_);

          // Release any waiting read operations.
          core_.pending_read_.expires_at(core_.neg_infin());

          // Try the operation again.
          continue;

        case engine::want_output_and_retry:

          // Release any waiting write operations.
          core_.pending_write_.expires_at(core_.neg_infin());

          // Try the operation again.
          continue;

        case engine::want_output:

          // Release any waiting write operations.
          core_.pending_write_.expires_at(core_.neg_infin());

          // Fall through to call handler.

        default:

          // Pass the result to the handler.
          op_.call_handler(handler_,
              core_.engine_.map_error_code(ec_),
              ec_ ? 0 : bytes_transferred_);

          // Our work here is done.
          return;
        }
      } while (!ec_);

      // Operation failed. Pass the result to the handler.
      op_.call_handler(handler_, core_.engine_.map_error_code(ec_), 0);
    }
  }

//private:
  Stream& next_layer_;
  stream_core& core_;
  Operation op_;
  int start_;
  engine::want want_;
  boost::system::error_code ec_;
  std::size_t bytes_transferred_;
  Handler handler_;
};

template <typename Stream, typename Operation, typename Handler>
inline void* asio_handler_allocate(std::size_t size,
    io_op<Stream, Operation, Handler>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Stream, typename Operation, typename Handler>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Stream, typename Operation, typename Handler>
inline bool asio_handler_is_continuation(
    io_op<Stream, Operation, Handler>* this_handler)
{
  return this_handler->start_ == 0 ? true
    : boost_asio_handler_cont_helpers::is_continuation(this_handler->handler_);
}

template <typename Function, typename Stream,
    typename Operation, typename Handler>
inline void asio_handler_invoke(Function& function,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Stream,
    typename Operation, typename Handler>
inline void asio_handler_invoke(const Function& function,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Stream, typename Operation, typename Handler>
inline void async_io(Stream& next_layer, stream_core& core,
    const Operation& op, Handler& handler)
{
  io_op<Stream, Operation, Handler>(
    next_layer, core, op, handler)(
      boost::system::error_code(), 0, 1);
}

} // namespace detail
} // namespace ssl

template <typename Stream, typename Operation,
    typename Handler, typename Allocator>
struct associated_allocator<
    ssl::detail::io_op<Stream, Operation, Handler>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(const ssl::detail::io_op<Stream, Operation, Handler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

template <typename Stream, typename Operation,
    typename Handler, typename Executor>
struct associated_executor<
    ssl::detail::io_op<Stream, Operation, Handler>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(const ssl::detail::io_op<Stream, Operation, Handler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_IO_HPP

/* io.hpp
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
*/