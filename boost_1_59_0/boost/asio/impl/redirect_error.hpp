
// impl/redirect_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_REDIRECT_ERROR_HPP
#define BOOST_ASIO_IMPL_REDIRECT_ERROR_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associator.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>
#include <boost/system/system_error.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

// Class to adapt a redirect_error_t as a completion handler.
template <typename Handler>
class redirect_error_handler
{
public:
  typedef void result_type;

  template <typename CompletionToken>
  redirect_error_handler(redirect_error_t<CompletionToken> e)
    : ec_(e.ec_),
      handler_(BOOST_ASIO_MOVE_CAST(CompletionToken)(e.token_))
  {
  }

  template <typename RedirectedHandler>
  redirect_error_handler(boost::system::error_code& ec,
      BOOST_ASIO_MOVE_ARG(RedirectedHandler) h)
    : ec_(ec),
      handler_(BOOST_ASIO_MOVE_CAST(RedirectedHandler)(h))
  {
  }

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)();
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Arg, typename... Args>
  typename enable_if<
    !is_same<typename decay<Arg>::type, boost::system::error_code>::value
  >::type
  operator()(BOOST_ASIO_MOVE_ARG(Arg) arg, BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        BOOST_ASIO_MOVE_CAST(Arg)(arg),
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

  template <typename... Args>
  void operator()(const boost::system::error_code& ec,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    ec_ = ec;
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Arg>
  typename enable_if<
    !is_same<typename decay<Arg>::type, boost::system::error_code>::value
  >::type
  operator()(BOOST_ASIO_MOVE_ARG(Arg) arg)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        BOOST_ASIO_MOVE_CAST(Arg)(arg));
  }

  void operator()(const boost::system::error_code& ec)
  {
    ec_ = ec;
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)();
  }

#define BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename Arg, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename enable_if< \
    !is_same<typename decay<Arg>::type, boost::system::error_code>::value \
  >::type \
  operator()(BOOST_ASIO_MOVE_ARG(Arg) arg, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)( \
        BOOST_ASIO_MOVE_CAST(Arg)(arg), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(const boost::system::error_code& ec, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    ec_ = ec; \
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)( \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

//private:
  boost::system::error_code& ec_;
  Handler handler_;
};

template <typename Handler>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    redirect_error_handler<Handler>* this_handler)
{
#if defined(BOOST_ASIO_NO_DEPRECATED)
  boost_asio_handler_alloc_helpers::allocate(size, this_handler->handler_);
  return asio_handler_allocate_is_no_longer_used();
#else // defined(BOOST_ASIO_NO_DEPRECATED)
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline asio_handler_deallocate_is_deprecated
asio_handler_deallocate(void* pointer, std::size_t size,
    redirect_error_handler<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    redirect_error_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    redirect_error_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(const Function& function,
    redirect_error_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Signature>
struct redirect_error_signature
{
  typedef Signature type;
};

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename R, typename... Args>
struct redirect_error_signature<R(boost::system::error_code, Args...)>
{
  typedef R type(Args...);
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const boost::system::error_code&, Args...)>
{
  typedef R type(Args...);
};

# if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

template <typename R, typename... Args>
struct redirect_error_signature<R(boost::system::error_code, Args...) &>
{
  typedef R type(Args...) &;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const boost::system::error_code&, Args...) &>
{
  typedef R type(Args...) &;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(boost::system::error_code, Args...) &&>
{
  typedef R type(Args...) &&;
};

template <typename R, typename... Args>
struct redirect_error_signature<R(const boost::system::error_code&, Args...) &&>
{
  typedef R type(Args...) &&;
};

#  if defined(BOOST_ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

template <typename R, typename... Args>
struct redirect_error_signature<
  R(boost::system::error_code, Args...) noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const boost::system::error_code&, Args...) noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(boost::system::error_code, Args...) & noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const boost::system::error_code&, Args...) & noexcept>
{
  typedef R type(Args...) & noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(boost::system::error_code, Args...) && noexcept>
{
  typedef R type(Args...) && noexcept;
};

template <typename R, typename... Args>
struct redirect_error_signature<
  R(const boost::system::error_code&, Args...) && noexcept>
{
  typedef R type(Args...) && noexcept;
};

#  endif // defined(BOOST_ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
# endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

template <typename R>
struct redirect_error_signature<R(boost::system::error_code)>
{
  typedef R type();
};

template <typename R>
struct redirect_error_signature<R(const boost::system::error_code&)>
{
  typedef R type();
};

#define BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(boost::system::error_code, BOOST_ASIO_VARIADIC_TARGS(n))> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)); \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const boost::system::error_code&, BOOST_ASIO_VARIADIC_TARGS(n))> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)); \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF

# if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

template <typename R>
struct redirect_error_signature<R(boost::system::error_code) &>
{
  typedef R type() &;
};

template <typename R>
struct redirect_error_signature<R(const boost::system::error_code&) &>
{
  typedef R type() &;
};

template <typename R>
struct redirect_error_signature<R(boost::system::error_code) &&>
{
  typedef R type() &&;
};

template <typename R>
struct redirect_error_signature<R(const boost::system::error_code&) &&>
{
  typedef R type() &&;
};

#define BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(boost::system::error_code, BOOST_ASIO_VARIADIC_TARGS(n)) &> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) &; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const boost::system::error_code&, BOOST_ASIO_VARIADIC_TARGS(n)) &> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) &; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(boost::system::error_code, BOOST_ASIO_VARIADIC_TARGS(n)) &&> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) &&; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const boost::system::error_code&, BOOST_ASIO_VARIADIC_TARGS(n)) &&> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) &&; \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF

#  if defined(BOOST_ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

template <typename R>
struct redirect_error_signature<
  R(boost::system::error_code) noexcept>
{
  typedef R type() noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(const boost::system::error_code&) noexcept>
{
  typedef R type() noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(boost::system::error_code) & noexcept>
{
  typedef R type() & noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(const boost::system::error_code&) & noexcept>
{
  typedef R type() & noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(boost::system::error_code) && noexcept>
{
  typedef R type() && noexcept;
};

template <typename R>
struct redirect_error_signature<
  R(const boost::system::error_code&) && noexcept>
{
  typedef R type() && noexcept;
};

#define BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(boost::system::error_code, BOOST_ASIO_VARIADIC_TARGS(n)) noexcept> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) noexcept; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const boost::system::error_code&, \
        BOOST_ASIO_VARIADIC_TARGS(n)) noexcept> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) noexcept; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(boost::system::error_code, \
        BOOST_ASIO_VARIADIC_TARGS(n)) & noexcept> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) & noexcept; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const boost::system::error_code&, \
        BOOST_ASIO_VARIADIC_TARGS(n)) & noexcept> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) & noexcept; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(boost::system::error_code, \
        BOOST_ASIO_VARIADIC_TARGS(n)) && noexcept> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) && noexcept; \
  }; \
  \
  template <typename R, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  struct redirect_error_signature< \
      R(const boost::system::error_code&, \
        BOOST_ASIO_VARIADIC_TARGS(n)) && noexcept> \
  { \
    typedef R type(BOOST_ASIO_VARIADIC_TARGS(n)) && noexcept; \
  }; \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF)
