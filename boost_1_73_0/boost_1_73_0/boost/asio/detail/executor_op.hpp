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
HJ4f8/tkuepDAclzQK81LYM3H4qtCmlsO8eMvQKcVjEcpBjoMcyAMMOSOw9PpCMU1QjSXSXzkakgHeltNgbue6qHe2g+VBsGAueeqQsAFkqugCIvfBmgNB26wVb+//6XZ50tmDzir1ajD27NBJzUFDJfPzhbLTEtT5Y9P7g9Jw3XUvGIWqkVM/FyCnYgozIKCi4AfJBVBREEU71nNOQDC9gMy2J7XOwhMfZC2/HJjxTttKhoQiu6Lebwy3L5NrjmnpurPkmIlaQkj/7Rz8zzLUfi50nIDiZnqbPIiAljZ926Z+DOtJgcEdg6xOoAGV37pOVhnGmqXGVSNuxwyW9Wlim1W4wFet7lSU1yv5TWj+QnlbuDloUAWTOAqfBGRRtA2MMUae9qFWmKhk1H01ZpO8Alo0BeMxgUyJhzHUBw7bMjFj3bZHXEXA1ipCegSSUR+QCmOrnycE46LHk7sl0l4AVULq4ORcPYnNrc9AAWOIdDAGwBIwt09+z641aPhtZBVQv7ivEcoW4yF3LmCSaW9hGGfoSS9yqkrLOJ9L3v8i3iPXQqLu0mY3Yv8OVJl9ChPnr592Ik3DOuX23qCKcyVdktUAcXqmhsIBeRv1W1Kn75s5NiabxdKqMbuZiIrvzGvkV078N4rcWZ1B0F
*/