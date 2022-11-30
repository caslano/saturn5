//
// experimental/deferred.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_DEFERRED_HPP
#define BOOST_ASIO_EXPERIMENTAL_DEFERRED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <tuple>
#include <boost/asio/associator.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/type_traits.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {

/// Trait for detecting objects that are usable as deferred operations.
template <typename T>
struct is_deferred : false_type
{
};

namespace detail {

// Helper trait for getting the completion signature from an async operation.

struct deferred_signature_probe {};

template <typename T>
struct deferred_signature_probe_result
{
  typedef T type;
};

template <typename T>
struct deferred_signature
{
  typedef typename decltype(
      declval<T>()(declval<deferred_signature_probe>()))::type type;
};

// Helper trait for getting the completion signature of the tail in a sequence
// when invoked with the specified arguments.

template <typename HeadSignature, typename Tail>
struct deferred_sequence_signature;

template <typename R, typename... Args, typename Tail>
struct deferred_sequence_signature<R(Args...), Tail>
{
  static_assert(
      !is_same<decltype(declval<Tail>()(declval<Args>()...)), void>::value,
      "deferred functions must produce a deferred return type");

  typedef typename decltype(
      declval<Tail>()(declval<Args>()...)(
        declval<deferred_signature_probe>()))::type type;
};

// Completion handler for the head component of a deferred sequence.
template <typename Handler, typename Tail>
class deferred_sequence_handler
{
public:
  template <typename H, typename T>
  explicit deferred_sequence_handler(
      BOOST_ASIO_MOVE_ARG(H) handler, BOOST_ASIO_MOVE_ARG(T) tail)
    : handler_(BOOST_ASIO_MOVE_CAST(H)(handler)),
      tail_(BOOST_ASIO_MOVE_CAST(T)(tail))
  {
  }

  template <typename... Args>
  void operator()(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Tail)(tail_)(
        BOOST_ASIO_MOVE_CAST(Args)(args)...)(
          BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_));
  }

//private:
  Handler handler_;
  Tail tail_;
};

} // namespace detail

/// Used to represent an empty deferred action.
struct deferred_noop
{
  /// No effect.
  template <typename... Args>
  void operator()(BOOST_ASIO_MOVE_ARG(Args)...) BOOST_ASIO_RVALUE_REF_QUAL
  {
  }

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
  /// No effect.
  template <typename... Args>
  decltype(auto) operator()(BOOST_ASIO_MOVE_ARG(Args)...) const &
  {
  }
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
};

#if !defined(GENERATING_DOCUMENTATION)
template <>
struct is_deferred<deferred_noop> : true_type
{
};
#endif // !defined(GENERATING_DOCUMENTATION)

/// Tag type to disambiguate deferred constructors.
struct deferred_init_tag {};

/// Wraps a function object so that it may be used as an element in a deferred
/// composition.
template <typename Function>
class deferred_function
{
public:
  /// Constructor. 
  template <typename F>
  BOOST_ASIO_CONSTEXPR explicit deferred_function(
      deferred_init_tag, BOOST_ASIO_MOVE_ARG(F) function)
    : function_(BOOST_ASIO_MOVE_CAST(F)(function))
  {
  }

  template <typename... Args>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(Args)... args) BOOST_ASIO_RVALUE_REF_QUAL
  {
    return BOOST_ASIO_MOVE_CAST(Function)(function_)(
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
  template <typename... Args>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(Args)... args) const &
  {
    return deferred_function(*this)(
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

//private:
  Function function_;
};

#if !defined(GENERATING_DOCUMENTATION)
template <typename Function>
struct is_deferred<deferred_function<Function> > : true_type
{
};
#endif // !defined(GENERATING_DOCUMENTATION)

/// Encapsulates deferred values.
template <typename... Values>
class BOOST_ASIO_NODISCARD deferred_values
{
private:
  std::tuple<Values...> values_;

  struct initiate
  {
    template <typename Handler, typename... V>
    void operator()(Handler handler, BOOST_ASIO_MOVE_ARG(V)... values)
    {
      BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler)(
          BOOST_ASIO_MOVE_CAST(V)(values)...);
    }
  };

  template <typename CompletionToken, std::size_t... I>
  decltype(auto) invoke_helper(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token,
      std::index_sequence<I...>)
  {
    return boost::asio::async_initiate<CompletionToken, void(Values...)>(
        initiate(), token,
        std::get<I>(BOOST_ASIO_MOVE_CAST(std::tuple<Values...>)(values_))...);
  }

public:
  /// Construct a deferred asynchronous operation from the arguments to an
  /// initiation function object.
  template <typename... V>
  BOOST_ASIO_CONSTEXPR explicit deferred_values(
      deferred_init_tag, BOOST_ASIO_MOVE_ARG(V)... values)
    : values_(BOOST_ASIO_MOVE_CAST(V)(values)...)
  {
  }

  /// Initiate the deferred operation using the supplied completion token.
  template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void(Values...)) CompletionToken>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token) BOOST_ASIO_RVALUE_REF_QUAL
  {
    return this->invoke_helper(
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token),
        std::index_sequence_for<Values...>());
  }

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
  template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void(Values...)) CompletionToken>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token) const &
  {
    return deferred_values(*this)(
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
  }
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
};

