//
// impl/dispatch.hpp
// ~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_DISPATCH_HPP
#define BOOST_ASIO_IMPL_DISPATCH_HPP

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

class initiate_dispatch
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

    ex.dispatch(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler), alloc);
  }
};

template <typename Executor>
class initiate_dispatch_with_executor
{
public:
  typedef Executor executor_type;

  explicit initiate_dispatch_with_executor(const Executor& ex)
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

    ex_.dispatch(detail::work_dispatcher<DecayedHandler>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_dispatch(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_executor<Executor>::value>::type*)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_dispatch_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) dispatch(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type*)
{
  return (dispatch)(ctx.get_executor(),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_DISPATCH_HPP

/* dispatch.hpp
zDLGeBsLVRmrew54ZrllvIZgfk+w4NrmeTqY5xqPy7w/Q/lyXQ+DHLVV6to1xuPyo44Zn88kMJ9nwOVtJBnI1vmiXY13XotHPXMmWQ595gxkQnfmTI5s/v44Vw7aBNEvSE4gPwgL+dH1C+90/n4MdPEMl6NfnHjR0C9o5Ldfi8r7gA/bxFvCNq3m0dFuvsrpScLG8RuFf8cZMmJtiHBlVS1/O6TaVX4lPIf8kepnKPJqa5qr+NW5CvH3Ps1Vtkle3fwkUZ2fEM5zCEdKA1AblVJXMUcpprRZoB9HMttQhIYo4TnFnKB928dpAzgNvtA3k6xxfAHHw35IRFqaakFTzzJnNyc7O/1pNfaz7mSfRq5rnhNM3qcfgx8XYT7DimWooVSiv5U8Btfzd3f5LwVliE47acZ5cwGaDmK/oorCFdJA/J+Kx2Yvi+naiW9mKig8W7oIfE7GY+cr9hfCi+UwvNco7DL7NDH+bEpPNuH7gnaS4lqUuFRjy7hPwaGTfdy81tDSYZ2MPriolPWVp5utvXXEOe6LGL6HFjpg1Ez+Xk0ZA1QIeullY/spdmjb734Zv4fozz0o/B/4fXrNPoTcTl8RTlcKV4CmG4VbiHFwHcLquRPtc8mPS+icSkq7BiuJNI6TpSKKywN9pqnNVR+zsYRzECsOl+XeRAGl75MuM/u1irVPLuGckObCr1z7rdP0QPGEvWsK4e2F7DrJdnMU7Vwxg/dyw0Z4XBEeZ4SV7YZxV89guWh1PqZVktlPgvF2z1D3Y+v+JfIy4BwHzkjy5SiyzUeaqfqW1P1g8i3hcWtUtrqf2zx5NNj/dbI3dVYA+TXWHU/juQXtXLRfK3tlFbXFhXSxRHAsoUiWPRW/o5C9egqvRZ8Lt7yPZqSgSRK2h2sp/Iik9E/24dXdz4E7Oeh50ovnD9x9wDZo4levg4kfnd3odHkgg514OjL8q1Ifr2jqY1ZVTW2N3ieF64Hx0oSsL6XwKnilhGnmJguq1T44UtB0ErK9nMK3wFu3laZ/VIr+cS+lL5Kqbb5/2k3pU6Gz4yTxTSefQ6Lq0dcJpw2NpUWQgSUo97tJin9DJ2v/O8bbALx/KHhuswyzTZDupRjTDJtgS/15fLxnoJ4NRXWk28PfWREgnsRzpYGsJ/MPaNqmvNR2jlRFeJ3kQjFHUmk7iLaRuG1Umayg9H5yhWSwW7Oc11B6V7kIfCp1dAb1kzkHOk7p5/37kc7ZOBtzlTlso71AuL5b+r7fckDv+/4Iwqrv+27kkzxHteeOMtW/+qh8bBd81G1S+MhGeJvKR93WkD74vxj48L8a5CMPeWwRfNTtboqP3ArBx+/0vRVoe1eoNmtnSD7Gv6rno1rDxyHkk1Mh7Ns+Wz5Yb47G+8bhGX+W4zj5rxww+Ju8qg8v47DRTpJJtwcgnvXseJ6jSQd1sssn0djbpDMIvyfLL9PT/rzmbJrpVaWa8zAYJ0H4qidQeAh0LGQK9XdoLvujRSfANOmAgTIt3EGLtljLNmlD9CkcRu+gcCK1yQTk9cpctU2ydDLajG/bmrQ9BOZQXEZuk2kHrfcA9tDppcBhffEbnjLg1OnqHFNi+/N5Gbej0AcPUPik1E1vaxA6Zj2lr5A6sY4ZKfJI4jaE//chhMGRT9CLebnQK+uI5mupu/D/4XzM3wcJ/4L/UPrt2nnXLK1d4EJ6r1e02wwKt9SOIWJemEFpQzms5Rl6pBL9v0r1S80w+aOqOIerVL+QuptM8yvG+ZHzcVZB5KJbmvJKYrzMatXGX3evsuEWkU0mLmt/aqYZVS101Ha7sWpidpP2MHt9wDKpXe/niTC3qWG+dfLKQKYV7L80g+1gJw5pZBI=
*/