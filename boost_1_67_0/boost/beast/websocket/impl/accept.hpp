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
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
*/