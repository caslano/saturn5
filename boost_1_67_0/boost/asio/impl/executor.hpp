//
// impl/executor.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXECUTOR_HPP
#define BOOST_ASIO_IMPL_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/executor_function.hpp>
#include <boost/asio/detail/global.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/recycling_allocator.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

#if defined(BOOST_ASIO_HAS_MOVE)

// Lightweight, move-only function object wrapper.
class executor::function
{
public:
  template <typename F, typename Alloc>
  explicit function(F f, const Alloc& a)
  {
    // Allocate and construct an operation to wrap the function.
    typedef detail::executor_function<F, Alloc> func_type;
    typename func_type::ptr p = {
      detail::addressof(a), func_type::ptr::allocate(a), 0 };
    func_ = new (p.v) func_type(BOOST_ASIO_MOVE_CAST(F)(f), a);
    p.v = 0;
  }

  function(function&& other) BOOST_ASIO_NOEXCEPT
    : func_(other.func_)
  {
    other.func_ = 0;
  }

  ~function()
  {
    if (func_)
      func_->destroy();
  }

  void operator()()
  {
    if (func_)
    {
      detail::executor_function_base* func = func_;
      func_ = 0;
      func->complete();
    }
  }

private:
  detail::executor_function_base* func_;
};

#else // defined(BOOST_ASIO_HAS_MOVE)

// Not so lightweight, copyable function object wrapper.
class executor::function
{
public:
  template <typename F, typename Alloc>
  explicit function(const F& f, const Alloc&)
    : impl_(new impl<F>(f))
  {
  }

  void operator()()
  {
    impl_->invoke_(impl_.get());
  }

private:
  // Base class for polymorphic function implementations.
  struct impl_base
  {
    void (*invoke_)(impl_base*);
  };

  // Polymorphic function implementation.
  template <typename F>
  struct impl : impl_base
  {
    impl(const F& f)
      : function_(f)
    {
      invoke_ = &function::invoke<F>;
    }

    F function_;
  };

  // Helper to invoke a function.
  template <typename F>
  static void invoke(impl_base* i)
  {
    static_cast<impl<F>*>(i)->function_();
  }

  detail::shared_ptr<impl_base> impl_;
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

// Default polymorphic allocator implementation.
template <typename Executor, typename Allocator>
class executor::impl
  : public executor::impl_base
{
public:
  typedef BOOST_ASIO_REBIND_ALLOC(Allocator, impl) allocator_type;

  static impl_base* create(const Executor& e, Allocator a = Allocator())
  {
    raw_mem mem(a);
    impl* p = new (mem.ptr_) impl(e, a);
    mem.ptr_ = 0;
    return p;
  }

  impl(const Executor& e, const Allocator& a) BOOST_ASIO_NOEXCEPT
    : impl_base(false),
      ref_count_(1),
      executor_(e),
      allocator_(a)
  {
  }

  impl_base* clone() const BOOST_ASIO_NOEXCEPT
  {
    ++ref_count_;
    return const_cast<impl_base*>(static_cast<const impl_base*>(this));
  }

  void destroy() BOOST_ASIO_NOEXCEPT
  {
    if (--ref_count_ == 0)
    {
      allocator_type alloc(allocator_);
      impl* p = this;
      p->~impl();
      alloc.deallocate(p, 1);
    }
  }

  void on_work_started() BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_started();
  }

  void on_work_finished() BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_finished();
  }

  execution_context& context() BOOST_ASIO_NOEXCEPT
  {
    return executor_.context();
  }

  void dispatch(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(function)(f), allocator_);
  }

  void post(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.post(BOOST_ASIO_MOVE_CAST(function)(f), allocator_);
  }

  void defer(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.defer(BOOST_ASIO_MOVE_CAST(function)(f), allocator_);
  }

  type_id_result_type target_type() const BOOST_ASIO_NOEXCEPT
  {
    return type_id<Executor>();
  }

  void* target() BOOST_ASIO_NOEXCEPT
  {
    return &executor_;
  }

  const void* target() const BOOST_ASIO_NOEXCEPT
  {
    return &executor_;
  }

  bool equals(const impl_base* e) const BOOST_ASIO_NOEXCEPT
  {
    if (this == e)
      return true;
    if (target_type() != e->target_type())
      return false;
    return executor_ == *static_cast<const Executor*>(e->target());
  }

