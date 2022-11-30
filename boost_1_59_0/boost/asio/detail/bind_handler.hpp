//
// detail/bind_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_BIND_HANDLER_HPP
#define BOOST_ASIO_DETAIL_BIND_HANDLER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename Handler>
class binder0
{
public:
  template <typename T>
  binder0(int, BOOST_ASIO_MOVE_ARG(T) handler)
    : handler_(BOOST_ASIO_MOVE_CAST(T)(handler))
  {
  }

  binder0(Handler& handler)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler))
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  binder0(const binder0& other)
    : handler_(other.handler_)
  {
  }

  binder0(binder0&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)();
  }

  void operator()() const
  {
    handler_();
  }

//private:
  Handler handler_;
};

template <typename Handler>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    binder0<Handler>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    binder0<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    binder0<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    binder0<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    binder0<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline binder0<typename decay<Handler>::type> bind_handler(
    BOOST_ASIO_MOVE_ARG(Handler) handler)
{
  return binder0<typename decay<Handler>::type>(
      0, BOOST_ASIO_MOVE_CAST(Handler)(handler));
}

template <typename Handler, typename Arg1>
class binder1
{
public:
  template <typename T>
  binder1(int, BOOST_ASIO_MOVE_ARG(T) handler, const Arg1& arg1)
    : handler_(BOOST_ASIO_MOVE_CAST(T)(handler)),
      arg1_(arg1)
  {
  }

  binder1(Handler& handler, const Arg1& arg1)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  binder1(const binder1& other)
    : handler_(other.handler_),
      arg1_(other.arg1_)
  {
  }

  binder1(binder1&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        static_cast<const Arg1&>(arg1_));
  }

  void operator()() const
  {
    handler_(arg1_);
  }

//private:
  Handler handler_;
  Arg1 arg1_;
};

template <typename Handler, typename Arg1>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    binder1<Handler, Arg1>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1>
inline bool asio_handler_is_continuation(
    binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler, typename Arg1>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1>
inline binder1<typename decay<Handler>::type, Arg1> bind_handler(
    BOOST_ASIO_MOVE_ARG(Handler) handler, const Arg1& arg1)
{
  return binder1<typename decay<Handler>::type, Arg1>(0,
      BOOST_ASIO_MOVE_CAST(Handler)(handler), arg1);
}

template <typename Handler, typename Arg1, typename Arg2>
class binder2
{
public:
  template <typename T>
  binder2(int, BOOST_ASIO_MOVE_ARG(T) handler,
      const Arg1& arg1, const Arg2& arg2)
    : handler_(BOOST_ASIO_MOVE_CAST(T)(handler)),
      arg1_(arg1),
      arg2_(arg2)
  {
  }

  binder2(Handler& handler, const Arg1& arg1, const Arg2& arg2)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  binder2(const binder2& other)
    : handler_(other.handler_),
      arg1_(other.arg1_),
      arg2_(other.arg2_)
  {
  }

  binder2(binder2&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_)),
      arg2_(BOOST_ASIO_MOVE_CAST(Arg2)(other.arg2_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_));
  }

  void operator()() const
  {
    handler_(arg1_, arg2_);
  }

//private:
  Handler handler_;
  Arg1 arg1_;
  Arg2 arg2_;
};

template <typename Handler, typename Arg1, typename Arg2>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2>
inline bool asio_handler_is_continuation(
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2>
inline binder2<typename decay<Handler>::type, Arg1, Arg2> bind_handler(
    BOOST_ASIO_MOVE_ARG(Handler) handler, const Arg1& arg1, const Arg2& arg2)
{
  return binder2<typename decay<Handler>::type, Arg1, Arg2>(0,
      BOOST_ASIO_MOVE_CAST(Handler)(handler), arg1, arg2);
}

template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
class binder3
{
public:
  template <typename T>
  binder3(int, BOOST_ASIO_MOVE_ARG(T) handler, const Arg1& arg1,
      const Arg2& arg2, const Arg3& arg3)
    : handler_(BOOST_ASIO_MOVE_CAST(T)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3)
  {
  }

  binder3(Handler& handler, const Arg1& arg1,
      const Arg2& arg2, const Arg3& arg3)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  binder3(const binder3& other)
    : handler_(other.handler_),
      arg1_(other.arg1_),
      arg2_(other.arg2_),
      arg3_(other.arg3_)
  {
  }

  binder3(binder3&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_)),
      arg2_(BOOST_ASIO_MOVE_CAST(Arg2)(other.arg2_)),
      arg3_(BOOST_ASIO_MOVE_CAST(Arg3)(other.arg3_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_),
        static_cast<const Arg3&>(arg3_));
  }

  void operator()() const
  {
    handler_(arg1_, arg2_, arg3_);
  }

