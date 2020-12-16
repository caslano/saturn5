//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_ACCEPT_IPP
#define BOOST_BEAST_WEBSOCKET_IMPL_ACCEPT_IPP

#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/beast/websocket/detail/type_traits.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/parser.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/buffer.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <memory>
#include <type_traits>

namespace boost {
namespace beast {
namespace websocket {

//------------------------------------------------------------------------------

namespace detail {

template<class Body, class Allocator>
void
impl_base<true>::
build_response_pmd(
    http::response<http::string_body>& res,
    http::request<Body,
        http::basic_fields<Allocator>> const& req)
{
    pmd_offer offer;
    pmd_offer unused;
    pmd_read(offer, req);
    pmd_negotiate(res, unused, offer, pmd_opts_);
}

template<class Body, class Allocator>
void
impl_base<false>::
build_response_pmd(
    http::response<http::string_body>&,
    http::request<Body,
        http::basic_fields<Allocator>> const&)
{
}

} // detail

template<class NextLayer, bool deflateSupported>
template<class Body, class Allocator, class Decorator>
response_type
stream<NextLayer, deflateSupported>::impl_type::
build_response(
    http::request<Body,
        http::basic_fields<Allocator>> const& req,
    Decorator const& decorator,
    error_code& result)
{
    auto const decorate =
        [this, &decorator](response_type& res)
        {
            decorator_opt(res);
            decorator(res);
            if(! res.count(http::field::server))
                res.set(http::field::server,
                    string_view(BOOST_BEAST_VERSION_STRING));
        };
    auto err =
        [&](error e)
        {
            result = e;
            response_type res;
            res.version(req.version());
            res.result(http::status::bad_request);
            res.body() = result.message();
            res.prepare_payload();
            decorate(res);
            return res;
        };
    if(req.version() != 11)
        return err(error::bad_http_version);
    if(req.method() != http::verb::get)
        return err(error::bad_method);
    if(! req.count(http::field::host))
        return err(error::no_host);
    {
        auto const it = req.find(http::field::connection);
        if(it == req.end())
            return err(error::no_connection);
        if(! http::token_list{it->value()}.exists("upgrade"))
            return err(error::no_connection_upgrade);
    }
    {
        auto const it = req.find(http::field::upgrade);
        if(it == req.end())
            return err(error::no_upgrade);
        if(! http::token_list{it->value()}.exists("websocket"))
            return err(error::no_upgrade_websocket);
    }
    string_view key;
    {
        auto const it = req.find(http::field::sec_websocket_key);
        if(it == req.end())
            return err(error::no_sec_key);
        key = it->value();
        if(key.size() > detail::sec_ws_key_type::max_size_n)
            return err(error::bad_sec_key);
    }
    {
        auto const it = req.find(http::field::sec_websocket_version);
        if(it == req.end())
            return err(error::no_sec_version);
        if(it->value() != "13")
        {
            response_type res;
            res.result(http::status::upgrade_required);
            res.version(req.version());
            res.set(http::field::sec_websocket_version, "13");
            result = error::bad_sec_version;
            res.body() = result.message();
            res.prepare_payload();
            decorate(res);
            return res;
        }
    }

    response_type res;
    res.result(http::status::switching_protocols);
    res.version(req.version());
    res.set(http::field::upgrade, "websocket");
    res.set(http::field::connection, "upgrade");
    {
        detail::sec_ws_accept_type acc;
        detail::make_sec_ws_accept(acc, key);
        res.set(http::field::sec_websocket_accept, acc);
    }
    this->build_response_pmd(res, req);
    decorate(res);
    result = {};
    return res;
}

//------------------------------------------------------------------------------

/** Respond to an HTTP request
*/
template<class NextLayer, bool deflateSupported>
template<class Handler>
class stream<NextLayer, deflateSupported>::response_op
    : public beast::stable_async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    boost::weak_ptr<impl_type> wp_;
    error_code result_; // must come before res_
    response_type& res_;

public:
    template<
        class Handler_,
        class Body, class Allocator,
        class Decorator>
    response_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        http::request<Body,
            http::basic_fields<Allocator>> const& req,
        Decorator const& decorator,
        bool cont = false)
        : stable_async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , res_(beast::allocate_stable<response_type>(*this,
            sp->build_response(req, decorator, result_)))
    {
        (*this)({}, 0, cont);
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
            impl.change_status(status::handshake);
            impl.update_timer(this->get_executor());

            // Send response
            BOOST_ASIO_CORO_YIELD
            http::async_write(
                impl.stream(), res_, std::move(*this));
            if(impl.check_stop_now(ec))
                goto upcall;
            if(! ec)
                ec = result_;
            if(! ec)
            {
                impl.do_pmd_config(res_);
                impl.open(role_type::server);
            }
        upcall:
            this->complete(cont, ec);
        }
    }
};

