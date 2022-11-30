//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_HTTP_IMPL_WRITE_HPP
#define BOOST_BEAST_HTTP_IMPL_WRITE_HPP

#include <boost/beast/http/type_traits.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/make_printable.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/write.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <ostream>
#include <sstream>

namespace boost {
namespace beast {
namespace http {
namespace detail {

template<
    class Handler,
    class Stream,
    bool isRequest, class Body, class Fields>
class write_some_op
    : public beast::async_base<
        Handler, beast::executor_type<Stream>>
{
    Stream& s_;
    serializer<isRequest,Body, Fields>& sr_;

    class lambda
    {
        write_some_op& op_;

    public:
        bool invoked = false;

        explicit
        lambda(write_some_op& op)
            : op_(op)
        {
        }

        template<class ConstBufferSequence>
        void
        operator()(
            error_code& ec,
            ConstBufferSequence const& buffers)
        {
            BOOST_ASIO_HANDLER_LOCATION((
                __FILE__, __LINE__,
                "http::async_write_some"));

            invoked = true;
            ec = {};
            op_.s_.async_write_some(
                buffers, std::move(op_));
        }
    };

public:
    template<class Handler_>
    write_some_op(
        Handler_&& h,
        Stream& s,
        serializer<isRequest, Body, Fields>& sr)
        : async_base<
            Handler, beast::executor_type<Stream>>(
                 std::forward<Handler_>(h), s.get_executor())
        , s_(s)
        , sr_(sr)
    {
        (*this)();
    }

    void
    operator()()
    {
        error_code ec;
        if(! sr_.is_done())
        {
            lambda f{*this};
            sr_.next(ec, f);
            if(ec)
            {
                BOOST_ASSERT(! f.invoked);

                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "http::async_write_some"));

                return net::post(
                    s_.get_executor(),
                    beast::bind_front_handler(
                        std::move(*this), ec, 0));
            }
            if(f.invoked)
            {
                // *this is now moved-from,
                return;
            }
            // What else could it be?
            BOOST_ASSERT(sr_.is_done());
        }

        BOOST_ASIO_HANDLER_LOCATION((
            __FILE__, __LINE__,
            "http::async_write_some"));

        return net::post(
            s_.get_executor(),
            beast::bind_front_handler(
                std::move(*this), ec, 0));
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred)
    {
        if(! ec)
            sr_.consume(bytes_transferred);
        this->complete_now(ec, bytes_transferred);
    }
};

//------------------------------------------------------------------------------

struct serializer_is_header_done
{
    template<
        bool isRequest, class Body, class Fields>
    bool
    operator()(
        serializer<isRequest, Body, Fields>& sr) const
    {
        return sr.is_header_done();
    }
};

struct serializer_is_done
{
    template<
        bool isRequest, class Body, class Fields>
    bool
    operator()(
        serializer<isRequest, Body, Fields>& sr) const
    {
        return sr.is_done();
    }
};

//------------------------------------------------------------------------------

template<
    class Handler,
    class Stream,
    class Predicate,
    bool isRequest, class Body, class Fields>
class write_op
    : public beast::async_base<
        Handler, beast::executor_type<Stream>>
    , public asio::coroutine
{
    Stream& s_;
    serializer<isRequest, Body, Fields>& sr_;
    std::size_t bytes_transferred_ = 0;

public:
    template<class Handler_>
    write_op(
        Handler_&& h,
        Stream& s,
        serializer<isRequest, Body, Fields>& sr)
        : async_base<
            Handler, beast::executor_type<Stream>>(
                std::forward<Handler_>(h), s.get_executor())
        , s_(s)
        , sr_(sr)
    {
        (*this)();
    }

    void
    operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            if(Predicate{}(sr_))
            {
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::async_write"));

                    net::post(
                        s_.get_executor(),
                        std::move(*this));
                }
                goto upcall;
            }
            for(;;)
            {
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::async_write"));

                    beast::http::async_write_some(
                        s_, sr_, std::move(*this));
                }
                bytes_transferred_ += bytes_transferred;
                if(ec)
                    goto upcall;
                if(Predicate{}(sr_))
                    break;
            }
        upcall:
            this->complete_now(ec, bytes_transferred_);
        }
    }
};

//------------------------------------------------------------------------------

template<
    class Handler,
    class Stream,
    bool isRequest, class Body, class Fields>
class write_msg_op
    : public beast::stable_async_base<
        Handler, beast::executor_type<Stream>>
{
    Stream& s_;
    serializer<isRequest, Body, Fields>& sr_;

public:
    template<
        class Handler_,
        class... Args>
    write_msg_op(
        Handler_&& h,
        Stream& s,
        Args&&... args)
        : stable_async_base<
            Handler, beast::executor_type<Stream>>(
                std::forward<Handler_>(h), s.get_executor())
        , s_(s)
        , sr_(beast::allocate_stable<
            serializer<isRequest, Body, Fields>>(
                *this, std::forward<Args>(args)...))
    {
        (*this)();
    }

    void
    operator()()
    {
        BOOST_ASIO_HANDLER_LOCATION((
            __FILE__, __LINE__,
            "http::async_write(msg)"));

        async_write(s_, sr_, std::move(*this));
    }

    void
    operator()(
        error_code ec, std::size_t bytes_transferred)
    {
        this->complete_now(ec, bytes_transferred);
    }
};

