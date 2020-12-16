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
tKyJc1h5nD5x9uzcSdmzMudk5eGtuHcDja+LkbdNHseOt5NMP5ozG1UJzXvHf0czDm0o/o+4ymm+6Z/qidthzXsnbDuX3wWa745ba9N/nSxh4wKFfs8zaf78cW+7vEXs1d3tReMz7SXqXNCpEnaR2gPWz2JvbOJqExHXVOzR5naaS9iAGafGmr6oUIdmoPh5lrUqvUUH1TmjqJZcb6XX8MhvpFzbbiVTF2OwL/XOBdDHHHuvAbuPCe0wfYyvLNC6qH2KU97IA1N/56s8cOwLxJ5h7OepLnvRfmi6PIMIBrFfGWG/19gL6v8Qrf97dK195SDnMMGy8CrSl7/Fp/7LY6RPnJo1cXr6pOy8ibnZM6n9PEXUeq/x1DP14HaxNwg49eDMR+W9t2i90XK8Tfx/F9A6qPGd7F83iC/jUa3f7vfE9HaF7e4R3GntXve2Jn1Pi/vlVpH06ftPbXGfF/CMBXV8fKOk7RBuTtwTTDtLkHBj/d+ttB2vlfBfuMJnmvYfI+GnudKN6GGu3OwbIu7xanfyoYE1ljpdVeu0vd7/8mPMf+l8l8jj0dhvwfC36MPWhs5c2OIS9Id2myAdnjaR4W0TUevzWY946+9M7O7620/r7/Ia3rNPm2DyiX//A9HrLx8wcukbZ2XnTZV6sshdb7XeffuAe8yu8ZFaZy+XylUcc2zZ4PRbi1zP7e7TVyQXeM7VY3PTMUvwm/Jg9GeYnbPAlfZJWXk0Ak2rhqth3qm6in006Qy42mle7kSXvOwkfoZYtUiXtjWNJ0mf2SUTSyAPvc9sp0910kz5c3/ti509nkfX9C/LVdHLUkvRilqO90eU46qIcjycoOY49pOJKEdTF3fULvBclfvUggF4GX6th6OlX0YUaM6hxeQnQ/UZmkv4t/QZnPiaF/bvru8ETcStmpah47eJOS+9v9jvo1T/4gqfaeRfQ3H/SscSGt4zbp9gZFI9cftMxxaO33pR5yBniPswtRMSe8R4QuMw4wlfOT8bv9+IvxTLV56qzG0lfj4q6Ne1/i79Hf0693JkWAnG+DkRfbqO8dXuO8ZXmXf9w16Ztxm7n8ybUYd/dO+BCrrG9ArSk7Gl2Ho2KWsKuzJF76s1fCUzJt+d8PvG5G7Z1uXkAs952qZnYi7Ab0L0Nm0fqB/Zno2cqifhMqxe/Kvp1rgSjR70NwmOObHt+4u6/KPn39aEW+Gl+N0UXU7nedu3/zO9IOFvD4zHhz6TxlnH9a6Vo23acWtj5tn2i31FIM2K9XtnVv8tzRz2O2JfHRjD0/m8N6v/Zmbe701N31grHHXeLm6z7adHINmq7GrPGpe25/wo7XkWfls8JO+haqdlS3yJfu3b7HH1usS9LpDBv97xXOG4KU3i+caS+Wit0xsj5qBHYXZx/WH92+ahBPdcdMn06G1ZwXN4xzve+mT2MGjhkhU5EfMB8yPmA/J9ZMU9m72y4oixe+ePW9S35DdGxxZDMI+QntSXitZZWt68rNw50eQDYbzjijFi70lPFCNhri58jzV1e6T4OZUvKOW1/jrxJPn2E2nGvY7R79S+mvnEgvFnjxLIbT+5pOMPnePTdKo8N/kbMSZJaFBU1m6z27xv/uWlZ84hFxmVoAsfLR81bCWzZ4b/HID6M/u38Oy/Ux7rc7vfOz3PeG1jS37PB5nDhTvg4/jdG+UZZ8+KOmYx5X5Ywq4J1jJy2omvUbTnVff6Zs3Ed2K/I1jTiokqdz4RP/cHmzn60SaeakVkTaLOH/wk7pOCSVbIvDee8yrXaDWu71pmPUoXuOpl2/1n73ufyt/G4pbt/ibWwQm7Al4v7jHB4tZetBI/Y4PFfQPoKH4qqp01LWKvbuY=
*/