//------------------------------------------------------------------------------

// read and respond to an upgrade request
//
template<class NextLayer, bool deflateSupported>
template<class Handler, class Decorator>
class stream<NextLayer, deflateSupported>::accept_op
    : public beast::stable_async_base<
        Handler, beast::executor_type<stream>>
    , public asio::coroutine
{
    boost::weak_ptr<impl_type> wp_;
    http::request_parser<http::empty_body>& p_;
    Decorator d_;

public:
    template<class Handler_, class Buffers>
    accept_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        Decorator const& decorator,
        Buffers const& buffers)
        : stable_async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , p_(beast::allocate_stable<
            http::request_parser<http::empty_body>>(*this))
        , d_(decorator)
    {
        auto& impl = *sp;
        error_code ec;
        auto const mb =
            beast::detail::dynamic_buffer_prepare(
            impl.rd_buf, buffer_bytes(buffers),
                ec, error::buffer_overflow);
        if(! ec)
            impl.rd_buf.commit(
                net::buffer_copy(*mb, buffers));
        (*this)(ec);
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
            impl.change_status(status::handshake);
            impl.update_timer(this->get_executor());

            // The constructor could have set ec
            if(ec)
                goto upcall;

            BOOST_ASIO_CORO_YIELD
            http::async_read(impl.stream(),
                impl.rd_buf, p_, std::move(*this));
            if(ec == http::error::end_of_stream)
                ec = error::closed;
            if(impl.check_stop_now(ec))
                goto upcall;

            {
                // Arguments from our state must be
                // moved to the stack before releasing
                // the handler.
                auto const req = p_.release();
                auto const decorator = d_;
                response_op<Handler>(
                    this->release_handler(),
                        sp, req, decorator, true);
                return;
            }

        upcall:
            this->complete(cont, ec);
        }
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_response_op
{
    template<
        class AcceptHandler,
        class Body, class Allocator,
        class Decorator>
    void
    operator()(
        AcceptHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        http::request<Body,
            http::basic_fields<Allocator>> const* m,
        Decorator const& d)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<AcceptHandler,
                void(error_code)>::value,
            "AcceptHandler type requirements not met");

        response_op<
            typename std::decay<AcceptHandler>::type>(
                std::forward<AcceptHandler>(h), sp, *m, d);
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_accept_op
{
    template<
        class AcceptHandler,
        class Decorator,
        class Buffers>
    void
    operator()(
        AcceptHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        Decorator const& d,
        Buffers const& b)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<AcceptHandler,
                void(error_code)>::value,
            "AcceptHandler type requirements not met");

        accept_op<
            typename std::decay<AcceptHandler>::type,
            Decorator>(
                std::forward<AcceptHandler>(h),
                sp,
                d,
                b);
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class Body, class Allocator,
    class Decorator>
void
stream<NextLayer, deflateSupported>::
do_accept(
    http::request<Body,
        http::basic_fields<Allocator>> const& req,
    Decorator const& decorator,
    error_code& ec)
{
    impl_->change_status(status::handshake);

    error_code result;
    auto const res = impl_->build_response(req, decorator, result);
    http::write(impl_->stream(), res, ec);
    if(ec)
        return;
    ec = result;
    if(ec)
    {
        // VFALCO TODO Respect keep alive setting, perform
        //             teardown if Connection: close.
        return;
    }
    impl_->do_pmd_config(res);
    impl_->open(role_type::server);
}

