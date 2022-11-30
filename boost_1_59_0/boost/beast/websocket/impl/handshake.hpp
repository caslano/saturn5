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
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_handshake"));

                http::async_write(impl.stream(),
                    d_.req, std::move(*this));
            }
            if(impl.check_stop_now(ec))
                goto upcall;

            // read HTTP response
            BOOST_ASIO_CORO_YIELD
            {
                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::async_handshake"));

                http::async_read(impl.stream(),
                    impl.rd_buf, d_.p,
                        std::move(*this));
            }
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
                {
                    BOOST_ASIO_HANDLER_LOCATION((
                        __FILE__, __LINE__,
                        "websocket::async_handshake"));

                    http::async_read(impl.stream(),
                        d_.fb, d_.p, std::move(*this));
                }

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
    if(res_p)
        res_p->result(http::status::internal_server_error);

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

    if (res_p)
    {
        // If res_p is not null, move parser's response into it.
        *res_p = p.release();
    }
    else
    {
        // Otherwise point res_p at the response in the parser.
        res_p = &p.get();
    }

    impl.on_response(*res_p, key, ec);
}

//------------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<BOOST_BEAST_ASYNC_TPARAM1 HandshakeHandler>
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
template<BOOST_BEAST_ASYNC_TPARAM1 HandshakeHandler>
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
    res.result(http::status::internal_server_error);
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

} // websocket
} // beast
} // boost

#endif

