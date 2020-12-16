//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_IMPL_READ_HPP
#define BOOST_BEAST_DETAIL_IMPL_READ_HPP

#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {
namespace detail {

// The number of bytes in the stack buffer when using non-blocking.
static std::size_t constexpr default_max_stack_buffer = 16384;

//------------------------------------------------------------------------------

struct dynamic_read_ops
{

// read into a dynamic buffer until the
// condition is met or an error occurs
template<
    class Stream,
    class DynamicBuffer,
    class Condition,
    class Handler>
class read_op
    : public asio::coroutine
    , public async_base<
        Handler, beast::executor_type<Stream>>
{
    Stream& s_;
    DynamicBuffer& b_;
    Condition cond_;
    error_code ec_;
    std::size_t total_ = 0;

public:
    read_op(read_op&&) = default;

    template<class Handler_, class Condition_>
    read_op(
        Handler_&& h,
        Stream& s,
        DynamicBuffer& b,
        Condition_&& cond)
        : async_base<Handler,
            beast::executor_type<Stream>>(
                std::forward<Handler_>(h),
                    s.get_executor())
        , s_(s)
        , b_(b)
        , cond_(std::forward<Condition_>(cond))
    {
        (*this)({}, 0, false);
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred,
        bool cont = true)
    {
        std::size_t max_prepare;
        BOOST_ASIO_CORO_REENTER(*this)
        {
            for(;;)
            {
                max_prepare = beast::read_size(b_, cond_(ec, total_, b_));
                if(max_prepare == 0)
                    break;
                BOOST_ASIO_CORO_YIELD
                s_.async_read_some(
                    b_.prepare(max_prepare), std::move(*this));
                b_.commit(bytes_transferred);
                total_ += bytes_transferred;
            }
            if(! cont)
            {
                // run this handler "as-if" using net::post
                // to reduce template instantiations
                ec_ = ec;
                BOOST_ASIO_CORO_YIELD
                s_.async_read_some(
                    b_.prepare(0), std::move(*this));
                ec = ec_;
            }
            this->complete_now(ec, total_);
        }
    }
};

//------------------------------------------------------------------------------

struct run_read_op
{
    template<
        class AsyncReadStream,
        class DynamicBuffer,
        class Condition,
        class ReadHandler>
    void
    operator()(
        ReadHandler&& h,
        AsyncReadStream* s,
        DynamicBuffer* b,
        Condition&& c)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
            void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        read_op<
            AsyncReadStream,
            DynamicBuffer,
            typename std::decay<Condition>::type,
            typename std::decay<ReadHandler>::type>(
                std::forward<ReadHandler>(h),
                *s,
                *b,
                std::forward<Condition>(c));
    }

};

};

//------------------------------------------------------------------------------

template<
    class SyncReadStream,
    class DynamicBuffer,
    class CompletionCondition,
    class>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionCondition cond)
{
    static_assert(is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    static_assert(
        detail::is_invocable<CompletionCondition,
            void(error_code&, std::size_t, DynamicBuffer&)>::value,
        "CompletionCondition type requirements not met");
    error_code ec;
    auto const bytes_transferred = detail::read(
        stream, buffer, std::move(cond), ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncReadStream,
    class DynamicBuffer,
    class CompletionCondition,
    class>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionCondition cond,
    error_code& ec)
{
    static_assert(is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    static_assert(
        detail::is_invocable<CompletionCondition,
            void(error_code&, std::size_t, DynamicBuffer&)>::value,
        "CompletionCondition type requirements not met");
    ec = {};
    std::size_t total = 0;
    std::size_t max_prepare;
    for(;;)
    {
        max_prepare =  beast::read_size(buffer, cond(ec, total, buffer));
        if(max_prepare == 0)
            break;
        std::size_t const bytes_transferred =
            stream.read_some(buffer.prepare(max_prepare), ec);
        buffer.commit(bytes_transferred);
        total += bytes_transferred;
    }
    return total;
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    class CompletionCondition,
    class ReadHandler,
    class>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    CompletionCondition&& cond,
    ReadHandler&& handler)
{
    static_assert(is_async_read_stream<AsyncReadStream>::value,
        "AsyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    static_assert(
        detail::is_invocable<CompletionCondition,
            void(error_code&, std::size_t, DynamicBuffer&)>::value,
        "CompletionCondition type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            typename dynamic_read_ops::run_read_op{},
            handler,
            &stream,
            &buffer,
            std::forward<CompletionCondition>(cond));
}

} // detail
} // beast
} // boost

