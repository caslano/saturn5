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
hlwj+DpsDt+AB8I3YT/4LhwA34FD1D1C3Ro/Yzf3+J/W+J/R+J/V+J/T+F/S+F/U+HETP24Tv45B4BEO8d+O3J7wDrgPvBMeBLfCg+G9cBC8B6aoe5y6t8MUS/vlcKLGXwseovF/iHcM/EjT/zHsCz/R39kOD4Gfw/HituPVPioc7xDvNs2XBzXeh2Af+LDmz+Oa/sfgaHVvl/LVPh8cpPHWhIQRk4ZcLEyHzeBU2AVmaLozYbK6t8N12K0a310aX0O4UuPL0u8CZsOWMAf2grman7PhBFgA02EhzITFcA6cB5fA+fA0uACuUP3/WrgEXgyPgxvg8fBa1ftvVrd931Yl9z1e73uC3vfhet8T9b4nwWR1Ex9vZ+2bwA4aXw3YQ+MbrvGNgo1hCmyh+vvWcKzG84Z5l0p/Q+LZS+p7mVmm31M8SdNzGhwIS7UeroDZcCUsgmfBY+BqeAJco/m2Fq6D58Gt8Hx4N1ynev318HF4EfwQXqHfvbwKNoZXwwS4CXaH18I+8EaYDDfDofAmOAZugePgzbDU0/d7+v5doO9feTnlg30DW/sK8hibii3BXol9BvsztvWVu34ewDOe8YxnPOMZz/x/zK6Y/89Jyy/Ilen/Pz//f2DY/H8MA04hA5sWyri2jFnO0Pn/lGEpUwqmMPefWVBIGrJzi0SPtyZG9I+ovMx6Wg3Tz+jh488MuZ8KLkQLUcfo7uepDtSW72V1UD1gnMjfH0xgJPlUaNTjr2F1xy73M78ZGGpNDBzmixNZQonsMYGAle1f6L/d1k1yLW/6dJ1Pi4O7i9y7wRU6Z5plfrcj7rD10Xofg/FfsrJM39xW1622lTgeCuZxF7X8dax2/sOtVf5HfCXBGtat2FjUhuj+NU23BLORK9d1zsjMDcWNzGDYTGSeDdYx/vlWB9XZthe/B4L5lNIaXydrtP8g6yz/k775wRhrLb+zhVBxxJNEqP1F9qbgdGt338JgfStWdcLcS970KdOK8grK72fA2SHZeMLiJu+OkLCTg7WtQLBjsIXVlDjTI+Jc4dvT39RaGOwg8baSGlKYmZmRNpObkXtJ5UorkX80GFuuF6b65uVamv97wIDIfBo8ifwsv+epdpmb38xAq5HsO9d6y7evtad/unWC/xt+P2AtDzaW39tGqEYi+2owlLeHt5G8ywvVxzgtp85Sbmv5ncboFprrumOfdaFcrxH2+1Ostqp37yRx3kvZBq0iX471ua+t1dJ/pHWm/xlrNfkdq2Vzz4qQXK1AJ+s5P+mRucDaEvYD0mPnfV5BRmaB5GdKhfyMkfwMyVKcmp+WSfuDksYW/rt8TazXfH2i0y7h2km43FyeRtKl+1ckXcsCvaxRgfoRz0bAPBOEyc7Q+t0YfiD+Q9VdLh9n5LML06bRJKUVzc3DFY/cTH5rnfxWl0AOc6rrmRWui8Z+u6+76P2PlvKYnlcwy7KaIj8L+QWS9tnU4hqUaSOrt5/12OY3imblp5WnqyE8ReJvKHV8S0T+fW9Rx8PSN3VKIUksmp+faYXdV8JZZfcVK2477xqSytutzcwbdNL53m/FRs4LLMU2pQFsGcszCvuRoLUxZfZyvR76ewh/D8Uyz2BsAe7Z2JHY0dgx2FGhMLSz2+G3Gt6Oc3CUu3cjZ9tX57nyLTUu81ybIO0x8wraHnNti5mLnCcyW3GTd7ilfSTeulKf3pAzYGij0opzp/GSKMgsLKReGv8XjH+4L3ml/h8Y/6z5Uwsozqh5zxt0GL4O2wJ7CvbWRHRrq1zfL2nT8y2puyuIwWfhMu8YO1xbMy80Xdx5Tu8XlW1l5pmmiXtu9LtC/PeA6eKfoe8JO3yC+vush8Vdw2k=
*/