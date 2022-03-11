//
// impl/spawn.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_SPAWN_HPP
#define BOOST_ASIO_IMPL_SPAWN_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/detail/atomic_count.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/detail/noncopyable.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/system/system_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

  template <typename Handler, typename T>
  class coro_handler
  {
  public:
    coro_handler(basic_yield_context<Handler> ctx)
      : coro_(ctx.coro_.lock()),
        ca_(ctx.ca_),
        handler_(ctx.handler_),
        ready_(0),
        ec_(ctx.ec_),
        value_(0)
    {
    }

    void operator()(T value)
    {
      *ec_ = boost::system::error_code();
      *value_ = BOOST_ASIO_MOVE_CAST(T)(value);
      if (--*ready_ == 0)
        (*coro_)();
    }

    void operator()(boost::system::error_code ec, T value)
    {
      *ec_ = ec;
      *value_ = BOOST_ASIO_MOVE_CAST(T)(value);
      if (--*ready_ == 0)
        (*coro_)();
    }

  //private:
    shared_ptr<typename basic_yield_context<Handler>::callee_type> coro_;
    typename basic_yield_context<Handler>::caller_type& ca_;
    Handler handler_;
    atomic_count* ready_;
    boost::system::error_code* ec_;
    T* value_;
  };

  template <typename Handler>
  class coro_handler<Handler, void>
  {
  public:
    coro_handler(basic_yield_context<Handler> ctx)
      : coro_(ctx.coro_.lock()),
        ca_(ctx.ca_),
        handler_(ctx.handler_),
        ready_(0),
        ec_(ctx.ec_)
    {
    }

    void operator()()
    {
      *ec_ = boost::system::error_code();
      if (--*ready_ == 0)
        (*coro_)();
    }

    void operator()(boost::system::error_code ec)
    {
      *ec_ = ec;
      if (--*ready_ == 0)
        (*coro_)();
    }

  //private:
    shared_ptr<typename basic_yield_context<Handler>::callee_type> coro_;
    typename basic_yield_context<Handler>::caller_type& ca_;
    Handler handler_;
    atomic_count* ready_;
    boost::system::error_code* ec_;
  };

  template <typename Handler, typename T>
  inline void* asio_handler_allocate(std::size_t size,
      coro_handler<Handler, T>* this_handler)
  {
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
  }

  template <typename Handler, typename T>
  inline void asio_handler_deallocate(void* pointer, std::size_t size,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
  }

  template <typename Handler, typename T>
  inline bool asio_handler_is_continuation(coro_handler<Handler, T>*)
  {
    return true;
  }

  template <typename Function, typename Handler, typename T>
  inline void asio_handler_invoke(Function& function,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Function, typename Handler, typename T>
  inline void asio_handler_invoke(const Function& function,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
  }

  template <typename Handler, typename T>
  class coro_async_result
  {
  public:
    typedef coro_handler<Handler, T> completion_handler_type;
    typedef T return_type;

    explicit coro_async_result(completion_handler_type& h)
      : handler_(h),
        ca_(h.ca_),
        ready_(2)
    {
      h.ready_ = &ready_;
      out_ec_ = h.ec_;
      if (!out_ec_) h.ec_ = &ec_;
      h.value_ = &value_;
    }

    return_type get()
    {
      // Must not hold shared_ptr to coro while suspended.
      handler_.coro_.reset();

      if (--ready_ != 0)
        ca_();
      if (!out_ec_ && ec_) throw boost::system::system_error(ec_);
      return BOOST_ASIO_MOVE_CAST(return_type)(value_);
    }

  private:
    completion_handler_type& handler_;
    typename basic_yield_context<Handler>::caller_type& ca_;
    atomic_count ready_;
    boost::system::error_code* out_ec_;
    boost::system::error_code ec_;
    return_type value_;
  };

  template <typename Handler>
  class coro_async_result<Handler, void>
  {
  public:
    typedef coro_handler<Handler, void> completion_handler_type;
    typedef void return_type;

    explicit coro_async_result(completion_handler_type& h)
      : handler_(h),
        ca_(h.ca_),
        ready_(2)
    {
      h.ready_ = &ready_;
      out_ec_ = h.ec_;
      if (!out_ec_) h.ec_ = &ec_;
    }

    void get()
    {
      // Must not hold shared_ptr to coro while suspended.
      handler_.coro_.reset();

      if (--ready_ != 0)
        ca_();
      if (!out_ec_ && ec_) throw boost::system::system_error(ec_);
    }

  private:
    completion_handler_type& handler_;
    typename basic_yield_context<Handler>::caller_type& ca_;
    atomic_count ready_;
    boost::system::error_code* out_ec_;
    boost::system::error_code ec_;
  };

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename Handler, typename ReturnType>
class async_result<basic_yield_context<Handler>, ReturnType()>
  : public detail::coro_async_result<Handler, void>
{
public:
  explicit async_result(
    typename detail::coro_async_result<Handler,
      void>::completion_handler_type& h)
    : detail::coro_async_result<Handler, void>(h)
  {
  }
};

template <typename Handler, typename ReturnType, typename Arg1>
class async_result<basic_yield_context<Handler>, ReturnType(Arg1)>
  : public detail::coro_async_result<Handler, typename decay<Arg1>::type>
{
public:
  explicit async_result(
    typename detail::coro_async_result<Handler,
      typename decay<Arg1>::type>::completion_handler_type& h)
    : detail::coro_async_result<Handler, typename decay<Arg1>::type>(h)
  {
  }
};

template <typename Handler, typename ReturnType>
class async_result<basic_yield_context<Handler>,
    ReturnType(boost::system::error_code)>
  : public detail::coro_async_result<Handler, void>
{
public:
  explicit async_result(
    typename detail::coro_async_result<Handler,
      void>::completion_handler_type& h)
    : detail::coro_async_result<Handler, void>(h)
  {
  }
};

template <typename Handler, typename ReturnType, typename Arg2>
class async_result<basic_yield_context<Handler>,
    ReturnType(boost::system::error_code, Arg2)>
  : public detail::coro_async_result<Handler, typename decay<Arg2>::type>
{
public:
  explicit async_result(
    typename detail::coro_async_result<Handler,
      typename decay<Arg2>::type>::completion_handler_type& h)
    : detail::coro_async_result<Handler, typename decay<Arg2>::type>(h)
  {
  }
};

template <typename Handler, typename T, typename Allocator>
struct associated_allocator<detail::coro_handler<Handler, T>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(const detail::coro_handler<Handler, T>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
  }
};