//private:
  Handler handler_;
  Arg1 arg1_;
  Arg2 arg2_;
  Arg3 arg3_;
};

template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline bool asio_handler_is_continuation(
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler,
    typename Arg1, typename Arg2, typename Arg3>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler,
    typename Arg1, typename Arg2, typename Arg3>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline binder3<typename decay<Handler>::type, Arg1, Arg2, Arg3> bind_handler(
    BOOST_ASIO_MOVE_ARG(Handler) handler, const Arg1& arg1, const Arg2& arg2,
    const Arg3& arg3)
{
  return binder3<typename decay<Handler>::type, Arg1, Arg2, Arg3>(0,
      BOOST_ASIO_MOVE_CAST(Handler)(handler), arg1, arg2, arg3);
}

template <typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
class binder4
{
public:
  template <typename T>
  binder4(int, BOOST_ASIO_MOVE_ARG(T) handler, const Arg1& arg1,
      const Arg2& arg2, const Arg3& arg3, const Arg4& arg4)
    : handler_(BOOST_ASIO_MOVE_CAST(T)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4)
  {
  }

  binder4(Handler& handler, const Arg1& arg1,
      const Arg2& arg2, const Arg3& arg3, const Arg4& arg4)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  binder4(const binder4& other)
    : handler_(other.handler_),
      arg1_(other.arg1_),
      arg2_(other.arg2_),
      arg3_(other.arg3_),
      arg4_(other.arg4_)
  {
  }

  binder4(binder4&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_)),
      arg2_(BOOST_ASIO_MOVE_CAST(Arg2)(other.arg2_)),
      arg3_(BOOST_ASIO_MOVE_CAST(Arg3)(other.arg3_)),
      arg4_(BOOST_ASIO_MOVE_CAST(Arg4)(other.arg4_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_),
        static_cast<const Arg3&>(arg3_),
        static_cast<const Arg4&>(arg4_));
  }

  void operator()() const
  {
    handler_(arg1_, arg2_, arg3_, arg4_);
  }

//private:
  Handler handler_;
  Arg1 arg1_;
  Arg2 arg2_;
  Arg3 arg3_;
  Arg4 arg4_;
};

template <typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline bool asio_handler_is_continuation(
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline binder4<typename decay<Handler>::type, Arg1, Arg2, Arg3, Arg4>
bind_handler(BOOST_ASIO_MOVE_ARG(Handler) handler, const Arg1& arg1,
    const Arg2& arg2, const Arg3& arg3, const Arg4& arg4)
{
  return binder4<typename decay<Handler>::type, Arg1, Arg2, Arg3, Arg4>(0,
      BOOST_ASIO_MOVE_CAST(Handler)(handler), arg1, arg2, arg3, arg4);
}

template <typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
class binder5
{
public:
  template <typename T>
  binder5(int, BOOST_ASIO_MOVE_ARG(T) handler, const Arg1& arg1,
      const Arg2& arg2, const Arg3& arg3, const Arg4& arg4, const Arg5& arg5)
    : handler_(BOOST_ASIO_MOVE_CAST(T)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4),
      arg5_(arg5)
  {
  }

  binder5(Handler& handler, const Arg1& arg1, const Arg2& arg2,
      const Arg3& arg3, const Arg4& arg4, const Arg5& arg5)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(arg2),
      arg3_(arg3),
      arg4_(arg4),
      arg5_(arg5)
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE)
  binder5(const binder5& other)
    : handler_(other.handler_),
      arg1_(other.arg1_),
      arg2_(other.arg2_),
      arg3_(other.arg3_),
      arg4_(other.arg4_),
      arg5_(other.arg5_)
  {
  }

  binder5(binder5&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_)),
      arg2_(BOOST_ASIO_MOVE_CAST(Arg2)(other.arg2_)),
      arg3_(BOOST_ASIO_MOVE_CAST(Arg3)(other.arg3_)),
      arg4_(BOOST_ASIO_MOVE_CAST(Arg4)(other.arg4_)),
      arg5_(BOOST_ASIO_MOVE_CAST(Arg5)(other.arg5_))
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE)

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_),
        static_cast<const Arg3&>(arg3_),
        static_cast<const Arg4&>(arg4_),
        static_cast<const Arg5&>(arg5_));
  }

  void operator()() const
  {
    handler_(arg1_, arg2_, arg3_, arg4_, arg5_);
  }

