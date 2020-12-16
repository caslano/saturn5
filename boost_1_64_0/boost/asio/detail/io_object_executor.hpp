//
// io_object_executor.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_IO_OBJECT_EXECUTOR_HPP
#define BOOST_ASIO_DETAIL_IO_OBJECT_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/io_context.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Wrap the (potentially polymorphic) executor so that we can bypass it when
// dispatching on a target executor that has a native I/O implementation.
template <typename Executor>
class io_object_executor
{
public:
  io_object_executor(const Executor& ex,
      bool native_implementation) BOOST_ASIO_NOEXCEPT
    : executor_(ex),
      has_native_impl_(native_implementation)
  {
  }

  io_object_executor(const io_object_executor& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.executor_),
      has_native_impl_(other.has_native_impl_)
  {
  }

  template <typename Executor1>
  io_object_executor(
      const io_object_executor<Executor1>& other) BOOST_ASIO_NOEXCEPT
    : executor_(other.inner_executor()),
      has_native_impl_(other.has_native_implementation())
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  io_object_executor(io_object_executor&& other) BOOST_ASIO_NOEXCEPT
    : executor_(BOOST_ASIO_MOVE_CAST(Executor)(other.executor_)),
      has_native_impl_(other.has_native_impl_)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  const Executor& inner_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_;
  }

  bool has_native_implementation() const BOOST_ASIO_NOEXCEPT
  {
    return has_native_impl_;
  }

  execution_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return executor_.context();
  }

  void on_work_started() const BOOST_ASIO_NOEXCEPT
  {
    if (is_same<Executor, io_context::executor_type>::value
        || has_native_impl_)
    {
      // When using a native implementation, work is already counted by the
      // execution context.
    }
    else
    {
      executor_.on_work_started();
    }
  }

  void on_work_finished() const BOOST_ASIO_NOEXCEPT
  {
    if (is_same<Executor, io_context::executor_type>::value
        || has_native_impl_)
    {
      // When using a native implementation, work is already counted by the
      // execution context.
    }
    else
    {
      executor_.on_work_finished();
    }
  }

  template <typename F, typename A>
  void dispatch(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    if (is_same<Executor, io_context::executor_type>::value
        || has_native_impl_)
    {
      // When using a native implementation, I/O completion handlers are
      // already dispatched according to the execution context's executor's
      // rules. We can call the function directly.
#if defined(BOOST_ASIO_HAS_MOVE)
      if (is_same<F, typename decay<F>::type>::value)
      {
        boost_asio_handler_invoke_helpers::invoke(f, f);
        return;
      }
#endif // defined(BOOST_ASIO_HAS_MOVE)
      typename decay<F>::type function(BOOST_ASIO_MOVE_CAST(F)(f));
      boost_asio_handler_invoke_helpers::invoke(function, function);
    }
    else
    {
      executor_.dispatch(BOOST_ASIO_MOVE_CAST(F)(f), a);
    }
  }

  template <typename F, typename A>
  void post(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    executor_.post(BOOST_ASIO_MOVE_CAST(F)(f), a);
  }

  template <typename F, typename A>
  void defer(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    executor_.defer(BOOST_ASIO_MOVE_CAST(F)(f), a);
  }

  friend bool operator==(const io_object_executor& a,
      const io_object_executor& b) BOOST_ASIO_NOEXCEPT
  {
    return a.executor_ == b.executor_
      && a.has_native_impl_ == b.has_native_impl_;
  }

  friend bool operator!=(const io_object_executor& a,
      const io_object_executor& b) BOOST_ASIO_NOEXCEPT
  {
    return a.executor_ != b.executor_
      || a.has_native_impl_ != b.has_native_impl_;
  }

private:
  Executor executor_;
  const bool has_native_impl_;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_IO_OBJECT_EXECUTOR_HPP

