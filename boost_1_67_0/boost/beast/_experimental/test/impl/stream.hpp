//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_IMPL_STREAM_HPP
#define BOOST_BEAST_TEST_IMPL_STREAM_HPP

#include <boost/beast/core/bind_handler.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/detail/service_base.hpp>
#include <boost/beast/core/detail/is_invocable.hpp>
#include <mutex>
#include <stdexcept>
#include <vector>

namespace boost {
namespace beast {
namespace test {

//------------------------------------------------------------------------------

struct stream::service_impl
{
    std::mutex m_;
    std::vector<state*> v_;

    BOOST_BEAST_DECL
    void
    remove(state& impl);
};

class stream::service
    : public beast::detail::service_base<service>
{
    boost::shared_ptr<service_impl> sp_;

    BOOST_BEAST_DECL
    void
    shutdown() override;

public:
    BOOST_BEAST_DECL
    explicit
    service(net::execution_context& ctx);

    BOOST_BEAST_DECL
    static
    auto
    make_impl(
        net::io_context& ctx,
        test::fail_count* fc) ->
            boost::shared_ptr<state>;
};

//------------------------------------------------------------------------------

template<class Handler, class Buffers>
class stream::read_op : public stream::read_op_base
{
    using ex1_type =
        net::io_context::executor_type;
    using ex2_type
        = net::associated_executor_t<Handler, ex1_type>;

    struct lambda
    {
        Handler h_;
        boost::weak_ptr<state> wp_;
        Buffers b_;
        net::executor_work_guard<ex2_type> wg2_;

        lambda(lambda&&) = default;
        lambda(lambda const&) = default;

        template<class Handler_>
        lambda(
            Handler_&& h,
            boost::shared_ptr<state> const& s,
            Buffers const& b)
            : h_(std::forward<Handler_>(h))
            , wp_(s)
            , b_(b)
            , wg2_(net::get_associated_executor(
                h_, s->ioc.get_executor()))
        {
        }

        void
        operator()(error_code ec)
        {
            std::size_t bytes_transferred = 0;
            auto sp = wp_.lock();
            if(! sp)
                ec = net::error::operation_aborted;
            if(! ec)
            {
                std::lock_guard<std::mutex> lock(sp->m);
                BOOST_ASSERT(! sp->op);
                if(sp->b.size() > 0)
                {
                    bytes_transferred =
                        net::buffer_copy(
                            b_, sp->b.data(), sp->read_max);
                    sp->b.consume(bytes_transferred);
                    sp->nread_bytes += bytes_transferred;
                }
                else if (buffer_bytes(b_) > 0)
                {
                    ec = net::error::eof;
                }
            }

            auto alloc = net::get_associated_allocator(h_);
            wg2_.get_executor().dispatch(
                beast::bind_front_handler(std::move(h_),
                    ec, bytes_transferred), alloc);
            wg2_.reset();
        }
    };

    lambda fn_;
    net::executor_work_guard<ex1_type> wg1_;

public:
    template<class Handler_>
    read_op(
        Handler_&& h,
        boost::shared_ptr<state> const& s,
        Buffers const& b)
        : fn_(std::forward<Handler_>(h), s, b)
        , wg1_(s->ioc.get_executor())
    {
    }

    void
    operator()(error_code ec) override
    {

        auto alloc = net::get_associated_allocator(fn_.h_);
        wg1_.get_executor().post(
            beast::bind_front_handler(std::move(fn_), ec), alloc);
        wg1_.reset();
    }
};

struct stream::run_read_op
{
    template<
        class ReadHandler,
        class MutableBufferSequence>
    void
    operator()(
        ReadHandler&& h,
        boost::shared_ptr<state> const& in,
        MutableBufferSequence const& buffers)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<ReadHandler,
                void(error_code, std::size_t)>::value,
            "ReadHandler type requirements not met");

