//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_STREAM_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_STREAM_HPP

#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/websocket/teardown.hpp>
#include <boost/beast/websocket/detail/hybi13.hpp>
#include <boost/beast/websocket/detail/mask.hpp>
#include <boost/beast/websocket/impl/stream_impl.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/rfc7230.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/assert.hpp>
#include <boost/make_shared.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <chrono>
#include <memory>
#include <stdexcept>
#include <utility>

namespace boost {
namespace beast {
namespace websocket {

template<class NextLayer, bool deflateSupported>
stream<NextLayer, deflateSupported>::
~stream()
{
    if(impl_)
        impl_->remove();
}

template<class NextLayer, bool deflateSupported>
template<class... Args>
stream<NextLayer, deflateSupported>::
stream(Args&&... args)
    : impl_(boost::make_shared<impl_type>(
        std::forward<Args>(args)...))
{
    BOOST_ASSERT(impl_->rd_buf.max_size() >=
        max_control_frame_size);
}

template<class NextLayer, bool deflateSupported>
auto
stream<NextLayer, deflateSupported>::
get_executor() noexcept ->
    executor_type
{
    return impl_->stream().get_executor();
}

template<class NextLayer, bool deflateSupported>
auto
stream<NextLayer, deflateSupported>::
next_layer() noexcept ->
    next_layer_type&
{
    return impl_->stream();
}

template<class NextLayer, bool deflateSupported>
auto
stream<NextLayer, deflateSupported>::
next_layer() const noexcept ->
    next_layer_type const&
{
    return impl_->stream();
}

template<class NextLayer, bool deflateSupported>
bool
stream<NextLayer, deflateSupported>::
is_open() const noexcept
{
    return impl_->status_ == status::open;
}

template<class NextLayer, bool deflateSupported>
bool
stream<NextLayer, deflateSupported>::
got_binary() const noexcept
{
    return impl_->rd_op == detail::opcode::binary;
}

template<class NextLayer, bool deflateSupported>
bool
stream<NextLayer, deflateSupported>::
is_message_done() const noexcept
{
    return impl_->rd_done;
}

template<class NextLayer, bool deflateSupported>
close_reason const&
stream<NextLayer, deflateSupported>::
reason() const noexcept
{
    return impl_->cr;
}

template<class NextLayer, bool deflateSupported>
std::size_t
stream<NextLayer, deflateSupported>::
read_size_hint(
    std::size_t initial_size) const
{
    return impl_->read_size_hint_pmd(
        initial_size, impl_->rd_done,
        impl_->rd_remain, impl_->rd_fh);
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer, class>
std::size_t
stream<NextLayer, deflateSupported>::
read_size_hint(DynamicBuffer& buffer) const
{
    static_assert(
        net::is_dynamic_buffer<DynamicBuffer>::value,
        "DynamicBuffer type requirements not met");
    return impl_->read_size_hint_db(buffer);
}

//------------------------------------------------------------------------------
//
// Settings
//
//------------------------------------------------------------------------------

// decorator

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
set_option(decorator opt)
{
    impl_->decorator_opt = std::move(opt.d_);
}

// timeout

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
get_option(timeout& opt)
{
    opt = impl_->timeout_opt;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
set_option(timeout const& opt)
{
    impl_->set_option(opt);
}

//

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
set_option(permessage_deflate const& o)
{
    impl_->set_option_pmd(o);
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
get_option(permessage_deflate& o)
{
    impl_->get_option_pmd(o);
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
auto_fragment(bool value)
{
    impl_->wr_frag_opt = value;
}

template<class NextLayer, bool deflateSupported>
bool
stream<NextLayer, deflateSupported>::
auto_fragment() const
{
    return impl_->wr_frag_opt;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
binary(bool value)
{
    impl_->wr_opcode = value ?
        detail::opcode::binary :
        detail::opcode::text;
}

template<class NextLayer, bool deflateSupported>
bool
stream<NextLayer, deflateSupported>::
binary() const
{
    return impl_->wr_opcode == detail::opcode::binary;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
control_callback(std::function<
    void(frame_type, string_view)> cb)
{
    impl_->ctrl_cb = std::move(cb);
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
control_callback()
{
    impl_->ctrl_cb = {};
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
read_message_max(std::size_t amount)
{
    impl_->rd_msg_max = amount;
}

template<class NextLayer, bool deflateSupported>
std::size_t
stream<NextLayer, deflateSupported>::
read_message_max() const
{
    return impl_->rd_msg_max;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
secure_prng(bool value)
{
    this->impl_->secure_prng_ = value;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
write_buffer_bytes(std::size_t amount)
{
    if(amount < 8)
        BOOST_THROW_EXCEPTION(std::invalid_argument{
            "write buffer size underflow"});
    impl_->wr_buf_opt = amount;
}

template<class NextLayer, bool deflateSupported>
std::size_t
stream<NextLayer, deflateSupported>::
write_buffer_bytes() const
{
    return impl_->wr_buf_opt;
}

template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
text(bool value)
{
    impl_->wr_opcode = value ?
        detail::opcode::text :
        detail::opcode::binary;
}

template<class NextLayer, bool deflateSupported>
bool
stream<NextLayer, deflateSupported>::
text() const
{
    return impl_->wr_opcode == detail::opcode::text;
}

//------------------------------------------------------------------------------

// _Fail the WebSocket Connection_
template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::
do_fail(
    std::uint16_t code,         // if set, send a close frame first
    error_code ev,              // error code to use upon success
    error_code& ec)             // set to the error, else set to ev
{
    BOOST_ASSERT(ev);
    impl_->change_status(status::closing);
    if(code != close_code::none && ! impl_->wr_close)
    {
        impl_->wr_close = true;
        detail::frame_buffer fb;
        impl_->template write_close<
            flat_static_buffer_base>(fb, code);
        net::write(impl_->stream(), fb.data(), ec);
        if(impl_->check_stop_now(ec))
            return;
    }
    using beast::websocket::teardown;
    teardown(impl_->role, impl_->stream(), ec);
    if(ec == net::error::eof)
    {
        // Rationale:
        // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
        ec = {};
    }
    if(! ec)
        ec = ev;
    if(ec && ec != error::closed)
        impl_->change_status(status::failed);
    else
        impl_->change_status(status::closed);
    impl_->close();
}

} // websocket
} // beast
} // boost

#endif

/* stream.hpp
ZKR8Gw/7CIRf2P0hHUxddNF7lxzyB7gxOXwde7jXEc3q5PHXdevuj6/Dx+G7+xlYw2mOZ0zlx2wOtycn8wGixVL2kUgTft2WYs5DkjLTfU4NGE5+aFjMyPG6SNyhvXI7vR6YIQBRS7wfY6vYYyL470tr7/S8AEYIkBape85/a3fqMIJdNQCtqtJnwxiVr5Mn6VdVinBLwLb13oWNpCiuaNp2p2uUFI/uuYlM0rm1yO+NAo68VRO8hQL6fl/qYmtoWMf/DOL/zM3VFT9HiXLrGP6buuq6Ut7vcxxZc274xUDqOEAM9fXb05L8qLPhxgaPY0yGpNCfh9TerVJjgxO3zq8jMl52XXPZpPwtTimeUOnOW8IVtzP+JYxbucIuYRtjWFCRFW3XbeUVNcNo5WW+YG6waKtQv3t4rJ+vU15WOQ+YfVnfD8UBDQ5p/e+UP9lWY2/Y2FZ1/AwEMOCt9yPYrE2Du7Tv8u/0cAA42lfSGAGQaBZEvKcxnDdpxIUJaujbf7xCoo6ciEIBs9TOwJnIqqd6hLDDPKJPy/p3KkM2hN2MpplXs2r2l6S4Swvxu96vrBBGxEB/CfgO70dqfZ4rR2h93yeDbLufV0R6YVepdJ84Zt1GGLFmfV4asTkMl9ccJp3uWlUdrN/p/jsBJpQvjSc1AuJ2VdogUZJDYYvAySCZuPytNRE7APjvCfdyZgTM0d4KerUW4xx6YdtF5qbY+gDVogL9PfB/43a3xL6AY61qOUozhFDVtBXYP07/SBWqRgxOisY2LKtoMue8dp0yu2zZjxpxfaeE2APMi92JCuaL6uMfx/p+HW4rGLDg0KOckOaet36l+Q7wFTAd9T4tSOYWhLyxtqNPRNMBrjb8HSxvYmCmHsxTbbsbgMbWwLX8OmHtHW+reB3bjGAHAYfMFExIildsv28Py5iRKT42O1GQkpKHiX6NTFAJqW6YoBxXc9n1fg1Jaq4lVMcVlM8IvpC+MRyuNCexYvIxa9126exMmM+IRwZDAinWMdTFHA4leWpWz94wK4xeSRgodlS4YV+CqH4H9elji6s4Nv656771rr3v/f3shYUpgstj6mpe9xtAsLtYX5h/khGRC/WREuw+m6bDy4oJZ3LSYH037GDoZZFUrG2Y5flkKqrjpgVAwYzYoHimW8LkFVUjGezMqNR2HRPjoQTubopq7djv7iIhsjaSA5WcwhFCvj9cRqhNwFb3fl5WXYqLkFUVfcZiQaDcjtS/E/n4BxxbbyutPctzN57JVwo4E/2amKXLWUGQmll8tINQmDKVkuPOCaBfvUd/aM1xnOb4ueEHtWzrcEf8B+WMUGIt+w9srFk8bBxioo4Gv8cs0lkRYMtXEv14CUfjLBaq1BubIHs2JvAkMF8tMVy3nVUPpxhnrbxOOXfFoZSXzTQ4ZCpFWaDqlZO96kcJidGQ1IQHnRUq/rasFdyHsHbl17/ueLrifKAq07CiHCFnq3TcrFLueh9Euo//cYBp9/igblPUjniL1Jd0gl/AUfCWAtKNJkxOodcUpIR0XtIRKW01Qon6Zt12UmSACVGYowY+gcy4JGFV8UQ07nrCrlnsGJe76XqcmVhmURmC43nbG/kvmIWEbadc6gyxYYWHaMX+t/ITTPsbxjFc8zbZUqbWkjXmZJX/GFtMKt9inMRkK1W9xJ99aYMaf8K8qe8nLIwR9J67YKYsSkuUHRqMYDhmljPmFJE803mQDvvXbddSYb8CjoZbh7f9UFad147V4nZl+YyGuoodoetWuUqtX4jJfm349ofpZQaeiQFnbj51JSh8V8d/Bi2RKCMbZ9OpsL8sgmXdsmOeZtcQpMQG3xIFLq8yDuu6btnE+k+nis37tQ8vaNapCpYOI3jcIko9LNvlhmFiwdrllDBb84MoijPvtlypM2x+VlO0r0Ni8EpuRTMhd7MsGUu4+rpc81tFiI4u5xRkPMFnhGMpbkYmHsZZCUhq27JuYvkYTtUtfEVPB9PXVoiS7Kc/bMr7uT7Sfpqj+VZihCRue79UytN82WqU/ZBaxJQhRCbY/vvzCb2u4/v9jH37L5Jg0/rcR0IfTgLRw+WNiTV9sLyOYNt2VbpLvCE1v84zJHxOmLF7pdP/w4kPhhhFki7TSfKUUTYjksl1uj6/6IG1AMrBLszZf9nLyDhZ7pbLy/j5uQF7i//l0jbHbEOAusBJGgzyJ9EcKHx0rNcRcbQ06zFHnQdCdBDOE1GQP3Oumt3gP8OVv48DNd/SLp/cpsR/VUcwULl8A9COUGKgC1aV2HupC2yIGX6bI71xPJT+0YLpj4lYYoZZuIheeusD55lru+m4dLMCBimUHgGzHYQcNEOeLgP30A0pEeaGivBe0w9l3nmfcXVZfhQRrPf3exbw1Lp2KZ3wUrL+9sQcR2RI2BSlX4ZRu4AVGqnPD/JKCWqMGWmjsmoYJ70suxm3s8ZggTpk0GfPyjYh3SvN9fHYn0CpZGw0mT44pDBN72Mm8fOv05eYTQCmzTiM4azJhy99KFs43RJzGynPRjcg2RhMJ/v9y5AwOBFlVM7yz4giDDGPJEnpHN6dBS4j7QOM2X3DGP+gtjgBDrH39/sW+9Z91nMBmxaEjJZKPstNW0O16OED7lJdVBQrQ6lUFsIAs2mRMBQn4YQsm8c4+p0OCiCqUBWpWljDvEux0srxuFtR5AEMc9yaHv9HH3vMYHPfAq6yh9J/aunIrUMmj/SQbyxEyw5ND7NklG3PD1gEE1yQ/FnqfG4nyF6to9vQW2ZO76e/QARkI3haZcPP+KnBZWIwnz8NEHfuEULQupq8hpxW8IZxHrOUnlSXd8Zp4s6AHkH5iaJiqVwJB/BME8zmw1NBgIsJVKX0oeq48dFzAJIsyqOwzNTCqnGa5fywkIFQKsiVFjDFPT2L95R9FpP5tY9N5z5ClWmG5/NqYwIa3MbRsfAU8fnNkrEjzpW7fbGI8xzPqBSTBc8RWB5UVV5YdgVb3xF3OW2kLkJiJGcwWaUjBuiEM+r7ZbO2v95xATstyPJPVf37SabsFDN1EqFezKZdEs+tNNviCNQq7+8jb+n2B4c1pGc9bCZHfJTQ46L5Qrop+Y+STp1gmQThOD0zgvJUpt+mRVnjF2Puu1THDFlzx7gBrn7CSVXjjEXXx3KtzVnmWcuEPbXRZXWrDOeeNSIyvGA8AC2xB7KOyBM12EaYYC5M+5pf1WLNDDY9R0HqNgfDSPkDr6aTzIkw9iLMJG8JWEGEt8aNMMckU7E5TqKbZNsrXY3iuqzXAXI0vO/bYGGIEvW2AQ4OY65ffTLAoLoHsgcqsIj99/NqKeGqre+nJrjr0AroZeiZVMIMl3Aukt0gtysZ/m78GABSVLr/mdVyeMXSDkPM+AfOE4XHYhNcPzmXMujWeL3Ffc9rd+39Ma1vezXnS1zErPRzCqafGanYExFgysz7VGq4F8iMx/ymrs/7Me7mGgefzyWYT/MlybPCZZ4g1G5juWLzebrN0Fx1AP08iXPoaHg5cPFQYs5zlal8//FXiJ86AYP2iamW51l+aInN5vvYJLi4l8oEJmWvPeldInaV4V/oDSHHSaarCFoqnguPxcydJB4BKstDLhyN+mr3+gLBs4QB+CVXgVyC6Tq9MzCiwzVNAQ/lRbaVFAbZYob6hXa5iJz3u1DWOJCFlNTEkq560hClQYX4nXMHqIyW8EckEQAct68J1R6Fy+K0S8itPEEsm+q/3QpPY5bFyJ5PM8bOM/lYYVGG3sp+9QdhKQ6qi2tOwq84I8tX3IiTpbXU2A6WYigYpdbt3YYHZWK4FDQ5TFecx5L9TYRUWrkfS6UdBhMcwCsVaJvAleFodl1RRuSTvYKMcZI07UYRGKdGNzC412k0qSY2HjICgKv2VxsGOFs4B10Ie21hO0TIj9E1Slb3JCWuo2IH2dpNf0or1c3KC8FlBGGrwDXi1JUnJ6nOMQXZ+R0T/C8f+yA7IIfoduNsC1nHlKJF3324/HeBfGoGsoiOsc2jhJo0xHNfmkqLb0sM1agcBhhp/uyNe/YMDMtdOuZ+aqlyieIuiBxkYDnUNwz/isJ5GVuSgxXko/6uPUFNcy6w4kah/gVM6ogxFJgJijlcKWKle89ktkzBJ7tDIgEsFwy83XYkZj8vSlxATObw2GeqYXHUrLZy5xko8tYtLQ+ULoWB3+JjatKQjOrGP3H6MXfu+UNL1UWdFau38zbCylLT/bLBcthH93A8yICFvH+oCFRloU9CXYMxh3pColW79HcuU2w0RVW2QWSRIGYeOmO2ERwImBWB/t3WodIc1LAjRXsxdEt6xPIZp8j71nN382191mfFBAem0g657kgSgFjf/g8WJH5L9/FfW/NmT1aOQCEmMu12d5NIySleHnIK2CW+fxwIxbHTvpHDcFAnjetlzRD7P0X5ZlTgNyyNxYk1/X4KHKYeAI60Pjz0Xno88KfWVdcrEFa93SVsZpin+YCPGi3TAxcwIwJsNQuCoW1hAUdqY0qKTmfJdzGtd/m97u+zrjXXBVyVk1L3X7sx+HmIZ1yBj7MIVq14x65HmPTm4giuyceNJ0tcUmHXN4/75Fqv47JHZ2dKGo9EYxJLAXDtJejOby4fXCL1jJpktsldDxRB/KVBpmlEEzOklWd+8hgCux6ovAAAy7OssWdHKJwFeKiYhk2ItbmD6BTOG/2B432uxNCvuXS6NA/Y4Qs0kYNu6o0MSeI2k7JUztom3gakXfTyJ2XhylpN7HJ+XTCD4eTiHnkfOEKZHGZLlVVkEplDIgSUSSZ1zlJoky4OanJGKGx/eioLF2X9mMb6oZ3iMjgWosf9J0ngGGeqCk8Yw7Rhc71W7jf03jfhjLZRJ+fvDT4twZBRlk/Jokzw5WnVpBpnvTryBsqp5HnuFirK7fyiZf5+5g5cjXwlr6dZzUGm/iec+zABVNrtkeERQczvFXDkUXv36fyFCMzW7LEzRUQrJ3p8oLXtUFe/2ybnVsWPBPlWh6Id0EETdeRQfNFuLdFHvveXwFQwO+5+n/72HePnxUzeacb3pNW+1XCvqxEdNVaC7vSpihSe3h7JY7yqrt0rUl+pzcdqUrQAlD3kh94UVBDnZG3fMYev+9HSaKLFQPYXDrYWHrOwiLP8pGjg4V39UNyFGFpbxtJg8KQ2GKLdt3Nzn388s3QZg84dk2dNLSvHLuu9jLKw6uoe64ajY0Yv1PkgnRPUTR2oCZCW6hno/CVdxv3R7Vt6WPe5mQKd187wUPThjWOWGxMiGfTJZU3oBqgdUf1DkZlaAhzxEkUK6wR3ayHUIY10F2XOEwYLwUVJYhb9zUc/lvtFLPTCCqXI0ePNzg1R1sbNcCftxRF6zLX3c9upD0mwLh8BXtptzXXXe/MntK4s6g9zVCYWbc/bQYuHawU0g/5vZKY5wNEQffJ/OZ22btH0d+9HYWFvGXd7vX3rtuvuN232xOzhJ5aBOGaMkmGsGUZDA7U3ZXI5tJfoT41rd+U0WxtkYP40Qf9E9EJhEQsMjb3bY+ZuFk1UY4PIYNi7QfeV6DjsW6H+3mn1eAx9KeDLru/viO/XqC+Tz2vnbnPS8Bdd0N5EVjFiW2oUL64AXopsqccD0n4UroiB+uHvUynvNtvHWSGnsW2kKFkzL4Og4xa48o98hJetZgAWvDZ2GKqgm+r8ruBht7jF3rI25qGMsWO/AJchqLYHHEolTbSMMR/4qT5MoulIB/nfCPM/zKR/fbIeAwAPu6TeRuRDkv1Mze6kvNcQOE/SDBMashxn2KtrCbTh3LVF1Nnd2w+f1x/8eC9Et7dKnC//pQ6pIlwmThMUpUW/tProPXB94Mfmv1bMz0bwl8NttS1EM8vL/KojX0WVATWwIAYIyoe9iL2UDInh7VS2UlqYd6TRrDpxNimkAztMlJOr0mxee2YEHrBRgTUf17a+npShdKwE5lVVIzWh9MaivLPybW/j0C34wIQwoP3Xzas659duB+FkJZpQ0rFMNKsYH5JYcrYXVuC/S/PPVyU81DF06Pq6Qw9HQaDcSA1V0BrTGUS42sKsgjtkPT/i7xswRcjZNSty+igIOzpm6CrQTOk660B0MuESPnIiPOnCiFKx3zH8MhP7wB8sMHSqr/jOS/Lng5Q5uKd/1EPX1cZsjYN15Ldxbh7GLE09Smyn7DFj3BYT5X0X6XrjaR+oKeB6/nJOAm9REWR+PZqT3sEoX/pNglna2iiLcEy0VpJ+dS6N3zJpY0Kk62ndIHxZWNXcmWt3ATBmb632vDSDoTLzxSpT3RH0HS+qkaPP3v7zDMXXKCSOrQjT4BnYAlUd8tkmqcyGgv67YtzQR7U4gCwb8ZF2fzlao3n4OvQRRGKA7z57SHZBx1ZH3KocwwQnZ+WzMU+6NpolFgSqursUB08zNWZ1ZIIf7RaWRqkp9g2Yv4uHPMX8sNVTkbsDSCIXzGm2eV4sUFSVqAvvF1DVMhyLTpgn42m/jEY6AwNBi2t1Wa7iQ/IsS8mTWGvEB7tVbYvop6gVaS1Ts2NEF+C7zb+XvT+W1tmNMMKmqNZGjMVrwt1jNcbHx/va0/wZEd5sQkvW1VX1epWvBDAmFXuF+AAILPfT32Yfv7zY4KMwJuY39BB1BHIsWGB6YsMRYYMFRCddGaX8dwmLdLYYAD4wqQ90SDmQrDCJ8Kn01DC3Lkn9IhU/kXXKu102XThqzQbAaNSgMoJ6OdyzBLEuI9hamEdf/7LV30Se0DWbzmsLVWF3svNeXZXl3Z7tv7+Xf17XjVimGQSaYUgQ1oV8aPT1zFurX/MAsDph3kbVaBAbHf75Z9RgAPl/7hkRYr+XFmWIQw8DXJ8wYInau520SfH3WI7GYUi4953uRsjSPMJVVsFJk2skMH+N3tQQBIhAMKRMaq0TMGbIsvRH5xzQMf5vU8Fzp8x75z/8aN8F6ze5pV+PtgANm23PrbwvT/Mvlh3Zc+/QyZFne0WCKWTLqPvHhUiFndqiA5vYJjAl7bq1etxfGt/p8SR3RgzVMeAHGWNy6i4wo4G5DfAmT/KPNYK2Z2IUe8TPaJ6Tf6edL7Q3+YSuyok6dBtf08TzbbZk1C5nq7HFy3BibBzlAGhZQFiwdF8aUptHnp9I59nENv+mmdJx6yVHmj86bMmlaHu18M4y3mtRAx59pc96kU5TcZ7nHsbTU2lMs3ike8THjO5zYkEMAeyv+r8ryB0OU6BoLM/Z2NGtdqbBMbXVhE7n8fu590EA9EhE6p8k0uVRZMWsifQhzMXYN2SnwC7qT4ThgrvgLVJQstIvgcoKM41oqumQ8cIjdc78y9/xsaZEzTYpTXEBKq1L8galsWpvhlRFgf35EtdY3phjNIenhgJwUwyzX6R9/U8k/MGfz6mN+wM9Y1O7jv6cc+StGaaJutUCx8smYQuDI8O1+cxN49oDmFtjzOCbFwkBv427O6dHAsM35hgXFPx8JWIUgrRKxmz/jAxZHi+pyl3LiWzuN5OeS3S1bqlk0P2t/dNqLg84HQd58ta0KGNJgW6flWHs7SnHN7wP3rGVC8oLByza70TJSJn1XWKqUaIqNOnuAPpnyyGiLUwkmy5VUOOz30cmh/6HHt8HMS1Xv17/Y0reDbL3TJiW8u9EF7s/S4nqHIQJ+3fjDctEZyVc5YyLVgwV7FBQ8OvoLCWfEsoXQLQOCM6ryfOEAHH0iJ+weCdc40HH654S3eQIl6thH82ac7AqsC3pxRlr0uWlGyRb8jgdlUDRcT4aWyhD+/H5QaP5KB02rv4QLZxd+50BnnmoPrDxfTkLWUMlwUQG11lDz2G76A9wkq2L+o4EsLlJAeeGYARjQfsgTNIQrIGWyFcU44wZZCSTly5PVDu4yGhG2zs9iy5EEQwOevSaiImUjkxJg8PAr1ZdSy42tHED5ehdfCIgTpdRLjAWRugpGUsf+SjDTsTAPjpWkulP3rEHBvoxrosaNTbeO4tJGp/7mP9ij5bkJOiJMB9W6XBs15IK1aUX2q9tNyv+93gfHsWE5ihfW5il0MT0rp50TLSAfhvR2+fu707bWUGkBqwolovw5AL6PDm04x/3xkM4rrs+JZmjaSg1EeIQ0UM/PMnho1C8X63nfzhT5mwW09TWJepH1vOrx74g2vxu9BZM66XPgPEYmD+nNkcAcyZCegQ6dvlR6mf/ZIi3Tj5kywqDJp05ycMWpQFWJDiT0ryhz8BRXXwkitKS+5CtmtS6xEewFoQeaGy/SHgT4qJPMxce/d+62SVNKjwx0EOecVk1qjD45HUuoov4Eg842e+VBbK40/jnB+nlm7a93fY37aclhkgYwIOspc6FQhv1XI/7OqEhhyYefk4w41os5rg5XKi8NsinwbmPM5y036oSwi30sRFeG7xSpOSBqRiqywwS5UBHty/zXc5gYAVPZ26uYAKElGlUSjp5IRjzo7yL8mJh2IpqiAiz2yqIbI7M5HagFKHh7EAOGG1RtWo87nYhZjiqut7OG8+haCH+/kqYoeZtWqxA73vxhkgw03DL2bJPBUmR8Wklj+kyqCy7R6E83Eh7dxVdhqjoxxxWPVpo3RQco6J2xnwakxku8TK1QTZUVuiwjSZmac96Oa/jmOZ4j0ONnvA2rxK/ujbCRXkMrsfJqiWSsFNcEX1vXgh7DJmoUt2hg1HaMdhko3eBjQeKZGf7e9mtDE10cCiIf5zwVseNha4cpDK9jkbpvw7KWNjgoqXQr76y6bwO9+BPn+JXDp5Efe5iQeXgCtEu+VBb4CJrxTkGDmDbvSPeqJni5Mqzx4tsLP8kjUYcAU3U2Yo05a1hFPGDAypteV11XNaE1wxCjOqCT2GfW+NMFNcDbzBKAoXh2rZt27bNW9u2bdvuV9u2bdu2ud1knvkDk5zJuz9z9+OLOp1w2geXqTfDacR7hEprEwlTjE414ch8iMfiGDFp63zFOg0sAes5nG/VPAESGWFayc8DbYTllt5qFcoki9v3Pd3JzTT1ehp5e4/efny7qr+cAU4br4z4SaIL6ROua8dignr6oEc9BGAxWBBcZcVEW+w0bu5edoAlpS3pfDbPGcxreRzRpyOT0SsSEDQcytQTpD5K8KWkn9FoSu94zamEf0+7Zwm8dhTO3BWskeTA0pSzV4MaRQVGjaDQdf2L/UOAndi6yQL/D9eN/vKzHsL0g2namHoziDE=
*/