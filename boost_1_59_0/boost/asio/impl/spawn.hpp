//
// impl/spawn.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
  inline asio_handler_allocate_is_deprecated
  asio_handler_allocate(std::size_t size,
      coro_handler<Handler, T>* this_handler)
  {
#if defined(BOOST_ASIO_NO_DEPRECATED)
    boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
    return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
    return boost_asio_handler_alloc_helpers::allocate(
        size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Handler, typename T>
  inline asio_handler_deallocate_is_deprecated
  asio_handler_deallocate(void* pointer, std::size_t size,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_alloc_helpers::deallocate(
        pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Handler, typename T>
  inline bool asio_handler_is_continuation(coro_handler<Handler, T>*)
  {
    return true;
  }

  template <typename Function, typename Handler, typename T>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename Handler, typename T>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      coro_handler<Handler, T>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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

template <template <typename, typename> class Associator,
    typename Handler, typename T, typename DefaultCandidate>
struct associator<Associator,
    detail::coro_handler<Handler, T>,
    DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::coro_handler<Handler, T>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
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
        BOOST_ASIO_MOVE_OR_LVALUE(Handler)(data->handler_)();
    }

    shared_ptr<spawn_data<Handler, Function> > data_;
  };

  template <typename Handler, typename Function>
  struct spawn_helper
  {
    typedef typename associated_allocator<Handler>::type allocator_type;

    allocator_type get_allocator() const BOOST_ASIO_NOEXCEPT
    {
      return (get_associated_allocator)(data_->handler_);
    }

    typedef typename associated_executor<Handler>::type executor_type;

    executor_type get_executor() const BOOST_ASIO_NOEXCEPT
    {
      return (get_associated_executor)(data_->handler_);
    }

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
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(Function& function,
      spawn_helper<Handler, Function1>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->data_->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
  }

  template <typename Function, typename Handler, typename Function1>
  inline asio_handler_invoke_is_deprecated
  asio_handler_invoke(const Function& function,
      spawn_helper<Handler, Function1>* this_handler)
  {
    boost_asio_handler_invoke_helpers::invoke(
        function, this_handler->data_->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
    return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
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
    typename constraint<
      !is_executor<typename decay<Handler>::type>::value &&
      !execution::is_executor<typename decay<Handler>::type>::value &&
      !is_convertible<Handler&, execution_context&>::value>::type)
{
  typedef typename decay<Handler>::type handler_type;
  typedef typename decay<Function>::type function_type;

  detail::spawn_helper<handler_type, function_type> helper;
  helper.data_.reset(
      new detail::spawn_data<handler_type, function_type>(
        BOOST_ASIO_MOVE_CAST(Handler)(handler), true,
        BOOST_ASIO_MOVE_CAST(Function)(function)));
  helper.attributes_ = attributes;

  boost::asio::dispatch(helper);
}

template <typename Handler, typename Function>
void spawn(basic_yield_context<Handler> ctx,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes)
{
  typedef typename decay<Function>::type function_type;

  Handler handler(ctx.handler_); // Explicit copy that might be moved from.

  detail::spawn_helper<Handler, function_type> helper;
  helper.data_.reset(
      new detail::spawn_data<Handler, function_type>(
        BOOST_ASIO_MOVE_CAST(Handler)(handler), false,
        BOOST_ASIO_MOVE_CAST(Function)(function)));
  helper.attributes_ = attributes;

  boost::asio::dispatch(helper);
}

template <typename Function, typename Executor>
inline void spawn(const Executor& ex,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type)
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

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Function>
inline void spawn(const boost::asio::io_context::strand& s,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes)
{
  boost::asio::spawn(boost::asio::bind_executor(
        s, &detail::default_spawn_handler),
      BOOST_ASIO_MOVE_CAST(Function)(function), attributes);
}

#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

template <typename Function, typename ExecutionContext>
inline void spawn(ExecutionContext& ctx,
    BOOST_ASIO_MOVE_ARG(Function) function,
    const boost::coroutines::attributes& attributes,
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type)
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
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
*/