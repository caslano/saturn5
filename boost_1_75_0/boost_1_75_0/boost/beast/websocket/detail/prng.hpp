//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_WEBSOCKET_DETAIL_PRNG_HPP
#define BOOST_BEAST_WEBSOCKET_DETAIL_PRNG_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/config.hpp>
#include <cstdint>
#include <random>

namespace boost {
namespace beast {
namespace websocket {
namespace detail {

using generator = std::uint32_t(*)();

//------------------------------------------------------------------------------

// Manually seed the prngs, must be called
// before acquiring a prng for the first time.
//
BOOST_BEAST_DECL
std::uint32_t const*
prng_seed(std::seed_seq* ss = nullptr);

// Acquire a PRNG using the TLS implementation if it
// is available, otherwise using the no-TLS implementation.
//
BOOST_BEAST_DECL
generator
make_prng(bool secure);

} // detail
} // websocket
} // beast
} // boost

#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/websocket/detail/prng.ipp>
#endif

#endif

/* prng.hpp
ts1R/irfSXlK8lgLQ98U3aJ/P3IK9iRBM9TXNAfHCv2pPEl/xmuucukIE2ePCHifHd4xHkGO+nYJ9o2QtNlRfh57nU7nAdAmjmeqXRVxek3fuPnBzLfSO+6wWYWtNDxiK/lwKzVE20oIQwG3XVukWW7e0VJtL5caN9FoI3msb6L5fBONXotnRFWrM0KWxD6Zrv2aqP0aK/H7j4meTTH0/DxG7J1+Eh4TJbxAnZZxBf/0rRhhZ6pp1K/boVGSmV75fREGzhPoCpGU/A60y+pll9B1QvM9woNNjPCL0y0G2ATvQZwLRg1ng50N4D5PsCP6XRHlYRYqPXRNQI83I9cIbVK8JkT3kcOohpcl7czT+mxtR5/39Gy7z7NM/1mfl69uX59/UeMMcRUmp6cOJpNF6Hu/7Um6yaJPQStA6Ddc025XQK5y5MpkSbkNHPODF6JbuLUaG9Vu1XnMZZfW4aj6IGrxNaK5LNt8eySQKTm9N9jRKzR8itadcn4j+iTyNTbHCgPFBPxI3O7IGC6Bmheuic5GhVwycFu9SjOFmExjHw4eipJglD65DsVkzsf+aZeaHvjuuOavKbBVPeiouSkz0Gzyn0oWtIGalNAgk1c2udRKuMyxqRW+U5AiZ+VdmWq1iBtH9keekGXi69xhxE3gKaIrxPQLmtmvfa9xnxEhyzX0M5X9tNNP+PCdZfiTrbmlI8SRCk4nv5aWza/i
*/