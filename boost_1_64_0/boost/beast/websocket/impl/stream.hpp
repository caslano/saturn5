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
6m7U86h3UWkxSVZP1HhUMWoD6kHUS6gPUKl6xqfFfgNd7m/Kd48iOX/TmkvchYV1ujVH8krrJoFK9ij0agthsrI3fBy1tzllDP4c9ZDUd/UbqzvRSga0Tc/DL0bPo/pU1rGQt2Udy+QzBgy29N0vFzrv+pt3GdXvBjrvDhWbdwOcdxdUv+vrvMurfpfpvBth3vXLct51qn5nfjex+t0g591TReZdf+mX8u6ACUeW6EuNfpCOe3nrfBn3CjhvN8e8k7Jr+qsx8fKun45vme8fH0550iKkC/yCH21EPlm7uEb9lFtRWR5SR6k8KdpR89SNon/PPo/f2oGaThnciHoZpeOXnnOjJxk3WosbU9BfL/qP7XL+3YWaQ77cjPo9qtqN5flLlhWae1TuEjsv2rMpO1ehsikvy1EHUWavnMj0cK3PKiku0PLQBO4T80o5mT7VyJTll+cvzS0sWWDOV96yJCp3kuoZnV0qY2BmvZrlrFfTcZRHRP4cq4vH3QWluUtLC4gG4+54cSe5hrunUAYbW4SxLS7jfgkqWs5uIeGuaWL+RtVdtmrLU8SrP0/pO4lr2RM0UvxEnunszU9ZyZY8H2v74w2UTX5qX+bJTwWF7OTD+bD8pPL9Vc9uPdG3ca2/xCWn/WHku5o7acaK/hfWLPy21VmD6djTtWzNnTWXIvsbawH/7jRj4+om9b/nTFz52epxz91lmuamfvWeoZwn5qtYl5hkzkyOk/58XOAZ4U3gE2InXvWOfKPQts0okX+M9VkbAn7Dt4dR/b1c7HC/NHkqTs/j/bWeyfuS1N+15qGJteYhM8ZFTDj7zcw+NI1/XzspVu+6GKPt8BGoN3E309tuLS4prvTnGRMPI0W2H/Fga75x7Kf6487Ew5linm6ZNmTtbfCJtbXBh2pYnjtJZGV8qLXSlsscPGFhPXPd5aDKTg+TV3uIfgRrZlvSmp1r2soPyPvmYeVD3ckw92hkiH6kvcNqHFQ2TNugi8iNse9yyoVxq4trDHcxkydi0fj79gLNf+rvP0X14t+RMla6W/Rb1L+OG9Vre/eK+ZWkS5p/Ha3IlCDTUWTG27uZe+xNHyGBPNSTuG9GHyHmzPjE5NgWSY3jE2Iac4tzUlxyfJNkbnVOS+64doeZfzL5nvzuL8MmLGXyO2mh5e9kMZ9k70QirLytF5kE6XtomcOfMnYtbCFn79c9VxJtG3Qo9K7dzQsog0UBZbDMXwb1fZ5Zv6vp6GsjdJZ/WXuLaoV6CPUev5dS6snPYBF2Q/OyymeYvJUl+m1WH20Tv1i1Bxd3NN8aOx1M27qv6G9jPLKRJ70s1/zjWpGZEpheZ2E+UMx3MYZpO/cgSPontiWftiDvUWiT+PuxetyDUFsdSHh4J+HxxOfWVEueB1FpqHs0PtuXeOJTGhzEaNiYg8rPYr1s87D4U5l0/quK86Gi3271wj9TUZegfPFo5mFWi+yZlMEk4vsE7/dK/dESbhe5EdQItj/OTb01WGQKGV/GxygtAybekzTuWx7nOHe+Lxl6t8OzqNaoh1FHsJ8z3x3ncpFSWP5V2f6Bd5dNMuY9zdqFNaLfrvWr5w4zk1dXicw20ecYN7q79mFUzq9Q+WnGvKNZR1Iu+t1aF6t8wD1p2Au8y0TT3NTTa0XuptC2yRdinqB60nuB1o1mD0XFEioRfnukfPOvFPlrsREX9A2WPLlcZO50/aa2PfU3XxBzZv1ww8k3fduKIv9oH7Rd/fJNTkC+CbsbrVPw3Wi6r4F4dterlr5zyebAZfJe4sRTB6xpYcmzQu9Hm4/6CH/lLXDnR71oJLxOVflBml98edKY9zZxfZXoR2l+8edJXWskMpM0Tzo=
*/