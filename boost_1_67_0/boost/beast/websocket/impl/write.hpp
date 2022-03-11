//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_WRITE_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_WRITE_HPP

#include <boost/beast/websocket/detail/mask.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_range.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/bind_continuation.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/websocket/detail/frame.hpp>
#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

template<class NextLayer, bool deflateSupported>
template<class Handler, class Buffers>
class stream<NextLayer, deflateSupported>::write_some_op
    : public beast::async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    enum
    {
        do_nomask_nofrag,
        do_nomask_frag,
        do_mask_nofrag,
        do_mask_frag,
        do_deflate
    };

    boost::weak_ptr<impl_type> wp_;
    buffers_suffix<Buffers> cb_;
    detail::frame_header fh_;
    detail::prepared_key key_;
    std::size_t bytes_transferred_ = 0;
    std::size_t remain_;
    std::size_t in_;
    int how_;
    bool fin_;
    bool more_ = false; // for ubsan
    bool cont_ = false;

public:
    static constexpr int id = 2; // for soft_mutex

    template<class Handler_>
    write_some_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        bool fin,
        Buffers const& bs)
        : beast::async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , cb_(bs)
        , fin_(fin)
    {
        auto& impl = *sp;

        // Set up the outgoing frame header
        if(! impl.wr_cont)
        {
            impl.begin_msg();
            fh_.rsv1 = impl.wr_compress;
        }
        else
        {
            fh_.rsv1 = false;
        }
        fh_.rsv2 = false;
        fh_.rsv3 = false;
        fh_.op = impl.wr_cont ?
            detail::opcode::cont : impl.wr_opcode;
        fh_.mask =
            impl.role == role_type::client;

        // Choose a write algorithm
        if(impl.wr_compress)
        {
            how_ = do_deflate;
        }
        else if(! fh_.mask)
        {
            if(! impl.wr_frag)
            {
                how_ = do_nomask_nofrag;
            }
            else
            {
                BOOST_ASSERT(impl.wr_buf_size != 0);
                remain_ = buffer_bytes(cb_);
                if(remain_ > impl.wr_buf_size)
                    how_ = do_nomask_frag;
                else
                    how_ = do_nomask_nofrag;
            }
        }
        else
        {
            if(! impl.wr_frag)
            {
                how_ = do_mask_nofrag;
            }
            else
            {
                BOOST_ASSERT(impl.wr_buf_size != 0);
                remain_ = buffer_bytes(cb_);
                if(remain_ > impl.wr_buf_size)
                    how_ = do_mask_frag;
                else
                    how_ = do_mask_nofrag;
            }
        }
        (*this)({}, 0, false);
    }

    void operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true);
};