struct run_write_some_op
{
    template<
        class WriteHandler,
        class Stream,
        bool isRequest, class Body, class Fields>
    void
    operator()(
        WriteHandler&& h,
        Stream* s,
        serializer<isRequest, Body, Fields>* sr)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
            void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        write_some_op<
            typename std::decay<WriteHandler>::type,
            Stream,
            isRequest, Body, Fields>(
                std::forward<WriteHandler>(h), *s, *sr);
    }
};

struct run_write_op
{
    template<
        class WriteHandler,
        class Stream,
        class Predicate,
        bool isRequest, class Body, class Fields>
    void
    operator()(
        WriteHandler&& h,
        Stream* s,
        Predicate const&,
        serializer<isRequest, Body, Fields>* sr)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
            void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        write_op<
            typename std::decay<WriteHandler>::type,
            Stream,
            Predicate,
            isRequest, Body, Fields>(
                std::forward<WriteHandler>(h), *s, *sr);
    }
};

struct run_write_msg_op
{
    template<
        class WriteHandler,
        class Stream,
        bool isRequest, class Body, class Fields,
        class... Args>
    void
    operator()(
        WriteHandler&& h,
        Stream* s,
        message<isRequest, Body, Fields>* m,
        std::false_type,
        Args&&... args)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
            void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        write_msg_op<
            typename std::decay<WriteHandler>::type,
            Stream,
            isRequest, Body, Fields>(
                std::forward<WriteHandler>(h), *s, *m,
                std::forward<Args>(args)...);
    }

    template<
        class WriteHandler,
        class Stream,
        bool isRequest, class Body, class Fields,
        class... Args>
    void
    operator()(
        WriteHandler&& h,
        Stream* s,
        message<isRequest, Body, Fields> const* m,
        std::true_type,
        Args&&... args)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
            void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        write_msg_op<
            typename std::decay<WriteHandler>::type,
            Stream,
            isRequest, Body, Fields>(
                std::forward<WriteHandler>(h), *s, *m,
                std::forward<Args>(args)...);
    }
};

//------------------------------------------------------------------------------

template<class Stream>
class write_some_lambda
{
    Stream& stream_;

public:
    bool invoked = false;
    std::size_t bytes_transferred = 0;

    explicit
    write_some_lambda(Stream& stream)
        : stream_(stream)
    {
    }

    template<class ConstBufferSequence>
    void
    operator()(error_code& ec,
        ConstBufferSequence const& buffers)
    {
        invoked = true;
        bytes_transferred =
            stream_.write_some(buffers, ec);
    }
};

template<class Stream>
class write_lambda
{
    Stream& stream_;

public:
    bool invoked = false;
    std::size_t bytes_transferred = 0;

    explicit
    write_lambda(Stream& stream)
        : stream_(stream)
    {
    }

    template<class ConstBufferSequence>
    void
    operator()(error_code& ec,
        ConstBufferSequence const& buffers)
    {
        invoked = true;
        bytes_transferred = net::write(
            stream_, buffers, ec);
    }
};

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_some_impl(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    error_code& ec)
{
    if(! sr.is_done())
    {
        write_some_lambda<SyncWriteStream> f{stream};
        sr.next(ec, f);
        if(ec)
            return f.bytes_transferred;
        if(f.invoked)
            sr.consume(f.bytes_transferred);
        return f.bytes_transferred;
    }
    ec = {};
    return 0;
}

template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write_some_impl(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler)
{
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            run_write_some_op{},
            handler,
            &stream,
            &sr);
}

} // detail