        initiate_read(
            in,
            std::unique_ptr<read_op_base>{
            new read_op<
                typename std::decay<ReadHandler>::type,
                MutableBufferSequence>(
                    std::move(h),
                    in,
                    buffers)},
            buffer_bytes(buffers));
    }
};

struct stream::run_write_op
{
    template<
        class WriteHandler,
        class ConstBufferSequence>
    void
    operator()(
        WriteHandler&& h,
        boost::shared_ptr<state> in_,
        boost::weak_ptr<state> out_,
        ConstBufferSequence const& buffers)
    {
        // If you get an error on the following line it means
        // that your handler does not meet the documented type
        // requirements for the handler.

        static_assert(
            beast::detail::is_invocable<WriteHandler,
                void(error_code, std::size_t)>::value,
            "WriteHandler type requirements not met");

        ++in_->nwrite;
        auto const upcall = [&](error_code ec, std::size_t n)
        {
            net::post(
                in_->ioc.get_executor(),
                beast::bind_front_handler(std::move(h), ec, n));
        };

        // test failure
        error_code ec;
        std::size_t n = 0;
        if(in_->fc && in_->fc->fail(ec))
            return upcall(ec, n);

        // A request to write 0 bytes to a stream is a no-op.
        if(buffer_bytes(buffers) == 0)
            return upcall(ec, n);

        // connection closed
        auto out = out_.lock();
        if(! out)
            return upcall(net::error::connection_reset, n);

        // copy buffers
        n = std::min<std::size_t>(
            buffer_bytes(buffers), in_->write_max);
        {
            std::lock_guard<std::mutex> lock(out->m);
            n = net::buffer_copy(out->b.prepare(n), buffers);
            out->b.commit(n);
            out->nwrite_bytes += n;
            out->notify_read();
        }
        BOOST_ASSERT(! ec);
        upcall(ec, n);
    }
};

//------------------------------------------------------------------------------

template<class MutableBufferSequence>
std::size_t
stream::
read_some(MutableBufferSequence const& buffers)
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");
    error_code ec;
    auto const n = read_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return n;
}

template<class MutableBufferSequence>
std::size_t
stream::
read_some(MutableBufferSequence const& buffers,
    error_code& ec)
{
    static_assert(net::is_mutable_buffer_sequence<
            MutableBufferSequence>::value,
        "MutableBufferSequence type requirements not met");

    ++in_->nread;

    // test failure
    if(in_->fc && in_->fc->fail(ec))
        return 0;

    // A request to read 0 bytes from a stream is a no-op.
    if(buffer_bytes(buffers) == 0)
    {
        ec = {};
        return 0;
    }

    std::unique_lock<std::mutex> lock{in_->m};
    BOOST_ASSERT(! in_->op);
    in_->cv.wait(lock,
        [&]()
        {
            return
                in_->b.size() > 0 ||
                in_->code != status::ok;
        });

    // deliver bytes before eof
    if(in_->b.size() > 0)
    {
        auto const n = net::buffer_copy(
            buffers, in_->b.data(), in_->read_max);
        in_->b.consume(n);
        in_->nread_bytes += n;
        return n;
    }

    // deliver error
    BOOST_ASSERT(in_->code != status::ok);
    ec = net::error::eof;
    return 0;
}

template<class MutableBufferSequence, class ReadHandler>
BOOST_BEAST_ASYNC_RESULT2(ReadHandler)
stream::
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
            run_read_op{},
            handler,
            in_,
            buffers);
}

