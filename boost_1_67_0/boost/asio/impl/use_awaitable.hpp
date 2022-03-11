//
// impl/use_awaitable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  awaitable_handler_base(awaitable<void, Executor> a, const Executor& ex)
    : awaitable_thread<Executor>(std::move(a), ex)
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
    return static_cast<awaitable_frame<T, Executor>*>(this->top_of_stack_);
  }
};

template <typename, typename...>
class awaitable_handler;

template <typename Executor>
class awaitable_handler<Executor, void>
  : public awaitable_handler_base<Executor, void>
{
public:
  using awaitable_handler_base<Executor, void>::awaitable_handler_base;

  void operator()()
  {
    this->frame()->attach_thread(this);
    this->frame()->return_void();
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
    this->frame()->pop_frame();
    this->pump();
  }
};

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename Executor, typename R, typename... Args>
class async_result<use_awaitable_t<Executor>, R(Args...)>
{
public:
  typedef typename detail::awaitable_handler<
      Executor, typename decay<Args>::type...> handler_type;
  typedef typename handler_type::awaitable_type return_type;

#if defined(_MSC_VER)
  template <typename T>
  static T dummy_return()
  {
    return std::move(*static_cast<T*>(nullptr));
  }

  template <>
  static void dummy_return()
  {
  }
#endif // defined(_MSC_VER)

  template <typename Initiation, typename... InitArgs>
  static return_type initiate(Initiation initiation,
      use_awaitable_t<Executor>, InitArgs... args)
  {
    co_await [&](auto* frame)
      {
        handler_type handler(frame->detach_thread());
        std::move(initiation)(std::move(handler), std::move(args)...);
        return static_cast<handler_type*>(nullptr);
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