//
// execution/detail/as_invocable.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_DETAIL_AS_INVOCABLE_HPP
#define BOOST_ASIO_EXECUTION_DETAIL_AS_INVOCABLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/receiver_invocation_error.hpp>
#include <boost/asio/execution/set_done.hpp>
#include <boost/asio/execution/set_error.hpp>
#include <boost/asio/execution/set_value.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

#if defined(BOOST_ASIO_HAS_MOVE)

template <typename Receiver, typename>
struct as_invocable
{
  Receiver* receiver_;

  explicit as_invocable(Receiver& r) BOOST_ASIO_NOEXCEPT
    : receiver_(boost::asio::detail::addressof(r))
  {
  }

  as_invocable(as_invocable&& other) BOOST_ASIO_NOEXCEPT
    : receiver_(other.receiver_)
  {
    other.receiver_ = 0;
  }

  ~as_invocable()
  {
    if (receiver_)
      execution::set_done(BOOST_ASIO_MOVE_OR_LVALUE(Receiver)(*receiver_));
  }

  void operator()() BOOST_ASIO_LVALUE_REF_QUAL BOOST_ASIO_NOEXCEPT
  {
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    try
    {
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
      execution::set_value(BOOST_ASIO_MOVE_CAST(Receiver)(*receiver_));
      receiver_ = 0;
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    }
    catch (...)
    {
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
      execution::set_error(BOOST_ASIO_MOVE_CAST(Receiver)(*receiver_),
          std::make_exception_ptr(receiver_invocation_error()));
      receiver_ = 0;
#else // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
      std::terminate();
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
    }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }
};

#else // defined(BOOST_ASIO_HAS_MOVE)

template <typename Receiver, typename>
struct as_invocable
{
  Receiver* receiver_;
  boost::asio::detail::shared_ptr<boost::asio::detail::atomic_count> ref_count_;

  explicit as_invocable(Receiver& r,
      const boost::asio::detail::shared_ptr<
        boost::asio::detail::atomic_count>& c) BOOST_ASIO_NOEXCEPT
    : receiver_(boost::asio::detail::addressof(r)),
      ref_count_(c)
  {
  }

  as_invocable(const as_invocable& other) BOOST_ASIO_NOEXCEPT
    : receiver_(other.receiver_),
      ref_count_(other.ref_count_)
  {
    ++(*ref_count_);
  }

  ~as_invocable()
  {
    if (--(*ref_count_) == 0)
      execution::set_done(*receiver_);
  }

  void operator()() BOOST_ASIO_LVALUE_REF_QUAL BOOST_ASIO_NOEXCEPT
  {
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    try
    {
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
      execution::set_value(*receiver_);
      ++(*ref_count_);
    }
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    catch (...)
    {
#if defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
      execution::set_error(*receiver_,
          std::make_exception_ptr(receiver_invocation_error()));
      ++(*ref_count_);
#else // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
      std::terminate();
#endif // defined(BOOST_ASIO_HAS_STD_EXCEPTION_PTR)
    }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

template <typename T>
struct is_as_invocable : false_type
{
};

template <typename Function, typename T>
struct is_as_invocable<as_invocable<Function, T> > : true_type
{
};

} // namespace detail
} // namespace execution
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_DETAIL_AS_INVOCABLE_HPP

/* as_invocable.hpp
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
*/