template<class ConstBufferSequence>
std::size_t
stream::
write_some(ConstBufferSequence const& buffers)
{
    static_assert(net::is_const_buffer_sequence<
            ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");
    error_code ec;
    auto const bytes_transferred =
        write_some(buffers, ec);
    if(ec)
        BOOST_THROW_EXCEPTION(system_error{ec});
    return bytes_transferred;
}

template<class ConstBufferSequence>
std::size_t
stream::
write_some(
    ConstBufferSequence const& buffers, error_code& ec)
{
    static_assert(net::is_const_buffer_sequence<
            ConstBufferSequence>::value,
        "ConstBufferSequence type requirements not met");

    ++in_->nwrite;

    // test failure
    if(in_->fc && in_->fc->fail(ec))
        return 0;

    // A request to write 0 bytes to a stream is a no-op.
    if(buffer_bytes(buffers) == 0)
    {
        ec = {};
        return 0;
    }

    // connection closed
    auto out = out_.lock();
    if(! out)
    {
        ec = net::error::connection_reset;
        return 0;
    }

    // copy buffers
    auto n = std::min<std::size_t>(
        buffer_bytes(buffers), in_->write_max);
    {
        std::lock_guard<std::mutex> lock(out->m);
        n = net::buffer_copy(out->b.prepare(n), buffers);
        out->b.commit(n);
        out->nwrite_bytes += n;
        out->notify_read();
    }
    return n;
}

template<class ConstBufferSequence, class WriteHandler>
BOOST_BEAST_ASYNC_RESULT2(WriteHandler)
stream::
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
            run_write_op{},
            handler,
            in_,
            out_,
            buffers);
}

//------------------------------------------------------------------------------

template<class TeardownHandler>
void
async_teardown(
    role_type,
    stream& s,
    TeardownHandler&& handler)
{
    error_code ec;
    if( s.in_->fc &&
        s.in_->fc->fail(ec))
        return net::post(
            s.get_executor(),
            beast::bind_front_handler(
                std::move(handler), ec));
    s.close();
    if( s.in_->fc &&
        s.in_->fc->fail(ec))
        ec = net::error::eof;
    else
        ec = {};

    net::post(
        s.get_executor(),
        beast::bind_front_handler(
            std::move(handler), ec));
}

//------------------------------------------------------------------------------

template<class Arg1, class... ArgN>
stream
connect(stream& to, Arg1&& arg1, ArgN&&... argn)
{
    stream from{
        std::forward<Arg1>(arg1),
        std::forward<ArgN>(argn)...};
    from.connect(to);
    return from;
}

} // test
} // beast
} // boost

#endif

