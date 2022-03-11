//
// async_result.hpp
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_ASYNC_RESULT_HPP
#define BOOST_ASIO_ASYNC_RESULT_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if defined(BOOST_ASIO_HAS_CONCEPTS) \
  && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  && defined(BOOST_ASIO_HAS_DECLTYPE)

namespace detail {

template <typename T>
struct is_completion_signature : false_type
{
};

template <typename R, typename... Args>
struct is_completion_signature<R(Args...)> : true_type
{
};

template <typename T, typename... Args>
BOOST_ASIO_CONCEPT callable_with = requires(T t, Args&&... args)
{
  t(static_cast<Args&&>(args)...);
};

template <typename T, typename Signature>
struct is_completion_handler_for : false_type
{
};

template <typename T, typename R, typename... Args>
struct is_completion_handler_for<T, R(Args...)>
  : integral_constant<bool, (callable_with<T, Args...>)>
{
};

} // namespace detail

template <typename T>
BOOST_ASIO_CONCEPT completion_signature =
  detail::is_completion_signature<T>::value;

#define BOOST_ASIO_COMPLETION_SIGNATURE \
  ::boost::asio::completion_signature

template <typename T, typename Signature>
BOOST_ASIO_CONCEPT completion_handler_for =
  detail::is_completion_signature<Signature>::value
    && detail::is_completion_handler_for<T, Signature>::value;

#define BOOST_ASIO_COMPLETION_HANDLER_FOR(s) \
  ::boost::asio::completion_handler_for<s>

#else // defined(BOOST_ASIO_HAS_CONCEPTS)
      //   && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   && defined(BOOST_ASIO_HAS_DECLTYPE)

#define BOOST_ASIO_COMPLETION_SIGNATURE typename
#define BOOST_ASIO_COMPLETION_HANDLER_FOR(s) typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)
       //   && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   && defined(BOOST_ASIO_HAS_DECLTYPE)

/// An interface for customising the behaviour of an initiating function.
/**
 * The async_result traits class is used for determining:
 *
 * @li the concrete completion handler type to be called at the end of the
 * asynchronous operation;
 *
 * @li the initiating function return type; and
 *
 * @li how the return value of the initiating function is obtained.
 *
 * The trait allows the handler and return types to be determined at the point
 * where the specific completion handler signature is known.
 *
 * This template may be specialised for user-defined completion token types.
 * The primary template assumes that the CompletionToken is the completion
 * handler.
 */
template <typename CompletionToken, BOOST_ASIO_COMPLETION_SIGNATURE Signature>
class async_result
{
public:
  /// The concrete completion handler type for the specific signature.
  typedef CompletionToken completion_handler_type;

  /// The return type of the initiating function.
  typedef void return_type;

  /// Construct an async result from a given handler.
  /**
   * When using a specalised async_result, the constructor has an opportunity
   * to initialise some state associated with the completion handler, which is
   * then returned from the initiating function.
   */
  explicit async_result(completion_handler_type& h)
  {
    (void)h;
  }

  /// Obtain the value to be returned from the initiating function.
  return_type get()
  {
  }

#if defined(GENERATING_DOCUMENTATION)

  /// Initiate the asynchronous operation that will produce the result, and
  /// obtain the value to be returned from the initiating function.
  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args);

#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation,
      BOOST_ASIO_COMPLETION_HANDLER_FOR(Signature) RawCompletionToken,
      typename... Args>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)(
        BOOST_ASIO_MOVE_CAST(RawCompletionToken)(token),
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation,
      BOOST_ASIO_COMPLETION_HANDLER_FOR(Signature) RawCompletionToken>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token)
  {
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)(
        BOOST_ASIO_MOVE_CAST(RawCompletionToken)(token));
  }

#define BOOST_ASIO_PRIVATE_INITIATE_DEF(n) \
  template <typename Initiation, \
      BOOST_ASIO_COMPLETION_HANDLER_FOR(Signature) RawCompletionToken, \
      BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  static return_type initiate( \
      BOOST_ASIO_MOVE_ARG(Initiation) initiation, \
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)( \
        BOOST_ASIO_MOVE_CAST(RawCompletionToken)(token), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INITIATE_DEF)
#undef BOOST_ASIO_PRIVATE_INITIATE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

private:
  async_result(const async_result&) BOOST_ASIO_DELETED;
  async_result& operator=(const async_result&) BOOST_ASIO_DELETED;
};

