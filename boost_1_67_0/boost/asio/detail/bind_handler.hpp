//
// detail/bind_handler.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

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
    handler_(static_cast<const Arg1&>(arg1_));
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
inline void* asio_handler_allocate(std::size_t size,
    binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Handler, typename Arg1>
inline bool asio_handler_is_continuation(
    binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1>
inline void asio_handler_invoke(Function& function,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1>
inline void asio_handler_invoke(const Function& function,
    binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
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
    handler_(static_cast<const Arg1&>(arg1_),
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
inline void* asio_handler_allocate(std::size_t size,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Handler, typename Arg1, typename Arg2>
inline bool asio_handler_is_continuation(
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_invoke(Function& function,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_invoke(const Function& function,
    binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
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
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_), static_cast<const Arg3&>(arg3_));
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
inline void* asio_handler_allocate(std::size_t size,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1, typename Arg2, typename Arg3>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
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
inline void asio_handler_invoke(Function& function,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Handler,
    typename Arg1, typename Arg2, typename Arg3>
inline void asio_handler_invoke(const Function& function,
    binder3<Handler, Arg1, Arg2, Arg3>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
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
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_), static_cast<const Arg3&>(arg3_),
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
inline void* asio_handler_allocate(std::size_t size,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
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
inline void asio_handler_invoke(Function& function,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4>
inline void asio_handler_invoke(const Function& function,
    binder4<Handler, Arg1, Arg2, Arg3, Arg4>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
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
    handler_(static_cast<const Arg1&>(arg1_),
        static_cast<const Arg2&>(arg2_), static_cast<const Arg3&>(arg3_),
        static_cast<const Arg4&>(arg4_), static_cast<const Arg5&>(arg5_));
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
inline void* asio_handler_allocate(std::size_t size,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1, typename Arg2,
    typename Arg3, typename Arg4, typename Arg5>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
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
inline void asio_handler_invoke(Function& function,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1,
    typename Arg2, typename Arg3, typename Arg4, typename Arg5>
inline void asio_handler_invoke(const Function& function,
    binder5<Handler, Arg1, Arg2, Arg3, Arg4, Arg5>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
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
    handler_(BOOST_ASIO_MOVE_CAST(Arg1)(arg1_));
  }

//private:
  Handler handler_;
  Arg1 arg1_;
};

template <typename Handler, typename Arg1>
inline void* asio_handler_allocate(std::size_t size,
    move_binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    move_binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Handler, typename Arg1>
inline bool asio_handler_is_continuation(
    move_binder1<Handler, Arg1>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1>
inline void asio_handler_invoke(BOOST_ASIO_MOVE_ARG(Function) function,
    move_binder1<Handler, Arg1>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      BOOST_ASIO_MOVE_CAST(Function)(function), this_handler->handler_);
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
    handler_(static_cast<const Arg1&>(arg1_),
        BOOST_ASIO_MOVE_CAST(Arg2)(arg2_));
  }

//private:
  Handler handler_;
  Arg1 arg1_;
  Arg2 arg2_;
};

template <typename Handler, typename Arg1, typename Arg2>
inline void* asio_handler_allocate(std::size_t size,
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Handler, typename Arg1, typename Arg2>
inline bool asio_handler_is_continuation(
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
      this_handler->handler_);
}

template <typename Function, typename Handler, typename Arg1, typename Arg2>
inline void asio_handler_invoke(BOOST_ASIO_MOVE_ARG(Function) function,
    move_binder2<Handler, Arg1, Arg2>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      BOOST_ASIO_MOVE_CAST(Function)(function), this_handler->handler_);
}

#endif // defined(BOOST_ASIO_HAS_MOVE)

} // namespace detail

template <typename Handler, typename Arg1, typename Allocator>
struct associated_allocator<detail::binder1<Handler, Arg1>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(const detail::binder1<Handler, Arg1>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

template <typename Handler, typename Arg1, typename Arg2, typename Allocator>
struct associated_allocator<detail::binder2<Handler, Arg1, Arg2>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(const detail::binder2<Handler, Arg1, Arg2>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

template <typename Handler, typename Arg1, typename Executor>
struct associated_executor<detail::binder1<Handler, Arg1>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(const detail::binder1<Handler, Arg1>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

template <typename Handler, typename Arg1, typename Arg2, typename Executor>
struct associated_executor<detail::binder2<Handler, Arg1, Arg2>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(const detail::binder2<Handler, Arg1, Arg2>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

#if defined(BOOST_ASIO_HAS_MOVE)

template <typename Handler, typename Arg1, typename Allocator>
struct associated_allocator<detail::move_binder1<Handler, Arg1>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(const detail::move_binder1<Handler, Arg1>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

template <typename Handler, typename Arg1, typename Arg2, typename Allocator>
struct associated_allocator<
    detail::move_binder2<Handler, Arg1, Arg2>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(const detail::move_binder2<Handler, Arg1, Arg2>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

template <typename Handler, typename Arg1, typename Executor>
struct associated_executor<detail::move_binder1<Handler, Arg1>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(const detail::move_binder1<Handler, Arg1>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

template <typename Handler, typename Arg1, typename Arg2, typename Executor>
struct associated_executor<detail::move_binder2<Handler, Arg1, Arg2>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(const detail::move_binder2<Handler, Arg1, Arg2>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
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