/* stream.hpp
Hz9Iv+ANX4CY7GTBWK1/VYrbzjaxSh1+uCPztQLTMIGy0jiBOkG6aw0moYhMWasFcMek9qQWn0RXMiRNm26qd7KQ8oxUgJu4QEqffMf4QWryVs2DFs5Xdzm3Yc2Wcs4EZGO9fxGsoTZ7aaIso5ueUKaLkkWdp3p6Rd0/4KjMgvvUE0JlaDFuiwZbK3wRqIGqu9a8idPUYIXJCZAygXHqFElXgX/qzsnC5+2k0cGEJ6WP6sRU49R0oZJLBXTlXj27HOtyJo/zbsscG+MC0qoy2DsYB/PqH4p78htK+iKIRjBKSUIRgSya7V+MqbhmAqFFT0oDZe6yG6o66C6mzRgwMI1F0YzZIGheLmVM2gi8UCauwR4c0E4uzyrdagOS+JmEdp5PmNq3yi9izMlRKnjZoKLX0dtjwMZSZc1KlFS21ydeHeooJw3JZP9eN+CCCHjCxG5/BGQbOWZHOz5j6rHnwbWGGxiyzofLRqF2uRMFjZ7kMezuYE9W3cCbaao6ONPl4HdZ4+lBbLFhfXBVHPaH6btNTSGBlFEWTBurstfcJGwg2WWMXk1rOIY6yzU/EN95jHcb2M5u3+jumR6mN1wt2dlTFBC+gE4D5sLAxfDMFmFnx2Ez/cstIG2s66nM/0qYZJAACCz304HjhI4q2nbtVNGIszlV8JzK1b6+404mlLVPY2HkD3pl7UBV6DHWmmV9CDx95Jft82TZHx5cPVQBLudOwMbLH3ZgIXRfqdKU6HRepmTVIctd0LH/o8n+9BLHTlc7maEcKPejDSTnldVReF2NCw2lp5v3FpUN+gq/oJEKmmThNjOzKwMB6C6nvpYvgbMvDflNfe6enfRHAE6cE5LiZ62nmuUWAgGr7PfB6d+MkotrIGag9SMyBTr4hzll6A2H1JfV/tLYdp1xbpZk757vGDp1YjUjN6/u2XrsHl2vUnskzJ9itiqj1UXW5AVMV/H5j2RU9yTdasNIbX3t328EaT3NjL1Npu7eWFzHlGliyQwHL4SHMJdDAuvgCppOoSoUvB91iIJeWpac1FMm3Y7D+NZPY9Gea13DwTfCIT1i5Vs4r86gTePuzn+ruZBUB0hvdekj1hbs9UdBRdNoqYIf80RGjx4N1zjV5LpwBildvNLpwKZxsCniC1EvQdHlDI7VEFaV/NRmwEp1ilhwcJKfVT2388g3ZCKWyZvQItVzdEUmuSvn0x/uwxkcshlWtb+od1aPA6dS6m5mwuhnSyI4PbiRGDyzEOpHJLIdn0l9y0Wr0APqxJEGfYufC8p5LrHr3TOue/88pxYXoOfHgaTdXWid08SO9+cNWMcDitvIJI6k9u0tADmV+TCut8gRaSdt+JovvLq8usxlndxUprZ1JbmqEkWLnKZWI+21uR2QE1Imzwjcn7NDQBDU9EEaq4FdJNYTgTo+KbrPnpz9Hno+m1U30l02lLJvaqDcUJOKBsWC/tpr4C+pSYYfRHzNiwecF8L42CEhqnX2jY7qfJiZlF1WiL0eXLsQu+10QuPy1Brc+b/H6ketka+c0k+MH5E5HaCrGlLHDZsmftRkyHwnQlN0Bk4147MGi28oSWCIoO9lODdKluEsnjlm0krUt2Ldq6bx+Elylo4qyExDXyZiLqFy1nugsxxW+ymL5DjkWR4sdMSGgul4a+G+duL6Nr89Fr94RMZ3c0hpCs+4TzgI3YqNKkw1p1JJ7DpQdhq5KZID7a0kLMN+KvIYENFmJ56KjjysItcAM3eSZzed/R/2lly3vPcMOEGl0pRdXDS9RrYsObw5loKbVhQ5r/qjenk8uXp8kmgQAZ7EQZfWPVkE6/8Gk+esfV4/M5xeDu4FB6pK2BgeaGEqCCjCQpCG230+hL6HLUm0RDWp3AcKqG2ci+ktX3/9nTA+l1sX10ZJFry2Y/SLTDY5PjbZ7ecXzpR6oW/wRijSGAD1g9WfgC1taWd1qVqhcpezqz/TC7M17wjKI4SJwzmnyy3YF2BWeR2zCRWE4aG6SvOUaY0jRYQ180jNWQB/utyesmfg87tyFPm2gvIvGaVH8VoxQbOVslZnWk700spxvRSifpS+o8Hx9sIMwCNa5jwLisr4JKprjUJbx9geYbdCqLky0VbEqs4CLsnb69abWUSZ3106vlhHqiTOMT6AKmugunFm0E2HtaSbPBQVCs2V1kkEI/YH2+mUzaAgtYt12ssmzxcXzKcKkXsvmy3wf+WBNUyVsWuZGV1u2/nOZjWiC5256eQthV3tqP2BoOZWhuf8KCn6INpp9JIt9baM7JgNZYUlaAXb8Pw4TL6iU2EZ2GHxMb0wkB+yx/7bfuUcicLPRkqMFGkrgntWERjwOTCgSCCHNfUnf/seY7/hlBYDOCRaIrY0K+2S9WzQ+WCpvMN619AEQx7DkpPLe7q9yCQpUza+sJLYY9n/WqRNuVCSnDtPy7HNnW7R+kawF8/z8sjSUunVt9caxJ2NUBUiFWoixnTEkTSLdNl8qN6uXNXEtmbXfidyWyD3wH6wlh5ClYhM107xznvSx3ICg5eclJHAiOpffq3trO6R/TSr35wk+KKAo7MN4HbUKOjb2HoFhLNfc6mVBKKSiaRhWe824wxeXmIzHO+S+zaJ1JE/MSIejye7EQqpR10O/Y+gAg51ylQYvWCZHdB4telwmtR6CwMLeURQNiZ5zqPyPUUTXxllrbZ/MTDtGg68wo6ZfjCEBIOwgaeZapFSpxKB/z9gMiqpRCycLeLojl4nnVImFqgrXsB156kEkAVmIcSx7ZYunSYuKr5ClpR1OCcGdKWzXTY3v59+FuUFTYRjNExpxuUg9cTB/+hpxTrBm2tgdVstzBwsCFYBErOmR5EuvUSQFMytfpjPfRwnDpZLAZfffvXo/htJ0ujWYrkPA5YiHfl8PT8knq347ZThKBjq0G/iYBSku7k1SmsDSdQZCMZu2Px4g/FeT9iIzugJLA4Zw2Havf4Clo6SXKOPIXPs3w8oR9SNrbBjvXyZWzlxcsZ8CbnkbduTzXfFhGm+Fg6fsscG6nu26/VESU9PLkWZ0DMgttqepee7j7StWFAfAMKySfBToNG9xQ3y6QjFc1sMB971Elcaw8T73eMUCQJletOx8h69ETaxNDk8tBSekiXtN8M4/C+GAtw89+xE4ry60ZuiyQg/817A7aAjho7u5gd+GTPxrFOSPoV4KMaW4fT6k3vaCE3hYKtnzEtxvlpJ1TZXBM5pbJ5wdnbd/H69uA9pzYU2QLvi0YvpioaaPAaegywHJ67fm2ohMv8Vg3P9mEhEWlkTMcDUChiKcnT9VSBcA9Xllse7MirhJO1OiNro4u2AF6LuALtXLfHkcUr77kPo1lWY/jylRurUowuXbti1jPi0buKAgV1+jhsXfcj5hYXe0cBEcsz3ehfXB9tVWw+RmVAh2/c4Em4CEZrlIV/qhhyvm5xM856eMfHoAZYr9NfXllxBlShxXJmW2p4gk0a1PovMbc1QeMLyVOeJyuM2XBnBjSftZHLXiMnR/g4W9jWUbwsx8n1vnXE4bbKaVVQqpPvYACHjqP2McZf3nQAfJW6HEPZg3nowWbXFW6q4rqWalhzlbGSQLp0VAAVcVVhZ8O1ZSVCznvv9WXJrrl/h8+GI9LLPmCXC4mDr3WpTdvHiBF7mIn0RqF5Rmt7XLsoIwY3y7UdK0HzGAxLvKXfypDpbygR85AXIMc6OmaV8vm2fXtGBQHpWi5liv5P3vyAKQL2lnU+i5fOXdJwsqCHfCevuHo4S5Qm0rS4ki0X+gSD7HyeO3E1VJ3X2Bs/HNqJU9J+GuPlBG/CdjlwYjrxNXmgu58bCS0jg+UiFkhZit0zna00ap1bwNRmika2r9EkqU3ALU3QJPhqxX9u1/gsAf8Q8WpEuoBBWtCPwyRG5iz5/culcQM9EU84ZHL5sfhoy4JL1M97lplP46jpDANdNtHuSRhlqc9W5tNNcbfySmqh5WCTaffOHFCEt1J4guceOXYdNnRKd0KZ4Ba5SSH4JfGuckd7hfBe1TRf77twMT0kYzagRQopxHIqrienDSxMU7MKXS6cZUVTdeuNbmfhXOt9E6hxDUxGghcjmiMtIRZIO4AdX5L4nI8DsYQAju4ACt7x1TDqpY9ZF9tFZ/4IdvCyBt6mTXH8E2RknjL/O6V7npwzm7DJfGsHqR74pz6wwTRnP4hg6UEkibCrI2gtW9StjNEArMNf1dVkbGDjI20pimbjvqXCMZYTu+I/h5cXQSejmzl8Z9qS5RudZ36rcTDqSDM/ln+xscdKcHU3q57605OElXlL2DngUjE4HK54KkGadwcp9I239V68bR7JAq1C0Kq5zqVA2WtHMx3pVggeyD0+xUH5x80Es3Rc9IOezhwmM7dQ7zsTyVNVKSxZymTDAxYlQrWzZE5KzY8intg1t6XE3H3NWoB0gBdFjLHPfly7JKyaalLYe4Mm17ansSMYjBjlzs2mn2wVUjwlk2UO2IdqRLqbHhSeykO/X/VOtRJfeMDmBoCmdl598/OVYxjxHJHQhuJu27P1kt61bC2GQRF2GT68Sl4aD58JR3ndYCeh1bat0pmpvmYwd0N5GZGVneWQ2zjhsb+nD9XBQp08+SaYsEzDTVwxQZaQS8GvCZpyHa/uKqo4M9E8CA8FxOX0TKkzynocop8PKsa+3PoFwmwHL5h6afcS2UZ1IvoEEVRAkEFQet/QSnIFluUfPSI2hncKMrBEv5456EUi2RH7aJf64lG3t5bbHir0rj3xZF55u3NoN7Cp85xLxcYxRVn/CmeX2S7Z6GXTm13fnEkQo2atYugGrrTviMmJU5sVaIkSEiXLbmzG6Eu49qeTVVrbUDwfXoFhWH+/lpBY89gF+bL8Hi7Si67mgJew8KLZoc1kZNqtYdoGvBboRZ3GtvXKhplIhZkdlapraj3Gw2s/xTqE4ujyhYtIONA7aBvX0r0IglQK2DjKuMlIMW/vbzh4fYJrisb+zufv6tH97ypPpEwdmurLbVmo/XpHy3jCvxw1bPBsg4AWwX/pXIAnZ2kxblwoQgTIHOt7U70fndEscdZjgDnTBuX6XOEJdY4QwvW1C6WltOr0sGn3Ycu+tbZYjSZyy+pPx1u+dZP1U8EC0q4mDAUMQaKQMH2F1zcXSMntKfb66bsjdOFDcDXy11LKF4e7rdU9OYrrXCjApIfl4NL3EYAoFyiP6c/tu0Jhd+rQdy9Wa4cSIuh3HApf5+Xr8WOBEzDlJwiPs2ikiZ5qUrh0euqP2ajSTTb2UA1wl09lznvg12kULWXRZvDpCKB8LmceOZekbBzndywgFoPOs6lfaGaVrXX9CdSwX7+81WuRKqfpT+3lCyWR0DO0eiH8jRkEE+h49KUMGRSBllCQet/Kc/ZGy7BR76rDf6lI7XChlK2wC+tqDYC6S9fBcqsrv0+xWMxeOJyPZhlhArz0tOAIEBNwOOLt7RBT04pjebr2EXQ1e69Jyhl/+8GwaNwl0qiOGMdVQCOPzmsohRJ1R4s5gFODaucup4WEvUTrsF02EpznE2Y/qL8gTqYfpG/cGWpSNEs51e3xwTKvhbmyIUy54/cHWm0eoRkC6NsE2Huf8IOEN8Zj+BWMMh4p0Mr1J+UNyT7/wvFodHXTYo4XvfxA9Af5HZTCvMzZBqBxUDHEcX6eLdq8pQXTThsiI8+qaXBBfJH1T5AaZXKIsUEmP6mtCvSDmYHIRtAOXR/PMCYDKTsb44Y//tGu0bXBWUPjlcnAqJuyDpgI5Ez+agDFJQ+4z4btt9D9mY7tILVKEXVCImbzKWBRhJLCBsfQeed0n8MtEnjxc2i3x2OrhxS6x4DFNqMOuFcMNNxlcj/a748Ox3bJZcv038uc1h/LqZiSK3KqdpxNFUFm4mo6mox8GiQyC0BfAcOWbE//FqO2WNL0Zc3uC5DXBs4kGsqj4+CdmzRC6Dk2RDPAm5BhaxiODBDRd6yArTcNHE8RhSLrwMnUVQLtO/2caTgUnQIOIPZKz9J92m4AebbQYxf0loZYha6ME/WgnnaAHrg6E0BiZjpipB3dgsm71XmuFkm660fHZ7uAc3faekA/k2V0iGqFRYbM/Q5shwy5iOXohbFVyZT6olQtOrfZU9oCCc9/GKYE/unuZF8KqUs+6cwZsacL8NTIWY5BgldNO5TXqywZnjrb9eUWsD+t0yzrAbKb5eInOkw7yYjQ4K6WzC3AiCmRLh/n0W/ftTqE/h6xxM/eIBdz1vwUYuC6ycYfzAC1LY5gcmAD/6iUDYeV9QdAdFkwU7wwqNGLJ/KZJiv+8pW2sd7KtLZzPDv4znOsW+Lm1PNMcw4iUmQdOoJlfAClHXaD+XChwx4N661SXIiC0DNL0R/OcSfV/biScHXA6Bl0yZZHezw4SUBH6+McEW9ThcXyIuJoVT9n9DfGpTOtpfS7cP4gHKnp8eMRng9Rd6VDSwVmogELEOMjkFdNqDbiQWQ3JBVcp6ZoL/2lj6E7+4rWRzkVgxOaho6t+4NiqzWxfLpU7sxs3I+moQIQ1exCIxJa6jzQr/S0iXpjg6vGV6r6tn8WHRqtPQNDeWjjIPI8WoEFUppOYxi0w7FLmDKeXs+27j9ZiLiQsyYAirVoeJnv0j05eNB/oUpylk70t7ULeWKwem7kda3vBvsDxcTA3vMB/dGL1Sefgld0qD7S68uDfXJRDoTd9nS4kq37tqSbYSGNPAKoMFLcLZ8DuuZzmpsOk9f6en8AUZPyC+5YC1MZD5S7VDU5WmzEBqZkBr7gGpzZBQf0M+tCjMkbQWBj3yQSn/vWAWT+2qPnu+LN3uMGIzvC5+CjMKkbl0biASHvQBdEn1Hz6R56bhXK3QsjqVZlGTKL7UtXtJQgaPuCVKL+ZjYQMcfNPg5K1PZPw58QN/4z/k2Z4EKuvzs100sfQhJyvr+/sncsoqVyEig4OcJwaR7SMMF0BhGyyKq1D85SB5icp7SPQ8ApAm2EF4ltcItYoV2xBIn3HBZc/RgfAV/ABqobri7JCf93EjMZya4sNAQ0HNNeEQNCtTWShcv/hUAMJlqJzrXUML465tNXI4E7ThUSzTWcrw0WPBhKy7VHK+yY0gui+Fc317kHJk0Uqs32ur3TL0qsZIakpQnCNMVE2BIntw0bowJeh9d0U/RlV/3S69lRjLGayUH4NehTQEMHKY9to0qEZUfNuMUZBBiAZywScECELYPDabMhRPhRg+w7YPF5K80SyUmWkqbjI1cSOmPEQOFYngCi5PoiSIXY5/ZUR3679SlfXQ0Ia9KLBqKKDddvgmz1t3fjoV3FrIpHQrIVoECFzBuG8btOIufVaPw/zBzTLLm25GrdODGPOfHX8jt7CcJ65TAYkliCi5miRaXKkFaLns6If9wcQ0myiRwFqZwlZ21tcspZRyLSi2Sn26tN308OeXKFVexEs85P8EGImUGPqjZGLKoj7NMseJlpNVyekU0qutaWgCSRlqZbAKHL7vkXzA7C+wn6LIW/fMOGSugw8ltBzvzqgBY33d8HLIktN13YeLSVqlL/ugjRftQmcgYMjvFXXnKKC3RmV7YqrmW3ObyQDiOfi0SWMol6W9ZBq5447UrjHc1OzfkSq9i4MPkVqvKSQM4T5jSnUMF62Mnhqb5k4tgX78jtdO4BYgbqF9nndW6CIkoQHbx/7fMe32xj82PGAk6D86QLI/vjg1LjCMy+Bxisd7vpUbhJxXsLuQVhIeN1GRmbE0mnCM4K7xUnjJu46t7UG7iRinD0hF7UON32pV3YG3ITGxIsf32fRWnwX971Ivl0gZU5yWzLGwZ4H95pOVI5LTBydUen92CeoxPeo9Jl86yRY5o9stIEiG8JT4Gl3YnyDOcrq+cItO00jCDDMfvKkUyHhXfQwpnuQN0eIl0bRO5i6RQlKpb76AU97KqpA9YeMLBPBHAxZhoFuw3mCOdP5W1i7tU4OsYllCjyzHLuKNh9u2D8bTF/HZJAkK2TdhfKIeLLEk/5Mj3m7gonhjyPUkcNr5QFiiB6aipnKsHks8z6SO7/JduriU5jo4+Ku22+SHFv3Lu8J+Z7CblPi4qXrbctVPlpHy7Ffg7rUsIzv9izT1efVf04nBGAXI+YfRrelvJKUnTMh8xC3ODKlEL7QZ918sMO4G2cv9wr30YKjgZh+QKOxbis3OxrhmDn/9cIo2CHvyonbaRA+D6ktNRIQBibcUx1+Qmmv62iIH7bX35E44fr+0tCvQqgAsrFH0r3KqCXu/gM+vufC8t/szHZDqFX/K1l5tvz9AyNAaKpOrUfMNSnXmsUT32iw/ibAmUcgKoQOr9eCPWCdIhnUftB/d3f1JKIhlUYUpnKnRUUivj7bMnslbql5X4CZSknICImFft/39VjMzzmmyq0wOuzd7cwxhau2oWW/mdAb/qaF9kt6MttpEZQwMVtHZk/3lamqEKZVDYmB8VenIrEWYdlIfd1gqXiXwiCmxSQHeMKURVJ6hEAZUNcBxkthcoShrZZnfU+N2D7LxWmu5nSikBClYBLDgiaVWCcm67vD1Ag4moohyZ6crXO1NHSd2JrLY8shgRgkg3A/KiFU3rqY5zZh+ErmcD60M1pPbbFJWD/l8FZ/8Wu4W1N7I66+9DGIArZGa3WiuUv/TJw4IXuWMmCQqLZfCfE4MNPBHAx99+z1vgIYksfMyRAn1LfQUIc//XrppwIrwsvagF/XneOuoBlBXxDSvNSV3+RtwuAyF/3dx+WXIPB8SRDa7y34rURbsDsHgq22sqA6n26xirNtXVvFgdX543vdDZE2ubKrQvotBuUSvnf240fXYI2J1cDmYFlXu1wwBK8fBi+rFgecvWYCIc/0E/W+BxBgIEsGi67Sq/66oG7oruPkDlCu/i6q/Fqh1pFODRPmO04Er1Lerjoh3gYOJ0nBMjZTO/Pyj3i7PA//1O0m9iUmIQJXE81jwU56GzBipVc46yGr5NjStJ7VvENSL69tzuVXHYU4DKNhhSmPmQo/TBTryxt30PyXUIp0AvRkPzIg1Vmojya4LLCOjdDZzCq3YYswm9yRjYlKcIaBDpVu0/N8krlkjTgJ4DztFQQZdwvbE6KFJKCVV2lh4MZGoYTG8TMjWgMV3tljuagZJ/EIkfcZOKMYPQoEDipaPxQ0RHIFUi31m4BIIIGa2ubFoi23qTK2VF0=
*/