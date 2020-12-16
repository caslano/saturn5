//
// detail/descriptor_write_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  descriptor_write_op_base(int descriptor,
      const ConstBufferSequence& buffers, func_type complete_func)
    : reactor_op(&descriptor_write_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }

  static status do_perform(reactor_op* base)
  {
    descriptor_write_op_base* o(static_cast<descriptor_write_op_base*>(base));

    buffer_sequence_adapter<boost::asio::const_buffer,
        ConstBufferSequence> bufs(o->buffers_);

    status result = descriptor_ops::non_blocking_write(o->descriptor_,
        bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_)
      ? done : not_done;

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

  descriptor_write_op(int descriptor, const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : descriptor_write_op_base<ConstBufferSequence>(
        descriptor, buffers, &descriptor_write_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    descriptor_write_op* o(static_cast<descriptor_write_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

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
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // !defined(BOOST_ASIO_WINDOWS) && !defined(__CYGWIN__)

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_WRITE_OP_HPP

/* descriptor_write_op.hpp
42GAAmJSIbvXSrvlMpaFsJzVYysEDquXOk2761yAB/7z1Oy07gV2zAycmBnkxczAiZnB/DET4nBT7TLGBsUaaCDbSNj460rMKuMbqimOh9LGZoWWQ3TidaExfLklPGSkKD1RmJdTrIsk8V5uKn7mMKGy1/kA46AfwUoQfmwML/nbGEsf3AwfxejuKMFL76asNGNifHHCJvDHpiwCY5XF+CqEgaesRhqWvDGZ4vQ7ag4BBy4b5Ba4bIq37TENAoyumRg9sQnUY1Mmga4ZGF0z8JTVCLpm4kkDm10D4XYNI2R0Bdgc244SYEMGA5gY/bUJGMCmTAIGMDAMYOApqxEYwMSTBjYNACLXAOnYTkymtkASyi1ZlAAoEifTNiZqeLS4Z2Jxd08GBolZSvHXU9LZ45KwRy6LP7l8Dgt7uSR0dUhobZKJE7ukq5d231zeZR29Em92SEevxM9c0tVLe1Uu77KOXomTuaTWK2gtzigEFHuGxqhAI11yuoj/ehYYIPzpou6FCxaHbBkOiKp1Gp3JALSSRUtTgAZ1ulzJphcaIK1dE2jCZtCOQy01GLvFheilScRTTTN20247dqXZOrPpLWlVWNej37EDyNxNjn9NEmTm4WqLnN2M7UpjJtok4ghTKc7VmoJIOw2hWgpSXWbKi+K/i5O/aYwESFVDuhQFhWapBz+lk7bUBFyyKAuNtNYBKFUBaWiQpBclf1FvkgxjcqpVE09ToLvJoxcuhb1kPaKrs/jwHr5c0wUUvdcJdVIQzy2NoVEKUpUC27jaJEjgMzhdSGYXDCQXLk3ZJHxunq42a7ONBgy4fnwAvx7ZH76ctHasd0XytoLLV1t5LHbAXcsHR8awy8HcSFPQtNWFH2XDb5SsLuDFjPg3NiyqaudBbQYzd63FJMptk3CrjV9QbsFXh+CUhkz/YITJ25q4isxiMK08QdpO3WkncNsZW7tsfHQgVNgh0b5DQYWulfi9D/yT/V2RldnfFdEIHYNTpjgtrW8GhdC6FbRS/+DIyuQHR3QKt60A0l8fCdPRfnywf6A3+zGwkIimlEnBiw3CBA2nQPItrgjoE2p4itQkimhyaHxhDwzYhQRqQwKvA0W/Th195j+0lE3m5YPNNLc8/PHssKxNoqxNmWWHm/oH7B0WpW3OajqvsFs0UxCPTM098WR/iMflUUEei0q6Vg+Dg3hN/6Iu/B97BVKhK4SJcTyBE4RvZgLFToHk4i78n+ZfnORfbORfrPP39YT/JCWQjIsgleSam0TZn3WPXv7tQBf6hlwJLOBWgw66HHrfNQRieWHnwaGFPVE6uSgHlP0GeRZOzsYITVUyyegOw5D14fECsjjfHh+yPz4+pD/rrZNhwxqmDUeaD4yP9fWOoEt43g2Pze20FjfToyjTQQYjdJCYFY6NrMJ8R0UVi0MFFuMUHCxgZsOGJawFrgDz1xU4LYGCZeKn1U2BrcFgjgKzMKidK+hUX4CTvEklFxOGhscHYaSBeJg1hAoaoPkuXO+Ngj+O9QlIbyamRHxPPMXmPXJNo+sa4GKERvq7wAmVvkACjNaxX5jYCx6WQvSuGlU9EeChhdJ0IQsQ5iOMxbYLf5Nf49DJuL6gCxR8P8qFq8dxzdAfa4nFTWxNaf1zB11A8RNFUbIevvmJZNipJI2/PbV6mkTraTqIaFA9gGkaN9e6kI7bxkhVIqjrRw4jjVJd4SPQy3rHBvtGB5CCqbphDFzI7CnnyCBqWXRye8aVhDrYHOwQNVDuqebIIGp1oOMbDfNI0a/OUoxjFW/GIdzmZolv8NnCqsNgkCIKXj8ePQJsYHS6kiVQRRaa5cfGe8fXRoHaJlHOoXTZ0dVmU8C6JaA=
*/