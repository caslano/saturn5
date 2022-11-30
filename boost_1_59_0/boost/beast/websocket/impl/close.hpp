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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_close"));

                    impl.op_close.emplace(std::move(*this));
                }
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_close"));

                    net::post(std::move(*this));
                }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_close"));

                net::async_write(impl.stream(), fb_.data(),
                    beast::detail::bind_continuation(std::move(*this)));
            }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_close"));

                    impl.op_r_close.emplace(std::move(*this));
                }
                impl.rd_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_close"));

                    net::post(std::move(*this));
                }
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
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "websocket::async_close"));

                        impl.stream().async_read_some(
                            impl.rd_buf.prepare(read_size(
                                impl.rd_buf, impl.rd_buf.max_size())),
                            beast::detail::bind_continuation(std::move(*this)));
                    }
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
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "websocket::async_close"));

                        impl.stream().async_read_some(
                            impl.rd_buf.prepare(read_size(
                                impl.rd_buf, impl.rd_buf.max_size())),
                            beast::detail::bind_continuation(std::move(*this)));
                    }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_close"));

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
template<BOOST_BEAST_ASYNC_TPARAM1 CloseHandler>
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