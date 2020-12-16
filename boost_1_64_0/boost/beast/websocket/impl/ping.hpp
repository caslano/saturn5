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
fx/Twt6XjqzG9TxhblL5r7m2Xfdctib+nLiya9fDJ7D2b+FvxgPpOxgPlDqMB1a5jAfWOYwHNkaMB3Qfu8NYb0vEWC9y3BXUJvt03be8SMfzSUuk3Qo1l2nljZfreF7l95Fniz6X27he5ZqZejVM3IWcNemLfnbNXtmRItNJ3Fkmjnjnsb/xby9pYcy0Qx0A8hH6OXcdQKRslrsOALkd6ZbMmB/ZinqFGfJ8FZq9ngtEpg9vqJrme5NfNCvrmxdSB/q2qPr+38rXAun400E/kOqgH0h30Q9kOegH8s21Aie9U8R++uGqD2ip+oAWqg/4wrFe6ksV4/Je1XAtKn13qozre1H9XfUC6m/0Ap3i/x69APlozibaUs8S80KAsQ58CIb06gnHOeYj/zk8u/pO63aCPOOap3YcnaTe0pa5rqULJSTneGRxNdX24hZx7+drzgzFWPJsue7tpnpovMMtu58Sa56x7Nw0qU5GX4+s6vm0rzBJ3CsD6QHeneHhCiyz3/wwkbkwkBvwa9nZ8fSIrj+mnRok/qfQB2kQCG87CBfZ/4jsM5izb2Zo+AkB3on6fNvvfHPGu8jUDZS5OfXpRD2TwLyP5eZNXyVD5EsDkwJB0+7WKT9/pvysAcnrPKupuAko5XgPPZzG1jTetEN9TcL6MIWm//aBxP+YX/Mfw/b+OWlkS/lZTCUiUxIwaaRfIu2dnuc0RfzPCUT3GeLs72yI/wmB7dZ7vo/8WWYf+yS59xnR/QXzHdT+ck91/OI28qPC7mOW6WsdLr9xQaA8rmmSkXbb2kjyo76vsbW/6Sd9JfE/4Usgj/LJowmcgFPAc91M+yS/aL+kvznHRvonEKv9kW3wHuz5XJ+ADbUHqTC+MdR+hfYXpP1eov0ItaYfkVqFfkT0Ws5VLms515k22DxLpi9hrhdoXyKyXTJt1V6mXY9sa26L0W+Sq+7oCV23+8XSqLbGrIR27U9omL76/R7X/oTK9Tb1ot2ykHuj+7peE6an+e5tGwlzlfM6X20zWmq82l5oHN12uO73i6VV6wckRcrKu9FtbBAnabnd9H94wjPNWRFR/QeeAXkXd16m32jXe+RZFvl2pt3WeOQWytvt6RIuYM4iayDuzdYErul5JPIM5GALsd2o4/s0rFp/JPSNiDXLzDciqjx/of0Ox/qd5bJWOd9lrfI8hzqeYPo5kq/mOxXkaSi8uNuZ38mP/J76npaYlUF0kXAplL0AJzk/A2VvXNc9ARqup7o5CexUGUfu8J3LI6ph21txepbY/riRC27zNfEHgz30OqfOnBK6nukvsGb7fvPtH723wLwDe0n4o4L7BYP6/rV/o210vTZta3fxH855fs8G9NnRMK1MW79I7ql11Hhcx/7LQ353cd5Ac73GaXFybQFX9jdt/M8SZ3GF8XScPjOdxb8o+BHv/Bju3R5X95Xf7up0jqGkf62EeyYQldawd3JxN6ljmt63RH5ioKZvqTXHf5dzmvXd+LrInhmIeGdrm/TByfgxQo8TN7kuZfS9r4Y137dGy+iM8vP7TJ8gSeLMCx4YrBE9Tjdt2QiRaRkUt6lTXcPvqasV1neZK799oW82vTW5Zu5niX0/8l54SuK9gP6ROVuweKp0F8r7C9NE5uCg23u9l9x33UDUe1zeT9sl7KLA5bQ77fU9/Ju+h+3vjp8QaY1u4AF4P7ZvXOTfT2DD39Opam29AnoB6KwbgOgHoMal3zFXfUPV3t+hNjD5VNMG7tT7XPQCDnttNka2aWHzgtU3b+c8v+U+3+Y8H+k2r7bz85Q7+w2Yv+ubN9tk3rH3ZY+ds++3BT3a/bC6+0dr286tvrN0nOcv3ecLnedT3ec=
*/