#if !defined(GENERATING_DOCUMENTATION)

template <BOOST_ASIO_COMPLETION_SIGNATURE Signature>
class async_result<void, Signature>
{
  // Empty.
};

#endif // !defined(GENERATING_DOCUMENTATION)

/// Helper template to deduce the handler type from a CompletionToken, capture
/// a local copy of the handler, and then create an async_result for the
/// handler.
template <typename CompletionToken, BOOST_ASIO_COMPLETION_SIGNATURE Signature>
struct async_completion
{
  /// The real handler type to be used for the asynchronous operation.
  typedef typename boost::asio::async_result<
    typename decay<CompletionToken>::type,
      Signature>::completion_handler_type completion_handler_type;

#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  /// Constructor.
  /**
   * The constructor creates the concrete completion handler and makes the link
   * between the handler and the asynchronous result.
   */
  explicit async_completion(CompletionToken& token)
    : completion_handler(static_cast<typename conditional<
        is_same<CompletionToken, completion_handler_type>::value,
        completion_handler_type&, CompletionToken&&>::type>(token)),
      result(completion_handler)
  {
  }
#else // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  explicit async_completion(typename decay<CompletionToken>::type& token)
    : completion_handler(token),
      result(completion_handler)
  {
  }

  explicit async_completion(const typename decay<CompletionToken>::type& token)
    : completion_handler(token),
      result(completion_handler)
  {
  }
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// A copy of, or reference to, a real handler object.
#if defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  typename conditional<
    is_same<CompletionToken, completion_handler_type>::value,
    completion_handler_type&, completion_handler_type>::type completion_handler;
#else // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)
  completion_handler_type completion_handler;
#endif // defined(BOOST_ASIO_HAS_MOVE) || defined(GENERATING_DOCUMENTATION)

  /// The result of the asynchronous operation's initiating function.
  async_result<typename decay<CompletionToken>::type, Signature> result;
};

namespace detail {

template <typename CompletionToken, typename Signature>
struct async_result_helper
  : async_result<typename decay<CompletionToken>::type, Signature>
{
};

struct async_result_memfns_base
{
  void initiate();
};

template <typename T>
struct async_result_memfns_derived
  : T, async_result_memfns_base
{
};

template <typename T, T>
struct async_result_memfns_check
{
};

template <typename>
char (&async_result_initiate_memfn_helper(...))[2];

template <typename T>
char async_result_initiate_memfn_helper(
    async_result_memfns_check<
      void (async_result_memfns_base::*)(),
      &async_result_memfns_derived<T>::initiate>*);

template <typename CompletionToken, typename Signature>
struct async_result_has_initiate_memfn
  : integral_constant<bool, sizeof(async_result_initiate_memfn_helper<
      async_result<typename decay<CompletionToken>::type, Signature>
    >(0)) != 1>
{
};

} // namespace detail

#if defined(GENERATING_DOCUMENTATION)
# define BOOST_ASIO_INITFN_RESULT_TYPE(ct, sig) \
  void_or_deduced
#elif defined(_MSC_VER) && (_MSC_VER < 1500)
# define BOOST_ASIO_INITFN_RESULT_TYPE(ct, sig) \
  typename ::boost::asio::detail::async_result_helper< \
    ct, sig>::return_type
#define BOOST_ASIO_HANDLER_TYPE(ct, sig) \
  typename ::boost::asio::detail::async_result_helper< \
    ct, sig>::completion_handler_type
#else
# define BOOST_ASIO_INITFN_RESULT_TYPE(ct, sig) \
  typename ::boost::asio::async_result< \
    typename ::boost::asio::decay<ct>::type, sig>::return_type
#define BOOST_ASIO_HANDLER_TYPE(ct, sig) \
  typename ::boost::asio::async_result< \
    typename ::boost::asio::decay<ct>::type, sig>::completion_handler_type
#endif

#if defined(GENERATION_DOCUMENTATION)
# define BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ct, sig) \
  auto
#elif defined(BOOST_ASIO_HAS_RETURN_TYPE_DEDUCTION)
# define BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ct, sig) \
  auto
#else
# define BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(ct, sig) \
  BOOST_ASIO_INITFN_RESULT_TYPE(ct, sig)
#endif

#if defined(GENERATION_DOCUMENTATION)
# define BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(ct, sig, expr) \
  void_or_deduced
