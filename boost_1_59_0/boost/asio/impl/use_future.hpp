//
// impl/use_future.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_USE_FUTURE_HPP
#define BOOST_ASIO_IMPL_USE_FUTURE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <tuple>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/memory.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/execution.hpp>
#include <boost/asio/packaged_task.hpp>
#include <boost/system/system_error.hpp>
#include <boost/asio/system_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename F, typename... Args>
inline void promise_invoke_and_set(std::promise<T>& p,
    F& f, BOOST_ASIO_MOVE_ARG(Args)... args)
{
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  try
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  {
    p.set_value(f(BOOST_ASIO_MOVE_CAST(Args)(args)...));
  }
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  catch (...)
  {
    p.set_exception(std::current_exception());
  }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
}

template <typename F, typename... Args>
inline void promise_invoke_and_set(std::promise<void>& p,
    F& f, BOOST_ASIO_MOVE_ARG(Args)... args)
{
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  try
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  {
    f(BOOST_ASIO_MOVE_CAST(Args)(args)...);
    p.set_value();
  }
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  catch (...)
  {
    p.set_exception(std::current_exception());
  }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
}

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename T, typename F>
inline void promise_invoke_and_set(std::promise<T>& p, F& f)
{
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  try
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  {
    p.set_value(f());
  }
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  catch (...)
  {
    p.set_exception(std::current_exception());
  }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
}

template <typename F, typename Args>
inline void promise_invoke_and_set(std::promise<void>& p, F& f)
{
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  try
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  {
    f();
    p.set_value();
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }
  catch (...)
  {
    p.set_exception(std::current_exception());
  }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
}

#if defined(BOOST_ASIO_NO_EXCEPTIONS)

