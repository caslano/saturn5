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
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler,
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