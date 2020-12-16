//
// detail/reactive_null_buffers_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP
#define BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/reactor_op.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename IoExecutor>
class reactive_null_buffers_op : public reactor_op
{
public:
  BOOST_ASIO_DEFINE_HANDLER_PTR(reactive_null_buffers_op);

  reactive_null_buffers_op(Handler& handler, const IoExecutor& io_ex)
    : reactor_op(&reactive_null_buffers_op::do_perform,
        &reactive_null_buffers_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      io_executor_(io_ex)
  {
    handler_work<Handler, IoExecutor>::start(handler_, io_executor_);
  }

  static status do_perform(reactor_op*)
  {
    return done;
  }

  static void do_complete(void* owner, operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    reactive_null_buffers_op* o(static_cast<reactive_null_buffers_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_REACTIVE_NULL_BUFFERS_OP_HPP

/* reactive_null_buffers_op.hpp
wgzlNiF2+NbH9XWy0IeH6UcvXV6mvnM2I7bSrW1qMePPeEzpmSnWWQnunz4+wSpN9m2bGdU3zwDpz8HN4I4xwuyEOt2pi/n3JKMMUlmsBMdgXYxG29U2vpGfIDYYbeJ8ZujG2E8u+Grm9FLRUd/gOfiJmvPF9zBg/i7N6dI3UOT7JI8PWkzPnuyxxXPlWcy/a963sBzyUzSnQ6L8tJ/q88G5AT9Nc2zahQWl/T0eH/HYexUzr7aXr/d5rNwbpvv9Po989gHNS31e2B/UDC+K5h/S3PwjjPvDHl8yFPKPaG7WbIX8o5qbs8xC/jGP95XDMvm45kOlheHzn1CcLkqd0ePl75MhP9Cvj6crTk1iEP8ZHi/3hr7/lOYjZa/Mz9Rs8YCXrrM0Wzprv4OWzPT42SG3FPF+WnFB2CsKNpVluAsSc+Ral4aD2oxz08w7A+s8ZUNfItiQnj8/YhKIOzs5bSMRIf0XWrvWFF0aUG3zeRMXWd3kFs+6crg4wczeUmKfTTHM4V1iWRfE7iFlHbd2ek0hhXkpcwz80YTi2c97DNcesgk9exl47tpv2XNzuTDOOPJ3BfRu0y9x2ltasHK5UpybXxnop+kh2lsa6HqfxVU+c3tNroY+UC4vLg1XyqXhgd4FFCLn7Zokl/Mkvpjksnf/WnCzwnLQ7Jeh+Cl48OsSXK89uz7B9b2INxheNFNzVneyfKR1uP1e8SXofQND8026zF51PsiEl0+yzZcTNt2xSrNFF/Fw/DdGNv534JsirtcjYH9qZEMzgMRuiRj9FuP58phhd2tRKzFfHtmQ9+j5r8XMdP9u4T+9o19P2nAe9RjqG7FdYyV8cGuK2a1isLktaQNXw+b22MaM/xAQ8vvNyEbu7vxWgjXqzL6dYN1JzLNHjM6ML04BNonEPHtkQ1ul3fezOxI8My+1O+s45nlYFt9L2uiy4LDuStqhxqHtvTtpo/2J+fiknfjm+0lO+5FNJWSbH8Q2snTfzsV7Njz+77RwPy7S8iPPRr+vmJP3eb1VfFVC+PemWCVvtTtyzsx9vg2Sh324HnOrTU35c/g/9XmxvLc4vIiThzB+5tvIOwD+c4/Hdft+n09mvK2Kz1OOmXdGzAMxp0zgFCayeTBtww0O6s0v0zbGoaiH+G33UNrOOQ77Yvn85dhWVtMhvF9PY5P74fE8fmzr7j95OMHywA+/TdkEfngkbaP9wOcxx3byMiJvj6ZsYl+R7e/Ttn6FQ9yPJW3hV+Tj8bSNVE6k8YmkXex/2j/s25o2Fverejo/YV5yet6+A0/6Nrm8Z9hT7HFaqsP3rVpd3fX+lKfR6fU8fx/rbi/l0x4bcGeAPRPpsi/jWY/hYh87bw/WnxUXVswpmizSn/d0SgPpL3i6xP+ip9s4mL3kGHX+HBjYX0OGzNL+Yp8VkdEzf4918wj2FvsMCcFZy5Zhkpb2FHualMG/I13K4D8eEx+8HOlSBmutq1lx0L7EtXbEJMxXaIbs2Lr4So8tobWqFCr4OglOISNNrwIvDfYt6i/547p1IyZrTNeLmIxh1k8we0bLBpY1/bq2odP9uraRp4tPXu30uK5t7Fhc1zZxLK5rr3HMr2uvdXpc1zb1GScEvt8MbGF/NKam+F7nuO/3zWPd1bstPCZrWF7v6bLuZEtfn7Try7cKdfV77g2O+eW6tae7a2OIbSNMxo3wwxsdC8d53OZuG/Mu+bEy5taJbOdsgrEZ+PY+l+eR3x0c12Myzu+OjmHMhTB3cnowFsNzb3Lcn1vY2elu/ENp2MXXuZDQx+0aMP0jR4/PdnN20fiI+O4x54qF598cc65E4HvE3LtLZM+I++WwV8iDvnzvJJ/q4ow=
*/