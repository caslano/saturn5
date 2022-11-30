//
// impl/executor.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/global.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/executor.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

// Default polymorphic executor implementation.
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
    detail::ref_count_up(ref_count_);
    return const_cast<impl_base*>(static_cast<const impl_base*>(this));
  }

  void destroy() BOOST_ASIO_NOEXCEPT
  {
    if (detail::ref_count_down(ref_count_))
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

// Polymorphic executor specialisation for system_executor.
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
    executor_.dispatch(BOOST_ASIO_MOVE_CAST(function)(f),
        std::allocator<void>());
  }

  void post(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.post(BOOST_ASIO_MOVE_CAST(function)(f),
        std::allocator<void>());
  }

  void defer(BOOST_ASIO_MOVE_ARG(function) f)
  {
    executor_.defer(BOOST_ASIO_MOVE_CAST(function)(f),
        std::allocator<void>());
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

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

#endif // BOOST_ASIO_IMPL_EXECUTOR_HPP

/* executor.hpp
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
*/