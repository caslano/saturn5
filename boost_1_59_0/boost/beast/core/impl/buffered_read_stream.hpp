//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_IMPL_BUFFERED_READ_STREAM_HPP
#define BOOST_BEAST_IMPL_BUFFERED_READ_STREAM_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/post.hpp>
#include <boost/throw_exception.hpp>

namespace boost {
namespace beast {


template<class Stream, class DynamicBuffer>
struct buffered_read_stream<Stream, DynamicBuffer>::ops
{

template<class MutableBufferSequence, class Handler>
class read_op
    : public async_base<Handler,
    beast::executor_type<buffered_read_stream>>
{
    buffered_read_stream& s_;
    MutableBufferSequence b_;
    int step_ = 0;

public:
    read_op(read_op&&) = default;
    read_op(read_op const&) = delete;

    template<class Handler_>
    read_op(
        Handler_&& h,
        buffered_read_stream& s,
        MutableBufferSequence const& b)
        : async_base<
            Handler, beast::executor_type<buffered_read_stream>>(
                std::forward<Handler_>(h), s.get_executor())
        , s_(s)
        , b_(b)
    {
        (*this)({}, 0);
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred)
    {
        // VFALCO TODO Rewrite this using reenter/yield
        switch(step_)
        {
        case 0:
            if(s_.buffer_.size() == 0)
            {
                if(s_.capacity_ == 0)
                {
                    // read (unbuffered)
                    step_ = 1;
                    return s_.next_layer_.async_read_some(
                        b_, std::move(*this));
                }
                // read
                step_ = 2;
                return s_.next_layer_.async_read_some(
                    s_.buffer_.prepare(read_size(
                        s_.buffer_, s_.capacity_)),
                            std::move(*this));
            }
            step_ = 3;
            return net::post(
                s_.get_executor(),
                beast::bind_front_handler(
                    std::move(*this), ec, 0));

        case 1:
            // upcall
            break;

        case 2:
            s_.buffer_.commit(bytes_transferred);
            BOOST_FALLTHROUGH;

        case 3:
            bytes_transferred =
                net::buffer_copy(b_, s_.buffer_.data());
            s_.buffer_.consume(bytes_transferred);
            break;
        }
        this->complete_now(ec, bytes_transferred);
    }
};

struct run_read_op
{
    template<class ReadHandler, class Buffers>
    void
    operator()(
        ReadHandler&& h,
        buffered_read_stream* s,
        Buffers const* b)
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
                std::forward<ReadHandler>(h), *s, *b);
    }
};

};

//------------------------------------------------------------------------------

template<class Stream, class DynamicBuffer>
template<class... Args>
buffered_read_stream<Stream, DynamicBuffer>::
buffered_read_stream(Args&&... args)
    : next_layer_(std::forward<Args>(args)...)
{
}

template<class Stream, class DynamicBuffer>
template<class ConstBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
buffered_read_stream<Stream, DynamicBuffer>::
async_write_some(
    ConstBufferSequence const& buffers,
    WriteHandler&& handler)
{
    static_assert(is_async_write_stream<next_layer_type>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    static_assert(detail::is_completion_token_for<WriteHandler,
        void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");
    return next_layer_.async_write_some(buffers,
        std::forward<WriteHandler>(handler));
}

template<class Stream, class DynamicBuffer>
template<class MutableBufferSequence>
std::size_t
buffered_read_stream<Stream, DynamicBuffer>::
read_some(
    MutableBufferSequence const& buffers)
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

template<class Stream, class DynamicBuffer>
template<class MutableBufferSequence>
std::size_t
buffered_read_stream<Stream, DynamicBuffer>::
read_some(MutableBufferSequence const& buffers,
    error_code& ec)
{
    static_assert(is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    if(buffer_.size() == 0)
    {
        if(capacity_ == 0)
            return next_layer_.read_some(buffers, ec);
        buffer_.commit(next_layer_.read_some(
            buffer_.prepare(read_size(buffer_,
                capacity_)), ec));
        if(ec)
            return 0;
    }
    else
    {
        ec = {};
    }
    auto bytes_transferred =
        net::buffer_copy(buffers, buffer_.data());
    buffer_.consume(bytes_transferred);
    return bytes_transferred;
}

template<class Stream, class DynamicBuffer>
template<class MutableBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
buffered_read_stream<Stream, DynamicBuffer>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(is_async_read_stream<next_layer_type>::value,
        "AsyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
            "MutableBufferSequence type requirements not met");
    if(buffer_.size() == 0 && capacity_ == 0)
        return next_layer_.async_read_some(buffers,
            std::forward<ReadHandler>(handler));
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            typename ops::run_read_op{},
            handler,
            this,
            &buffers);
}

} // beast
} // boost

#endif

/* buffered_read_stream.hpp
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
*/