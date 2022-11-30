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
template<class Handler, class Buffers>
void
stream<NextLayer, deflateSupported>::
write_some_op<Handler, Buffers>::
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    fin_ ?
                        "websocket::async_write" :
                        "websocket::async_write_some"
                    ));

                impl.op_wr.emplace(std::move(*this));
            }
            impl.wr_block.lock(this);
            BOOST_ASIO_CORO_YIELD
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    fin_ ?
                        "websocket::async_write" :
                        "websocket::async_write_some"
                    ));

                net::post(std::move(*this));
            }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    fin_ ?
                        "websocket::async_write" :
                        "websocket::async_write_some"
                    ));

                net::async_write(impl.stream(),
                    buffers_cat(
                        net::const_buffer(impl.wr_fb.data()),
                        net::const_buffer(0, 0),
                        cb_,
                        buffers_prefix(0, cb_)
                        ),
                        beast::detail::bind_continuation(std::move(*this)));
            }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        fin_ ?
                            "websocket::async_write" :
                            "websocket::async_write_some"
                        ));

                    buffers_suffix<Buffers> empty_cb(cb_);
                    empty_cb.consume(~std::size_t(0));

                    net::async_write(impl.stream(),
                        buffers_cat(
                            net::const_buffer(impl.wr_fb.data()),
                            net::const_buffer(0, 0),
                            empty_cb,
                            buffers_prefix(clamp(fh_.len), cb_)
                            ),
                            beast::detail::bind_continuation(std::move(*this)));
                }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    fin_ ?
                        "websocket::async_write" :
                        "websocket::async_write_some"
                    ));

                buffers_suffix<Buffers> empty_cb(cb_);
                empty_cb.consume(~std::size_t(0));

                net::async_write(impl.stream(),
                    buffers_cat(
                        net::const_buffer(impl.wr_fb.data()),
                        net::const_buffer(net::buffer(impl.wr_buf.get(), n)),
                        empty_cb,
                        buffers_prefix(0, empty_cb)
                        ),
                        beast::detail::bind_continuation(std::move(*this)));
            }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        fin_ ?
                            "websocket::async_write" :
                            "websocket::async_write_some"
                        ));

                    buffers_suffix<Buffers> empty_cb(cb_);
                    empty_cb.consume(~std::size_t(0));

                    net::async_write(impl.stream(),
                        buffers_cat(
                            net::const_buffer(0, 0),
                            net::const_buffer(net::buffer(impl.wr_buf.get(), n)),
                            empty_cb,
                            buffers_prefix(0, empty_cb)
                            ),
                            beast::detail::bind_continuation(std::move(*this)));
                }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        fin_ ?
                            "websocket::async_write" :
                            "websocket::async_write_some"
                        ));

                    buffers_suffix<Buffers> empty_cb(cb_);
                    empty_cb.consume(~std::size_t(0));

                    net::async_write(impl.stream(),
                        buffers_cat(
                            net::const_buffer(impl.wr_fb.data()),
                            net::const_buffer(net::buffer(impl.wr_buf.get(), n)),
                            empty_cb,
                            buffers_prefix(0, empty_cb)
                            ),
                            beast::detail::bind_continuation(std::move(*this)));
                }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        fin_ ?
                            "websocket::async_write" :
                            "websocket::async_write_some"
                        ));

                    buffers_suffix<Buffers> empty_cb(cb_);
                    empty_cb.consume(~std::size_t(0));

                    net::async_write(impl.stream(),
                        buffers_cat(
                            net::const_buffer(impl.wr_fb.data()),
                            net::const_buffer(b),
                            empty_cb,
                            buffers_prefix(0, empty_cb)
                            ),
                            beast::detail::bind_continuation(std::move(*this)));
                }
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
template<class ConstBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
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
template<class ConstBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
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