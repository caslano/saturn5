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
xM9/i7Gje3NlLpu5W6y9qD3nSZxStaWTxgi/8UKvjTbjxVkSXomu8asxvz3nyrVZtKz+5rfnGjmXLb8lYZReQ66z7dZ7dDicHxvXlw9AnDmV6uaTl+tlvlRkbNx/eFRHw/S/5H0vx9v31BbB402JD7e/H3Hboraur3X482VvKV2i403Q7yBxDIc+LNdVX+2r113P0J3n0GdIeeR+pl+G5ZzcI+qPpWVa7eMTUIRue3CZ9Ezwb3y7q2zT5HpsT4ilcdexc+KzclzZP9bNspMHzkXzkOPxaZT7evykWgYn2mMI8TuS2iN6ZvHyBaWlVrBtOlxlH+xjG72uY3aibTpOsG0G+9iG+6ptvGPNoNxE22Sim32ej23UZy/ADsTxluOu4yyH+1uHh33yV4BukW/+6hqaa5oYqoLzWOTk0YyX1VpP7mv6vHac+dfxRsegao+9HxmSWJ489Mp8y9NQs1nLMlLyWkulmrIQJ9auRsn1KnN9qeu6+c3qQnlGSt65n6tdjZJz3COujm4cmlimMehGfMvEc1NTXc2m4Hak8XJ1fdVTR+aaeS7pQpl86kjnO9WeeUzZsMTyTCfuzvPifKqqeThtqfHxVdS5msmr8akyz5zmmvmt63w53D5w/bz+VJ62VjA8sRxj7d82/3KUR1qagspCnPjxHW3T1mLXzXpIF+rF49Pn+a2We3jq5hWfMp1K/Pa4MsnmG1wLKk97kvK0x5VneRf83bpSnp0jfNoa8TsSysPQG1we1Xc/uxxfft3t5zWfvBWhm700Lm8MU/g+ylq8WVfrhL3cdjgw0r9ei+LvFdnYXBtoB9UPrldz3aztdSKfx1Ovd47y98ssW9o1v0z0j+WXyfWT75cZ/G2TID/CE+ev6e9H2HU/Tn+/xiD/zq77cfr7awb5d3bdj/NpyX/+gWXlH/vukV5Nb5u87TMT/3J3kB9q1/01/1f9Mo/lf/kIwiHvBPbq2ty9rr/vdv3NGqX5+3rX31tdf1/n+nuz/v1Z5HLX31e4/t7i+rvJ9fcm9ftcbIH69x1239S/xyPqx6hcAnn/zzWvH+NU9Tc7BcwAp7m/h3KMeKdpvOka73RXvGKNl+4T70yNNx9MA89y+1tqvJ4+8WZpvNlKG5ij8Sps0XgrNF5vcJXGa1P/ss+Co8GH1G/0c+B09RebC34eXAB+ESwBHwHPt8N6nzKkXe8zXe/TC1ys95kUUjuCOeAUcAg4DRwNTgXHafgU8NSQ+gM67xD1PWorMsG2E2gfF6p/42pwnvrdnqV+uTXgpfot5nKwEawAd4KV4AfBteDtev5OPb9bz+8Bq8AHwWrwG2ANeED9H38M1oJPq//jIfAd4G/ABvWbbQSPgk1gWoh2CQ4Ct4JDwCvAkeCVYCHYyv+ngVeDs8FrwDPBa8FF4PXgcvDd4FvBm8Aa8D3g1eB68BawHtwFbgO/BDr+ikP1fQ9gyf2QfP4Oqz0fV//Er4N56k9bAH5P2wV5bZ0JPqH2/r765f4YXAn+BFwNPgWu0XA1+DS4Qf02rwKfA68FnwevB38Bbgd/BX4E/LX6L/4BfBjsAB8D/wzuVb121XsKfEnr4S9q/79qeY+CfwOR1telnNF6GAxmg8NB/qZcph2z5q/9xacdf5RTw8C7wPHgbvAU8G7wTPAecBH4Me0fhNUPVdfPwfM0Xbcf6ie0/94HDtRwLni/1sMnwULwU+Cp6ue5GHzQ/Y1xTX+8pu/2Qx1D+eTZRfvbOHCshp1xYq/JX+I4sUD9ZBdr+zgHHAmeq+NGqbaTErXDeeDZ4FLNJ9f1PrpGCjb53Od9mt4HwCLwg9rOPuTyX18Gfhhcpf7qb1e/9LXgbS6/1Ta9Ty4=
*/