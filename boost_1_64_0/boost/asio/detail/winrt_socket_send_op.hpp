//
// detail/winrt_socket_send_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP
#define BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#if defined(BOOST_ASIO_WINDOWS_RUNTIME)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/winrt_async_op.hpp>
#include <boost/asio/error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename ConstBufferSequence, typename Handler, typename IoExecutor>
class winrt_socket_send_op :
  public winrt_async_op<unsigned int>
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(winrt_socket_send_op);

  winrt_socket_send_op(const ConstBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : winrt_async_op<unsigned int>(&winrt_socket_send_op::do_complete),
      buffers_(buffers),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code&, std::size_t)
  {
    // Take ownership of the operation object.
    winrt_socket_send_op* o(static_cast<winrt_socket_send_op*>(base));
    ptr p = { boost::asio::detail::addressof(o->handler_), o, o };
    handler_work<Handler, IoExecutor> w(o->handler_, o->io_executor_);

    BOOST_ASIO_HANDLER_COMPLETION((*o));

#if defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)
    // Check whether buffers are still valid.
    if (owner)
    {
      buffer_sequence_adapter<boost::asio::const_buffer,
          ConstBufferSequence>::validate(o->buffers_);
    }
#endif // defined(BOOST_ASIO_ENABLE_BUFFER_DEBUGGING)

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    detail::binder2<Handler, boost::system::error_code, std::size_t>
      handler(o->handler_, o->ec_, o->result_);
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
  ConstBufferSequence buffers_;
  Handler handler_;
  IoExecutor io_executor_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_WINDOWS_RUNTIME)

#endif // BOOST_ASIO_DETAIL_WINRT_SOCKET_SEND_OP_HPP

/* winrt_socket_send_op.hpp
fCuRaRKf5Cm3Ka6fxlvU42eQ1zgex9X3nXnnUHO8PoetxzdenMv2cfM0kc+eM8jnT+ObzmcuO9D88h6hq5hfyFyFxNW01vRbm/c84w0XxXMsbLVb2a4X2a210m5l2xxp21POp3uW/N87M/G97Xa1YfyEousnngW7l8nuK6fQWL1ZVU0ar6WwSQym8Q/OwWpr3Xc7fv/nNOW4hc0hPJ0/TN8HNmDfU3TsH5zyWyX3VcTxM3V0iNh/jSMRarOL8Tx+p3qOkuGYpsTw83U2nfdPjo7Kk1i3N1GJVZeo3fD9UryL4I/3FzixH/sGq39y9FFCnNNwfpkGsbS+/E55H53vNXWmskLV5q28RMeobAjDY+9i+DtGAe2f6HTgua4AKySXOFKVONqnxa/K2V3M2Ia6YIRaiTjsMergyvTOJvvlziehKPi5mqVkO/6gjHEGN5pe3buOnBcdQHk9Va1Q1is91S5ybEskpe9cR4bygdrfEUTjRncNFeviIx00/rK9OyjCWi8XdtDj0/RyC9wB3dzOdVvt3120Yx89h/VyQzw1bmeYeR4D2wnh2829aSzpRaaxpGyTBZvlIp4Jv8gwjN8ju6nYFsbaun3SvG6ZTl/3eXZ7cdxT7PL5u6XQ4S1iW3ZUV8xrYowpyqiPHm+ZzXP6Wgs9Xo9Rj5dtN+jHn/J3jnLveZSUdK//RoP/cYP/oPT/Z2v8WmvqNl/7t7lavs3VCv6ptHw3kZbv6VYLf4wYt7P/R7s21SeN/uBeOw1hOw3bs9q/TWn/nlDwpzZo/O6W62DJ3/QtNgrMhzu34TfVQx7YDBQ23D/9LuJ1nu53se73It3vC3S/z9X9XppGx6RyMY9/Z4r1JnS/F/PvAQrVxzIOC/n356JO5t+z4Jbz7yNwK/h3Jc51If/e7/DqFVcrrMPBWiDYR+OB1yvcD8N6upW8lv5lrJe7DrwFvAK8E7wSvAe8inVzrwafBa8B3wKvBz8U+Qd+Ks4Lfsfbnap3ewfwer3ucWiDTrHHoFOcKe1YjwIMIjt7HeUyP473rdRwIG0Ishsqno25vJynevNjEdgVzAV7gYXgOeAycD64CrxE5B+4lf3bwUrw9+Cl4APsf5D9+0T+gi+CVWBrFfkMjgWvBEvAjeAW8HqwFvw12AnX8i6wD3gPOBh8EBwHPgROB38HXgjeB1aA94Nrwb3gZeAD4DrwUfBa8AlQ3G+PgbeAT4F3g0+Dj4LPgK+DIn2n+Pinwf1gkBPXBHSDwt+O/R3AV8A48FWwB3gAzADfAOeCb4G54L3g5eBucD14B3g7uAXcBb4DPgS+Cz4D1oNvg++BH7OdA9fvRtAFrgC7g6VgIijs0sHzwUz2Sx3qjvblZACXkyQ5N5rmXZNdN7G+HpeT07zWnELlBBDnB1uBA8E24HRxXNADdgSvASNEvrN/G/t/A0aC94Ax4BEwFhRryXUFF4Ep4C4wE3wEFMd9GxwKfgQOBz9l/2fs/wrMBk+BI0An0jESDAXHgZFgb3AQOBEcAU4Cp4KTwcXgFHAF2A4sZf/FYJC4fuznfEWBtr9Pe+vu05zopvOfjteI3UCdXXUj583Q2e3283j1dnYG3fN9jdRLCTq70Jimj6fIuWFiXhzZkf1xtvuj4i1nD/OajI+CfcAnwH7gM2A2+Cw4EvwInAE+D54PvgBeAb4I3gq+BO4AXwZ3gX8FnwZfBf8CHgBfBF8D68C/ga+AB8E3wNfBd9n/Gfgm+A34FngKPASK+u1tsD34LtgdfA9MBQ+Dg8EPQZRNii+3VzynieZUmdqrm7EpDLwFjARv5XZrN9gFvA1MAn8D9gVrwSxwJzgZvBtcBt4DVoK7wF9w+KvA34E=
*/