//
// execution/detail/bulk_sender.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXECUTION_DETAIL_BULK_SENDER_HPP
#define BOOST_ASIO_EXECUTION_DETAIL_BULK_SENDER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/execution/connect.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution/set_done.hpp>
#include <boost/asio/execution/set_error.hpp>
#include <boost/asio/traits/connect_member.hpp>
#include <boost/asio/traits/set_done_member.hpp>
#include <boost/asio/traits/set_error_member.hpp>
#include <boost/asio/traits/set_value_member.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace execution {
namespace detail {

template <typename Receiver, typename Function, typename Number, typename Index>
struct bulk_receiver
{
  typename remove_cvref<Receiver>::type receiver_;
  typename decay<Function>::type f_;
  typename decay<Number>::type n_;

  template <typename R, typename F, typename N>
  explicit bulk_receiver(BOOST_ASIO_MOVE_ARG(R) r,
      BOOST_ASIO_MOVE_ARG(F) f, BOOST_ASIO_MOVE_ARG(N) n)
    : receiver_(BOOST_ASIO_MOVE_CAST(R)(r)),
      f_(BOOST_ASIO_MOVE_CAST(F)(f)),
      n_(BOOST_ASIO_MOVE_CAST(N)(n))
  {
  }

  void set_value()
  {
    for (Index i = 0; i < n_; ++i)
      f_(i);

    execution::set_value(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(receiver_));
  }

  template <typename Error>
  void set_error(BOOST_ASIO_MOVE_ARG(Error) e) BOOST_ASIO_NOEXCEPT
  {
    execution::set_error(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(receiver_),
        BOOST_ASIO_MOVE_CAST(Error)(e));
  }

  void set_done() BOOST_ASIO_NOEXCEPT
  {
    execution::set_done(
        BOOST_ASIO_MOVE_OR_LVALUE(
          typename remove_cvref<Receiver>::type)(receiver_));
  }
};

template <typename Sender, typename Receiver,
  typename Function, typename Number>
struct bulk_receiver_traits
{
  typedef bulk_receiver<
      Receiver, Function, Number,
      typename execution::executor_index<
        typename remove_cvref<Sender>::type
      >::type
    > type;

#if defined(BOOST_ASIO_HAS_MOVE)
  typedef type arg_type;
#else // defined(BOOST_ASIO_HAS_MOVE)
  typedef const type& arg_type;
#endif // defined(BOOST_ASIO_HAS_MOVE)
};

template <typename Sender, typename Function, typename Number>
struct bulk_sender : sender_base
{
  typename remove_cvref<Sender>::type sender_;
  typename decay<Function>::type f_;
  typename decay<Number>::type n_;

  template <typename S, typename F, typename N>
  explicit bulk_sender(BOOST_ASIO_MOVE_ARG(S) s,
      BOOST_ASIO_MOVE_ARG(F) f, BOOST_ASIO_MOVE_ARG(N) n)
    : sender_(BOOST_ASIO_MOVE_CAST(S)(s)),
      f_(BOOST_ASIO_MOVE_CAST(F)(f)),
      n_(BOOST_ASIO_MOVE_CAST(N)(n))
  {
  }

  template <typename Receiver>
  typename connect_result<
      BOOST_ASIO_MOVE_OR_LVALUE_TYPE(typename remove_cvref<Sender>::type),
      typename bulk_receiver_traits<
        Sender, Receiver, Function, Number
      >::arg_type
  >::type connect(BOOST_ASIO_MOVE_ARG(Receiver) r,
      typename enable_if<
        can_connect<
          typename remove_cvref<Sender>::type,
          typename bulk_receiver_traits<
            Sender, Receiver, Function, Number
          >::arg_type
        >::value
      >::type* = 0) BOOST_ASIO_RVALUE_REF_QUAL BOOST_ASIO_NOEXCEPT
  {
    return execution::connect(
        BOOST_ASIO_MOVE_OR_LVALUE(typename remove_cvref<Sender>::type)(sender_),
        typename bulk_receiver_traits<Sender, Receiver, Function, Number>::type(
          BOOST_ASIO_MOVE_CAST(Receiver)(r),
          BOOST_ASIO_MOVE_CAST(typename decay<Function>::type)(f_),
          BOOST_ASIO_MOVE_CAST(typename decay<Number>::type)(n_)));
  }

  template <typename Receiver>
  typename connect_result<
      const typename remove_cvref<Sender>::type&,
      typename bulk_receiver_traits<
        Sender, Receiver, Function, Number
      >::arg_type
  >::type connect(BOOST_ASIO_MOVE_ARG(Receiver) r,
      typename enable_if<
        can_connect<
          const typename remove_cvref<Sender>::type&,
          typename bulk_receiver_traits<
            Sender, Receiver, Function, Number
          >::arg_type
        >::value
      >::type* = 0) const BOOST_ASIO_LVALUE_REF_QUAL BOOST_ASIO_NOEXCEPT
  {
    return execution::connect(sender_,
        typename bulk_receiver_traits<Sender, Receiver, Function, Number>::type(
          BOOST_ASIO_MOVE_CAST(Receiver)(r), f_, n_));
  }
};

} // namespace detail
} // namespace execution
namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

template <typename Receiver, typename Function, typename Number, typename Index>
struct set_value_member<
    execution::detail::bulk_receiver<Receiver, Function, Number, Index>,
    void()>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_VALUE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)

template <typename Receiver, typename Function,
    typename Number, typename Index, typename Error>
struct set_error_member<
    execution::detail::bulk_receiver<Receiver, Function, Number, Index>,
    Error>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_ERROR_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)

template <typename Receiver, typename Function, typename Number, typename Index>
struct set_done_member<
    execution::detail::bulk_receiver<Receiver, Function, Number, Index> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_SET_DONE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_MEMBER_TRAIT)

template <typename Sender, typename Function,
    typename Number, typename Receiver>
struct connect_member<
    execution::detail::bulk_sender<Sender, Function, Number>,
    Receiver,
    typename enable_if<
      execution::can_connect<
        BOOST_ASIO_MOVE_OR_LVALUE_TYPE(typename remove_cvref<Sender>::type),
        typename execution::detail::bulk_receiver_traits<
          Sender, Receiver, Function, Number
        >::arg_type
      >::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef typename execution::connect_result<
      BOOST_ASIO_MOVE_OR_LVALUE_TYPE(typename remove_cvref<Sender>::type),
      typename execution::detail::bulk_receiver_traits<
        Sender, Receiver, Function, Number
      >::arg_type
    >::type result_type;
};

template <typename Sender, typename Function,
    typename Number, typename Receiver>
struct connect_member<
    const execution::detail::bulk_sender<Sender, Function, Number>,
    Receiver,
    typename enable_if<
      execution::can_connect<
        const typename remove_cvref<Sender>::type&,
        typename execution::detail::bulk_receiver_traits<
          Sender, Receiver, Function, Number
        >::arg_type
      >::value
    >::type>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef typename execution::connect_result<
      const typename remove_cvref<Sender>::type&,
      typename execution::detail::bulk_receiver_traits<
        Sender, Receiver, Function, Number
      >::arg_type
    >::type result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_CONNECT_MEMBER_TRAIT)

} // namespace traits
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXECUTION_DETAIL_BULK_SENDER_HPP

/* bulk_sender.hpp
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
*/