//------------------------------------------------------------------------------

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_some(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write_some(stream, sr, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_some(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    error_code& ec)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    return detail::write_some_impl(stream, sr, ec);
}

template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write_some(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler)
{
    static_assert(is_async_write_stream<
            AsyncWriteStream>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    return detail::async_write_some_impl(stream, sr,
        std::forward<WriteHandler>(handler));
}

//------------------------------------------------------------------------------

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_header(SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write_header(stream, sr, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write_header(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    error_code& ec)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    sr.split(true);
    std::size_t bytes_transferred = 0;
    if(! sr.is_header_done())
    {
        detail::write_lambda<SyncWriteStream> f{stream};
        do
        {
            sr.next(ec, f);
            bytes_transferred += f.bytes_transferred;
            if(ec)
                return bytes_transferred;
            BOOST_ASSERT(f.invoked);
            sr.consume(f.bytes_transferred);
        }
        while(! sr.is_header_done());
    }
    else
    {
        ec = {};
    }
    return bytes_transferred;
}

template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write_header(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler)
{
    static_assert(is_async_write_stream<
            AsyncWriteStream>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    sr.split(true);
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            detail::run_write_op{},
            handler,
            &stream,
            detail::serializer_is_header_done{},
            &sr);
}

//------------------------------------------------------------------------------

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write(stream, sr, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
std::size_t
write(
    SyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    error_code& ec)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    std::size_t bytes_transferred = 0;
    sr.split(false);
    for(;;)
    {
        bytes_transferred +=
            write_some(stream, sr, ec);
        if(ec)
            return bytes_transferred;
        if(sr.is_done())
            break;
    }
    return bytes_transferred;
}

template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write(
    AsyncWriteStream& stream,
    serializer<isRequest, Body, Fields>& sr,
    WriteHandler&& handler)
{
    static_assert(is_async_write_stream<
            AsyncWriteStream>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    sr.split(false);
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            detail::run_write_op{},
            handler,
            &stream,
            detail::serializer_is_done{},
            &sr);
}

//------------------------------------------------------------------------------

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
typename std::enable_if<
    is_mutable_body_writer<Body>::value,
    std::size_t>::type
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields>& msg)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write(stream, msg, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
typename std::enable_if<
    ! is_mutable_body_writer<Body>::value,
    std::size_t>::type
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields> const& msg)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write(stream, msg, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
typename std::enable_if<
    is_mutable_body_writer<Body>::value,
    std::size_t>::type
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields>& msg,
    error_code& ec)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    serializer<isRequest, Body, Fields> sr{msg};
    return write(stream, sr, ec);
}

template<
    class SyncWriteStream,
    bool isRequest, class Body, class Fields>
typename std::enable_if<
    ! is_mutable_body_writer<Body>::value,
    std::size_t>::type
write(
    SyncWriteStream& stream,
    message<isRequest, Body, Fields> const& msg,
    error_code& ec)
{
    static_assert(is_sync_write_stream<SyncWriteStream>::value,
        "SyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    serializer<isRequest, Body, Fields> sr{msg};
    return write(stream, sr, ec);
}

template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write(
    AsyncWriteStream& stream,
    message<isRequest, Body, Fields>& msg,
    WriteHandler&& handler,
    typename std::enable_if<
        is_mutable_body_writer<Body>::value>::type*)
{
    static_assert(
        is_async_write_stream<AsyncWriteStream>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            detail::run_write_msg_op{},
            handler,
            &stream,
            &msg,
            std::false_type{});
}

template<
    class AsyncWriteStream,
    bool isRequest, class Body, class Fields,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
async_write(
    AsyncWriteStream& stream,
    message<isRequest, Body, Fields> const& msg,
    WriteHandler&& handler,
    typename std::enable_if<
        ! is_mutable_body_writer<Body>::value>::type*)
{
    static_assert(
        is_async_write_stream<AsyncWriteStream>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            detail::run_write_msg_op{},
            handler,
            &stream,
            &msg,
            std::true_type{});
}

//------------------------------------------------------------------------------

namespace detail {

template<class Serializer>
class write_ostream_lambda
{
    std::ostream& os_;
    Serializer& sr_;

public:
    write_ostream_lambda(std::ostream& os,
            Serializer& sr)
        : os_(os)
        , sr_(sr)
    {
    }

    template<class ConstBufferSequence>
    void
    operator()(error_code& ec,
        ConstBufferSequence const& buffers) const
    {
        ec = {};
        if(os_.fail())
            return;
        std::size_t bytes_transferred = 0;
        for(auto b : beast::buffers_range_ref(buffers))
        {
            os_.write(static_cast<char const*>(
                b.data()), b.size());
            if(os_.fail())
                return;
            bytes_transferred += b.size();
        }
        sr_.consume(bytes_transferred);
    }
};

} // detail

template<class Fields>
std::ostream&
operator<<(std::ostream& os,
    header<true, Fields> const& h)
{
    typename Fields::writer fr{
        h, h.version(), h.method()};
    return os << beast::make_printable(fr.get());
}

template<class Fields>
std::ostream&
operator<<(std::ostream& os,
    header<false, Fields> const& h)
{
    typename Fields::writer fr{
        h, h.version(), h.result_int()};
    return os << beast::make_printable(fr.get());
}

template<bool isRequest, class Body, class Fields>
std::ostream&
operator<<(std::ostream& os,
    message<isRequest, Body, Fields> const& msg)
{
    static_assert(is_body<Body>::value,
        "Body type requirements not met");
    static_assert(is_body_writer<Body>::value,
        "BodyWriter type requirements not met");
    serializer<isRequest, Body, Fields> sr{msg};
    error_code ec;
    detail::write_ostream_lambda<decltype(sr)> f{os, sr};
    do
    {
        sr.next(ec, f);
        if(os.fail())
            break;
        if(ec)
        {
            os.setstate(std::ios::failbit);
            break;
        }
    }
    while(! sr.is_done());
    return os;
}

} // http
} // beast
} // boost

#endif

/* write.hpp
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
*/