//
// bind_allocator.hpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BIND_ALLOCATOR_HPP
#define BOOST_ASIO_BIND_ALLOCATOR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/async_result.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper to automatically define nested typedef result_type.

template <typename T, typename = void>
struct allocator_binder_result_type
{
protected:
  typedef void result_type_or_void;
};

template <typename T>
struct allocator_binder_result_type<T,
  typename void_type<typename T::result_type>::type>
{
  typedef typename T::result_type result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R>
struct allocator_binder_result_type<R(*)()>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R>
struct allocator_binder_result_type<R(&)()>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1>
struct allocator_binder_result_type<R(*)(A1)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1>
struct allocator_binder_result_type<R(&)(A1)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1, typename A2>
struct allocator_binder_result_type<R(*)(A1, A2)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1, typename A2>
struct allocator_binder_result_type<R(&)(A1, A2)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

// Helper to automatically define nested typedef argument_type.

template <typename T, typename = void>
struct allocator_binder_argument_type {};

template <typename T>
struct allocator_binder_argument_type<T,
  typename void_type<typename T::argument_type>::type>
{
  typedef typename T::argument_type argument_type;
};

template <typename R, typename A1>
struct allocator_binder_argument_type<R(*)(A1)>
{
  typedef A1 argument_type;
};

template <typename R, typename A1>
struct allocator_binder_argument_type<R(&)(A1)>
{
  typedef A1 argument_type;
};

// Helper to automatically define nested typedefs first_argument_type and
// second_argument_type.

template <typename T, typename = void>
struct allocator_binder_argument_types {};

template <typename T>
struct allocator_binder_argument_types<T,
  typename void_type<typename T::first_argument_type>::type>
{
  typedef typename T::first_argument_type first_argument_type;
  typedef typename T::second_argument_type second_argument_type;
};

template <typename R, typename A1, typename A2>
struct allocator_binder_argument_type<R(*)(A1, A2)>
{
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
};

template <typename R, typename A1, typename A2>
struct allocator_binder_argument_type<R(&)(A1, A2)>
{
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
};

// Helper to enable SFINAE on zero-argument operator() below.

template <typename T, typename = void>
struct allocator_binder_result_of0
{
  typedef void type;
};

template <typename T>
struct allocator_binder_result_of0<T,
  typename void_type<typename result_of<T()>::type>::type>
{
  typedef typename result_of<T()>::type type;
};

} // namespace detail

/// A call wrapper type to bind an allocator of type @c Allocator
/// to an object of type @c T.
template <typename T, typename Allocator>
class allocator_binder
#if !defined(GENERATING_DOCUMENTATION)
  : public detail::allocator_binder_result_type<T>,
    public detail::allocator_binder_argument_type<T>,
    public detail::allocator_binder_argument_types<T>
