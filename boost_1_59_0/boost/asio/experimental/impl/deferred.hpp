//
// experimental/impl/deferred.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2022 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_EXPERIMENTAL_IMPL_DEFERRED_HPP
#define BOOST_ASIO_EXPERIMENTAL_IMPL_DEFERRED_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {

#if !defined(GENERATING_DOCUMENTATION)

template <typename R, typename... Args>
class async_result<
    experimental::detail::deferred_signature_probe, R(Args...)>
{
public:
  typedef experimental::detail::deferred_signature_probe_result<void(Args...)>
    return_type;

  template <typename Initiation, typename... InitArgs>
  static return_type initiate(
      BOOST_ASIO_MOVE_ARG(Initiation),
      experimental::detail::deferred_signature_probe,
      BOOST_ASIO_MOVE_ARG(InitArgs)...)
  {
    return return_type{};
  }
};

template <typename Signature>
class async_result<experimental::deferred_t, Signature>
{
public:
  template <typename Initiation, typename... InitArgs>
  static experimental::deferred_async_operation<
      Signature, Initiation, InitArgs...>
  initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      experimental::deferred_t, BOOST_ASIO_MOVE_ARG(InitArgs)... args)
  {
    return experimental::deferred_async_operation<
        Signature, Initiation, InitArgs...>(
          experimental::deferred_init_tag{},
          BOOST_ASIO_MOVE_CAST(Initiation)(initiation),
          BOOST_ASIO_MOVE_CAST(InitArgs)(args)...);
    }
};

template <typename Function, typename R, typename... Args>
class async_result<
    experimental::deferred_function<Function>, R(Args...)>
{
public:
  template <typename Initiation, typename... InitArgs>
  static auto initiate(BOOST_ASIO_MOVE_ARG(Initiation) initiation,
      experimental::deferred_function<Function> token,
      BOOST_ASIO_MOVE_ARG(InitArgs)... init_args)
  {
    return experimental::deferred_sequence<
        experimental::deferred_async_operation<
          R(Args...), Initiation, InitArgs...>,
        Function>(experimental::deferred_init_tag{},
          experimental::deferred_async_operation<
            R(Args...), Initiation, InitArgs...>(
              experimental::deferred_init_tag{},
              BOOST_ASIO_MOVE_CAST(Initiation)(initiation),
              BOOST_ASIO_MOVE_CAST(InitArgs)(init_args)...),
          BOOST_ASIO_MOVE_CAST(Function)(token.function_));
  }
};

template <template <typename, typename> class Associator,
    typename Handler, typename Tail, typename DefaultCandidate>
struct associator<Associator,
    experimental::detail::deferred_sequence_handler<Handler, Tail>,
    DefaultCandidate>
  : Associator<Handler, DefaultCandidate>
{
  static typename Associator<Handler, DefaultCandidate>::type get(
      const experimental::detail::deferred_sequence_handler<Handler, Tail>& h,
      const DefaultCandidate& c = DefaultCandidate()) BOOST_ASIO_NOEXCEPT
  {
    return Associator<Handler, DefaultCandidate>::get(h.handler_, c);
  }
};

#endif // !defined(GENERATING_DOCUMENTATION)

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_EXPERIMENTAL_IMPL_DEFERRED_HPP

/* deferred.hpp
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
*/