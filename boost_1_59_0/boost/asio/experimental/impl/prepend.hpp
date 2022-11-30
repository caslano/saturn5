//
// experimental/impl/prepend.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXPERIMENTAL_PREPEND_HPP
#define BOOST_ASIO_IMPL_EXPERIMENTAL_PREPEND_HPP

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

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace experimental {
namespace detail {

// Class to adapt a prepend_t as a completion handler.
template <typename Handler, typename... Values>
class prepend_handler
{
public:
  typedef void result_type;

  template <typename H>
  prepend_handler(BOOST_ASIO_MOVE_ARG(H) handler, std::tuple<Values...> values)
    : handler_(BOOST_ASIO_MOVE_CAST(H)(handler)),
      values_(BOOST_ASIO_MOVE_CAST(std::tuple<Values...>)(values))
  {
  }

  template <typename... Args>
  void operator()(BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    this->invoke(
        std::make_index_sequence<sizeof...(Values)>{},
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

  template <std::size_t... I, typename... Args>
  void invoke(std::index_sequence<I...>, BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    BOOST_ASIO_MOVE_OR_LVALUE(Handler)(handler_)(
        BOOST_ASIO_MOVE_CAST(Values)(std::get<I>(values_))...,
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }

//private:
  Handler handler_;
  std::tuple<Values...> values_;
};

template <typename Handler>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    prepend_handler<Handler>* this_handler)
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
    prepend_handler<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    prepend_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    prepend_handler<Handler>* this_handler)
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
    prepend_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Signature, typename... Values>
struct prepend_signature;

template <typename R, typename... Args, typename... Values>
struct prepend_signature<R(Args...), Values...>
{
  typedef R type(Values..., typename decay<Args>::type...);
};

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename... Values, typename Signature>
struct async_result<
    experimental::prepend_t<CompletionToken, Values...>, Signature>
  : async_result<CompletionToken,
      typename experimental::detail::prepend_signature<
        Signature, Values...>::type>
{
  typedef typename experimental::detail::prepend_signature<
      Signature, Values...>::type signature;

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
        std::tuple<Values...> values,
        BOOST_ASIO_MOVE_ARG(Args)... args)
    {
      BOOST_ASIO_MOVE_CAST(Initiation)(initiation_)(
          experimental::detail::prepend_handler<
            typename decay<Handler>::type, Values...>(
              BOOST_ASIO_MOVE_CAST(Handler)(handler),
              BOOST_ASIO_MOVE_CAST(std::tuple<Values...>)(values)),
          BOOST_ASIO_MOVE_CAST(Args)(args)...);
    }

    Initiation initiation_;
  };

  template <typename Initiation, typename RawCompletionToken, typename... Args>
  static BOOST_ASIO_INITFN_DEDUCED_RESULT_TYPE(CompletionToken, signature,
      (async_initiate<CompletionToken, signature>(
        declval<init_wrapper<typename decay<Initiation>::type> >(),
        declval<CompletionToken&>(),
        declval<std::tuple<Values...> >(),
        declval<BOOST_ASIO_MOVE_ARG(Args)>()...)))
  initiate(
      BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      BOOST_ASIO_MOVE_ARG(RawCompletionToken) token,
      BOOST_ASIO_MOVE_ARG(Args)... args)
  {
    return async_initiate<CompletionToken, signature>(
        init_wrapper<typename decay<Initiation>::type>(
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation)),
        token.token_,
        BOOST_ASIO_MOVE_CAST(std::tuple<Values...>)(token.values_),
        BOOST_ASIO_MOVE_CAST(Args)(args)...);
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename... Values, typename DefaultCandidate>
struct associator<Associator,
    experimental::detail::prepend_handler<Handler, Values...>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const experimental::detail::prepend_handler<Handler, Values...>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXPERIMENTAL_PREPEND_HPP

/* prepend.hpp
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
*/