#endif

/* read.hpp
A4CNgW0tdGlV0MWQbn/SxVroMqqga0G6eNK1rEHM/lJPXv/fy+uerB6arL4Z99CnyDuRm97vyepe8pKXvFRfqUHk/9zMU/vUofy/aaIp/5udVsj//Szr89vobP8W+R/E1cp1Vhl1p09j8w9S9ke7qm3+qx02fxdbev8Qbco6XcBSnc1/VfW6ALSpNM4BdWDzX6Wz+a8KTieAdnqbP+ttNv9V1dj8Vzls/ixb531QiOfHs/nvfroCdxlfr0P4XHQIszqH/7hk/C1JVzUZGrPoqytn7zn7ATaUriDVoitYVhObP+m6mHS1sfmvos3fpK+NzZ/0A0z6Gtj8C8Ixv/uDX1fi6RBqp0PYkBnp6RH2ID3CtszIetMlDML9NhY5G3mRp0vwkpe85KVK8v/M+pf/+9dVDMDAGoAMvw6AHVfoAZLpB1DVGoCCVRY9QP/gY/UF5OVCyqYfoP8E4DOMJZewUhtLTsmRI6RNmY9yKmm66mLJsX6MiiX3+b2UUzWx5I6U9usYSy5A39k1ltwxqB8m9Q9J+zGqfQd/rDjhCFhkiRWXRpn7yiSps+3ply+0c3wm7VU1jDOXARwCWXrfgK4DuaQ9wiIgB+LN9VPHJVvjzqnYcwXVxJ5bYIk9V+Qihxe7xJ4rdYk992Dl2HPCG/AMx8gzS0y6q1xi0mVUE5OumDELj6UOJJU6p9IVwemc/O1aO3VOai+zZ6S+l9GG+x2OVDRxrud4OOpfkPq9jBie861S7ozxgac4f+Fy/szzVvfx7AL3Xz5j9R1EXVyPQKyv4ur1Vf42sdr57ZD6CMWj34t5vznmt6Y9xlbL+VnP8VY6vUxFjkc+jnqu5BXB6bn87Tro9Fysb6vO1zFSHoYnjs+p61JzHiltBkFubkJ9V6Cf1lq+HS/1TdV+XelS7oHrIsLKN9y3DRMvi3oyjZ6j/vVn7voSnd5Lp6fR6cP0eq+DW5vHy8PPvmTg7M+SJ5z5ylkTc7MH6fQ0Or1azfV57nojnX5Lp1/U6e10esea+/jUlV7NXS+o0/Pp9I7V68nkW4XfMNsNu57sUurJllJPdhn1VOXqu0G+UYSuJfJW0vVFu66MD9QTeDAwBTgIOJjxgkYxXtBYxgs6CTgCOJd7Fp0FPBZ4P/A44GbujfUx98LayT2vovD7GcBWwEzGEZoKHAfMAU4HzgCeC5zFPafygDcB84ErgfOAD3Evq2eACznPNIPvK74jt/Mb73DOMwnt4hgnqTXjJCEbyZxvL2Aqy0ezzH75nsA7xqXf1mi3H/V9sdTvdQAmkK/tgD1Y7sMy++VzFDxw9kt9ZVtgR/bXieM8EDgc2AV4HMtTWF4SpG/SNffXj2+S6BR7IANTh9Q8ns2epFusrV5xUVZkyLrFTOSxNdQtQq8I/eL/V7dYX3rFUtxLLyKXI+9Ajirbc3WLDWT/7y+if4iyf8D+byjZH7IB5f4eQdj/txRb5f7q/bqDsf8XFQcni6Fdlfb/tVJP+z/bK7u6kqlC+26uqf0/IQh5KsE+TspG9Wf/TysOTi5CO739n/VW+3+OlPX2/6lST/s/6Z32/5IQz09N5Jr6ll88+3/VckSLaebxS6Z9NPuMlIWrTzpo+ueHZd96455j53eXXxrO/r+luHZr/ouKQ1vzn1Ac2pr/tOL6XfOfUFY/3+n/F/v/rvxG9+z/u883egruozTkTOQFe/D3uZe85CUv1VdqIPm/X13K/0UT/PJ/P4v8f2AQ8n+0Vf7vVzfyf/ny4OR/tKtS/v9R6in/s71Tru4aon95TeX/jOXVy/8ZLuPsVo/+/4XLg5P/0U4v/7PeKv+vkLJe/r9H6in/k94p/yeFeH48+X/Pkf+PEvk=
*/