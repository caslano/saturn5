//  boost/memory_order.hpp
//
//  Defines enum boost::memory_order per the C++0x working draft
//
//  Copyright (c) 2008, 2009 Peter Dimov
//  Copyright (c) 2018 Andrey Semashev
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MEMORY_ORDER_HPP_INCLUDED
#define BOOST_MEMORY_ORDER_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(BOOST_HAS_PRAGMA_ONCE)
# pragma once
#endif

namespace boost
{

//
// Enum values are chosen so that code that needs to insert
// a trailing fence for acquire semantics can use a single
// test such as:
//
// if( mo & memory_order_acquire ) { ...fence... }
//
// For leading fences one can use:
//
// if( mo & memory_order_release ) { ...fence... }
//
// Architectures such as Alpha that need a fence on consume
// can use:
//
// if( mo & ( memory_order_acquire | memory_order_consume ) ) { ...fence... }
//
// The values are also in the order of increasing "strength"
// of the fences so that success/failure orders can be checked
// efficiently in compare_exchange methods.
//

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum class memory_order : unsigned int
{
    relaxed = 0,
    consume = 1,
    acquire = 2,
    release = 4,
    acq_rel = 6, // acquire | release
    seq_cst = 14 // acq_rel | 8
};

BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_relaxed = memory_order::relaxed;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_consume = memory_order::consume;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_acquire = memory_order::acquire;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_release = memory_order::release;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_acq_rel = memory_order::acq_rel;
BOOST_INLINE_VARIABLE BOOST_CONSTEXPR_OR_CONST memory_order memory_order_seq_cst = memory_order::seq_cst;

#undef BOOST_MEMORY_ORDER_INLINE_VARIABLE

#else // !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

enum memory_order
{
    memory_order_relaxed = 0,
    memory_order_consume = 1,
    memory_order_acquire = 2,
    memory_order_release = 4,
    memory_order_acq_rel = 6, // acquire | release
    memory_order_seq_cst = 14 // acq_rel | 8
};

#endif // !defined(BOOST_NO_CXX11_SCOPED_ENUMS)

} // namespace boost

#endif // #ifndef BOOST_MEMORY_ORDER_HPP_INCLUDED

/* memory_order.hpp
vQgXIS4UJvqy6GvUvGXds4RHLiPRXED1v6XY538Pyad+n4Tb3eQHYZ0MN18oTG4WTufoB67nJ4YAFKsEosZvKlHDrTQwz/6WoLdEtWVICvlIUN11pJIPDfjwDKJY7V3zQMDAVXW2i1MGjwxQjX4KbPbpCIBsTLEVsqap6MzL3jQZwe95Nb71McoXlt477AfeZMfQLxY66SPy5i9KKgv+TZhtpWU4noUDiucZAgpIE8U7teessZ20PJmZrkCOCddp7htr++oVloV3VOM2y9AL7u6qne0QNDsK2WzeChIbj1rUgt6Y8ZaiGK22aXAH5cu8qfmcIxiOxAH+H0VQ82ig3/ARd8XgPuH5Md4HHCtMXrD1LQirqeSolYaSGWhcRvzOmD+ivrSFr4lqmM4VPGkL59NixYWGE5deXpNYtbEz9BLZn1R8u91ms5wysvbxqqrOpbhiJbgVcLFAO1xSC3cB+/VyzSdxnZfWBReZkqR2Qs3gPz0gtlVb0Z290nszMfjBX5NW3rkty1GCVYbz+5uo9VhHVMLQ4LdogueJL4TINpsML4LmOcNnR5D31w==
*/