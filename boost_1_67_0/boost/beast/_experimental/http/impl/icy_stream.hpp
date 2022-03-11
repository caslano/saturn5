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
                    s_.next_layer().async_read_some(
                        net::mutable_buffer(
                            s_.buf_ + s_.n_, 3 - s_.n_),
                        std::move(*this));
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
                s_.next_layer().async_read_some(
                    b_, std::move(*this));
            }
        upcall:
            if(! cont)
            {
                ec_ = ec;
                n_ = bytes_transferred;
                BOOST_ASIO_CORO_YIELD
                s_.next_layer().async_read_some(
                    net::mutable_buffer{},
                    std::move(*this));
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
    class ReadHandler>
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
    class WriteHandler>
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