private:
  mutable detail::atomic_count ref_count_;
  Executor executor_;
  Allocator allocator_;

  struct raw_mem
  {
    allocator_type allocator_;
    impl* ptr_;

    explicit raw_mem(const Allocator& a)
      : allocator_(a),
        ptr_(allocator_.allocate(1))
    {
    }

    ~raw_mem()
    {
      if (ptr_)
        allocator_.deallocate(ptr_, 1);
    }

  private:
    // Disallow copying and assignment.
    raw_mem(const raw_mem&);
    raw_mem operator=(const raw_mem&);
  };
};

// Polymorphic allocator specialisation for system_executor.
template <typename Allocator>
class executor::impl<system_executor, Allocator>
  : public executor::impl_base
{
public:
  static impl_base* create(const system_executor&,
      const Allocator& = Allocator())
  {
    return &detail::global<impl<system_executor, std::allocator<void> > >();
  }

  impl()
    : impl_base(true)
  {
  }

  impl_base* clone() const BOOST_ASIO_NOEXCEPT
  {
    return const_cast<impl_base*>(static_cast<const impl_base*>(this));
  }

  void destroy() BOOST_ASIO_NOEXCEPT
  {
  }

  void on_work_started() BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_started();
  }

  void on_work_finished() BOOST_ASIO_NOEXCEPT
  {
    executor_.on_work_finished();
  }

  execution_context& context() BOOST_ASIO_NOEXCEPT
  {
    return executor_.context();
  }

  void dispatch(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(function)(f), allocator_);
  }

  void post(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.post(BOOST_ASIO_MOVE_CAST(function)(f), allocator_);
  }

  void defer(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.defer(BOOST_ASIO_MOVE_CAST(function)(f), allocator_);
  }

  type_id_result_type target_type() const BOOST_ASIO_NOEXCEPT
  {
    return type_id<system_executor>();
  }

  void* target() BOOST_ASIO_NOEXCEPT
  {
    return &executor_;
  }

  const void* target() const BOOST_ASIO_NOEXCEPT
  {
    return &executor_;
  }

  bool equals(const impl_base* e) const BOOST_ASIO_NOEXCEPT
  {
    return this == e;
  }

private:
  system_executor executor_;
  Allocator allocator_;
};

template <typename Executor>
executor::executor(Executor e)
  : impl_(impl<Executor, std::allocator<void> >::create(e))
{
}

template <typename Executor, typename Allocator>
executor::executor(allocator_arg_t, const Allocator& a, Executor e)
  : impl_(impl<Executor, Allocator>::create(e, a))
{
}

template <typename Function, typename Allocator>
void executor::dispatch(BOOST_ASIO_MOVE_ARG(Function) f,
    const Allocator& a) const
{
  impl_base* i = get_impl();
  if (i->fast_dispatch_)
    system_executor().dispatch(BOOST_ASIO_MOVE_CAST(Function)(f), a);
  else
    i->dispatch(function(BOOST_ASIO_MOVE_CAST(Function)(f), a));
}

template <typename Function, typename Allocator>
void executor::post(BOOST_ASIO_MOVE_ARG(Function) f,
    const Allocator& a) const
{
  get_impl()->post(function(BOOST_ASIO_MOVE_CAST(Function)(f), a));
}

template <typename Function, typename Allocator>
void executor::defer(BOOST_ASIO_MOVE_ARG(Function) f,
    const Allocator& a) const
{
  get_impl()->defer(function(BOOST_ASIO_MOVE_CAST(Function)(f), a));
}

template <typename Executor>
Executor* executor::target() BOOST_ASIO_NOEXCEPT
{
  return impl_ && impl_->target_type() == type_id<Executor>()
    ? static_cast<Executor*>(impl_->target()) : 0;
}

template <typename Executor>
const Executor* executor::target() const BOOST_ASIO_NOEXCEPT
{
  return impl_ && impl_->target_type() == type_id<Executor>()
    ? static_cast<Executor*>(impl_->target()) : 0;
}

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXECUTOR_HPP

/* executor.hpp
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
*/