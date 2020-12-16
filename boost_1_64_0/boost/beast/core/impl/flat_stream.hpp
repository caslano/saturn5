//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_FLAT_STREAM_HPP
#define BOOST_BEAST_CORE_IMPL_FLAT_STREAM_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/static_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/websocket/teardown.hpp>
#include <boost/asio/buffer.hpp>
#include <memory>

namespace boost {
namespace beast {

template<class NextLayer>
struct flat_stream<NextLayer>::ops
{

template<class Handler>
class write_op
    : public async_base<Handler,
        beast::executor_type<flat_stream>>
{
public:
    template<
        class ConstBufferSequence,
        class Handler_>
    write_op(
        Handler_&& h,
        flat_stream<NextLayer>& s,
        ConstBufferSequence const& b)
        : async_base<Handler,
            beast::executor_type<flat_stream>>(
                std::forward<Handler_>(h),
                s.get_executor())
    {
        auto const result =
            flatten(b, max_size);
        if(result.flatten)
        {
            s.buffer_.clear();
            s.buffer_.commit(net::buffer_copy(
                s.buffer_.prepare(result.size),
                b, result.size));
            s.stream_.async_write_some(
                s.buffer_.data(), std::move(*this));
        }
        else
        {
            s.buffer_.clear();
            s.buffer_.shrink_to_fit();
            s.stream_.async_write_some(
                beast::buffers_prefix(
                    result.size, b), std::move(*this));
        }
    }

    void
    operator()(
        boost::system::error_code ec,
        std::size_t bytes_transferred)
    {
        this->complete_now(ec, bytes_transferred);
    }
};

struct run_write_op
{
    template<class WriteHandler, class Buffers>
    void
    operator()(
        WriteHandler&& h,
        flat_stream* s,
        Buffers const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
            void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        write_op<
            typename std::decay<WriteHandler>::type>(
                std::forward<WriteHandler>(h), *s, b);
    }
};

};

//------------------------------------------------------------------------------

template<class NextLayer>
template<class... Args>
flat_stream<NextLayer>::
flat_stream(Args&&... args)
    : stream_(std::forward<Args>(args)...)
{
}

template<class NextLayer>
template<class MutableBufferSequence>
std::size_t
flat_stream<NextLayer>::
read_some(MutableBufferSequence const& buffers)
{
    static_assert(boost::beast::is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    error_code ec;
    auto n = read_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(boost::system::system_error{ec});
    return n;
}

template<class NextLayer>
template<class MutableBufferSequence>
std::size_t
flat_stream<NextLayer>::
read_some(MutableBufferSequence const& buffers, error_code& ec)
{
    static_assert(boost::beast::is_sync_read_stream<next_layer_type>::value,
        "SyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    return stream_.read_some(buffers, ec);
}

template<class NextLayer>
template<
    class MutableBufferSequence,
    class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
flat_stream<NextLayer>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(boost::beast::is_async_read_stream<next_layer_type>::value,
        "AsyncReadStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence >::value,
        "MutableBufferSequence type requirements not met");
    return stream_.async_read_some(
        buffers, std::forward<ReadHandler>(handler));
}

template<class NextLayer>
template<class ConstBufferSequence>
std::size_t
flat_stream<NextLayer>::
write_some(ConstBufferSequence const& buffers)
{
    static_assert(boost::beast::is_sync_write_stream<next_layer_type>::value,
        "SyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    error_code ec;
    auto n = write_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(boost::system::system_error{ec});
    return n;
}

template<class NextLayer>
template<class ConstBufferSequence>
std::size_t
flat_stream<NextLayer>::
stack_write_some(
    std::size_t size,
    ConstBufferSequence const& buffers,
    error_code& ec)
{
    static_buffer<max_stack> b;
    b.commit(net::buffer_copy(
        b.prepare(size), buffers));
    return stream_.write_some(b.data(), ec);
}

template<class NextLayer>
template<class ConstBufferSequence>
std::size_t
flat_stream<NextLayer>::
write_some(ConstBufferSequence const& buffers, error_code& ec)
{
    static_assert(boost::beast::is_sync_write_stream<next_layer_type>::value,
        "SyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    auto const result = flatten(buffers, max_size);
    if(result.flatten)
    {
        if(result.size <= max_stack)
            return stack_write_some(result.size, buffers, ec);

        buffer_.clear();
        buffer_.commit(net::buffer_copy(
            buffer_.prepare(result.size),
            buffers));
        return stream_.write_some(buffer_.data(), ec);
    }
    buffer_.clear();
    buffer_.shrink_to_fit();
    return stream_.write_some(
        boost::beast::buffers_prefix(result.size, buffers), ec);
}

template<class NextLayer>
template<
    class ConstBufferSequence,
    class WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
flat_stream<NextLayer>::
async_write_some(
    ConstBufferSequence const& buffers,
    WriteHandler&& handler)
{
    static_assert(boost::beast::is_async_write_stream<next_layer_type>::value,
        "AsyncWriteStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            typename ops::run_write_op{},
            handler,
            this,
            buffers);
}

template<class NextLayer>
void
teardown(
    boost::beast::role_type role,
    flat_stream<NextLayer>& s,
    error_code& ec)
{
    using boost::beast::websocket::teardown;
    teardown(role, s.next_layer(), ec);
}

template<class NextLayer, class TeardownHandler>
void
async_teardown(
    boost::beast::role_type role,
    flat_stream<NextLayer>& s,
    TeardownHandler&& handler)
{
    using boost::beast::websocket::async_teardown;
    async_teardown(role, s.next_layer(), std::move(handler));
}

} // beast
} // boost

#endif

/* flat_stream.hpp
18jy8i3mn/JXy3EdTtuDI0jfykk5CMqsgF503r8GarRJ2JM2CUGDNDzPwPGcD1nAZcBpwMtpq3IdbVVuoK3KLbRVWUtblTfQRuU24KXA7cBc4DO0Wfk8sJB+O4uAr9Pv6IfAEuAn9Ct6DFgBPA5cThuXK4DfAFcCnbRJGUmblG2APwKm0TZlf2CN3i/AtcAzaavyHOBVwAnADcDzgJv0+wVupq3Mq4GXAXFvsq5dA1wKvBa4Cnid3h/A64HXAG8AXg/8KXA38BfAt4G3AhuBdbSZeQewPcZku14/8F7g+cAHgIuADwGXAH8L3AR8GHgj8BHgTcDHgD8D7gLWAf8AfAS4B7gH+AzwTeBzev3AfcB/AZ9X85MyBMAzLObni5yfL9Gv6185H18BptIv+OmMK/+iLC+e5SlbmvR33ob+muOAH9P/WV91dizn4kLXU/xq01428iUB0Wcyv/9FP2rHgeOAXwDPBX4JzJL57H4P/hs4F+hwYvyATq47EcC1wFbA9cDWXGeigbcB2wGfAHYC7gPGA/cDE4ENwK7ATxk/CkwGfgtMAcbqbQf2BvYC9gH25nuzG3AwsDtwCLAz8EJgAnAOMAa4EtgGuAaYCqwBpgE3A/sA2c88S+U6YOEPvR/9oWeZ/KHz7A/Yz4LuG473t0C5xvFR51o8gwOd6CZMBGr0n5lM/52DgPcCpwDvY//vBFYA7wfeD3wA+Ff67/w78GHgR8BHgJ/QH+4/6Q/3OP3ffkX/t3ojngBGAncDo4BPAhOATwNTgHuAo4F/Al4EfBaYB9wHvB1YD3wI+CLwEeBLwMeAfwXuAj4PfBr4AvBZ4H4gromf20PAfwCPAd8AfgFsAGKuiD/azsC3gd2A7wKTgO/p7QJ+AOwPPGj0x7nO/nlZyudlJZ+X5aQ7gFBHulQ+Lwni1x8/+qnsAqzheKwFjgBeQb+DVwLHAO8ATqWfyun0Uzmb18uAmzhum4HX0A/p9fQn+gvgdXp/0l/sU/QT+wz9pD5PP6n76f/0AP2fHgX+HNhKXw+BMcA6YEfgHUZ/sevt5/dHnN+HOL8PG/2Ir7ef3//k/P6M8/tz0tUqHp3wH4XuDPHj6fUHmUh/kKnAAcDRwIHAbPp7zKGfx8vo3/Fu+nd8DjgM+BL9AL9NP8Dv02/qh/Sb+jn9pH4NHA9s6ZDnS/bT5wIXAs8DLgFOAlYDJwNrgVOANwCzgNuAU4E/A07jfL8QuBs4E7gHOAv4J+Bs4AfAOcCPgDnAj4FzgZ8C5wG/BOYCuzoxFpzP8zmfC4G9gEXANGAx5/cC4EBgCXAwsBQ4BbgQOBVYDpwBrAAWAl3ABcDFwGXAJUY/r7QDk2mx30mk/+cU4Fj6yRxPP5nvBmnDGP4xT8iGMXxm/tfsGMOHZkBbxvSreUptGgf0u9nM9o3hk9PWxjH8c9LOcXA+OpvL3jH8d/7XbR6fiG/PkOweXx5xymwf570LP5wIOxD2ITQiJLwXpY1GKEHYivAQwgGE4wgJ78N/J0IOQjXCLQi7ERoQtA9gPxlhIkIJwsYPwjaLwr/w72R+p0j/v6C8uHn0//+i9P+934d9eG6fhLADKbsXqzNj6A/m5pfBkVJF4dKyIsM5eH77wDpfbhmOdm55HurUXwXiDuTPHu4Mfoy7Lm8duaVKhuNYJ/oDVGfTzE9/gTfH6+noGoMsdsslevo0+HKgTQGhoU0B+uPBzqm0EPqRBVWlFXJWRF+B0UIbbTrvjef5zyxJS3SsQLnvI+j1J8aLt/mFVYtcSpeoi+S72DEY//8OoQ/tHzzcyX22BHEtdR69TPJ+pmWj9x/WOtF2ArxUyfX9Wkdc9bZlkejiYL/M9A6OJO0=
*/