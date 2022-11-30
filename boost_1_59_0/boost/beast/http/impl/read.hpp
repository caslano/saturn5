//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
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
#include <boost/beast/core/detail/buffer.hpp>
#include <boost/beast/core/detail/read.hpp>
#include <boost/asio/error.hpp>
#include <boost/asio/compose.hpp>
#include <boost/asio/coroutine.hpp>

namespace boost {
namespace beast {
namespace http {

namespace detail {

struct parser_is_done
{
    template<bool isRequest>
    bool
    operator()(basic_parser<isRequest> const& p) const
    {
        return p.is_done();
    }
};

struct parser_is_header_done
{
    template<bool isRequest>
    bool
    operator()(basic_parser<isRequest> const& p) const
    {
        return p.is_header_done();
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
        BOOST_ASIO_HANDLER_LOCATION((
            __FILE__, __LINE__,
            "http::async_read(msg)"));

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

template<class AsyncReadStream, class DynamicBuffer, bool isRequest>
class read_some_op : asio::coroutine
{
    AsyncReadStream& s_;
    DynamicBuffer& b_;
    basic_parser<isRequest>& p_;
    std::size_t bytes_transferred_;
    bool cont_;

public:
    read_some_op(
        AsyncReadStream& s,
        DynamicBuffer& b,
        basic_parser<isRequest>& p)
        : s_(s)
        , b_(b)
        , p_(p)
        , bytes_transferred_(0)
        , cont_(false)
    {
    }

    template<class Self>
    void operator()(
        Self& self,
        error_code ec = {},
        std::size_t bytes_transferred = 0)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            if(b_.size() == 0)
                goto do_read;
            for(;;)
            {
                // parse
                {
                    auto const used = p_.put(b_.data(), ec);
                    bytes_transferred_ += used;
                    b_.consume(used);
                }
                if(ec != http::error::need_more)
                    break;

            do_read:
                BOOST_ASIO_CORO_YIELD
                {
                    cont_ = true;
                    // VFALCO This was read_size_or_throw
                    auto const size = read_size(b_, 65536);
                    if(size == 0)
                    {
                        ec = error::buffer_overflow;
                        goto upcall;
                    }
                    auto const mb =
                        beast::detail::dynamic_buffer_prepare(
                            b_, size, ec, error::buffer_overflow);
                    if(ec)
                        goto upcall;

                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::async_read_some"));

                    s_.async_read_some(*mb, std::move(self));
                }
                b_.commit(bytes_transferred);
                if(ec == net::error::eof)
                {
                    BOOST_ASSERT(bytes_transferred == 0);
                    if(p_.got_some())
                    {
                        // caller sees EOF on next read
                        ec.assign(0, ec.category());
                        p_.put_eof(ec);
                        if(ec)
                            goto upcall;
                        BOOST_ASSERT(p_.is_done());
                        goto upcall;
                    }
                    ec = error::end_of_stream;
                    break;
                }
                if(ec)
                    break;
            }

        upcall:
            if(! cont_)
            {
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::async_read_some"));

                    net::post(
                        beast::bind_front_handler(std::move(self), ec));
                }
            }
            self.complete(ec, bytes_transferred_);
        }
    }
};

template<class Stream, class DynamicBuffer, bool isRequest, class Condition>
class read_op
    : asio::coroutine
{
    Stream& s_;
    DynamicBuffer& b_;
    basic_parser<isRequest>& p_;
    std::size_t bytes_transferred_;

public:
    read_op(Stream& s, DynamicBuffer& b, basic_parser<isRequest>& p)
    : s_(s)
    , b_(b)
    , p_(p)
    , bytes_transferred_(0)
    {
    }

    template<class Self>
    void operator()(Self& self, error_code ec = {}, std::size_t bytes_transferred = 0)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            if (Condition{}(p_))
            {
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::async_read"));

                    net::post(std::move(self));
                }
            }
            else
            {
                do
                {
                    BOOST_ASIO_CORO_YIELD
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "http::async_read"));

                        async_read_some(
                            s_, b_, p_, std::move(self));
                    }
                    bytes_transferred_ += bytes_transferred;
                } while (!ec &&
                         !Condition{}(p_));
            }
            self.complete(ec, bytes_transferred_);
        }
    }
};


template<
    class SyncReadStream,
    class DynamicBuffer,
    bool isRequest>
std::size_t
read_some(SyncReadStream& s, DynamicBuffer& b, basic_parser<isRequest>& p, error_code& ec)
{
    std::size_t total = 0;
    ec.clear();
    if(b.size() == 0)
        goto do_read;
    for(;;)
    {
        // parse
        {
            auto const used = p.put(b.data(), ec);
            total += used;
            b.consume(used);
        }
        if(ec != http::error::need_more)
            break;

    do_read:
        // VFALCO This was read_size_or_throw
        auto const size = read_size(b, 65536);
        if(size == 0)
        {
            ec = error::buffer_overflow;
            return total;
        }
        auto const mb =
            beast::detail::dynamic_buffer_prepare(
                b, size, ec, error::buffer_overflow);
        if(ec)
            return total;
        std::size_t
            bytes_transferred =
                s.read_some(*mb, ec);
        b.commit(bytes_transferred);
        if(ec == net::error::eof)
        {
            BOOST_ASSERT(bytes_transferred == 0);
            if(p.got_some())
            {
                // caller sees EOF on next read
                ec.assign(0, ec.category());
                p.put_eof(ec);
                if(ec)
                    return total;
                BOOST_ASSERT(p.is_done());
                return total;
            }
            ec = error::end_of_stream;
            break;
        }
        if(ec)
            break;
    }

    return total;
}

template<class Condition, class Stream, class DynamicBuffer, bool isRequest>
std::size_t sync_read_op(Stream& s, DynamicBuffer& b, basic_parser<isRequest>& p, error_code& ec)
{
    std::size_t total = 0;
    ec.clear();

    if (!Condition{}(p))
    {
        do
        {
            total +=
                detail::read_some(s, b, p, ec);
        } while (!ec &&
                 !Condition{}(p));
    }
    return total;
}

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
    return detail::read_some(stream, buffer, parser, ec);
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read_some(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler)
{
    return net::async_compose<ReadHandler,
        void(beast::error_code, std::size_t)>(
            detail::read_some_op<AsyncReadStream, DynamicBuffer, isRequest> {
                stream,
                buffer,
                parser
            },
            handler,
            stream);
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
    return detail::sync_read_op<
        detail::parser_is_header_done>(
            stream, buffer, parser, ec);
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
async_read_header(
    AsyncReadStream& stream,
    DynamicBuffer& buffer,
    basic_parser<isRequest>& parser,
    ReadHandler&& handler)
{
    parser.eager(false);
    return net::async_compose<
        ReadHandler,
        void(error_code, std::size_t)>(
        detail::read_op<
            AsyncReadStream,
            DynamicBuffer,
            isRequest,
            detail::parser_is_header_done>(
                stream, buffer, parser),
            handler, stream);
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
    return detail::sync_read_op<
        detail::parser_is_done>(
            stream, buffer, parser, ec);
}

template<
    class AsyncReadStream,
    class DynamicBuffer,
    bool isRequest,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
    return net::async_compose<
        ReadHandler,
        void(error_code, std::size_t)>(
            detail::read_op<
                AsyncReadStream,
                DynamicBuffer,
                isRequest,
                detail::parser_is_done>(
                    stream, buffer, parser),
            handler, stream);
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
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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