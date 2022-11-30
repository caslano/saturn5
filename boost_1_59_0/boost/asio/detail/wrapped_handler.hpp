//
// detail/wrapped_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP
#define BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/bind_handler.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

struct is_continuation_delegated
{
  template <typename Dispatcher, typename Handler>
  bool operator()(Dispatcher&, Handler& handler) const
  {
    return boost_asio_handler_cont_helpers::is_continuation(handler);
  }
};

struct is_continuation_if_running
{
  template <typename Dispatcher, typename Handler>
  bool operator()(Dispatcher& dispatcher, Handler&) const
  {
    return dispatcher.running_in_this_thread();
  }
};

template <typename Dispatcher, typename Handler,
    typename IsContinuation = is_continuation_delegated>
class wrapped_handler
{
public:
  typedef void result_type;

  wrapped_handler(Dispatcher dispatcher, Handler& handler)
    : dispatcher_(dispatcher),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  wrapped_handler(const wrapped_handler& other)
    : dispatcher_(other.dispatcher_),
      handler_(other.handler_)
  {
  }

  wrapped_handler(wrapped_handler&& other)
    : dispatcher_(other.dispatcher_),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    dispatcher_.dispatch(BOOST_ASIO_MOVE_CAST(Handler)(handler_));
  }

  void operator()() const
  {
    dispatcher_.dispatch(handler_);
  }

  template <typename Arg1>
  void operator()(const Arg1& arg1)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }

  template <typename Arg1>
  void operator()(const Arg1& arg1) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1));
  }

  template <typename Arg1, typename Arg2>
  void operator()(const Arg1& arg1, const Arg2& arg2)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }

  template <typename Arg1, typename Arg2>
  void operator()(const Arg1& arg1, const Arg2& arg2) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2));
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3)
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }

  template <typename Arg1, typename Arg2, typename Arg3>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3) const
  {
    dispatcher_.dispatch(detail::bind_handler(handler_, arg1, arg2, arg3));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4, const Arg5& arg5)
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

  template <typename Arg1, typename Arg2, typename Arg3, typename Arg4,
      typename Arg5>
  void operator()(const Arg1& arg1, const Arg2& arg2, const Arg3& arg3,
      const Arg4& arg4, const Arg5& arg5) const
  {
    dispatcher_.dispatch(
        detail::bind_handler(handler_, arg1, arg2, arg3, arg4, arg5));
  }

//private:
  Dispatcher dispatcher_;
  Handler handler_;
};

template <typename Handler, typename Context>
class rewrapped_handler
{
public:
  explicit rewrapped_handler(Handler& handler, const Context& context)
    : context_(context),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

  explicit rewrapped_handler(const Handler& handler, const Context& context)
    : context_(context),
      handler_(handler)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  rewrapped_handler(const rewrapped_handler& other)
    : context_(other.context_),
      handler_(other.handler_)
  {
  }

  rewrapped_handler(rewrapped_handler&& other)
    : context_(BOOST_ASIO_MOVE_CAST(Context)(other.context_)),
      handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    handler_();
  }

  void operator()() const
  {
    handler_();
  }

//private:
  Context context_;
  Handler handler_;
};

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline bool asio_handler_is_continuation(
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return IsContinuation()(this_handler->dispatcher_, this_handler->handler_);
}

template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Context>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    rewrapped_handler<Handler, Context>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Context>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->context_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Dispatcher, typename Context>
inline bool asio_handler_is_continuation(
    rewrapped_handler<Dispatcher, Context>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->context_);
}

template <typename Function, typename Handler, typename Context>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler, typename Context>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP

/* wrapped_handler.hpp
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
*/