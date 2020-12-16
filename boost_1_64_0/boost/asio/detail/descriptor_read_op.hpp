//
// detail/descriptor_read_op.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  descriptor_read_op_base(int descriptor,
      const MutableBufferSequence& buffers, func_type complete_func)
    : reactor_op(&descriptor_read_op_base::do_perform, complete_func),
      descriptor_(descriptor),
      buffers_(buffers)
  {
  }

  static status do_perform(reactor_op* base)
  {
    descriptor_read_op_base* o(static_cast<descriptor_read_op_base*>(base));

    buffer_sequence_adapter<boost::asio::mutable_buffer,
        MutableBufferSequence> bufs(o->buffers_);

    status result = descriptor_ops::non_blocking_read(o->descriptor_,
        bufs.buffers(), bufs.count(), o->ec_, o->bytes_transferred_)
      ? done : not_done;

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

  descriptor_read_op(int descriptor, const MutableBufferSequence& buffers,
      Handler& handler, const IoExecutor& io_ex)
    : descriptor_read_op_base<MutableBufferSequence>(
        descriptor, buffers, &descriptor_read_op::do_complete),
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
    descriptor_read_op* o(static_cast<descriptor_read_op*>(base));
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

#endif // BOOST_ASIO_DETAIL_DESCRIPTOR_READ_OP_HPP

/* descriptor_read_op.hpp
Ik0UfoEvh0rVSrYVWjjRLDa3JqJkrQWCxGk28qfkG7AggyyLj5C6NL7LlEMO5XBrl7skXmjJIfE+SR47lFNB/FChy487HJzU5eCjeWROjQM5nY8dxeWRcMl1Ob3CTSKXxBtBOWTfWE75kYE1OSQ+Kdfdk89v49Dh5Mth8ywznjNcawddbv3iBduuW5jPO6xBzFYqGyO/1FD7ecrZvq8F2LTHzu9wbi0Q5E8jfKAOh2ackJsbIwwN45yBQ+A5O5ebnI24dkab+AtuzryLNxTx7NRE/AGwDI9QbAciUKmeCGimRfF937kPIhTwrV5cRzIwjrkVg8CGN8SDY2NrB0bxaxOjg3huE8VcNizs0mkVuF05hGdboqpRg0uigorDRuUxT5ZtxWWM8Qbe3g9h3+DISjSCR0ijx9DD25SOpD2Jbx2F34qxRPGK4bD6erQjwuU4h8OGy+KSZ/tga1uC/hkaOj8t4spiNXPF1U0uEz/g5Ao6mQErXIcysLtDYQ9jU+0Zm8JHBHD+KtZcBaPvtaBJh6/AY20ymMc0wfym0RswVzBPlyHN6VC0A8LanjOkcEm3pWhTgVAR3hfLCDp4Km7N41zjMvgwXLNVyZrcaSq9R2sZu4rzDrxzi91WrovkWyQ662Oi2pztx+nTPMmbHvkyTJU8AfqazkVXmvYvfpDQzRPvpXMFwQsUhos7XDBPP4JO/Qjm64f2Rlfyf/QQeToOp/n4Ur5gU6ehDea1kDXZowxw6jB7VhDkeyDuhcSaRkbRyfBDBTbG6SpDDaI3FjQzRB/TCYl+3NgqV5bNzawMjhrRGFW0MtAs30S8Dgs4BFrNcqilZWMrS7bm8Oihk1GVNkZ5TekWNDQzjOF2qq5Hc2ZBV4114X3asKTDpmXxCc7h/oF0ubM5TPyKzWEOmZReEwbqxsgAGyMDnB0ZQHNkQJgjA8IZGXDpSNhYZ7FHZk1/3moPOu26jVGXQSEKZDEsY9Q8UzZRukqBSs2mof5ai+b0ogjCXNUsEqdSVI+TeD0rwNLkZney2ksSGL0cAblLEUijWmOdANZrRJYwNjqZ1pzFw+VhfZeE/R1yEn7hsK6ues1wSWzNI4vkqogRmbuSlCtrZ70rXV4MHMxngqCDCYI8EwR5JgjyTOA4jbtkaPIFTBDMY4LANkHk0lgFEiJbRvN4YCQTzoB0IBtZNmAvB6DgjVMFbMZsrKsEmVgyxbCLLoHhStPBXGiIIY7CS3tGcI8/gkgAgUthOvVdBserpsliRpgEpkQlZfRrezh0NmGqPIlNG5PIkeDI6XJuTv3QEQZ7suEK8ZxtM/zMkiEKb/O7fYePOwQudZpcgN50bjPo2Kkgp1NBbqdgfVM5/VmXlHK+EtNBgkstHST4OkwqifY8EC9wKfhktRiYvJ7EmtJeCcq8mWTT8B2LmoJRc6jQwC6P5tt1W3uMlcmkgcWl81QI4h+7dOlou+jyyX04VxLfiXMF5lPuWTmeLNM+Gr5xm/U8KzserTFA9mUQzWOM8gTJi5YOAWtXc9hGTeuR/YRQloQhKjZ2qmuCjKyDKJEK0vcHs4SrDlhXHXMcUy/SCNdEbWKs12Jw4RNpixy1s4VDaFHTM8WSQXXb7XU77XXntdfttIcjdw0Pf4S7yHL43I4htgYATG4ssL/D5ArsqTTl3MDC2Slj8Ew6DoI2toYNzjedRhZNhd5pUmYE0Tsvi3LjgrvtciVuc3rr5dJ6hrgSeHGOSo4Xm7szl3as576G5IoQJDrR2G+nEvuVpI6CQhMHSCQ7ZnBqNcOsu9lzJa7hg3zDBx0NH3QyfNDR8EG+4YNOhg86Gz7IN3zQ0fBBJ8MHL2T4oIPhq1ge6lO5wRw=
*/