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
crPy8bPl1meA1f4cbvFW+3O4xVntz+HW32p/DjcrH2863Kx8vOJw62O1P4eblY/dDrdYq/053GKs9me59R5gtT+HW7zV/hxucVb7c7hZ+VjlcLPysdThZuVjkcPNykeOw83KxzyHm5WPFIdbjNX+LLdYKx+THG7xVvtzuMVZ7c/hZuUjzuFm5aOXw83KR1eHm5WPDg43Kx8tHW5WPpo63HQ+mqj2Z7kN0Pqv19n1eK3/bOlxWv/O0vtr/UtL76f1jy29r/42o4E+tv42zhr7LfPxNhZ67mO2nsdgf78xRs9jqt7GbL2PtebpsdYPIso2p1xfuLHq7ws/6zjojpnexlq9jUl6G1P1Nhb67x9j9zzW6m0M/NzH2D2P2Z772Oy5jqXrvUD87Pcm5n1OFbwD2esnezPJGFqYjJG1hl3go7L3bFsYLXov2B72Fz0OhsPBog+BF8BRoo+GEXCi6JNgFzhN9OkwEs4UPQV2h3NFnwejYLboOTAaLhR9EYyB14pOk9NjHCtFXwX7wjWir4X94R2ib4DxcLPoW+BAuE307XAQfFj0R+Bg+KTou2ECfE50moYeA3lZ9FfgCPiG6G/CUfA90f8Mx8C/iP4xHAu/EP1LOB5+K/p3cCI8JfrPMBH+Ivqv8BJYz2bq9WESbCJ6UzgNthC9JUyG7UXvAC+DXUTvCmfAaNF7wZmwv+hxMBUOFn0InAVHiT4azoETRZ8E58Jpok+HGXCm6CnwSjhX9HlwAcwWPQfmwIWiL4JXwWtFXwrz4UrRV8FCVf82qX+4SNW/6BvgYrhZ9C1wiap/0bfDa1T9i/4IXKrqX/TdcJmqf9Gfh8tV/Yv+Crxe1b/ob8JVqv5tUv/wRlX/on8Mb1b1b5P6h7eo+hf9O7gWnhL9Z3irqn/Rf4W3w3o+Uv9wPWwielO4AbYQvSW8C7YXvQO8G3YRvSu8B0aL3gtugf1Fj4P3wsGiD4H3w1Gij4YPwImiT4Lb4TTRp8M/wJmip8CH4FzR58FHYLboCb41rr0q41+uY1sVg5zHtFzGsWT8yuPYldcxKxmjYmzK67iUjEk5j0dVH3dyHnNyH2+6Idp5fMl9XOl0tPt4kvtYkvs40hHkjJIEa8xIxoqsMSIZG7KPB519LOgElPEft7GfwFhEjbFA93GecxvjcR7TSe5tjeXoMRwPYzdnHbfxMmYj4zVnH6uxj9NEIe5jMrUfjymFbWE8ImMvjLu4j7mchkcVEeexlQQkdIw1lsI4ivMYiuv4yeGv6sY66v7q/ur+6v7q/ur+6v7q/ur+6v7q/ur+6v5q//efG//Py/89xv9bM97+LS+ry3nZxZd/6XPTCrMKSLwwv0D7fYdfhfbjgAVp2XPS8uaoY7bA73v8qipNv4K0WVnphqG/J3ixh2GtwxEva4Kp92MdYXP4o0rz6maG/XuCpEumTkli7R0SdpmzaGhdf0Mg4WOtdQC/1/pPNkf4uVlp8/K1fzMrfCdrHbnPtB5vs6+fc2+x0ocavWQtj8Yheh69NY8y0WZPo5e1ltx3Wv9FHzMySH/jkLYgXdaes8JHaX06+gmt/+pkY1revFg1XjYyeBL+kZadNsptRHCZ5N+3noTt7QgbUy3sDgnbSBWOKv8FuUZrWeNnxBIVbqOtHyEvMlryXjvEKldD5oK2lrUB/ibl6GM0I2Sw0Z3a7MKM0Abq/TSvRF6iLgN9OwU0CegcMLKej28Q7B7QmUXqfP2qpWmtIdBaHz9QHyOYX120vttow4jCbI6x3PDV9jTVtivLDZ2nGBjCsffRRlI59ss9XOf1T5J5/Urai43lhHuFcL4lTwVE8J+yLCSU9ol/Bn47kf0qnfolHwQ2aOQ=
*/