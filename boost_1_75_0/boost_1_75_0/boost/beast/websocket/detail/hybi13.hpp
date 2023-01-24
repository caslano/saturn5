//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_HYBI13_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_HYBI13_HPP

#include <boost/beast/core/static_string.hpp>
#include <boost/beast/core/string.hpp>
#include <boost/beast/core/detail/base64.hpp>
#include <cstdint>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using sec_ws_key_type = static_string<
    beast::detail::base64::encoded_size(16)>;

using sec_ws_accept_type = static_string<
    beast::detail::base64::encoded_size(20)>;

BOOST_BEAST_DECL
void
make_sec_ws_key(sec_ws_key_type& key);

BOOST_BEAST_DECL
void
make_sec_ws_accept(
    sec_ws_accept_type& accept,
    string_view key);

} // detail
} // websocket
} // beast
} // boost

#if BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/hybi13.ipp>
#endif

#endif

/* hybi13.hpp
1ODkYVdgBmJupiBEZL1Y4MjfIWK0uBEXPAKeTYCd+qhNotC6j9k4UnjcRiZ1iyVu+UamtAXycd3QrscDvmTpEO0Zk/822BJoiReyPDIGzAucC8bY0Ylz3LBoW+Ia9KuyV0SxUs4826pZ8YJR6wsXA6hyE14OS76gn52DK1HsAbEHPV7U6tci0+1QerbgiVteQ1OrXkrKk3k8WhsEMQMD98B3ppILA7+ZyEkAIi+3/J1bft+1ehZ6AsIDo15x3GGVmn2uNfGkRZcqXBcAW1Z1umAfM6yB9uVa1FrXmhjEgTONFW0ZZZVcb5uw32PgNKzmHv/2Kr3uY20Q05pKsFPMtXqI8euKUdbW3yWw7/KBlM1ZyQOw0ZbYS5tU6mLV7dy8cgdACtwAQq5ne24t9lIdmOpafWMCteVRcm8nJ90vG0I0RvvWzL/VTdGsqnPGjVzpNE85d6DVGD1s9I1hrqxvurG1Cd5Kg/cJl7y5aUksUIAruUUqub8S0Vb0KEfgDguECj0sDLwc5afTqtsvoVX34KSixN0t79Dn1ANz2p0NlQL0VqPFsbLuXrZEwe6t5hOskXFQr53RekbzDLMSGmIKn888pXkkzectllbzmdfmfObx+bxiCJ9Pj7KnMGw+U4eEzad9SNvzSSHXmm42k2Xyp7HUEZo+7msmN+lsN5BvjfhiOR1f9iA2sbwJ1i5wGoBjsSJ3RQmZwBYp43aT
*/