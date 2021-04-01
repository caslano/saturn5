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
FOxuxb2iPreqeR34PlvwKn6XE6Z8bIMNQk7Nv3SOkss6KzovrF9mSnw/PU7EGivttRnJAXjBawFD3NXRHZ4lH3blqbwAlSHCnRJtqkS+Xcx1IBNmElLjymSv8JpVOYNK9OmTYapgceGC53tb3eUDQFLy2eJjCBuI6ttgKUdignwJuc64GTDZkROpv1Fzk7662w5vdSlCGYtqXKX7+rgcw/BShjDSpGqzO7gjVlF7QtqdLGaUGSTe1cf0ge7Dn0xs1p2+6EUYeO5fEjHEnhBweTlRMF5XenWg9n84Zrz3V4EueLlIfXSGLL51GBs3YWldsfRUFIe9r0j+NHnunobQDHkmxVDWKNPeoWaMoQ0ehvynmPSSc2PcniFHyJuWnQpwPs8vIComqpZwtCLbUFnnq3LAKjpjuYk/TtEypQnRxNePsI6bhMu0XfuoFULhdvYx49Aris03UfIZu+dfkR70Mg4Ic3b9hlxPvSuqK1QjkQ5KAp0MNixRkfDAepbDrKwnLIqzuUxcGHgNf3FIBTzboIvLuUwJyx3oC5YkagHjke8WaVugUzk/SigVUA==
*/