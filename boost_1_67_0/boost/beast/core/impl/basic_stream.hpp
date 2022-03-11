//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_CORE_IMPL_BASIC_STREAM_HPP
#define BOOST_BEAST_CORE_IMPL_BASIC_STREAM_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/websocket/teardown.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/assert.hpp>
#include <boost/make_shared.hpp>
#include <boost/core/exchange.hpp>
#include <cstdlib>
#include <type_traits>
#include <utility>

namespace boost {
namespace beast {

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
template<class... Args>
basic_stream<Protocol, Executor, RatePolicy>::
impl_type::
impl_type(std::false_type, Args&&... args)
    : socket(std::forward<Args>(args)...)
    , read(ex())
    , write(ex())
    , timer(ex())
{
    reset();
}

template<class Protocol, class Executor, class RatePolicy>
template<class RatePolicy_, class... Args>
basic_stream<Protocol, Executor, RatePolicy>::
impl_type::
impl_type(std::true_type,
    RatePolicy_&& policy, Args&&... args)
    : boost::empty_value<RatePolicy>(
        boost::empty_init_t{},
        std::forward<RatePolicy_>(policy))
    , socket(std::forward<Args>(args)...)
    , read(ex())
    , write(ex())
    , timer(ex())
{
    reset();
}

template<class Protocol, class Executor, class RatePolicy>
template<class Executor2>
void
basic_stream<Protocol, Executor, RatePolicy>::
impl_type::
on_timer(Executor2 const& ex2)
{
    BOOST_ASSERT(waiting > 0);

    // the last waiter starts the new slice
    if(--waiting > 0)
        return;

    // update the expiration time
    BOOST_VERIFY(timer.expires_after(
        std::chrono::seconds(1)) == 0);

    rate_policy_access::on_timer(policy());

    struct handler : boost::empty_value<Executor2>
    {
        boost::weak_ptr<impl_type> wp;

        using executor_type = Executor2;

        executor_type
        get_executor() const noexcept
        {
            return this->get();
        }

        handler(
            Executor2 const& ex2,
            boost::shared_ptr<impl_type> const& sp)
            : boost::empty_value<Executor2>(
                boost::empty_init_t{}, ex2)
            , wp(sp)
        {
        }

        void
        operator()(error_code ec)
        {
            auto sp = wp.lock();
            if(! sp)
                return;
            if(ec == net::error::operation_aborted)
                return;
            BOOST_ASSERT(! ec);
            if(ec)
                return;
            sp->on_timer(this->get());
        }
    };

    // wait on the timer again
    ++waiting;
    timer.async_wait(handler(ex2, this->shared_from_this()));
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
impl_type::
reset()
{
    // If assert goes off, it means that there are
    // already read or write (or connect) operations
    // outstanding, so there is nothing to apply
    // the expiration time to!
    //
    BOOST_ASSERT(! read.pending || ! write.pending);

    if(! read.pending)
        BOOST_VERIFY(
            read.timer.expires_at(never()) == 0);

    if(! write.pending)
        BOOST_VERIFY(
            write.timer.expires_at(never()) == 0);
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
impl_type::
close() noexcept
{
    {
        error_code ec;
        socket.close(ec);
    }
    try
    {
        timer.cancel();
    }
    catch(...)
    {
    }
}

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
template<class Executor2>
struct basic_stream<Protocol, Executor, RatePolicy>::
    timeout_handler
{
    using executor_type = Executor2;

    op_state& state;
    boost::weak_ptr<impl_type> wp;
    tick_type tick;
    executor_type ex;

    executor_type get_executor() const noexcept
    {
        return ex;
    }

    void
    operator()(error_code ec)
    {
        // timer canceled
        if(ec == net::error::operation_aborted)
            return;
        BOOST_ASSERT(! ec);

        auto sp = wp.lock();

        // stream destroyed
        if(! sp)
            return;

        // stale timer
        if(tick < state.tick)
            return;
        BOOST_ASSERT(tick == state.tick);

        // timeout
        BOOST_ASSERT(! state.timeout);
        sp->close();
        state.timeout = true;
    }
};

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
struct basic_stream<Protocol, Executor, RatePolicy>::ops
{

template<bool isRead, class Buffers, class Handler>
class transfer_op
    : public async_base<Handler, Executor>
    , public boost::asio::coroutine
{
    boost::shared_ptr<impl_type> impl_;
    pending_guard pg_;
    Buffers b_;

    using is_read = std::integral_constant<bool, isRead>;

    op_state&
    state()
    {
        if (isRead)
            return impl_->read;
        else
            return impl_->write;
    }

    std::size_t
    available_bytes()
    {
        if (isRead)
            return rate_policy_access::
                available_read_bytes(impl_->policy());
        else
            return rate_policy_access::
                available_write_bytes(impl_->policy());
    }

    void
    transfer_bytes(std::size_t n)
    {
        if (isRead)
            rate_policy_access::
                transfer_read_bytes(impl_->policy(), n);
        else
            rate_policy_access::
                transfer_write_bytes(impl_->policy(), n);
    }

    void
    async_perform(
        std::size_t amount, std::true_type)
    {
        impl_->socket.async_read_some(
            beast::buffers_prefix(amount, b_),
                std::move(*this));
    }

    void
    async_perform(
        std::size_t amount, std::false_type)
    {
        impl_->socket.async_write_some(
            beast::buffers_prefix(amount, b_),
                std::move(*this));
    }

public:
    template<class Handler_>
    transfer_op(
        Handler_&& h,
        basic_stream& s,
        Buffers const& b)
        : async_base<Handler, Executor>(
            std::forward<Handler_>(h), s.get_executor())
        , impl_(s.impl_)
        , pg_(state().pending)
        , b_(b)
    {
        (*this)({});
    }

    void
    operator()(
        error_code ec,
        std::size_t bytes_transferred = 0)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            // handle empty buffers
            if(detail::buffers_empty(b_))
            {
                // make sure we perform the no-op
                BOOST_ASIO_CORO_YIELD
                async_perform(0, is_read{});
                // apply the timeout manually, otherwise
                // behavior varies across platforms.
                if(state().timer.expiry() <= clock_type::now())
                {
                    impl_->close();
                    ec = beast::error::timeout;
                }
                goto upcall;
            }

            // if a timeout is active, wait on the timer
            if(state().timer.expiry() != never())
                state().timer.async_wait(
                    timeout_handler<decltype(this->get_executor())>{
                        state(),
                        impl_,
                        state().tick,
                        this->get_executor()});

            // check rate limit, maybe wait
            std::size_t amount;
            amount = available_bytes();
            if(amount == 0)
            {
                ++impl_->waiting;
                BOOST_ASIO_CORO_YIELD
                impl_->timer.async_wait(std::move(*this));
                if(ec)
                {
                    // socket was closed, or a timeout
                    BOOST_ASSERT(ec ==
                        net::error::operation_aborted);
                    // timeout handler invoked?
                    if(state().timeout)
                    {
                        // yes, socket already closed
                        ec = beast::error::timeout;
                        state().timeout = false;
                    }
                    goto upcall;
                }
                impl_->on_timer(this->get_executor());

                // Allow at least one byte, otherwise
                // bytes_transferred could be 0.
                amount = std::max<std::size_t>(
                    available_bytes(), 1);
            }

            BOOST_ASIO_CORO_YIELD
            async_perform(amount, is_read{});

            if(state().timer.expiry() != never())
            {
                ++state().tick;

                // try cancelling timer
                auto const n =
                    state().timer.cancel();
                if(n == 0)
                {
                    // timeout handler invoked?
                    if(state().timeout)
                    {
                        // yes, socket already closed
                        ec = beast::error::timeout;
                        state().timeout = false;
                    }
                }
                else
                {
                    BOOST_ASSERT(n == 1);
                    BOOST_ASSERT(! state().timeout);
                }
            }

        upcall:
            pg_.reset();
            transfer_bytes(bytes_transferred);
            this->complete_now(ec, bytes_transferred);
        }
    }
};

template<class Handler>
class connect_op
    : public async_base<Handler, Executor>
{
    boost::shared_ptr<impl_type> impl_;
    pending_guard pg0_;
    pending_guard pg1_;

    op_state&
    state() noexcept
    {
        return impl_->write;
    }

public:
    template<class Handler_>
    connect_op(
        Handler_&& h,
        basic_stream& s,
        endpoint_type ep)
        : async_base<Handler, Executor>(
            std::forward<Handler_>(h), s.get_executor())
        , impl_(s.impl_)
        , pg0_(impl_->read.pending)
        , pg1_(impl_->write.pending)
    {
        if(state().timer.expiry() != stream_base::never())
            impl_->write.timer.async_wait(
                timeout_handler<decltype(this->get_executor())>{
                    state(),
                    impl_,
                    state().tick,
                    this->get_executor()});

        impl_->socket.async_connect(
            ep, std::move(*this));
        // *this is now moved-from
    }

    template<
        class Endpoints, class Condition,
        class Handler_>
    connect_op(
        Handler_&& h,
        basic_stream& s,
        Endpoints const& eps,
        Condition const& cond)
        : async_base<Handler, Executor>(
            std::forward<Handler_>(h), s.get_executor())
        , impl_(s.impl_)
        , pg0_(impl_->read.pending)
        , pg1_(impl_->write.pending)
    {
        if(state().timer.expiry() != stream_base::never())
            impl_->write.timer.async_wait(
                timeout_handler<decltype(this->get_executor())>{
                    state(),
                    impl_,
                    state().tick,
                    this->get_executor()});

        net::async_connect(impl_->socket,
            eps, cond, std::move(*this));
        // *this is now moved-from
    }

    template<
        class Iterator, class Condition,
        class Handler_>
    connect_op(
        Handler_&& h,
        basic_stream& s,
        Iterator begin, Iterator end,
        Condition const& cond)
        : async_base<Handler, Executor>(
            std::forward<Handler_>(h), s.get_executor())
        , impl_(s.impl_)
        , pg0_(impl_->read.pending)
        , pg1_(impl_->write.pending)
    {
        if(state().timer.expiry() != stream_base::never())
            impl_->write.timer.async_wait(
                timeout_handler<decltype(this->get_executor())>{
                    state(),
                    impl_,
                    state().tick,
                    this->get_executor()});

        net::async_connect(impl_->socket,
            begin, end, cond, std::move(*this));
        // *this is now moved-from
    }

    template<class... Args>
    void
    operator()(error_code ec, Args&&... args)
    {
        if(state().timer.expiry() != stream_base::never())
        {
            ++state().tick;

            // try cancelling timer
            auto const n =
                impl_->write.timer.cancel();
            if(n == 0)
            {
                // timeout handler invoked?
                if(state().timeout)
                {
                    // yes, socket already closed
                    ec = beast::error::timeout;
                    state().timeout = false;
                }
            }
            else
            {
                BOOST_ASSERT(n == 1);
                BOOST_ASSERT(! state().timeout);
            }
        }

        pg0_.reset();
        pg1_.reset();
        this->complete_now(ec, std::forward<Args>(args)...);
    }
};

struct run_read_op
{
    template<class ReadHandler, class Buffers>
    void
    operator()(
        ReadHandler&& h,
        basic_stream* s,
        Buffers const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            detail::is_invocable<ReadHandler,
                void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        transfer_op<
            true,
            Buffers,
            typename std::decay<ReadHandler>::type>(
                std::forward<ReadHandler>(h), *s, b);
    }
};

struct run_write_op
{
    template<class WriteHandler, class Buffers>
    void
    operator()(
        WriteHandler&& h,
        basic_stream* s,
        Buffers const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            detail::is_invocable<WriteHandler,
                void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        transfer_op<
            false,
            Buffers,
            typename std::decay<WriteHandler>::type>(
                std::forward<WriteHandler>(h), *s, b);
    }
};

struct run_connect_op
{
    template<class ConnectHandler>
    void
    operator()(
        ConnectHandler&& h,
        basic_stream* s,
        endpoint_type const& ep)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            detail::is_invocable<ConnectHandler,
                void(error_code)>::value,
            "ConnectHandler type requirements not met");

        connect_op<typename std::decay<ConnectHandler>::type>(
            std::forward<ConnectHandler>(h), *s, ep);
    }
};

struct run_connect_range_op
{
    template<
        class RangeConnectHandler,
        class EndpointSequence,
        class Condition>
    void
    operator()(
        RangeConnectHandler&& h,
        basic_stream* s,
        EndpointSequence const& eps,
        Condition const& cond)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            detail::is_invocable<RangeConnectHandler,
                void(error_code, typename Protocol::endpoint)>::value,
            "RangeConnectHandler type requirements not met");

