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
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
*/