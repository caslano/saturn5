//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_ICY_STREAM_HPP
#define BOOST_BEAST_CORE_IMPL_ICY_STREAM_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <cstring>
#include <memory>
#include <utility>

namespace boost {
namespace beast {
namespace http {

namespace detail {

template<class ConstBufferSequence>
boost::tribool
is_icy(ConstBufferSequence const& buffers)
{
    char buf[3];
    auto const n = net::buffer_copy(
        net::mutable_buffer(buf, 3),
        buffers);
    if(n >= 1 && buf[0] != 'I')
        return false;
    if(n >= 2 && buf[1] != 'C')
        return false;
    if(n >= 3 && buf[2] != 'Y')
        return false;
    if(n < 3)
        return boost::indeterminate;
    return true;
}

} // detail

template<class NextLayer>
struct icy_stream<NextLayer>::ops
{

template<class Buffers, class Handler>
class read_op
    : public beast::async_base<Handler,
        beast::executor_type<icy_stream>>
    , public asio::coroutine
{
    icy_stream& s_;
    Buffers b_;
    std::size_t n_ = 0;
    error_code ec_;
    bool match_ = false;

public:
    template<class Handler_>
    read_op(
        Handler_&& h,
        icy_stream& s,
        Buffers const& b)
        : async_base<Handler,
            beast::executor_type<icy_stream>>(
                std::forward<Handler_>(h), s.get_executor())
        , s_(s)
        , b_(b)
    {
        (*this)({}, 0, false);
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred,
        bool cont = true)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            if(s_.detect_)
            {
                BOOST_ASSERT(s_.n_ == 0);
                for(;;)
                {
                    // Try to read the first three characters
                    BOOST_ASIO_CORO_YIELD
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "http::icy_stream::async_read_some"));

                        s_.next_layer().async_read_some(
                            net::mutable_buffer(
                                s_.buf_ + s_.n_, 3 - s_.n_),
                            std::move(*this));
                    }
                    s_.n_ += static_cast<char>(bytes_transferred);
                    if(ec)
                        goto upcall;
                    auto result = detail::is_icy(
                        net::const_buffer(s_.buf_, s_.n_));
                    if(boost::indeterminate(result))
                        continue;
                    if(result)
                        s_.n_ = static_cast<char>(net::buffer_copy(
                            net::buffer(s_.buf_, sizeof(s_.buf_)),
                            icy_stream::version()));
                    break;
                }
                s_.detect_ = false;
            }
            if(s_.n_ > 0)
            {
                bytes_transferred = net::buffer_copy(
                    b_, net::const_buffer(s_.buf_, s_.n_));
                s_.n_ -= static_cast<char>(bytes_transferred);
                std::memmove(
                    s_.buf_,
                    s_.buf_ + bytes_transferred,
                    sizeof(s_.buf_) - bytes_transferred);
            }
            else
            {
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::icy_stream::async_read_some"));

                    s_.next_layer().async_read_some(
                        b_, std::move(*this));
                }
            }
        upcall:
            if(! cont)
            {
                ec_ = ec;
                n_ = bytes_transferred;
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "http::icy_stream::async_read_some"));

                    s_.next_layer().async_read_some(
                        net::mutable_buffer{},
                        std::move(*this));
                }
                ec = ec_;
                bytes_transferred = n_;
            }
            this->complete_now(ec, bytes_transferred);
        }
    }
};

struct run_read_op
{
    template<class ReadHandler, class Buffers>
    void
    operator()(
        ReadHandler&& h,
        icy_stream* s,
        Buffers const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
            void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        read_op<
            Buffers,
            typename std::decay<ReadHandler>::type>(
                std::forward<ReadHandler>(h), *s, b);
    }
};

};

//------------------------------------------------------------------------------

template<class NextLayer>
template<class... Args>
icy_stream<NextLayer>::
icy_stream(Args&&... args)
    : stream_(std::forward<Args>(args)...)
{
    std::memset(buf_, 0, sizeof(buf_));
}

template<class NextLayer>
template<class MutableBufferSequence>
std::size_t
icy_stream<NextLayer>::
read_some(MutableBufferSequence const& buffers)
{
    static_assert(is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    error_code ec;
    auto n = read_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return n;
}

template<class NextLayer>
template<class MutableBufferSequence>
std::size_t
icy_stream<NextLayer>::
read_some(MutableBufferSequence const& buffers, error_code& ec)
{
    static_assert(is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    std::size_t bytes_transferred;
    if(detect_)
    {
        BOOST_ASSERT(n_ == 0);
        for(;;)
        {
            // Try to read the first three characters
            bytes_transferred = next_layer().read_some(
                net::mutable_buffer(buf_ + n_, 3 - n_), ec);
            n_ += static_cast<char>(bytes_transferred);
            if(ec)
                return 0;
            auto result = detail::is_icy(
                net::const_buffer(buf_, n_));
            if(boost::indeterminate(result))
                continue;
            if(result)
                n_ = static_cast<char>(net::buffer_copy(
                    net::buffer(buf_, sizeof(buf_)),
                    icy_stream::version()));
            break;
        }
        detect_ = false;
    }
    if(n_ > 0)
    {
        bytes_transferred = net::buffer_copy(
            buffers, net::const_buffer(buf_, n_));
        n_ -= static_cast<char>(bytes_transferred);
        std::memmove(
            buf_,
            buf_ + bytes_transferred,
            sizeof(buf_) - bytes_transferred);
    }
    else
    {
        bytes_transferred =
            next_layer().read_some(buffers, ec);
    }
    return bytes_transferred;
}

template<class NextLayer>
template<
    class MutableBufferSequence,
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
icy_stream<NextLayer>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(is_async_read_stream<next_layer_type>::value,
        "AsyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence >::value,
        "MutableBufferSequence type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            typename ops::run_read_op{},
            handler,
            this,
            buffers);
}

template<class NextLayer>
template<class MutableBufferSequence>
std::size_t
icy_stream<NextLayer>::
write_some(MutableBufferSequence const& buffers)
{
    static_assert(is_sync_write_stream<next_layer_type>::value,
        "SyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    return stream_.write_some(buffers);
}

template<class NextLayer>
template<class MutableBufferSequence>
std::size_t
icy_stream<NextLayer>::
write_some(MutableBufferSequence const& buffers, error_code& ec)
{
    static_assert(is_sync_write_stream<next_layer_type>::value,
        "SyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    return stream_.write_some(buffers, ec);
}

template<class NextLayer>
template<
    class MutableBufferSequence,
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
icy_stream<NextLayer>::
async_write_some(
    MutableBufferSequence const& buffers,
    WriteHandler&& handler)
{
    static_assert(is_async_write_stream<next_layer_type>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    return stream_.async_write_some(
        buffers, std::forward<WriteHandler>(handler));
}

} // http
} // beast
} // boost

#endif

/* icy_stream.hpp
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
*/