//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_PING_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_PING_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/bind_continuation.hpp>
#include <boost/beast/websocket/detail/frame.hpp>
#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <boost/throw_exception.hpp>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

/*
    This composed operation handles sending ping and pong frames.
    It only sends the frames it does not make attempts to read
    any frame data.
*/
template<class NextLayer, bool deflateSupported>
template<class Handler>
class stream<NextLayer, deflateSupported>::ping_op
    : public beast::stable_async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    boost::weak_ptr<impl_type> wp_;
    detail::frame_buffer& fb_;

public:
    static constexpr int id = 3; // for soft_mutex

    template<class Handler_>
    ping_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        detail::opcode op,
        ping_data const& payload)
        : stable_async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , fb_(beast::allocate_stable<
            detail::frame_buffer>(*this))
    {
        // Serialize the ping or pong frame
        sp->template write_ping<
            flat_static_buffer_base>(fb_, op, payload);
        (*this)({}, 0, false);
    }

    void operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true)
    {
        boost::ignore_unused(bytes_transferred);
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
                impl.op_ping.emplace(std::move(*this));
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                net::post(std::move(*this));
                BOOST_ASSERT(impl.wr_block.is_locked(this));
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // Send ping frame
            BOOST_ASIO_CORO_YIELD
            net::async_write(impl.stream(), fb_.data(),
                beast::detail::bind_continuation(std::move(*this)));
            if(impl.check_stop_now(ec))
                goto upcall;

        upcall:
            impl.wr_block.unlock(this);
            impl.op_close.maybe_invoke()
                || impl.op_idle_ping.maybe_invoke()
                || impl.op_rd.maybe_invoke()
                || impl.op_wr.maybe_invoke();
            this->complete(cont, ec);
        }
    }
};

//------------------------------------------------------------------------------

// sends the idle ping
template<class NextLayer, bool deflateSupported>
template<class Executor>
class stream<NextLayer, deflateSupported>::idle_ping_op
    : public asio::coroutine
    , public boost::empty_value<Executor>
{
    boost::weak_ptr<impl_type> wp_;
    std::unique_ptr<detail::frame_buffer> fb_;

public:
    static constexpr int id = 4; // for soft_mutex

    using executor_type = Executor;

    executor_type
    get_executor() const noexcept
    {
        return this->get();
    }

    idle_ping_op(
        boost::shared_ptr<impl_type> const& sp,
        Executor const& ex)
        : boost::empty_value<Executor>(
            boost::empty_init_t{}, ex)
        , wp_(sp)
        , fb_(new detail::frame_buffer)
    {
        if(! sp->idle_pinging)
        {
            // Create the ping frame
            ping_data payload; // empty for now
            sp->template write_ping<
                flat_static_buffer_base>(*fb_,
                    detail::opcode::ping, payload);

            sp->idle_pinging = true;
            (*this)({}, 0);
        }
        else
        {
            // if we are already in the middle of sending
            // an idle ping, don't bother sending another.
        }
    }

    void operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0)
    {
        boost::ignore_unused(bytes_transferred);
        auto sp = wp_.lock();
        if(! sp)
            return;
        auto& impl = *sp;
        BOOST_ASIO_CORO_REENTER(*this)
        {
            // Acquire the write lock
            if(! impl.wr_block.try_lock(this))
            {
                BOOST_ASIO_CORO_YIELD
                impl.op_idle_ping.emplace(std::move(*this));
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                net::post(
                    this->get_executor(), std::move(*this));
                BOOST_ASSERT(impl.wr_block.is_locked(this));
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // Send ping frame
            BOOST_ASIO_CORO_YIELD
            net::async_write(impl.stream(), fb_->data(),
                //beast::detail::bind_continuation(std::move(*this)));
                std::move(*this));
            if(impl.check_stop_now(ec))
                goto upcall;

        upcall:
            BOOST_ASSERT(sp->idle_pinging);
            sp->idle_pinging = false;
            impl.wr_block.unlock(this);
            impl.op_close.maybe_invoke()
                || impl.op_ping.maybe_invoke()
                || impl.op_rd.maybe_invoke()
                || impl.op_wr.maybe_invoke();
        }
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_ping_op
{
    template<class WriteHandler>
    void
    operator()(
        WriteHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        detail::opcode op,
        ping_data const& p)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
                void(error_code)>::value,
            "WriteHandler type requirements not met");

        ping_op<
            typename std::decay<WriteHandler>::type>(
                std::forward<WriteHandler>(h),
                sp,
                op,
                p);
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
ping(ping_data const& payload)
{
    error_code ec;
    ping(payload, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
ping(ping_data const& payload, error_code& ec)
{
    if(impl_->check_stop_now(ec))
        return;
    detail::frame_buffer fb;
    impl_->template write_ping<flat_static_buffer_base>(
        fb, detail::opcode::ping, payload);
    net::write(impl_->stream(), fb.data(), ec);
    if(impl_->check_stop_now(ec))
        return;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
pong(ping_data const& payload)
{
    error_code ec;
    pong(payload, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
pong(ping_data const& payload, error_code& ec)
{
    if(impl_->check_stop_now(ec))
        return;
    detail::frame_buffer fb;
    impl_->template write_ping<flat_static_buffer_base>(
        fb, detail::opcode::pong, payload);
    net::write(impl_->stream(), fb.data(), ec);
    if(impl_->check_stop_now(ec))
        return;
}

template<class NextLayer, bool deflateSupported>
template<class WriteHandler>
BOOST_BEAST_ASYNC_RESULT1(WriteHandler)
stream<NextLayer, deflateSupported>::
async_ping(ping_data const& payload, WriteHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code)>(
            run_ping_op{},
            handler,
            impl_,
            detail::opcode::ping,
            payload);
}

template<class NextLayer, bool deflateSupported>
template<class WriteHandler>
BOOST_BEAST_ASYNC_RESULT1(WriteHandler)
stream<NextLayer, deflateSupported>::
async_pong(ping_data const& payload, WriteHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    return net::async_initiate<
        WriteHandler,
        void(error_code)>(
            run_ping_op{},
            handler,
            impl_,
            detail::opcode::pong,
            payload);
}

} // websocket
} // beast
} // boost

#endif

/* ping.hpp
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
*/