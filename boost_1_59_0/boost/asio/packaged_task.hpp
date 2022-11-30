//
// packaged_task.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_PACKAGED_TASK_HPP
#define BOOST_ASIO_PACKAGED_TASK_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/future.hpp>

#if defined(BOOST_ASIO_HAS_STD_FUTURE_CLASS) \
  || defined(GENERATING_DOCUMENTATION)

#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)

/// Partial specialisation of @c async_result for @c std::packaged_task.
template <typename Result, typename... Args, typename Signature>
class async_result<std::packaged_task<Result(Args...)>, Signature>
{
public:
  /// The packaged task is the concrete completion handler type.
  typedef std::packaged_task<Result(Args...)> completion_handler_type;

  /// The return type of the initiating function is the future obtained from
  /// the packaged task.
  typedef std::future<Result> return_type;

  /// The constructor extracts the future from the packaged task.
  explicit async_result(completion_handler_type& h)
    : future_(h.get_future())
  {
  }

  /// Returns the packaged task's future.
  return_type get()
  {
    return std::move(future_);
  }

private:
  return_type future_;
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   || defined(GENERATING_DOCUMENTATION)

template <typename Result, typename Signature>
struct async_result<std::packaged_task<Result()>, Signature>
{
  typedef std::packaged_task<Result()> completion_handler_type;
  typedef std::future<Result> return_type;

  explicit async_result(completion_handler_type& h)
    : future_(h.get_future())
  {
  }

  return_type get()
  {
    return std::move(future_);
  }

private:
  return_type future_;
};

#define BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF(n) \
  template <typename Result, \
    BOOST_ASIO_VARIADIC_TPARAMS(n), typename Signature> \
  class async_result< \
    std::packaged_task<Result(BOOST_ASIO_VARIADIC_TARGS(n))>, Signature> \
  { \
  public: \
    typedef std::packaged_task< \
      Result(BOOST_ASIO_VARIADIC_TARGS(n))> \
        completion_handler_type; \
  \
    typedef std::future<Result> return_type; \
  \
    explicit async_result(completion_handler_type& h) \
      : future_(h.get_future()) \
    { \
    } \
  \
    return_type get() \
    { \
      return std::move(future_); \
    } \
  \
  private: \
    return_type future_; \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF)
#undef BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // defined(BOOST_ASIO_HAS_STD_FUTURE_CLASS)
       //   || defined(GENERATING_DOCUMENTATION)

#endif // BOOST_ASIO_PACKAGED_TASK_HPP

/* packaged_task.hpp
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
*/