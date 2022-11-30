//
// impl/use_awaitable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_USE_AWAITABLE_HPP
#define BOOST_ASIO_IMPL_USE_AWAITABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/cancellation_signal.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Executor, typename T>
class awaitable_handler_base
  : public awaitable_thread<Executor>
{
public:
  typedef void result_type;
  typedef awaitable<T, Executor> awaitable_type;

  // Construct from the entry point of a new thread of execution.
  awaitable_handler_base(awaitable<awaitable_thread_entry_point, Executor> a,
      const Executor& ex, cancellation_slot pcs, cancellation_state cs)
    : awaitable_thread<Executor>(std::move(a), ex, pcs, cs)
  {
  }

  // Transfer ownership from another awaitable_thread.
  explicit awaitable_handler_base(awaitable_thread<Executor>* h)
    : awaitable_thread<Executor>(std::move(*h))
  {
  }

protected:
  awaitable_frame<T, Executor>* frame() noexcept
  {
    return static_cast<awaitable_frame<T, Executor>*>(
        this->entry_point()->top_of_stack_);
  }
};

template <typename, typename...>
class awaitable_handler;

template <typename Executor>
class awaitable_handler<Executor>
  : public awaitable_handler_base<Executor, void>
{
public:
  using awaitable_handler_base<Executor, void>::awaitable_handler_base;

  void operator()()
  {
    this->frame()->attach_thread(this);
    this->frame()->return_void();
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor>
class awaitable_handler<Executor, boost::system::error_code>
  : public awaitable_handler_base<Executor, void>
{
public:
  using awaitable_handler_base<Executor, void>::awaitable_handler_base;

  void operator()(const boost::system::error_code& ec)
  {
    this->frame()->attach_thread(this);
    if (ec)
      this->frame()->set_error(ec);
    else
      this->frame()->return_void();
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor>
class awaitable_handler<Executor, std::exception_ptr>
  : public awaitable_handler_base<Executor, void>
{
public:
  using awaitable_handler_base<Executor, void>::awaitable_handler_base;

  void operator()(std::exception_ptr ex)
  {
    this->frame()->attach_thread(this);
    if (ex)
      this->frame()->set_except(ex);
    else
      this->frame()->return_void();
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor, typename T>
class awaitable_handler<Executor, T>
  : public awaitable_handler_base<Executor, T>
{
public:
  using awaitable_handler_base<Executor, T>::awaitable_handler_base;

  template <typename Arg>
  void operator()(Arg&& arg)
  {
    this->frame()->attach_thread(this);
    this->frame()->return_value(std::forward<Arg>(arg));
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor, typename T>
class awaitable_handler<Executor, boost::system::error_code, T>
  : public awaitable_handler_base<Executor, T>
{
public:
  using awaitable_handler_base<Executor, T>::awaitable_handler_base;

  template <typename Arg>
  void operator()(const boost::system::error_code& ec, Arg&& arg)
  {
    this->frame()->attach_thread(this);
    if (ec)
      this->frame()->set_error(ec);
    else
      this->frame()->return_value(std::forward<Arg>(arg));
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor, typename T>
class awaitable_handler<Executor, std::exception_ptr, T>
  : public awaitable_handler_base<Executor, T>
{
public:
  using awaitable_handler_base<Executor, T>::awaitable_handler_base;

  template <typename Arg>
  void operator()(std::exception_ptr ex, Arg&& arg)
  {
    this->frame()->attach_thread(this);
    if (ex)
      this->frame()->set_except(ex);
    else
      this->frame()->return_value(std::forward<Arg>(arg));
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor, typename... Ts>
class awaitable_handler
  : public awaitable_handler_base<Executor, std::tuple<Ts...>>
{
public:
  using awaitable_handler_base<Executor,
    std::tuple<Ts...>>::awaitable_handler_base;

  template <typename... Args>
  void operator()(Args&&... args)
  {
    this->frame()->attach_thread(this);
    this->frame()->return_values(std::forward<Args>(args)...);
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor, typename... Ts>
class awaitable_handler<Executor, boost::system::error_code, Ts...>
  : public awaitable_handler_base<Executor, std::tuple<Ts...>>
{
public:
  using awaitable_handler_base<Executor,
    std::tuple<Ts...>>::awaitable_handler_base;

  template <typename... Args>
  void operator()(const boost::system::error_code& ec, Args&&... args)
  {
    this->frame()->attach_thread(this);
    if (ec)
      this->frame()->set_error(ec);
    else
      this->frame()->return_values(std::forward<Args>(args)...);
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

template <typename Executor, typename... Ts>
class awaitable_handler<Executor, std::exception_ptr, Ts...>
  : public awaitable_handler_base<Executor, std::tuple<Ts...>>
{
public:
  using awaitable_handler_base<Executor,
    std::tuple<Ts...>>::awaitable_handler_base;

  template <typename... Args>
  void operator()(std::exception_ptr ex, Args&&... args)
  {
    this->frame()->attach_thread(this);
    if (ex)
      this->frame()->set_except(ex);
    else
      this->frame()->return_values(std::forward<Args>(args)...);
    this->frame()->clear_cancellation_slot();
    this->frame()->pop_frame();
    this->pump();
  }
};

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

#if defined(_MSC_VER)
template <typename T>
T dummy_return()
{
  return std::move(*static_cast<T*>(nullptr));
}

template <>
inline void dummy_return()
{
}
#endif // defined(_MSC_VER)

template <typename Executor, typename R, typename... Args>
class async_result<use_awaitable_t<Executor>, R(Args...)>
{
public:
  typedef typename detail::awaitable_handler<
      Executor, typename decay<Args>::type...> handler_type;
  typedef typename handler_type::awaitable_type return_type;

  template <typename Initiation, typename... InitArgs>
#if defined(__APPLE_CC__) && (__clang_major__ == 13)
  __attribute__((noinline))
#endif // defined(__APPLE_CC__) && (__clang_major__ == 13)
  static handler_type* do_init(
      detail::awaitable_frame_base<Executor>* frame, Initiation& initiation,
      use_awaitable_t<Executor> u, InitArgs&... args)
  {
    (void)u;
    BOOST_ASIO_HANDLER_LOCATION((u.file_name_, u.line_, u.function_name_));
    handler_type handler(frame->detach_thread());
    std::move(initiation)(std::move(handler), std::move(args)...);
    return nullptr;
  }

  template <typename Initiation, typename... InitArgs>
  static return_type initiate(Initiation initiation,
      use_awaitable_t<Executor> u, InitArgs... args)
  {
    co_await [&] (auto* frame)
      {
        return do_init(frame, initiation, u, args...);
      };

    for (;;) {} // Never reached.
#if defined(_MSC_VER)
    co_return dummy_return<typename return_type::value_type>();
#endif // defined(_MSC_VER)
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_USE_AWAITABLE_HPP

/* use_awaitable.hpp
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
*/