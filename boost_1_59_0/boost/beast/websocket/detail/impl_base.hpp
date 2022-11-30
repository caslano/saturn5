//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_IMPL_BASE_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_IMPL_BASE_HPP

#include <boost/beast/websocket/option.hpp>
#include <boost/beast/websocket/detail/frame.hpp>
#include <boost/beast/websocket/detail/pmd_extension.hpp>
#include <boost/beast/core/buffer_traits.hpp>
#include <boost/beast/core/role.hpp>
#include <boost/beast/http/empty_body.hpp>
#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/beast/zlib/deflate_stream.hpp>
#include <boost/beast/zlib/inflate_stream.hpp>
#include <boost/beast/core/buffers_suffix.hpp>
#include <boost/beast/core/error.hpp>
#include <boost/beast/core/detail/clamp.hpp>
#include <boost/asio/buffer.hpp>
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

//------------------------------------------------------------------------------

template<bool deflateSupported>
struct impl_base;

template<>
struct impl_base<true>
{
    // State information for the permessage-deflate extension
    struct pmd_type
    {
        // `true` if current read message is compressed
        bool rd_set = false;

        zlib::deflate_stream zo;
        zlib::inflate_stream zi;
    };

    std::unique_ptr<pmd_type>   pmd_;           // pmd settings or nullptr
    permessage_deflate          pmd_opts_;      // local pmd options
    detail::pmd_offer           pmd_config_;    // offer (client) or negotiation (server)

    // return `true` if current message is deflated
    bool
    rd_deflated() const
    {
        return pmd_ && pmd_->rd_set;
    }

    // set whether current message is deflated
    // returns `false` on protocol violation
    bool
    rd_deflated(bool rsv1)
    {
        if(pmd_)
        {
            pmd_->rd_set = rsv1;
            return true;
        }
        return ! rsv1; // pmd not negotiated
    }

    // Compress a buffer sequence
    // Returns: `true` if more calls are needed
    //
    template<class ConstBufferSequence>
    bool
    deflate(
        net::mutable_buffer& out,
        buffers_suffix<ConstBufferSequence>& cb,
        bool fin,
        std::size_t& total_in,
        error_code& ec)
    {
        BOOST_ASSERT(out.size() >= 6);
        auto& zo = this->pmd_->zo;
        zlib::z_params zs;
        zs.avail_in = 0;
        zs.next_in = nullptr;
        zs.avail_out = out.size();
        zs.next_out = out.data();
        for(auto in : beast::buffers_range_ref(cb))
        {
            zs.avail_in = in.size();
            if(zs.avail_in == 0)
                continue;
            zs.next_in = in.data();
            zo.write(zs, zlib::Flush::none, ec);
            if(ec)
            {
                if(ec != zlib::error::need_buffers)
                    return false;
                BOOST_ASSERT(zs.avail_out == 0);
                BOOST_ASSERT(zs.total_out == out.size());
                ec = {};
                break;
            }
            if(zs.avail_out == 0)
            {
                BOOST_ASSERT(zs.total_out == out.size());
                break;
            }
            BOOST_ASSERT(zs.avail_in == 0);
        }
        total_in = zs.total_in;
        cb.consume(zs.total_in);
        if(zs.avail_out > 0 && fin)
        {
            auto const remain = buffer_bytes(cb);
            if(remain == 0)
            {
                // Inspired by Mark Adler
                // https://github.com/madler/zlib/issues/149
                //
                // VFALCO We could do this flush twice depending
                //        on how much space is in the output.
                zo.write(zs, zlib::Flush::block, ec);
                BOOST_ASSERT(! ec || ec == zlib::error::need_buffers);
                if(ec == zlib::error::need_buffers)
                    ec = {};
                if(ec)
                    return false;
                if(zs.avail_out >= 6)
                {
                    zo.write(zs, zlib::Flush::sync, ec);
                    BOOST_ASSERT(! ec);
                    // remove flush marker
                    zs.total_out -= 4;
                    out = net::buffer(out.data(), zs.total_out);
                    return false;
                }
            }
        }
        ec = {};
        out = net::buffer(out.data(), zs.total_out);
        return true;
    }

