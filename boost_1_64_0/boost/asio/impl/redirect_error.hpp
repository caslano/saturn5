
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
BvwrYK//s3cmcFVVaQC/j8UNVEBU3DFRURHBDTRT3M0VE5XKBFQUEoFYFJMS07TFlEqzzJTK1CmnqCytrGiyMrOyssbKJiora6yozJwZp+Z/zv3efe/x3kO0ZvnND+rz/76z3e8s99zl3HMO3CDu9vuDso1mfSZ6uD/YKOfz3dL/3wO7wc3wYrgFjoP3QX2/iwTdbab3naTXGh6V9DIIFw2zYW+YCwfAq+BgmAf1/D04By6E8+EieBUsgkXwWngNXAqvh8vgKrhc2tlKeBtcBderdgzvUu0YlsGb4QNwNXwUroGPw9vgC/B2uA+ug2/D9fBdeAf8AG5wvh/a5P08GiH96EjoB0c5xUvc5L2f+EbOv2+ln/gO2vvfVIkX66H//ZJwrQz9vKLPu6/k/vJrp/hlEr+Nh/iD5LiDYVM4BLaGCc79cA35XSTxi6TfWOx03EqJN9jDcYvF7mugcrsW9lH169xf3eP9uEOknBOknIc618893su5g8QLh/VhR4mXqOQe1/tm5T9C4r2PXSHwQ6jbN+wAP4adVb8Eo0SPFd0qf0m3tYdyuKKheb7NhMEwBTYX3bp+3uP9OhEg+QmE9WBjaNVbDfGaS7wWEq8ltOrtHu/X+zP1TXv/CUPhLzBMdHv8oM3e8ztL8jtb8jtH8otuxY+R+O09xL+4gRl/ElTxEmEr0a3zZbN3+zPk+JlQ2X8lDBPdut+p4fhT5PjJcvxL5fjojvra7L3drpHzZa2cL6XO51kN8ZZLvBUS73rn80zihXmw98/1THuPwKaqHcNmoqv45SriFjN+PV8dX79z2SrX96OE6wRPwIGwCg6HP8Ax8EeYCH+CyfAUvAx+D9Pg3+GV8AzMVu0EFsJf4bXQh3azG/rCvdAP/gnWl/cdjaDqfwPgX2Aw/ByGwOMwFDa20bfBENgBtoThsD3sCGPgBXAgjICDYGc4GkZCPT4Cp8OecAPsBTfCGPgsjIUvwt7wJTgATvSh/4RJ8CKYARNgKRwB18ORKh04Cm6Co+H98GL4PBwLX4UT4Gvi/rq4fyDuR2E0/BZOlPOsAjl0n1lvvfmngawVsUvqPbu+2S7zYFeYD6NU+1P5h4VwClyo7IaL4AJYDBeL/yq4UuUHroL3wRvgY/BmqbfVUl+3wLck/aOwCJ6BV0NlZAnsDK9T9th0OEe/u9XMx3oP/e5k6V8ugRfDKTBJ9CzRF4l+k+hWP/SA9/N4mvRj0+V9XDJsJTrx9cmWIPEflfgqfIHEn0G4cJgCO8NU2AvOgkPgHDgWpsNL4FyYCufDXDgPFsIMuFzcb4dXwnu1LvffSPg2045HpJ5bqPtve39smOczAfT9mg0Og2FwEuwFL4P14BwYAFeI/63ivwmGwpdga/gGbA+72LS/fp94ARwOO9nM86UznAqj4CzYE2ZJ+EWwhU2fR/o4W7W7vI/wQ3bIdamBzo8eV+mLu/obGmBeX4fBCDgcxsARME70AaIPhSPhWNEniH4pHAVT4VhYBMcFmOU8Gf4BXgF3w5nwPZgCP4dpsArOgv+AqdAXG2fDQDgfdoJZcDhcoI4Ls2ESXAJzYTFcBa+Ba+FSeCtcBsvgdfBp0V+FsYGUO1yu7IEr4F/gSvgZXKvsgqXwZ7gB1vfhORYGwbthGHwIXgB3wmj4POwH/wgvFPeLRB8p/lPgC/Am+CK8DR6Ad8L34b3wA2Un/BAehEfhW6IfEb0SfgT/Dv8C1QWsEraHn8Fe8BiMg1/ARHgcJsPv4BWwChbD03Az/Bt8EBqUzyvQB34Ko+BxGA3r+Znl1wn2g11gfxgD42AfOBheBIfAcTABZsGhcAkcDXfCMfAJmAgr4CXwKLwMfgVnwJM=
*/