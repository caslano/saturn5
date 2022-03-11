//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_HANDSHAKE_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_HANDSHAKE_HPP

#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/beast/websocket/detail/type_traits.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/core/async_base.hpp>
#include <boost/beast/core/flat_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>
#include <memory>

namespace boost {
namespace beast {
namespace websocket {

//------------------------------------------------------------------------------

// send the upgrade request and process the response
//
template<class NextLayer, bool deflateSupported>
template<class Handler>
class stream<NextLayer, deflateSupported>::handshake_op
    : public beast::stable_async_base<Handler,
        beast::executor_type<stream>>
    , public asio::coroutine
{
    struct data
    {
        // VFALCO This really should be two separate
        //        composed operations, to save on memory
        request_type req;
        http::response_parser<
            typename response_type::body_type> p;
        flat_buffer fb;
        bool overflow = false; // could be a member of the op

        explicit
        data(request_type&& req_)
            : req(std::move(req_))
        {
        }
    };

    boost::weak_ptr<impl_type> wp_;
    detail::sec_ws_key_type key_;
    response_type* res_p_;
    data& d_;

public:
    template<class Handler_>
    handshake_op(
        Handler_&& h,
        boost::shared_ptr<impl_type> const& sp,
        request_type&& req,
        detail::sec_ws_key_type key,
        response_type* res_p)
        : stable_async_base<Handler,
            beast::executor_type<stream>>(
                std::forward<Handler_>(h),
                    sp->stream().get_executor())
        , wp_(sp)
        , key_(key)
        , res_p_(res_p)
        , d_(beast::allocate_stable<data>(
            *this, std::move(req)))
    {
        sp->reset(); // VFALCO I don't like this
        (*this)({}, 0, false);
    }

    void
    operator()(
        error_code ec = {},
        std::size_t bytes_used = 0,
        bool cont = true)
    {
        boost::ignore_unused(bytes_used);
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

            // write HTTP request
            impl.do_pmd_config(d_.req);
            BOOST_ASIO_CORO_YIELD
            http::async_write(impl.stream(),
                d_.req, std::move(*this));
            if(impl.check_stop_now(ec))
                goto upcall;

            // read HTTP response
            BOOST_ASIO_CORO_YIELD
            http::async_read(impl.stream(),
                impl.rd_buf, d_.p,
                    std::move(*this));
            if(ec == http::error::buffer_overflow)
            {
                // If the response overflows the internal
                // read buffer, switch to a dynamically
                // allocated flat buffer.

                d_.fb.commit(net::buffer_copy(
                    d_.fb.prepare(impl.rd_buf.size()),
                    impl.rd_buf.data()));
                impl.rd_buf.clear();

                BOOST_ASIO_CORO_YIELD
                http::async_read(impl.stream(),
                    d_.fb, d_.p, std::move(*this));

                if(! ec)
                {
                    // Copy any leftovers back into the read
                    // buffer, since this represents websocket
                    // frame data.

                    if(d_.fb.size() <= impl.rd_buf.capacity())
                    {
                        impl.rd_buf.commit(net::buffer_copy(
                            impl.rd_buf.prepare(d_.fb.size()),
                            d_.fb.data()));
                    }
                    else
                    {
                        ec = http::error::buffer_overflow;
                    }
                }

                // Do this before the upcall
                d_.fb.clear();
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // success
            impl.reset_idle();
            impl.on_response(d_.p.get(), key_, ec);
            if(res_p_)
                swap(d_.p.get(), *res_p_);

        upcall:
            this->complete(cont ,ec);
        }
    }
};

template<class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::
    run_handshake_op
{
    template<class HandshakeHandler>
    void operator()(
        HandshakeHandler&& h,
        boost::shared_ptr<impl_type> const& sp,
        request_type&& req,
        detail::sec_ws_key_type key,
        response_type* res_p)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<HandshakeHandler,
                void(error_code)>::value,
            "HandshakeHandler type requirements not met");