    void
    do_context_takeover_write(role_type role)
    {
        if((role == role_type::client &&
            this->pmd_config_.client_no_context_takeover) ||
           (role == role_type::server &&
            this->pmd_config_.server_no_context_takeover))
        {
            this->pmd_->zo.reset();
        }
    }

    void
    inflate(
        zlib::z_params& zs,
        zlib::Flush flush,
        error_code& ec)
    {
        pmd_->zi.write(zs, flush, ec);
    }

    void
    do_context_takeover_read(role_type role)
    {
        if((role == role_type::client &&
                pmd_config_.server_no_context_takeover) ||
           (role == role_type::server &&
                pmd_config_.client_no_context_takeover))
        {
            pmd_->zi.clear();
        }
    }

    template<class Body, class Allocator>
    void
    build_response_pmd(
        http::response<http::string_body>& res,
        http::request<Body,
            http::basic_fields<Allocator>> const& req);

    void
    on_response_pmd(
        http::response<http::string_body> const& res)
    {
        detail::pmd_offer offer;
        detail::pmd_read(offer, res);
        // VFALCO see if offer satisfies pmd_config_,
        //        return an error if not.
        pmd_config_ = offer; // overwrite for now
    }

    template<class Allocator>
    void
    do_pmd_config(
        http::basic_fields<Allocator> const& h)
    {
        detail::pmd_read(pmd_config_, h);
    }

    void
    set_option_pmd(permessage_deflate const& o)
    {
        if( o.server_max_window_bits > 15 ||
            o.server_max_window_bits < 9)
            BOOST_THROW_EXCEPTION(std::invalid_argument{
                "invalid server_max_window_bits"});
        if( o.client_max_window_bits > 15 ||
            o.client_max_window_bits < 9)
            BOOST_THROW_EXCEPTION(std::invalid_argument{
                "invalid client_max_window_bits"});
        if( o.compLevel < 0 ||
            o.compLevel > 9)
            BOOST_THROW_EXCEPTION(std::invalid_argument{
                "invalid compLevel"});
        if( o.memLevel < 1 ||
            o.memLevel > 9)
            BOOST_THROW_EXCEPTION(std::invalid_argument{
                "invalid memLevel"});
        pmd_opts_ = o;
    }

    void
    get_option_pmd(permessage_deflate& o)
    {
        o = pmd_opts_;
    }


    void
    build_request_pmd(http::request<http::empty_body>& req)
    {
        if(pmd_opts_.client_enable)
        {
            detail::pmd_offer config;
            config.accept = true;
            config.server_max_window_bits =
                pmd_opts_.server_max_window_bits;
            config.client_max_window_bits =
                pmd_opts_.client_max_window_bits;
            config.server_no_context_takeover =
                pmd_opts_.server_no_context_takeover;
            config.client_no_context_takeover =
                pmd_opts_.client_no_context_takeover;
            detail::pmd_write(req, config);
        }
    }

    void
    open_pmd(role_type role)
    {
        if(((role == role_type::client &&
                pmd_opts_.client_enable) ||
            (role == role_type::server &&
                pmd_opts_.server_enable)) &&
            pmd_config_.accept)
        {
            detail::pmd_normalize(pmd_config_);
            pmd_.reset(::new pmd_type);
            if(role == role_type::client)
            {
                pmd_->zi.reset(
                    pmd_config_.server_max_window_bits);
                pmd_->zo.reset(
                    pmd_opts_.compLevel,
                    pmd_config_.client_max_window_bits,
                    pmd_opts_.memLevel,
                    zlib::Strategy::normal);
            }
            else
            {
                pmd_->zi.reset(
                    pmd_config_.client_max_window_bits);
                pmd_->zo.reset(
                    pmd_opts_.compLevel,
                    pmd_config_.server_max_window_bits,
                    pmd_opts_.memLevel,
                    zlib::Strategy::normal);
            }
        }
    }

