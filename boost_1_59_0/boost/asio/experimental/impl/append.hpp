//
// experimental/impl/append.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_EXPERIMENTAL_APPEND_HPP
#define BOOST_ASIO_IMPL_EXPERIMENTAL_APPEND_HPP

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

// Class to adapt a append_t as a completion handler.
template <typename Handler, typename... Values>
class append_handler
{
public:
  typedef void result_type;

  template <typename H>
  append_handler(BOOST_ASIO_MOVE_ARG(H) handler, std::tuple<Values...> values)
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
        BOOST_ASIO_MOVE_CAST(Args)(args)...,
        BOOST_ASIO_MOVE_CAST(Values)(std::get<I>(values_))...);
  }

//private:
  Handler handler_;
  std::tuple<Values...> values_;
};

template <typename Handler>
inline asio_handler_allocate_is_deprecated
asio_handler_allocate(std::size_t size,
    append_handler<Handler>* this_handler)
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
    append_handler<Handler>* this_handler)
{
  boost_asio_handler_alloc_helpers::deallocate(
      pointer, size, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_deallocate_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Handler>
inline bool asio_handler_is_continuation(
    append_handler<Handler>* this_handler)
{
  return boost_asio_handler_cont_helpers::is_continuation(
        this_handler->handler_);
}

template <typename Function, typename Handler>
inline asio_handler_invoke_is_deprecated
asio_handler_invoke(Function& function,
    append_handler<Handler>* this_handler)
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
    append_handler<Handler>* this_handler)
{
  boost_asio_handler_invoke_helpers::invoke(
      function, this_handler->handler_);
#if defined(BOOST_ASIO_NO_DEPRECATED)
  return asio_handler_invoke_is_no_longer_used();
#endif // defined(BOOST_ASIO_NO_DEPRECATED)
}

template <typename Signature, typename... Values>
struct append_signature;

template <typename R, typename... Args, typename... Values>
struct append_signature<R(Args...), Values...>
{
  typedef R type(typename decay<Args>::type..., Values...);
};

} // namespace detail
} // namespace experimental

#if !defined(GENERATING_DOCUMENTATION)

template <typename CompletionToken, typename... Values, typename Signature>
struct async_result<
    experimental::append_t<CompletionToken, Values...>, Signature>
  : async_result<CompletionToken,
      typename experimental::detail::append_signature<
        Signature, Values...>::type>
{
  typedef typename experimental::detail::append_signature<
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
          experimental::detail::append_handler<
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
    experimental::detail::append_handler<Handler, Values...>, DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const experimental::detail::append_handler<Handler, Values...>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_EXPERIMENTAL_APPEND_HPP

/* append.hpp
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
*/