#define BOOST_ASIO_PRIVATE_PROMISE_INVOKE_DEF(n) \
  template <typename T, typename F, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline void promise_invoke_and_set(std::promise<T>& p, \
      F& f, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    p.set_value(f(BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
  } \
  \
  template <typename F, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline void promise_invoke_and_set(std::promise<void>& p, \
      F& f, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    f(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    p.set_value(); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_PROMISE_INVOKE_DEF)
#undef BOOST_ASIO_PRIVATE_PROMISE_INVOKE_DEF

#else // defined(BOOST_ASIO_NO_EXCEPTIONS)

#define BOOST_ASIO_PRIVATE_PROMISE_INVOKE_DEF(n) \
  template <typename T, typename F, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline void promise_invoke_and_set(std::promise<T>& p, \
      F& f, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    try \
    { \
      p.set_value(f(BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
    } \
    catch (...) \
    { \
      p.set_exception(std::current_exception()); \
    } \
  } \
  \
  template <typename F, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline void promise_invoke_and_set(std::promise<void>& p, \
      F& f, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    try \
    { \
      f(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
      p.set_value(); \
    } \
    catch (...) \
    { \
      p.set_exception(std::current_exception()); \
    } \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_PROMISE_INVOKE_DEF)
#undef BOOST_ASIO_PRIVATE_PROMISE_INVOKE_DEF

#endif // defined(BOOST_ASIO_NO_EXCEPTIONS)

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

// A function object adapter to invoke a nullary function object and capture
// any exception thrown into a promise.
template <typename T, typename F>
class promise_invoker
{
public:
  promise_invoker(const shared_ptr<std::promise<T> >& p,
      BOOST_ASIO_MOVE_ARG(F) f)
    : p_(p), f_(BOOST_ASIO_MOVE_CAST(F)(f))
  {
  }

  void operator()()
  {
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    try
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
    {
      f_();
    }
#if !defined(BOOST_ASIO_NO_EXCEPTIONS)
    catch (...)
    {
      p_->set_exception(std::current_exception());
    }
#endif // !defined(BOOST_ASIO_NO_EXCEPTIONS)
  }

private:
  shared_ptr<std::promise<T> > p_;
  typename decay<F>::type f_;
};

// An executor that adapts the system_executor to capture any exeption thrown
// by a submitted function object and save it into a promise.
template <typename T, typename Blocking = execution::blocking_t::possibly_t>
class promise_executor
{
public:
  explicit promise_executor(const shared_ptr<std::promise<T> >& p)
    : p_(p)
  {
  }

  static BOOST_ASIO_CONSTEXPR Blocking query(execution::blocking_t)
  {
    return Blocking();
  }

  promise_executor<T, execution::blocking_t::possibly_t>
  require(execution::blocking_t::possibly_t) const
  {
    return promise_executor<T, execution::blocking_t::possibly_t>(p_);
  }

  promise_executor<T, execution::blocking_t::never_t>
  require(execution::blocking_t::never_t) const
  {
    return promise_executor<T, execution::blocking_t::never_t>(p_);
  }

  template <typename F>
  void execute(BOOST_ASIO_MOVE_ARG(F) f) const
  {
    execution::execute(
        boost::asio::require(system_executor(), Blocking()),
        promise_invoker<T, F>(p_, BOOST_ASIO_MOVE_CAST(F)(f)));
  }

#if !defined(BOOST_ASIO_NO_TS_EXECUTORS)
  execution_context& context() const BOOST_ASIO_NOEXCEPT
  {
    return system_executor().context();
  }

  void on_work_started() const BOOST_ASIO_NOEXCEPT {}
  void on_work_finished() const BOOST_ASIO_NOEXCEPT {}

  template <typename F, typename A>
  void dispatch(BOOST_ASIO_MOVE_ARG(F) f, const A&) const
  {
    promise_invoker<T, F>(p_, BOOST_ASIO_MOVE_CAST(F)(f))();
  }

  template <typename F, typename A>
  void post(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    system_executor().post(
        promise_invoker<T, F>(p_, BOOST_ASIO_MOVE_CAST(F)(f)), a);
  }

  template <typename F, typename A>
  void defer(BOOST_ASIO_MOVE_ARG(F) f, const A& a) const
  {
    system_executor().defer(
        promise_invoker<T, F>(p_, BOOST_ASIO_MOVE_CAST(F)(f)), a);
  }
#endif // !defined(BOOST_ASIO_NO_TS_EXECUTORS)

  friend bool operator==(const promise_executor& a,
      const promise_executor& b) BOOST_ASIO_NOEXCEPT
  {
    return a.p_ == b.p_;
  }

  friend bool operator!=(const promise_executor& a,
      const promise_executor& b) BOOST_ASIO_NOEXCEPT
  {
    return a.p_ != b.p_;
  }

private:
  shared_ptr<std::promise<T> > p_;
};

// The base class for all completion handlers that create promises.
template <typename T>
class promise_creator
{
public:
  typedef promise_executor<T> executor_type;

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return executor_type(p_);
  }

  typedef std::future<T> future_type;

  future_type get_future()
  {
    return p_->get_future();
  }

protected:
  template <typename Allocator>
  void create_promise(const Allocator& a)
  {
    BOOST_ASIO_REBIND_ALLOC(Allocator, char) b(a);
    p_ = std::allocate_shared<std::promise<T>>(b, std::allocator_arg, b);
  }

  shared_ptr<std::promise<T> > p_;
};

// For completion signature void().
class promise_handler_0
  : public promise_creator<void>
{
public:
  void operator()()
  {
    this->p_->set_value();
  }
};

// For completion signature void(error_code).
class promise_handler_ec_0
  : public promise_creator<void>
{
public:
  void operator()(const boost::system::error_code& ec)
  {
    if (ec)
    {
      this->p_->set_exception(
          std::make_exception_ptr(
            boost::system::system_error(ec)));
    }
    else
    {
      this->p_->set_value();
    }
  }
};

// For completion signature void(exception_ptr).
class promise_handler_ex_0
  : public promise_creator<void>
{
public:
  void operator()(const std::exception_ptr& ex)
  {
    if (ex)
    {
      this->p_->set_exception(ex);
    }
    else
    {
      this->p_->set_value();
    }
  }
};

// For completion signature void(T).
template <typename T>
class promise_handler_1
  : public promise_creator<T>
{
public:
  template <typename Arg>
  void operator()(BOOST_ASIO_MOVE_ARG(Arg) arg)
  {
    this->p_->set_value(BOOST_ASIO_MOVE_CAST(Arg)(arg));
  }
};

// For completion signature void(error_code, T).
template <typename T>
class promise_handler_ec_1
  : public promise_creator<T>
{
public:
  template <typename Arg>
  void operator()(const boost::system::error_code& ec,
      BOOST_ASIO_MOVE_ARG(Arg) arg)
  {
    if (ec)
    {
      this->p_->set_exception(
          std::make_exception_ptr(
            boost::system::system_error(ec)));
    }
    else
      this->p_->set_value(BOOST_ASIO_MOVE_CAST(Arg)(arg));
  }
};

// For completion signature void(exception_ptr, T).
template <typename T>
class promise_handler_ex_1
  : public promise_creator<T>
{
public:
  template <typename Arg>
  void operator()(const std::exception_ptr& ex,
      BOOST_ASIO_MOVE_ARG(Arg) arg)
  {
    if (ex)
      this->p_->set_exception(ex);
    else
      this->p_->set_value(BOOST_ASIO_MOVE_CAST(Arg)(arg));
  }
};

// For completion signature void(T1, ..., Tn);
template <typename T>
class promise_handler_n
  : public promise_creator<T>
{
public:
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename... Args>
  void operator()(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    this->p_->set_value(
        std::forward_as_tuple(
          BOOST_ASIO_MOVE_CAST(Args)(args)...));
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#define BOOST_ASIO_PRIVATE_CALL_OP_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  {\
    this->p_->set_value( \
        std::forward_as_tuple( \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CALL_OP_DEF)
#undef BOOST_ASIO_PRIVATE_CALL_OP_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
};

// For completion signature void(error_code, T1, ..., Tn);
template <typename T>
class promise_handler_ec_n
  : public promise_creator<T>
{
public:
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename... Args>
  void operator()(const boost::system::error_code& ec,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    if (ec)
    {
      this->p_->set_exception(
          std::make_exception_ptr(
            boost::system::system_error(ec)));
    }
    else
    {
      this->p_->set_value(
          std::forward_as_tuple(
            BOOST_ASIO_MOVE_CAST(Args)(args)...));
    }
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#define BOOST_ASIO_PRIVATE_CALL_OP_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(const boost::system::error_code& ec, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  {\
    if (ec) \
    { \
      this->p_->set_exception( \
          std::make_exception_ptr( \
            boost::system::system_error(ec))); \
    } \
    else \
    { \
      this->p_->set_value( \
          std::forward_as_tuple( \
            BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
    } \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CALL_OP_DEF)
#undef BOOST_ASIO_PRIVATE_CALL_OP_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
};

// For completion signature void(exception_ptr, T1, ..., Tn);
template <typename T>
class promise_handler_ex_n
  : public promise_creator<T>
{
public:
#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename... Args>
  void operator()(const std::exception_ptr& ex,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    if (ex)
      this->p_->set_exception(ex);
    else
    {
      this->p_->set_value(
          std::forward_as_tuple(
            BOOST_ASIO_MOVE_CAST(Args)(args)...));
    }
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#define BOOST_ASIO_PRIVATE_CALL_OP_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(const std::exception_ptr& ex, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  {\
    if (ex) \
      this->p_->set_exception(ex); \
    else \
    { \
      this->p_->set_value( \
          std::forward_as_tuple( \
            BOOST_ASIO_VARIADIC_MOVE_ARGS(n))); \
    } \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CALL_OP_DEF)
#undef BOOST_ASIO_PRIVATE_CALL_OP_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
};

// Helper template to choose the appropriate concrete promise handler
// implementation based on the supplied completion signature.
template <typename> class promise_handler_selector;

template <>
class promise_handler_selector<void()>
  : public promise_handler_0 {};

template <>
class promise_handler_selector<void(boost::system::error_code)>
  : public promise_handler_ec_0 {};

template <>
class promise_handler_selector<void(std::exception_ptr)>
  : public promise_handler_ex_0 {};

template <typename Arg>
class promise_handler_selector<void(Arg)>
  : public promise_handler_1<Arg> {};

template <typename Arg>
class promise_handler_selector<void(boost::system::error_code, Arg)>
  : public promise_handler_ec_1<Arg> {};

template <typename Arg>
class promise_handler_selector<void(std::exception_ptr, Arg)>
  : public promise_handler_ex_1<Arg> {};

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename... Arg>
class promise_handler_selector<void(Arg...)>
  : public promise_handler_n<std::tuple<Arg...> > {};

template <typename... Arg>
class promise_handler_selector<void(boost::system::error_code, Arg...)>
  : public promise_handler_ec_n<std::tuple<Arg...> > {};

template <typename... Arg>
class promise_handler_selector<void(std::exception_ptr, Arg...)>
  : public promise_handler_ex_n<std::tuple<Arg...> > {};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#define BOOST_ASIO_PRIVATE_PROMISE_SELECTOR_DEF(n) \
  template <typename Arg, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  class promise_handler_selector< \
    void(Arg, BOOST_ASIO_VARIADIC_TARGS(n))> \
      : public promise_handler_n< \
        std::tuple<Arg, BOOST_ASIO_VARIADIC_TARGS(n)> > {}; \
  \
  template <typename Arg, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  class promise_handler_selector< \
    void(boost::system::error_code, Arg, BOOST_ASIO_VARIADIC_TARGS(n))> \
      : public promise_handler_ec_n< \
        std::tuple<Arg, BOOST_ASIO_VARIADIC_TARGS(n)> > {}; \
  \
  template <typename Arg, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  class promise_handler_selector< \
    void(std::exception_ptr, Arg, BOOST_ASIO_VARIADIC_TARGS(n))> \
      : public promise_handler_ex_n< \
        std::tuple<Arg, BOOST_ASIO_VARIADIC_TARGS(n)> > {}; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE_5(BOOST_ASIO_PRIVATE_PROMISE_SELECTOR_DEF)
#undef BOOST_ASIO_PRIVATE_PROMISE_SELECTOR_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

// Completion handlers produced from the use_future completion token, when not
// using use_future::operator().
template <typename Signature, typename Allocator>
class promise_handler
  : public promise_handler_selector<Signature>
{
public:
  typedef Allocator allocator_type;
  typedef void result_type;

  promise_handler(use_future_t<Allocator> u)
    : allocator_(u.get_allocator())
  {
    this->create_promise(allocator_);
  }

  allocator_type get_allocator() const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

private:
  Allocator allocator_;
};

template <typename Function>
struct promise_function_wrapper
{
  explicit promise_function_wrapper(Function& f)
    : function_(BOOST_ASIO_MOVE_CAST(Function)(f))
  {
  }

  explicit promise_function_wrapper(const Function& f)
    : function_(f)
  {
  }

  void operator()()
  {
    function_();
  }

  Function function_;
};

#if !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Function, typename Signature, typename Allocator>
inline void asio_handler_invoke(Function& f,
    promise_handler<Signature, Allocator>* h)
{
  typename promise_handler<Signature, Allocator>::executor_type
    ex(h->get_executor());
  boost::asio::dispatch(ex, promise_function_wrapper<Function>(f));
}

template <typename Function, typename Signature, typename Allocator>
inline void asio_handler_invoke(const Function& f,
    promise_handler<Signature, Allocator>* h)
{
  typename promise_handler<Signature, Allocator>::executor_type
    ex(h->get_executor());
  boost::asio::dispatch(ex, promise_function_wrapper<Function>(f));
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

// Helper base class for async_result specialisation.
template <typename Signature, typename Allocator>
class promise_async_result
{
public:
  typedef promise_handler<Signature, Allocator> completion_handler_type;
  typedef typename completion_handler_type::future_type return_type;

  explicit promise_async_result(completion_handler_type& h)
    : future_(h.get_future())
  {
  }

  return_type get()
  {
    return BOOST_ASIO_MOVE_CAST(return_type)(future_);
  }

private:
  return_type future_;
};

// Return value from use_future::operator().
template <typename Function, typename Allocator>
class packaged_token
{
public:
  packaged_token(Function f, const Allocator& a)
    : function_(BOOST_ASIO_MOVE_CAST(Function)(f)),
      allocator_(a)
  {
  }

//private:
  Function function_;
  Allocator allocator_;
};

// Completion handlers produced from the use_future completion token, when
// using use_future::operator().
template <typename Function, typename Allocator, typename Result>
class packaged_handler
  : public promise_creator<Result>
{
public:
  typedef Allocator allocator_type;
  typedef void result_type;

  packaged_handler(packaged_token<Function, Allocator> t)
    : function_(BOOST_ASIO_MOVE_CAST(Function)(t.function_)),
      allocator_(t.allocator_)
  {
    this->create_promise(allocator_);
  }

  allocator_type get_allocator() const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename... Args>
  void operator()(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    (promise_invoke_and_set)(*this->p_,
        function_, BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  void operator()()
  {
    (promise_invoke_and_set)(*this->p_, function_);
  }

#define BOOST_ASIO_PRIVATE_CALL_OP_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  {\
    (promise_invoke_and_set)(*this->p_, \
        function_, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_CALL_OP_DEF)
#undef BOOST_ASIO_PRIVATE_CALL_OP_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

private:
  Function function_;
  Allocator allocator_;
};

#if !defined(BOOST_ASIO_NO_DEPRECATED)

template <typename Function,
    typename Function1, typename Allocator, typename Result>
inline void asio_handler_invoke(Function& f,
    packaged_handler<Function1, Allocator, Result>* h)
{
  typename packaged_handler<Function1, Allocator, Result>::executor_type
    ex(h->get_executor());
  boost::asio::dispatch(ex, promise_function_wrapper<Function>(f));
}

template <typename Function,
    typename Function1, typename Allocator, typename Result>
inline void asio_handler_invoke(const Function& f,
    packaged_handler<Function1, Allocator, Result>* h)
{
  typename packaged_handler<Function1, Allocator, Result>::executor_type
    ex(h->get_executor());
  boost::asio::dispatch(ex, promise_function_wrapper<Function>(f));
}

#endif // !defined(BOOST_ASIO_NO_DEPRECATED)

// Helper base class for async_result specialisation.
template <typename Function, typename Allocator, typename Result>
class packaged_async_result
{
public:
  typedef packaged_handler<Function, Allocator, Result> completion_handler_type;
  typedef typename completion_handler_type::future_type return_type;

  explicit packaged_async_result(completion_handler_type& h)
    : future_(h.get_future())
  {
  }

  return_type get()
  {
    return BOOST_ASIO_MOVE_CAST(return_type)(future_);
  }

private:
  return_type future_;
};

} // namespace detail

template <typename Allocator> template <typename Function>
inline detail::packaged_token<typename decay<Function>::type, Allocator>
use_future_t<Allocator>::operator()(BOOST_ASIO_MOVE_ARG(Function) f) const
{
  return detail::packaged_token<typename decay<Function>::type, Allocator>(
      BOOST_ASIO_MOVE_CAST(Function)(f), allocator_);
}

#if !defined(GENERATING_DOCUMENTATION)

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Allocator, typename Result, typename... Args>
class async_result<use_future_t<Allocator>, Result(Args...)>
  : public detail::promise_async_result<
      void(typename decay<Args>::type...), Allocator>
{
public:
  explicit async_result(
    typename detail::promise_async_result<void(typename decay<Args>::type...),
      Allocator>::completion_handler_type& h)
    : detail::promise_async_result<
        void(typename decay<Args>::type...), Allocator>(h)
  {
  }
};

template <typename Function, typename Allocator,
    typename Result, typename... Args>
class async_result<detail::packaged_token<Function, Allocator>, Result(Args...)>
  : public detail::packaged_async_result<Function, Allocator,
      typename result_of<Function(Args...)>::type>
{
public:
  explicit async_result(
    typename detail::packaged_async_result<Function, Allocator,
      typename result_of<Function(Args...)>::type>::completion_handler_type& h)
    : detail::packaged_async_result<Function, Allocator,
        typename result_of<Function(Args...)>::type>(h)
  {
  }
};

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename Allocator, typename Result>
class async_result<use_future_t<Allocator>, Result()>
  : public detail::promise_async_result<void(), Allocator>
{
public:
  explicit async_result(
    typename detail::promise_async_result<
      void(), Allocator>::completion_handler_type& h)
    : detail::promise_async_result<void(), Allocator>(h)
  {
  }
};

template <typename Function, typename Allocator, typename Result>
class async_result<detail::packaged_token<Function, Allocator>, Result()>
  : public detail::packaged_async_result<Function, Allocator,
      typename result_of<Function()>::type>
{
public:
  explicit async_result(
    typename detail::packaged_async_result<Function, Allocator,
      typename result_of<Function()>::type>::completion_handler_type& h)
    : detail::packaged_async_result<Function, Allocator,
        typename result_of<Function()>::type>(h)
  {
  }
};

#define BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF(n) \
  template <typename Allocator, \
      typename Result, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  class async_result<use_future_t<Allocator>, \
      Result(BOOST_ASIO_VARIADIC_TARGS(n))> \
    : public detail::promise_async_result< \
        void(BOOST_ASIO_VARIADIC_DECAY(n)), Allocator> \
  { \
  public: \
    explicit async_result( \
      typename detail::promise_async_result< \
        void(BOOST_ASIO_VARIADIC_DECAY(n)), \
        Allocator>::completion_handler_type& h) \
      : detail::promise_async_result< \
          void(BOOST_ASIO_VARIADIC_DECAY(n)), Allocator>(h) \
    { \
    } \
  }; \
  \
  template <typename Function, typename Allocator, \
      typename Result, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  class async_result<detail::packaged_token<Function, Allocator>, \
      Result(BOOST_ASIO_VARIADIC_TARGS(n))> \
    : public detail::packaged_async_result<Function, Allocator, \
        typename result_of<Function(BOOST_ASIO_VARIADIC_TARGS(n))>::type> \
  { \
  public: \
    explicit async_result( \
      typename detail::packaged_async_result<Function, Allocator, \
        typename result_of<Function(BOOST_ASIO_VARIADIC_TARGS(n))>::type \
        >::completion_handler_type& h) \
      : detail::packaged_async_result<Function, Allocator, \
          typename result_of<Function(BOOST_ASIO_VARIADIC_TARGS(n))>::type>(h) \
    { \
    } \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF)
#undef BOOST_ASIO_PRIVATE_ASYNC_RESULT_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

namespace traits {

#if !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

template <typename T, typename Blocking>
struct equality_comparable<
    boost::asio::detail::promise_executor<T, Blocking> >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EQUALITY_COMPARABLE_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

template <typename T, typename Blocking, typename Function>
struct execute_member<
    boost::asio::detail::promise_executor<T, Blocking>, Function>
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = false);
  typedef void result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_EXECUTE_MEMBER_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_TRAIT)

template <typename T, typename Blocking, typename Property>
struct query_static_constexpr_member<
    boost::asio::detail::promise_executor<T, Blocking>,
    Property,
    typename boost::asio::enable_if<
      boost::asio::is_convertible<
        Property,
        boost::asio::execution::blocking_t
      >::value
    >::type
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef Blocking result_type;

  static BOOST_ASIO_CONSTEXPR result_type value() BOOST_ASIO_NOEXCEPT
  {
    return Blocking();
  }
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_QUERY_STATIC_CONSTEXPR_TRAIT)

#if !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

template <typename T, typename Blocking>
struct require_member<
    boost::asio::detail::promise_executor<T, Blocking>,
    execution::blocking_t::possibly_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::detail::promise_executor<T,
      execution::blocking_t::possibly_t> result_type;
};

template <typename T, typename Blocking>
struct require_member<
    boost::asio::detail::promise_executor<T, Blocking>,
    execution::blocking_t::never_t
  >
{
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_valid = true);
  BOOST_ASIO_STATIC_CONSTEXPR(bool, is_noexcept = true);
  typedef boost::asio::detail::promise_executor<T,
      execution::blocking_t::never_t> result_type;
};

#endif // !defined(BOOST_ASIO_HAS_DEDUCED_REQUIRE_MEMBER_TRAIT)

} // namespace traits

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_USE_FUTURE_HPP

/* use_future.hpp
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
*/