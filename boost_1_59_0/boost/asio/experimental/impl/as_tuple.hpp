//
// experimental/impl/as_tuple.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXPERIMENTAL_AS_TUPLE_HPP
#define BOOST_ASIO_IMPL_EXPERIMENTAL_AS_TUPLE_HPP

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

// Class to adapt a as_tuple_t as a completion handler.
template <typename Handler>
class as_tuple_handler
{
public:
  typedef void result_type;

  template <typename CompletionToken>
  as_tuple_handler(as_tuple_t<CompletionToken> e)
    : handler_(BOOST_ASIO_MOVE_CAST(CompletionToken)(e.token_))
  {
  }

  template <typename RedirectedHandler>
  as_tuple_handler(BOOST_ASIO_MOVE_ARG(RedirectedHandler) h)
    : handler_(BOOST_ASIO_MOVE_CAST(RedirectedHandler)(h))
  {
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
    as_tuple_handler<Handler>* this_handler)
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
    as_tuple_handler<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    as_tuple_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    as_tuple_handler<Handler>* this_handler)
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
    as_tuple_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Signature>
struct as_tuple_signature;

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...)>
{
  typedef R type(std::tuple<typename decay<Args>::type...>);
};

#if defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) &>
{
  typedef R type(std::tuple<typename decay<Args>::type...>) &;
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) &&>
{
  typedef R type(std::tuple<typename decay<Args>::type...>) &&;
};

# if defined(BOOST_ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) noexcept>
{
  typedef R type(std::tuple<typename decay<Args>::type...>) noexcept;
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) & noexcept>
{
  typedef R type(std::tuple<typename decay<Args>::type...>) & noexcept;
};

template <typename R, typename... Args>
struct as_tuple_signature<R(Args...) && noexcept>
{
  typedef R type(std::tuple<typename decay<Args>::type...>) && noexcept;
};

# endif // defined(BOOST_ASIO_HAS_NOEXCEPT_FUNCTION_TYPE)
#endif // defined(BOOST_ASIO_HAS_REF_QUALIFIED_FUNCTIONS)

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename... Signatures>
struct async_result<experimental::as_tuple_t<CompletionToken>, Signatures...>
  : async_result<CompletionToken,
      typename experimental::detail::as_tuple_signature<Signatures>::type...>
{
  typedef async_result<CompletionToken,
    typename experimental::detail::as_tuple_signature<Signatures>::type...>
      base_async_result;

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
          experimental::detail::as_tuple_handler<
            typename decay<Handler>::type>(
              BOOST_ASIO_MOVE_CAST(Handler)(handler)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

    Initiation initiation_;
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken,
      typename experimental::detail::as_tuple_signature<Signatures>::type...,
      (base_async_result::initiate(
        declval<init_wrapper<typename decay<Initiation>::type> >(),
        declval<CompletionToken>(),
        declval<BOOST_ASIO_MOVE_ARG(Args)>()...)))
  initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return base_async_result::initiate(
        init_wrapper<typename decay<Initiation>::type>(
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_, BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename DefaultCandidate>
struct associator<Associator,
    experimental::detail::as_tuple_handler<Handler>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const experimental::detail::as_tuple_handler<Handler>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXPERIMENTAL_AS_TUPLE_HPP

/* as_tuple.hpp
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
*/