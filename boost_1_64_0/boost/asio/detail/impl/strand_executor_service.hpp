//
// detail/impl/strand_executor_service.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP
#define BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/call_stack.hpp>
#include <boost/asio/detail/fenced_block.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/executor_work_guard.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Executor>
class strand_executor_service::invoker
{
public:
  invoker(const implementation_type& impl, Executor& ex)
    : impl_(impl),
      work_(ex)
  {
  }

  invoker(const invoker& other)
    : impl_(other.impl_),
      work_(other.work_)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  invoker(invoker&& other)
    : impl_(BOOST_ASIO_MOVE_CAST(implementation_type)(other.impl_)),
      work_(BOOST_ASIO_MOVE_CAST(executor_work_guard<Executor>)(other.work_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  struct on_invoker_exit
  {
    invoker* this_;

    ~on_invoker_exit()
    {
      this_->impl_->mutex_->lock();
      this_->impl_->ready_queue_.push(this_->impl_->waiting_queue_);
      bool more_handlers = this_->impl_->locked_ =
        !this_->impl_->ready_queue_.empty();
      this_->impl_->mutex_->unlock();

      if (more_handlers)
      {
        Executor ex(this_->work_.get_executor());
        recycling_allocator<void> allocator;
        ex.post(BOOST_ASIO_MOVE_CAST(invoker)(*this_), allocator);
      }
    }
  };

  void operator()()
  {
    // Indicate that this strand is executing on the current thread.
    call_stack<strand_impl>::context ctx(impl_.get());

    // Ensure the next handler, if any, is scheduled on block exit.
    on_invoker_exit on_exit = { this };
    (void)on_exit;

    // Run all ready handlers. No lock is required since the ready queue is
    // accessed only within the strand.
    boost::system::error_code ec;
    while (scheduler_operation* o = impl_->ready_queue_.front())
    {
      impl_->ready_queue_.pop();
      o->complete(impl_.get(), ec, 0);
    }
  }

private:
  implementation_type impl_;
  executor_work_guard<Executor> work_;
};

template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::dispatch(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // If we are already in the strand then the function can run immediately.
  if (call_stack<strand_impl>::contains(impl.get()))
  {
    // Make a local, non-const copy of the function.
    function_type tmp(BOOST_ASIO_MOVE_CAST(Function)(function));

    fenced_block b(fenced_block::full);
    boost_asio_handler_invoke_helpers::invoke(tmp, tmp);
    return;
  }

  // Allocate and construct an operation to wrap the function.
  typedef executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(function), a);

  BOOST_ASIO_HANDLER_CREATION((impl->service_->context(), *p.p,
        "strand_executor", impl.get(), 0, "dispatch"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
    ex.dispatch(invoker<Executor>(impl, ex), a);
}

// Request invocation of the given function and return immediately.
template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::post(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(function), a);

  BOOST_ASIO_HANDLER_CREATION((impl->service_->context(), *p.p,
        "strand_executor", impl.get(), 0, "post"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
    ex.post(invoker<Executor>(impl, ex), a);
}

// Request invocation of the given function and return immediately.
template <typename Executor, typename Function, typename Allocator>
void strand_executor_service::defer(const implementation_type& impl,
    Executor& ex, BOOST_ASIO_MOVE_ARG(Function) function, const Allocator& a)
{
  typedef typename decay<Function>::type function_type;

  // Allocate and construct an operation to wrap the function.
  typedef executor_op<function_type, Allocator> op;
  typename op::ptr p = { detail::addressof(a), op::ptr::allocate(a), 0 };
  p.p = new (p.v) op(BOOST_ASIO_MOVE_CAST(Function)(function), a);

  BOOST_ASIO_HANDLER_CREATION((impl->service_->context(), *p.p,
        "strand_executor", impl.get(), 0, "defer"));

  // Add the function to the strand and schedule the strand if required.
  bool first = enqueue(impl, p.p);
  p.v = p.p = 0;
  if (first)
    ex.defer(invoker<Executor>(impl, ex), a);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IMPL_STRAND_EXECUTOR_SERVICE_HPP

/* strand_executor_service.hpp
XjnGq/Ol6Fzn0pm95uhrYy6dH7Lp/D3RecOq6+xzepfOdVbYnNE483omXa6RrkvnsrFenRejc7NX52j1DL9rXj8hus6dJrjm9R6dz7yejc6u+VTJOK/OPyNQNMGhc7Q6htf1PjXBvde7hVvY3qec+iLv2uttg75MulyTdB36FuR59b0cnlqnvtHqF17Xe1QMffe49K1169sG/dilr3l3TlM/ftn6DOoP/YE6b5pg2YZKbO9I5LiL2Fzq7Vm/1/he5jn05QSeQ371SBq+6/dHfPRqRK+0Cy294t87QiZYJ4l36vSVBHTSuopLp33j/euqyOgU/95RUXSdiH9n6mn7Bf71FDY6xb93FI6hU/gdqqeKCV6dmtGpzuiUwN6RTafc3j57R21cT6Thu88y4UKvTs+jU6PRKf69o8YYOjW2cT0F6dR5om89MfhbOsW/d4SMRydahqUT8WennkjD+b3GRP96yjM6xbd3BH9wHUn82a0jS58Dk7zP4+PoU2H0iW/vCH7HM3krYeuZnJPu3UvZPNHxTEbeu5eyO4Fnsu+YmO6/d/RwgVfnF9C53ugce++o3qXvkzH0/bFL33offb+agL6+42W6/97RwItabnCl6rsIOoG+oUkOfQtah5d561av9907MufbMiKylGgf0tEy0ftl2M52Wefb0NnED1LbwU67vL3BEolPlfhtkYzqno11RmiwxBeEzpVULu7ZgNINhbyLsD6Zmp6f2qFPyN7/xYauVb5PUDZ3pcdfvp72ZM4GoZOrfKsne8v3MOUbjlq+vvtXpnw/7FO+4RjlG45RvvtilO9trvLNot1koVvKGG/5fuUMy1fbb1zlWzbFO+bO5yZNpnwT3/sUWe6kZeHeHyQ+oefJ/FhthzR89z4nTPXqVsRN0gos3RLf+0Q2WDeJT+jZMj9GvaGb/95nyjSvbjPz0M/oFt/eZ5FNn5WZnv1C4hOqq5j9nDR89z4b3frofDZs9Im99xmOoUs4sbqJ2adcupi6qZvu0kWfCXVGl/jmOXWqT9B53ro2rhvbeVznGmGRSx8dgxuNPvHNcRpj6NPYxvXj0se8OxfP8K+fUKGlT/x7ocgE6yTxZ7eOVCdsZfrXUZ7RKf490bzoOhF/duvJWt/pPcv7LnkKnSqMTontjSLnfI8mbL1XDu/t3TPaXOh6jy507xGe+Xs06frur6QWe3V/Gd3rje7x740i43yfjqH3j11613v0PvP36SC9U2b713noIkvv+PdGkXHuw1wUXe+Mixx6I+/aIzyL9X1qtn99lxq9498bLXXpXRlD79UuvUvdep/F+m6c4xq3tL7rjN7x742KDHfw03OBxLftWByk0+65Lp20LhuNTvHvjTZG14n4th2LScN3b3Rnibd9voVOocmWTnHujU529UnCVtvsmO6zNzrZ1ScJO/YJ22Atg3R99wm3z/PqfCTSJ43Oce6NunSujKHzapfOpW6d22A9I0jnmvlenUPcpM7oHOfeqEvnh2w6r+/jszfq1Bl59z7hmdcz6frujVYt8Or8KvXcbHSOc2/UpXOXKdF17jTFtTfq0fnM65l0ffdGVy706rwanYumWDrHsTc6xbU3avTVb9Lce6NOfZF37RW2QV8mXd+90SUXe/VdyU1qjb5x7I269L07hr57XPrWuvVtg37s1vc41462oV+WLpMj1zse7/v3axetueqFriM+Eb7tAz2C/bU8Lv5LfvRM2Wt3rx1w9O3b64pfyL4fZw1vyvX6V5YOvrPinq4f6nYgKePE3of+e/y7+PtZaTu/L0H+XaZK+Zfcd6B52HVf//3Y782458P3PbAycT8u/y5/Lf5+VtrOj8sJyk0/OZK16v0=
*/