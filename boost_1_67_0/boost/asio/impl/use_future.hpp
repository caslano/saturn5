//
// impl/use_future.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/system/error_code.hpp>
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
template <typename T>
class promise_executor
{
public:
  explicit promise_executor(const shared_ptr<std::promise<T> >& p)
    : p_(p)
  {
  }

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
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_PROMISE_SELECTOR_DEF)
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

template <typename Function, typename Signature, typename Allocator>
inline void asio_handler_invoke(Function& f,
    promise_handler<Signature, Allocator>* h)
{
  typename promise_handler<Signature, Allocator>::executor_type
    ex(h->get_executor());
  ex.dispatch(BOOST_ASIO_MOVE_CAST(Function)(f), std::allocator<void>());
}

template <typename Function, typename Signature, typename Allocator>
inline void asio_handler_invoke(const Function& f,
    promise_handler<Signature, Allocator>* h)
{
  typename promise_handler<Signature, Allocator>::executor_type
    ex(h->get_executor());
  ex.dispatch(f, std::allocator<void>());
}

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

template <typename Function,
    typename Function1, typename Allocator, typename Result>
inline void asio_handler_invoke(Function& f,
    packaged_handler<Function1, Allocator, Result>* h)
{
  typename packaged_handler<Function1, Allocator, Result>::executor_type
    ex(h->get_executor());
  ex.dispatch(BOOST_ASIO_MOVE_CAST(Function)(f), std::allocator<void>());
}

template <typename Function,
    typename Function1, typename Allocator, typename Result>
inline void asio_handler_invoke(const Function& f,
    packaged_handler<Function1, Allocator, Result>* h)
{
  typename packaged_handler<Function1, Allocator, Result>::executor_type
    ex(h->get_executor());
  ex.dispatch(f, std::allocator<void>());
}

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

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_USE_FUTURE_HPP

/* use_future.hpp
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
*/