#endif // !defined(GENERATING_DOCUMENTATION)
{
public:
  /// The type of the target object.
  typedef T target_type;

  /// The type of the associated allocator.
  typedef Allocator allocator_type;

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

  /// Construct an allocator wrapper for the specified object.
  /**
   * This constructor is only valid if the type @c T is constructible from type
   * @c U.
   */
  template <typename U>
  allocator_binder(const allocator_type& s,
      BOOST_ASIO_MOVE_ARG(U) u)
    : allocator_(s),
      target_(BOOST_ASIO_MOVE_CAST(U)(u))
  {
  }

  /// Copy constructor.
  allocator_binder(const allocator_binder& other)
    : allocator_(other.get_allocator()),
      target_(other.get())
  {
  }

  /// Construct a copy, but specify a different allocator.
  allocator_binder(const allocator_type& s,
      const allocator_binder& other)
    : allocator_(s),
      target_(other.get())
  {
  }

  /// Construct a copy of a different allocator wrapper type.
  /**
   * This constructor is only valid if the @c Allocator type is
   * constructible from type @c OtherAllocator, and the type @c T is
   * constructible from type @c U.
   */
  template <typename U, typename OtherAllocator>
  allocator_binder(
      const allocator_binder<U, OtherAllocator>& other)
    : allocator_(other.get_allocator()),
      target_(other.get())
  {
  }

  /// Construct a copy of a different allocator wrapper type, but
  /// specify a different allocator.
  /**
   * This constructor is only valid if the type @c T is constructible from type
   * @c U.
   */
  template <typename U, typename OtherAllocator>
  allocator_binder(const allocator_type& s,
      const allocator_binder<U, OtherAllocator>& other)
    : allocator_(s),
      target_(other.get())
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Move constructor.
  allocator_binder(allocator_binder&& other)
    : allocator_(BOOST_ASIO_MOVE_CAST(allocator_type)(
          other.get_allocator())),
      target_(BOOST_ASIO_MOVE_CAST(T)(other.get()))
  {
  }

  /// Move construct the target object, but specify a different allocator.
  allocator_binder(const allocator_type& s,
      allocator_binder&& other)
    : allocator_(s),
      target_(BOOST_ASIO_MOVE_CAST(T)(other.get()))
  {
  }

  /// Move construct from a different allocator wrapper type.
  template <typename U, typename OtherAllocator>
  allocator_binder(
      allocator_binder<U, OtherAllocator>&& other)
    : allocator_(BOOST_ASIO_MOVE_CAST(OtherAllocator)(
          other.get_allocator())),
      target_(BOOST_ASIO_MOVE_CAST(U)(other.get()))
  {
  }

  /// Move construct from a different allocator wrapper type, but
  /// specify a different allocator.
  template <typename U, typename OtherAllocator>
  allocator_binder(const allocator_type& s,
      allocator_binder<U, OtherAllocator>&& other)
    : allocator_(s),
      target_(BOOST_ASIO_MOVE_CAST(U)(other.get()))
  {
  }

#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~allocator_binder()
  {
  }

  /// Obtain a reference to the target object.
  target_type& get() BOOST_ASIO_NOEXCEPT
  {
    return target_;
  }

  /// Obtain a reference to the target object.
  const target_type& get() const BOOST_ASIO_NOEXCEPT
  {
    return target_;
  }

  /// Obtain the associated allocator.
  allocator_type get_allocator() const BOOST_ASIO_NOEXCEPT
  {
    return allocator_;
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
    return target_(BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

  /// Forwarding function call operator.
  template <typename... Args>
  typename result_of<T(Args...)>::type operator()(
      BOOST_ASIO_MOVE_ARG(Args)... args) const
  {
    return target_(BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#elif defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS) && !defined(_MSC_VER)

  typename detail::allocator_binder_result_of0<T>::type operator()()
  {
    return target_();
  }

  typename detail::allocator_binder_result_of0<T>::type
  operator()() const
  {
    return target_();
  }

#define BOOST_ASIO_PRIVATE_BINDER_CALL_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename result_of<T(BOOST_ASIO_VARIADIC_TARGS(n))>::type operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename result_of<T(BOOST_ASIO_VARIADIC_TARGS(n))>::type operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
  { \
    return target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_BINDER_CALL_DEF)
#undef BOOST_ASIO_PRIVATE_BINDER_CALL_DEF

#else // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS) && !defined(_MSC_VER)

  typedef typename detail::allocator_binder_result_type<
    T>::result_type_or_void result_type_or_void;

  result_type_or_void operator()()
  {
    return target_();
  }

  result_type_or_void operator()() const
  {
    return target_();
  }

#define BOOST_ASIO_PRIVATE_BINDER_CALL_DEF(n) \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  result_type_or_void operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  result_type_or_void operator()( \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
  { \
    return target_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_BINDER_CALL_DEF)
#undef BOOST_ASIO_PRIVATE_BINDER_CALL_DEF

#endif // defined(BOOST_ASIO_HAS_STD_TYPE_TRAITS) && !defined(_MSC_VER)

private:
  Allocator allocator_;
  T target_;
};

/// Associate an object of type @c T with an allocator of type
/// @c Allocator.
template <typename Allocator, typename T>
BOOST_ASIO_NODISCARD inline allocator_binder<typename decay<T>::type, Allocator>
bind_allocator(const Allocator& s, BOOST_ASIO_MOVE_ARG(T) t)
{
  return allocator_binder<
    typename decay<T>::type, Allocator>(
      s, BOOST_ASIO_MOVE_CAST(T)(t));
}

#if !defined(GENERATING_DOCUMENTATION)

namespace detail {

template <typename TargetAsyncResult,
  typename Allocator, typename = void>
struct allocator_binder_async_result_completion_handler_type
{
};

template <typename TargetAsyncResult, typename Allocator>
struct allocator_binder_async_result_completion_handler_type<
  TargetAsyncResult, Allocator,
  typename void_type<
    typename TargetAsyncResult::completion_handler_type
  >::type>
{
  typedef allocator_binder<
    typename TargetAsyncResult::completion_handler_type, Allocator>
      completion_handler_type;
};

template <typename TargetAsyncResult, typename = void>
struct allocator_binder_async_result_return_type
{
};

template <typename TargetAsyncResult>
struct allocator_binder_async_result_return_type<
  TargetAsyncResult,
  typename void_type<
    typename TargetAsyncResult::return_type
  >::type>
{
  typedef typename TargetAsyncResult::return_type return_type;
};

} // namespace detail

template <typename T, typename Allocator, typename Signature>
class async_result<allocator_binder<T, Allocator>, Signature> :
  public detail::allocator_binder_async_result_completion_handler_type<
    async_result<T, Signature>, Allocator>,
  public detail::allocator_binder_async_result_return_type<
    async_result<T, Signature> >
{
public:
  explicit async_result(allocator_binder<T, Allocator>& b)
    : target_(b.get())
  {
  }

  typename async_result<T, Signature>::return_type get()
  {
    return target_.get();
  }

  template <typename Initiation>
  struct init_wrapper
  {
    template <typename Init>
    init_wrapper(const Allocator& allocator, BOOST_ASIO_MOVE_ARG(Init) init)
      : allocator_(allocator),
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
          allocator_binder<
            typename decay<Handler>::type, Allocator>(
              allocator_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler,
        BOOST_ASIO_MOVE_ARG(Args)... args) const
    {
      initiation_(
          allocator_binder<
            typename decay<Handler>::type, Allocator>(
              allocator_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          allocator_binder<
            typename decay<Handler>::type, Allocator>(
              allocator_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler) const
    {
      initiation_(
          allocator_binder<
            typename decay<Handler>::type, Allocator>(
              allocator_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

#define BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF(n) \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)( \
          allocator_binder< \
            typename decay<Handler>::type, Allocator>( \
              allocator_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    { \
      initiation_( \
          allocator_binder< \
            typename decay<Handler>::type, Allocator>( \
              allocator_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF)
#undef BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    Allocator allocator_;
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
          token.get_allocator(),
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
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
          token.get_allocator(),
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
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
          token.get_allocator(), \
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation)), \
        token.get(), BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INITIATE_DEF)
#undef BOOST_ASIO_PRIVATE_INITIATE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

private:
  async_result(const async_result&) BOOST_ASIO_DELETED;
  async_result& operator=(const async_result&) BOOST_ASIO_DELETED;

  async_result<T, Signature> target_;
};

template <template <typename, typename> class Associator,
    typename T, typename Allocator, typename DefaultCandidate>
struct associator<Associator,
    allocator_binder<T, Allocator>,
    DefaultCandidate>
{
  typedef typename Associator<T, DefaultCandidate>::type type;

  static type get(const allocator_binder<T, Allocator>& b,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<T, DefaultCandidate>::get(b.get(), c);
  }
};

template <typename T, typename Allocator, typename Allocator1>
struct associated_allocator<
    allocator_binder<T, Allocator>,
    Allocator1>
{
  typedef Allocator type;

  static type get(const allocator_binder<T, Allocator>& b,
      const Allocator1& = Allocator1()) BOOST_ASIO_NOEXCEPT
  {
    return b.get_allocator();
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BIND_ALLOCATOR_HPP

/* bind_allocator.hpp
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
*/