template<class NextLayer, bool deflateSupported>
template<class Buffers, class Handler>
void
stream<NextLayer, deflateSupported>::
write_some_op<Buffers, Handler>::
operator()(
    error_code ec,
    std::size_t bytes_transferred,
    bool cont)
{
    using beast::detail::clamp;
    std::size_t n;
    net::mutable_buffer b;
    auto sp = wp_.lock();
    if(! sp)
    {
        ec = net::error::operation_aborted;
        bytes_transferred_ = 0;
        return this->complete(cont, ec, bytes_transferred_);
    }
    auto& impl = *sp;
    BOOST_ASIO_CORO_REENTER(*this)
    {
        // Acquire the write lock
        if(! impl.wr_block.try_lock(this))
        {
        do_suspend:
            BOOST_ASIO_CORO_YIELD
            impl.op_wr.emplace(std::move(*this));
            impl.wr_block.lock(this);
            BOOST_ASIO_CORO_YIELD
            net::post(std::move(*this));
            BOOST_ASSERT(impl.wr_block.is_locked(this));
        }
        if(impl.check_stop_now(ec))
            goto upcall;

        //------------------------------------------------------------------

        if(how_ == do_nomask_nofrag)
        {
            // send a single frame
            fh_.fin = fin_;
            fh_.len = buffer_bytes(cb_);
            impl.wr_fb.clear();
            detail::write<flat_static_buffer_base>(
                impl.wr_fb, fh_);
            impl.wr_cont = ! fin_;
            BOOST_ASIO_CORO_YIELD
            net::async_write(impl.stream(),
                buffers_cat(impl.wr_fb.data(), cb_),
                    beast::detail::bind_continuation(std::move(*this)));
            bytes_transferred_ += clamp(fh_.len);
            if(impl.check_stop_now(ec))
                goto upcall;
            goto upcall;
        }

        //------------------------------------------------------------------

        if(how_ == do_nomask_frag)
        {
            // send multiple frames
            for(;;)
            {
                n = clamp(remain_, impl.wr_buf_size);
                fh_.len = n;
                remain_ -= n;
                fh_.fin = fin_ ? remain_ == 0 : false;
                impl.wr_fb.clear();
                detail::write<flat_static_buffer_base>(
                    impl.wr_fb, fh_);
                impl.wr_cont = ! fin_;
                // Send frame
                BOOST_ASIO_CORO_YIELD
                net::async_write(impl.stream(), buffers_cat(
                    impl.wr_fb.data(),
                    buffers_prefix(clamp(fh_.len), cb_)),
                        beast::detail::bind_continuation(std::move(*this)));
                n = clamp(fh_.len); // restore `n` on yield
                bytes_transferred_ += n;
                if(impl.check_stop_now(ec))
                    goto upcall;
                if(remain_ == 0)
                    break;
                cb_.consume(n);
                fh_.op = detail::opcode::cont;

                // Give up the write lock in between each frame
                // so that outgoing control frames might be sent.
                impl.wr_block.unlock(this);
                if( impl.op_close.maybe_invoke()
                    || impl.op_idle_ping.maybe_invoke()
                    || impl.op_rd.maybe_invoke()
                    || impl.op_ping.maybe_invoke())
                {
                    BOOST_ASSERT(impl.wr_block.is_locked());
                    goto do_suspend;
                }
                impl.wr_block.lock(this);
            }
            goto upcall;
        }

        //------------------------------------------------------------------

        if(how_ == do_mask_nofrag)
        {
            // send a single frame using multiple writes
            remain_ = beast::buffer_bytes(cb_);
            fh_.fin = fin_;
            fh_.len = remain_;
            fh_.key = impl.create_mask();
            detail::prepare_key(key_, fh_.key);
            impl.wr_fb.clear();
            detail::write<flat_static_buffer_base>(
                impl.wr_fb, fh_);
            n = clamp(remain_, impl.wr_buf_size);
            net::buffer_copy(net::buffer(
                impl.wr_buf.get(), n), cb_);
            detail::mask_inplace(net::buffer(
                impl.wr_buf.get(), n), key_);
            remain_ -= n;
            impl.wr_cont = ! fin_;
            // write frame header and some payload
            BOOST_ASIO_CORO_YIELD
            net::async_write(impl.stream(), buffers_cat(
                impl.wr_fb.data(),
                net::buffer(impl.wr_buf.get(), n)),
                    beast::detail::bind_continuation(std::move(*this)));
            // VFALCO What about consuming the buffer on error?
            bytes_transferred_ +=
                bytes_transferred - impl.wr_fb.size();
            if(impl.check_stop_now(ec))
                goto upcall;
            while(remain_ > 0)
            {
                cb_.consume(impl.wr_buf_size);
                n = clamp(remain_, impl.wr_buf_size);
                net::buffer_copy(net::buffer(
                    impl.wr_buf.get(), n), cb_);
                detail::mask_inplace(net::buffer(
                    impl.wr_buf.get(), n), key_);
                remain_ -= n;
                // write more payload
                BOOST_ASIO_CORO_YIELD
                net::async_write(impl.stream(),
                    net::buffer(impl.wr_buf.get(), n),
                        beast::detail::bind_continuation(std::move(*this)));
                bytes_transferred_ += bytes_transferred;
                if(impl.check_stop_now(ec))
                    goto upcall;
            }
            goto upcall;
        }

        //------------------------------------------------------------------

        if(how_ == do_mask_frag)
        {
            // send multiple frames
            for(;;)
            {
                n = clamp(remain_, impl.wr_buf_size);
                remain_ -= n;
                fh_.len = n;
                fh_.key = impl.create_mask();
                fh_.fin = fin_ ? remain_ == 0 : false;
                detail::prepare_key(key_, fh_.key);
                net::buffer_copy(net::buffer(
                    impl.wr_buf.get(), n), cb_);
                detail::mask_inplace(net::buffer(
                    impl.wr_buf.get(), n), key_);
                impl.wr_fb.clear();
                detail::write<flat_static_buffer_base>(
                    impl.wr_fb, fh_);
                impl.wr_cont = ! fin_;
                // Send frame
                BOOST_ASIO_CORO_YIELD
                net::async_write(impl.stream(), buffers_cat(
                    impl.wr_fb.data(),
                    net::buffer(impl.wr_buf.get(), n)),
                        beast::detail::bind_continuation(std::move(*this)));
                n = bytes_transferred - impl.wr_fb.size();
                bytes_transferred_ += n;
                if(impl.check_stop_now(ec))
                    goto upcall;
                if(remain_ == 0)
                    break;
                cb_.consume(n);
                fh_.op = detail::opcode::cont;
                // Give up the write lock in between each frame
                // so that outgoing control frames might be sent.
                impl.wr_block.unlock(this);
                if( impl.op_close.maybe_invoke()
                    || impl.op_idle_ping.maybe_invoke()
                    || impl.op_rd.maybe_invoke()
                    || impl.op_ping.maybe_invoke())
                {
                    BOOST_ASSERT(impl.wr_block.is_locked());
                    goto do_suspend;
                }
                impl.wr_block.lock(this);
            }
            goto upcall;
        }

        //------------------------------------------------------------------

        if(how_ == do_deflate)
        {
            // send compressed frames
            for(;;)
            {
                b = net::buffer(impl.wr_buf.get(),
                    impl.wr_buf_size);
                more_ = impl.deflate(b, cb_, fin_, in_, ec);
                if(impl.check_stop_now(ec))
                    goto upcall;
                n = buffer_bytes(b);
                if(n == 0)
                {
                    // The input was consumed, but there is
                    // no output due to compression latency.
                    BOOST_ASSERT(! fin_);
                    BOOST_ASSERT(buffer_bytes(cb_) == 0);
                    goto upcall;
                }
                if(fh_.mask)
                {
                    fh_.key = impl.create_mask();
                    detail::prepared_key key;
                    detail::prepare_key(key, fh_.key);
                    detail::mask_inplace(b, key);
                }
                fh_.fin = ! more_;
                fh_.len = n;
                impl.wr_fb.clear();
                detail::write<
                    flat_static_buffer_base>(impl.wr_fb, fh_);
                impl.wr_cont = ! fin_;
                // Send frame
                BOOST_ASIO_CORO_YIELD
                net::async_write(impl.stream(), buffers_cat(
                    impl.wr_fb.data(), b),
                        beast::detail::bind_continuation(std::move(*this)));
                bytes_transferred_ += in_;
                if(impl.check_stop_now(ec))
                    goto upcall;
                if(more_)
                {
                    fh_.op = detail::opcode::cont;
                    fh_.rsv1 = false;
                    // Give up the write lock in between each frame
                    // so that outgoing control frames might be sent.
                    impl.wr_block.unlock(this);
                    if( impl.op_close.maybe_invoke()
                        || impl.op_idle_ping.maybe_invoke()
                        || impl.op_rd.maybe_invoke()
                        || impl.op_ping.maybe_invoke())
                    {
                        BOOST_ASSERT(impl.wr_block.is_locked());
                        goto do_suspend;
                    }
                    impl.wr_block.lock(this);
                }
                else
                {
                    if(fh_.fin)
                        impl.do_context_takeover_write(impl.role);
                    goto upcall;
                }
            }
        }

    //--------------------------------------------------------------------------

    upcall:
        impl.wr_block.unlock(this);
        impl.op_close.maybe_invoke()
            || impl.op_idle_ping.maybe_invoke()
            || impl.op_rd.maybe_invoke()
            || impl.op_ping.maybe_invoke();
        this->complete(cont, ec, bytes_transferred_);
    }
}

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_write_some_op
{
    template<
        class WriteHandler,
        class ConstBufferSequence>
    void
    operator()(
        WriteHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        bool fin,
        ConstBufferSequence const& b)
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
            ConstBufferSequence>(
                std::forward<WriteHandler>(h),
                sp,
                fin,
                b);
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence>
std::size_t
stream<NextLayer, deflateSupported>::
write_some(bool fin, ConstBufferSequence const& buffers)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write_some(fin, buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence>
std::size_t
stream<NextLayer, deflateSupported>::
write_some(bool fin,
    ConstBufferSequence const& buffers, error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    using beast::detail::clamp;
    auto& impl = *impl_;
    std::size_t bytes_transferred = 0;
    ec = {};
    if(impl.check_stop_now(ec))
        return bytes_transferred;
    detail::frame_header fh;
    if(! impl.wr_cont)
    {
        impl.begin_msg();
        fh.rsv1 = impl.wr_compress;
    }
    else
    {
        fh.rsv1 = false;
    }
    fh.rsv2 = false;
    fh.rsv3 = false;
    fh.op = impl.wr_cont ?
        detail::opcode::cont : impl.wr_opcode;
    fh.mask = impl.role == role_type::client;
    auto remain = buffer_bytes(buffers);
    if(impl.wr_compress)
    {

        buffers_suffix<
            ConstBufferSequence> cb(buffers);
        for(;;)
        {
            auto b = net::buffer(
                impl.wr_buf.get(), impl.wr_buf_size);
            auto const more = impl.deflate(
                b, cb, fin, bytes_transferred, ec);
            if(impl.check_stop_now(ec))
                return bytes_transferred;
            auto const n = buffer_bytes(b);
            if(n == 0)
            {
                // The input was consumed, but there
                // is no output due to compression
                // latency.
                BOOST_ASSERT(! fin);
                BOOST_ASSERT(buffer_bytes(cb) == 0);
                fh.fin = false;
                break;
            }
            if(fh.mask)
            {
                fh.key = this->impl_->create_mask();
                detail::prepared_key key;
                detail::prepare_key(key, fh.key);
                detail::mask_inplace(b, key);
            }
            fh.fin = ! more;
            fh.len = n;
            detail::fh_buffer fh_buf;
            detail::write<
                flat_static_buffer_base>(fh_buf, fh);
            impl.wr_cont = ! fin;
            net::write(impl.stream(),
                buffers_cat(fh_buf.data(), b), ec);
            if(impl.check_stop_now(ec))
                return bytes_transferred;
            if(! more)
                break;
            fh.op = detail::opcode::cont;
            fh.rsv1 = false;
        }
        if(fh.fin)
            impl.do_context_takeover_write(impl.role);
    }
    else if(! fh.mask)
    {
        if(! impl.wr_frag)
        {
            // no mask, no autofrag
            fh.fin = fin;
            fh.len = remain;
            detail::fh_buffer fh_buf;
            detail::write<
                flat_static_buffer_base>(fh_buf, fh);
            impl.wr_cont = ! fin;
            net::write(impl.stream(),
                buffers_cat(fh_buf.data(), buffers), ec);
            if(impl.check_stop_now(ec))
                return bytes_transferred;
            bytes_transferred += remain;
        }
        else
        {
            // no mask, autofrag
            BOOST_ASSERT(impl.wr_buf_size != 0);
            buffers_suffix<
                ConstBufferSequence> cb{buffers};
            for(;;)
            {
                auto const n = clamp(remain, impl.wr_buf_size);
                remain -= n;
                fh.len = n;
                fh.fin = fin ? remain == 0 : false;
                detail::fh_buffer fh_buf;
                detail::write<
                    flat_static_buffer_base>(fh_buf, fh);
                impl.wr_cont = ! fin;
                net::write(impl.stream(),
                    beast::buffers_cat(fh_buf.data(),
                        beast::buffers_prefix(n, cb)), ec);
                bytes_transferred += n;
                if(impl.check_stop_now(ec))
                    return bytes_transferred;
                if(remain == 0)
                    break;
                fh.op = detail::opcode::cont;
                cb.consume(n);
            }
        }
    }
    else if(! impl.wr_frag)
    {
        // mask, no autofrag
        fh.fin = fin;
        fh.len = remain;
        fh.key = this->impl_->create_mask();
        detail::prepared_key key;
        detail::prepare_key(key, fh.key);
        detail::fh_buffer fh_buf;
        detail::write<
            flat_static_buffer_base>(fh_buf, fh);
        buffers_suffix<
            ConstBufferSequence> cb{buffers};
        {
            auto const n =
                clamp(remain, impl.wr_buf_size);
            auto const b =
                net::buffer(impl.wr_buf.get(), n);
            net::buffer_copy(b, cb);
            cb.consume(n);
            remain -= n;
            detail::mask_inplace(b, key);
            impl.wr_cont = ! fin;
            net::write(impl.stream(),
                buffers_cat(fh_buf.data(), b), ec);
            bytes_transferred += n;
            if(impl.check_stop_now(ec))
                return bytes_transferred;
        }
        while(remain > 0)
        {
            auto const n =
                clamp(remain, impl.wr_buf_size);
            auto const b =
                net::buffer(impl.wr_buf.get(), n);
            net::buffer_copy(b, cb);
            cb.consume(n);
            remain -= n;
            detail::mask_inplace(b, key);
            net::write(impl.stream(), b, ec);
            bytes_transferred += n;
            if(impl.check_stop_now(ec))
                return bytes_transferred;
        }
    }
    else
    {
        // mask, autofrag
        BOOST_ASSERT(impl.wr_buf_size != 0);
        buffers_suffix<
            ConstBufferSequence> cb(buffers);
        for(;;)
        {
            fh.key = this->impl_->create_mask();
            detail::prepared_key key;
            detail::prepare_key(key, fh.key);
            auto const n =
                clamp(remain, impl.wr_buf_size);
            auto const b =
                net::buffer(impl.wr_buf.get(), n);
            net::buffer_copy(b, cb);
            detail::mask_inplace(b, key);
            fh.len = n;
            remain -= n;
            fh.fin = fin ? remain == 0 : false;
            impl.wr_cont = ! fh.fin;
            detail::fh_buffer fh_buf;
            detail::write<
                flat_static_buffer_base>(fh_buf, fh);
            net::write(impl.stream(),
                buffers_cat(fh_buf.data(), b), ec);
            bytes_transferred += n;
            if(impl.check_stop_now(ec))
                return bytes_transferred;
            if(remain == 0)
                break;
            fh.op = detail::opcode::cont;
            cb.consume(n);
        }
    }
    return bytes_transferred;
}

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence, class WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
stream<NextLayer, deflateSupported>::
async_write_some(bool fin,
    ConstBufferSequence const& bs, WriteHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            run_write_some_op{},
            handler,
            impl_,
            fin,
            bs);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence>
std::size_t
stream<NextLayer, deflateSupported>::
write(ConstBufferSequence const& buffers)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    error_code ec;
    auto const bytes_transferred = write(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence>
std::size_t
stream<NextLayer, deflateSupported>::
write(ConstBufferSequence const& buffers, error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    return write_some(true, buffers, ec);
}

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence, class WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
stream<NextLayer, deflateSupported>::
async_write(
    ConstBufferSequence const& bs, WriteHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code, std::size_t)>(
            run_write_some_op{},
            handler,
            impl_,
            true,
            bs);
}

} // websocket
} // beast
} // boost

#endif

/* write.hpp
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
*/