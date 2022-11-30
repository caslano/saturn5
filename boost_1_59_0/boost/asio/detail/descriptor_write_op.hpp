//
// detail/descriptor_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP
#define BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP

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

template <typename ConstBufferSequence>
class descriptor_write_op_base : public reactor_op
{
public:
  descriptor_write_op_base(const boost::system::error_code& success_ec,
      int descriptor, const ConstBufferSequence& buffers,
      func_type complete_func)
    : reactor_op(success_ec,
        &descriptor_write_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }

  static status do_perform(reactor_op* base)
  {
    descriptor_write_op_base* o(static_cast<descriptor_write_op_base*>(base));

    typedef buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs_type;

    status result;
    if (bufs_type::is_single_buffer)
    {
      result = descriptor_ops::non_blocking_write1(o->descriptor_,
          bufs_type::first(o->buffers_).data(),
          bufs_type::first(o->buffers_).size(),
          o->ec_, o->bytes_transferred_) ? done : not_done;
    }
    else
    {
      bufs_type bufs(o->buffers_);
      result = descriptor_ops::non_blocking_write(o->descriptor_,
          bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_)
        ? done : not_done;
    }

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_write",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  int descriptor_;
  ConstBufferSequence buffers_;
};

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class descriptor_write_op
  : public descriptor_write_op_base<ConstBufferSequence>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(descriptor_write_op);

  descriptor_write_op(const boost::system::error_code& success_ec,
      int descriptor, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : descriptor_write_op_base<ConstBufferSequence>(success_ec,
        descriptor, buffers, &descriptor_write_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      work_(handler_, io_ex)
  {
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    descriptor_write_op* o(static_cast<descriptor_write_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP

/* descriptor_write_op.hpp
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
*/