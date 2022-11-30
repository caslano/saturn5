//
// execution/detail/as_receiver.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_DETAIL_AS_RECEIVER_HPP
#define BOOST_ASIO_EXECUTION_DETAIL_AS_RECEIVER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/traits/set_done_member.hpp>
#include <boost/asio/traits/set_error_member.hpp>
#include <boost/asio/traits/set_value_member.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

template <typename Function, typename>
struct as_receiver
{
  Function f_;

  template <typename F>
  explicit as_receiver(BOOST_ASIO_MOVE_ARG(F) f, int)
    : f_(BOOST_ASIO_MOVE_CAST(F)(f))
  {
  }

#if defined(BOOST_ASIO_MSVC) && defined(BOOST_ASIO_HAS_MOVE)
  as_receiver(as_receiver&& other)
    : f_(BOOST_ASIO_MOVE_CAST(Function)(other.f_))
  {
  }
#endif // defined(BOOST_ASIO_MSVC) && defined(BOOST_ASIO_HAS_MOVE)

  void set_value()
    BOOST_ASIO_NOEXCEPT_IF(noexcept(declval<Function&>()()))
  {
    f_();
  }

  template <typename E>
  void set_error(E) BOOST_ASIO_NOEXCEPT
  {
    std::terminate();
  }

  void set_done() BOOST_ASIO_NOEXCEPT
  {
  }
};

template <typename T>
struct is_as_receiver : false_type
{
};

template <typename Function, typename T>
struct is_as_receiver<as_receiver<Function, T> > : true_type
{
};

} // namespace detail
} // namespace execution
namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

template <typename Function, typename T>
struct set_value_member<
    boost::asio::execution::detail::as_receiver<Function, T>, void()>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
#if defined(BOOST_ASIO_HAS_NOEXCEPT)
  BOOST_ASIO_STATIC_CONSTEXPR(bool,
      is_noexcept = noexcept(declval<Function&>()()));
#else // defined(BOOST_ASIO_HAS_NOEXCEPT)
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
#endif // defined(BOOST_ASIO_HAS_NOEXCEPT)
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)

template <typename Function, typename T, typename E>
struct set_error_member<
    boost::asio::execution::detail::as_receiver<Function, T>, E>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)

template <typename Function, typename T>
struct set_done_member<
    boost::asio::execution::detail::as_receiver<Function, T> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_DETAIL_AS_RECEIVER_HPP

/* as_receiver.hpp
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
*/