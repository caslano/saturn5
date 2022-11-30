//
// experimental/impl/promise.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2021-2022 Klemens D. Morgenstern
//                         (klemens dot morgenstern at gmx dot net)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_ASIO_EXPERIMENTAL_IMPL_PROMISE_HPP
#define BOOST_ASIO_EXPERIMENTAL_IMPL_PROMISE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/cancellation_signal.hpp>
#include <boost/asio/experimental/detail/completion_handler_erasure.hpp>
#include <tuple>
#include <optional>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

template<typename Signature = void(), typename Executor = any_io_executor>
struct promise;

namespace detail {

template<typename Signature, typename Executor>
struct promise_impl;

template<typename ... Ts, typename Executor>
struct promise_impl<void(Ts...), Executor>
{
  using result_type = std::tuple<Ts...>;

  promise_impl(Executor executor = {})
    : executor(std::move(executor))
  {
  }

  std::optional<result_type> result;
  bool done{false};
  detail::completion_handler_erasure<void(Ts...), Executor> completion;
  cancellation_signal cancel;
  Executor executor;
};

template<typename Signature = void(), typename Executor = any_io_executor>
struct promise_handler;

template<typename Signature, typename Executor>
struct promise_handler;

template<typename ... Ts, typename Executor>
struct promise_handler<void(Ts...), Executor>
{
  using promise_type = promise<void(Ts...), Executor>;

  promise_handler(Executor executor) // get_associated_allocator(exec)
    : impl_{
        std::allocate_shared<promise_impl<void(Ts...), Executor>>(
          get_associated_allocator(executor))}
  {
    impl_->executor = std::move(executor);
  }

  std::shared_ptr<promise_impl<void(Ts...), Executor>> impl_;

  using cancellation_slot_type = cancellation_slot;

  cancellation_slot_type get_cancellation_slot() const noexcept
  {
    return impl_->cancel.slot();
  }

  auto make_promise() -> promise<void(Ts...), Executor>
  {
    return {impl_};
  }

  void operator()(std::remove_reference_t<Ts>... ts)
  {
    assert(impl_);
    impl_->result.emplace(std::move(ts)...);
    impl_->done = true;
    if (auto f = std::exchange(impl_->completion, nullptr); f != nullptr)
      std::apply(std::move(f), std::move(*impl_->result));
  }
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_IMPL_PROMISE_HPP

/* promise.hpp
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
*/