#elif defined(BOOST_ASIO_HAS_DECLTYPE)
# define BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(ct, sig, expr) \
  decltype expr
#else
# define BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(ct, sig, expr) \
  BOOST_ASIO_INITFN_RESULT_TYPE(ct, sig)
#endif

#if defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken,
    completion_signature Signature,
    typename Initiation, typename... Args>
void_or_deduced async_initiate(
    BOOST_ASIO_MOVE_ARG(Initiation) initiation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken),
    BOOST_ASIO_MOVE_ARG(Args)... args);

#elif defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename CompletionToken,
    BOOST_ASIO_COMPLETION_SIGNATURE Signature,
    typename Initiation, typename... Args>
inline typename enable_if<
    detail::async_result_has_initiate_memfn<CompletionToken, Signature>::value,
    BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken, Signature,
      (async_result<typename decay<CompletionToken>::type,
        Signature>::initiate(declval<BOOST_ASIO_MOVE_ARG(Initiation)>(),
          declval<BOOST_ASIO_MOVE_ARG(CompletionToken)>(),
          declval<BOOST_ASIO_MOVE_ARG(Args)>()...)))>::type
async_initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token,
    BOOST_ASIO_MOVE_ARG(Args)... args)
{
  return async_result<typename decay<CompletionToken>::type,
    Signature>::initiate(BOOST_ASIO_MOVE_CAST(Initiation)(initiation),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token),
      BOOST_ASIO_MOVE_CAST(Args)(args)...);
}

template <typename CompletionToken,
    BOOST_ASIO_COMPLETION_SIGNATURE Signature,
    typename Initiation, typename... Args>
inline typename enable_if<
    !detail::async_result_has_initiate_memfn<CompletionToken, Signature>::value,
    BOOST_ASIO_INITFN_RESULT_TYPE(CompletionToken, Signature)>::type
async_initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token,
    BOOST_ASIO_MOVE_ARG(Args)... args)
{
  async_completion<CompletionToken, Signature> completion(token);

  BOOST_ASIO_MOVE_CAST(Initiation)(initiation)(
      BOOST_ASIO_MOVE_CAST(BOOST_ASIO_HANDLER_TYPE(CompletionToken,
        Signature))(completion.completion_handler),
      BOOST_ASIO_MOVE_CAST(Args)(args)...);

  return completion.result.get();
}

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename CompletionToken,
    BOOST_ASIO_COMPLETION_SIGNATURE Signature,
    typename Initiation>
inline typename enable_if<
    detail::async_result_has_initiate_memfn<CompletionToken, Signature>::value,
    BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken, Signature,
      (async_result<typename decay<CompletionToken>::type,
        Signature>::initiate(declval<BOOST_ASIO_MOVE_ARG(Initiation)>(),
          declval<BOOST_ASIO_MOVE_ARG(CompletionToken)>())))>::type
async_initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token)
{
  return async_result<typename decay<CompletionToken>::type,
    Signature>::initiate(BOOST_ASIO_MOVE_CAST(Initiation)(initiation),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
}

template <typename CompletionToken,
    BOOST_ASIO_COMPLETION_SIGNATURE Signature,
    typename Initiation>
inline typename enable_if<
    !detail::async_result_has_initiate_memfn<CompletionToken, Signature>::value,
    BOOST_ASIO_INITFN_RESULT_TYPE(CompletionToken, Signature)>::type
async_initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation,
    BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token)
{
  async_completion<CompletionToken, Signature> completion(token);

  BOOST_ASIO_MOVE_CAST(Initiation)(initiation)(
      BOOST_ASIO_MOVE_CAST(BOOST_ASIO_HANDLER_TYPE(CompletionToken,
        Signature))(completion.completion_handler));

  return completion.result.get();
}