        connect_op<typename std::decay<RangeConnectHandler>::type>(
            std::forward<RangeConnectHandler>(h), *s, eps, cond);
    }
};

struct run_connect_iter_op
{
    template<
        class IteratorConnectHandler,
        class Iterator,
        class Condition>
    void
    operator()(
        IteratorConnectHandler&& h,
        basic_stream* s,
        Iterator begin, Iterator end,
        Condition const& cond)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            detail::is_invocable<IteratorConnectHandler,
                void(error_code, Iterator)>::value,
            "IteratorConnectHandler type requirements not met");

        connect_op<typename std::decay<IteratorConnectHandler>::type>(
            std::forward<IteratorConnectHandler>(h), *s, begin, end, cond);
    }
};

};

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
basic_stream<Protocol, Executor, RatePolicy>::
~basic_stream()
{
    // the shared object can outlive *this,
    // cancel any operations so the shared
    // object is destroyed as soon as possible.
    impl_->close();
}

template<class Protocol, class Executor, class RatePolicy>
template<class Arg0, class... Args, class>
basic_stream<Protocol, Executor, RatePolicy>::
basic_stream(Arg0&& arg0, Args&&... args)
    : impl_(boost::make_shared<impl_type>(
        std::false_type{},
        std::forward<Arg0>(arg0),
        std::forward<Args>(args)...))
{
}

