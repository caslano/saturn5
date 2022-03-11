//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_READ_HPP
#define BOOST_BEAST_HTTP_IMPL_READ_HPP

#include <boost/beast/http/type_traits.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/read.hpp>
#include <boost/asio/error.hpp>

namespace boost {
namespace beast {
namespace http {

namespace detail {

// The default maximum number of bytes to transfer in a single operation.
std::size_t constexpr default_max_transfer_size = 65536;

template<
    class DynamicBuffer,
    bool isRequest,
    class Condition>
std::size_t
parse_until(
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec,
    Condition cond)
{
    if(ec == net::error::eof)
    {
        if(parser.got_some())
        {
            // Caller sees EOF on next read
            ec = {};
            parser.put_eof(ec);
            BOOST_ASSERT(ec || parser.is_done());
        }
        else
        {
            ec = error::end_of_stream;
        }
        return 0;
    }
    if(ec)
    {
        // Upgrade the error if we have a partial message.
        // This causes SSL short reads (and every other error)
        // to be converted into something else, allowing the
        // caller to distinguish an SSL short read which
        // represents a safe connection closure, versus
        // a closure with data loss.
        if( ec != net::error::operation_aborted &&
            parser.got_some() && ! parser.is_done())
        {
            ec = error::partial_message;
        }

        return 0;
    }
    if(parser.is_done())
        return 0;
    if(buffer.size() > 0)
    {
        auto const bytes_used =
            parser.put(buffer.data(), ec);
        // total = total + bytes_used; // VFALCO Can't do this in a condition
        buffer.consume(bytes_used);
        if(ec == http::error::need_more)
        {
            if(buffer.size() >= buffer.max_size())
            {
                ec = http::error::buffer_overflow;
                return 0;
            }
            ec = {};
        }
        else if(ec || cond())
        {
            return 0;
        }
    }
    return default_max_transfer_size;
}

// predicate is true on any forward parser progress
template<bool isRequest>
struct read_some_condition
{
    basic_parser<isRequest>& parser;

    template<class DynamicBuffer>
    std::size_t
    operator()(error_code& ec, std::size_t,
        DynamicBuffer& buffer)
    {
        return detail::parse_until(
            buffer, parser, ec,
            []
            {
                return true;
            });
    }
};

// predicate is true when parser header is complete
template<bool isRequest>
struct read_header_condition
{
    basic_parser<isRequest>& parser;

    template<class DynamicBuffer>
    std::size_t
    operator()(error_code& ec, std::size_t,
        DynamicBuffer& buffer)
    {
        return detail::parse_until(
            buffer, parser, ec,
            [this]
            {
                return parser.is_header_done();
            });
    }
};

// predicate is true when parser message is complete
template<bool isRequest>
struct read_all_condition
{
    basic_parser<isRequest>& parser;

    template<class DynamicBuffer>
    std::size_t
    operator()(error_code& ec, std::size_t,
        DynamicBuffer& buffer)
    {
        return detail::parse_until(
            buffer, parser, ec,
            [this]
            {
                return parser.is_done();
            });
    }
};

//------------------------------------------------------------------------------

template<
    class Stream, class DynamicBuffer,
    bool isRequest, class Body, class Allocator,
    class Handler>
class read_msg_op
    : public beast::stable_async_base<
        Handler, beast::executor_type<Stream>>
    , public asio::coroutine
{
    using parser_type =
        parser<isRequest, Body, Allocator>;

    using message_type =
        typename parser_type::value_type;

    struct data
    {
        Stream& s;
        message_type& m;
        parser_type p;

        data(
            Stream& s_,
            message_type& m_)
            : s(s_)
            , m(m_)
            , p(std::move(m))
        {
        }
    };

    data& d_;

public:
    template<class Handler_>
    read_msg_op(
        Handler_&& h,
        Stream& s,
        DynamicBuffer& b,
        message_type& m)
        : stable_async_base<
            Handler, beast::executor_type<Stream>>(
                std::forward<Handler_>(h), s.get_executor())
        , d_(beast::allocate_stable<data>(
            *this, s, m))
    {
        http::async_read(d_.s, b, d_.p, std::move(*this));
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred)
    {
        if(! ec)
            d_.m = d_.p.release();
        this->complete_now(ec, bytes_transferred);
    }
};

struct run_read_msg_op
{
    template<
        class ReadHandler,
        class AsyncReadStream,
        class DynamicBuffer,
        bool isRequest, class Body, class Allocator>
    void
    operator()(
        ReadHandler&& h,
        AsyncReadStream* s,
        DynamicBuffer* b,
        message<isRequest, Body,
            basic_fields<Allocator>>* m)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
            void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        read_msg_op<
            AsyncReadStream,
            DynamicBuffer,
            isRequest, Body, Allocator,
            typename std::decay<ReadHandler>::type>(
                std::forward<ReadHandler>(h), *s, *b, *m);
    }
};

} // detail

//------------------------------------------------------------------------------

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_some(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        http::read_some(stream, buffer, parser, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_some(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    return beast::detail::read(stream, buffer,
        detail::read_some_condition<
            isRequest>{parser}, ec);
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read_some(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler)
{
    return beast::detail::async_read(
        stream,
        buffer,
        detail::read_some_condition<
            isRequest>{parser},
        std::forward<ReadHandler>(handler));
}

//------------------------------------------------------------------------------

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_header(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        http::read_header(stream, buffer, parser, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_header(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    parser.eager(false);
    return beast::detail::read(stream, buffer,
        detail::read_header_condition<
            isRequest>{parser}, ec);
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read_header(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler)
{
    parser.eager(false);
    return beast::detail::async_read(
        stream,
        buffer,
        detail::read_header_condition<
            isRequest>{parser},
        std::forward<ReadHandler>(handler));
}

//------------------------------------------------------------------------------

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        http::read(stream, buffer, parser, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    error_code& ec)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    parser.eager(true);
    return beast::detail::read(stream, buffer,
        detail::read_all_condition<
            isRequest>{parser}, ec);
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler)
{
    static_assert(
        is_async_read_stream<AsyncReadStream>::value,
        "AsyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    parser.eager(true);
    return beast::detail::async_read(
        stream,
        buffer,
        detail::read_all_condition<
            isRequest>{parser},
        std::forward<ReadHandler>(handler));
}

//------------------------------------------------------------------------------

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest, class Body, class Allocator>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    message<isRequest, Body, basic_fields<Allocator>>& msg)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_reader<Body>::value,
        "BodyReader type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        http::read(stream, buffer, msg, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest, class Body, class Allocator>
std::size_t
read(
    SyncReadStream& stream,
    DynamicBuffer& buffer,
    message<isRequest, Body, basic_fields<Allocator>>& msg,
    error_code& ec)
{
    static_assert(
        is_sync_read_stream<SyncReadStream>::value,
        "SyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_reader<Body>::value,
        "BodyReader type requirements not met");
    parser<isRequest, Body, Allocator> p(std::move(msg));
    p.eager(true);
    auto const bytes_transferred =
        http::read(stream, buffer, p, ec);
    if(ec)
        return bytes_transferred;
    msg = p.release();
    return bytes_transferred;
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest, class Body, class Allocator,
    class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    message<isRequest, Body, basic_fields<Allocator>>& msg,
    ReadHandler&& handler)
{
    static_assert(
        is_async_read_stream<AsyncReadStream>::value,
        "AsyncReadStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_reader<Body>::value,
        "BodyReader type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            detail::run_read_msg_op{},
                handler, &stream, &buffer, &msg);
}

} // http
} // beast
} // boost

#endif

/* read.hpp
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
*/