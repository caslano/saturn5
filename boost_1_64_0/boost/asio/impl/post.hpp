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
6pnCy+FJ65Qm4THYoIStaAvh3S0PxP+ZeLj/cX6Z2r6p9b2idPa9ojZQfT3IX7dQ03Y8x3iQ8G/HDYUtpGI8ln2HbVMnPwv0sRQek/YSrV+mOwLx3AoPxPXI4wlpOtNg1v8fvtuTfV5GUh4/AjNKag/dvBTPfdIgcW7cY5TnanmanMy8My9B3oUPgo/y9qm0nPcp5L2b7upqhP5tfBC6he+YycYuarQHpy8lOeMDZy6Ft/R4wpp11lKkOL+A5gj8rm+lCLypF33rN1hZf9Hfpk8D9ZRIcYHILykuX+4AittRV1bj2BrKcwBqMF7Ybd6muNa6tQJsbaQfOuApzkbtNHMulm/xDVWBcR+I44vM9njKY5bFeb7VBl1RZNH3E9U8RTxna7AB5W8NMP2O4ncG+CrgU8rduv/R92+rfV3W1Yz7lDwab1LqcSLiBnyuxL1G/QJrKruxk2mDutz3Bdl0iW63jo51JY/RlxJeBvd7kQ/R7QOdpT7heWEK0SZwH9fTHmJa3itmvRak/R/hdhf85lBegzU6gfNjndBgo698nN8UqqcvMZs6IPLIMeRxTIx9rLdqgvvQkUS/QlZpcw20JxC2mzv01umrkjKNb5r45kii/C+V14KrD/hMujjEHKD4NxHziPBJ8lHcDbLlfT2Utli2Onvye+I3WV4mXSfG8BqWA9V204bor5Xt9GW8kiPhXMf+P6JMahsKm157wquivFw+gYcMg+tFN+EsN/r6iTXLaEq/R7oBFDZ7+mLeksjp/B4tksjvCOW3GbnBZ4D9fgZ+LvwJaT7QicKVxJPwN+P3DNDZS+hSNvWOclqbNGAcP7kZlhS6nyIPvjIeVzssT16yu/eSabxbsFJWaFrU1dvto8/JJl1OT1lMwAc0KiEAK1lXVjehK7dbnl9vnjvt08+dSP8dstGpDWJvnfsxxx+z1rXUV9JVXVsTwO1tMQ9jPxrWwZrmZL4HCH2M9jGfP4K2MdhLtkn01w+V25rhXhB4vxQ6mNYs0MJ28yvGTRfr8PMoHId+69Lo0FKt7mWaFLGu7knhNvIG/LfTgfmCrgPRTUS4O4UT5Qckp+VZE2MFTTsh79kUbo93RZh0m/i2n3DexeqnnVa/cl5izmW5r1dJOO9L4xEj+jCfmSF87wgnKvhtIYV3YL8wneNwcxPFDcI7AmfPTsB4mfOo2o+u8Lha4ENCmz7kZ/yCR7kPRddanm3ZhfGyt6lzp/1/2tyJzu+mMqzBezuJuZOfO+DMQDtIiRRHcycu8wEpFzVRaDN3+o1w+uvmTrlfKXGRun3KS7MVXdC8c9JtzrDm/k6yy/MdY782zpVI9nhNpu3T+n6X/TjbC/hMgJ54SrD+2fCV6HfcsbXzCY4SfU/Fz7LsmyNFensxZ9iLsN03r/ma/OzW4q9Tus/uviYxR3ou8N4m7blsj2YdqtdluRZtkmfxLeuhr/heEcP6seAJbmS2WQ/gOm401jFNMS3rWdiqXCcDZ8hliHPs1Xxam+ue+7iDaFpxW6j4Pis7I6d1ZFudej9L03P9P1J/Br8d/TiwI5DpVXxvxTzAx5BBPpWhrlx4Y5RWE//X+3W+NozXRowBMylcLF8qOxhf51vD+HFC/5VSuEzGPbR6X4jiYH02Ek6M0OPjvkYYt6RcLCUxDlafFBct/JfzKFyI8MVGe5Swpd5G+a7CLDOK49ASRHcDNMoCkw5SWOtM6auR2kbc2/u4kg/d7toZX5rHibOQ7ydcl7hzMpbC65B+rfZOcjF+TKD0cow9SRyHcnBcHJ/D7FTrpyYooy/S+yegXX0cx++Cd81AphP1WhKs1zmE46a52lT0mbufZJ8SZ90KuqA8096O7GM=
*/