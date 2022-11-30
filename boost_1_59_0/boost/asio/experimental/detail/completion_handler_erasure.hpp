//
// experimental/detail/completion_handler_erasure.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_COMPLETION_HANDLER_ERASURE_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_COMPLETION_HANDLER_ERASURE_HPP

#include <new>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/dispatch.hpp>

namespace boost {
namespace asio {

class any_io_executor;

namespace experimental {
namespace detail {

template<typename Signature, typename Executor>
struct completion_handler_erasure_base;

template<typename Func, typename Signature, typename Executor>
struct completion_handler_erasure_impl;

template<typename Return, typename... Args, typename Executor>
struct completion_handler_erasure_base<Return(Args...), Executor>
{
  Executor executor;

  completion_handler_erasure_base(Executor&& executor)
    : executor(std::move(executor))
  {
  }

  virtual Return call(Args... args) = 0;
  virtual void destroy() = 0;
  virtual ~completion_handler_erasure_base() = default;
};

template<typename Func, typename Return, typename... Args, typename Executor>
struct completion_handler_erasure_impl<Func, Return(Args...), Executor> final
    : completion_handler_erasure_base<Return(Args...), Executor>
{
  using allocator_base = typename associated_allocator<Func>::type;
  using allocator_type =
    typename std::allocator_traits<allocator_base>::template rebind_alloc<
      completion_handler_erasure_impl>;

  completion_handler_erasure_impl(Executor&& exec, Func&& func)
    : completion_handler_erasure_base<Return(Args...), Executor>(
        std::move(exec)), func(std::move(func))
  {
  }

  struct uninit_deleter_t
  {
    allocator_type allocator;

    uninit_deleter_t(const Func& func)
      : allocator(get_associated_allocator(func))
    {
    }

    void operator()(completion_handler_erasure_impl* p)
    {
      std::allocator_traits<allocator_type>::deallocate(allocator, p, 1);
    }
  };

  static completion_handler_erasure_impl* make(Executor exec, Func&& func)
  {
    uninit_deleter_t deleter(func);
    std::unique_ptr<completion_handler_erasure_impl, uninit_deleter_t>
      uninit_ptr(std::allocator_traits<allocator_type>::allocate(
            deleter.allocator, 1), deleter);
    completion_handler_erasure_impl* ptr =
      new (uninit_ptr.get()) completion_handler_erasure_impl(
        std::move(exec), std::move(func));
    uninit_ptr.release();
    return ptr;
  }

  struct deleter_t
  {
    allocator_type allocator;

    deleter_t(const Func& func)
      : allocator(get_associated_allocator(func))
    {
    }

    void operator()(completion_handler_erasure_impl* p)
    {
      std::allocator_traits<allocator_type>::destroy(allocator, p);
      std::allocator_traits<allocator_type>::deallocate(allocator, p, 1);
    }
  };

  virtual Return call(Args... args) override
  {
    std::unique_ptr<completion_handler_erasure_impl,
      deleter_t> p(this, deleter_t(func));
    Func f(std::move(func));
    p.reset();
    std::move(f)(std::move(args)...);
  }

  virtual void destroy() override
  {
    std::unique_ptr<completion_handler_erasure_impl,
      deleter_t>(this, deleter_t(func));
  }

  Func func;
};

template<typename Signature, typename Executor = any_io_executor>
struct completion_handler_erasure;

template<typename Return, typename... Args, typename Executor>
struct completion_handler_erasure<Return(Args...), Executor>
{
  struct deleter_t
  {
    void operator()(
        completion_handler_erasure_base<Return(Args...), Executor>* p)
    {
      p->destroy();
    }
  };

  completion_handler_erasure(const completion_handler_erasure&) = delete;
  completion_handler_erasure(completion_handler_erasure&&) = default;
  completion_handler_erasure& operator=(
      const completion_handler_erasure&) = delete;
  completion_handler_erasure& operator=(
      completion_handler_erasure&&) = default;

  constexpr completion_handler_erasure() = default;

  constexpr completion_handler_erasure(nullptr_t)
    : completion_handler_erasure()
  {
  }

  template<typename Func>
  completion_handler_erasure(Executor exec, Func&& func)
    : impl_(completion_handler_erasure_impl<
        std::decay_t<Func>, Return(Args...), Executor>::make(
          std::move(exec), std::forward<Func>(func)))
  {
  }

  ~completion_handler_erasure()
  {
    if (impl_)
    {
      Executor executor(impl_->executor);
      boost::asio::dispatch(executor,
          [impl = std::move(impl_)]() mutable
          {
            impl.reset();
          });
    }
  }

  Return operator()(Args... args)
  {
    if (impl_)
      impl_.release()->call(std::move(args)...);
  }

  constexpr bool operator==(nullptr_t) const noexcept {return impl_ == nullptr;}
  constexpr bool operator!=(nullptr_t) const noexcept {return impl_ != nullptr;}
  constexpr bool operator!() const noexcept {return impl_ == nullptr;}

private:
  std::unique_ptr<
    completion_handler_erasure_base<Return(Args...), Executor>, deleter_t>
      impl_;
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_COMPLETION_HANDLER_ERASURE_HPP

/* completion_handler_erasure.hpp
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
*/