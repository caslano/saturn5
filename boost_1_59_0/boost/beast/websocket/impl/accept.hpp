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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_accept"));

                http::async_write(
                    impl.stream(), res_, std::move(*this));
            }
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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_accept"));

                http::async_read(impl.stream(),
                    impl.rd_buf, p_, std::move(*this));
            }
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
    BOOST_BEAST_ASYNC_TPARAM1 AcceptHandler>
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
    class ConstBufferSequence,
    BOOST_BEAST_ASYNC_TPARAM1 AcceptHandler>
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
    class Body, class Allocator,
    BOOST_BEAST_ASYNC_TPARAM1 AcceptHandler>
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

} // websocket
} // beast
} // boost

#endif

/* accept.hpp
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
*/