
// impl/redirect_error.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
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
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/associated_allocator.hpp>
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
    handler_();
  }

#if defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Arg, typename... Args>
  typename enable_if<
    !is_same<typename decay<Arg>::type, boost::system::error_code>::value
  >::type
  operator()(BOOST_ASIO_MOVE_ARG(Arg) arg, BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    handler_(BOOST_ASIO_MOVE_CAST(Arg)(arg),
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

  template <typename... Args>
  void operator()(const boost::system::error_code& ec,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    ec_ = ec;
    handler_(BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

#else // defined(BOOST_ASIO_HAS_VARIADIC_TEMPLATES)

  template <typename Arg>
  typename enable_if<
    !is_same<typename decay<Arg>::type, boost::system::error_code>::value
  >::type
  operator()(BOOST_ASIO_MOVE_ARG(Arg) arg)
  {
    handler_(BOOST_ASIO_MOVE_CAST(Arg)(arg));
  }

  void operator()(const boost::system::error_code& ec)
  {
    ec_ = ec;
    handler_();
  }

#define BOOST_ASIO_PRIVATE_REDIRECT_ERROR_DEF(n) \
  template <typename Arg, BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  typename enable_if< \
    !is_same<typename decay<Arg>::type, boost::system::error_code>::value \
  >::type \
  operator()(BOOST_ASIO_MOVE_ARG(Arg) arg, BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    handler_(BOOST_ASIO_MOVE_CAST(Arg)(arg), \
        BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
  } \
  \
  template <BOOST_ASIO_VARIADIC_TPARAMS(n)> \
  void operator()(const boost::system::error_code& ec, \
      BOOST_ASIO_VARIADIC_MOVE_PARAMS(n)) \
  { \
    ec_ = ec; \
    handler_(BOOST_ASIO_VARIADIC_MOVE_ARGS(n)); \
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
inline void* asio_handler_allocate(std::size_t size,
    redirect_error_handler<Handler>* this_handler)
{
  return boost_asio_handler_alloc_helpers::allocate(
      size, this_handler->handler_);
}

template <typename Handler>
inline void asio_handler_deallocate(void* pointer, std::size_t size,
    redirect_error_handler<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    redirect_error_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Function, typename Handler>
inline void asio_handler_invoke(Function& function,
    redirect_error_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
}

template <typename Function, typename Handler>
inline void asio_handler_invoke(const Function& function,
    redirect_error_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
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

template <typename Handler, typename Executor>
struct associated_executor<detail::redirect_error_handler<Handler>, Executor>
{
  typedef typename associated_executor<Handler, Executor>::type type;

  static type get(
      const detail::redirect_error_handler<Handler>& h,
      const Executor& ex = Executor()) BOOST_ASIO_NOEXCEPT
  {
    return associated_executor<Handler, Executor>::get(h.handler_, ex);
  }
};

template <typename Handler, typename Allocator>
struct associated_allocator<detail::redirect_error_handler<Handler>, Allocator>
{
  typedef typename associated_allocator<Handler, Allocator>::type type;

  static type get(
      const detail::redirect_error_handler<Handler>& h,
      const Allocator& a = Allocator()) BOOST_ASIO_NOEXCEPT
  {
    return associated_allocator<Handler, Allocator>::get(h.handler_, a);
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