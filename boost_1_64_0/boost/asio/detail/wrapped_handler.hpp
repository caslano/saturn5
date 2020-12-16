//
// detail/wrapped_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
inline void* asio_handler_allocate(std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Dispatcher, typename Handler, typename IsContinuation>
inline bool asio_handler_is_continuation(
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  return IsContinuation()(this_handler->dispatcher_, this_handler->handler_);
}

template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline void asio_handler_invoke(Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
}

template <typename Function, typename Dispatcher,
    typename Handler, typename IsContinuation>
inline void asio_handler_invoke(const Function& function,
    wrapped_handler<Dispatcher, Handler, IsContinuation>* this_handler)
{
  this_handler->dispatcher_.dispatch(
      rewrapped_handler<Function, Handler>(
        function, this_handler->handler_));
}

template <typename Handler, typename Context>
inline void* asio_handler_allocate(std::size_t size,
    rewrapped_handler<Handler, Context>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->context_);
}

template <typename Handler, typename Context>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->context_);
}

template <typename Dispatcher, typename Context>
inline bool asio_handler_is_continuation(
    rewrapped_handler<Dispatcher, Context>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->context_);
}

template <typename Function, typename Handler, typename Context>
inline void asio_handler_invoke(Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
}

template <typename Function, typename Handler, typename Context>
inline void asio_handler_invoke(const Function& function,
    rewrapped_handler<Handler, Context>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->context_);
}

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_WRAPPED_HANDLER_HPP

/* wrapped_handler.hpp
M4SsO/CLTigmbCfsIzQQTt/RuqbU+mv9ne/fv+b9f2Vlmbz9n5v/f+v9f/nvzLv93CkLZ8+YMlnf/tVP/8d4xprGJm9S7BxYrO7C9SV8HV3yv07+qKQVl6wq2lB2Nr2iWN4Voanpwb762TqunjsT7+hTZxcWbaiRMh6InYd/3ZNuGtFLy8h00pCd8pWH/N/b0zSrrkv0sa1LZPu8hy8dE+J+YN47TQPsPsv/7HwXhL7l7+F/1nc5u7/LujYBfuUneNuViD/trN83sVbi8w6+jL7I8+mLlvrUtuo6oHWNIKQpFlJX1FXXtVPmT5s9+ew3C64TH1Prtd8t+kvMWauPSjzZtKsogfcUymYc1jvauVnflcu1XxYTiqDb79tO6RU52/BB8deC7ON2kX7W9ln5Bhu/lS9IfLwzj7Cr714mz0BzBugHEp8SyiDPh02esoqKdRuidp/RDUJ3rcTzTTlZkm+PybexpLJ0leObw78WuoskPsfkG2P6P6T9P4201yUtx/R3YRxny6zvEcMv/W36SP0kmeumH3rp+/yHzXXDq6RNA/domuHH+N7R78LrO//79WzRLYS8XMIU5zgWFRfnFFaWbKxYV1Js/D+maV/ZzgFdL/lKQrnme+Ralp5bqZA8FGS9Q5v03uZc0lKJV3DuOSxniWqRtRraeaGcExpjPxMqZb6Y6fUBVC1ldDLyf7fEe8q5IqvMuylzgJyrzTJlLnD4E433vD3jANIf0tf2s0UVck34dXwTYGt77/rrKmTopKvfWXkV+Up2rrtC1/J1V8ryfJ8is4NXx7WHLmuqsz2q6rVNDl0Pbct1fWObihyyuVy/L7BJ3WWVELYgm/muNsnnKVbwZfSSymo/2dT2ab4RRg/cIvGpQn/n6Ea5NGs7hn6Y8VOwSeKzhfef6/dCLH1VI2mTJJ5v8g4x5wv79aR/ejavA/RslUeWckHayDVto8oc7YiNpfgHf3iq2pGPcc7xmo56T9GxvYQwngJPBvRjFZqiqCywHzXfiKB+M+lpxn+9lmjOmRqaZuUj3v7IcPhhN/VJv6S/079fUlO8zxJroMl5p6df5EmtsLiouihYvjRfB33maJqnDnaeXLqhNsX/GSfP1a7S6vj3GPZ7n29MfSdSvHP/8tg8c9XHTTzh55pJFk8R9fGmBN0Ja8dw3VVHFX2tT8jW07H09+ui42NXTH9r3oy4+5sy6G8pwyEHMzt5+7uMttW52xanHEg+PZOdJN+wIYN9/f8c5CR2LRWkXK5JuU49rt8CGKZjOZjwkZg/Tycv+jQQxIPSqz+Mo11ljmv7TVqz4+83dzvr3KXM2NyV+fmszs/1Y+znnqFRXvooL90Id1LWSeXF/iK2cn3jfXKX856ktN1saSuUDyst1cj05xO4h1KW8aOTa+IrHGNR1sV7j5+QS3yap/3mPl/hvM9D2/L7fIVnf9X/ewE7oMv3tslxr69w9iv0Lb/XU5bnva4mNWAffIKnXQnpvfrfBX8n6bhPX5THdJK3L1qk+0ZY58jT9UyL+k3aBG7oQf15Uk/s4XzlCodvBNY5KouqSyvKpb/pLqXt6Tk/niGyrOnUcGXo3eHD9K3rPL/Q5bvongsv0vtxOPSlSbHrEbuPB9VdJTVFlasl/5yA/HNs+c3Zc91LC5G/uipknqHqJ8bo7pb0BWmazr/Gp46ktzPPVSclvkTjeJv8J3vnAt9lWcXx/9hALgPHgDEu4mBcBgzYEGGT24AB46JMQRuGbcgllgh/YSDIzJVWVlRTqbCoZhGkWc20xNKapn3QsJaikZItJaOkWoZERtr3f3beZ+/1f4Fht/35HH573uec93nOc3vf5/KeI+GuZtwK6bg=
*/