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
21B4H9YjsEV+j/cS3UL99cDkBGjQdUPynCrUkS7/6NnRvjwdCp7M4dSLFkKv+u/4hwgJIPeUvAA0/qOSuyWfsDH7sbFMAPfA4UJnIc/HX6GyT1j2SQDg6KAcxAamcRcu8JtuPXMHLLcT7TJ5Pd8IE7JcOdDehGgtIsy1LiMbMvc/6FehQcZvwch3EO8vtsnrQ83/QNVpKyqbsIr3GhX9oUbe0JzZi51H0DkjiAgUlKX2y5qxBCf2h9W4eRSL6STe2dGw/B744NdMgJuAd8/VLJNJG/u/L1ExJ7wznO3ueM/hgxZ0XbPjIJPfEgveRWJgZLD/BRmiFhcrnjCGhDMOlHV+uHvNcmFZlVAJVLZbLohrK2wB/GTtpIcTEa6wrE3ZN3J9lfnnb/RR+Ke3Ma3OIes4Dn5BByad9va4HNxlf0RtwlvI13Gd8abFPr5Zist/jj5uJdavLkUnfvIeublVli9lkx6Uk/fnaJB7JXJT/3CBVQ/he84vIVJHodC08W3PFDA0yIty2ibtaLMqr2G5PklvWMybzLetk9OijrFukvJLlvA7GC0VvaOtBe0Ls3FNJZxltLoEdLGOKJctrc+ECh/L5KWOARlftM3Jai4mEEsLa+LO1fKte6dQJeJCjBJkR5aAyceTK0Q1fAtdhhOPteY23SJ3nycaiDBmj7wuS0iXC33RFtgVXnmQczZ9DOFY9A6GObsXtBWamaSh
*/