/* io_object_executor.hpp
QId3f8596fBRz9tnHT4Naa+u//sF+6x7uO0l34gOfxd5HR76sndVhzdrWL8OT8C0OPcVz3qld0PX+Nuv+x50+NY1ftt1eMw73m9des/9ve+3aG/7/4HfcwzV4VvXGad7/Ym/P+jcZ/Zpvd+3Ed5JHrNhJvXX1ZZM+tvXM2mxMdUBmTRk50xaoeu76d0zqanLvM/wTCrr8J/2yqTZOrwWd+riiEw6eGQmDTNnhY/cJ5MK0fwGRuu0byYNRGGkNfOpKDoevg5TdPiTfCbN1OHO/TKpqsNbY6EOj8FyHS5gvQ6PRX/zh4/EUN3kCwuZNC6uOzaTdj88kybrGv9lXCbN0rkjnIsFOjz4yExaosN9x9sHHZ6AzD5dva5igO45OpPmHZtJ3br600x672fWp/MTMukSTIwxvM9xmVTSTf7W8e5Rd/NRmKFL/DZm6+wJmXTHiZk0J8afZM5JmdSIMadk0tOnZlItzj0tk9KZ2Df+HphJW01x3bwxvAjjdYM/xySd/VUm7YTJOs8/wdQYzw9iRYznTzHKnOmsTDr2bHPG/PzJVM9LF87J+M8Wel46e14mPYEZOjywnEk9Onw85se5/O1f209d5MuxVPfwfVgfY/gltFpDkzc6P5P6xJr5WvTTdd7uAntufJ6PxlBd4h4M01WeNS2TpsW98LG/sc86fN10z0yH/43FMefFmbTfbzNppQ6fhPU6POYS192vq9djMVSHL0BeN3m7S/1zOnza7+yzDvdgmi5clkln/MHexpov1xihK/waBrlWmplJO1xh/brCq7DYubkrM2kkZsU8fMIfM2murvKTqOsGf44enZ2VSTejFsdnOY7lcfyqTDoQg/bv6vUJGK7Dff/k+9HhrTBRh3fDVF3jz9AwT/ja2Zm0TofvQtaYdI13GxUd/gxzdfir11qPLvIVWKrDb2ONDn+J1gO8z3/OpF+gv67wfcjpOr+GITp823XWr8OLMUEXrjceU3R4GWbp8FZzPHcd3h6LdXgMVsT8/M2/WsOorl4/gf463O8Gz0WHF2GMDj+FCTr8Fqbo8LuYocMfoKrDH6Ouw603unfdwyPn+m2xhhL/4Cb3+B3r4UNu9pupw8fM893p8C8wRTd4q1tcSxe4hJm6wn9DRlf5oFs9I13ii5FiDN+EFbrGc2/zbcY81Uw6C7NjDN+E1gON4eVYGNfl8+7wm6+bvO/f3Ysu8jIMMj7d6XcVfXSDP8V6Y3J3ZdL5mKN7+FGsjDl5i7u9G7qbP8bYA/U9fqswRufmZ9IzGK6z92bSVZgQY+7LpCsxWVe57X7vbYzn1ZgWvcD7+6D90ZV/2JN/umdd4x0eticHOc79F0Ln+TwM0eF/YoQO933EnyM6/Cgm6/BTqOjwp5ijS4s8CyxwrfCMR92jDl+PNbrJMxb7nTS+xsMf8yx0kZdjqU6Pe+ZYoXt4gyf8c6PdF++Fhs7z0VitS/w7NHUPP4h1us67LHG/3/Ws+SRkdIkfQFaHj3vSd6fDZYzQdT7iX56LrvGuT3t2sW/81jPm1/l/e+b/MY9rlfm1ZfYw1vasP4uR10U+C6NjDF+NQqyN+y63tzp8MSbq8N9R1k0+/Tnfte7hf2OubvCnqOr0vDEv2M+Ykwev8O5Zc5Gvx2Td5P1e9Fsdx/lxzIjjfMVLfkt1jQc0zKnL3IMJcZxfxNIYz31f8bx0jkdimi7wKVihy3wN1ugqP4mVusGfY6rOvppJO2KtzvMZaD24q9drMECH02t+i3Q3/wKjdYXXoaDDp620bzr8G5R1nR9e4/3XtXe9z5/Ynzh3vd9MrIgx/BpW6vCRn1uPDt+P7CFdvX4OQ3T4Y4zQ+S+Mxyxd4je/NI8=
*/