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
            this->get_context(
                this->boost::empty_value<NextLayer>::get().get_executor()))
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

                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::check_stop_now"
                    ));

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

                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::check_stop_now"
                    ));

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

                BOOST_ASIO_HANDLER_LOCATION((
                    __FILE__, __LINE__,
                    "websocket::check_stop_now"
                    ));

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
    template<class Executor>
    static net::execution_context&
    get_context(Executor const& ex,
        typename std::enable_if< net::execution::is_executor<Executor>::value >::type* = 0)
    {
        return net::query(ex, net::execution::context);
    }

    template<class Executor>
    static net::execution_context&
    get_context(Executor const& ex,
        typename std::enable_if< !net::execution::is_executor<Executor>::value >::type* = 0)
    {
        return ex.context();
    }

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
                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "websocket::timeout_handler"
                            ));

                        idle_ping_op<Executor>(sp, get_executor());
                    }
                    ++impl.idle_counter;
                    impl.timer.expires_after(
                        impl.timeout_opt.idle_timeout / 2);

                    {
                        BOOST_ASIO_HANDLER_LOCATION((
                            __FILE__, __LINE__,
                            "websocket::timeout_handler"
                            ));

                        impl.timer.async_wait(std::move(*this));
                    }
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
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
*/