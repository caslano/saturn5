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

template<class Stream, class DynamicBuffer>
template<class... Args>
buffered_read_stream<Stream, DynamicBuffer>::
buffered_read_stream(Args&&... args)
    : next_layer_(std::forward<Args>(args)...)
{
}

template<class Stream, class DynamicBuffer>
template<class ConstBufferSequence, class WriteHandler>
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
    static_assert(detail::is_invocable<WriteHandler,
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
template<class MutableBufferSequence, class ReadHandler>
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
            buffers);
}

} // beast
} // boost

#endif

/* buffered_read_stream.hpp
ypcGK0yxiWy/XW0IG74pVysbPsfas6pTtjXLfSowx2afYq8TtjmmUee8X+zeFlWf08a2mM/17cEIi5DSdrWtLZZiIF3dAAWb+ikDzQMImaKfVKWfA6mf9taz8Xx1HtbKDQMJz9BO82EEn2lz0Gx7PnxZlTnsjNT4i3m3lZ5K3gnEdpZ7qW7tX+gyFd3uQif3FN0huDMy8LwEoS0FpRp/jZQ8LUYa/me/x7J6WWlmCA3b43aSfivSE9jvBWmyhMfDBgsNKyk0Bn9B8vSxvAek43vQiLjbOCdfM86paLaPc05GXDvO4e/v8ZKnCuOcQbwX1FOZqSdpEyuT8f2UyrFN+vjwsQ3zrEkNjm12cY5tVJ7sDTm2GVRqOMc27Y0VJlE+sw0WGa7X3ijKYccVevcqnO8e8/qBqFfcZ1vAvdnqntS10Deaa2jyvrEuLfYbU+S+1JHtHUijx7dtAyB2BkeZ78A1tncAJiaGtX0J05SbebuptrW5xIfj2So/BWLbUjTbWvyLVTfMALJN29LjpG3Uo4yQrneU9Jx2fdaZ8icpXQnfgfFZ6B554/hM+Rgz+WF/RR9sPeR/jCHYX+UhTIeu/AFdwRzJN7WuvKS2tML82B4OXqVdO+1wmD+PsoltImYKqBtHer1DNxWWdGv7pD2ivs2xzwc/YXahcXIPPFhtER06GE4dLKUO+rDw3ghfZ+D3MaADH0b0GMBus7WhGedDfubt4zqeN4u/Q9J7RajbXCVTkrKnxDMc9TUlg+fIsL5yEJIha1uA12m15eU+Tsb4SuurLPWFO4pf5kcp1Dd+d6O3mwroG+U5/PmNle9U4UuuFIQ60xYpsFfDbD++0hl+thHytLXiiflS7enD2Ybs6eyHa8uBSscZkp7IOGpD4p5I75NV52wzwpPcS7PeG047Nspa1iNc1gIQ5Npl9Y06YMxuE3Yf69t9fJFvj30Ni6/CEp9hte2jbKH0qSp9n1C6jL3GQc/ZeH7WZqh7IzkPX/gJmOLS6iVPaOOVXoZQL2b/H21fE/BbGOCZuuE98OloB4UbG3IRxM7IAz3mK91IM5Df098Hii6oh2CeBEvaVOogmLaxVs6Rkp6k5Bzdfv0HxpKUEc8zZZR4mopP5bcG+8usAKEJqQzl5rxkQLa6I31qenHiOBlmSb3gN1b6jCMtdU6aLOs7qvqUfSzp1t91vqP6/oPv6GT5bTSfx+9p9d7KM2wyPeAi0wzQ+11lqi6fxW8Fr/BciqlbzA5bfwscfE+Kgu8s8u0VHlWZtnfuip7hfNaAzyZXPv01fp/ZHer0TzqOF1NEFjP/tIbqUosPUYcsB0Yhi1sdZLEOUkQ+9RxbPfiz3dtWi7t8DXUVetlaIrctla6+1/6kXO21rdG9wmUqBX2rq0wzS6oayoXnknCZSJNlGUNUls1W398qPTRW7oBMJUomp703nvEPsQ9e33bAHfVJNOgA877vvJnXl7VWPzRikxdOXbL8le3/Pn+tr+aY92dvdUraq599OX/Cubc1rjps4qF6u+G3skTee57/PWln/xPHJz455Kvr7lnzz7Mb1tgHa+yJO243/IPZ9xhyydy2H/neMALfnss8cjakkW75O83yd6bl7xT1d2BsMt8DHZjvPP8+1/yG5t8vc55utVofknU6SetNG1+D507uRHva52i/+RKwHPgqcBrwTeB02hdXAn+nnaYXZdUBU4AzgZvyfMkBwNnAPXjO5GTgScDZPKdyHnAG8DxgNfBGnlt5M/A44HLg8cAvgScAvwWeCFwHPBTYxxuw+ywA+oBjgMXAQ4EltBudrOaVhVbkTgKOo9wP0n55KXAE8BGeY/kY0NTv48A9gU8A9wc+DZw=
*/