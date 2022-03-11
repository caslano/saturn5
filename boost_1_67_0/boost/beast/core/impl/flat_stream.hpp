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
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
*/