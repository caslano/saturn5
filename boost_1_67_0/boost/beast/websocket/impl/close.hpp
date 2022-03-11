//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_CLOSE_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_CLOSE_HPP

#include <boost/beast/websocket/teardown.hpp>
#include <boost/beast/websocket/detail/mask.hpp>
#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/bind_continuation.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <boost/throw_exception.hpp>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

/*  Close the WebSocket Connection

    This composed operation sends the close frame if it hasn't already
    been sent, then reads and discards frames until receiving a close
    frame. Finally it invokes the teardown operation to shut down the
    underlying connection.
*/
template<class NextLayer, bool deflateSupported>
template<class Handler>
class stream<NextLayer, deflateSupported>::close_op
    : public beast::stable_async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    boost::weak_ptr<impl_type> wp_;
    error_code ev_;
    detail::frame_buffer& fb_;

public:
    static constexpr int id = 5; // for soft_mutex

    template<class Handler_>
    close_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        close_reason const& cr)
        : stable_async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , fb_(beast::allocate_stable<
            detail::frame_buffer>(*this))
    {
        // Serialize the close frame
        sp->template write_close<
            flat_static_buffer_base>(fb_, cr);
        (*this)({}, 0, false);
    }

    void
    operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true)
    {
        using beast::detail::clamp;
        auto sp = wp_.lock();
        if(! sp)
        {
            ec = net::error::operation_aborted;
            return this->complete(cont, ec);
        }
        auto& impl = *sp;
        BOOST_ASIO_CORO_REENTER(*this)
        {
            // Acquire the write lock
            if(! impl.wr_block.try_lock(this))
            {
                BOOST_ASIO_CORO_YIELD
                impl.op_close.emplace(std::move(*this));
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                net::post(std::move(*this));
                BOOST_ASSERT(impl.wr_block.is_locked(this));
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // Can't call close twice
            // TODO return a custom error code
            BOOST_ASSERT(! impl.wr_close);

            // Send close frame
            impl.wr_close = true;
            impl.change_status(status::closing);
            impl.update_timer(this->get_executor());
            BOOST_ASIO_CORO_YIELD
            net::async_write(impl.stream(), fb_.data(),
                beast::detail::bind_continuation(std::move(*this)));
            if(impl.check_stop_now(ec))
                goto upcall;

            if(impl.rd_close)
            {
                // This happens when the read_op gets a close frame
                // at the same time close_op is sending the close frame.
                // The read_op will be suspended on the write block.
                goto teardown;
            }

            // Acquire the read lock
            if(! impl.rd_block.try_lock(this))
            {
                BOOST_ASIO_CORO_YIELD
                impl.op_r_close.emplace(std::move(*this));
                impl.rd_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                net::post(std::move(*this));
                BOOST_ASSERT(impl.rd_block.is_locked(this));
                if(impl.check_stop_now(ec))
                    goto upcall;
                BOOST_ASSERT(! impl.rd_close);
            }

            // Read until a receiving a close frame
            // TODO There should be a timeout on this
            if(impl.rd_remain > 0)
                goto read_payload;
            for(;;)
            {
                // Read frame header
                while(! impl.parse_fh(
                    impl.rd_fh, impl.rd_buf, ev_))
                {
                    if(ev_)
                        goto teardown;
                    BOOST_ASIO_CORO_YIELD
                    impl.stream().async_read_some(
                        impl.rd_buf.prepare(read_size(
                            impl.rd_buf, impl.rd_buf.max_size())),
                        beast::detail::bind_continuation(std::move(*this)));
                    impl.rd_buf.commit(bytes_transferred);
                    if(impl.check_stop_now(ec))
                        goto upcall;
                }
                if(detail::is_control(impl.rd_fh.op))
                {
                    // Discard ping or pong frame
                    if(impl.rd_fh.op != detail::opcode::close)
                    {
                        impl.rd_buf.consume(clamp(impl.rd_fh.len));
                        continue;
                    }

                    // Process close frame
                    // TODO Should we invoke the control callback?
                    BOOST_ASSERT(! impl.rd_close);
                    impl.rd_close = true;
                    auto const mb = buffers_prefix(
                        clamp(impl.rd_fh.len),
                        impl.rd_buf.data());
                    if(impl.rd_fh.len > 0 && impl.rd_fh.mask)
                        detail::mask_inplace(mb, impl.rd_key);
                    detail::read_close(impl.cr, mb, ev_);
                    if(ev_)
                        goto teardown;
                    impl.rd_buf.consume(clamp(impl.rd_fh.len));
                    goto teardown;
                }

            read_payload:
                // Discard message frame
                while(impl.rd_buf.size() < impl.rd_remain)
                {
                    impl.rd_remain -= impl.rd_buf.size();
                    impl.rd_buf.consume(impl.rd_buf.size());
                    BOOST_ASIO_CORO_YIELD
                    impl.stream().async_read_some(
                        impl.rd_buf.prepare(read_size(
                            impl.rd_buf, impl.rd_buf.max_size())),
                        beast::detail::bind_continuation(std::move(*this)));
                    impl.rd_buf.commit(bytes_transferred);
                    if(impl.check_stop_now(ec))
                        goto upcall;
                }
                BOOST_ASSERT(impl.rd_buf.size() >= impl.rd_remain);
                impl.rd_buf.consume(clamp(impl.rd_remain));
                impl.rd_remain = 0;
            }

        teardown:
            // Teardown
            BOOST_ASSERT(impl.wr_block.is_locked(this));
            using beast::websocket::async_teardown;
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
                ec = ev_;
            if(ec)
                impl.change_status(status::failed);
            else
                impl.change_status(status::closed);
            impl.close();

        upcall:
            impl.wr_block.unlock(this);
            impl.rd_block.try_unlock(this)
                && impl.op_r_rd.maybe_invoke();
            impl.op_rd.maybe_invoke()
                || impl.op_idle_ping.maybe_invoke()
                || impl.op_ping.maybe_invoke()
                || impl.op_wr.maybe_invoke();
            this->complete(cont, ec);
        }
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_close_op
{
    template<class CloseHandler>
    void
    operator()(
        CloseHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        close_reason const& cr)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<CloseHandler,
                void(error_code)>::value,
            "CloseHandler type requirements not met");

        close_op<
            typename std::decay<CloseHandler>::type>(
                std::forward<CloseHandler>(h),
                sp,
                cr);
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
close(close_reason const& cr)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    error_code ec;
    close(cr, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
close(close_reason const& cr, error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    using beast::detail::clamp;
    auto& impl = *impl_;
    ec = {};
    if(impl.check_stop_now(ec))
        return;
    BOOST_ASSERT(! impl.rd_close);

    // Can't call close twice
    // TODO return a custom error code
    BOOST_ASSERT(! impl.wr_close);

    // Send close frame
    {
        impl.wr_close = true;
        impl.change_status(status::closing);
        detail::frame_buffer fb;
        impl.template write_close<flat_static_buffer_base>(fb, cr);
        net::write(impl.stream(), fb.data(), ec);
        if(impl.check_stop_now(ec))
            return;
    }

    // Read until a receiving a close frame
    error_code ev;
    if(impl.rd_remain > 0)
        goto read_payload;
    for(;;)
    {
        // Read frame header
        while(! impl.parse_fh(
            impl.rd_fh, impl.rd_buf, ev))
        {
            if(ev)
            {
                // Protocol violation
                return do_fail(close_code::none, ev, ec);
            }
            impl.rd_buf.commit(impl.stream().read_some(
                impl.rd_buf.prepare(read_size(
                    impl.rd_buf, impl.rd_buf.max_size())), ec));
            if(impl.check_stop_now(ec))
                return;
        }

        if(detail::is_control(impl.rd_fh.op))
        {
            // Discard ping/pong frame
            if(impl.rd_fh.op != detail::opcode::close)
            {
                impl.rd_buf.consume(clamp(impl.rd_fh.len));
                continue;
            }

            // Handle close frame
            // TODO Should we invoke the control callback?
            BOOST_ASSERT(! impl.rd_close);
            impl.rd_close = true;
            auto const mb = buffers_prefix(
                clamp(impl.rd_fh.len),
                impl.rd_buf.data());
            if(impl.rd_fh.len > 0 && impl.rd_fh.mask)
                detail::mask_inplace(mb, impl.rd_key);
            detail::read_close(impl.cr, mb, ev);
            if(ev)
            {
                // Protocol violation
                return do_fail(close_code::none, ev, ec);
            }
            impl.rd_buf.consume(clamp(impl.rd_fh.len));
            break;
        }

    read_payload:
        // Discard message frame
        while(impl.rd_buf.size() < impl.rd_remain)
        {
            impl.rd_remain -= impl.rd_buf.size();
            impl.rd_buf.consume(impl.rd_buf.size());
            impl.rd_buf.commit(
                impl.stream().read_some(
                    impl.rd_buf.prepare(
                        read_size(
                            impl.rd_buf,
                            impl.rd_buf.max_size())),
                    ec));
            if(impl.check_stop_now(ec))
                return;
        }
        BOOST_ASSERT(
            impl.rd_buf.size() >= impl.rd_remain);
        impl.rd_buf.consume(clamp(impl.rd_remain));
        impl.rd_remain = 0;
    }
    // _Close the WebSocket Connection_
    do_fail(close_code::none, error::closed, ec);
    if(ec == error::closed)
        ec = {};
}

template<class NextLayer, bool deflateSupported>
template<class CloseHandler>
BOOST_BEAST_ASYNC_RESULT1(CloseHandler)
stream<NextLayer, deflateSupported>::
async_close(close_reason const& cr, CloseHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    return net::async_initiate<
        CloseHandler,
        void(error_code)>(
            run_close_op{},
            handler,
            impl_,
            cr);
}

} // websocket
} // beast
} // boost

#endif

/* close.hpp
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
*/