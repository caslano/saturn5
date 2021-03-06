/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/memory_order_utils.hpp
 *
 * This header contains utilities related to memory order constants.
 */

#ifndef BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

BOOST_FORCEINLINE BOOST_CONSTEXPR memory_order deduce_failure_order(memory_order order) BOOST_NOEXCEPT
{
    return order == memory_order_acq_rel ? memory_order_acquire : (order == memory_order_release ? memory_order_relaxed : order);
}

BOOST_FORCEINLINE BOOST_CONSTEXPR bool cas_failure_order_must_not_be_stronger_than_success_order(memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
{
    // 15 == (memory_order_seq_cst | memory_order_consume), see memory_order.hpp
    // Given the enum values we can test the strength of memory order requirements with this single condition.
    return (static_cast< unsigned int >(failure_order) & 15u) <= (static_cast< unsigned int >(success_order) & 15u);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_MEMORY_ORDER_UTILS_HPP_INCLUDED_

/* memory_order_utils.hpp
emkJL9WjZtv/EsjBP1GtlOrVj36Va4hcnzIXUJHHSPSHGxywrA0jbLmPHzRJddfP6AN/Ok1PW2Xe5if3+kEzywkDldtyn/1C35sFE3dePrD5pjLxQIb+a1KQ0Dm7mCYCgLKBDMtyrRmwtjt4pKiheCwY+8P/SV50FFk/OYSRjXxj4NU3xL296VunRBikFyBSBXRz8hJHXkaeOxpBgWDJT6WHZF1tFkvNofYq/vbLk3OBJKYixjITHLbPO0G4lm9MbFFAN6fCLKdrhxLBpmvjXCX+amh3t6wT+IeIkkDG/IMWiKKPQ2aKTyGtxyatungkpD/QVNj5Xsn4/zQx6zZAbUQqazul+GiNhYX1MiG/ZIS2m58umLC+dcXdPSkdpqsNyCWYywv+vEESkONhxKXQRmNH1oKFcLyrCyHHESaqQYszgPf2NuLB0ilhEc5eLqtL/XGTxAxyNVAHE2cvcEzKmwJItl6rUZzknVfh2kICbmBW0nBMTtmxvtI2tZc4ZxoG5lilNXp8gKyvTMaP85pOy99xPkz7dXPvUAd+xAjM3zXMcRKP2Q1BeRASGA==
*/