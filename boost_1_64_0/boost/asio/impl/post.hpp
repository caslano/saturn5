//
// impl/post.hpp
// ~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_IMPL_POST_HPP
#define BOOST_ASIO_IMPL_POST_HPP

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

class initiate_post
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

    ex.post(BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler), alloc);
  }
};

template <typename Executor>
class initiate_post_with_executor
{
public:
  typedef Executor executor_type;

  explicit initiate_post_with_executor(const Executor& ex)
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

    ex_.post(detail::work_dispatcher<DecayedHandler>(
          BOOST_ASIO_MOVE_CAST(CompletionHandler)(handler)), alloc);
  }

private:
  Executor ex_;
};

} // namespace detail

template <BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    BOOST_ASIO_MOVE_ARG(CompletionToken) token)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_post(), token);
}

template <typename Executor,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    const Executor& ex, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_executor<Executor>::value>::type*)
{
  return async_initiate<CompletionToken, void()>(
      detail::initiate_post_with_executor<Executor>(ex), token);
}

template <typename ExecutionContext,
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void()) CompletionToken>
inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void()) post(
    ExecutionContext& ctx, BOOST_ASIO_MOVE_ARG(CompletionToken) token,
    typename enable_if<is_convertible<
      ExecutionContext&, execution_context&>::value>::type*)
{
  return (post)(ctx.get_executor(),
      BOOST_ASIO_MOVE_CAST(CompletionToken)(token));
}

} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_IMPL_POST_HPP

/* post.hpp
y2pg/KPbLwjYL90K2vZFWOtLWWc8DshTYu+3qUpWK6MxvG4Nd7+Pxb4vY+UbogYmjojU8vJNfq7v6GYbO4uDp3UArU5eIjl6seQ//lOS+dp2i4H3rB+Jzteq1hfANxunDE+4vWMKIY7JOQfz/CumgjX4cBGK9z1L5RIMzQwar8CdrInnxQ8Y9z+LZ6dJDwvk3m0o2K1oSq28T3E/pdPkqhGhUZYbcczHrBM71EyZb1VnC+XFI5mdxSD6SZwT3g3C/Dp2IlD2bS/jnC75kgKoc5dBmXrKIYTG6C9QTVZ4Ed1hEJoEemNb62bRX6O/G16JOCM6Yk2a6q1/j2O9acDVNBrh5G2AWQPLYP1/GVCHr0F23s53+RFJRE2NsvmYDljJ4P73OMGYddC+CaMLqFnYSdei0g6M0WQJJEEmRpIkhdIDMOQI8HYDP5LNCETI+L7alNAOldPfx2aTZx4hgiKmOkCYkcp7w4w+F82yIWmE7SAixxN50M91hncyNuNAl1AQd+3ZMmuEukyfJpDnnwuq4PuLmC96yQyIPEEc+gvBGlM2vc2q8cO0gyhthg==
*/