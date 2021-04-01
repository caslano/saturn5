//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_PMD_EXTENSION_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_PMD_EXTENSION_HPP

#include <boost/beast/core/error.hpp>
#include <boost/beast/websocket/option.hpp>
#include <boost/beast/http/rfc7230.hpp>
#include <utility>
#include <type_traits>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

// permessage-deflate offer parameters
//
// "context takeover" means:
// preserve sliding window across messages
//
struct pmd_offer
{
    bool accept;

    // 0 = absent, or 8..15
    int server_max_window_bits;

    // -1 = present, 0 = absent, or 8..15
    int client_max_window_bits;

    // `true` if server_no_context_takeover offered
    bool server_no_context_takeover;

    // `true` if client_no_context_takeover offered
    bool client_no_context_takeover;
};

BOOST_BEAST_DECL
int
parse_bits(string_view s);

BOOST_BEAST_DECL
void
pmd_read_impl(pmd_offer& offer, http::ext_list const& list);

BOOST_BEAST_DECL
static_string<512>
pmd_write_impl(pmd_offer const& offer);

BOOST_BEAST_DECL
static_string<512>
pmd_negotiate_impl(
    pmd_offer& config,
    pmd_offer const& offer,
    permessage_deflate const& o);

// Parse permessage-deflate request fields
//
template<class Allocator>
void
pmd_read(pmd_offer& offer,
    http::basic_fields<Allocator> const& fields)
{
    http::ext_list list{
        fields["Sec-WebSocket-Extensions"]};
    detail::pmd_read_impl(offer, list);
}

// Set permessage-deflate fields for a client offer
//
template<class Allocator>
void
pmd_write(http::basic_fields<Allocator>& fields,
    pmd_offer const& offer)
{
    auto s = detail::pmd_write_impl(offer);
    fields.set(http::field::sec_websocket_extensions, s);
}

// Negotiate a permessage-deflate client offer
//
template<class Allocator>
void
pmd_negotiate(
    http::basic_fields<Allocator>& fields,
    pmd_offer& config,
    pmd_offer const& offer,
    permessage_deflate const& o)
{
    if(! (offer.accept && o.server_enable))
    {
        config.accept = false;
        return;
    }
    config.accept = true;

    auto s = detail::pmd_negotiate_impl(config, offer, o);
    if(config.accept)
        fields.set(http::field::sec_websocket_extensions, s);
}

// Normalize the server's response
//
BOOST_BEAST_DECL
void
pmd_normalize(pmd_offer& offer);

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/pmd_extension.ipp>
#endif

#endif

/* pmd_extension.hpp
ZLgJZYRgGmm53b7x14MQiMY24muOk3wFuzmIWA+4SiFZ2tfdsIiTR5sf7Ce4H1gusuDAC6+7tzuefswboD+/M59PBwJ8I0E6bYLN3GsWKq+x8x4BfE87Tv6oCLNaRwWH11iJ5EKRvZgUqP4kPCOCJiEpWgukTYbFG8Wq5JExaouwHWPOK+tSSVPQS9+Pb/ZxY1VXeBMYyjAMSDAJZQyAuTlBhf54+IVMwW7XHXz93rvptbCN6j2/ChAlU2sXbsl+8jWzUenyETV1T5auQN9fg7dYfsMpBdWvKKxdQ/4jAYBj2g6T2Vbmh58hVN08XJSkRQp+XrcgbKfMDyUu++sKI2PcmJF6OxBlv254JGS42A4cXrjaoPunlMeO0UlJHXcN2sHz1F+WmLxyfLt+3eEBZo9XKD+oroNo9nTielhpO89nEP536OiVZd1m2GrqTtxc7bUqS3BgZnmHMWJyidjJadE/4U+noMczlxIwpU15CDZxoiDLK5VJ5Y/6gEDLy47fPXULIVewoktzaoTFhvTj1rUATNw+87jf9a/HGOGHvfh4d0jA2RtErwOdFw==
*/