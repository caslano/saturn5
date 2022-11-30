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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_read_some"));

                    impl.op_r_rd.emplace(std::move(*this));
                }
                impl.rd_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_read_some"));

                    net::post(std::move(*this));
                }
                BOOST_ASSERT(impl.rd_block.is_locked(this));

                BOOST_ASSERT(!ec);
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
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "websocket::async_read_some"));

                        impl.stream().async_read_some(
                            impl.rd_buf.prepare(read_size(
                                impl.rd_buf, impl.rd_buf.max_size())),
                                    std::move(*this));
                    }
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
                                {
                                    BOOST_ASIO_HANDLER_LOCATION((
                                        __FILE__, __LINE__,
                                        "websocket::async_read_some"));

                                    net::post(std::move(*this));
                                }
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
                            {
                                BOOST_ASIO_HANDLER_LOCATION((
                                    __FILE__, __LINE__,
                                    "websocket::async_read_some"));

                                impl.op_rd.emplace(std::move(*this));
                            }
                            impl.wr_block.lock(this);
                            BOOST_ASIO_CORO_YIELD
                            {
                                BOOST_ASIO_HANDLER_LOCATION((
                                    __FILE__, __LINE__,
                                    "websocket::async_read_some"));

                                net::post(std::move(*this));
                            }
                            BOOST_ASSERT(impl.wr_block.is_locked(this));
                            if(impl.check_stop_now(ec))
                                goto upcall;
                        }

                        // Send pong
                        BOOST_ASSERT(impl.wr_block.is_locked(this));
                        BOOST_ASIO_CORO_YIELD
                        {
                            BOOST_ASIO_HANDLER_LOCATION((
                                __FILE__, __LINE__,
                                "websocket::async_read_some"));

                            net::async_write(
                                impl.stream(), net::const_buffer(impl.rd_fb.data()),
                                beast::detail::bind_continuation(std::move(*this)));
                        }
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
                                {
                                    BOOST_ASIO_HANDLER_LOCATION((
                                        __FILE__, __LINE__,
                                        "websocket::async_read_some"));

                                    net::post(std::move(*this));
                                }
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
                                {
                                    BOOST_ASIO_HANDLER_LOCATION((
                                        __FILE__, __LINE__,
                                        "websocket::async_read_some"));

                                    net::post(std::move(*this));
                                }
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
                        {
                            BOOST_ASIO_HANDLER_LOCATION((
                                __FILE__, __LINE__,
                                "websocket::async_read_some"));

                            impl.stream().async_read_some(
                                impl.rd_buf.prepare(read_size(
                                    impl.rd_buf, impl.rd_buf.max_size())),
                                        std::move(*this));
                        }
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
                        {
                            BOOST_ASIO_HANDLER_LOCATION((
                                __FILE__, __LINE__,
                                "websocket::async_read_some"));

                            impl.stream().async_read_some(buffers_prefix(
                                clamp(impl.rd_remain), cb_), std::move(*this));
                        }
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
                        {
                            BOOST_ASIO_HANDLER_LOCATION((
                                __FILE__, __LINE__,
                                "websocket::async_read_some"));

                            impl.stream().async_read_some(
                                impl.rd_buf.prepare(read_size(
                                    impl.rd_buf, impl.rd_buf.max_size())),
                                        std::move(*this));
                        }
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
                    // boolean to track the end of the message.
                    bool fin = false;
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
                        static std::uint8_t constexpr
                            empty_block[4] = { 0x00, 0x00, 0xff, 0xff };
                        zs.next_in = empty_block;
                        zs.avail_in = sizeof(empty_block);
                        fin = true;
                    }
                    else
                    {
                        break;
                    }
                    impl.inflate(zs, zlib::Flush::sync, ec);
                    if(impl.check_stop_now(ec))
                        goto upcall;
                    if(fin && zs.total_out == 0) {
                        impl.do_context_takeover_read(impl.role);
                        impl.rd_done = true;
                        break;
                    }
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
                    if (! fin) {
                        impl.rd_remain -= zs.total_in;
                        impl.rd_buf.consume(zs.total_in);
                    }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_read_some"));

                    impl.op_rd.emplace(std::move(*this));
                }
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_read_some"));

                    net::post(std::move(*this));
                }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_read_some"));

                    net::async_write(impl.stream(), net::const_buffer(impl.rd_fb.data()),
                        beast::detail::bind_continuation(std::move(*this)));
                }
                BOOST_ASSERT(impl.wr_block.is_locked(this));
                if(impl.check_stop_now(ec))
                    goto upcall;
            }

            // Teardown
            using beast::websocket::async_teardown;
            BOOST_ASSERT(impl.wr_block.is_locked(this));
            BOOST_ASIO_CORO_YIELD
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_read_some"));

                async_teardown(impl.role, impl.stream(),
                    beast::detail::bind_continuation(std::move(*this)));
            }
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

                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_read"));

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
template<class DynamicBuffer, BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
template<class DynamicBuffer, BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
            // boolean to track the end of the message.
            bool fin = false;
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
                    empty_block[4] = { 0x00, 0x00, 0xff, 0xff };
                zs.next_in = empty_block;
                zs.avail_in = sizeof(empty_block);
                fin = true;
            }
            else
            {
                break;
            }
            impl.inflate(zs, zlib::Flush::sync, ec);
            if(impl.check_stop_now(ec))
                return bytes_written;
            if (fin && zs.total_out == 0) {
                impl.do_context_takeover_read(impl.role);
                impl.rd_done = true;
                break;
            }
            if(impl.rd_msg_max && beast::detail::sum_exceeds(
                impl.rd_size, zs.total_out, impl.rd_msg_max))
            {
                do_fail(close_code::too_big,
                    error::message_too_big, ec);
                return bytes_written;
            }
            cb.consume(zs.total_out);
            impl.rd_size += zs.total_out;
            if (! fin) {
                impl.rd_remain -= zs.total_in;
                impl.rd_buf.consume(zs.total_in);
            }
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
template<class MutableBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
+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
*/