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

            BOOST_ASIO_HANDLER_LOCATION((
                __FILE__, __LINE__,
                "flat_stream::async_write_some"));

            s.stream_.async_write_some(
                s.buffer_.data(), std::move(*this));
        }
        else
        {
            s.buffer_.clear();
            s.buffer_.shrink_to_fit();

            BOOST_ASIO_HANDLER_LOCATION((
                __FILE__, __LINE__,
                "flat_stream::async_write_some"));

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
    BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
    BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
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