#undef BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF

#  endif // defined(BOOST_ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
# endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)
#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

} // namespace detail

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename Signature>
struct async_result<redirect_error_t<CompletionToken>, Signature>
{
  typedef typename async_result<CompletionToken,
    typename detail::redirect_error_signature<Signature>::type>
      ::return_type return_type;

  template <typename Initiation>
  struct init_wrapper
  {
    template <typename Init>
    init_wrapper(boost::system::error_code& ec, BOOST_ASIO_MOVE_ARG(Init) init)
      : ec_(ec),
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
          detail::redirect_error_handler<
            typename decay<Handler>::type>(
              ec_, BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    template <typename Handler>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          detail::redirect_error_handler<
            typename decay<Handler>::type>(
              ec_, BOOST_ASIO_MOVE_CAST(Handler)(handler)));
    }

#define BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF(n) \
    template <typename Handler, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
    void operator()( \
        BOOST_ASIO_MOVE_ARG(Handler) handler, \
        BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
    { \
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)( \
          detail::redirect_error_handler< \
            typename decay<Handler>::type>( \
              ec_, BOOST_ASIO_MOVE_CAST(Handler)(handler)), \
          BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
    } \
    /**/
    BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF)
#undef BOOST_ASIO_PRIVATE_INIT_WRAPPER_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

    boost::system::error_code& ec_;
    Initiation initiation_;
  };

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return async_initiate<CompletionToken,
      typename detail::redirect_error_signature<Signature>::type>(
        init_wrapper<typename decay<Initiation>::type>(
          token.ec_, BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_, BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Initiation, typename RawCompletionToken>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token)
  {
    return async_initiate<CompletionToken,
      typename detail::redirect_error_signature<Signature>::type>(
        init_wrapper<typename decay<Initiation>::type>(
          token.ec_, BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_);
  }

#define BOOST_ASIO_PRIVATE_INITIATE_DEF(n) \
  template <typename Initiation, typename RawCompletionToken, \
      BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  static return_type initiate( \
      BOOST_ASIO_MOVE_ARG(Initiation) initiation, \
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    return async_initiate<CompletionToken, \
      typename detail::redirect_error_signature<Signature>::type>( \
        init_wrapper<typename decay<Initiation>::type>( \
          token.ec_, BOOST_ASIO_MOVE_CAST(Initiation)(initiation)), \
        token.token_, BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  /**/
  BOOST_ASIO_VARIADIC_GENERATE(BOOST_ASIO_PRIVATE_INITIATE_DEF)
#undef BOOST_ASIO_PRIVATE_INITIATE_DEF

#endif // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)
};

template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    detail::redirect_error_handler<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const detail::redirect_error_handler<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_REDIRECT_ERROR_HPP

/* redirect_error.hpp
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
*/