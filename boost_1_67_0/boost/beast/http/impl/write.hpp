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
                net::post(
                    s_.get_executor(),
                    std::move(*this));
                goto upcall;
            }
            for(;;)
            {
                BOOST_ASIO_CORO_YIELD
                beast::http::async_write_some(
                    s_, sr_, std::move(*this));
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
    class WriteHandler>
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
    class WriteHandler>
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
    class WriteHandler>
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
    class WriteHandler>
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
    class WriteHandler>
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
    class WriteHandler>
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