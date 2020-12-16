//
// impl/defer.hpp
// ~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_DEFER_HPP
#define BOOST_ASIO_IMPL_DEFER_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>
#include <boost/asio/associated_allocator.hpp>
#include <boost/asio/associated_executor.hpp>
#include <boost/asio/detail/work_dispatcher.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

class initiate_defer
{
public:
  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler) const
  {
    typedef typename decay<CompletionHandler>::type DecayedHandler;

    typename associated_executor<DecayedHandler>::type ex(
        (get_associated_executor)(handler));

    typename associated_allocator<DecayedHandler>::type alloc(
        (get_associated_allocator)(handler));

    ex.defer(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler), alloc);
  }
};

template <typename Executor>
class initiate_defer_with_executor
{
public:
  typedef Executor executor_type;

  explicit initiate_defer_with_executor(const Executor& ex)
    : ex_(ex)
  {
  }

  executor_type get_executor() const BOOST_ASIO_NOEXCEPT
  {
    return ex_;
  }

  template <typename CompletionHandler>
  void operator()(BOOST_ASIO_MOVE_ARG(CompletionHandler) handler) const
  {
    typedef typename decay<CompletionHandler>::type DecayedHandler;

    typename associated_allocator<DecayedHandler>::type alloc(
        (get_associated_allocator)(handler));

    ex_.defer(detail::work_dispatcher<DecayedHandler>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) defer(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_defer(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) defer(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_executor<Executor>::value>::type*)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_defer_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) defer(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type*)
{
  return (defer)(ctx.get_executor(),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_DEFER_HPP

/* defer.hpp
ZeF22/QotZGjH+zEVVKVHO1YyLhqW7kYFytiol2KvnqL/JHcXgp39KVxe5hOxveAXrxXERHC2W3AoW9voXu3DIS+I10/0OPyBL+9HZXA+p7xjg5kPR2RAzyPsyVwjPpazfPMQF4PedI8DowLpruBGa9oEOau6cBrUR+j4oxFWOH/y2TznUxfU3uUS0lsq1pN5fkyrAXuTn5HinY0Ou6Sb4fcat+xdJAYy6bZ8bEFODEJxMd8w5goyn9skFImyuc2T1hnjwvzD+s1HtfBIB6L3fWPmsZixkkejDoN4GwQdWnAGQKcAgUnsv4Nw/3Jor4rBqv1fX2Kx5FgrG9Rht5D4GunjNnXF4VHOiOw5oloF+zTVXO0Np/9pPOWOS+Wejt7mvTuOmk//DF+g/dIqdwFcynY7fHefo4MeblzsPSuczTkS+ip4gVBHxGhrzZTXg86r5TSnSkUp+rTK5xzMFt9Gv5/n0PO9zjaSycck3XlnTpElcXru3mi20p2dVc3RG37G1x2bb8ROLdnAKfV9SdUnGmxepxDwXz62uVzcgi3d6sbykR7G+o/fij3tZY3LAmP9rjaS/b9bQhw+yi4kTeO9ERF6+4xmhNraP+han0srfCgpHb1sWooy0nLpRfYlWPnUC5H3NJ9dnJ7DDh9Fd7cS59Wce5N0POUczGX1bn0O487SlNOwzyR5aHHY7EIjxPjVCzpvhsxohTq8i24WJX1ZYOhXGx1y5KLud9EL+tn6DeijvddHJjDwgCw/Igyh3UF7H91iN+Dh+rUtfyIsT61eWReEsjDE778IXc3ysS0D+/jdeHHT1D/wbqjLb3nFbwjDfT8nidDvacCeCqvdRpesxE/K5hHneUcmvM4IfLwRCwfiVvrw6PdWZyXHc93Es85khc8K21QjTyOq+9DLh6X+TwObXtFDkN7BXD7Y+AwtVcS49UO0/AW4e7vziDGbH0axhJfbuLJA9pqPMxThMflteJJyMbdw9T+vOykHT9hw4P8LNvZND+/PR7k517kLw1nfkDdFD+Zw9V+uexBIz+jEfYhPIjXPwpsHxd4XAkEKS43O7A26geoxvXn3wrd+dkIsy2moIm10gaLPdXdwheL5hS0ftpHOhwrhj6BcIcneD3F4XmG8POG8PuGsGe7Ppwtwvo7Ec+MDDD8PNt4HsZTCZz8HbQ+Ex9OG9Zmwr4zn/CWSdloryJh31Hp0zXnJCEXsYfL6Zj5+VlnzaPw3VI//J+LR6PXhI27inDukvqC/zl42E7GeXXQnptThnPlhW3xLkqfT/KUOwLjAcp8gTJ294ZERkaTbKhpRZyGFB8ubaA0VY4uPEd/s8CZM1wPvI5mORB0VYTD/KPd7tihb8dvRZhtMdyOG/jylO68r9sZz48doKefEu0Is0/FjMKa8pmVZaX6cYPbsoBw/dyGKm28Zrxpvm2Ky6XjsWJMAPEGZBZDkL9jZR7pY+ni+bWzCivKFpTZy9xqwq+S0/Ef+5/Mr5pPnN4uwHSVSN9M6VPlGHA1SXZo169i/f864eTK7eU2kmEdL86TkncqOA75mJQhzpNqJLr/oVzHSM42oj12X6qOr3Eep1cyzyUZ78ylbP+pbx1QjX4pYNNB/Gk8pPti6pMtxzTOI28051H3YiCP+EAeEuIH4GG70JtWeSRxHp8AL4fyuNGd6Z7pLnMPQU5tnTw3p32RtSmSZn+H97J4PdZiZ6Af+nnNdRGFByPdAbnpqGkXbl9e88YR3mxe26p1GSunIc4htyA+fcxj5Bi1PqpN44CYmzTT38XKjlWzU9/fDu60tmvljgtkdivbPpeyLFc/rZFliE0oP9m/Em6lPEL4yTI96tBqvbuF0qLF+WQ=
*/