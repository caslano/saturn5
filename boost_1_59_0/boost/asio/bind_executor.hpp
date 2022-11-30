//
// bind_executor.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BIND_EXECUTOR_HPP
#define BOOST_ASIO_BIND_EXECUTOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/execution/executor.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/uses_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper to automatically define nested typedef result_type.

template <typename T, typename = void>
struct executor_binder_result_type
{
protected:
  typedef void result_type_or_void;
};

template <typename T>
struct executor_binder_result_type<T,
  typename void_type<typename T::result_type>::type>
{
  typedef typename T::result_type result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R>
struct executor_binder_result_type<R(*)()>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R>
struct executor_binder_result_type<R(&)()>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1>
struct executor_binder_result_type<R(*)(A1)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1>
struct executor_binder_result_type<R(&)(A1)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1, typename A2>
struct executor_binder_result_type<R(*)(A1, A2)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1, typename A2>
struct executor_binder_result_type<R(&)(A1, A2)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

// Helper to automatically define nested typedef argument_type.

template <typename T, typename = void>
struct executor_binder_argument_type {};

template <typename T>
struct executor_binder_argument_type<T,
  typename void_type<typename T::argument_type>::type>
{
  typedef typename T::argument_type argument_type;
};

template <typename R, typename A1>
struct executor_binder_argument_type<R(*)(A1)>
{
  typedef A1 argument_type;
};

template <typename R, typename A1>
struct executor_binder_argument_type<R(&)(A1)>
{
  typedef A1 argument_type;
};

// Helper to automatically define nested typedefs first_argument_type and
// second_argument_type.

template <typename T, typename = void>
struct executor_binder_argument_types {};

template <typename T>
struct executor_binder_argument_types<T,
  typename void_type<typename T::first_argument_type>::type>
{
  typedef typename T::first_argument_type first_argument_type;
  typedef typename T::second_argument_type second_argument_type;
};

template <typename R, typename A1, typename A2>
struct executor_binder_argument_type<R(*)(A1, A2)>
{
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
};

template <typename R, typename A1, typename A2>
struct executor_binder_argument_type<R(&)(A1, A2)>
{
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
};

// Helper to perform uses_executor construction of the target type, if
// required.

template <typename T, typename Executor, bool UsesExecutor>
class executor_binder_base;

template <typename T, typename Executor>
class executor_binder_base<T, Executor, true>
{
protected:
  template <typename E, typename U>
  executor_binder_base(BOOST_ASIO_MOVE_ARG(E) e, BOOST_ASIO_MOVE_ARG(U) u)
    : executor_(BOOST_ASIO_MOVE_CAST(E)(e)),
      target_(executor_arg_t(), executor_, BOOST_ASIO_MOVE_CAST(U)(u))
  {
  }

  Executor executor_;
  T target_;
};

template <typename T, typename Executor>
class executor_binder_base<T, Executor, false>
{
protected:
  template <typename E, typename U>
  executor_binder_base(BOOST_ASIO_MOVE_ARG(E) e, BOOST_ASIO_MOVE_ARG(U) u)
    : executor_(BOOST_ASIO_MOVE_CAST(E)(e)),
      target_(BOOST_ASIO_MOVE_CAST(U)(u))
  {
  }

  Executor executor_;
  T target_;
};

// Helper to enable SFINAE on zero-argument operator() below.

template <typename T, typename = void>
struct executor_binder_result_of0
{
  typedef void type;
};

template <typename T>
struct executor_binder_result_of0<T,
  typename void_type<typename result_of<T()>::type>::type>
{
  typedef typename result_of<T()>::type type;
};

} // namespace detail

/// A call wrapper type to bind an executor of type @c Executor to an object of
/// type @c T.
template <typename T, typename Executor>
class executor_binder
#if !defined(GENERATING_DOCUMENTATION)
  : public detail::executor_binder_result_type<T>,
    public detail::executor_binder_argument_type<T>,
    public detail::executor_binder_argument_types<T>,
    private detail::executor_binder_base<
      T, Executor, uses_executor<T, Executor>::value>