        handshake_op<
            typename std::decay<HandshakeHandler>::type>(
                std::forward<HandshakeHandler>(h),
                    sp, std::move(req), key, res_p);
    }
};

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator>
void
stream<NextLayer, deflateSupported>::
do_handshake(
    response_type* res_p,
    string_view host,
    string_view target,
    RequestDecorator const& decorator,
    error_code& ec)
{
    auto& impl = *impl_;
    impl.change_status(status::handshake);
    impl.reset();
    detail::sec_ws_key_type key;
    {
        auto const req = impl.build_request(
            key, host, target, decorator);
        impl.do_pmd_config(req);
        http::write(impl.stream(), req, ec);
    }
    if(impl.check_stop_now(ec))
        return;
    http::response_parser<
        typename response_type::body_type> p;
    http::read(next_layer(), impl.rd_buf, p, ec);
    if(ec == http::error::buffer_overflow)
    {
        // If the response overflows the internal
        // read buffer, switch to a dynamically
        // allocated flat buffer.

        flat_buffer fb;
        fb.commit(net::buffer_copy(
            fb.prepare(impl.rd_buf.size()),
            impl.rd_buf.data()));
        impl.rd_buf.clear();

        http::read(next_layer(), fb, p, ec);;

        if(! ec)
        {
            // Copy any leftovers back into the read
            // buffer, since this represents websocket
            // frame data.

            if(fb.size() <= impl.rd_buf.capacity())
            {
                impl.rd_buf.commit(net::buffer_copy(
                    impl.rd_buf.prepare(fb.size()),
                    fb.data()));
            }
            else
            {
                ec = http::error::buffer_overflow;
            }
        }
    }
    if(impl.check_stop_now(ec))
        return;

    impl.on_response(p.get(), key, ec);
    if(impl.check_stop_now(ec))
        return;

    if(res_p)
        *res_p = p.release();
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class HandshakeHandler>
BOOST_BEAST_ASYNC_RESULT1(HandshakeHandler)
stream<NextLayer, deflateSupported>::
async_handshake(
    string_view host,
    string_view target,
    HandshakeHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    detail::sec_ws_key_type key;
    auto req = impl_->build_request(
        key, host, target, &default_decorate_req);
    return net::async_initiate<
        HandshakeHandler,
        void(error_code)>(
            run_handshake_op{},
            handler,
            impl_,
            std::move(req),
            key,
            nullptr);
}

template<class NextLayer, bool deflateSupported>
template<class HandshakeHandler>
BOOST_BEAST_ASYNC_RESULT1(HandshakeHandler)
stream<NextLayer, deflateSupported>::
async_handshake(
    response_type& res,
    string_view host,
    string_view target,
    HandshakeHandler&& handler)
{
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    detail::sec_ws_key_type key;
    auto req = impl_->build_request(
        key, host, target, &default_decorate_req);
    return net::async_initiate<
        HandshakeHandler,
        void(error_code)>(
            run_handshake_op{},
            handler,
            impl_,
            std::move(req),
            key,
            &res);
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
handshake(string_view host,
    string_view target)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    error_code ec;
    handshake(
        host, target, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
handshake(response_type& res,
    string_view host,
        string_view target)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    error_code ec;
    handshake(res, host, target, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
handshake(string_view host,
    string_view target, error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    do_handshake(nullptr,
        host, target, &default_decorate_req, ec);
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
handshake(response_type& res,
    string_view host,
        string_view target,
            error_code& ec)
{
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    do_handshake(&res,
        host, target, &default_decorate_req, ec);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator>
void
stream<NextLayer, deflateSupported>::
handshake_ex(string_view host,
    string_view target,
        RequestDecorator const& decorator)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(RequestDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_request_decorator<
            RequestDecorator>::value,
        "RequestDecorator requirements not met");
    error_code ec;
    handshake_ex(host, target, decorator, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator>
void
stream<NextLayer, deflateSupported>::
handshake_ex(response_type& res,
    string_view host,
        string_view target,
            RequestDecorator const& decorator)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(RequestDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_request_decorator<
            RequestDecorator>::value,
        "RequestDecorator requirements not met");
    error_code ec;
    handshake_ex(res, host, target, decorator, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
}

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator>
void
stream<NextLayer, deflateSupported>::
handshake_ex(string_view host,
    string_view target,
        RequestDecorator const& decorator,
            error_code& ec)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(RequestDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_request_decorator<
            RequestDecorator>::value,
        "RequestDecorator requirements not met");
    do_handshake(nullptr,
        host, target, decorator, ec);
}

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator>
void
stream<NextLayer, deflateSupported>::
handshake_ex(response_type& res,
    string_view host,
        string_view target,
            RequestDecorator const& decorator,
                error_code& ec)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(RequestDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_sync_stream<next_layer_type>::value,
        "SyncStream type requirements not met");
    static_assert(detail::is_request_decorator<
            RequestDecorator>::value,
        "RequestDecorator requirements not met");
    do_handshake(&res,
        host, target, decorator, ec);
}

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator, class HandshakeHandler>
BOOST_BEAST_ASYNC_RESULT1(HandshakeHandler)
stream<NextLayer, deflateSupported>::
async_handshake_ex(string_view host,
    string_view target,
        RequestDecorator const& decorator,
            HandshakeHandler&& handler)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(RequestDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(detail::is_request_decorator<
            RequestDecorator>::value,
        "RequestDecorator requirements not met");
    detail::sec_ws_key_type key;
    auto req = impl_->build_request(
        key, host, target, decorator);
    return net::async_initiate<
        HandshakeHandler,
        void(error_code)>(
            run_handshake_op{},
            handler,
            impl_,
            std::move(req),
            key,
            nullptr);
}

template<class NextLayer, bool deflateSupported>
template<class RequestDecorator, class HandshakeHandler>
BOOST_BEAST_ASYNC_RESULT1(HandshakeHandler)
stream<NextLayer, deflateSupported>::
async_handshake_ex(response_type& res,
    string_view host,
        string_view target,
            RequestDecorator const& decorator,
                HandshakeHandler&& handler)
{
#ifndef BOOST_BEAST_ALLOW_DEPRECATED
    static_assert(sizeof(RequestDecorator) == 0,
        BOOST_BEAST_DEPRECATION_STRING);
#endif
    static_assert(is_async_stream<next_layer_type>::value,
        "AsyncStream type requirements not met");
    static_assert(detail::is_request_decorator<
            RequestDecorator>::value,
        "RequestDecorator requirements not met");
    detail::sec_ws_key_type key;
    auto req = impl_->build_request(
        key, host, target, decorator);
    return net::async_initiate<
        HandshakeHandler,
        void(error_code)>(
            run_handshake_op{},
            handler,
            impl_,
            std::move(req),
            key,
            &res);
}

} // websocket
} // beast
} // boost

#endif

/* handshake.hpp
4ygm60oT4JGjXtqWzXr+fq/AR73wVvnjvFQWFha19vPzc6n3B/5RoiibPNIYsnD+veLKAoXDDeuOqN2Pw5fYSXCj6jjv28IEmXWp3oZyezhu6NhxNzRmRhw6Qr5/4rKxbppWVldIowSv8xQF67OzcuRKW6urqvRFpk1LQNKwaCAZtvFqh2E+Iu/v72C5PBQsJCwMDLrtJSUl+PRB8OGTVHMiBZHlvg3Kz1xFKhMHxlHMMVKZWw1/dnsbACiF4OYR94uQphUKZRMjmaygIqEgKgN7RISceNQFY6qBESFM/1ypPb+8ZCT9fqvvY4lq3pl73LnTMzJwE9MoY0MtfXxsbG58HX1cXFx6fBs13Wjw8fB4UxyBYBQaluZXJH9EiCfRPnOUDH67gH/4ftCTWQKHXA8EhRwCYYQ4FQ7Cd3Z9fX11fn4+dy7PT0CgXwUADNLcT8Pf1PHBOOxS0l0BTtFSP8aRhxjNwSJp5ZNlFQaKxisrK6tLS0urC2jKM861bdwT7ghRF2Biar5n8dS+xuj2MsYudxwbZsUQ7awky3n9BobapvvtWAmpPEV8VSaR1y8cEEoktLm5eRiTybh0wdpaURXWN1QAcSOrJLUO1/16OHq8A3mnrgeAQPk6eqpzC9CfD4tN3QgXScx9fWPDg5OT0525f9RC9e8fhJrkr5b6n/fDBNnvLPAIzoTUKoPLnxNAIrlGcdfpFO+6RwcFgfJ55jLj6UyOKiCRhktYJCxgEDL/Q7Jn1QE9l46ttmifP0rjOwfyxfrjX1skcM4uHTysuMxwaFJRdF1Aki/RuFztzFzY8luKJBUrUYw+hF87QNAdpj0O52q+iabygAcgkCP4Yq6qpvTCoczyi1AotJEo+poFxWSYCDgEZbuGBKFbhkEbSpYufJPy33aZd5eJTanhX3UdG1duTGBhG027N0ul811WG80yrIDz71VKXzZJXxlA41pD997F7zzQsZoTkBglJb2ufiDFEs/lag3GLJAYVuoKzFwI+kyo8VtAf6sxFq5BYKo3o9UkuPiJHIQtkq+vNlpcrtebKkQ/EbClvtSfbSAoWti/TOrfaPjnlxdkFiVJcNDFc/xiTT+ajL8/36yAhmEg/0bFoMHBhAmyuuu6wHJcVut3fFxFkDk5HzlPqgLDbSKK+bMSAEV4AhZ5TSTT8paXrhOrhKnsIMlV27fPCDusA9q/n5XcLHjOhd5RsbxbFMkW3anZ0qvW6pIRB2O1YfGzsyM4b6a6XSUN/rgI9EH/hpTLFUEfrJitJCw0RQer1foionRPNbIsHbJcNUE/k7SZG4d1nItHXHcN0GFxhjWnTtS7OUstbedQ6HoQNPr0omO5Eqw6GkOmQw917u37oTS/b7j0pamv3xmB+NaA+qwLBMUVd2Yg3zxbucPbt0POxyb+8dnNxLUZ+GhvG/1ayfnO/UOFrDxxt1DUu+cZFQ98qUaj6ZwUbafGkq9SJEJdsZ0dF8T9Ma9SG48cRu/vvcEhjWViTL3m6/QGgrXWIYApSi2GZuidsryOqzxyW/f+crnYOFgR+X5Oc1OgMKBV/NupAfMsmqSaorVIoVFj1NhojMTAmRn19dsQ8MONskfugIZ4PpP7ulgO7tPiYprvssCDIQYeS3B6qdToJFmcXpvJyrvbFQqYrjK8PmvshXb1hazZvL5GoVA6dzU2VbRGluNcqdHpEdoYrLyTsfkaYtlR2ZSFpNgoachckP5wASIwj2yp+LdNxSOk4Fc+FIE+k8nlck3DIpdUQ296yE1heqlKCKJQ9J7tSfTI/cp/qtPD+sjzbHoKjKDRHJjNgtMJ6yekWiCKKWQq9+++zaHWnOH+MiEDaWUyHRXrWQcNC46bYvG6JQew5C5WSGhBj1pIegNmKNX9qHM8ANTHDzS3EdduEJFWffTG/TcoXMpATqgvYZw0dxDEunmfSCUoZIwyUKkPrGsEno9RJCf5RGDcW7BOHdOUHo6nLJYczZs3nR8HBP5BYWyfDmEohO3sPlvlOTzR5j0c7wRPa9jAdcHzoZh7eEifAgJN8E+qi7+8Svbf2+PKNwKeefuBIwDiXEqxmrOcM1dxczfiuAiacj255R25ciHkxm6p0EWm1smIJli+F8mY8ROsVZtQbu3fhb76VEXKQlFYOPegBKFod0asy2qbLRhvDnrgEtB/dbxEavTK+63kPI73qAzUWk1wFjj/Lp4dnnAKylZDAfnl4CDYJOeyR31KC3gcNxN9877SKwR7RMKNIX0akPSB/EsPckI3E4OBM3mNtokbJI17RBKXkWWhrMhzsIwz74CAZ66NIdjl/ojVjvDr/ZtxSCTPdtWvQLvntgWh0HH/puV7v7w+xi/Bd18hNzAZet7h8NV02W+LWETAT+AVag8HbW22SpNZm0bR5Qf2LwMRiREJwuV70zPtuU6f9fqoyvvLvwsatQwlEhQX/M4wr4gfrJEkD3QI9SJ2VbrxZdDQ3kCuCGt+Oate3l7Bpvj0GFLe3c8iibNz5Qi7FX9inZbFGMLMA0zTMM1LPsl5UdTBQkoNThHOVDlnCM6lTSnmOvuat6D841qRYucyeQY2ymQOm//v4IhlaQkfaQG9lstpVgB8aoUuMCvhPg5Yt3WaaRub+UZnfKpdbwOeDnrD576A4fM2nUFINzUDqEARy6lCz9VYEsPaDIaYVtoYrqUpMI6RXy7euAzg+KejXdDJpKURgERrKzrjjvgfdxfAYBXjyQTOejeT489niV7HI3K69iT3Q5Bej0qXiC6HRwsrwG5bRavBvJh81VT8F3v/w6pBjNWyNbrJdrScxneTSEIF95ThlMRG47xn9h+FSmwZ7yXywUjowornDZseY+kyVyenyVLEAGLrRntMpsqmgegcHcRmzxeNvJPgi36pJq5eijZnBILg5wzM4JcMPTJn/no2pSVfkTRc3DxjUY/S7WU882azKRzI2hTYOGNFs5Q1Ho9mX3vt1Jd3Pogp9QEpkbZa/fZnM3QFOkCT0zHynM3ykKhu1rdo/vu9scMjs+CdL8oWmfHFsHC7hasH4tBiRcnBw5hihfJzYDh2/qy5TMxH+bpovz2WZzCHF1fjn2FYvYOVbpxmzees2U4D0dSiUcnYXCJzV2cNjHQuSfdiP6LFSw0XncjFleA80AZpjbuQYKGpZNw854VnuQY9D1YW4GGrcoOMybwrLsGPni9J19edH9JFXA9P1dfjliCOGlel0vBi/7+q/+YnuMjxpUNLWSs5bnuB0U0vvE7anS6cS73o5Eda+O1S7a8SakBvFoghFKj+PBHrH+IUK4Lje9qyFtnbsjNs0qzpkwK143fyWb6e84VUpUtMLeH4NIMUr5rrtlZxwNBm4YOl0EEQRx3ceCaOmufcNc/91S3zsjcoPcftiNbrqhc6Pdvw+ak9rbKBf6B7/5JbmJe3e/NCsVOwSqM9dDJvvZkTxTcaH5qgkK344i2fO0xJMmbcIh7lhUbwO0DWL5Uua/Ta6KdLSlWZUgdmAIjFQFml/rcFv4m/7HWckHdhkoJNASCiHXWadJf3BQp1tqc2ue/zgkIsOdU+leccQCeuh0wgzw+e22jx3nSYdQMHvfOaHL5C6QusBENi3qB3ZW8V1hxAnW0f1XkiX8C3hq8Fz2A97wVHkC7PEpqWAoXTMwJkMxSO6tB4PFqsCAdnjgpsuKku4scTw4uzrP0eNntX8EMJGZk35DCwWx+kZ5rX5Y5X9I3bDIXTdAGaKJoDtYQbSVgQXnVwFf8Q3eYwMP/ixUDjOYAfXN4+LvIPXMzyPbR/4C+gUQcnT7M/vUpHt6wCHd6dVGkxNsHH4qHabip9sReqrS2Olqwx+nEfIIU+KpMn94ecqKjrpRA+jEvm96bcw8APJLj5T4Pu4izrxa5fhNCMpAyUFznunQ80DkPiO34txWP3aeDsy6aSnileRa1wXaQWQTP9Vj3L5esEfPDG0MAVltvIgQvvpJlbSfAYDUAVZr/UejpryVVRD41a6pXZc3HbDIAwjBrZsKd0JI/0jdcKvtPivwi3H2wwToWsfwz4STaB+tZN/Kuv+DsQLdmOjqc/KTVBScBCejKBdXHt6wy19m2+dvanfO+7DPOdJtOcblrPfxPiGm7cREO20XFqovUfaTC43KCHOt5ieNCWf/ZuQjy0v+57saoxdiLe/ql8arl1zA9zH2o1mS/pL6eHPwgaCjDWjR4kM0YcKYTpULZf98gCkICO9IRSip5JyR7EieK1qXaJa/2xde2b0AOKcjlZo4fZ4L3drrXcgPOA2z07+wMOp4blDhrpNwAPUcm26D5zHgo+0LAuuENZIXiTBiTBnH8b6+hzVoxdDe/Sefu2FxbjRRL5eLZXNC9TyPRdggYOWZxtvjL3vH6kn+7lCRVv9MbsMd+1skIwxddhHoRxp6M/2r/WYMKG636aBz0EQK0yyZ3q34HDsrmBnP35SD7QTv9toBp7LTV0FpxMDwMsWuk6fCMy5LSO/HxOyyW0xRNzvmdokowre95SqnP2m7K2pyc/HJOcT29qq8JovYHjARJX3J3GU+lRnISb1B8F5xQ7lSxj6/mP2x9n+dtH7veextxNKqK/6UPgd9ADGCKzwwoMtwbdi4jOOzOqf13tcQPZkuVmfvo54gMRYs6JWsPk6j1Xsl378zqQDSo6ucp4NYD19137NZPB9pLQr4wSClDfi1F0oTpkhoeL+z2PL2fRFMklOD7sPIlahS5/QBGbmHhnjsYgyKg1xOcZix8EbhnnhxJsclmtfFkIjiPwwwpahJkjCjf1yFQkckPHXiT17XZg2VSbAwtZ7rFrl0PPNTo6QOhFjccMDwavleTRzHxc7DJ8AWyCOdPR50hyr7lhGsKyIGXB2A6bi7aX6Kd8AI7LMg/tdqqeLrHyE1zBLuaA7MxFlCtLvnhCruzW7A6dHa1MXid/n4FfVqXtjF5AKJ04SSRJ4a3PaqM/q4aT3PLjAj4I+GnXQpkZGVudkf4xy0keYx5u6ppC7Fw7JtegLA0PZzlCFfWcnecxPz+aUpt3RuLh/jW75IRNO9sA6l9/AIvGj4NycPdCzFJag6FBAJoBs1nHTbftRYQsvOzPxsqEeU9r1cHloU5RyAB0qtZou3B60Ec8+7TjBrT75dhmperZBwHQiJRSYtUmssl05prr614IcHIlDu9issadVssmzrXXwU3IstNFf2frURPEDd81A8+XthxdWfydvsDfUwR25Gb2nvgyaODeLutHWJb5pvZbXGQXgZtcErpJssPDEs+mnBInVcKuME2iKjOErkpn+yQdq6Rs4wm65JgxByJ10oGm6Yqeizy5AvKHalfJABPyKHQtHLifEfozQGKTHHLlRGjUjPgwxCpx1lOeV+0q0eu4B9lGsjXdu+0XzIjfQXJsr1WcqY9k2RFYeFfXZR+aajGiSeHfTHTQ5dIfitqUimWfg4q9vB5XH9VSgx0cKkcWxoKh53tRR25DKhRffjmnE93TuYRPP8dFjJ4f+mwm/bDcZXE2Mz/VGgdNOBRZASWA0GndQN6jNWoeAp5CX4kHEj6Af+QCBDUiZ+5rFodpofkn7R/GUwsagltXFo7LEaIRYeuFUmDRvGQ4X1UTggv3wJsegkxgEM5jQ7dfLzs9AtAvvH6BHYE7ZLGX5enGvpE/mV795opoAqhf4GfoF4HuVSJwx0kJYCNC7qcr37I58OBipvsJzULUaCF+BnBzflTvU5Ty4wZy/VDsxtkOftIRgXHi1CDJ9VfvZ0ZknU1KLMsDIyCAEL44mXU6qW7j0DQzUO/RqYlzZD3bIddLFz3w5otIHiLxGxJQRNfFBq53nbN8JsalHW/bcl1JLdYJlCvNHTdQFTOcPDgea/ADMLiBNKJz/4p7a0/rVZg2Wl+2PXKWp2I83feR523oQ5avB9cMAOYu6nLkSWfQ2M0fEWzj8BxW2RgpOpmAHIhYKmXBNn+mW4Kybzwn8NSNKF2r7T7HKdPkjyZ6F435oWe3+/ZsX9vQ1d26Jt9akdt4cIFqz0Z2lGymKQTLK8mas2ABPpyYzQ2XN2sN2e4fP0f1tn68uRr5PHuiCCJ17bIDZYOwzCwhvkpw0c+v3dkXuZ8T4zZlncq2Wyk3nafV9lZvvgkm5zKijspVyU7l3Pa9T7JceItaUHTyH9xz5juWfbTpqsYGN4gB5hbPD8pP3TKr5hvN8/jlQ3xzOwENRBLLR21lZVsvnk5C8nS+iWjC3W/j0qrydEaIi80lkmZyKh2FGWFKJ7k7HxkVwFfemN3YzPSlOU8FVsoZw+ElqbiD+xC/0MYSGBML9j9DZxTjuBs+7d2ShRoq2bG6wBst2CtdDM6tfeQw4TecPaRNTFoPOlUClXQ+WmpvO6HHif6SnO+FR6Nitl9Ud2Qv9y09VLcdp38zTbMf1HB7lk+ZgYf22jX7+ghARYNyys/62sqZSSlO+sqj4qzW8Wx+rzsIPUmzrY3u3QU/aQ/3lomGxLnLwEjHyJs1kfH3xockQZhWduEdHMngDoVIHQTjOebl3EzdoaNEkTwefNbKJpI/PriFFx6BdzruQUeyvS88MTV6xnFWJcu5DGg9w0Fp9DWtG3nux6+E+FlpDNS3dBXkV5bBQ2HOO1r4LZNgD4VEgMRXgMbvKApXTo4e0O9NkMhTpffWSSXpV6sWVW1yrDeZPwc7NSiur/ao1HRv2y+n5Yns6mLPLdXKbMFlemeiETotL9/atDeeiLd1XUJQjdxMLA2KDjHbplAxzQq4eU5K3Ef6Ca9jwBXdZ5r/IHaZcdz2I18+GZz3N0PW0Nq43nT0E+N/aHSOKy8CBpWFhHLjpRK/CXoJEqQlX+2YAYstyNZUKvXRJ1kvJOVUaX6IHx0OMyB/CLfbfLXbPkhOw0i73w5yLVVb/qmOCxh6zVamK6Wr1JRgiwMTHowJap639/CeTafg66GIqW+vZu4pC5/5eAVDyjLkrysT1LD+eBUdAL7xWQlkRJiAONMKdtQboeExtI7DzvW8P6+oybbXS7X3VwQoAnqAe4PE4V44gurksw4fplJ5stlCsnZ7U8uzulK/cOLemt2j7t+FFKVADofffU58RopMp/M8Si0o09fgMIo5QI+mSDrRkPFWwB9BuzHJRgg+IS1ZXUvZNbT9SOlBwet6PAhCzexFnYjFI5leSIywYcv2n5SObdzfNQMMLVb2rDtbUndZPJWaAprq2mulfEtZMrB167c6ycJOx3crBMAJUP+ExXOazR4Q1lbuJFLQOzZLsZf9qz1L8ddH9m3FrOSfgj445Brj1vp9AAQs+9NcD9TF9xG10VjQRExDYFOVc7PUMMpw/tcRXgnOwlkiYwkOQbr6lEofL/+e46st3/RLynhnIp9GW4tZS4FIC+qw7Ah4DC8JDG6n1NizYgTaRIliGfmBTqT3tg2j44hkQklPyJY7O6ft+53fFCpKf5/f/MfOh4neAyofa4+EN4Y0icETlvhxse/rQ0V1e/hKQ4mwNAe/4miM+MzciJm60/Q4WZZZ38Q14bXbBvbArZIKGs1oyOP0cC2zZGpX2YNmTaG1wUKySoon5+bRoQa3lpubDHWMRcXAbtoMJDGlGPtYU090xebdO3S/85aimszWPvuigsUm5lkaLd2fnw19p5zInUQgYYUKl3Jb+l1jp+PgBMpZr5uvhdmvLRt0XwPVjSAhUXwqe4/WFur4HDYYjWasberlQgesoyUTFJhscnTYxAyXo7crQrwSYsiZWjlN6xYx0WDrjluWPKEaGikRs+H+KjbObeUnedrVHW5MrDdmBTAE6arkCl0fqYOL1HtPFv2hRvyffpOBap9v/T7ke72sYVzut9F7Q7P0jWTtpCySRHoULVNyJNX9obNc4C4iDJpHhUTXE+jv5IQS4IEHqXFqSsVsoyMNmTVntujrm/q4wjCvqkP/7jYul6AMnef82Q/He5RtoPHPuMklCJKHXcT60rJl6xzFrHrwIKpZnXK8qPdH/oxsl0QXR6byV+ctt4/dnw9d1bjGvKDIU/HL3bKR08z+Vxuvv4bFU+NhG+ZX6Wcf6GvNlIInvpTkBujrjYBReI7IR8Ud7GcVZaGve26ccjiZyEdnb60cheTrzvbsiASk9JMORO4LiLzzixhgM64ypR9TtJxL7KYXcYReZPvRETPw5D/353I8fVcXb4xnb2LQN+hWm6VcPeXlrU13sg92VHY3aPy63BIKFWyj04SD6b9L4Nx9UKSuoSv9UaIpoYRuYZ5GmUO4bDvP0nnMiq6qT1POkxTHPTUwKHRFthHqkodx6V4gHr6xjD1h4V2qEivIAxxVFxcXVn03bevk8YWHsClCnhpCWa6xCql9bsm5NeJvd17G104DwSuWFiZm8Glrq/mrtxef3S29JO2DKsUzwH3NajalkXvGKKKTnl1Q+tcbCTPXT3HgQcwd1yEbV/Z3EYjzqt62JJmq1br8ltQ8bWKuero9TP1DU9tWV7uX6LHRfxWMLKbXO2UD3uY9W8q+AO6zQd6bGQMaY3azpOx6cimEjjz3vYmHHPUOFXAi5l/xR6KUz7As9abZy2khgVhdKoJl7H/uHlV6cLI53xJrD/fZFBXFslbK9VQkRf+xRqSkUNwVAjKevQiYCjceb+MnuSFyQXAKK99ZeMB7HQ7obZDzGcPcHWPNC/XuCa1Nb7El4t4vpOfJlrh1MI/fWYOBQ3LQK5UJ3rqZQe7ZzJ2u5hZh3ZgzSLT5X8aGOmx2qchOeSSZ9NyfZCVKNARSNY7FuAhgjSmQeRcscM243WQ0qeyglT9qQ4ZfXCzPmMKWVHVzMePX9n9SvbV9XHfk7JNSRzXvcDxMMpE75drJAwBiUEgjwyV1C7afByLLrOp8zKE6vVVyWXOcDO3palXvCqVdqfLcrEq8MlzZIUpsn2IjUIA59iP05pKnH6NQpzpR7esQNSJp+gWdlBbcisnf8UK4AUBpZwIxWMIrppO//eFdS5R2W0uUeVtTL1QFfGnOWSZs4uvY5j3i/9cc/ufrHWCWUmVL7u7v+uaPx0VVS/XKehQ2ts5tP3q3rVfRkkNbJXNWFB7QsMcSgNL79wCM1r1xieME6eDZZseOZ1gVVydC5homr9tSNxObDHXArfIZbQFVl6EivVnGZEXNH51TnUsnOimO3ByVY3pDotWn8ZQ6Ide0RCI+e0L8hpRRB/nBEs445+bgJ4K645M=
*/