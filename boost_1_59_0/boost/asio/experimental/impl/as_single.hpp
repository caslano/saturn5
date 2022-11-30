//
// experimental/impl/as_single.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXPERIMENTAL_AS_SINGLE_HPP
#define BOOST_ASIO_IMPL_EXPERIMENTAL_AS_SINGLE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <tuple>

#include <boost/asio/associator.hpp>
#include <boost/asio/async_result.hpp>
#include <boost/asio/detail/handler_alloc_helpers.hpp>
#include <boost/asio/detail/handler_cont_helpers.hpp>
#include <boost/asio/detail/handler_invoke_helpers.hpp>
#include <boost/asio/detail/type_traits.hpp>
#include <boost/asio/detail/variadic_templates.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

// Class to adapt a as_single_t as a completion handler.
template <typename Handler>
class as_single_handler
{
public:
  typedef void result_type;

  template <typename CompletionToken>
  as_single_handler(as_single_t<CompletionToken> e)
    : handler_(BOOST_ASIO_MOVE_CAST(CompletionToken)(e.token_))
  {
  }

  template <typename RedirectedHandler>
  as_single_handler(BOOST_ASIO_MOVE_ARG(RedirectedHandler) h)
    : handler_(BOOST_ASIO_MOVE_CAST(RedirectedHandler)(h))
  {
  }

  void operator()()
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)();
  }

  template <typename Arg>
  void operator()(BOOST_ASIO_MOVE_ARG(Arg) arg)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        BOOST_ASIO_MOVE_CAST(Arg)(arg));
  }

  template <typename... Args>
  void operator()(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        std::make_tuple(BOOST_ASIO_MOVE_CAST(Args)(args)...));
  }

//private:
  Handler handler_;
};

template <typename Handler>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    as_single_handler<Handler>* this_handler)
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
    as_single_handler<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    as_single_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    as_single_handler<Handler>* this_handler)
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
    as_single_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Signature>
struct as_single_signature
{
  typedef Signature type;
};

template <typename R>
struct as_single_signature<R()>
{
  typedef R type();
};

template <typename R, typename Arg>
struct as_single_signature<R(Arg)>
{
  typedef R type(Arg);
};

template <typename R, typename... Args>
struct as_single_signature<R(Args...)>
{
  typedef R type(std::tuple<typename decay<Args>::type...>);
};

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename Signature>
struct async_result<experimental::as_single_t<CompletionToken>, Signature>
{
  typedef typename async_result<CompletionToken,
    typename experimental::detail::as_single_signature<Signature>::type>
      ::return_type return_type;

  template <typename Initiation>
  struct init_wrapper
  {
    init_wrapper(Initiation init)
      : initiation_(BOOST_ASIO_MOVE_CAST(Initiation)(init))
    {
    }

    template <typename Handler, typename... Args>
    void operator()(
        BOOST_ASIO_MOVE_ARG(Handler) handler,
        BOOST_ASIO_MOVE_ARG(Args)... args)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          experimental::detail::as_single_handler<
            typename decay<Handler>::type>(
              BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

    Initiation initiation_;
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return async_initiate<CompletionToken,
      typename experimental::detail::as_single_signature<Signature>::type>(
        init_wrapper<typename decay<Initiation>::type>(
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_, BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    experimental::detail::as_single_handler<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const experimental::detail::as_single_handler<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXPERIMENTAL_AS_SINGLE_HPP

/* as_single.hpp
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
*/