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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_ping"));

                    impl.op_ping.emplace(std::move(*this));
                }
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_ping"));

                    net::post(std::move(*this));
                }
                BOOST_ASSERT(impl.wr_block.is_locked(this));
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // Send ping frame
            BOOST_ASIO_CORO_YIELD
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_ping"));

                net::async_write(impl.stream(), fb_.data(),
                    beast::detail::bind_continuation(std::move(*this)));
            }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                                                __FILE__, __LINE__,
                                                "websocket::async_ping"));

                    impl.op_idle_ping.emplace(std::move(*this));
                }
                impl.wr_block.lock(this);
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_ping"));

                    net::post(
                        this->get_executor(), std::move(*this));
                }
                BOOST_ASSERT(impl.wr_block.is_locked(this));
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // Send ping frame
            BOOST_ASIO_CORO_YIELD
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_ping"));

                net::async_write(impl.stream(), fb_->data(),
                    std::move(*this));
            }
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
template<BOOST_BEAST_ASYNC_TPARAM1 WriteHandler>
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
template<BOOST_BEAST_ASYNC_TPARAM1 WriteHandler>
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