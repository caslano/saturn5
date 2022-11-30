//
// ssl/detail/io.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#include <boost/asio/detail/base_from_cancellation_state.hpp>
#include <boost/asio/detail/handler_tracking.hpp>
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
  : public boost::asio::detail::base_from_cancellation_state<Handler>
{
public:
  io_op(Stream& next_layer, stream_core& core,
      const Operation& op, Handler& handler)
    : boost::asio::detail::base_from_cancellation_state<Handler>(handler),
      next_layer_(next_layer),
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
    : boost::asio::detail::base_from_cancellation_state<Handler>(other),
      next_layer_(other.next_layer_),
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
    : boost::asio::detail::base_from_cancellation_state<Handler>(
        BOOST_ASIO_MOVE_CAST(
          boost::asio::detail::base_from_cancellation_state<Handler>)(
            other)),
      next_layer_(other.next_layer_),
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

            BOOST_ASIO_HANDLER_LOCATION((
                  __FILE__, __LINE__, Operation::tracking_name()));

            // Start reading some data from the underlying transport.
            next_layer_.async_read_some(
                boost::asio::buffer(core_.input_buffer_),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }
          else
          {
            BOOST_ASIO_HANDLER_LOCATION((
                  __FILE__, __LINE__, Operation::tracking_name()));

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

            BOOST_ASIO_HANDLER_LOCATION((
                  __FILE__, __LINE__, Operation::tracking_name()));

            // Start writing all the data to the underlying transport.
            boost::asio::async_write(next_layer_,
                core_.engine_.get_output(core_.output_buffer_),
                BOOST_ASIO_MOVE_CAST(io_op)(*this));
          }
          else
          {
            BOOST_ASIO_HANDLER_LOCATION((
                  __FILE__, __LINE__, Operation::tracking_name()));

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
            BOOST_ASIO_HANDLER_LOCATION((
                  __FILE__, __LINE__, Operation::tracking_name()));

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

          // Check for cancellation before continuing.
          if (this->cancelled() != cancellation_type::none)
          {
            ec_ = boost::asio::error::operation_aborted;
            break;
          }

          // Try the operation again.
          continue;

        case engine::want_output_and_retry:

          // Release any waiting write operations.
          core_.pending_write_.expires_at(core_.neg_infin());

          // Check for cancellation before continuing.
          if (this->cancelled() != cancellation_type::none)
          {
            ec_ = boost::asio::error::operation_aborted;
            break;
          }

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
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    io_op<Stream, Operation, Handler>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Stream, typename Operation, typename Handler>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Stream,
    typename Operation, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    io_op<Stream, Operation, Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename Stream, typename Operation,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    ssl::detail::io_op<Stream, Operation, Handler>,
    DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const ssl::detail::io_op<Stream, Operation, Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_SSL_DETAIL_IO_HPP

/* io.hpp
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
*/