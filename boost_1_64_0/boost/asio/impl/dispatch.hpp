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
3khb/OKogcL12rXi4fBboKBR7Z4LRNcx/pbvJhYy68tbBa7ppOMW33TPz/IE/0QUBMKME2+E8zClNhQZ5EWWl8g+yYBkXArEtU5DcTilR1KqQ5claLyhKCWxyMpRc4itJZwWxAiJdl2RaHI4OvmkZtI3LJ3dey3VkRj5YAcDtAEgFpA1BD+wdut3OirCPfLyzeJ5gTw2Lxe6lcwJ9T4r8tj+26OOT0Zb9obJZ4Rbq+ZnrO1EeEO04FKq56w1NudXjPgPlpLJGRnqdOVb6IKgS+nTDLinDpS80ZcFelMAS7uTjK7CdOR7IxuP7GnVFexNO4TFrjQGmWVwpmRRZ1ThcGhEeg80878h6Ko3pccvNDurJPIgWi5VKYTzyu2pHiNS3Ytu557bOtnGaL9vp0WToklGSlHlXNAbDpO56eHz+ZviiU7zuGmENyhtvw26kQGLmIxZu50LK3ZSH0vyL2z/IWDPXlP2M3THld39l3EK6jP/D4BWUNnzrctfkpEJamZS6P50eWkEp4TUJMf6GhGNHlOhlaRjfT59zipVIQIeyeyJyN/vsKrenA2NOQ==
*/