template <typename Handler, typename T, typename Executor>
struct associated_executor<detail::coro_handler<Handler, T>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(const detail::coro_handler<Handler, T>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

namespace detail {

  template <typename Handler, typename Function>
  struct spawn_data : private noncopyable
  {
    template <typename Hand, typename Func>
    spawn_data(BOOST_ASIO_MOVE_ARG(Hand) handler,
        bool call_handler, BOOST_ASIO_MOVE_ARG(Func) function)
      : handler_(BOOST_ASIO_MOVE_CAST(Hand)(handler)),
        call_handler_(call_handler),
        function_(BOOST_ASIO_MOVE_CAST(Func)(function))
    {
    }

    weak_ptr<typename basic_yield_context<Handler>::callee_type> coro_;
    Handler handler_;
    bool call_handler_;
    Function function_;
  };

  template <typename Handler, typename Function>
  struct coro_entry_point
  {
    void operator()(typename basic_yield_context<Handler>::caller_type& ca)
    {
      shared_ptr<spawn_data<Handler, Function> > data(data_);
#if !defined(BOOST_COROUTINES_UNIDIRECT) && !defined(BOOST_COROUTINES_V2)
      ca(); // Yield until coroutine pointer has been initialised.
#endif // !defined(BOOST_COROUTINES_UNIDIRECT) && !defined(BOOST_COROUTINES_V2)
      const basic_yield_context<Handler> yield(
          data->coro_, ca, data->handler_);

      (data->function_)(yield);
      if (data->call_handler_)
        (data->handler_)();
    }

    shared_ptr<spawn_data<Handler, Function> > data_;
  };

  template <typename Handler, typename Function>
  struct spawn_helper
  {
    void operator()()
    {
      typedef typename basic_yield_context<Handler>::callee_type callee_type;
      coro_entry_point<Handler, Function> entry_point = { data_ };
      shared_ptr<callee_type> coro(new callee_type(entry_point, attributes_));
      data_->coro_ = coro;
      (*coro)();
    }

    shared_ptr<spawn_data<Handler, Function> > data_;
    boost::coroutines::attributes attributes_;
  };

  template <typename Function, typename Handler, typename Function1>
  inline void asio_handler_invoke(Function& function,
      spawn_helper<Handler, Function1>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->data_->handler_);
  }

  template <typename Function, typename Handler, typename Function1>
  inline void asio_handler_invoke(const Function& function,
      spawn_helper<Handler, Function1>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->data_->handler_);
  }

  inline void default_spawn_handler() {}

} // namespace detail

