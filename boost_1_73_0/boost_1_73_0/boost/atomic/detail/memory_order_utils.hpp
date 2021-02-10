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
ZegvHmL5EsE+B8en0Zfob1BLAwQKAAAACAAtZ0pSbQ2WYlQIAABMEwAAJgAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvYW55YXV0aHB1dC5jVVQFAAG2SCRgrVdtc9s2Ev6uX7FWpq3oYSQ7/tCr7WROteVEE0XySPJlcpcOByJBkTVF8AjQsq7pf++zACnJdq5xZ6pMLAoEdp/dffYFvcO/79OiQ/rmJ7D/A3zwbU9cl+pXGZqv7w6CL+T+4dRnfH9LSY92R74EHn37yBfq2CNBreWcn4PgW4o+Mzb+0+OTnwN+xAqO8ckLVWzKdJkY6lx4dPzTT/+gl/Tq6NWRT5ciT2VGMyPzhSyXPp1HduWfibi/72r5xidpSGTdWtQ8STVpFZu1KCXhOUtDmWsZkdAUSR2W6QI/0pxMIilOM0kXk+tPw/Fbn9ZJGiYsZKMq0omqsogScSeplKFM75yMQpSGVIzjEB6l2kBgZVKVd6FbkpHlSrMMVi8yrUjciTQTCygShhJjCn3a64VVmQF9L1Kh7oWN+d3ErLaWfAKIldiQKgwZRZWWPvFOn1YqSmP+hkOwWFSLLNWJv0MDVXnUUyVpmWUsC+dSqR1sSbPaPT5vowKIU8NfWuWaVa0TtXqwEX5kKXFV5lAE
*/