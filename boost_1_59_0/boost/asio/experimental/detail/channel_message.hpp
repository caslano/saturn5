//
// experimental/detail/channel_message.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_MESSAGE_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_MESSAGE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <tuple>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Signature>
class channel_message;

template <typename R>
class channel_message<R()>
{
public:
  channel_message(int)
  {
  }

  template <typename Handler>
  void receive(Handler& handler)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler)();
  }
};

template <typename R, typename Arg0>
class channel_message<R(Arg0)>
{
public:
  template <typename T0>
  channel_message(int, BOOST_ASIO_MOVE_ARG(T0) t0)
    : arg0_(BOOST_ASIO_MOVE_CAST(T0)(t0))
  {
  }

  template <typename Handler>
  void receive(Handler& handler)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler)(
        BOOST_ASIO_MOVE_CAST(arg0_type)(arg0_));
  }

private:
  typedef typename decay<Arg0>::type arg0_type;
  arg0_type arg0_;
};

template <typename R, typename Arg0, typename Arg1>
class channel_message<R(Arg0, Arg1)>
{
public:
  template <typename T0, typename T1>
  channel_message(int, BOOST_ASIO_MOVE_ARG(T0) t0, BOOST_ASIO_MOVE_ARG(T1) t1)
    : arg0_(BOOST_ASIO_MOVE_CAST(T0)(t0)),
      arg1_(BOOST_ASIO_MOVE_CAST(T1)(t1))
  {
  }

  template <typename Handler>
  void receive(Handler& handler)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler)(
        BOOST_ASIO_MOVE_CAST(arg0_type)(arg0_),
        BOOST_ASIO_MOVE_CAST(arg1_type)(arg1_));
  }

private:
  typedef typename decay<Arg0>::type arg0_type;
  arg0_type arg0_;
  typedef typename decay<Arg1>::type arg1_type;
  arg1_type arg1_;
};

template <typename R, typename... Args>
class channel_message<R(Args...)>
{
public:
  template <typename... T>
  channel_message(int, BOOST_ASIO_MOVE_ARG(T)... t)
    : args_(BOOST_ASIO_MOVE_CAST(T)(t)...)
  {
  }

  template <typename Handler>
  void receive(Handler& h)
  {
    std::apply(BOOST_ASIO_MOVE_OR_LVALUE(Handler)(h),
        BOOST_ASIO_MOVE_CAST(args_type)(args_));
  }

private:
  typedef std::tuple<typename decay<Args>::type...> args_type;
  args_type args_;
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_MESSAGE_HPP

/* channel_message.hpp
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
*/