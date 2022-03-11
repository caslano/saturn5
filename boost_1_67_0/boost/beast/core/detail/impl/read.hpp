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
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
*/