#define BOOST_ASIO_PRIVATE_INITIATE_DEF(n) \
  template <typename CompletionToken, \
      BOOST_ASIO_COMPLETION_SIGNATURE Signature, \
      typename Initiation, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline typename enable_if< \
      detail::async_result_has_initiate_memfn< \
        CompletionToken, Signature>::value, \
      BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken, Signature, \
        (async_result<typename decay<CompletionToken>::type, \
          Signature>::initiate(declval<BOOST_ASIO_MOVE_ARG(Initiation)>(), \
            declval<BOOST_ASIO_MOVE_ARG(CompletionToken)>(), \
            BOOST_ASIO_VARIADIC_MOVE_DECLVAL(n))))>::type \
  async_initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation, \
      BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return async_result<typename decay<CompletionToken>::type, \
      Signature>::initiate(BOOST_ASIO_MOVE_CAST(Initiation)(initiation), \
        BOOST_ASIO_MOVE_CAST(CompletionToken)(token), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <typename CompletionToken, \
      BOOST_ASIO_COMPLETION_SIGNATURE Signature, \
      typename Initiation, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  inline typename enable_if< \
      !detail::async_result_has_initiate_memfn< \
        CompletionToken, Signature>::value, \
      BOOST_ASIO_INITFN_RESULT_TYPE(CompletionToken, Signature)>::type \
  async_initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation, \
      BOOST_ASIO_NONDEDUCED_MOVE_ARG(CompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    async_completion<CompletionToken, Signature> completion(token); \
  \
    BOOST_ASIO_MOVE_CAST(Initiation)(initiation)( \
        BOOST_ASIO_MOVE_CAST(BOOST_ASIO_HANDLER_TYPE(CompletionToken, \
          Signature))(completion.completion_handler), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  \
    return completion.result.get(); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INITIATE_DEF)
#undef BOOST_ASIO_PRIVATE_INITIATE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

#if defined(BOOST_ASIO_HAS_CONCEPTS) \
  && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES) \
  && defined(BOOST_ASIO_HAS_DECLTYPE)

namespace detail {

template <typename Signature>
struct initiation_archetype
{
  template <completion_handler_for<Signature> CompletionHandler>
  void operator()(CompletionHandler&&) const
  {
  }
};

} // namespace detail

template <typename T, typename Signature>
BOOST_ASIO_CONCEPT completion_token_for =
  detail::is_completion_signature<Signature>::value
  &&
  requires(T&& t)
  {
    async_initiate<T, Signature>(detail::initiation_archetype<Signature>{}, t);
  };

#define BOOST_ASIO_COMPLETION_TOKEN_FOR(s) \
  ::boost::asio::completion_token_for<s>

#else // defined(BOOST_ASIO_HAS_CONCEPTS)
      //   && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
      //   && defined(BOOST_ASIO_HAS_DECLTYPE)

#define BOOST_ASIO_COMPLETION_TOKEN_FOR(s) typename

#endif // defined(BOOST_ASIO_HAS_CONCEPTS)
       //   && defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
       //   && defined(BOOST_ASIO_HAS_DECLTYPE)

namespace detail {

template <typename>
struct default_completion_token_check
{
  typedef void type;
};

template <typename T, typename = void>
struct default_completion_token_impl
{
  typedef void type;
};

template <typename T>
struct default_completion_token_impl<T,
  typename default_completion_token_check<
    typename T::default_completion_token_type>::type>
{
  typedef typename T::default_completion_token_type type;
};

} // namespace detail

#if defined(GENERATING_DOCUMENTATION)

/// Traits type used to determine the default completion token type associated
/// with a type (such as an executor).
/**
 * A program may specialise this traits type if the @c T template parameter in
 * the specialisation is a user-defined type.
 *
 * Specialisations of this trait may provide a nested typedef @c type, which is
 * a default-constructible completion token type.
 */
template <typename T>
struct default_completion_token
{
  /// If @c T has a nested type @c default_completion_token_type,
  /// <tt>T::default_completion_token_type</tt>. Otherwise the typedef @c type
  /// is not defined.
  typedef see_below type;
};
#else
template <typename T>
struct default_completion_token
  : detail::default_completion_token_impl<T>
{
};
#endif

#if defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

template <typename T>
using default_completion_token_t = typename default_completion_token<T>::type;

#endif // defined(BOOST_ASIO_HAS_ALIAS_TEMPLATES)

#if defined(BOOST_ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)

#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(e) \
  = typename ::boost::asio::default_completion_token<e>::type
#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(e) \
  = typename ::boost::asio::default_completion_token<e>::type()

#else // defined(BOOST_ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)

#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN_TYPE(e)
#define BOOST_ASIO_DEFAULT_COMPLETION_TOKEN(e)

#endif // defined(BOOST_ASIO_HAS_DEFAULT_FUNCTION_TEMPLATE_ARGUMENTS)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_ASYNC_RESULT_HPP

/* async_result.hpp
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
*/