//private:
  Handler handler_;
  Arg1 arg1_;
  Arg2 arg2_;
  Arg3 arg3_;
  Arg4 arg4_;
  Arg5 arg5_;
};

template <typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline bool asio_handler_is_continuation(
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4, typename Arg5>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4, typename Arg5>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline binder5<typename decay<Handler>::type, Arg1, Arg2, Arg3, Arg4, Arg5>
bind_handler(BOOST_ASIO_MOVE_ARG(Handler) handler, const Arg1& arg1,
    const Arg2& arg2, const Arg3& arg3, const Arg4& arg4, const Arg5& arg5)
{
  return binder5<typename decay<Handler>::type, Arg1, Arg2, Arg3, Arg4, Arg5>(0,
      BOOST_ASIO_MOVE_CAST(Handler)(handler), arg1, arg2, arg3, arg4, arg5);
}

#if defined(BOOST_ASIO_HAS_MOVE)

template <typename Handler, typename Arg1>
class move_binder1
{
public:
  move_binder1(int, BOOST_ASIO_MOVE_ARG(Handler) handler,
      BOOST_ASIO_MOVE_ARG(Arg1) arg1)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(arg1))
  {
  }

  move_binder1(move_binder1&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_))
  {
  }

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        BOOST_ASIO_MOVE_CAST(Arg1)(arg1_));
  }

//private:
  Handler handler_;
  Arg1 arg1_;
};

template <typename Handler, typename Arg1>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    move_binder1<Handler, Arg1>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    move_binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1>
inline bool asio_handler_is_continuation(
    move_binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(BOOST_ASIO_MOVE_ARG(Function) function,
    move_binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      BOOST_ASIO_MOVE_CAST(Function)(function), this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2>
class move_binder2
{
public:
  move_binder2(int, BOOST_ASIO_MOVE_ARG(Handler) handler,
      const Arg1& arg1, BOOST_ASIO_MOVE_ARG(Arg2) arg2)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(handler)),
      arg1_(arg1),
      arg2_(BOOST_ASIO_MOVE_CAST(Arg2)(arg2))
  {
  }

  move_binder2(move_binder2&& other)
    : handler_(BOOST_ASIO_MOVE_CAST(Handler)(other.handler_)),
      arg1_(BOOST_ASIO_MOVE_CAST(Arg1)(other.arg1_)),
      arg2_(BOOST_ASIO_MOVE_CAST(Arg2)(other.arg2_))
  {
  }

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        static_cast<const Arg1&>(arg1_),
        BOOST_ASIO_MOVE_CAST(Arg2)(arg2_));
  }

//private:
  Handler handler_;
  Arg1 arg1_;
  Arg2 arg2_;
};

template <typename Handler, typename Arg1, typename Arg2>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler, typename Arg1, typename Arg2>
inline bool asio_handler_is_continuation(
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(BOOST_ASIO_MOVE_ARG(Function) function,
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      BOOST_ASIO_MOVE_CAST(Function)(function), this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace detail

template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    detail::binder0<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::binder0<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename DefaultCandidate>
struct associator<Associator,
    detail::binder1<Handler, Arg1>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::binder1<Handler, Arg1>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename Arg2,
    typename DefaultCandidate>
struct associator<Associator,
    detail::binder2<Handler, Arg1, Arg2>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::binder2<Handler, Arg1, Arg2>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename DefaultCandidate>
struct associator<Associator,
    detail::binder3<Handler, Arg1, Arg2, Arg3>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::binder3<Handler, Arg1, Arg2, Arg3>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename Arg4, typename DefaultCandidate>
struct associator<Associator,
    detail::binder4<Handler, Arg1, Arg2, Arg3, Arg4>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::binder4<Handler, Arg1, Arg2, Arg3, Arg4>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename Arg2, typename Arg3,
    typename Arg4, typename Arg5, typename DefaultCandidate>
struct associator<Associator,
    detail::binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#if defined(BOOST_ASIO_HAS_MOVE)

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename DefaultCandidate>
struct associator<Associator,
    detail::move_binder1<Handler, Arg1>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::move_binder1<Handler, Arg1>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Arg1, typename Arg2,
    typename DefaultCandidate>
struct associator<Associator,
    detail::move_binder2<Handler, Arg1, Arg2>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::move_binder2<Handler, Arg1, Arg2>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_BIND_HANDLER_HPP

/* bind_handler.hpp
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
*/