#if !defined(GENERATING_DOCUMENTATION)
template <typename... Values>
struct is_deferred<deferred_values<Values...> > : true_type
{
};
#endif // !defined(GENERATING_DOCUMENTATION)

/// Encapsulates a deferred asynchronous operation.
template <typename Signature, typename Initiation, typename... InitArgs>
class BOOST_ASIO_NODISCARD deferred_async_operation
{
private:
  typename decay<Initiation>::type initiation_;
  typedef std::tuple<typename decay<InitArgs>::type...> init_args_t;
  init_args_t init_args_;

  template <typename CompletionToken, std::size_t... I>
  decltype(auto) invoke_helper(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token,
      std::index_sequence<I...>)
  {
    return boost::asio::async_initiate<CompletionToken, Signature>(
        BOOST_ASIO_MOVE_CAST(typename decay<Initiation>::type)(initiation_),
        token, std::get<I>(BOOST_ASIO_MOVE_CAST(init_args_t)(init_args_))...);
  }

public:
  /// Construct a deferred asynchronous operation from the arguments to an
  /// initiation function object.
  template <typename I, typename... A>
  BOOST_ASIO_CONSTEXPR explicit deferred_async_operation(
      deferred_init_tag, BOOST_ASIO_MOVE_ARG(I) initiation,
      BOOST_ASIO_MOVE_ARG(A)... init_args)
    : initiation_(BOOST_ASIO_MOVE_CAST(I)(initiation)),
      init_args_(BOOST_ASIO_MOVE_CAST(A)(init_args)...)
  {
  }

  /// Initiate the asynchronous operation using the supplied completion token.
  template <BOOST_ASIO_COMPLETION_TOKEN_FOR(Signature) CompletionToken>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token) BOOST_ASIO_RVALUE_REF_QUAL
  {
    return this->invoke_helper(
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token),
        std::index_sequence_for<InitArgs...>());
  }

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
  template <BOOST_ASIO_COMPLETION_TOKEN_FOR(Signature) CompletionToken>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token) const &
  {
    return deferred_async_operation(*this)(
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
  }
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
};

#if !defined(GENERATING_DOCUMENTATION)
template <typename Signature, typename Initiation, typename... InitArgs>
struct is_deferred<
    deferred_async_operation<Signature, Initiation, InitArgs...> > : true_type
{
};
#endif // !defined(GENERATING_DOCUMENTATION)

/// Defines a link between two consecutive operations in a sequence.
template <typename Head, typename Tail>
class BOOST_ASIO_NODISCARD deferred_sequence
{
private:
  typedef typename detail::deferred_sequence_signature<
    typename detail::deferred_signature<Head>::type, Tail>::type
      signature;

public:
  template <typename H, typename T>
  BOOST_ASIO_CONSTEXPR explicit deferred_sequence(deferred_init_tag,
      BOOST_ASIO_MOVE_ARG(H) head, BOOST_ASIO_MOVE_ARG(T) tail)
    : head_(BOOST_ASIO_MOVE_CAST(H)(head)),
      tail_(BOOST_ASIO_MOVE_CAST(T)(tail))
  {
  }

  template <BOOST_ASIO_COMPLETION_TOKEN_FOR(signature) CompletionToken>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token) BOOST_ASIO_RVALUE_REF_QUAL
  {
    return boost::asio::async_initiate<CompletionToken, signature>(
        initiate(), token, BOOST_ASIO_MOVE_OR_LVALUE(Head)(head_),
        BOOST_ASIO_MOVE_OR_LVALUE(Tail)(tail_));
  }

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
  template <BOOST_ASIO_COMPLETION_TOKEN_FOR(signature) CompletionToken>
  decltype(auto) operator()(
      BOOST_ASIO_MOVE_ARG(CompletionToken) token) const &
  {
    return deferred_sequence(*this)(
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
  }
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

private:
  struct initiate
  {
    template <typename Handler>
    void operator()(BOOST_ASIO_MOVE_ARG(Handler) handler,
        Head head, BOOST_ASIO_MOVE_ARG(Tail) tail)
    {
      BOOST_ASIO_MOVE_OR_LVALUE(Head)(head)(
          detail::deferred_sequence_handler<
            typename decay<Handler>::type,
            typename decay<Tail>::type>(
              BOOST_ASIO_MOVE_CAST(Handler)(handler),
              BOOST_ASIO_MOVE_CAST(Tail)(tail)));
    }
  };

  Head head_;
  Tail tail_;
};