template<class NextLayer, bool deflateSupported>
template<class Buffers, class Decorator>
void
stream<NextLayer, deflateSupported>::
do_accept(
    Buffers const& buffers,
    Decorator const& decorator,
    error_code& ec)
{
    impl_->reset();
    auto const mb =
        beast::detail::dynamic_buffer_prepare(
        impl_->rd_buf, buffer_bytes(buffers), ec,
            error::buffer_overflow);
    if(ec)
        return;
    impl_->rd_buf.commit(net::buffer_copy(*mb, buffers));

    http::request_parser<http::empty_body> p;
    http::read(next_layer(), impl_->rd_buf, p, ec);
    if(ec == http::error::end_of_stream)
        ec = error::closed;
    if(ec)
        return;
    do_accept(p.get(), decorator, ec);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
accept()
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    error_code ec;
    accept(ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
accept(error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    do_accept(
        net::const_buffer{},
        &default_decorate_res, ec);
}

template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence>
typename std::enable_if<! http::detail::is_header<
    ConstBufferSequence>::value>::type
stream<NextLayer, deflateSupported>::
accept(ConstBufferSequence const& buffers)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    error_code ec;
    accept(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}
template<class NextLayer, bool deflateSupported>
template<class ConstBufferSequence>
typename std::enable_if<! http::detail::is_header<
    ConstBufferSequence>::value>::type
stream<NextLayer, deflateSupported>::
accept(
    ConstBufferSequence const& buffers, error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    do_accept(buffers, &default_decorate_res, ec);
}


template<class NextLayer, bool deflateSupported>
template<class Body, class Allocator>
void
stream<NextLayer, deflateSupported>::
accept(
    http::request<Body,
        http::basic_fields<Allocator>> const& req)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    error_code ec;
    accept(req, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
template<class Body, class Allocator>
void
stream<NextLayer, deflateSupported>::
accept(
    http::request<Body,
        http::basic_fields<Allocator>> const& req,
    error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    impl_->reset();
    do_accept(req, &default_decorate_res, ec);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<
    class AcceptHandler>
BOOST_BEAST_ASYNC_RESULT1(AcceptHandler)
stream<NextLayer, deflateSupported>::
async_accept(
    AcceptHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    impl_->reset();
    return net::async_initiate<
        AcceptHandler,
        void(error_code)>(
            run_accept_op{},
            handler,
            impl_,
            &default_decorate_res,
            net::const_buffer{});
}

template<class NextLayer, bool deflateSupported>
template<
    class ResponseDecorator,
    class AcceptHandler>
BOOST_BEAST_ASYNC_RESULT1(AcceptHandler)
stream<NextLayer, deflateSupported>::
async_accept_ex(
    ResponseDecorator const& decorator,
    AcceptHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    impl_->reset();
    return net::async_initiate<
        AcceptHandler,
        void(error_code)>(
            run_accept_op{},
            handler,
            impl_,
            decorator,
            net::const_buffer{});
}

template<class NextLayer, bool deflateSupported>
template<
    class ConstBufferSequence,
    class AcceptHandler>
BOOST_BEAST_ASYNC_RESULT1(AcceptHandler)
stream<NextLayer, deflateSupported>::
async_accept(
    ConstBufferSequence const& buffers,
    AcceptHandler&& handler,
    typename std::enable_if<
        ! http::detail::is_header<
        ConstBufferSequence>::value>::type*
)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    impl_->reset();
    return net::async_initiate<
        AcceptHandler,
        void(error_code)>(
            run_accept_op{},
            handler,
            impl_,
            &default_decorate_res,
            buffers);
}

template<class NextLayer, bool deflateSupported>
template<
    class ConstBufferSequence,
    class ResponseDecorator,
    class AcceptHandler>
BOOST_BEAST_ASYNC_RESULT1(AcceptHandler)
stream<NextLayer, deflateSupported>::
async_accept_ex(
    ConstBufferSequence const& buffers,
    ResponseDecorator const& decorator,
    AcceptHandler&& handler,
    typename std::enable_if<
        ! http::detail::is_header<
        ConstBufferSequence>::value>::type*)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    impl_->reset();
    return net::async_initiate<
        AcceptHandler,
        void(error_code)>(
            run_accept_op{},
            handler,
            impl_,
            decorator,
            buffers);
}

template<class NextLayer, bool deflateSupported>
template<
    class Body, class Allocator,
    class AcceptHandler>
BOOST_BEAST_ASYNC_RESULT1(AcceptHandler)
stream<NextLayer, deflateSupported>::
async_accept(
    http::request<Body, http::basic_fields<Allocator>> const& req,
    AcceptHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    impl_->reset();
    return net::async_initiate<
        AcceptHandler,
        void(error_code)>(
            run_response_op{},
            handler,
            impl_,
            &req,
            &default_decorate_res);
}

template<class NextLayer, bool deflateSupported>
template<
    class Body, class Allocator,
    class ResponseDecorator,
    class AcceptHandler>
BOOST_BEAST_ASYNC_RESULT1(AcceptHandler)
stream<NextLayer, deflateSupported>::
async_accept_ex(
    http::request<Body, http::basic_fields<Allocator>> const& req,
    ResponseDecorator const& decorator,
    AcceptHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    impl_->reset();
    return net::async_initiate<
        AcceptHandler,
        void(error_code)>(
            run_response_op{},
            handler,
            impl_,
            &req,
            decorator);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class ResponseDecorator>
void
stream<NextLayer, deflateSupported>::
accept_ex(ResponseDecorator const& decorator)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(ResponseDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    error_code ec;
    accept_ex(decorator, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
template<class ResponseDecorator>
void
stream<NextLayer, deflateSupported>::
accept_ex(ResponseDecorator const& decorator, error_code& ec)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(ResponseDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    do_accept(
        net::const_buffer{},
        decorator, ec);
}

template<class NextLayer, bool deflateSupported>
template<
    class ConstBufferSequence,
    class ResponseDecorator>
typename std::enable_if<! http::detail::is_header<
    ConstBufferSequence>::value>::type
stream<NextLayer, deflateSupported>::
accept_ex(
    ConstBufferSequence const& buffers,
    ResponseDecorator const &decorator)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(ResponseDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    error_code ec;
    accept_ex(buffers, decorator, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
template<
    class ConstBufferSequence,
    class ResponseDecorator>
typename std::enable_if<! http::detail::is_header<
    ConstBufferSequence>::value>::type
stream<NextLayer, deflateSupported>::
accept_ex(
    ConstBufferSequence const& buffers,
    ResponseDecorator const& decorator,
    error_code& ec)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(ResponseDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    static_assert(net::is_const_buffer_sequence<
        ConstBufferSequence>::value,
            "ConstBufferSequence type requirements not met");
    do_accept(buffers, decorator, ec);
}

template<class NextLayer, bool deflateSupported>
template<
    class Body, class Allocator,
    class ResponseDecorator>
void
stream<NextLayer, deflateSupported>::
accept_ex(
    http::request<Body,
        http::basic_fields<Allocator>> const& req,
    ResponseDecorator const& decorator)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(ResponseDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    error_code ec;
    accept_ex(req, decorator, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
template<
    class Body, class Allocator,
    class ResponseDecorator>
void
stream<NextLayer, deflateSupported>::
accept_ex(
    http::request<Body,
        http::basic_fields<Allocator>> const& req,
    ResponseDecorator const& decorator,
    error_code& ec)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(ResponseDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_response_decorator<
        ResponseDecorator>::value,
            "ResponseDecorator requirements not met");
    impl_->reset();
    do_accept(req, decorator, ec);
}

} // websocket
} // beast
} // boost

#endif

/* accept.hpp
45vhoz2EA+GJofbT7b7kXPXigjmZ4fcmXqYOHS1hG/j0XjWuA8LqZ77ep+3X29SNeeJu7HOoyyrb07SJxeLe1+fQJqpsN/M8FYi7s9P3U+QZmin+7cK/lUIcO24Dc5EdebF5BnDzpIq7i+t3AkYQZqHE3cx3KOVLtTfnhvdrzJm98CBlf+XBymTl6Hj7XP+qPzOkq8IzUxL9zJhnJP8PtZn/hPO5nc/hdju3+68/n/sROZ/7A6tThwXJcRd0vG/yI+PrtJ/8953D7Xwu+D/zfO4kS/uDsHbI8kdA2+GQ4XFYHOJQWAsOg/q9au3DSF+vwveq5yOXCBfAnvBouB88Bg6Dx8JxcAnMhCfABXApPBOeDFfDhfBWuBzeA08zv6/vTviww+8Th5wnvgJ2gSthV3g27A/XwIHwXE3H+XAGXAcXwYvgifAcuBFeAjfBS6F+31rfIZJXFb5vPRK5enAUbAbHwL3haA2/xbR/8m6Q8Hvw95Uafrzm3xFwAJwIJ8AjYRpMh4VwCiyBU2EpnKb5lgGvgplwM5wOH4Iz4NMwC74Ps+FnMA/GkIYc2A0WwD6wECbDIjgQFsN53veGvTOEd8EZwp9cWtuK2Vjb6oFNxS7euOvnrnfN+H9WXm41jf+TqzD+ty4KH//z239g/J/0sfP4f5l+n3+M9uOH6Lgt5kLt75rf1HFbRua0vIxMx28GDfVpOGLZz6rrNFZT/0YiPwZ3K3EfxIisVvh4zXxjLkH8k61O+Gu/V+OIcfx+z2jbnztK4nfq05/063fobtV+Ye/K8os+XH+HsdPgqLFTStTYKbWS78J9EnDO43XrXfI4M7eyPCZcpXmMf2QeX7++8jzetL5CHhNHpXmMv3Meb/mb8niV6h+OwDbApqgea+s65zxWPZZbHmu4FJ7NeuF5bL6N9Yr472914H/Ndw3T3EnvoH57SvixuJ8V90DC13bSYal8rCnDp8Q92OqMfFSZROipCGfGaDRLEWVzcxXGRX+kbHScFDEOSo8oq8gx9jbVHUzU52E89jl+b7FLmyNj7KK8tLxc12dCww6yekc+E6aOl4r/geRfLVNeiytpR1KM/3DGDTGSnylR+Tmhmuq6jj1d63an2trH1Pware1Hklv7gW7NvW5rOO6rqxXj1H6ofyNTVweE3KQm0aH9SDHyo9FE1HXUo402MjGmPvcX98HU/1qRdbSa8rSq7ceh9rf0NI8HafvRF7uY+NMviMpjo8+ie1BAfqMKyrLcdT8FEj7J1nMRnz7X3HOAcLdxv4324J2g+qwES0wV9FnyOxH1pEmdMuG7sI2wm1Unt9XpHtx1cqaNe07CXYImtaam344rzllPZ/z3Mt/Se1HclzIuQwvKPdcqv2fR4d3I3+0aU/bwtrgd50FIbzN2ndHb7JSOz86nZ+o4l7Xlkk9ayq5lHBtVxpZDGX9L3R5RDWW8cfcy4Q6a9tbYhch+sdYl7SS9qJL66T9P9Iuadjue2DDdXl6OpeXbENYS+UZGDzvqT9yT/T7oXb9MuMDHfcFxqnNNOi/qnnZC55omYTuqztWOq4uTzlX9+hs9ar64k5x0rio70OhAHd7dKtPXfNt5lri7+ty+cXuq+D+qbp911Pmiq414rxOnea8vdtG95iF7lKY95H+76FpD+VauZ71R/D8J+2Ylb9Uwve8M8e/sc9TVqk46U2Q6+JKpAw3C6vdSeCN2s85dfIm9hb+3qH5W5cQuicNdhf5I6HknPyKe93QHPW1WlJ42P6p/Mi+qf7L4H6in/ad9R/FX0dOu/PjB8/ZZ1PaXuT+tPejYa/c4y/uOYlX1tNZF7nraPVVPOxjWgkNUz5hq6fgVjpFwWDhcw70=
*/