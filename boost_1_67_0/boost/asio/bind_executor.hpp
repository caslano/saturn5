//
// bind_executor.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/execution_context.hpp>
#include <boost/asio/is_executor.hpp>
#include <boost/asio/uses_executor.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename T>
struct executor_binder_check
{
  typedef void type;
};

// Helper to automatically define nested typedef result_type.

template <typename T, typename = void>
struct executor_binder_result_type
{
protected:
  typedef void result_type_or_void;
};

template <typename T>
struct executor_binder_result_type<T,
  typename executor_binder_check<typename T::result_type>::type>
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
  typename executor_binder_check<typename T::argument_type>::type>
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
  typename executor_binder_check<typename T::first_argument_type>::type>
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

// Helper to:
// - Apply the empty base optimisation to the executor.
// - Perform uses_executor construction of the target type, if required.

template <typename T, typename Executor, bool UsesExecutor>
class executor_binder_base;

template <typename T, typename Executor>
class executor_binder_base<T, Executor, true>
  : protected Executor
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
  typename executor_binder_check<typename result_of<T()>::type>::type>
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
inline executor_binder<typename decay<T>::type, Executor>
bind_executor(const Executor& ex, BOOST_ASIO_MOVE_ARG(T) t,
    typename enable_if<is_executor<Executor>::value>::type* = 0)
{
  return executor_binder<typename decay<T>::type, Executor>(
      executor_arg_t(), ex, BOOST_ASIO_MOVE_CAST(T)(t));
}

/// Associate an object of type @c T with an execution context's executor.
template <typename ExecutionContext, typename T>
inline executor_binder<typename decay<T>::type,
  typename ExecutionContext::executor_type>
bind_executor(ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(T) t,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type* = 0)
{
  return executor_binder<typename decay<T>::type,
    typename ExecutionContext::executor_type>(
      executor_arg_t(), ctx.get_executor(), BOOST_ASIO_MOVE_CAST(T)(t));
}

#if !defined(GENERATING_DOCUMENTATION)

template <typename T, typename Executor>
struct uses_executor<executor_binder<T, Executor>, Executor>
  : true_type {};

template <typename T, typename Executor, typename Signature>
class async_result<executor_binder<T, Executor>, Signature>
{
public:
  typedef executor_binder<
    typename async_result<T, Signature>::completion_handler_type, Executor>
      completion_handler_type;

  typedef typename async_result<T, Signature>::return_type return_type;

  explicit async_result(executor_binder<T, Executor>& b)
    : target_(b.get())
  {
  }

  return_type get()
  {
    return target_.get();
  }

private:
  async_result(const async_result&) BOOST_ASIO_DELETED;
  async_result& operator=(const async_result&) BOOST_ASIO_DELETED;

  async_result<T, Signature> target_;
};

template <typename T, typename Executor, typename Allocator>
struct associated_allocator<executor_binder<T, Executor>, Allocator>
{
  typedef typename associated_allocator<T, Allocator>::type type;

  static type get(const executor_binder<T, Executor>& b,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<T, Allocator>::get(b.get(), a);
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