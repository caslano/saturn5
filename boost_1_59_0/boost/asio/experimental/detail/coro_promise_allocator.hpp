//
// experimental/detail/coro_promise_allocator.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CORO_PROMISE_ALLOCATOR_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CORO_PROMISE_ALLOCATOR_HPP

#include <boost/asio/detail/config.hpp>
#include <boost/asio/experimental/coro_traits.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Coroutine,
     typename Executor = typename Coroutine::executor_type,
     typename Allocator = typename std::allocator_traits<
       associated_allocator_t<Executor>>:: template rebind_alloc<std::byte>,
     bool Noexcept = noexcept(std::declval<Allocator>().allocate(0u))>
struct coro_promise_allocator
{
  using allocator_type = Allocator;

  template <typename... Args>
  void* operator new(const std::size_t size, Executor executor, Args&&...)
  {
    static_assert(std::is_nothrow_move_constructible_v<allocator_type>);
    allocator_type alloc{get_associated_allocator(executor)};

    const auto csize = size + sizeof(alloc);
    const auto raw =
      std::allocator_traits<allocator_type>::allocate(alloc, csize);
    new (raw) allocator_type(std::move(alloc));
    return static_cast<std::byte*>(raw) + sizeof(alloc);
  }

  template <execution_context Context, typename... Args>
  void* operator new(const std::size_t size, Context&& ctx, Args&&... args)
  {
    return coro_promise_allocator::operator new(size,
        ctx.get_executor(), std::forward<Args>(args)...);
  }

  void operator delete(void* raw, std::size_t size )
  {
    auto * alloc_p = static_cast<allocator_type*>(raw);

    auto alloc = std::move(*alloc_p);
    alloc_p->~allocator_type();
    std::allocator_traits<allocator_type>::deallocate(alloc,
        static_cast<std::byte*>(raw), size + sizeof(allocator_type));
  }
};

template <typename Coroutine, typename Executor>
struct coro_promise_allocator<Coroutine,
    Executor, std::allocator<std::byte>, false>
{

};

template <typename Coroutine, typename Executor, typename Allocator>
struct coro_promise_allocator<Coroutine, Executor, Allocator, true>
{
  using allocator_type = Allocator;

  template <typename... Args>
  void* operator new(const std::size_t size,
      Executor executor, Args&&...) noexcept
  {
    static_assert(std::is_nothrow_move_constructible_v<allocator_type>);
    allocator_type alloc{get_associated_allocator(executor)};

    const auto csize = size + sizeof(alloc);
    const auto raw =
      std::allocator_traits<allocator_type>::allocate(alloc, csize);
    if (raw == nullptr)
      return nullptr;
    new (raw) allocator_type(std::move(alloc));
    return static_cast<std::byte*>(raw) + sizeof(alloc);
  }

  template <execution_context Context, typename... Args>
  void* operator new(const std::size_t size,
      Context&& ctx, Args&&... args) noexcept
  {
    return coro_promise_allocator::operator new(size,
        ctx.get_executor(), std::forward<Args>(args)...);
  }

  void operator delete(void* raw, std::size_t size) noexcept
  {
    auto * alloc_p = static_cast<allocator_type*>(raw);
    auto alloc = std::move(*alloc_p);
    alloc_p->~allocator_type();
    const auto csize = size + sizeof(allocator_type);
    std::allocator_traits<allocator_type>::deallocate(alloc,
        static_cast<std::byte*>(raw) - sizeof(allocator_type), csize);
  }

  static auto get_return_object_on_allocation_failure() noexcept -> Coroutine
  {
    return Coroutine{};
  }
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CORO_PROMISE_ALLOCATOR_HPP

/* coro_promise_allocator.hpp
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
*/