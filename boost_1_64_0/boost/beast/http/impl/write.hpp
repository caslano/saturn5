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
tK7i+lJYyveY/Rwi36WgLJzbjx33yDm3BWP6j8g1ih437lfrnvg7tE6u1jrJn2PqRAe5Y9fJYtFfy+hi6oQ0fOtE00usk1ytk2qJV0JKmdZ0V98sl/PpkoeDtF9afLQ/az0sleuTqYdBOr5Fx7YRA47P1rZd+xTgAy6201zH2fVJUw+xc+3G1t5xbrYyhT6tv7H3I+/MR99la89Tp45fPJO6250ZC9LnEo9RdSxltd8JL8ijMMgiZDGyBDkH4XeTsqyUdIbZI06G5y6Gg3pY8jE66fcK3PudP6BlmqRlKtBnjba5/mWKzSAs9+/6se6ZsF/pFv3WwYN6zz1qxw7PPfWGSWxYMK/zNsz12NDcwdgvTdIa1Sn7Ofs3Hxngb7/2eYllMcbrhu1W6Z775yNDlXcwYBDzvzNd96syRYvup891fttatpjfWUd/glzPl9++xo0tLrueJtdHat919MeIfpr8HvPb51qHmCbXp5nfWPTNtzbGWVH9etBZ25gi16fqb6yjP8L0+xLs8pYujLGUkX4vZTT7sVIuzlEu17yGvHNOf7edtQqEc+TP29+P6GZRt6qtr0H6cS4SZ2t79FCqe5C9Nc4IU/73SHiTy56SgLE3+p7vSbxPwue67b/JsX+Z0Z9o5jRmDsn8qkr16uL0KLvpN0XYevBAsTsS+3tpN+sgzZmTJNYB+Y+fW5JXfc78wJn+c5AD+j2CiUh/XaN7hrwWzY/ViazusYd1ZX3UDh8emFAfqj/E1f75LXK1/4VyPVvrw9HPMe3z9Fz6YBdsQx4C2if3jevj9bnKGdIxZTDyI+JXxJdRfraCy1jhk+fleVbS8S0xz9783az78M9EBmpdPMUfO+PztzHCnLImMH/omzEiQ9o06pWmD3Dd+w2m+yU81DWmVDVubGgxdfYJuZ5r+sRODbvLf0E364x8cs7Op7ZnM35IXjzrlBW6t/8TWo/7kbtZQzzktZMsRFMmWZ+24tph9lnyzUdrMmXoba8Jkv+VyCrkQuQi5GJkNfJWZK7+zt1pfufMWrf5nXslatek7cA9Fh4Y6v87d+is+LK41xj0eb6Tv3GvgEeoqH3plDv0jR+t/t399SOO/OuDuxf/dNzn/sRam5xve/GtY26r+GSf67MOhHJfve/RrvOku8rH9ecxB/Gku85v9udVnzg+dxA/+6ODhd/8yy+MKX580XOjVpy76tr0h8YE8dSDeMld5xn787aDeNhBvOogfnYQnz6Itx3EC+8637qr+0bZ+2irXw5ruOiQ7tWIvXZfGxLOqzVb/37ZHm/17wxkjv5ti+FL6/uSSxDS8vCl8R2Fl0v64BLwGlD2WUbaNF44pOnb60oa7xLd/7UF/JsdH/yn8nTTdP9i8kPY2edV31Po+4vauH1eP6DpfRCcAt7p2u/1DPDDym++HVyo18/V/VhLNezcJ6L3WeBzn+v1PjeAQ8B3gyPBm8BCcLve9z3gdN1/djb4XnCehh1eb7veZ5na1c3rXdAzup/uYnAyuAQ8BywB7fi7LV07Bms0nwPAmx1eMINnDpgHDgHHgMPB08A8DReABeBkcDx4KjgRtPNdBM5S/fngBHCRXl+q18v0+kXgKeCl4DSwXM/b+YwgezWfazSfWWC15vM62ktf8HpwGPhuMF/DUzRcBN4IztLwQg2fC24HSzV8sW13bX9bLF3XBEv1vmGwXu/7LrXPVWqfq9U+71f7EMY+5E/tc31I61Ptgh524X7gYnAHeI6ed9rRbr3/Np92dAt6A8HbwNPAO9S+d4Il4N3gSvCjYBV4F9gA7gYv1+vcB/K3rnGBbXqfvmCL3qeP3qc/OAEcAMr6JyjfcwRXgYPATeBgcCs=
*/