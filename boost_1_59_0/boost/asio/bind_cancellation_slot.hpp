//
// bind_cancellation_slot.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_BIND_CANCELLATION_SLOT_HPP
#define BOOST_ASIO_BIND_CANCELLATION_SLOT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/asio/associated_cancellation_slot.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/async_result.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Helper to automatically define nested typedef result_type.

template <typename T, typename = void>
struct cancellation_slot_binder_result_type
{
protected:
  typedef void result_type_or_void;
};

template <typename T>
struct cancellation_slot_binder_result_type<T,
  typename void_type<typename T::result_type>::type>
{
  typedef typename T::result_type result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R>
struct cancellation_slot_binder_result_type<R(*)()>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R>
struct cancellation_slot_binder_result_type<R(&)()>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1>
struct cancellation_slot_binder_result_type<R(*)(A1)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1>
struct cancellation_slot_binder_result_type<R(&)(A1)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1, typename A2>
struct cancellation_slot_binder_result_type<R(*)(A1, A2)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

template <typename R, typename A1, typename A2>
struct cancellation_slot_binder_result_type<R(&)(A1, A2)>
{
  typedef R result_type;
protected:
  typedef result_type result_type_or_void;
};

// Helper to automatically define nested typedef argument_type.

template <typename T, typename = void>
struct cancellation_slot_binder_argument_type {};

template <typename T>
struct cancellation_slot_binder_argument_type<T,
  typename void_type<typename T::argument_type>::type>
{
  typedef typename T::argument_type argument_type;
};

template <typename R, typename A1>
struct cancellation_slot_binder_argument_type<R(*)(A1)>
{
  typedef A1 argument_type;
};

template <typename R, typename A1>
struct cancellation_slot_binder_argument_type<R(&)(A1)>
{
  typedef A1 argument_type;
};

// Helper to automatically define nested typedefs first_argument_type and
// second_argument_type.

template <typename T, typename = void>
struct cancellation_slot_binder_argument_types {};

template <typename T>
struct cancellation_slot_binder_argument_types<T,
  typename void_type<typename T::first_argument_type>::type>
{
  typedef typename T::first_argument_type first_argument_type;
  typedef typename T::second_argument_type second_argument_type;
};

template <typename R, typename A1, typename A2>
struct cancellation_slot_binder_argument_type<R(*)(A1, A2)>
{
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
};

template <typename R, typename A1, typename A2>
struct cancellation_slot_binder_argument_type<R(&)(A1, A2)>
{
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
};

// Helper to enable SFINAE on zero-argument operator() below.

template <typename T, typename = void>
struct cancellation_slot_binder_result_of0
{
  typedef void type;
};

template <typename T>
struct cancellation_slot_binder_result_of0<T,
  typename void_type<typename result_of<T()>::type>::type>
{
  typedef typename result_of<T()>::type type;
};

} // namespace detail

/// A call wrapper type to bind a cancellation slot of type @c CancellationSlot
/// to an object of type @c T.
template <typename T, typename CancellationSlot>
class cancellation_slot_binder
#if !defined(GENERATING_DOCUMENTATION)
  : public detail::cancellation_slot_binder_result_type<T>,
    public detail::cancellation_slot_binder_argument_type<T>,
    public detail::cancellation_slot_binder_argument_types<T>