#endif // !defined(GENERATING_DOCUMENTATION)
{
public:
  /// The type of the target object.
  typedef T target_type;

  /// The type of the associated executor.
  typedef Executor executor_type;

#if defined(GENERATING_DOCUMENTATION)
  /// The return type if a function.
  /**
   * The type of @c result_type is based on the type @c T of the wrapper's
   * target object:
   *
   * @li if @c T is a pointer to function type, @c result_type is a synonym for
   * the return type of @c T;
   *
   * @li if @c T is a class type with a member type @c result_type, then @c
   * result_type is a synonym for @c T::result_type;
   *
   * @li otherwise @c result_type is not defined.
   */
  typedef see_below result_type;

  /// The type of the function's argument.
  /**
   * The type of @c argument_type is based on the type @c T of the wrapper's
   * target object:
   *
   * @li if @c T is a pointer to a function type accepting a single argument,
   * @c argument_type is a synonym for the return type of @c T;
   *
   * @li if @c T is a class type with a member type @c argument_type, then @c
   * argument_type is a synonym for @c T::argument_type;
   *
   * @li otherwise @c argument_type is not defined.
   */
  typedef see_below argument_type;

  /// The type of the function's first argument.
  /**
   * The type of @c first_argument_type is based on the type @c T of the
   * wrapper's target object:
   *
   * @li if @c T is a pointer to a function type accepting two arguments, @c
   * first_argument_type is a synonym for the return type of @c T;
   *
   * @li if @c T is a class type with a member type @c first_argument_type,
   * then @c first_argument_type is a synonym for @c T::first_argument_type;
   *
   * @li otherwise @c first_argument_type is not defined.
   */
  typedef see_below first_argument_type;

  /// The type of the function's second argument.
  /**
   * The type of @c second_argument_type is based on the type @c T of the
   * wrapper's target object:
   *
   * @li if @c T is a pointer to a function type accepting two arguments, @c
   * second_argument_type is a synonym for the return type of @c T;
   *
   * @li if @c T is a class type with a member type @c first_argument_type,
   * then @c second_argument_type is a synonym for @c T::second_argument_type;
   *
   * @li otherwise @c second_argument_type is not defined.
   */
  typedef see_below second_argument_type;
#endif // defined(GENERATING_DOCUMENTATION)

  /// Construct an executor wrapper for the specified object.
  /**
   * This constructor is only valid if the type @c T is constructible from type
   * @c U.
   */
  template <typename U>
  executor_binder(executor_arg_t, const executor_type& e,
      BOOST_ASIO_MOVE_ARG(U) u)
    : base_type(e, BOOST_ASIO_MOVE_CAST(U)(u))
  {
  }

  /// Copy constructor.
  executor_binder(const executor_binder& other)
    : base_type(other.get_executor(), other.get())
  {
  }

  /// Construct a copy, but specify a different executor.
  executor_binder(executor_arg_t, const executor_type& e,
      const executor_binder& other)
    : base_type(e, other.get())
  {
  }

  /// Construct a copy of a different executor wrapper type.
  /**
   * This constructor is only valid if the @c Executor type is constructible
   * from type @c OtherExecutor, and the type @c T is constructible from type
   * @c U.
   */
  template <typename U, typename OtherExecutor>
  executor_binder(const executor_binder<U, OtherExecutor>& other)
    : base_type(other.get_executor(), other.get())
  {
  }

  /// Construct a copy of a different executor wrapper type, but specify a
  /// different executor.
  /**
   * This constructor is only valid if the type @c T is constructible from type
   * @c U.
   */
  template <typename U, typename OtherExecutor>
  executor_binder(executor_arg_t, const executor_type& e,
      const executor_binder<U, OtherExecutor>& other)
    : base_type(e, other.get())
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Move constructor.
  executor_binder(executor_binder&& other)
    : base_type(BOOST_ASIO_MOVE_CAST(executor_type)(other.get_executor()),
        BOOST_ASIO_MOVE_CAST(T)(other.get()))
  {
  }

  /// Move construct the target object, but specify a different executor.
  executor_binder(executor_arg_t, const executor_type& e,
      executor_binder&& other)
    : base_type(e, BOOST_ASIO_MOVE_CAST(T)(other.get()))
  {
  }

  /// Move construct from a different executor wrapper type.
  template <typename U, typename OtherExecutor>
  executor_binder(executor_binder<U, OtherExecutor>&& other)
    : base_type(BOOST_ASIO_MOVE_CAST(OtherExecutor)(other.get_executor()),
        BOOST_ASIO_MOVE_CAST(U)(other.get()))
  {
  }

  /// Move construct from a different executor wrapper type, but specify a
  /// different executor.
  template <typename U, typename OtherExecutor>
  executor_binder(executor_arg_t, const executor_type& e,
      executor_binder<U, OtherExecutor>&& other)
    : base_type(e, BOOST_ASIO_MOVE_CAST(U)(other.get()))
  {
  }

#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~executor_binder()
  {
  }

  /// Obtain a reference to the target object.
  target_type& get() BOOST_ASIO_NOEXCEPT
  {
    return this->target_;
  }

  /// Obtain a reference to the target object.
  const target_type& get() const BOOST_ASIO_NOEXCEPT
  {
    return this->target_;
  }

  /// Obtain the associated executor.
  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return this->executor_;
  }

