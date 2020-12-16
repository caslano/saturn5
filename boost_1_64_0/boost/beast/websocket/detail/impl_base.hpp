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
mv9asGhrG6OvPUyIkbVpabec9umGGR2Wt9j7wsFf/tI4+ppH/zV60dY8Hv/axmhrGLOq2NffXHrd1bedknNzrw5VP7r+YLlW0ddg+q8xjLZ28sTtzeK/xjD6mkT/NZjR1jwe/xrDNCnft5dMuvLOat9t/rTqhPd3X/w4jfWwc+6Stpl83UvkYv37gO4r0sbSb22Qxxa3EGygYZ/lks3nYAx8Hmo4vnNFD/eOhntXw72n4fKdb0j6DYtwIlfmaLiKAdYtwgTYAjaAbWFj2B0mwQGwBpwIk+EMWBOeq/4WwcrwFbW/q/ZwQOxmv4Ov9bn7a/rd+x28oq+9r8LK8DVYHb4OW8F9sAd8A/ZRu6zTdObs9RsF8YrM7AD58TfPB5vAphAj8bWEqbAVPB22htmwDZwOx8JFsAO8FHaEV8JOcDnsBu+Bp8AHYHf4ChwM34Sp8H3YC34Fe8NDsA88KcBzw8rwNNge9oNd4enwFDgA9oYD4TB4BsyGg+AFcDBcDIfCy2AavBqeCW+EZ8Gb4TC4Ho6Am+Fo+BQcA5+DYzUf15l5afxqPibaY3Itnw+1PD6GLeEnur/IFzANHoQz4ddwKfwGXgatAOkBn2o+/WKnQ68/BQ5hP6DXP9brh8ER7GVIw8+QOiTu3SHuun+JzunqGCg/Yv+Sy3Vd7l9hW93HpDO8TtN7PRwBb4BnwxUwA94IJ8Cb4DR4s9aDW+EKeBu8C66C6zVezT+dP6SO+eTfGq3fa2ESvAueDDfAjrqPSyZ8EGbBzZqfD8HZ8BF4J9wKd8Bt8BO4HX4Gn9B6tgP+qPbf4N9gXdKyEdaHXFd5onNf8GQfeRImnyvAGJgMy2i+U390Donn1XCxcJCGu0jXRS+GleASWBVeos+7VMtjGewEL4WnqF3XXevcC7Jf43evu56n5bpQ47lAy/V8OFLtxEP56DwC/ErjqQSv1XjO1njO0fLIhDXhBE3PRHgqzFN5M1nLZwqcDKfCWTAb5sAZ8BY4C26Cs+HrMAe+ofG8B3O1vPLc8lnLYScmUj6XD9DuYBysr/amau8D4+EwtU9R+5/Uvl7t96h9k9o3q32b2p36sL+YfukF7V9e1P5lr6se7Sgm3C4N95SGe9qE0/cpWMkn3GTSZXMqTIDToZYr7w3a7n3KdQj+KsMzYUM4QvNrJGwJR8GucBzsAcfDQfBsOASmwxEwA06DE+BsOBHOgaPhYjgGXgzPguvgMLhB/TnPZ2k6m/k8X399rgGazoHwCB5Srylr7bg+1tqHOXR97DF1BzK4Hn9DrNUGk4pRfQGjKzCca8XpC+x79/fpDPjpC0TqCkzl3n76ApFnQvZlEDwaE01PIPxeUV2BcCphb4g9bl2BNu8V1RdYxL0jdQaWcw29gSI6A8tviC2x3sAq/O5o49UbGM/9v2hD+RF/NN2BPReESqw/8MVjIdEhOIApRnfAV2/give8ugPhC0MnVH9g43vHp0Pw4F3BE6M/cGHoP6ZDsIUy3os5hIlfEWs1wKRixmMWYVZitmH2YY5gqt8Ya3XADMfMwCzDrLuxVA+h9Ff6K/2V/kp/pb//1u8/sf4/Jz1vZs6ME7P+f2Id4lDd/wY63+WMJMpiYhoxL7S/QPe/T/rp/bh3NjfPEhWE2ZNK8P0qvtIHDe2JhaAV5CwWXedj7hlfVuc2YpgnhNfCB/C/f5d+V3TfkyMFnW95afjh3JXc2XNz9DuEE6aZ+cZb/inbPj+mJvdLw5Qn3NUSLle/VThhGkuYUdjLSph5MTX4hj0EY4cZI2EyrSRd8xsWP/HheswqjMLotyji0nW/4o9VA8/JeX6uOCboty3Hby0rWdczHxX7S5xMVM4ahzk=
*/