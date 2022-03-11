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
                    zo.write(zs, zlib::Flush::full, ec);
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