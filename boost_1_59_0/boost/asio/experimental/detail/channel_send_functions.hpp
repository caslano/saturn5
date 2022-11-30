//
// experimental/detail/channel_send_functions.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SEND_FUNCTIONS_HPP
#define BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SEND_FUNCTIONS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/experimental/detail/channel_message.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

template <typename Derived, typename Executor, typename... Signatures>
class channel_send_functions;

template <typename Derived, typename Executor, typename R, typename... Args>
class channel_send_functions<Derived, Executor, R(Args...)>
{
public:
  template <typename... Args2>
  typename enable_if<
    is_constructible<detail::channel_message<R(Args...)>, int, Args2...>::value,
    bool
  >::type try_send(BOOST_ASIO_MOVE_ARG(Args2)... args)
  {
    typedef typename detail::channel_message<R(Args...)> message_type;
    Derived* self = static_cast<Derived*>(this);
    return self->service_->template try_send<message_type>(
        self->impl_, BOOST_ASIO_MOVE_CAST(Args2)(args)...);
  }

  template <typename... Args2>
  typename enable_if<
    is_constructible<detail::channel_message<R(Args...)>, int, Args2...>::value,
    std::size_t
  >::type try_send_n(std::size_t count, BOOST_ASIO_MOVE_ARG(Args2)... args)
  {
    typedef typename detail::channel_message<R(Args...)> message_type;
    Derived* self = static_cast<Derived*>(this);
    return self->service_->template try_send_n<message_type>(
        self->impl_, count, BOOST_ASIO_MOVE_CAST(Args2)(args)...);
  }

  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        CompletionToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
  auto async_send(Args... args,
      BOOST_ASIO_MOVE_ARG(CompletionToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor))
  {
    typedef typename Derived::payload_type payload_type;
    typedef typename detail::channel_message<R(Args...)> message_type;
    Derived* self = static_cast<Derived*>(this);
    return async_initiate<CompletionToken, void (boost::system::error_code)>(
        typename Derived::initiate_async_send(self), token,
        payload_type(message_type(0, BOOST_ASIO_MOVE_CAST(Args)(args)...)));
  }
};

template <typename Derived, typename Executor,
    typename R, typename... Args, typename... Signatures>
class channel_send_functions<Derived, Executor, R(Args...), Signatures...> :
  public channel_send_functions<Derived, Executor, Signatures...>
{
public:
  using channel_send_functions<Derived, Executor, Signatures...>::try_send;
  using channel_send_functions<Derived, Executor, Signatures...>::async_send;

  template <typename... Args2>
  typename enable_if<
    is_constructible<detail::channel_message<R(Args...)>, int, Args2...>::value,
    bool
  >::type try_send(BOOST_ASIO_MOVE_ARG(Args2)... args)
  {
    typedef typename detail::channel_message<R(Args...)> message_type;
    Derived* self = static_cast<Derived*>(this);
    return self->service_->template try_send<message_type>(
        self->impl_, BOOST_ASIO_MOVE_CAST(Args2)(args)...);
  }

  template <typename... Args2>
  typename enable_if<
    is_constructible<detail::channel_message<R(Args...)>, int, Args2...>::value,
    std::size_t
  >::type try_send_n(std::size_t count, BOOST_ASIO_MOVE_ARG(Args2)... args)
  {
    typedef typename detail::channel_message<R(Args...)> message_type;
    Derived* self = static_cast<Derived*>(this);
    return self->service_->template try_send_n<message_type>(
        self->impl_, count, BOOST_ASIO_MOVE_CAST(Args2)(args)...);
  }

  template <
      BOOST_ASIO_COMPLETION_TOKEN_FOR(void (boost::system::error_code))
        CompletionToken BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(Executor)>
  auto async_send(Args... args,
      BOOST_ASIO_MOVE_ARG(CompletionToken) token
        BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(Executor))
  {
    typedef typename Derived::payload_type payload_type;
    typedef typename detail::channel_message<R(Args...)> message_type;
    Derived* self = static_cast<Derived*>(this);
    return async_initiate<CompletionToken, void (boost::system::error_code)>(
        typename Derived::initiate_async_send(self), token,
        payload_type(message_type(0, BOOST_ASIO_MOVE_CAST(Args)(args)...)));
  }
};

} // namespace detail
} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DETAIL_CHANNEL_SEND_FUNCTIONS_HPP

/* channel_send_functions.hpp
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
*/