//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_IMPL_STREAM_IMPL_HPP
#define BOOST_BEAST_WEBSOCKET_IMPL_STREAM_IMPL_HPP

#include <boost/beast/websocket/rfc6455.hpp>
#include <boost/beast/websocket/detail/frame.hpp>
#include <boost/beast/websocket/detail/hybi13.hpp>
#include <boost/beast/websocket/detail/mask.hpp>
#include <boost/beast/websocket/detail/pmd_extension.hpp>
#include <boost/beast/websocket/detail/prng.hpp>
#include <boost/beast/websocket/detail/service.hpp>
#include <boost/beast/websocket/detail/soft_mutex.hpp>
#include <boost/beast/websocket/detail/utf8_checker.hpp>
#include <boost/beast/http/read.hpp>
#include <boost/beast/http/write.hpp>
#include <boost/beast/http/rfc7230.hpp>
#include <boost/beast/core/buffers_cat.hpp>
#include <boost/beast/core/buffers_prefix.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/flat_static_buffer.hpp>
#include <boost/beast/core/saved_handler.hpp>
#include <boost/beast/core/static_buffer.hpp>
#include <boost/beast/core/stream_traits.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/core/empty_value.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

namespace boost {
namespace beast {
namespace websocket {

template<
    class NextLayer, bool deflateSupported>
struct stream<NextLayer, deflateSupported>::impl_type
    : boost::empty_value<NextLayer>
    , detail::service::impl_type
    , detail::impl_base<deflateSupported>
{
    NextLayer& stream() noexcept
    {
        return this->boost::empty_value<
            NextLayer>::get();
    }

    boost::weak_ptr<impl_type>
    weak_from_this()
    {
        return boost::static_pointer_cast<
            impl_type>(this->detail::service::
                impl_type::shared_from_this());
    }

    boost::shared_ptr<impl_type>
    shared_this()
    {
        return boost::static_pointer_cast<
            impl_type>(this->detail::service::
                impl_type::shared_from_this());
    }

    net::steady_timer       timer;          // used for timeouts
    close_reason            cr;             // set from received close frame
    control_cb_type         ctrl_cb;        // control callback

    std::size_t             rd_msg_max      /* max message size */ = 16 * 1024 * 1024;
    std::uint64_t           rd_size         /* total size of current message so far */ = 0;
    std::uint64_t           rd_remain       /* message frame bytes left in current frame */ = 0;
    detail::frame_header    rd_fh;          // current frame header
    detail::prepared_key    rd_key;         // current stateful mask key
    detail::frame_buffer    rd_fb;          // to write control frames (during reads)
    detail::utf8_checker    rd_utf8;        // to validate utf8
    static_buffer<
        +tcp_frame_size>    rd_buf;         // buffer for reads
    detail::opcode          rd_op           /* current message binary or text */ = detail::opcode::text;
    bool                    rd_cont         /* `true` if the next frame is a continuation */ = false;
    bool                    rd_done         /* set when a message is done */ = true;
    bool                    rd_close        /* did we read a close frame? */ = false;
    detail::soft_mutex      rd_block;       // op currently reading

    role_type               role            /* server or client */ = role_type::client;
    status                  status_         /* state of the object */ = status::closed;

    detail::soft_mutex      wr_block;       // op currently writing
    bool                    wr_close        /* did we write a close frame? */ = false;
    bool                    wr_cont         /* next write is a continuation */ = false;
    bool                    wr_frag         /* autofrag the current message */ = false;
    bool                    wr_frag_opt     /* autofrag option setting */ = true;
    bool                    wr_compress;    /* compress current message */
    bool                    wr_compress_opt /* compress message setting */ = true;
    detail::opcode          wr_opcode       /* message type */ = detail::opcode::text;
    std::unique_ptr<
        std::uint8_t[]>     wr_buf;         // write buffer
    std::size_t             wr_buf_size     /* write buffer size (current message) */ = 0;
    std::size_t             wr_buf_opt      /* write buffer size option setting */ = 4096;
    detail::fh_buffer       wr_fb;          // header buffer used for writes

    saved_handler           op_rd;          // paused read op
    saved_handler           op_wr;          // paused write op
    saved_handler           op_ping;        // paused ping op
    saved_handler           op_idle_ping;   // paused idle ping op
    saved_handler           op_close;       // paused close op
    saved_handler           op_r_rd;        // paused read op (async read)
    saved_handler           op_r_close;     // paused close op (async read)

    bool    idle_pinging = false;
    bool    secure_prng_ = true;
    bool    ec_delivered = false;
    bool    timed_out = false;
    int     idle_counter = 0;

    detail::decorator       decorator_opt;  // Decorator for HTTP messages
    timeout                 timeout_opt;    // Timeout/idle settings

    template<class... Args>
    impl_type(Args&&... args)
        : boost::empty_value<NextLayer>(
            boost::empty_init_t{},
            std::forward<Args>(args)...)
        , detail::service::impl_type(
            this->boost::empty_value<NextLayer>::get().get_executor().context())
        , timer(this->boost::empty_value<NextLayer>::get().get_executor())
    {
        timeout_opt.handshake_timeout = none();
        timeout_opt.idle_timeout = none();
        timeout_opt.keep_alive_pings = false;
    }

    void
    shutdown() override
    {
        op_rd.reset();
        op_wr.reset();
        op_ping.reset();
        op_idle_ping.reset();
        op_close.reset();
        op_r_rd.reset();
        op_r_close.reset();
    }

    void
    open(role_type role_)
    {
        // VFALCO TODO analyze and remove dupe code in reset()
        timer.expires_at(never());
        timed_out = false;
        cr.code = close_code::none;
        role = role_;
        status_ = status::open;
        rd_remain = 0;
        rd_cont = false;
        rd_done = true;
        // Can't clear this because accept uses it
        //rd_buf.reset();
        rd_fh.fin = false;
        rd_close = false;
        wr_close = false;
        // These should not be necessary, because all completion
        // handlers must be allowed to execute otherwise the
        // stream exhibits undefined behavior.
        wr_block.reset();
        rd_block.reset();

        wr_cont = false;
        wr_buf_size = 0;

        this->open_pmd(role);
    }

    void
    close()
    {
        timer.cancel();
        wr_buf.reset();
        this->close_pmd();
    }

    void
    reset()
    {
        BOOST_ASSERT(status_ != status::open);
        timer.expires_at(never());
        cr.code = close_code::none;
        rd_remain = 0;
        rd_cont = false;
        rd_done = true;
        rd_buf.consume(rd_buf.size());
        rd_fh.fin = false;
        rd_close = false;
        wr_close = false;
        wr_cont = false;
        // These should not be necessary, because all completion
        // handlers must be allowed to execute otherwise the
        // stream exhibits undefined behavior.
        wr_block.reset();
        rd_block.reset();

        // VFALCO Is this needed?
        timer.cancel();
    }

    void
    time_out()
    {
        timed_out = true;
        change_status(status::closed);
        close_socket(get_lowest_layer(stream()));
    }

    // Called just before sending
    // the first frame of each message
    void
    begin_msg()
    {
        wr_frag = wr_frag_opt;
        wr_compress =
            this->pmd_enabled() && wr_compress_opt;

        // Maintain the write buffer
        if( this->pmd_enabled() ||
            role == role_type::client)
        {
            if(! wr_buf ||
                wr_buf_size != wr_buf_opt)
            {
                wr_buf_size = wr_buf_opt;
                wr_buf = boost::make_unique_noinit<
                    std::uint8_t[]>(wr_buf_size);
            }
        }
        else
        {
            wr_buf_size = wr_buf_opt;
            wr_buf.reset();
        }

        //
    }

    //--------------------------------------------------------------------------

    template<class Decorator>
    request_type
    build_request(
        detail::sec_ws_key_type& key,
        string_view host, string_view target,
        Decorator const& decorator);

    void
    on_response(
        response_type const& res,
        detail::sec_ws_key_type const& key,
        error_code& ec);

    template<class Body, class Allocator, class Decorator>
    response_type
    build_response(
        http::request<Body,
            http::basic_fields<Allocator>> const& req,
        Decorator const& decorator,
        error_code& result);

    // Attempt to read a complete frame header.
    // Returns `false` if more bytes are needed
    template<class DynamicBuffer>
    bool
    parse_fh(detail::frame_header& fh,
        DynamicBuffer& b, error_code& ec);

    std::uint32_t
    create_mask()
    {
        auto g = detail::make_prng(secure_prng_);
        for(;;)
            if(auto key = g())
                return key;
    }

    template<class DynamicBuffer>
    std::size_t
    read_size_hint_db(DynamicBuffer& buffer) const
    {
        auto const initial_size = (std::min)(
            +tcp_frame_size,
            buffer.max_size() - buffer.size());
        if(initial_size == 0)
            return 1; // buffer is full
        return this->read_size_hint_pmd(
            initial_size, rd_done, rd_remain, rd_fh);
    }

    template<class DynamicBuffer>
    void
    write_ping(DynamicBuffer& db,
        detail::opcode code, ping_data const& data);

    template<class DynamicBuffer>
    void
    write_close(DynamicBuffer& db, close_reason const& cr);

    //--------------------------------------------------------------------------

    void
    set_option(timeout const& opt)
    {
        if( opt.handshake_timeout == none() &&
            opt.idle_timeout == none())
        {
            // turn timer off
            timer.cancel();
            timer.expires_at(never());
        }

        timeout_opt = opt;
    }

    // Determine if an operation should stop and
    // deliver an error code to the completion handler.
    //
    // This function must be called at the beginning
    // of every composed operation, and every time a
    // composed operation receives an intermediate
    // completion.
    //
    bool
    check_stop_now(error_code& ec)
    {
        // Deliver the timeout to the first caller
        if(timed_out)
        {
            timed_out = false;
            ec = beast::error::timeout;
            return true;
        }

        // If the stream is closed then abort
        if( status_ == status::closed ||
            status_ == status::failed)
        {
            //BOOST_ASSERT(ec_delivered);
            ec = net::error::operation_aborted;
            return true;
        }

        // If no error then keep going
        if(! ec)
            return false;

        // Is this the first error seen?
        if(ec_delivered)
        {
            // No, so abort
            ec = net::error::operation_aborted;
            return true;
        }

        // Deliver the error to the completion handler
        ec_delivered = true;
        if(status_ != status::closed)
            status_ = status::failed;
        return true;
    }

    // Change the status of the stream
    void
    change_status(status new_status)
    {
        switch(new_status)
        {
        case status::handshake:
            break;

        case status::open:
            break;

        case status::closing:
            //BOOST_ASSERT(status_ == status::open);
            break;

        case status::failed:
        case status::closed:
            // this->close(); // Is this right?
            break;

        default:
            break;
        }
        status_ = new_status;
    }

    // Called to disarm the idle timeout counter
    void
    reset_idle()
    {
        idle_counter = 0;
    }

    // Maintain the expiration timer
    template<class Executor>
    void
    update_timer(Executor const& ex)
    {
        switch(status_)
        {
        case status::handshake:
            BOOST_ASSERT(idle_counter == 0);
            if(! is_timer_set() &&
                timeout_opt.handshake_timeout != none())
            {
                timer.expires_after(
                    timeout_opt.handshake_timeout);
                timer.async_wait(
                    timeout_handler<Executor>(
                        ex, this->weak_from_this()));
            }
            break;

        case status::open:
            if(timeout_opt.idle_timeout != none())
            {
                idle_counter = 0;
                if(timeout_opt.keep_alive_pings)
                    timer.expires_after(
                        timeout_opt.idle_timeout / 2);
                else
                    timer.expires_after(
                        timeout_opt.idle_timeout);
                timer.async_wait(
                    timeout_handler<Executor>(
                        ex, this->weak_from_this()));
            }
            else
            {
                timer.cancel();
                timer.expires_at(never());
            }
            break;

        case status::closing:
            if(timeout_opt.handshake_timeout != none())
            {
                idle_counter = 0;
                timer.expires_after(
                    timeout_opt.handshake_timeout);
                timer.async_wait(
                    timeout_handler<Executor>(
                        ex, this->weak_from_this()));
            }
            else
            {
                // VFALCO This assert goes off when there's also
                // a pending read with the timer set. The bigger
                // fix is to give close its own timeout, instead
                // of using the handshake timeout.
                // BOOST_ASSERT(! is_timer_set());
            }
            break;

        case status::failed:
        case status::closed:
            // this->close(); // Is this right?
            timer.cancel();
            timer.expires_at(never());
            break;
        }
    }

private:
    bool
    is_timer_set() const
    {
        return timer.expiry() != never();
    }

    template<class Executor>
    class timeout_handler
        : boost::empty_value<Executor>
    {
        boost::weak_ptr<impl_type> wp_;

    public:
        timeout_handler(
            Executor const& ex,
            boost::weak_ptr<impl_type>&& wp)
            : boost::empty_value<Executor>(
                boost::empty_init_t{}, ex)
            , wp_(std::move(wp))
        {
        }

        using executor_type = Executor;

        executor_type
        get_executor() const noexcept
        {
            return this->get();
        }

        void
        operator()(error_code ec)
        {
            // timer canceled?
            if(ec == net::error::operation_aborted)
                return;
            BOOST_ASSERT(! ec);

            // stream destroyed?
            auto sp = wp_.lock();
            if(! sp)
                return;
            auto& impl = *sp;

            switch(impl.status_)
            {
            case status::handshake:
                impl.time_out();
                return;

            case status::open:
                // timeout was disabled
                if(impl.timeout_opt.idle_timeout == none())
                    return;

                if( impl.timeout_opt.keep_alive_pings &&
                    impl.idle_counter < 1)
                {
                    idle_ping_op<Executor>(sp, get_executor());

                    ++impl.idle_counter;
                    impl.timer.expires_after(
                        impl.timeout_opt.idle_timeout / 2);
                    impl.timer.async_wait(std::move(*this));
                    return;
                }

                impl.time_out();
                return;

            case status::closing:
                impl.time_out();
                return;

            case status::closed:
            case status::failed:
                // nothing to do?
                return;
            }
        }
    };
};

//--------------------------------------------------------------------------
//
// client
//
//--------------------------------------------------------------------------

template<class NextLayer, bool deflateSupported>
template<class Decorator>
request_type
stream<NextLayer, deflateSupported>::impl_type::
build_request(
    detail::sec_ws_key_type& key,
    string_view host, string_view target,
    Decorator const& decorator)
{
    request_type req;
    req.target(target);
    req.version(11);
    req.method(http::verb::get);
    req.set(http::field::host, host);
    req.set(http::field::upgrade, "websocket");
    req.set(http::field::connection, "upgrade");
    detail::make_sec_ws_key(key);
    req.set(http::field::sec_websocket_key, key);
    req.set(http::field::sec_websocket_version, "13");
    this->build_request_pmd(req);
    decorator_opt(req);
    decorator(req);
    if(! req.count(http::field::user_agent))
        req.set(http::field::user_agent,
            BOOST_BEAST_VERSION_STRING);
    return req;
}

// Called when the WebSocket Upgrade response is received
template<class NextLayer, bool deflateSupported>
void
stream<NextLayer, deflateSupported>::impl_type::
on_response(
    response_type const& res,
    detail::sec_ws_key_type const& key,
    error_code& ec)
{
    auto const err =
        [&](error e)
        {
            ec = e;
        };
    if(res.result() != http::status::switching_protocols)
        return err(error::upgrade_declined);
    if(res.version() != 11)
        return err(error::bad_http_version);
    {
        auto const it = res.find(http::field::connection);
        if(it == res.end())
            return err(error::no_connection);
        if(! http::token_list{it->value()}.exists("upgrade"))
            return err(error::no_connection_upgrade);
    }
    {
        auto const it = res.find(http::field::upgrade);
        if(it == res.end())
            return err(error::no_upgrade);
        if(! http::token_list{it->value()}.exists("websocket"))
            return err(error::no_upgrade_websocket);
    }
    {
        auto const it = res.find(
            http::field::sec_websocket_accept);
        if(it == res.end())
            return err(error::no_sec_accept);
        detail::sec_ws_accept_type acc;
        detail::make_sec_ws_accept(acc, key);
        if(acc.compare(it->value()) != 0)
            return err(error::bad_sec_accept);
    }

    ec = {};
    this->on_response_pmd(res);
    this->open(role_type::client);
}

//------------------------------------------------------------------------------

// Attempt to read a complete frame header.
// Returns `false` if more bytes are needed
template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
bool
stream<NextLayer, deflateSupported>::impl_type::
parse_fh(
    detail::frame_header& fh,
    DynamicBuffer& b,
    error_code& ec)
{
    if(buffer_bytes(b.data()) < 2)
    {
        // need more bytes
        ec = {};
        return false;
    }
    buffers_suffix<typename
        DynamicBuffer::const_buffers_type> cb{
            b.data()};
    std::size_t need;
    {
        std::uint8_t tmp[2];
        cb.consume(net::buffer_copy(
            net::buffer(tmp), cb));
        fh.len = tmp[1] & 0x7f;
        switch(fh.len)
        {
            case 126: need = 2; break;
            case 127: need = 8; break;
            default:
                need = 0;
        }
        fh.mask = (tmp[1] & 0x80) != 0;
        if(fh.mask)
            need += 4;
        if(buffer_bytes(cb) < need)
        {
            // need more bytes
            ec = {};
            return false;
        }
        fh.op   = static_cast<
            detail::opcode>(tmp[0] & 0x0f);
        fh.fin  = (tmp[0] & 0x80) != 0;
        fh.rsv1 = (tmp[0] & 0x40) != 0;
        fh.rsv2 = (tmp[0] & 0x20) != 0;
        fh.rsv3 = (tmp[0] & 0x10) != 0;
    }
    switch(fh.op)
    {
    case detail::opcode::binary:
    case detail::opcode::text:
        if(rd_cont)
        {
            // new data frame when continuation expected
            ec = error::bad_data_frame;
            return false;
        }
        if(fh.rsv2 || fh.rsv3 ||
            ! this->rd_deflated(fh.rsv1))
        {
            // reserved bits not cleared
            ec = error::bad_reserved_bits;
            return false;
        }
        break;

    case detail::opcode::cont:
        if(! rd_cont)
        {
            // continuation without an active message
            ec = error::bad_continuation;
            return false;
        }
        if(fh.rsv1 || fh.rsv2 || fh.rsv3)
        {
            // reserved bits not cleared
            ec = error::bad_reserved_bits;
            return false;
        }
        break;

    default:
        if(detail::is_reserved(fh.op))
        {
            // reserved opcode
            ec = error::bad_opcode;
            return false;
        }
        if(! fh.fin)
        {
            // fragmented control message
            ec = error::bad_control_fragment;
            return false;
        }
        if(fh.len > 125)
        {
            // invalid length for control message
            ec = error::bad_control_size;
            return false;
        }
        if(fh.rsv1 || fh.rsv2 || fh.rsv3)
        {
            // reserved bits not cleared
            ec = error::bad_reserved_bits;
            return false;
        }
        break;
    }
    if(role == role_type::server && ! fh.mask)
    {
        // unmasked frame from client
        ec = error::bad_unmasked_frame;
        return false;
    }
    if(role == role_type::client && fh.mask)
    {
        // masked frame from server
        ec = error::bad_masked_frame;
        return false;
    }
    if(detail::is_control(fh.op) &&
        buffer_bytes(cb) < need + fh.len)
    {
        // Make the entire control frame payload
        // get read in before we return `true`
        return false;
    }
    switch(fh.len)
    {
    case 126:
    {

        std::uint16_t len_be;
        BOOST_ASSERT(buffer_bytes(cb) >= sizeof(len_be));
        cb.consume(net::buffer_copy(
            net::mutable_buffer(&len_be, sizeof(len_be)), cb));
        fh.len = endian::big_to_native(len_be);
        if(fh.len < 126)
        {
            // length not canonical
            ec = error::bad_size;
            return false;
        }
        break;
    }
    case 127:
    {
        std::uint64_t len_be;
        BOOST_ASSERT(buffer_bytes(cb) >= sizeof(len_be));
        cb.consume(net::buffer_copy(
            net::mutable_buffer(&len_be, sizeof(len_be)), cb));
        fh.len = endian::big_to_native(len_be);
        if(fh.len < 65536)
        {
            // length not canonical
            ec = error::bad_size;
            return false;
        }
        break;
    }
    }
    if(fh.mask)
    {
        std::uint32_t key_le;
        BOOST_ASSERT(buffer_bytes(cb) >= sizeof(key_le));
        cb.consume(net::buffer_copy(
            net::mutable_buffer(&key_le, sizeof(key_le)), cb));
        fh.key = endian::little_to_native(key_le);
        detail::prepare_key(rd_key, fh.key);
    }
    else
    {
        // initialize this otherwise operator== breaks
        fh.key = 0;
    }
    if(! detail::is_control(fh.op))
    {
        if(fh.op != detail::opcode::cont)
        {
            rd_size = 0;
            rd_op = fh.op;
        }
        else
        {
            if(rd_size > (std::numeric_limits<
                std::uint64_t>::max)() - fh.len)
            {
                // message size exceeds configured limit
                ec = error::message_too_big;
                return false;
            }
        }
        if(! this->rd_deflated())
        {
            if(rd_msg_max && beast::detail::sum_exceeds(
                rd_size, fh.len, rd_msg_max))
            {
                // message size exceeds configured limit
                ec = error::message_too_big;
                return false;
            }
        }
        rd_cont = ! fh.fin;
        rd_remain = fh.len;
    }
    b.consume(b.size() - buffer_bytes(cb));
    ec = {};
    return true;
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
void
stream<NextLayer, deflateSupported>::impl_type::
write_ping(DynamicBuffer& db,
    detail::opcode code, ping_data const& data)
{
    detail::frame_header fh;
    fh.op = code;
    fh.fin = true;
    fh.rsv1 = false;
    fh.rsv2 = false;
    fh.rsv3 = false;
    fh.len = data.size();
    fh.mask = role == role_type::client;
    if(fh.mask)
        fh.key = create_mask();
    detail::write(db, fh);
    if(data.empty())
        return;
    detail::prepared_key key;
    if(fh.mask)
        detail::prepare_key(key, fh.key);
    auto mb = db.prepare(data.size());
    net::buffer_copy(mb,
        net::const_buffer(
            data.data(), data.size()));
    if(fh.mask)
        detail::mask_inplace(mb, key);
    db.commit(data.size());
}

template<class NextLayer, bool deflateSupported>
template<class DynamicBuffer>
void
stream<NextLayer, deflateSupported>::impl_type::
write_close(DynamicBuffer& db, close_reason const& cr)
{
    using namespace boost::endian;
    detail::frame_header fh;
    fh.op = detail::opcode::close;
    fh.fin = true;
    fh.rsv1 = false;
    fh.rsv2 = false;
    fh.rsv3 = false;
    fh.len = cr.code == close_code::none ?
        0 : 2 + cr.reason.size();
    if(role == role_type::client)
    {
        fh.mask = true;
        fh.key = create_mask();
    }
    else
    {
        fh.mask = false;
    }
    detail::write(db, fh);
    if(cr.code != close_code::none)
    {
        detail::prepared_key key;
        if(fh.mask)
            detail::prepare_key(key, fh.key);
        {
            auto code_be = endian::native_to_big<std::uint16_t>(cr.code);
            auto mb = db.prepare(2);
            net::buffer_copy(mb,
                net::const_buffer(&code_be, sizeof(code_be)));
            if(fh.mask)
                detail::mask_inplace(mb, key);
            db.commit(2);
        }
        if(! cr.reason.empty())
        {
            auto mb = db.prepare(cr.reason.size());
            net::buffer_copy(mb,
                net::const_buffer(
                    cr.reason.data(), cr.reason.size()));
            if(fh.mask)
                detail::mask_inplace(mb, key);
            db.commit(cr.reason.size());
        }
    }
}

} // websocket
} // beast
} // boost

#endif

/* stream_impl.hpp
xfe7a8altSJolWgWiIDXwefp+SFss1vv9VPIhREZPf2nxTinwpUsWTrmLPjktm9T7T++TPndNPxT3p2CA0l3Osg9Egp7XtjMH5OqRqxrgGGwPkrpWGZmnhLG8d56A4oz6WBQiN9SUIwqlajBm1AHEM0wIGbFm7xv23ej7ITM6wZF3S5Q9InHQYUwBlxsnq/VUilh/FNIcZOIgEEPe/4M7IynrUgkCov/tDFn4CTeK0FAMlrf4/KWuXWOohRkXVMbOUZDPjViOn0Jp+ZEDOZMBzLLilO6oUgdrTf4KgiCNf+bugny+mWTNxNWOuNPBOobhmwF5Qyx0YXTKZ/4XIHPy4c3KgCDgp91GR0FeIxELZb7WInlGca9kDsCPUo4M4PZdlpmKBfsVEj9LMTEquazcSCaDJiNNZBhoC1R2k5kImie042lGi7hUkp9Udt0UKw/yGYdxf/tMaMpHV10TSnJkwxHTdSGJcSaelqdHppXi8XW3ktWIhQpj5oJkGOXPtMEEODPbU42tJ+RlB5R3xYPRtG/k4563oRaPWaue9NnpHSRWkx0W2MULHOMpBdviNxQCiKBwHe2vquUeoSSzHUQwvtQVoTIU7e4WYPr9IcaxVv+ro69p8+hdU0mBEoXsOEnRaFOhp4bEDcG/3XPMPwoBlAfTLR4bAd8+2cM06ScyQ7fMlYSpd7hl7CnBz+uEdrW0PaiLSyDTc3FAPbAYHSpe6PWZvq2EUUyiAsCExCkLe6BbK2oTWPw2H1m3pPXauAM+3QwLsgVrLlKOY2TFOQqJwGkmA0HY7awqpwgJNo1HM0/3IjzH9r7j4mvpGFQCO1nmVAcoJ52CbOm2DWZgwC4s1E+PeCG/mis8/1HRpAIK+gKr2FrlUGDRm2IKAbBb19YbVIJfK4dbsYM7MJMzI8QSS66tPb1SOaj7jQk7QM32mq23VAwDsBEG0cfTL08XHDpIIslt6fBmRUenisRRvYIgL9E1oQb1LuXOTIR9XJRLh+t8xL1JzQZo2yi7Q+aNfyXWWaK1VmyoDDZa92+hdIgbUQk1VIbsVBlpBvNqIUg6/AgT/0/ZU9lcfSQvphEt0J5FDoHGioF+vf6jP+woDm4petHeGFgzrd/kxPlWslaTEXYBrDWdqBZsYyWtt7QdWBOXI1XuXy85MRNEiQQw7KIU8Qh0g4KEHomqzF4GB+XjT0lyzbXa2wz6YX1sYsjR5qIMg7yBQAG5gCl9WzjJ6yD933I9lCIweMWyIFI+ZIADZNnZzAVuuUM2/CuFHOf1cqK+BD7PhzRavbMptm4TV33vzmQR0eEyBIjNN4M647SMe6jWIbjueAa0FATKq/ctWCnUzjeO5RmQFaXii69NpVhibPkVOJt9MU2+Bn8g6C7MZTPdRKhViVAOhu9GmYww7i0XOM9s4cwLaqGYOgAxc4YXSnj42JYxSqnqIp/jFeI4LTuv+fDs9iRu0whtK1ygI2xfK+7bZjfEX5zhyJlBqHZm2qzLJIOOm/yvRFEJBdqQWlg9UyyoahRWii2RxlVZ8IBuHWtDe8DdyP148xrN4TSQW7j6RTfupDZEPDB9VBS9DS/SRzN9qLSaVWe1zR5rfI/u0gaickjF9EXTXjxeFGe13KNVNrXOAcxkhCHQx+isvEITyrthl0z86zMjWAWATXwlxbi94lsdwuiOL18YJPWhuJRzNm5U/BsHN57lC+vMHLMzm/1BfBW0UG0UeyHNXMG7nS6fhK04v8zDxFfyttEdrqQJH8uNs/muyjssGtP41fBLVvHJ8gKTCO717WHJGtVJp8wQkDy9w8zXMK/Mjv7cAhSMYP64Kj4zLpj7UNIxoH3aQ5CNXUFp+QM1UkvGPFuA+gqorng4Iv7+M+P7XIQxKNMOjUxCN1Y/Wa8GkahMiaynKTqXF6Xcisagux4OEEn8DPk07eR65J5hxg5V3GOTGcPdOmyc8a0YPD6FGRltV2+ccl4TC6W3YBXDItDLKtnN9wnpfdIpJgMs3OtFCe86wqwK9i7RA0eLjQO0zWuxhnh05zTutCx1sBgctMoun2zH9d/uLmgfdgRIQz4COEZ4isQPFb78G2jWwU6ejPU3yymMxTnRdzs5ZbEta3l5nnP3CjwOgyDbrdEc1H3ySXUp9Qzr9KmstLYgb0n6k3Zeu/cVxy+jn2Q1eEF5wwxOrk/kihCMttzGjJ7Tk2+H0wInjiqcCZgcloiuQVkIPCSN/Q4UAP7LWiVbV5n4fWtO2k0/gdqCZgj0MXpgqLaUTMtl43B+0jP7bze8b0qVV123Lkf8ZjlCt6pHzT9juk6ZgEO0eEtuvLfWcSYlMTEiINIIqufgJAFYQhb00C8edkEPP9N0QbTbRdI4LNGBxC0DYXwvdl+xy4nk3S/CFt3Sohwx6QTtmt2SMXSxX387M8Yz/7YQbfuWnr3useyI6fZjGcM29VvkQwlt0dU9ENtAsm/ulYjh9V4aC/xWh29+EyDc6njyUPBHxvIK8bT16hcIR9ro2gEX8b0EttJFcsTHwwET/f50/gLViLPEU+ckdfQcPtutw/eTTvi0MWh0Vco4fPqZ4fATRi78v+SUI/uXozsFSPYjfvuu9oGGnMd5NIok7PQv1Q9iiHPgGE0vAj3A5e1V7oat9mVM5qqROuEP92EvweoUnT3AW8VTzho3J3rTgz4gIkxS8r3aDt15veUHS6b6jXf4jhm/tsyWBG5BHzTrNqd/pEYdhcm+tCs0j/3BAH2qBMeIep7GcSZMlQqeMOSp7AvaFEEbINTFB3btmz8stvgvH1iL6AdnbybZ4MHjl2KmkEnJHaOgvWSuE1KErEvGXpmV9l4/xGtr5w4pHY3mA9RM7u/e5byZg5sbGTFsGbS2zjGFTyRye7g9OZCJ2p8tlYMYWkdO8WPAMjY1KEI4bcAnQHGYeRCUY5Alvef4A6wpVucUTyE9Sn2BA4vrbKNNm/TZwAtAWVf6sLSVxN5KU4VoGSL9wgZyLxbCDA9vWrE+878iRpRGNYHNAK992oC1At9/0hHiJCjyK4Z0L5aIp0lgY5jYC14z2vTtwJIMs1oAl+n/uBjScrmBl6sUU2yDbsv9+QALeRXDRtZ92YDOekLRJbG740dM0kFCULzjAtXqVx+48ZgenZxaGqoSUyQD0JNbdJREkcp9x5nt2a2XEF3J1mogus7SZs6gk7/HvAKpgxb5z1aqf4gHQ9jOxWWl7fVXaGeU8IQ2jqer7p62nvmI59yYQvnVoogPaORpOk73LeOeWHSXWq/iVszBcguKPv4t2/RUmHpahJNQdLp/K37QLi7KXkhSXukZjXjTWldGUxdYjFSObwx3M3YV+gWm/Hj4BP+FLJ777sboIUhsyiinNGpUzZYGR/ivxlWNvyWOpoM/s5kcatoxY9zu3dOCLfCMSC3WNG9UiGUw4ZxZiA53rJJQ/2fELcs5jgbuGk0xIC2KMHSK+y6Jrjhb8RwLDVpDPmnietv5FP9Mw7ryvHtrqLnGIaUjbeBBGo5tBbR2qICL4ZrH6dhSG7DcKoUtjPedufv3SPVAaEV4FtF7+Cwa79JsekxBrZpjGmq4RKLIDo8kpWM9NtKdQaCfvjFGzLi8OW+Csk8MW0H3giWG5Fr9CXZvyYhLh1xGh7Covbd4AmKS5m7fRfRnPJXeLWxwoNREa7WO5j5FCAnx2q2kgyCr/DjhiWg3Rx30rWLQf45wcIqvbq24bm5WJtSIU9DpsmaHS46aFUiLf5I+zV3PEDzl5uQreKJpZ5F4myMOIeapQpPb3xRtqf9U7lcB5nF9mGmbfZAYlikcbCYhhjyxaIIepRmtaDJWwtE3ijzbEFITIhfb87Yu8YyzGv7mxwBrXeiC7D6RwzrVzuGtpASvNEbO3TRXnXvaVFO3lw05/1tLiyAn4Y8U9Ifa5UkLbvVFEQOfjJU7gMxWbo6O97DpL60Pilx1EzSmQz5lAW3sQf7NKqW5k+7cTRCh1lr2OJXzNHrDzR1zCgvofYas24jUMK5UYcrTm20fTWm4SSb4BtrrgdcDPd7R17l3A+Z+PUVvCJaenbe/M5xO/3grTq+VIoWzSDUYJdI9fOr9SQ2LvDpvm/Adt8xXzWnw+d+uMEbu8Wpt3pL0tVqk0gWaTg1+nc5rhVIQ9YmwrfcT685XTlaGr0qv8Te9WUfJEzWIfveC7kyhaTvoY3uvKmLGLw42H5eNDBhIC1+1VEOLoYcFKlrZaCaPFecgzOxTlecPVnYQLO90Ipue+9VlQmdGKgH9VSlxd1NYkOiyGIEMeyfvQ5XID8H2Wir834HKD+mwMnzOzaW03kTpaYXnUo1WbN1VYrzugI7GThrAELHtgHm36UNj3rwb4LDqE/TSGf44G8RxWsD2IRXGXCQuBiPCopxwL5Ya/Ko4bWr09hXjBu2iNfgC8KEVdU3HBgnUNfUbdfPs9v+D+UhweG+0bYKe2oTmMmxh86Fk7RfTr/QTyKhYxZ8Ke9Iq8Vz3BGoSDbIhdfUXwZ0CUGJYRYtC4/igg95+f+ARWidvS/9YgapOi+KRkg040TrgfB1WX0h6BCmclDu5et17mbQ5Dey1Zdk00hKu76gjODUaWcSfNpbp1oAGjX9T/HdIGn9zyET4MwDFs9ASnujh/kLDMmx5QtJV1yCKM7wTBHyoa381zs5t3iLkZXTZhdxG6TUMMOLXKbykC3V27Ppp9olf35YajfM6e8VXHuAzUe4eLsW+AV+YMY2EBTGJNVYvIiCc6SWdf6L8oZbFJwY94aUCkGL67+XE06hEq1utOWmLXzvqI1nd1iuyo1k9HVHa5TzcOHP9rTZjThaO6I03EjXPWBx4EOeEnWJyrmnN69s+lyMOEVDIvL5CWBDMVCBtTTTTnnQ0xsgSyC+LpqrkP8JTAo2e8kYQPeLQwXZqU0L6ARFPU7fDalp8cDxpDhbPsp/LXGZINKi8LOfHlrk4AKvr0cNKKAMRhjW4dVgqPIMd+//7rJd3iZoNYxmPrdDnRPic2+Fx4OK9P+vFTt4OxgyUH2iiHw2KZPjGHe5pVW4GHWFH9J40yvv+TniCNYkbWVFKXXfJJIDu4D50zrNIK2/ZfbFcZQrBzd7CpP0IVUv7dTng5d3dd5DpMLPlD0+V9jM07ecdp2NMP1m8aoTgBczx5MZJPs2B73fVkzyutA3tJGiL+vqdPAsI864UMqeOt2w7pCjbae5rOpmDjLifmNRdmz2GuPCkW3Dy1FXgqJfVzyLPqJn5t2DSrY737V2xwXIIOnHa+DCm+ShzEKkL1IBbxuOy4hMn4bJPjCGP1vy984C7P5wEX/O7dUVMhiXjeP9ZE80Jq5159z3ML2T05DaZO0TAwIO00/47vnb/8QXLfGhjWdGYzkZxCpHvUf12tDa+Wwv/LBrvzHHbypLchpJHMtPkhD0RT/UyB6Gy7gjX286UMHNCqlqoXNVAexe2hbySt7odot9r23+u2ORMgf8tOLGe6aAG+U3TiZF5Nc4xrAMbzdVRNERBtLKmN7+qs3PAtRNygpKPXFR+yrB9D/asr3SgxVx4MOSKW81V0mA1jBwHrtOYxAoxM/KhD0fs42Xrtl+/zfz+iq+6nsXiiThQS/3naYs3TIBMT7kJf2wdr3dhreGXL1UhkWiGjk9Lps8Dq/sFTgUVWBu+pJSa0NvnYwHVzUt+UMjd+gm3c6I7BP0HkzAXtHQMhNMb0HlcrPkVLxb+3AAxgpzQRYymFHy2PX7j3TKubCyfpYk+YvGo/jPnHEhtoMwELuNF09h0FVXgmz8vaDi8TFn3Wpsp6MTxxuz82S++ds27Ip/rxvWd2ksG0/En017HsdscgtRZ2gQL2h6ctOT6uY9Nx8/oZatE0G08TwKhCmyJVl4QM4fiC64peYjDP7bEIeBMLwUw9whC9HBJ5XNUfRCStAGtT+r9k5Dit/i0+K8g6Z3eo4bkK3d9iMXsp9X8YMGXVQ24zcq+blMj3tvmHMdpgiU+7jRZEj5ThynPAUfKzj4k0AyZW1vOQRD91kgzCSFd9qGjnPlta6Pp+zwYCJFYPu0gRUn1tm08Jzu0ZNlHR7DRBjzaIX9crYpNoRT4Ae6k6KqCagqbYfTzBpVKHQbpgYufg8RxJpaxg8fQngj7IMMQbwl3Cz/lRGHlep6FB2nzaciAkJqDECqXbe+5XYt9ff8G4/eyPmd5ANCPnJmFcxH5K8lOOd1eo1ieUeAN/Yb54eNVX8Czv2miAVty71xpFvgiXoBGGxZ/YZLIkXBs3za/2D7dzz/u2Cn2NzGxXg06WE4kW1/b12D3W0Fv+RZJyPd7Ok6/PHJBJt61HXq2B8MABpqz/94wxT97QjwXybWtH/yGgmK9FDmERXGiJDLZxv8GvtLMa6QCMHkdn3QPpVh/NWNUXPrqceGHUMlyMVTuWOA0Um532KHS9aW+9TWcJCJVmi1c8IA94QLuPBx8FRmlUydGphVoAJ3xMDouBrDhjkRmaxsi93wg0YjzfO2FV+jwu4yEkuiAbApRXoiIr9nRbDdh5RT/AdqbSj9SfYuNFr/9g85mPuhVj6UWfxHcLzo0DXOUfDA3uiNRTSHWkVUEbWMmFmz/7iHALR1nRNGk9f5rOR7/4nHMFCgeVg0jlVTfchLpi8FXeKr0UAB5ozmIvwCAVeS7QvxIkgeBkBvvUqbk7+0LHmBKdoVvpRlHsnlgjU6JKQ08quse3H3GVhmS7c/+S1Dw2TSFDsmiEIE7PJO3PGZRapsZbF7gW8akAvKdvEW2OvMI5Wm7GvSA0PGQgcQeOzh3ec18io844G6O5hFxrSmR1KrhytObNNk4pYQx2xcl+ZDiM+PgU1STMIvXuKy0LkCmgjX/fp6vMQd9XUV6Nz1F3NpaLVTpiSWE+ZLItt0stGg1SBJzL8nqGGStMQeqrT+kMtBjoyLWPgDog+vo2BkcKsEOrSf0w2KpWtKE8AD/Z3y81JXiW/C+ii0m1QWeQuXALJKZ1rk5hLCTLbNPB/wg9QMfyFMYSAKWST1R8x5GT8+DP+xnjPITqE0wq8h/zXYEgqF+V3Mmc2qdGtWmW4aPTPwubj9zsXjj9//kGMfWd+NxUmbXM7u7afzHKtffWVf2K4hhubQCvXEngckAsQlr7dC6pi+ydVS/QjylkQDPqGteSYQ7kmNylNUhHRNHhX3UZQz/M3laLWkuAmmmsK2exzw+5RkUUx6zUTtV5geJ3CVg25ZRv3ktGtOEs/jACjicH6jlums81y78hrck0t6hRY9mvX9GQMtiPBnb3uVQnA2Px+1o7Y7rgvH/VkAJXJU5hlQM3Dmnl/I7YacThnBr9lGlo0QrVHvWJLJj64Buluv+fB3NmkkBewX1soJGpMT2CR9WXNW6LKkTdMGOs6SrYwtHgoaCu+UGE2OeoaQRl6uXQYb2I5Pi42yGUXw3UhWxBiP9YX/qV2G4axpp0f9SgEWHX6aIOf59kjLpRz2fbpkpew0DPncMaJyIACQYrVnnbzs8lobGrBQRzcCR/ji77V+ah9O4Aw6KKY6+us/6BnmjQy1dPBCxxqNur3ldY0HXgbYXOY84n3eJVDj3e57i7S9sVmsdDkW+JSW+b5CSzOmNMBsojEHtZxmeSfpX3iQDu03dKSIT/AC5bVT6zeJKmMF+vN1ZxN8n5VGvu9lcC7LWuoxTjm06bXFIVGkvNFlb2jTn6RdqZjMlfKD0LTCZrZU3vwEN6fxcqIkpFsA3FFvxpWDbV32uTk5mZnMQjUqPUqGgGGdajsTh3JEjh/TleGvmsjubvTPV5rzeb7i5r5e2oo4nRKC0rp6wQ2KHFY/kgwiVa74bCgFoTWhfrgLtwRRXBlcMGBrTzh1fwI0r1j7fiTQv4iurfZAZhZ5+m5Qa5213vemAQK7kwzRTTViqnZp1ooInl1h2J4mdmCDaSp4mAZYjf0w/sCeXvH+kmXR3I2EiAUMwXB1+pzzQ/5A7IeuJRn3Vt+F6I+up2J8OxfPKPeHW80avUDcvhLZMamVdeq8hOhekAr7IZHrpnILWyfxVCzUmVoNCZvOGhs0YZUowykm9yLcf2G8M++AlIZ8VjBioYnwTOAoYzxt1wwe7a715Fub6zt/9HPkdwR0Kz053fEYGY4+FWsU434qbj3CDVDE+7zgib4SzfG9v3OLT49/KHZNpaPVEht63ytcvVh0JEpA3jvXXjB2XAZJ/JdFExf1cMb+4Wx9RF2XRajD8/VqTjePA/wyNr4Z56xDLMpg8ll095koHedFad2xaWQeEIKcCT0RJ/1kmypjFbjdG7YiDZEUHyz0LULsnIab08qbO7dsulgOuNRgzQDMYYNgvXC4Jl/Yhf+AFIhDFYOBN9rz5SjZfaTYorTkCu63vrPWm4eGTqnYVtCB0g908U40G3qOhsuwQwhkY2XZDVfvtmh/w7sUtYXoOurfjbT/rM+AgBANu7yoM8vkTdICZrSb0diovSfJZwbj2OTZ+LS0PtOoljdJRlJvjxNZe+s1+8+G9mScnMhiJ3ZfbSj2qBrW/JinmZ9brdMOq83QqcAgrKQPSm1wBsvGc0deKG+DnubkHSJZhUIp3Zx7Bkrp6xjCrw1pNMX8NbYZX7a+DWbwhxqs/yWx/uj2cRnO6SYoje2rULAn0cRMnKH5sd2/bXAcjwRr/Z/l5cGDqttkfX86LrVk9gf3RB+yHDamuSeC2e2RSf9uBtTYv1zPGZtXRScxdz65Jb46mWaNepF4tOwWZkeqU/QTgiB1Arhy2bSVJTxzPiOquIicK8W5IzqyrfMvkXgUfI7xbvzgaGPcwh8RptOKFGXPlJnj0xuK9BMrDCrPYVN3AlHXubk9SOxNFqy2TxlbxXMnDrIobD2fK5dV+J2Oel8bm+ZtFuT4K6k1wpBFgxxkA/UbenCGZELjpCetijnUrf7UXW8Uj1kwL7x60XSHJcHiMOXydtgjCPxkgnCgBQ+PzOuKQYDVoBx5XOeZo55F+wpWuR4sXH+/jYD+cVUmn9zkrQkUqa9xezGuxblk1Nl34MkGMXvZKM9cZg7yvGPMyU8fOmxpOelPwvPil66BO2DByWgBlRtwzvY54stfwUxV4QBLIDRV3FD3z1m3IlkPvMVfpFN0jX0OfxSjXVyHaSJ5uC+61Q8WZCA2A6EO9TbZjN76RbmZDZV9+4fo1Ca1c/kX/l4OOBP8cM0GuwbRefKmFx71qCI=
*/