#endif // !defined(GENERATING_DOCUMENTATION)
{
public:
  /// The type of the target object.
  typedef T target_type;

  /// The type of the associated cancellation slot.
  typedef CancellationSlot cancellation_slot_type;

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

  /// Construct a cancellation slot wrapper for the specified object.
  /**
   * This constructor is only valid if the type @c T is constructible from type
   * @c U.
   */
  template <typename U>
  cancellation_slot_binder(const cancellation_slot_type& s,
      BOOST_ASIO_MOVE_ARG(U) u)
    : slot_(s),
      target_(BOOST_ASIO_MOVE_CAST(U)(u))
  {
  }

  /// Copy constructor.
  cancellation_slot_binder(const cancellation_slot_binder& other)
    : slot_(other.get_cancellation_slot()),
      target_(other.get())
  {
  }

  /// Construct a copy, but specify a different cancellation slot.
  cancellation_slot_binder(const cancellation_slot_type& s,
      const cancellation_slot_binder& other)
    : slot_(s),
      target_(other.get())
  {
  }

  /// Construct a copy of a different cancellation slot wrapper type.
  /**
   * This constructor is only valid if the @c CancellationSlot type is
   * constructible from type @c OtherCancellationSlot, and the type @c T is
   * constructible from type @c U.
   */
  template <typename U, typename OtherCancellationSlot>
  cancellation_slot_binder(
      const cancellation_slot_binder<U, OtherCancellationSlot>& other)
    : slot_(other.get_cancellation_slot()),
      target_(other.get())
  {
  }

  /// Construct a copy of a different cancellation slot wrapper type, but
  /// specify a different cancellation slot.
  /**
   * This constructor is only valid if the type @c T is constructible from type
   * @c U.
   */
  template <typename U, typename OtherCancellationSlot>
  cancellation_slot_binder(const cancellation_slot_type& s,
      const cancellation_slot_binder<U, OtherCancellationSlot>& other)
    : slot_(s),
      target_(other.get())
  {
  }

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Move constructor.
  cancellation_slot_binder(cancellation_slot_binder&& other)
    : slot_(BOOST_ASIO_MOVE_CAST(cancellation_slot_type)(
          other.get_cancellation_slot())),
      target_(BOOST_ASIO_MOVE_CAST(T)(other.get()))
  {
  }

  /// Move construct the target object, but specify a different cancellation
  /// slot.
  cancellation_slot_binder(const cancellation_slot_type& s,
      cancellation_slot_binder&& other)
    : slot_(s),
      target_(BOOST_ASIO_MOVE_CAST(T)(other.get()))
  {
  }

  /// Move construct from a different cancellation slot wrapper type.
  template <typename U, typename OtherCancellationSlot>
  cancellation_slot_binder(
      cancellation_slot_binder<U, OtherCancellationSlot>&& other)
    : slot_(BOOST_ASIO_MOVE_CAST(OtherCancellationSlot)(
          other.get_cancellation_slot())),
      target_(BOOST_ASIO_MOVE_CAST(U)(other.get()))
  {
  }

  /// Move construct from a different cancellation slot wrapper type, but
  /// specify a different cancellation slot.
  template <typename U, typename OtherCancellationSlot>
  cancellation_slot_binder(const cancellation_slot_type& s,
      cancellation_slot_binder<U, OtherCancellationSlot>&& other)
    : slot_(s),
      target_(BOOST_ASIO_MOVE_CAST(U)(other.get()))
  {
  }

#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// Destructor.
  ~cancellation_slot_binder()
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

  /// Obtain the associated cancellation slot.
  cancellation_slot_type get_cancellation_slot() const BOOST_ASIO_NOEXCEPT
  {
    return slot_;
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

  typename detail::cancellation_slot_binder_result_of0<T>::type operator()()
  {
    return target_();
  }

  typename detail::cancellation_slot_binder_result_of0<T>::type
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

  typedef typename detail::cancellation_slot_binder_result_type<
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
  CancellationSlot slot_;
  T target_;
};

/// Associate an object of type @c T with a cancellation slot of type
/// @c CancellationSlot.
template <typename CancellationSlot, typename T>
BOOST_ASIO_NODISCARD inline
cancellation_slot_binder<typename decay<T>::type, CancellationSlot>
bind_cancellation_slot(const CancellationSlot& s, BOOST_ASIO_MOVE_ARG(T) t)
{
  return cancellation_slot_binder<
    typename decay<T>::type, CancellationSlot>(
      s, BOOST_ASIO_MOVE_CAST(T)(t));
}

#if !defined(GENERATING_DOCUMENTATION)

namespace detail {

template <typename TargetAsyncResult,
  typename CancellationSlot, typename = void>
struct cancellation_slot_binder_async_result_completion_handler_type
{
};

template <typename TargetAsyncResult, typename CancellationSlot>
struct cancellation_slot_binder_async_result_completion_handler_type<
  TargetAsyncResult, CancellationSlot,
  typename void_type<
    typename TargetAsyncResult::completion_handler_type
  >::type>
{
  typedef cancellation_slot_binder<
    typename TargetAsyncResult::completion_handler_type, CancellationSlot>
      completion_handler_type;
};

template <typename TargetAsyncResult, typename = void>
struct cancellation_slot_binder_async_result_return_type
{
};

template <typename TargetAsyncResult>
struct cancellation_slot_binder_async_result_return_type<
  TargetAsyncResult,
  typename void_type<
    typename TargetAsyncResult::return_type
  >::type>
{
  typedef typename TargetAsyncResult::return_type return_type;
};

} // namespace detail

template <typename T, typename CancellationSlot, typename Signature>
class async_result<cancellation_slot_binder<T, CancellationSlot>, Signature> :
  public detail::cancellation_slot_binder_async_result_completion_handler_type<
    async_result<T, Signature>, CancellationSlot>,
  public detail::cancellation_slot_binder_async_result_return_type<
    async_result<T, Signature> >
{
public:
  explicit async_result(cancellation_slot_binder<T, CancellationSlot>& b)
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
    init_wrapper(const CancellationSlot& slot, BOOST_ASIO_MOVE_ARG(Init) init)
      : slot_(slot),
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
          cancellation_slot_binder<
            typename decay<Handler>::type, CancellationSlot>(
              slot_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

    template <typename Handler, typename... Args>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler,
        BOOST_ASIO_MOVE_ARG(Args)... args) const
    {
      initiation_(
          cancellation_slot_binder<
            typename decay<Handler>::type, CancellationSlot>(
              slot_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          cancellation_slot_binder<
            typename decay<Handler>::type, CancellationSlot>(
              slot_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler) const
    {
      initiation_(
          cancellation_slot_binder<
            typename decay<Handler>::type, CancellationSlot>(
              slot_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

#define BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF(n) \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)( \
          cancellation_slot_binder< \
            typename decay<Handler>::type, CancellationSlot>( \
              slot_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) const \
    { \
      initiation_( \
          cancellation_slot_binder< \
            typename decay<Handler>::type, CancellationSlot>( \
              slot_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF)
#undef BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    CancellationSlot slot_;
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
          token.get_cancellation_slot(),
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
          token.get_cancellation_slot(),
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
          token.get_cancellation_slot(), \
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
    typename T, typename CancellationSlot, typename DefaultCandidate>
struct associator<Associator,
    cancellation_slot_binder<T, CancellationSlot>,
    DefaultCandidate>
{
  typedef typename Associator<T, DefaultCandidate>::type type;

  static type get(const cancellation_slot_binder<T, CancellationSlot>& b,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<T, DefaultCandidate>::get(b.get(), c);
  }
};

template <typename T, typename CancellationSlot, typename CancellationSlot1>
struct associated_cancellation_slot<
    cancellation_slot_binder<T, CancellationSlot>,
    CancellationSlot1>
{
  typedef CancellationSlot type;

  static type get(const cancellation_slot_binder<T, CancellationSlot>& b,
      const CancellationSlot1& = CancellationSlot1()) BOOST_ASIO_NOEXCEPT
  {
    return b.get_cancellation_slot();
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_BIND_CANCELLATION_SLOT_HPP

/* bind_cancellation_slot.hpp
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
*/