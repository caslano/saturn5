//
// detail/executor_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_EXECUTOR_OP_HPP
#define BOOST_ASIO_DETAIL_EXECUTOR_OP_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/scheduler_operation.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler, typename Alloc,
    typename Operation = scheduler_operation>
class executor_op : public Operation
{
public:
  BOOST_ASIO_DEFINE_HANDLER_ALLOCATOR_PTR(executor_op);

  template <typename H>
  executor_op(BOOST_ASIO_MOVE_ARG(H) h, const Alloc& allocator)
    : Operation(&executor_op::do_complete),
      handler_(BOOST_ASIO_MOVE_CAST(H)(h)),
      allocator_(allocator)
  {
  }

  static void do_complete(void* owner, Operation* base,
      const boost::system::error_code& /*ec*/,
      std::size_t /*bytes_transferred*/)
  {
    // Take ownership of the handler object.
    executor_op* o(static_cast<executor_op*>(base));
    Alloc allocator(o->allocator_);
    ptr p = { detail::addressof(allocator), o, o };

    BOOST_ASIO_HANDLER_COMPLETION((*o));

    // Make a copy of the handler so that the memory can be deallocated before
    // the upcall is made. Even if we're not about to make an upcall, a
    // sub-object of the handler may be the true owner of the memory associated
    // with the handler. Consequently, a local copy of the handler is required
    // to ensure that any owning sub-object remains valid until after we have
    // deallocated the memory here.
    Handler handler(BOOST_ASIO_MOVE_CAST(Handler)(o->handler_));
    p.reset();

    // Make the upcall if required.
    if (owner)
    {
      fenced_block b(fenced_block::half);
      BOOST_ASIO_HANDLER_INVOCATION_BEGIN(());
      boost_asio_handler_invoke_helpers::invoke(handler, handler);
      BOOST_ASIO_HANDLER_INVOCATION_END;
    }
  }

private:
  Handler handler_;
  Alloc allocator_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_EXECUTOR_OP_HPP

/* executor_op.hpp
HFJZapYCYBHKLAFvvtXyjrfUhm3qXmYJwI/8WG8pa8I732lN+PYttQmUsb/wXUgLt9H8qnFHQUjCs2K3BnQnPxJ9vLNQ/suU02HPwU3clrirthwMb1kfC1rmo0OWQJwtPjNzLZBDldIcTn4GuJcZ8GmFhmLOw58HHZoM/Xmp2G3mL5IzdbrKiC5lEbzwtnyufnkeu5wRnrnjwSWJDjnlfETE55sR00Rvjxsmj816a32M69ylynD1qZJSuZZmCCUu07YhbVvaH5oRe3HmSk1HSJu5gicQyhX5bOaKYKapY95yjMEvZzNXcDaLtjWn8Sx13G3RzLkvo8kuePrbq075D6Qkr5b5cvf4K/f4821Oip9/H1LX9zjk2R2arQriVp5S7tEYjMMrfLmQJ7bMhc/jFaBm8HkCPpvhswM+cSOiTvhshM8Qwge5XTi0zkRnJo2j88/iUD9eDY+8mF15GCovdcpT1NqFe/93tUG7wRj5c5+PqpFzj6erSMfzToRY23EDJrg/Xb2PMDX0XpI886TWA3LRmzqaiuKZeFIVTxUOjj+pu5wL2ZN00O3cVZYq2jeHNqU55xkz2+1d+KREBaLl03QYZVkZHqg4RK47ASEKLcGhw6e34h44eCdO/iPc8WUwiESN/fd/T+y//oQmq788YLQOzhMU+1fnRWL/f+apgYvZ3D/2j//+2H86rtVplPb5/LMxcGdZwNAqiNwF
*/