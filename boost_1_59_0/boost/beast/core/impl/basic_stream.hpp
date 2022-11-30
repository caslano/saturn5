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

    static bool never_pending_;

public:
    template<class Handler_>
    transfer_op(
        Handler_&& h,
        basic_stream& s,
        Buffers const& b)
        : async_base<Handler, Executor>(
            std::forward<Handler_>(h), s.get_executor())
        , impl_(s.impl_)
        , pg_()
        , b_(b)
    {
        if (buffer_bytes(b_) == 0 && state().pending)
        {
            // Workaround:
            // Corner case discovered in https://github.com/boostorg/beast/issues/2065
            // Enclosing SSL stream wishes to complete a 0-length write early by
            // executing a 0-length read against the underlying stream.
            // This can occur even if an existing async_read is in progress.
            // In this specific case, we will complete the async op with no error
            // in order to prevent assertions and/or internal corruption of the basic_stream
            this->complete(false, error_code(), 0);
        }
        else
        {
            pg_.assign(state().pending);
            (*this)({});
        }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        (isRead ? "basic_stream::async_read_some"
                            : "basic_stream::async_write_some")));

                    async_perform(0, is_read{});
                }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    (isRead ? "basic_stream::async_read_some"
                        : "basic_stream::async_write_some")));

                state().timer.async_wait(
                    timeout_handler<decltype(this->get_executor())>{
                        state(),
                        impl_,
                        state().tick,
                        this->get_executor()});
            }

            // check rate limit, maybe wait
            std::size_t amount;
            amount = available_bytes();
            if(amount == 0)
            {
                ++impl_->waiting;
                BOOST_ASIO_CORO_YIELD
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        (isRead ? "basic_stream::async_read_some"
                            : "basic_stream::async_write_some")));

                    impl_->timer.async_wait(std::move(*this));
                }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    (isRead ? "basic_stream::async_read_some"
                        : "basic_stream::async_write_some")));

                async_perform(amount, is_read{});
            }

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
        {
            BOOST_ASIO_HANDLER_LOCATION((
                __FILE__, __LINE__,
                "basic_stream::async_connect"));

            impl_->write.timer.async_wait(
                timeout_handler<decltype(this->get_executor())>{
                    state(),
                    impl_,
                    state().tick,
                    this->get_executor()});
        }

        BOOST_ASIO_HANDLER_LOCATION((
            __FILE__, __LINE__,
            "basic_stream::async_connect"));

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
        {
            BOOST_ASIO_HANDLER_LOCATION((
                __FILE__, __LINE__,
                "basic_stream::async_connect"));

            impl_->write.timer.async_wait(
                timeout_handler<decltype(this->get_executor())>{
                    state(),
                    impl_,
                    state().tick,
                    this->get_executor()});
        }

        BOOST_ASIO_HANDLER_LOCATION((
            __FILE__, __LINE__,
            "basic_stream::async_connect"));

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
        {
            BOOST_ASIO_HANDLER_LOCATION((
                __FILE__, __LINE__,
                "basic_stream::async_connect"));

            impl_->write.timer.async_wait(
                timeout_handler<decltype(this->get_executor())>{
                    state(),
                    impl_,
                    state().tick,
                    this->get_executor()});
        }

        BOOST_ASIO_HANDLER_LOCATION((
            __FILE__, __LINE__,
            "basic_stream::async_connect"));

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
    // Explainer: Asio's sockets provide the guarantee that a moved-from socket
    // will be in a state as-if newly created. i.e.:
    // * having the same (valid) executor
    // * the socket shall not be open
    // We provide the same guarantee by moving the impl rather than the pointer
    // controlling its lifetime.
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
expires_after(net::steady_timer::duration expiry_time)
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
template<BOOST_BEAST_ASYNC_TPARAM1 ConnectHandler>
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
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, typename Protocol::endpoint)) RangeConnectHandler,
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
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, typename Protocol::endpoint)) RangeConnectHandler,
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
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, Iterator)) IteratorConnectHandler>
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
    BOOST_ASIO_COMPLETION_TOKEN_FOR(void(error_code, Iterator)) IteratorConnectHandler>
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
template<class MutableBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 ReadHandler>
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
template<class ConstBufferSequence, BOOST_BEAST_ASYNC_TPARAM2 WriteHandler>
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