template<class Protocol, class Executor, class RatePolicy>
template<class RatePolicy_, class Arg0, class... Args, class>
basic_stream<Protocol, Executor, RatePolicy>::
basic_stream(
    RatePolicy_&& policy, Arg0&& arg0, Args&&... args)
    : impl_(boost::make_shared<impl_type>(
        std::true_type{},
        std::forward<RatePolicy_>(policy),
        std::forward<Arg0>(arg0),
        std::forward<Args>(args)...))
{
}

template<class Protocol, class Executor, class RatePolicy>
basic_stream<Protocol, Executor, RatePolicy>::
basic_stream(basic_stream&& other)
    : impl_(boost::make_shared<impl_type>(
        std::move(*other.impl_)))
{
    // VFALCO I'm not sure this implementation is correct...
}

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
auto
basic_stream<Protocol, Executor, RatePolicy>::
release_socket() ->
    socket_type
{
    this->cancel();
    return std::move(impl_->socket);
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
expires_after(std::chrono::nanoseconds expiry_time)
{
    // If assert goes off, it means that there are
    // already read or write (or connect) operations
    // outstanding, so there is nothing to apply
    // the expiration time to!
    //
    BOOST_ASSERT(
        ! impl_->read.pending ||
        ! impl_->write.pending);

    if(! impl_->read.pending)
        BOOST_VERIFY(
            impl_->read.timer.expires_after(
                expiry_time) == 0);

    if(! impl_->write.pending)
        BOOST_VERIFY(
            impl_->write.timer.expires_after(
                expiry_time) == 0);
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
expires_at(
    net::steady_timer::time_point expiry_time)
{
    // If assert goes off, it means that there are
    // already read or write (or connect) operations
    // outstanding, so there is nothing to apply
    // the expiration time to!
    //
    BOOST_ASSERT(
        ! impl_->read.pending ||
        ! impl_->write.pending);

    if(! impl_->read.pending)
        BOOST_VERIFY(
            impl_->read.timer.expires_at(
                expiry_time) == 0);

    if(! impl_->write.pending)
        BOOST_VERIFY(
            impl_->write.timer.expires_at(
                expiry_time) == 0);
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
expires_never()
{
    impl_->reset();
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
cancel()
{
    error_code ec;
    impl_->socket.cancel(ec);
    impl_->timer.cancel();
}

template<class Protocol, class Executor, class RatePolicy>
void
basic_stream<Protocol, Executor, RatePolicy>::
close()
{
    impl_->close();
}

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
template<class ConnectHandler>
BOOST_BEAST_ASYNC_RESULT1(ConnectHandler)
basic_stream<Protocol, Executor, RatePolicy>::
async_connect(
    endpoint_type const& ep,
    ConnectHandler&& handler)
{
    return net::async_initiate<
        ConnectHandler,
        void(error_code)>(
            typename ops::run_connect_op{},
            handler,
            this,
            ep);
}

template<class Protocol, class Executor, class RatePolicy>
template<
    class EndpointSequence,
    class RangeConnectHandler,
    class>
BOOST_ASIO_INITFN_RESULT_TYPE(RangeConnectHandler,void(error_code, typename Protocol::endpoint))
basic_stream<Protocol, Executor, RatePolicy>::
async_connect(
    EndpointSequence const& endpoints,
    RangeConnectHandler&& handler)
{
    return net::async_initiate<
        RangeConnectHandler,
        void(error_code, typename Protocol::endpoint)>(
            typename ops::run_connect_range_op{},
            handler,
            this,
            endpoints,
            detail::any_endpoint{});
}

template<class Protocol, class Executor, class RatePolicy>
template<
    class EndpointSequence,
    class ConnectCondition,
    class RangeConnectHandler,
    class>
BOOST_ASIO_INITFN_RESULT_TYPE(RangeConnectHandler,void (error_code, typename Protocol::endpoint))
basic_stream<Protocol, Executor, RatePolicy>::
async_connect(
    EndpointSequence const& endpoints,
    ConnectCondition connect_condition,
    RangeConnectHandler&& handler)
{
    return net::async_initiate<
        RangeConnectHandler,
        void(error_code, typename Protocol::endpoint)>(
            typename ops::run_connect_range_op{},
            handler,
            this,
            endpoints,
            connect_condition);
}

template<class Protocol, class Executor, class RatePolicy>
template<
    class Iterator,
    class IteratorConnectHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(IteratorConnectHandler,void (error_code, Iterator))
basic_stream<Protocol, Executor, RatePolicy>::
async_connect(
    Iterator begin, Iterator end,
    IteratorConnectHandler&& handler)
{
    return net::async_initiate<
        IteratorConnectHandler,
        void(error_code, Iterator)>(
            typename ops::run_connect_iter_op{},
            handler,
            this,
            begin, end,
            detail::any_endpoint{});
}

template<class Protocol, class Executor, class RatePolicy>
template<
    class Iterator,
    class ConnectCondition,
    class IteratorConnectHandler>
BOOST_ASIO_INITFN_RESULT_TYPE(IteratorConnectHandler,void (error_code, Iterator))
basic_stream<Protocol, Executor, RatePolicy>::
async_connect(
    Iterator begin, Iterator end,
    ConnectCondition connect_condition,
    IteratorConnectHandler&& handler)
{
    return net::async_initiate<
        IteratorConnectHandler,
        void(error_code, Iterator)>(
            typename ops::run_connect_iter_op{},
            handler,
            this,
            begin, end,
            connect_condition);
}

//------------------------------------------------------------------------------

template<class Protocol, class Executor, class RatePolicy>
template<class MutableBufferSequence, class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
basic_stream<Protocol, Executor, RatePolicy>::
async_read_some(
    MutableBufferSequence const& buffers,
    ReadHandler&& handler)
{
    static_assert(net::is_mutable_buffer_sequence<
        MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    return net::async_initiate<
        ReadHandler,
        void(error_code, std::size_t)>(
            typename ops::run_read_op{},
            handler,
            this,
            buffers);
}

template<class Protocol, class Executor, class RatePolicy>
template<class ConstBufferSequence, class WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
basic_stream<Protocol, Executor, RatePolicy>::
async_write_some(
    ConstBufferSequence const& buffers,
    WriteHandler&& handler)
{
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

//------------------------------------------------------------------------------
//
// Customization points
//

#if ! BOOST_BEAST_DOXYGEN

template<
    class Protocol, class Executor, class RatePolicy>
void
beast_close_socket(
    basic_stream<Protocol, Executor, RatePolicy>& stream)
{
    error_code ec;
    stream.socket().close(ec);
}

template<
    class Protocol, class Executor, class RatePolicy>
void
teardown(
    role_type role,
    basic_stream<Protocol, Executor, RatePolicy>& stream,
    error_code& ec)
{
    using beast::websocket::teardown;
    teardown(role, stream.socket(), ec);
}

template<
    class Protocol, class Executor, class RatePolicy,
    class TeardownHandler>
void
async_teardown(
    role_type role,
    basic_stream<Protocol, Executor, RatePolicy>& stream,
    TeardownHandler&& handler)
{
    using beast::websocket::async_teardown;
    async_teardown(role, stream.socket(),
        std::forward<TeardownHandler>(handler));
}

#endif

} // beast
} // boost

#endif

/* basic_stream.hpp
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
*/