template <typename Function>
inline void spawn(BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes)
{
  typedef typename decay<Function>::type function_type;

  typename associated_executor<function_type>::type ex(
      (get_associated_executor)(function));

  boost::asio::spawn(ex, BOOST_ASIO_MOVE_CAST(Function)(function), attributes);
}

template <typename Handler, typename Function>
void spawn(BOOST_ASIO_MOVE_ARG(Handler) handler,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes,
    typename enable_if<!is_executor<typename decay<Handler>::type>::value &&
      !is_convertible<Handler&, execution_context&>::value>::type*)
{
  typedef typename decay<Handler>::type handler_type;
  typedef typename decay<Function>::type function_type;

  typename associated_executor<handler_type>::type ex(
      (get_associated_executor)(handler));

  typename associated_allocator<handler_type>::type a(
      (get_associated_allocator)(handler));

  detail::spawn_helper<handler_type, function_type> helper;
  helper.data_.reset(
      new detail::spawn_data<handler_type, function_type>(
        BOOST_ASIO_MOVE_CAST(Handler)(handler), true,
        BOOST_ASIO_MOVE_CAST(Function)(function)));
  helper.attributes_ = attributes;

  ex.dispatch(helper, a);
}

template <typename Handler, typename Function>
void spawn(basic_yield_context<Handler> ctx,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes)
{
  typedef typename decay<Function>::type function_type;

  Handler handler(ctx.handler_); // Explicit copy that might be moved from.

  typename associated_executor<Handler>::type ex(
      (get_associated_executor)(handler));

  typename associated_allocator<Handler>::type a(
      (get_associated_allocator)(handler));

  detail::spawn_helper<Handler, function_type> helper;
  helper.data_.reset(
      new detail::spawn_data<Handler, function_type>(
        BOOST_ASIO_MOVE_CAST(Handler)(handler), false,
        BOOST_ASIO_MOVE_CAST(Function)(function)));
  helper.attributes_ = attributes;

  ex.dispatch(helper, a);
}

template <typename Function, typename Executor>
inline void spawn(const Executor& ex,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes,
    typename enable_if<is_executor<Executor>::value>::type*)
{
  boost::asio::spawn(boost::asio::strand<Executor>(ex),
      BOOST_ASIO_MOVE_CAST(Function)(function), attributes);
}

template <typename Function, typename Executor>
inline void spawn(const strand<Executor>& ex,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes)
{
  boost::asio::spawn(boost::asio::bind_executor(
        ex, &detail::default_spawn_handler),
      BOOST_ASIO_MOVE_CAST(Function)(function), attributes);
}

template <typename Function>
inline void spawn(const boost::asio::io_context::strand& s,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes)
{
  boost::asio::spawn(boost::asio::bind_executor(
        s, &detail::default_spawn_handler),
      BOOST_ASIO_MOVE_CAST(Function)(function), attributes);
}

template <typename Function, typename ExecutionContext>
inline void spawn(ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type*)
{
  boost::asio::spawn(ctx.get_executor(),
      BOOST_ASIO_MOVE_CAST(Function)(function), attributes);
}

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_SPAWN_HPP

/* spawn.hpp
+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
*/