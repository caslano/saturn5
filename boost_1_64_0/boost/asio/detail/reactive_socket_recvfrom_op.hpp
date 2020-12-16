//
// detail/reactive_socket_recvfrom_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>
#include <boost/asio/detail/socket_ops.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename MutableBufferSequence, typename Endpoint>
class reactive_socket_recvfrom_op_base : public reactor_op
{
public:
  reactive_socket_recvfrom_op_base(socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, func_type complete_func)
    : reactor_op(&reactive_socket_recvfrom_op_base::do_perform, complete_func),
      socket_(socket),
      protocol_type_(protocol_type),
      buffers_(buffers),
      sender_endpoint_(endpoint),
      flags_(flags)
  {
  }

  static status do_perform(reactor_op* base)
  {
    reactive_socket_recvfrom_op_base* o(
        static_cast<reactive_socket_recvfrom_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    std::size_t addr_len = o->sender_endpoint_.capacity();
    status result = socket_ops::non_blocking_recvfrom(o->socket_,
        bufs.buffers(), bufs.count(), o->flags_,
        o->sender_endpoint_.data(), &addr_len,
        o->ec_, o->bytes_transferred_) ? done : not_done;

    if (result && !o->ec_)
      o->sender_endpoint_.resize(addr_len);

    BOOST_ASIO_HANDLER_REACTOR_OPERATION((*o, "non_blocking_recvfrom",
          o->ec_, o->bytes_transferred_));

    return result;
  }

private:
  socket_type socket_;
  int protocol_type_;
  MutableBufferSequence buffers_;
  Endpoint& sender_endpoint_;
  socket_base::message_flags flags_;
};

template <typename MutableBufferSequence, typename Endpoint,
    typename Handler, typename IoExecutor>
class reactive_socket_recvfrom_op :
  public reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_socket_recvfrom_op);

  reactive_socket_recvfrom_op(socket_type socket, int protocol_type,
      const MutableBufferSequence& buffers, Endpoint& endpoint,
      socket_base::message_flags flags, Handler& handler,
      const IoExecutor& io_ex)
    : reactive_socket_recvfrom_op_base<MutableBufferSequence, Endpoint>(
        socket, protocol_type, buffers, endpoint, flags,
        &reactive_socket_recvfrom_op::do_complete),
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
    reactive_socket_recvfrom_op* o(
        static_cast<reactive_socket_recvfrom_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_SOCKET_RECVFROM_OP_HPP

/* reactive_socket_recvfrom_op.hpp
HpPvPO/1dBwpdkITX/exD9G3aZgSatvfrO/3mMyPfSDQW3WuVTnq3Aen41Sx2OZDCZtuXh2HJfn8w9PZSGg8bxnYdSdpg3Du5i193s467Ua2kn30MZ/lKR993LOhyOVs3ATT788nQ95eXs2Xs39PV6ya13q6zQbpZ2i9k62y45BPiV4cmllcVGbC47DOFMafwfOM9LNCHedDnC06qjF/x/y00usNDuMcpY1Pdhq2jf9MpJve6Dhm58as3hgbI3aeYiYPZj1iu6eBveTnK8b5o7vaKB0XCPP2SV4Y6BWaWW8Ru0iz3FTulY2afR8vDlinS9/b+Z5XYd4FL7wRQ+5BvETsil/YZmyAs22Vnq8w7UA2RcMXm+ZLfY52AvsFU6wy5fbdXBbw7hTrl3s6dYZ8rm2su/OZrvSY/L75gqejXUD6rgpYHpwzdLXHZVx2TaTTejueE/WYnL91ra9PtTD2ui7S5Vvn9QHr5stJv8HXTYHjDtdIL8Z4dJw83+Ea8OWNMTcndKPHyBF8f6uvd5v8FLGbPYZFRAjvFp+dmLVbpH9F62aHZK3aIf2roT7F46iv+XrT9Lo8Byq6HJrc4jbhG4qZtqinmnP+bw30bmdstq3Ht2lmdGrEkJfbCzZijhS0i8egf1Prak7wW1pXc4Lf1rqaE/yO0XGpcQW3VVOavhvrRYWiZ+4wzJxz0zPUO9y7UMV9p9ZV3N/Tuor7LtZVMNx+3q31BpfRPUrT3wC/T7o50F2lxs1d+sx9L/6hr7ux0I8KvbSQrwsoihVx/DjUuXOiZ+7V7IR2w84L3hfpMu//E2bRPrafKt3b96b0xer8pZ+zzseu0wcdSjS9j/fHDAln/ouQSyJ5XhN8tDifWp4l9iBYPTMbUswYa7RaW2HT+kvHVvBPQOgPWb3lPsLy3ais84WHS+z5mZQieu7X4ObHQY33NGKOEzqKiWwfdhrfq2DryG+13j/f29v6iMfKvUO8sdWcx407UQNeGVo8xywzJfZowDhgDvf3mpX6hg4fclteiT/mc4kWaX7c54iW+9UnNEsv5uC9cWKHOwXYT38M9dkc7pORXhkaHlhSMRFzgcDPf1J22h9/1rrkiPL7lGbDnp+J/yXktIFY/PF0wBEv75tTjCo0nnk21Cu9i5eCPRcxM3kH9nzEzAd15P0FxfQY9cVA5/rHeXspYFIHcYdpxGP//C2ycT4g/vcE50g4jn8EPKiTZPPP2EaSgbz8K7ZBMvi74r9Dnq6f5LP/BLaoo8ReTrHZHMdaG8QsrqscztqRrfjsFSEL3tFXhly8Qf5aJ+BBveZ51NgGdVt8um7CRr9X6wWc6iSeXT9iqOfgG0QcdR18w4ijvqOd3Yg59Q5u7lRrXNEpnRtr3VVyZpsEbBVDSsNrfKadSPy1PhfnIN5NQ85h85ypZmGlt3OmgU3YB2wecERPdXELzaap7O6OVG3LlZ30LSN9NqV9q1hXSeM2+w1rsqGVPmy3tbZLvTDw5TbaDhl1+/Z8JkkB39bjw1E5bhdyeRGIbx9yxG/9t4PmVFE5zTtq3b0AzHbSzFV+Zm/SzFV8TsvOSWYK+EhOyy6aq28yu4a6u3wqq07Cx7tFNuYdwvO7p5h7nNP25tDGvWvM90jwVeqd2DPmuqzIZq+UTVAf9k7ZcDxU5/YJefz+UVz7JuzC/m+/hI1Nzj6Gz4h4+l10c7ChPb+PlJ6ZaYZS4Of3T9rMpnzPSjOdJWo7Dojt4vcXtgfGtvE7jHKZHdrCUe7e1IjHZXJwbKOTTz4/ZA02lU67Wm8Ui6ZlHchbIvvhqN69NbbR7QTZvC22ifqEt4c29A6zfw6NGdoM5r0xR7vBfE7M0T5w+vo=
*/