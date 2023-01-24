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
9LMppsg1ZSWavpf5w1TA/MDFRBY65ZUUAgms5TKIpePmLCav/7ZsJ+bB8u6KTXngLNP6j/nHtFAA4j+4ILmZ8KZDYV0Ajdai3YWEzxLIrUXdZVYpW4EcisTc3Y9bUkbz7v0/JxxrWorYIWcF7X5XX8CxMIOLRBDCpJw5V5vZM9Yf4NYaZCHa5w4acaW6PQd9fxSbcV7S6LyTfGbqoJf4Ph7bJ1dPVJBcxSZPTkkQmF26ikf3WnUvy+WfT3NbAbn4eLdBO9p3tcZUfpYZ/OF0Nk8j/pvf320gc9wDvCzDDc/Rgiv8z4fTJabNq8+F7QDqbe5Yl0ycUAGbltrsIaTX84iH31KT1be05AXyFHQyB2HPcUHqVkiN06jpq9EqH0QSGYkZyw06kTYg6Qx6GSQLvmSr9nbPzcZSA76IHvU7Raa+OwibEXUfbRa1FMoDsI5l4OqjbhB1xERIKPI5ziYqHoMwfUo/e8sFHMqJlbVDWIqw2ga2oL6Iml+K9Cgk+gU+uvCURiDSEO7u5tn1bGFRreIklF9wXftRIkvLTBFFq/tSTyao30kZwwZa1Z4QfH9xACiL+Tzm843kfbcn465IapebSmAgN7kZiyC9KAvT7GiTKnx4KA79JvO8nw9KGZiZnaz9Ea8NDxg8Lmbd7YiZ6IDhwPSovE3a1v1EiPx1ihWTAJoJfTB/n5QCI6JvPnS1pZ37VeWey245Vs4J
*/