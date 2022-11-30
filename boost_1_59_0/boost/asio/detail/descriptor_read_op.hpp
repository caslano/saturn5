//
// detail/descriptor_read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP
#define BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/descriptor_ops.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_work.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence>
class descriptor_read_op_base : public reactor_op
{
public:
  descriptor_read_op_base(const boost::system::error_code& success_ec,
      int descriptor, const MutableBufferSequence& buffers,
      func_type complete_func)
    : reactor_op(success_ec,
        &descriptor_read_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }

  static status do_perform(reactor_op* base)
  {
    descriptor_read_op_base* o(static_cast<descriptor_read_op_base*>(base));

    typedef buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs_type;

    status result;
    if (bufs_type::is_single_buffer)
    {
      result = descriptor_ops::non_blocking_read1(o->descriptor_,
          bufs_type::first(o->buffers_).data(),
          bufs_type::first(o->buffers_).size(),
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }
    else
    {
      bufs_type bufs(o->buffers_);
      result = descriptor_ops::non_blocking_read(o->descriptor_,
          bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_)
        ? done : not_done;
    }

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_read",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  int descriptor_;
  MutableBufferSequence buffers_;
};

template <typename MutableBufferSequence, typename Handler, typename IoExecutor>
class descriptor_read_op
  : public descriptor_read_op_base<MutableBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(descriptor_read_op);

  descriptor_read_op(const boost::system::error_code& success_ec,
      int descriptor, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : descriptor_read_op_base<MutableBufferSequence>(success_ec,
        descriptor, buffers, &descriptor_read_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    descriptor_read_op* o(static_cast<descriptor_read_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Take ownership of the operation's outstanding work.
    handler_work<Handler, IoExecutor> w(
        BOOST_ASIO_MOVE_CAST2(handler_work<Handler, IoExecutor>)(
          o->work_));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->bytes_transferred_);
    p.h = boost::asio::detail::addressof(handler.handler_);
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN((handler.arg1_, handler.arg2_));
      w.complete(handler, handler.handler_);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  handler_work<Handler, IoExecutor> work_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP

/* descriptor_read_op.hpp
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
*/