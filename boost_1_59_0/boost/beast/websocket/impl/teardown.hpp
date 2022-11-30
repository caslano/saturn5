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
        , nb_(false)
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
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "websocket::tcp::async_teardown"
                        ));

                        s_.async_wait(
                            net::socket_base::wait_read,
                                beast::detail::bind_continuation(std::move(*this)));
                    }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::tcp::async_teardown"
                        ));

                    net::post(bind_front_handler(
                        std::move(*this), ec));
                }
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