#if defined(GENERATING_DOCUMENTATION)

  template <typename... Args> auto operator()(Args&& ...);
  template <typename... Args> auto operator()(Args&& ...) const;

#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  /// Forwarding function call operator.
  template <typename... Args>
  typename result_of<T(Args...)>::type operator()(
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return this->target_(BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

  /// Forwarding function call operator.
  template <typename... Args>
  typename result_of<T(Args...)>::type operator()(
      BOOST_ASIO_MOVE_ARG(Args)... args) const
  {
    return this->target_(BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#elif defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS) && !defined(_MSC_VER)

  typename detail::executor_binder_result_of0<T>::type operator()()
  {
    return this->target_();
  }

  typename detail::executor_binder_result_of0<T>::type operator()() const
  {
    return this->target_();
  }

#define BOOST_ASIO_PRIVATE_BIND_EXECUTOR_CALL_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename result_of<T(BOOST_ASIO_VARIADIC_TARGS(n))>::type operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return this->target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename result_of<T(BOOST_ASIO_VARIADIC_TARGS(n))>::type operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
  { \
    return this->target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_BIND_EXECUTOR_CALL_DEF)
#undef BOOST_ASIO_PRIVATE_BIND_EXECUTOR_CALL_DEF

#else // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS) && !defined(_MSC_VER)

  typedef typename detail::executor_binder_result_type<T>::result_type_or_void
    result_type_or_void;

  result_type_or_void operator()()
  {
    return this->target_();
  }

  result_type_or_void operator()() const
  {
    return this->target_();
  }

#define BOOST_ASIO_PRIVATE_BIND_EXECUTOR_CALL_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  result_type_or_void operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return this->target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  result_type_or_void operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
  { \
    return this->target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_BIND_EXECUTOR_CALL_DEF)
#undef BOOST_ASIO_PRIVATE_BIND_EXECUTOR_CALL_DEF

#endif // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS) && !defined(_MSC_VER)

private:
  typedef detail::executor_binder_base<T, Executor,
    uses_executor<T, Executor>::value> base_type;
};

/// Associate an object of type @c T with an executor of type @c Executor.
template <typename Executor, typename T>
BOOST_ASIO_NODISCARD inline executor_binder<typename decay<T>::type, Executor>
bind_executor(const Executor& ex, BOOST_ASIO_MOVE_ARG(T) t,
    typename constraint<
      is_executor<Executor>::value || execution::is_executor<Executor>::value
    >::type = 0)
{
  return executor_binder<typename decay<T>::type, Executor>(
      executor_arg_t(), ex, BOOST_ASIO_MOVE_CAST(T)(t));
}

/// Associate an object of type @c T with an execution context's executor.
template <typename ExecutionContext, typename T>
BOOST_ASIO_NODISCARD inline executor_binder<typename decay<T>::type,
  typename ExecutionContext::executor_type>
bind_executor(ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(T) t,
    typename constraint<is_convertible<
      ExecutionContext&, execution_context&>::value>::type = 0)
{
  return executor_binder<typename decay<T>::type,
    typename ExecutionContext::executor_type>(
      executor_arg_t(), ctx.get_executor(), BOOST_ASIO_MOVE_CAST(T)(t));
}

#if !defined(GENERATING_DOCUMENTATION)

template <typename T, typename Executor>
struct uses_executor<executor_binder<T, Executor>, Executor>
  : true_type {};

namespace detail {

template <typename TargetAsyncResult, typename Executor, typename = void>
class executor_binder_completion_handler_async_result
{
public:
  template <typename T>
  explicit executor_binder_completion_handler_async_result(T&)
  {
  }
};

template <typename TargetAsyncResult, typename Executor>
class executor_binder_completion_handler_async_result<
  TargetAsyncResult, Executor,
  typename void_type<
    typename TargetAsyncResult::completion_handler_type
  >::type>
{
public:
  typedef executor_binder<
    typename TargetAsyncResult::completion_handler_type, Executor>
      completion_handler_type;

  explicit executor_binder_completion_handler_async_result(
      typename TargetAsyncResult::completion_handler_type& handler)
    : target_(handler)
  {
  }

  typename TargetAsyncResult::return_type get()
  {
    return target_.get();
  }

private:
  TargetAsyncResult target_;
};

template <typename TargetAsyncResult, typename = void>
struct executor_binder_async_result_return_type
{
};

template <typename TargetAsyncResult>
struct executor_binder_async_result_return_type<
  TargetAsyncResult,
  typename void_type<
    typename TargetAsyncResult::return_type
  >::type>
{
  typedef typename TargetAsyncResult::return_type return_type;
};

} // namespace detail

template <typename T, typename Executor, typename Signature>
class async_result<executor_binder<T, Executor>, Signature> :
  public detail::executor_binder_completion_handler_async_result<
    async_result<T, Signature>, Executor>,
  public detail::executor_binder_async_result_return_type<
    async_result<T, Signature> >
{
public:
  explicit async_result(executor_binder<T, Executor>& b)
    : detail::executor_binder_completion_handler_async_result<
        async_result<T, Signature>, Executor>(b.get())
  {
  }

  template <typename Initiation>
  struct init_wrapper
  {
    template <typename Init>
    init_wrapper(const Executor& ex, BOOST_ASIO_MOVE_ARG(Init) init)
      : ex_(ex),
        initiation_(BOOST_ASIO_MOVE_CAST(Init)(init))
    {
    }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template <typename Handler, typename... Args>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler,
        BOOST_ASIO_MOVE_ARG(Args)... args)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          executor_binder<typename decay<Handler>::type, Executor>(
            executor_arg_t(), ex_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler,
        BOOST_ASIO_MOVE_ARG(Args)... args) const
    {
      initiation_(
          executor_binder<typename decay<Handler>::type, Executor>(
            executor_arg_t(), ex_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          executor_binder<typename decay<Handler>::type, Executor>(
            executor_arg_t(), ex_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler) const
    {
      initiation_(
          executor_binder<typename decay<Handler>::type, Executor>(
            executor_arg_t(), ex_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

#define BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF(n) \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)( \
          executor_binder<typename decay<Handler>::type, Executor>( \
            executor_arg_t(), ex_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    { \
      initiation_( \
          executor_binder<typename decay<Handler>::type, Executor>( \
            executor_arg_t(), ex_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF)
#undef BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    Executor ex_;
    Initiation initiation_;
  };

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(T, Signature,
    (async_initiate<T, Signature>(
        declval<init_wrapper<typename decay<Initiation>::type> >(),
        declval<RawCompletionToken>().get(),
        declval<BOOST_ASIO_MOVE_ARG(Args)>()...)))
  initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return async_initiate<T, Signature>(
        init_wrapper<typename decay<Initiation>::type>(
          token.get_executor(), BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.get(), BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken>
  static BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(T, Signature,
    (async_initiate<T, Signature>(
        declval<init_wrapper<typename decay<Initiation>::type> >(),
        declval<RawCompletionToken>().get())))
  initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token)
  {
    return async_initiate<T, Signature>(
        init_wrapper<typename decay<Initiation>::type>(
          token.get_executor(), BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.get());
  }

#define BOOST_ASIO_PRIVATE_INITIATE_DEF(n) \
  template <typename Initiation, typename RawCompletionToken, \
      BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  static BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(T, Signature, \
    (async_initiate<T, Signature>( \
        declval<init_wrapper<typename decay<Initiation>::type> >(), \
        declval<RawCompletionToken>().get(), \
        BOOST_ASIO_VARIADIC_MOVE_DECLVAL(n)))) \
  initiate( \
      BOOST_ASIO_MOVE_ARG(Initiation) initiation, \
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return async_initiate<T, Signature>( \
        init_wrapper<typename decay<Initiation>::type>( \
          token.get_executor(), BOOST_ASIO_MOVE_CAST(Initiation)(initiation)), \
        token.get(), BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INITIATE_DEF)
#undef BOOST_ASIO_PRIVATE_INITIATE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

private:
  async_result(const async_result&) BOOST_ASIO_DELETED;
  async_result& operator=(const async_result&) BOOST_ASIO_DELETED;
};

template <template <typename, typename> class Associator,
    typename T, typename Executor, typename DefaultCandidate>
struct associator<Associator, executor_binder<T, Executor>, DefaultCandidate>
{
  typedef typename Associator<T, DefaultCandidate>::type type;

  static type get(const executor_binder<T, Executor>& b,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<T, DefaultCandidate>::get(b.get(), c);
  }
};

template <typename T, typename Executor, typename Executor1>
struct associated_executor<executor_binder<T, Executor>, Executor1>
{
  typedef Executor type;

  static type get(const executor_binder<T, Executor>& b,
      const Executor1& = Executor1()) BOOST_ASIO_NOEXCEPT
  {
    return b.get_executor();
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BIND_EXECUTOR_HPP

/* bind_executor.hpp
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
*/