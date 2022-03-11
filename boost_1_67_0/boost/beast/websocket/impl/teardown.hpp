//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_TEARDOWN_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_TEARDOWN_HPP

#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/bind_continuation.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

namespace detail {

template<
    class Protocol, class Executor,
    class Handler>
class teardown_tcp_op
    : public beast::async_base<
        Handler, beast::executor_type<
            net::basic_stream_socket<
                Protocol, Executor>>>
    , public asio::coroutine
{
    using socket_type =
        net::basic_stream_socket<Protocol, Executor>;

    socket_type& s_;
    role_type role_;
    bool nb_;

public:
    template<class Handler_>
    teardown_tcp_op(
        Handler_&& h,
        socket_type& s,
        role_type role)
        : async_base<Handler,
            beast::executor_type<
                net::basic_stream_socket<
                    Protocol, Executor>>>(
            std::forward<Handler_>(h),
            s.get_executor())
        , s_(s)
        , role_(role)
    {
        (*this)({}, 0, false);
    }

    void
    operator()(
        error_code ec = {},
        std::size_t bytes_transferred = 0,
        bool cont = true)
    {
        BOOST_ASIO_CORO_REENTER(*this)
        {
            nb_ = s_.non_blocking();
            s_.non_blocking(true, ec);
            if(ec)
                goto upcall;
            if(role_ == role_type::server)
                s_.shutdown(net::socket_base::shutdown_send, ec);
            if(ec)
                goto upcall;
            for(;;)
            {
                {
                    char buf[2048];
                    s_.read_some(net::buffer(buf), ec);
                }
                if(ec == net::error::would_block)
                {
                    BOOST_ASIO_CORO_YIELD
                    s_.async_wait(
                        net::socket_base::wait_read,
                            beast::detail::bind_continuation(std::move(*this)));
                    continue;
                }
                if(ec)
                {
                    if(ec != net::error::eof)
                        goto upcall;
                    ec = {};
                    break;
                }
                if(bytes_transferred == 0)
                {
                    // happens sometimes
                    // https://github.com/boostorg/beast/issues/1373
                    break;
                }
            }
            if(role_ == role_type::client)
                s_.shutdown(net::socket_base::shutdown_send, ec);
            if(ec)
                goto upcall;
            s_.close(ec);
        upcall:
            if(! cont)
            {
                BOOST_ASIO_CORO_YIELD
                net::post(bind_front_handler(
                    std::move(*this), ec));
            }
            {
                error_code ignored;
                s_.non_blocking(nb_, ignored);
            }
            this->complete_now(ec);
        }
    }
};

} // detail

//------------------------------------------------------------------------------

template<class Protocol, class Executor>
void
teardown(
    role_type role,
    net::basic_stream_socket<
        Protocol, Executor>& socket,
    error_code& ec)
{
    if(role == role_type::server)
        socket.shutdown(
            net::socket_base::shutdown_send, ec);
    if(ec)
        return;
    for(;;)
    {
        char buf[2048];
        auto const bytes_transferred =
            socket.read_some(net::buffer(buf), ec);
        if(ec)
        {
            if(ec != net::error::eof)
                return;
            ec = {};
            break;
        }
        if(bytes_transferred == 0)
        {
            // happens sometimes
            // https://github.com/boostorg/beast/issues/1373
            break;
        }
    }
    if(role == role_type::client)
        socket.shutdown(
            net::socket_base::shutdown_send, ec);
    if(ec)
        return;
    socket.close(ec);
}

template<
    class Protocol, class Executor,
    class TeardownHandler>
void
async_teardown(
    role_type role,
    net::basic_stream_socket<
        Protocol, Executor>& socket,
    TeardownHandler&& handler)
{
    static_assert(beast::detail::is_invocable<
        TeardownHandler, void(error_code)>::value,
            "TeardownHandler type requirements not met");
    detail::teardown_tcp_op<
        Protocol,
        Executor,
        typename std::decay<TeardownHandler>::type>(
            std::forward<TeardownHandler>(handler),
            socket,
            role);
}

} // websocket
} // beast
} // boost

#endif

/* teardown.hpp
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
*/