/* handshake.hpp
RCHLRvAwAMCtDdJ6PDm/VIJOW9m/7kmoeQmVpQCOSabOIIIXUswcin1LXHY8PF1090epQnIdZ1C7sMJ2ISB9NZEM1q/FxqK3c2jhqx3XVlvFNXFZRITieOyVpLiI9xJMnpGeeGmxpQQNE3wxFgV1yzpwN6swJ8eDfxpx0ISMCZ0oXsh3MdhVcHF97NOWvrNiuoNh+sRll5zQ/VI+gLactaH0ILggBj4swQzmDENRzi9IBR08u2gcAjBlefKrEJTlagUlarmAcKYae3JyOELIGmiAuBktJu0ASaldh4lNB+Be968HCnkPXoVw+OX4x+9itBEyQFkFSGmLFBq3Raxk31WA0XIiLh6xF0wce0NnT2/27kTG6wxSmztTdvM8ntGa4bygyaIYdLXQl4Bw3f8SQvZBzNr+AB0LO2jiC6PrFzsJdax3o+HP2tJzKDOJjFU17l3QnL6qhxV92MqwoMnIwpTv87Ak3AxLQl5ad3mqnVoRsHvmvRkMkFJXBPhj7zGtRKIUApdL42ioq6cS4gTFTgSRfNTQjDGT4wkS4CWjFFxhm4H0jsi2w/Xg0GR7THmVY+89vF0hXfFcYMuXzWsy9QwIDkhlF5zY+/mm37upT/Q1IZ8jZ5hxgReSzlelMIfRmYO0/gR61cZnYxs871WFVN/S4ws37cU9zYwkLV5hK8uAI7t/Z97q8bIbETuoys+/nelVBQXBa+1dsb7RaOjIn2yY5mgH00fNAQu/vGzue0aCbo6hhhP3EU41kpCUxchzywqpBfjyhg8wt4iuO5g1Mo6XZJ5PQtPklykEI4IrWoljY0PNgZHLBgOrNfVKNww+WBNFKscUb4odJSsBtf3sG6SUlQurLrrvAN3cCBgUfVjHrtdaY7aDRBzUyvRH4ZUIUis4GMopYPf2Raa7c21C/B0Z2C9Lyzt4mIsQQguRcCPKYZ4HC6ttuvtLdAIf4cFlmJtFpMoaoSMBTsd03ZTaVfPlwf0eyg2Wj4+BgDFiM6DCpI5+O3abNEizwDG3mHHIMOXkrOeDGWV8OsVvi0MGipXdDrQBm9WoaJ8aMsC+nDOhDMzneRGCQ2InU6hyV/MztLNiL/Fcc04RthoFlWJmb0n3uJ5vBkKrUKH+AbTj0HUkmNOMPjDOELu/UMA0vFdMkwemVZp1wbSYTcjRkj4wLS2KXKT3dKCN88C8z8FHmt7EA9uNi2FwAu3YgfPCyCZjR03NfRVSXZlI4aMx2d8s7FuTIEWHq0bjVXLntaZZ1CsVkatPt/I6ojnRjPVZ06Nbemr0A8flkot94a0wGC8Ya1/FMfTEPJqh9w8WFEEA735M0n/iIg+CgihR/Tet+HgANBGg/wjHw7UKMkhLqrSxTcjUrwsAwLRDQAiAUivzVIDa5r4CqdXRQ2tGgCiG+0k2xpAb7atJo6lqbsFHmCFqvHiJce2yzeBejWdjfDk+1dngIZ5B1N2hqPvtW5vPZcmO4pXg7vSHqxg5O59E0WD7/gBxej84Sdxi4XacMc9K0rsXR7CBj/90DMCoYmQysuMAjm3Avqly60IWk6H6Umi4moR/sbeIUJECTzkTM/RCpOrVjR09uVtY3SutAk3Fazdg7mLNnARi6iHx7ZumaquZpdyCft9U9qBvDt/x/9EsNsleBVqwkQgkAkOtVUXLwAkjHrYXoZn1ntEgHc5q4t+P9HULE1qpPqTEKiclGVrGpYwKNvl2HXUBFymA68YEHzW08BtyhiAhZVWtbmXCHgzL2pdW60Aa+uF0AA6//YNGxFdyvTztT1IIz8nA6N4lnMiDbcGpO/IC9k6V3OJ3t31pkN9rNLe1yGbQ9j6hYeTQsVAEKLypKgoGiBF5D2Yd9jE23l8dZNfC3EKcTqL1gHseLJLIWEzd+MRvoqyoOpf+deaG13imH7p9kXepI2lMrnI0EhZCbdJEZWRXyNU+PPk9luh7tLvqBADvtwJntlUvWP2Yy7wGVQqytRHkF1c0OOc1BllD+G8OjRMDKTBkd2+su+O6JeOFUoM/zzLuRzQ7e5r2nffOcRKhuk9OYSJ6YZi1uvXZarsqNlvnm8Gf//AWJejGC+H7Oz3ORhqyD8ehM2qukw9mWN8YZindrmSfY+/AstjN/8sTD8Sa8r6JcmB2YB2BOR4YiAGoNjTuJPBeMgA7/cQgXaVbWM4Ew0/i/uHjhQnRPwjSfon4UDT1xXtjV9Vowu2gEUwsmg7ZX+LYih198ra7q0yjHiikFWn9mWFM21woYPHP7Q/lBbvU+S4OAHFoa72Y+WlfwwaEwk8dAqWKXkq4WTuFHV87NAk8PEVZ3xq3ex1b7iV5z3Lw6y3r3JKJcW+Gl+/Zyn49wFxwFbXqMDKiuZsz2LVdxw7RCA60QV7T3JA2+Xxjcu7A0oxTLC1PdZuIY4AgWMDq27enUzG65frxdx1973B2sLQiSfeWKdWKuvhodSSa1zC7an1x70HvlcAM+oJU63rB2vuI89kJzJAksq1UKK0Y7sSsXejBQfeGkA6BCCSXGhG0UauaTengqA9fLIyEBA4QFim249Z5l9GqhPnHYd3zvmEJ26nK+EiMnHJMCE4rgpvu7UhHavh5+NzuiXNZnvHqDNt6EbQtIHFaXDJqJtge8e3nEB/chRU0wteqXuGlc0DwefU/PSmGfp8teLfOHj1htHSvNpvg3lgVFAdey1b8/DkIh6/SFu2ClXjsS8wLOME4UbRJAKCBGCvhJg+vtu3x7biru+FigvvVSIqZE2Ew0rsQG8bFMhuJlLMo1RbZj8zXlIBhbj9cSalbl1fZZepuUHAgHXqtPAzS8ka/ruyES/45eLgeUYMRHgk3FLe83AyPXZxqBT1CIy+LvWFj0ioHZLfE1BVNZoS/Mu/7YaQ4lybkbM2VifKuIy4pXhbovmyEOBRx4XlpgYnWbmgo/QsfjCnGvRuylbC7zABLba7VzEyoRH8dSyb9Cg7dctHN7rM56MrMGlm4y6L8ZJEDaowQUwpCGus0PJbGaNBzW80Tp7cQpwD5DaMhC0yWI8GahvuGj6tTdnsomPudlHedgK2meNCWNdkcM0wvLDDxAQRQXPrAifhggKRgxOR6VLKxPlWP6/drmpOQpMWSzf+ZwA0KFVw06SV+oXFkmFg/cSD7EdnMWbMq6kHRxZZVXQPGgIRpDXKiS4r81cC+xAMCdhvGyQXDkF5jqk8sMoS07KltYP/pAL6iVPOT0Q6TY6QewrxSfrr29tj18fR/S0wosQnGIGDMA4QW5q+CLMGGMkgzNkgxyYxhw3xvbhakoG5gjaBVsYDQdopw8BdcBgtgHmhDtVXS3vpwM8uI/1ecAgzVCmyiFrf1Imqz1c/UYxvLATUXYBO/YgISDA1MHo/y6Da90DxotXHj1QAmOKmCZP0nop4/HDo47Rq0b6CxXHwyAT8DAFCSM3yApe1N6w9XVlhxbNvW2qyoaoPgkYl44QA5Xsu/ekULlZTFo1fqxgeOUUZIwe6eqDpO4iG38KDot8iyzXgzrRGOt6cFKqaEutsm0wD2HS+FgsY0wD8MCOjVXpvmciGXL6KjbzOJIvx/Tln9xVc6rNoIGu/FCq7j+ooDvJFZrPUA5jcwD1A8cd277c37tbumhJR7iJTVvA+kCoCFulTOIEERyg5i3SzGa7dkTCJQoHGGdzBOcE84pGJ9Qdj0cVQ1LjZYGQM6q5Min5j+2OLap+IubLuxN7neVo9wR4HVJgApS+T1cYO2kjJRL3kvcaUspro4RibQgPkcDL5EsLoP162Vx74t7W+Z7FtbVynjdr+TmxLAbeUmYAt93+3O13tY8Vx2qoLpCo5EMgR9RKPWcigP85AICY0noRaUOYd4zI/I4oI1s3jJaulZSOzEN8lzMzgsGG9IhfoJdq5p+lghO2t4FFoQAec2Rtu+l8vWBSY18nxz7KAnm0kiglX52DwcvHoVq599+O91RrfLvfcy1xT3GwtlieCag7JuXMGGGYPzjb8Ne2BkUhMC/1kYKH6kAHYWWn0pZPVE98d7bEnKstZtcIjAzHtOtXtdiuXBY8gtC0SW2r6uwAQfEvcyPDFiNPiG83J9J6YxhUAFsNmNzW3Z/LQW6ilBrXsq/GsptElpwMMS8rfcUnSShwPSE171UVsTYwM8ydyye+Xv+4hjaNMk7/axVkrYG2FWFjAih2tcS8W/TPYhqeFXICKhyT6xZhs5VdZjNIiZqV6V6uEzKSiOYhavlcwAw56hBeVWTp5MMz+89KF5Y1J7MVcrtu3uGNHbQ0NY0+qADnEutblBbuLrxvYm8/iXPzXSAjfpKskQYDNP7HXMLYCBaphg1lD0GOxpbs/5NUPDefZqQDIhQK08d10p6i94FxJHAzKU/IetsOgO3qOBK3P2RVBT7rUjvPNmKsZFAKBDitE/5ccHB9m0B2CEfHCZ0T5fABd+m7OE9x2una+T7tJTvoi+o6V/utj4KdcfZ7rU/GwTClzsRppEUA8UwAYQbqHLVsqGTU8xyvZ761v1Hv7hsE5JrhZxd0h9N0uvpzjZ86vZ7CdIgFUddsfCkgTOExqDuFflrbKrQBGanDCTW1pvxn7vkL1xH6jJSJLvy7E5mQrXMtiNiq4RJsFxXS6UT+3ynX7X9LznZs4GeboUvKKcRNEOCABmrweHn5AnaFXkqGCyXl0WgYA55w9YgfduuhStcRtoToU8mLbpajtPs/2FTYQ5QDLrH2oWoseCZO3YUp9CaBozu272OeFirqOu7Qz+fo7jHrddrZxpePfmFpi5XUaqGx6Y3Nv42PKZhvhoVTgcSm83ubdSk6W3SKsVj5mnHiSEcO2th+ELnMAj40Nmqyh2yURdTrXBE+Ka0SaJIFvB9hegLTN0TUOhZeWejsE63nM/c+vsZXW8GYbrq16v2qhZV4xUVuLlc/0Hj2pSE0m8cHQzc1RHLwNvf5YWil3F8jP317IHbzV++nqSaEWDK8+NRpWWn+2n+UM7bthKDa7hhH1TwvSREVrlYKSNDuquBZZbE8cxQp1UVihtFaehWFeWpYnD4kUPBz+AbsZoU1FJ54QA155lySJZ4Sn7xUt7jp/4MYRKpzUxEHsyGy4VTMxexsPJ0dn9roLNRnCgl1t/qR/SQYrTUVOWXNJQ8tAmWGIv2NcE9+UGLAOejjqOCaKxWkWRGJvHw1Z5tBsMa91GbUSmWLAHRk6+EFm7FqpzRhdYABRtaBssSO7Kl/7EleOqllftRrBgfT87/LVGEcME6piLLvmQZdxl2quKO5Hnsh/1JOLCKXJHXBOtkwtigosCzOcroyGb8G2r0doz8bgLz1SJ1hK0YrNl2rsB96kULrrI9QqD/8HkSvsp27iPqMr4DxoHrrP5Tmov8Bzn0oBcbM8GT9eb1WEND22t22NRq2ATzMmVR4fdzYchkm1GyO5Ei5nyeNIUOvVGm2ZFA71cj0kUXKgtd+e+HsYnNL4dtHavmRe1+bFxSitJCgyxqHy8S8ZcDUc7qbcOG+My6lvZe9qAh3pvYtcZs5DeTZNZQ7UUseDI9BVtcVwul65pSlhY8aaZC9niichbTFu79FfdLuMViXTfDq8z1GGja04t3M4M+4dXMbiJbnRrGr0mj1DApeIa/fwNMvPs4OD+wgGeGcmVfuVRvwIAk9dRLHx2VURd+2lQ7K5lcbKSfjEjmRKIaqvxffPCE1KGfRlvnQTwTtNd+W4IM0/g38OyNVxIR+6jB/YFpDTkhAEyPMc+XuLsSQICjKvb1rkJnuV5d5KNB1UgbmkZPDg3EVZsSoV888YW62a5rJ2KCdew5FkF9VoxEBwae7vlCxt8USt1aVpHVGk+npNn3KKe6muzrJKm5IkfQEzShURwXwBfIUlAAN8fHw+hhuK56OiVSQ034SkBW8+bZ6VdA8hg5aF+BW+NQdZ8ner5/Za/ihuqanOtjlYdb1EnLQX+IEgA6ZXHvmCE7LN79vbeaxrFg8saGwpGyXSu63/VjnnGmyVFV/HLBGj6nFkmJgxpGb1xYC7Wm6009MdUWMIYWce7PuPLSkFQIRBt/vU4WByrFxaFdch/Zc8Z5Rat1KSzti4HwNfW31kGUtNNWb0dJ+j4qCvrUQC4ipF0kYD+g114WRKG5BpQ3H3q1h5p23O9bno/ex6i6EHBWJRZxDmE7evTggQBP8HhcBs6xWkrAhGinsOj2kwGmpI8u1MzczvXYcqC6ikuunjYjrEYKOUY9Od1uwZ0mX9ldFimNNBvAjeS78tbN5hIppXeZeN6J03R8X4TKWIZjwINjYWCSmsr+fs93K9coy29RKKnx0/hoPnyiFxxGIopU3u1WrdwGYJmZnZMt/ooXZCJZn3QEVmw09Ms5eLQ1MhPbcvueyQG16K+fg8Qb2IITgXqe2ABBQIaMFy0M1XR4q0SuyTLX9pDzkZlbWMGWWKgtVSLs4QFBTfN0f3TkFLkgHjVF+KnGZRwRSI19iggkCJHrtMTZak2XVXY+Jwtm6DZABzLCyBE3RgHU2M4aj25dJMOhxm1/E6Vk6iCTkHf82nPU5PHc01aVSYl4ctAiHkKuP8CMD6x2jIfDtmBc5obqgiUmFvrseVhUiBPSFvvpkPVHn/NoseHnnbExLBKQbWYzoCTkhN+8EG0iSQgPb8eZ8P7FHUUxqMBAkkLGuifP4xKAHtB30Kue/r1TTUzJfpWRHdRqR7gWQrc0/OxgD5l89Ouxok6h7OLe+K4iMPMG3NE5WhlNHKk03p12VQM698vC244+oDiXJu5u/FPjJyzuQyZehLURFpMw0NO5u6wE7TDZQMw+ujGdYRLX6VGDFVawjdWzFgiAqaMJZn/tUPH/ayIE9alL3cSrqOEBicK1pD49nElGvsttgKsw5PysdRLfVlnuynyMc0C2z/pH/IWAggKDRZ7BkHcnmBY29tJTShBKRkkfNtmu+l3jRGbJv5/Te+M0PHMqitwQNlwWGbuWzAJJBys5Ck56yw1KQrb9TzfXOQgmR94sO541kh8IujMC+KoetW3lzTJE+n2g8pk0AQ+4WiUcD8O53U0nuSUqPeKr/Su0EYJmA+phgAYn5Pjw7V5LZ3ByvIQq0ObSHdQeoFU/B3zdcKtGDvh6Mm3Xj5Ge+HsB6gu0Tkh3vXVmMEajc826dmT1zhnqTncQE2ni9NsqJBweGzADWslKPA6e4I/0nwlMkcAElYh3T/Z7PanZyV6yVkufQx1CauS+mKS8Fhh5oYV/20/gX26CfeTEjQn3FBwmgM8RCm5h042gP/uWqzTVtNjpjmiawVZrNZyug6VOaSTl5BaZVN/J+hFg2qKwyQS3pf/QkzF6J9R4u5uGakr+yoQ5jbUh8N9PvkCMX8qJHQeKD9cfi4fo+VQOGr+X838xLd/13Wi0cwnNOmhXeKlNIvEHn7F7yINLuDRZSBJZZYNnlasWcN1bbXb3ltVCB+RvU3MzMyQyVRt7X8Fcvk9X6F/GF+4TXfECntb+fNuhZcmZl5mH9uYqYMqI/z9nQqfd2PPh/G5LbrdJ6Bg+Dhggo4J2O3buNbN4axIc1pYRZP1btS6Nz68NUzbJCJ8pPEP1hz3Efk2Igco1aeXSlkuDYA+NgdSZb1eKUYNHzeFJv6tKb553Q2hX+zdgLEn655Ud5MUDYm08wAFlqkSQBNCAcZr
*/