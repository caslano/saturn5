//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_READ_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_READ_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/websocket/teardown.hpp>
#include <boost/beast/websocket/detail/mask.hpp>
#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/read_size.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/bind_continuation.hpp>
#include <boost/beast/core/detail/buffer.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/core/detail/config.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <limits>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

/*  Read some message data into a buffer sequence.

    Also reads and handles control frames.
*/
template<class NextLayer, bool deflateSupported>
template<class Handler, class MutableBufferSequence>
class stream<NextLayer, deflateSupported>::read_some_op
    : public beast::async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    boost::weak_ptr<impl_type> wp_;
    MutableBufferSequence bs_;
    buffers_suffix<MutableBufferSequence> cb_;
    std::size_t bytes_written_ = 0;
    error_code result_;
    close_code code_;
    bool did_read_ = false;

public:
    static constexpr int id = 1; // for soft_mutex

    template<class Handler_>
    read_some_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        MutableBufferSequence const& bs)
        : async_base<
            Handler, beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , bs_(bs)
        , cb_(bs)
        , code_(close_code::none)
    {
        (*this)({}, 0, false);
    }

    void operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true)
    {
        using beast::detail::clamp;
        auto sp = wp_.lock();
        if(! sp)
        {
            ec = net::error::operation_aborted;
            bytes_written_ = 0;
            return this->complete(cont, ec, bytes_written_);
        }
        auto& impl = *sp;
        BOOST_ASIO_CORO_REENTER(*this)
        {
            impl.update_timer(this->get_executor());

        acquire_read_lock:
            // Acquire the read lock
            if(! impl.rd_block.try_lock(this))
            {
            do_suspend:
                BOOST_ASIO_CORO_YIELD
                impl.op_r_rd.emplace(std::move(*this));
                impl.rd_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                net::post(std::move(*this));
                BOOST_ASSERT(impl.rd_block.is_locked(this));

                // VFALCO Is this check correct here?
                BOOST_ASSERT(! ec && impl.check_stop_now(ec));
                if(impl.check_stop_now(ec))
                {
                    BOOST_ASSERT(ec == net::error::operation_aborted);
                    goto upcall;
                }
                // VFALCO Should never get here

                // The only way to get read blocked is if
                // a `close_op` wrote a close frame
                BOOST_ASSERT(impl.wr_close);
                BOOST_ASSERT(impl.status_ != status::open);
                ec = net::error::operation_aborted;
                goto upcall;
            }
            else
            {
                // Make sure the stream is not closed
                if( impl.status_ == status::closed ||
                    impl.status_ == status::failed)
                {
                    ec = net::error::operation_aborted;
                    goto upcall;
                }
            }

            // if status_ == status::closing, we want to suspend
            // the read operation until the close completes,
            // then finish the read with operation_aborted.

        loop:
            BOOST_ASSERT(impl.rd_block.is_locked(this));
            // See if we need to read a frame header. This
            // condition is structured to give the decompressor
            // a chance to emit the final empty deflate block
            //
            if(impl.rd_remain == 0 &&
                (! impl.rd_fh.fin || impl.rd_done))
            {
                // Read frame header
                while(! impl.parse_fh(
                    impl.rd_fh, impl.rd_buf, result_))
                {
                    if(result_)
                    {
                        // _Fail the WebSocket Connection_
                        if(result_ == error::message_too_big)
                            code_ = close_code::too_big;
                        else
                            code_ = close_code::protocol_error;
                        goto close;
                    }
                    BOOST_ASSERT(impl.rd_block.is_locked(this));
                    BOOST_ASIO_CORO_YIELD
                    impl.stream().async_read_some(
                        impl.rd_buf.prepare(read_size(
                            impl.rd_buf, impl.rd_buf.max_size())),
                                std::move(*this));
                    BOOST_ASSERT(impl.rd_block.is_locked(this));
                    impl.rd_buf.commit(bytes_transferred);
                    if(impl.check_stop_now(ec))
                        goto upcall;
                    impl.reset_idle();

                    // Allow a close operation
                    // to acquire the read block
                    impl.rd_block.unlock(this);
                    if( impl.op_r_close.maybe_invoke())
                    {
                        // Suspend
                        BOOST_ASSERT(impl.rd_block.is_locked());
                        goto do_suspend;
                    }
                    // Acquire read block
                    impl.rd_block.lock(this);
                }
                // Immediately apply the mask to the portion
                // of the buffer holding payload data.
                if(impl.rd_fh.len > 0 && impl.rd_fh.mask)
                    detail::mask_inplace(buffers_prefix(
                        clamp(impl.rd_fh.len),
                            impl.rd_buf.data()),
                                impl.rd_key);
                if(detail::is_control(impl.rd_fh.op))
                {
                    // Clear this otherwise the next
                    // frame will be considered final.
                    impl.rd_fh.fin = false;

                    // Handle ping frame
                    if(impl.rd_fh.op == detail::opcode::ping)
                    {
                        if(impl.ctrl_cb)
                        {
                            if(! cont)
                            {
                                BOOST_ASIO_CORO_YIELD
                                net::post(std::move(*this));
                                BOOST_ASSERT(cont);
                                // VFALCO call check_stop_now() here?
                            }
                        }
                        {
                            auto const b = buffers_prefix(
                                clamp(impl.rd_fh.len),
                                    impl.rd_buf.data());
                            auto const len = buffer_bytes(b);
                            BOOST_ASSERT(len == impl.rd_fh.len);
                            ping_data payload;
                            detail::read_ping(payload, b);
                            impl.rd_buf.consume(len);
                            // Ignore ping when closing
                            if(impl.status_ == status::closing)
                                goto loop;
                            if(impl.ctrl_cb)
                                impl.ctrl_cb(
                                    frame_type::ping, payload);
                            impl.rd_fb.clear();
                            impl.template write_ping<
                                flat_static_buffer_base>(impl.rd_fb,
                                    detail::opcode::pong, payload);
                        }

                        // Allow a close operation
                        // to acquire the read block
                        impl.rd_block.unlock(this);
                        impl.op_r_close.maybe_invoke();

                        // Acquire the write lock
                        if(! impl.wr_block.try_lock(this))
                        {
                            BOOST_ASIO_CORO_YIELD
                            impl.op_rd.emplace(std::move(*this));
                            impl.wr_block.lock(this);
                            BOOST_ASIO_CORO_YIELD
                            net::post(std::move(*this));
                            BOOST_ASSERT(impl.wr_block.is_locked(this));
                            if(impl.check_stop_now(ec))
                                goto upcall;
                        }

                        // Send pong
                        BOOST_ASSERT(impl.wr_block.is_locked(this));
                        BOOST_ASIO_CORO_YIELD
                        net::async_write(
                            impl.stream(), impl.rd_fb.data(),
                            beast::detail::bind_continuation(std::move(*this)));
                        BOOST_ASSERT(impl.wr_block.is_locked(this));
                        if(impl.check_stop_now(ec))
                            goto upcall;
                        impl.wr_block.unlock(this);
                        impl.op_close.maybe_invoke()
                            || impl.op_idle_ping.maybe_invoke()
                            || impl.op_ping.maybe_invoke()
                            || impl.op_wr.maybe_invoke();
                        goto acquire_read_lock;
                    }

                    // Handle pong frame
                    if(impl.rd_fh.op == detail::opcode::pong)
                    {
                        // Ignore pong when closing
                        if(! impl.wr_close && impl.ctrl_cb)
                        {
                            if(! cont)
                            {
                                BOOST_ASIO_CORO_YIELD
                                net::post(std::move(*this));
                                BOOST_ASSERT(cont);
                            }
                        }
                        auto const cb = buffers_prefix(clamp(
                            impl.rd_fh.len), impl.rd_buf.data());
                        auto const len = buffer_bytes(cb);
                        BOOST_ASSERT(len == impl.rd_fh.len);
                        ping_data payload;
                        detail::read_ping(payload, cb);
                        impl.rd_buf.consume(len);
                        // Ignore pong when closing
                        if(! impl.wr_close && impl.ctrl_cb)
                            impl.ctrl_cb(frame_type::pong, payload);
                        goto loop;
                    }

                    // Handle close frame
                    BOOST_ASSERT(impl.rd_fh.op == detail::opcode::close);
                    {
                        if(impl.ctrl_cb)
                        {
                            if(! cont)
                            {
                                BOOST_ASIO_CORO_YIELD
                                net::post(std::move(*this));
                                BOOST_ASSERT(cont);
                            }
                        }
                        auto const cb = buffers_prefix(clamp(
                            impl.rd_fh.len), impl.rd_buf.data());
                        auto const len = buffer_bytes(cb);
                        BOOST_ASSERT(len == impl.rd_fh.len);
                        BOOST_ASSERT(! impl.rd_close);
                        impl.rd_close = true;
                        close_reason cr;
                        detail::read_close(cr, cb, result_);
                        if(result_)
                        {
                            // _Fail the WebSocket Connection_
                            code_ = close_code::protocol_error;
                            goto close;
                        }
                        impl.cr = cr;
                        impl.rd_buf.consume(len);
                        if(impl.ctrl_cb)
                            impl.ctrl_cb(frame_type::close,
                                impl.cr.reason);
                        // See if we are already closing
                        if(impl.status_ == status::closing)
                        {
                            // _Close the WebSocket Connection_
                            BOOST_ASSERT(impl.wr_close);
                            code_ = close_code::none;
                            result_ = error::closed;
                            goto close;
                        }
                        // _Start the WebSocket Closing Handshake_
                        code_ = cr.code == close_code::none ?
                            close_code::normal :
                            static_cast<close_code>(cr.code);
                        result_ = error::closed;
                        goto close;
                    }
                }
                if(impl.rd_fh.len == 0 && ! impl.rd_fh.fin)
                {
                    // Empty non-final frame
                    goto loop;
                }
                impl.rd_done = false;
            }
            if(! impl.rd_deflated())
            {
                if(impl.rd_remain > 0)
                {
                    if(impl.rd_buf.size() == 0 && impl.rd_buf.max_size() >
                        (std::min)(clamp(impl.rd_remain),
                            buffer_bytes(cb_)))
                    {
                        // Fill the read buffer first, otherwise we
                        // get fewer bytes at the cost of one I/O.
                        BOOST_ASIO_CORO_YIELD
                        impl.stream().async_read_some(
                            impl.rd_buf.prepare(read_size(
                                impl.rd_buf, impl.rd_buf.max_size())),
                                    std::move(*this));
                        impl.rd_buf.commit(bytes_transferred);
                        if(impl.check_stop_now(ec))
                            goto upcall;
                        impl.reset_idle();
                        if(impl.rd_fh.mask)
                            detail::mask_inplace(buffers_prefix(clamp(
                                impl.rd_remain), impl.rd_buf.data()),
                                    impl.rd_key);
                    }
                    if(impl.rd_buf.size() > 0)
                    {
                        // Copy from the read buffer.
                        // The mask was already applied.
                        bytes_transferred = net::buffer_copy(cb_,
                            impl.rd_buf.data(), clamp(impl.rd_remain));
                        auto const mb = buffers_prefix(
                            bytes_transferred, cb_);
                        impl.rd_remain -= bytes_transferred;
                        if(impl.rd_op == detail::opcode::text)
                        {
                            if(! impl.rd_utf8.write(mb) ||
                                (impl.rd_remain == 0 && impl.rd_fh.fin &&
                                    ! impl.rd_utf8.finish()))
                            {
                                // _Fail the WebSocket Connection_
                                code_ = close_code::bad_payload;
                                result_ = error::bad_frame_payload;
                                goto close;
                            }
                        }
                        bytes_written_ += bytes_transferred;
                        impl.rd_size += bytes_transferred;
                        impl.rd_buf.consume(bytes_transferred);
                    }
                    else
                    {
                        // Read into caller's buffer
                        BOOST_ASSERT(impl.rd_remain > 0);
                        BOOST_ASSERT(buffer_bytes(cb_) > 0);
                        BOOST_ASSERT(buffer_bytes(buffers_prefix(
                            clamp(impl.rd_remain), cb_)) > 0);
                        BOOST_ASIO_CORO_YIELD
                        impl.stream().async_read_some(buffers_prefix(
                            clamp(impl.rd_remain), cb_), std::move(*this));
                        if(impl.check_stop_now(ec))
                            goto upcall;
                        impl.reset_idle();
                        BOOST_ASSERT(bytes_transferred > 0);
                        auto const mb = buffers_prefix(
                            bytes_transferred, cb_);
                        impl.rd_remain -= bytes_transferred;
                        if(impl.rd_fh.mask)
                            detail::mask_inplace(mb, impl.rd_key);
                        if(impl.rd_op == detail::opcode::text)
                        {
                            if(! impl.rd_utf8.write(mb) ||
                                (impl.rd_remain == 0 && impl.rd_fh.fin &&
                                    ! impl.rd_utf8.finish()))
                            {
                                // _Fail the WebSocket Connection_
                                code_ = close_code::bad_payload;
                                result_ = error::bad_frame_payload;
                                goto close;
                            }
                        }
                        bytes_written_ += bytes_transferred;
                        impl.rd_size += bytes_transferred;
                    }
                }
                BOOST_ASSERT( ! impl.rd_done );
                if( impl.rd_remain == 0 && impl.rd_fh.fin )
                    impl.rd_done = true;
            }
            else
            {
                // Read compressed message frame payload:
                // inflate even if rd_fh_.len == 0, otherwise we
                // never emit the end-of-stream deflate block.
                while(buffer_bytes(cb_) > 0)
                {
                    if( impl.rd_remain > 0 &&
                        impl.rd_buf.size() == 0 &&
                        ! did_read_)
                    {
                        // read new
                        BOOST_ASIO_CORO_YIELD
                        impl.stream().async_read_some(
                            impl.rd_buf.prepare(read_size(
                                impl.rd_buf, impl.rd_buf.max_size())),
                                    std::move(*this));
                        if(impl.check_stop_now(ec))
                            goto upcall;
                        impl.reset_idle();
                        BOOST_ASSERT(bytes_transferred > 0);
                        impl.rd_buf.commit(bytes_transferred);
                        if(impl.rd_fh.mask)
                            detail::mask_inplace(
                                buffers_prefix(clamp(impl.rd_remain),
                                    impl.rd_buf.data()), impl.rd_key);
                        did_read_ = true;
                    }
                    zlib::z_params zs;
                    {
                        auto const out = buffers_front(cb_);
                        zs.next_out = out.data();
                        zs.avail_out = out.size();
                        BOOST_ASSERT(zs.avail_out > 0);
                    }
                    if(impl.rd_remain > 0)
                    {
                        if(impl.rd_buf.size() > 0)
                        {
                            // use what's there
                            auto const in = buffers_prefix(
                                clamp(impl.rd_remain), buffers_front(
                                    impl.rd_buf.data()));
                            zs.avail_in = in.size();
                            zs.next_in = in.data();
                        }
                        else
                        {
                            break;
                        }
                    }
                    else if(impl.rd_fh.fin)
                    {
                        // append the empty block codes
                        std::uint8_t constexpr
                            empty_block[4] = { 0x00, 0x00, 0xff, 0xff };
                        zs.next_in = empty_block;
                        zs.avail_in = sizeof(empty_block);
                        impl.inflate(zs, zlib::Flush::sync, ec);
                        if(! ec)
                        {
                            // https://github.com/madler/zlib/issues/280
                            if(zs.total_out > 0)
                                ec = error::partial_deflate_block;
                        }
                        if(impl.check_stop_now(ec))
                            goto upcall;
                        impl.do_context_takeover_read(impl.role);
                        impl.rd_done = true;
                        break;
                    }
                    else
                    {
                        break;
                    }
                    impl.inflate(zs, zlib::Flush::sync, ec);
                    if(impl.check_stop_now(ec))
                        goto upcall;
                    if(impl.rd_msg_max && beast::detail::sum_exceeds(
                        impl.rd_size, zs.total_out, impl.rd_msg_max))
                    {
                        // _Fail the WebSocket Connection_
                        code_ = close_code::too_big;
                        result_ = error::message_too_big;
                        goto close;
                    }
                    cb_.consume(zs.total_out);
                    impl.rd_size += zs.total_out;
                    impl.rd_remain -= zs.total_in;
                    impl.rd_buf.consume(zs.total_in);
                    bytes_written_ += zs.total_out;
                }
                if(impl.rd_op == detail::opcode::text)
                {
                    // check utf8
                    if(! impl.rd_utf8.write(
                        buffers_prefix(bytes_written_, bs_)) || (
                            impl.rd_done && ! impl.rd_utf8.finish()))
                    {
                        // _Fail the WebSocket Connection_
                        code_ = close_code::bad_payload;
                        result_ = error::bad_frame_payload;
                        goto close;
                    }
                }
            }
            goto upcall;

        close:
            // Acquire the write lock
            if(! impl.wr_block.try_lock(this))
            {
                BOOST_ASIO_CORO_YIELD
                impl.op_rd.emplace(std::move(*this));
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                net::post(std::move(*this));
                BOOST_ASSERT(impl.wr_block.is_locked(this));
                if(impl.check_stop_now(ec))
                    goto upcall;
            }

            impl.change_status(status::closing);

            if(! impl.wr_close)
            {
                impl.wr_close = true;

                // Serialize close frame
                impl.rd_fb.clear();
                impl.template write_close<
                    flat_static_buffer_base>(
                        impl.rd_fb, code_);

                // Send close frame
                BOOST_ASSERT(impl.wr_block.is_locked(this));
                BOOST_ASIO_CORO_YIELD
                net::async_write(impl.stream(), impl.rd_fb.data(),
                    beast::detail::bind_continuation(std::move(*this)));
                BOOST_ASSERT(impl.wr_block.is_locked(this));
                if(impl.check_stop_now(ec))
                    goto upcall;
            }

            // Teardown
            using beast::websocket::async_teardown;
            BOOST_ASSERT(impl.wr_block.is_locked(this));
            BOOST_ASIO_CORO_YIELD
            async_teardown(impl.role, impl.stream(),
                beast::detail::bind_continuation(std::move(*this)));
            BOOST_ASSERT(impl.wr_block.is_locked(this));
            if(ec == net::error::eof)
            {
                // Rationale:
                // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
                ec = {};
            }
            if(! ec)
                ec = result_;
            if(ec && ec != error::closed)
                impl.change_status(status::failed);
            else
                impl.change_status(status::closed);
            impl.close();

        upcall:
            impl.rd_block.try_unlock(this);
            impl.op_r_close.maybe_invoke();
            if(impl.wr_block.try_unlock(this))
                impl.op_close.maybe_invoke()
                    || impl.op_idle_ping.maybe_invoke()
                    || impl.op_ping.maybe_invoke()
                    || impl.op_wr.maybe_invoke();
            this->complete(cont, ec, bytes_written_);
        }
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class Handler,  class DynamicBuffer>
class stream<NextLayer, deflateSupported>::read_op
    : public beast::async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    boost::weak_ptr<impl_type> wp_;
    DynamicBuffer& b_;
    std::size_t limit_;
    std::size_t bytes_written_ = 0;
    bool some_;

public:
    template<class Handler_>
    read_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        DynamicBuffer& b,
        std::size_t limit,
        bool some)
        : async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , b_(b)
        , limit_(limit ? limit : (
            std::numeric_limits<std::size_t>::max)())
        , some_(some)
    {
        (*this)({}, 0, false);
    }

    void operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true)
    {
        using beast::detail::clamp;
        auto sp = wp_.lock();
        if(! sp)
        {
            ec = net::error::operation_aborted;
            bytes_written_ = 0;
            return this->complete(cont, ec, bytes_written_);
        }
        auto& impl = *sp;
        using mutable_buffers_type = typename
            DynamicBuffer::mutable_buffers_type;
        BOOST_ASIO_CORO_REENTER(*this)
        {
            do
            {
                // VFALCO TODO use boost::beast::bind_continuation
                BOOST_ASIO_CORO_YIELD
                {
                    auto mb = beast::detail::dynamic_buffer_prepare(b_,
                        clamp(impl.read_size_hint_db(b_), limit_),
                            ec, error::buffer_overflow);
                    if(impl.check_stop_now(ec))
                        goto upcall;
                    read_some_op<read_op, mutable_buffers_type>(
                        std::move(*this), sp, *mb);
                }

                b_.commit(bytes_transferred);
                bytes_written_ += bytes_transferred;
                if(ec)
                    goto upcall;
            }
            while(! some_ && ! impl.rd_done);

        upcall:
            this->complete(cont, ec, bytes_written_);
        }
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_read_some_op
{
    template<
        class ReadHandler,
        class MutableBufferSequence>
    void
    operator()(
        ReadHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        MutableBufferSequence const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
                void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        read_some_op<
            typename std::decay<ReadHandler>::type,
            MutableBufferSequence>(
                std::forward<ReadHandler>(h),
                sp,
                b);
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_read_op
{
    template<
        class ReadHandler,
        class DynamicBuffer>
    void
    operator()(
        ReadHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        DynamicBuffer* b,
        std::size_t limit,
        bool some)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
                void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        read_op<
            typename std::decay<ReadHandler>::type,
            DynamicBuffer>(
                std::forward<ReadHandler>(h),
                sp,
                *b,
                limit,
                some);
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
std::size_t
stream<NextLayer, deflateSupported>::
read(DynamicBuffer& buffer)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    error_code ec;
    auto const bytes_written = read(buffer, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_written;
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
std::size_t
stream<NextLayer, deflateSupported>::
read(DynamicBuffer& buffer, error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    std::size_t bytes_written = 0;
    do
    {
        bytes_written += read_some(buffer, 0, ec);
        if(ec)
            return bytes_written;
    }
    while(! is_message_done());
    return bytes_written;
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer, class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
stream<NextLayer, deflateSupported>::
async_read(DynamicBuffer& buffer, ReadHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            run_read_op{},
            handler,
            impl_,
            &buffer,
            0,
            false);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
std::size_t
stream<NextLayer, deflateSupported>::
read_some(
    DynamicBuffer& buffer,
    std::size_t limit)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    error_code ec;
    auto const bytes_written =
        read_some(buffer, limit, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_written;
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
std::size_t
stream<NextLayer, deflateSupported>::
read_some(
    DynamicBuffer& buffer,
    std::size_t limit,
    error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    using beast::detail::clamp;
    if(! limit)
        limit = (std::numeric_limits<std::size_t>::max)();
    auto const size =
        clamp(read_size_hint(buffer), limit);
    BOOST_ASSERT(size > 0);
    auto mb = beast::detail::dynamic_buffer_prepare(
        buffer, size, ec, error::buffer_overflow);
    if(impl_->check_stop_now(ec))
        return 0;
    auto const bytes_written = read_some(*mb, ec);
    buffer.commit(bytes_written);
    return bytes_written;
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer, class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
stream<NextLayer, deflateSupported>::
async_read_some(
    DynamicBuffer& buffer,
    std::size_t limit,
    ReadHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            run_read_op{},
            handler,
            impl_,
            &buffer,
            limit,
            true);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class MutableBufferSequence>
std::size_t
stream<NextLayer, deflateSupported>::
read_some(
    MutableBufferSequence const& buffers)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    error_code ec;
    auto const bytes_written = read_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_written;
}

template<class NextLayer, bool deflateSupported>
template<class MutableBufferSequence>
std::size_t
stream<NextLayer, deflateSupported>::
read_some(
    MutableBufferSequence const& buffers,
    error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    using beast::detail::clamp;
    auto& impl = *impl_;
    close_code code{};
    std::size_t bytes_written = 0;
    ec = {};
    // Make sure the stream is open
    if(impl.check_stop_now(ec))
        return bytes_written;
loop:
    // See if we need to read a frame header. This
    // condition is structured to give the decompressor
    // a chance to emit the final empty deflate block
    //
    if(impl.rd_remain == 0 && (
        ! impl.rd_fh.fin || impl.rd_done))
    {
        // Read frame header
        error_code result;
        while(! impl.parse_fh(impl.rd_fh, impl.rd_buf, result))
        {
            if(result)
            {
                // _Fail the WebSocket Connection_
                if(result == error::message_too_big)
                    code = close_code::too_big;
                else
                    code = close_code::protocol_error;
                do_fail(code, result, ec);
                return bytes_written;
            }
            auto const bytes_transferred =
                impl.stream().read_some(
                    impl.rd_buf.prepare(read_size(
                        impl.rd_buf, impl.rd_buf.max_size())),
                    ec);
            impl.rd_buf.commit(bytes_transferred);
            if(impl.check_stop_now(ec))
                return bytes_written;
        }
        // Immediately apply the mask to the portion
        // of the buffer holding payload data.
        if(impl.rd_fh.len > 0 && impl.rd_fh.mask)
            detail::mask_inplace(buffers_prefix(
                clamp(impl.rd_fh.len), impl.rd_buf.data()),
                    impl.rd_key);
        if(detail::is_control(impl.rd_fh.op))
        {
            // Get control frame payload
            auto const b = buffers_prefix(
                clamp(impl.rd_fh.len), impl.rd_buf.data());
            auto const len = buffer_bytes(b);
            BOOST_ASSERT(len == impl.rd_fh.len);

            // Clear this otherwise the next
            // frame will be considered final.
            impl.rd_fh.fin = false;

            // Handle ping frame
            if(impl.rd_fh.op == detail::opcode::ping)
            {
                ping_data payload;
                detail::read_ping(payload, b);
                impl.rd_buf.consume(len);
                if(impl.wr_close)
                {
                    // Ignore ping when closing
                    goto loop;
                }
                if(impl.ctrl_cb)
                    impl.ctrl_cb(frame_type::ping, payload);
                detail::frame_buffer fb;
                impl.template write_ping<flat_static_buffer_base>(fb,
                    detail::opcode::pong, payload);
                net::write(impl.stream(), fb.data(), ec);
                if(impl.check_stop_now(ec))
                    return bytes_written;
                goto loop;
            }
            // Handle pong frame
            if(impl.rd_fh.op == detail::opcode::pong)
            {
                ping_data payload;
                detail::read_ping(payload, b);
                impl.rd_buf.consume(len);
                if(impl.ctrl_cb)
                    impl.ctrl_cb(frame_type::pong, payload);
                goto loop;
            }
            // Handle close frame
            BOOST_ASSERT(impl.rd_fh.op == detail::opcode::close);
            {
                BOOST_ASSERT(! impl.rd_close);
                impl.rd_close = true;
                close_reason cr;
                detail::read_close(cr, b, result);
                if(result)
                {
                    // _Fail the WebSocket Connection_
                    do_fail(close_code::protocol_error,
                        result, ec);
                    return bytes_written;
                }
                impl.cr = cr;
                impl.rd_buf.consume(len);
                if(impl.ctrl_cb)
                    impl.ctrl_cb(frame_type::close, impl.cr.reason);
                BOOST_ASSERT(! impl.wr_close);
                // _Start the WebSocket Closing Handshake_
                do_fail(
                    cr.code == close_code::none ?
                        close_code::normal :
                        static_cast<close_code>(cr.code),
                    error::closed, ec);
                return bytes_written;
            }
        }
        if(impl.rd_fh.len == 0 && ! impl.rd_fh.fin)
        {
            // Empty non-final frame
            goto loop;
        }
        impl.rd_done = false;
    }
    else
    {
        ec = {};
    }
    if(! impl.rd_deflated())
    {
        if(impl.rd_remain > 0)
        {
            if(impl.rd_buf.size() == 0 && impl.rd_buf.max_size() >
                (std::min)(clamp(impl.rd_remain),
                    buffer_bytes(buffers)))
            {
                // Fill the read buffer first, otherwise we
                // get fewer bytes at the cost of one I/O.
                impl.rd_buf.commit(impl.stream().read_some(
                    impl.rd_buf.prepare(read_size(impl.rd_buf,
                        impl.rd_buf.max_size())), ec));
                if(impl.check_stop_now(ec))
                    return bytes_written;
                if(impl.rd_fh.mask)
                    detail::mask_inplace(
                        buffers_prefix(clamp(impl.rd_remain),
                            impl.rd_buf.data()), impl.rd_key);
            }
            if(impl.rd_buf.size() > 0)
            {
                // Copy from the read buffer.
                // The mask was already applied.
                auto const bytes_transferred = net::buffer_copy(
                    buffers, impl.rd_buf.data(),
                        clamp(impl.rd_remain));
                auto const mb = buffers_prefix(
                    bytes_transferred, buffers);
                impl.rd_remain -= bytes_transferred;
                if(impl.rd_op == detail::opcode::text)
                {
                    if(! impl.rd_utf8.write(mb) ||
                        (impl.rd_remain == 0 && impl.rd_fh.fin &&
                            ! impl.rd_utf8.finish()))
                    {
                        // _Fail the WebSocket Connection_
                        do_fail(close_code::bad_payload,
                            error::bad_frame_payload, ec);
                        return bytes_written;
                    }
                }
                bytes_written += bytes_transferred;
                impl.rd_size += bytes_transferred;
                impl.rd_buf.consume(bytes_transferred);
            }
            else
            {
                // Read into caller's buffer
                BOOST_ASSERT(impl.rd_remain > 0);
                BOOST_ASSERT(buffer_bytes(buffers) > 0);
                BOOST_ASSERT(buffer_bytes(buffers_prefix(
                    clamp(impl.rd_remain), buffers)) > 0);
                auto const bytes_transferred =
                    impl.stream().read_some(buffers_prefix(
                        clamp(impl.rd_remain), buffers), ec);
                // VFALCO What if some bytes were written?
                if(impl.check_stop_now(ec))
                    return bytes_written;
                BOOST_ASSERT(bytes_transferred > 0);
                auto const mb = buffers_prefix(
                    bytes_transferred, buffers);
                impl.rd_remain -= bytes_transferred;
                if(impl.rd_fh.mask)
                    detail::mask_inplace(mb, impl.rd_key);
                if(impl.rd_op == detail::opcode::text)
                {
                    if(! impl.rd_utf8.write(mb) ||
                        (impl.rd_remain == 0 && impl.rd_fh.fin &&
                            ! impl.rd_utf8.finish()))
                    {
                        // _Fail the WebSocket Connection_
                        do_fail(close_code::bad_payload,
                            error::bad_frame_payload, ec);
                        return bytes_written;
                    }
                }
                bytes_written += bytes_transferred;
                impl.rd_size += bytes_transferred;
            }
        }
        BOOST_ASSERT( ! impl.rd_done );
        if( impl.rd_remain == 0 && impl.rd_fh.fin )
            impl.rd_done = true;
    }
    else
    {
        // Read compressed message frame payload:
        // inflate even if rd_fh_.len == 0, otherwise we
        // never emit the end-of-stream deflate block.
        //
        bool did_read = false;
        buffers_suffix<MutableBufferSequence> cb(buffers);
        while(buffer_bytes(cb) > 0)
        {
            zlib::z_params zs;
            {
                auto const out = beast::buffers_front(cb);
                zs.next_out = out.data();
                zs.avail_out = out.size();
                BOOST_ASSERT(zs.avail_out > 0);
            }
            if(impl.rd_remain > 0)
            {
                if(impl.rd_buf.size() > 0)
                {
                    // use what's there
                    auto const in = buffers_prefix(
                        clamp(impl.rd_remain), beast::buffers_front(
                            impl.rd_buf.data()));
                    zs.avail_in = in.size();
                    zs.next_in = in.data();
                }
                else if(! did_read)
                {
                    // read new
                    auto const bytes_transferred =
                        impl.stream().read_some(
                            impl.rd_buf.prepare(read_size(
                                impl.rd_buf, impl.rd_buf.max_size())),
                            ec);
                    if(impl.check_stop_now(ec))
                        return bytes_written;
                    BOOST_ASSERT(bytes_transferred > 0);
                    impl.rd_buf.commit(bytes_transferred);
                    if(impl.rd_fh.mask)
                        detail::mask_inplace(
                            buffers_prefix(clamp(impl.rd_remain),
                                impl.rd_buf.data()), impl.rd_key);
                    auto const in = buffers_prefix(
                        clamp(impl.rd_remain), buffers_front(
                            impl.rd_buf.data()));
                    zs.avail_in = in.size();
                    zs.next_in = in.data();
                    did_read = true;
                }
                else
                {
                    break;
                }
            }
            else if(impl.rd_fh.fin)
            {
                // append the empty block codes
                static std::uint8_t constexpr
                    empty_block[4] = {
                        0x00, 0x00, 0xff, 0xff };
                zs.next_in = empty_block;
                zs.avail_in = sizeof(empty_block);
                impl.inflate(zs, zlib::Flush::sync, ec);
                if(! ec)
                {
                    // https://github.com/madler/zlib/issues/280
                    if(zs.total_out > 0)
                        ec = error::partial_deflate_block;
                }
                if(impl.check_stop_now(ec))
                    return bytes_written;
                impl.do_context_takeover_read(impl.role);
                impl.rd_done = true;
                break;
            }
            else
            {
                break;
            }
            impl.inflate(zs, zlib::Flush::sync, ec);
            if(impl.check_stop_now(ec))
                return bytes_written;
            if(impl.rd_msg_max && beast::detail::sum_exceeds(
                impl.rd_size, zs.total_out, impl.rd_msg_max))
            {
                do_fail(close_code::too_big,
                    error::message_too_big, ec);
                return bytes_written;
            }
            cb.consume(zs.total_out);
            impl.rd_size += zs.total_out;
            impl.rd_remain -= zs.total_in;
            impl.rd_buf.consume(zs.total_in);
            bytes_written += zs.total_out;
        }
        if(impl.rd_op == detail::opcode::text)
        {
            // check utf8
            if(! impl.rd_utf8.write(beast::buffers_prefix(
                bytes_written, buffers)) || (
                    impl.rd_done && ! impl.rd_utf8.finish()))
            {
                // _Fail the WebSocket Connection_
                do_fail(close_code::bad_payload,
                    error::bad_frame_payload, ec);
                return bytes_written;
            }
        }
    }
    return bytes_written;
}

template<class NextLayer, bool deflateSupported>
template<class MutableBufferSequence, class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
stream<NextLayer, deflateSupported>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            run_read_some_op{},
            handler,
            impl_,
            buffers);
}

} // websocket
} // beast
} // boost

#endif

/* read.hpp
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
*/