#if !defined(GENERATING_DOCUMENTATION)
template <typename Head, typename Tail>
struct is_deferred<deferred_sequence<Head, Tail> > : true_type
{
};
#endif // !defined(GENERATING_DOCUMENTATION)

/// Used to represent a deferred conditional branch.
template <typename OnTrue = deferred_noop,
    typename OnFalse = deferred_noop>
class BOOST_ASIO_NODISCARD deferred_conditional
{
public:
  /// Construct a deferred conditional with the value to determine which branch
  /// will be executed.
  BOOST_ASIO_CONSTEXPR explicit deferred_conditional(bool b)
    : on_true_(),
      on_false_(),
      bool_(b)
  {
  }

  /// Invoke the conditional branch bsaed on the stored alue.
  template <typename... Args>
  auto operator()(BOOST_ASIO_MOVE_ARG(Args)... args) BOOST_ASIO_RVALUE_REF_QUAL
  {
    if (bool_)
    {
      return BOOST_ASIO_MOVE_OR_LVALUE(OnTrue)(on_true_)(
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }
    else
    {
      return BOOST_ASIO_MOVE_OR_LVALUE(OnFalse)(on_false_)(
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }
  }

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
  template <typename... Args>
  auto operator()(BOOST_ASIO_MOVE_ARG(Args)... args) const &
  {
    return deferred_conditional(*this)(
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

  /// Set the true branch of the conditional.
  template <typename T>
  deferred_conditional<T, OnFalse> then(T on_true,
      typename constraint<
        is_deferred<T>::value
      >::type* = 0,
      typename constraint<
        is_same<
          typename conditional<true, OnTrue, T>::type,
          deferred_noop
        >::value
      >::type* = 0) BOOST_ASIO_RVALUE_REF_QUAL
  {
    return deferred_conditional<T, OnFalse>(
        bool_, BOOST_ASIO_MOVE_CAST(T)(on_true),
        BOOST_ASIO_MOVE_CAST(OnFalse)(on_false_));
  }

  /// Set the false branch of the conditional.
  template <typename T>
  deferred_conditional<OnTrue, T> otherwise(T on_false,
      typename constraint<
        is_deferred<T>::value
      >::type* = 0,
      typename constraint<
        !is_same<
          typename conditional<true, OnTrue, T>::type,
          deferred_noop
        >::value
      >::type* = 0,
      typename constraint<
        is_same<
          typename conditional<true, OnFalse, T>::type,
          deferred_noop
        >::value
      >::type* = 0) BOOST_ASIO_RVALUE_REF_QUAL
  {
    return deferred_conditional<OnTrue, T>(
        bool_, BOOST_ASIO_MOVE_CAST(OnTrue)(on_true_),
        BOOST_ASIO_MOVE_CAST(T)(on_false));
  }

private:
  template <typename T, typename F> friend class deferred_conditional;

  // Helper constructor.
  template <typename T, typename F>
  explicit deferred_conditional(bool b, BOOST_ASIO_MOVE_ARG(T) on_true,
      BOOST_ASIO_MOVE_ARG(F) on_false)
    : on_true_(BOOST_ASIO_MOVE_CAST(T)(on_true)),
      on_false_(BOOST_ASIO_MOVE_CAST(F)(on_false)),
      bool_(b)
  {
  }

  OnTrue on_true_;
  OnFalse on_false_;
  bool bool_;
};

#if !defined(GENERATING_DOCUMENTATION)
template <typename OnTrue, typename OnFalse>
struct is_deferred<deferred_conditional<OnTrue, OnFalse> > : true_type
{
};
#endif // !defined(GENERATING_DOCUMENTATION)

/// Class used to specify that an asynchronous operation should return a
/// function object to lazily launch the operation.
/**
 * The deferred_t class is used to indicate that an asynchronous operation
 * should return a function object which is itself an initiation function. A
 * deferred_t object may be passed as a completion token to an asynchronous
 * operation, typically using the special value @c boost::asio::deferred. For
 * example:
 *
 * @code auto my_deferred_op
 *   = my_socket.async_read_some(my_buffer,
 *       boost::asio::experimental::deferred); @endcode
 *
 * The initiating function (async_read_some in the above example) returns a
 * function object that will lazily initiate the operation.
 */
class deferred_t
{
public:
  /// Default constructor.
  BOOST_ASIO_CONSTEXPR deferred_t()
  {
  }

  /// Adapts an executor to add the @c deferred_t completion token as the
  /// default.
  template <typename InnerExecutor>
  struct executor_with_default : InnerExecutor
  {
    /// Specify @c deferred_t as the default completion token type.
    typedef deferred_t default_completion_token_type;

    /// Construct the adapted executor from the inner executor type.
    template <typename InnerExecutor1>
    executor_with_default(const InnerExecutor1& ex,
        typename constraint<
          conditional<
            !is_same<InnerExecutor1, executor_with_default>::value,
            is_convertible<InnerExecutor1, InnerExecutor>,
            false_type
          >::type::value
        >::type = 0) BOOST_ASIO_NOEXCEPT
      : InnerExecutor(ex)
    {
    }
  };

  /// Type alias to adapt an I/O object to use @c deferred_t as its
  /// default completion token type.
#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES) \
  || defined(GENERATING_DOCUMENTATION)
  template <typename T>
  using as_default_on_t = typename T::template rebind_executor<
      executor_with_default<typename T::executor_type> >::other;
#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)
       //   || defined(GENERATING_DOCUMENTATION)

  /// Function helper to adapt an I/O object to use @c deferred_t as its
  /// default completion token type.
  template <typename T>
  static typename decay<T>::type::template rebind_executor<
      executor_with_default<typename decay<T>::type::executor_type>
    >::other
  as_default_on(BOOST_ASIO_MOVE_ARG(T) object)
  {
    return typename decay<T>::type::template rebind_executor<
        executor_with_default<typename decay<T>::type::executor_type>
      >::other(BOOST_ASIO_MOVE_CAST(T)(object));
  }

  /// Creates a new deferred from a function.
  template <typename Function>
  typename constraint<
    !is_deferred<typename decay<Function>::type>::value,
    deferred_function<typename decay<Function>::type>
  >::type operator()(BOOST_ASIO_MOVE_ARG(Function) function) const
  {
    return deferred_function<typename decay<Function>::type>(
        deferred_init_tag{}, BOOST_ASIO_MOVE_CAST(Function)(function));
  }

  /// Passes through anything that is already deferred.
  template <typename T>
  typename constraint<
    is_deferred<typename decay<T>::type>::value,
    typename decay<T>::type
  >::type operator()(BOOST_ASIO_MOVE_ARG(T) t) const
  {
    return BOOST_ASIO_MOVE_CAST(T)(t);
  }

  /// Returns a deferred operation that returns the provided values.
  template <typename... Args>
  static BOOST_ASIO_CONSTEXPR deferred_values<typename decay<Args>::type...>
  values(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return deferred_values<typename decay<Args>::type...>(
        deferred_init_tag{}, BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

  /// Creates a conditional object for branching deferred operations.
  static BOOST_ASIO_CONSTEXPR deferred_conditional<> when(bool b)
  {
    return deferred_conditional<>(b);
  }
};

/// Pipe operator used to chain deferred operations.
template <typename Head, typename Tail>
inline auto operator|(Head head, BOOST_ASIO_MOVE_ARG(Tail) tail)
  -> typename constraint<
      is_deferred<Head>::value,
      decltype(BOOST_ASIO_MOVE_OR_LVALUE(Head)(head)(
            BOOST_ASIO_MOVE_CAST(Tail)(tail)))
    >::type
{
  return BOOST_ASIO_MOVE_OR_LVALUE(Head)(head)(
      BOOST_ASIO_MOVE_CAST(Tail)(tail));
}

/// A @ref completion_token object used to specify that an asynchronous
/// operation should return a function object to lazily launch the operation.
/**
 * See the documentation for boost::asio::experimental::deferred_t for a usage
 * example.
 */
#if defined(BOOST_ASIO_HAS_CONSTEXPR) || defined(GENERATING_DOCUMENTATION)
constexpr deferred_t deferred;
#elif defined(BOOST_ASIO_MSVC)
__declspec(selectany) deferred_t deferred;
#endif

} // namespace experimental
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#include <boost/asio/experimental/impl/deferred.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_DEFERRED_HPP

/* deferred.hpp
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
*/