    void close_pmd()
    {
        pmd_.reset();
    }

    bool pmd_enabled() const
    {
        return pmd_ != nullptr;
    }

    std::size_t
    read_size_hint_pmd(
        std::size_t initial_size,
        bool rd_done,
        std::uint64_t rd_remain,
        detail::frame_header const& rd_fh) const
    {
        using beast::detail::clamp;
        std::size_t result;
        BOOST_ASSERT(initial_size > 0);
        if(! pmd_ || (! rd_done && ! pmd_->rd_set))
        {
            // current message is uncompressed

            if(rd_done)
            {
                // first message frame
                result = initial_size;
                goto done;
            }
            else if(rd_fh.fin)
            {
                // last message frame
                BOOST_ASSERT(rd_remain > 0);
                result = clamp(rd_remain);
                goto done;
            }
        }
        result = (std::max)(
            initial_size, clamp(rd_remain));
    done:
        BOOST_ASSERT(result != 0);
        return result;
    }
};

//------------------------------------------------------------------------------

template<>
struct impl_base<false>
{
    // These stubs are for avoiding linking in the zlib
    // code when permessage-deflate is not enabled.

    bool
    rd_deflated() const
    {
        return false;
    }

    bool
    rd_deflated(bool rsv1)
    {
        return ! rsv1;
    }

    template<class ConstBufferSequence>
    bool
    deflate(
        net::mutable_buffer&,
        buffers_suffix<ConstBufferSequence>&,
        bool,
        std::size_t&,
        error_code&)
    {
        return false;
    }

    void
    do_context_takeover_write(role_type)
    {
    }

    void
    inflate(
        zlib::z_params&,
        zlib::Flush,
        error_code&)
    {
    }

    void
    do_context_takeover_read(role_type)
    {
    }

    template<class Body, class Allocator>
    void
    build_response_pmd(
        http::response<http::string_body>&,
        http::request<Body,
            http::basic_fields<Allocator>> const&);

    void
    on_response_pmd(
        http::response<http::string_body> const&)
    {
    }

    template<class Allocator>
    void
    do_pmd_config(http::basic_fields<Allocator> const&)
    {
    }

    void
    set_option_pmd(permessage_deflate const& o)
    {
        if(o.client_enable || o.server_enable)
        {
            // Can't enable permessage-deflate
            // when deflateSupported == false.
            //
            BOOST_THROW_EXCEPTION(std::invalid_argument{
                "deflateSupported == false"});
        }
    }

    void
    get_option_pmd(permessage_deflate& o)
    {
        o = {};
        o.client_enable = false;
        o.server_enable = false;
    }

    void
    build_request_pmd(
        http::request<http::empty_body>&)
    {
    }

    void open_pmd(role_type)
    {
    }

    void close_pmd()
    {
    }

    bool pmd_enabled() const
    {
        return false;
    }

    std::size_t
    read_size_hint_pmd(
        std::size_t initial_size,
        bool rd_done,
        std::uint64_t rd_remain,
        frame_header const& rd_fh) const
    {
        using beast::detail::clamp;
        std::size_t result;
        BOOST_ASSERT(initial_size > 0);
        // compression is not supported
        if(rd_done)
        {
            // first message frame
            result = initial_size;
        }
        else if(rd_fh.fin)
        {
            // last message frame
            BOOST_ASSERT(rd_remain > 0);
            result = clamp(rd_remain);
        }
        else
        {
            result = (std::max)(
                initial_size, clamp(rd_remain));
        }
        BOOST_ASSERT(result != 0);
        return result;
    }
};

} // detail
} // websocket
} // beast
} // boost

#endif

/* impl_base.hpp
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
*/