/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/ops_gcc_ppc_common.hpp
 *
 * This header contains basic utilities for gcc PowerPC backend.
 */

#ifndef BOOST_ATOMIC_DETAIL_OPS_GCC_PPC_COMMON_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_OPS_GCC_PPC_COMMON_HPP_INCLUDED_

#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

// The implementation below uses information from this document:
// http://www.rdrop.com/users/paulmck/scalability/paper/N2745r.2010.02.19a.html

// A note about memory_order_consume. Technically, this architecture allows to avoid
// unnecessary memory barrier after consume load since it supports data dependency ordering.
// However, some compiler optimizations may break a seemingly valid code relying on data
// dependency tracking by injecting bogus branches to aid out of order execution.
// This may happen not only in Boost.Atomic code but also in user's code, which we have no
// control of. See this thread: http://lists.boost.org/Archives/boost/2014/06/213890.php.
// For this reason we promote memory_order_consume to memory_order_acquire.

struct gcc_ppc_operations_base
{
    static BOOST_CONSTEXPR_OR_CONST bool full_cas_based = false;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = true;

    static BOOST_FORCEINLINE void fence_before(memory_order order) BOOST_NOEXCEPT
    {
#if defined(__powerpc64__) || defined(__PPC64__)
        if (order == memory_order_seq_cst)
            __asm__ __volatile__ ("sync" ::: "memory");
        else if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __asm__ __volatile__ ("lwsync" ::: "memory");
#else
        if ((static_cast< unsigned int >(order) & static_cast< unsigned int >(memory_order_release)) != 0u)
            __asm__ __volatile__ ("sync" ::: "memory");
#endif
    }

    static BOOST_FORCEINLINE void fence_after(memory_order order) BOOST_NOEXCEPT
    {
        if ((static_cast< unsigned int >(order) & (static_cast< unsigned int >(memory_order_consume) | static_cast< unsigned int >(memory_order_acquire))) != 0u)
            __asm__ __volatile__ ("isync" ::: "memory");
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_OPS_GCC_PPC_COMMON_HPP_INCLUDED_

/* ops_gcc_ppc_common.hpp
ljnGvFalS85kELvm/GhZ5RmJEvYWr6nsv98vLbKyyrBeM/dicFlkyli941yTCOK5CUMCZj08dmJCIOz3/LnAPJU/WQTXavRE0qn8fQHPO7bf5OYm2OS4EFxDhnFxvuC99mOBuB0oHxvJv3SVLx3p/2dr+2GKHUIrypObKe8PJrehlz8dd/4JUEsDBAoAAAAIAC1nSlIz4tNOvAMAAPwIAAAkAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9jZXJ0aW5mby5jVVQFAAG2SCRgrVRtb9s2EP6uX3H1sMByVcvtp7Z2g7mO3Roz7MBSFgTLINASFXGQSIGkYmdL//uOlOQo2ApnQBXEJ5LPy/F4lD/4cY8DAzj5RPY/wgejZVxK8SeN9X+jo+gR6j9k3WI8ZeLDE+UxcuE05RH6lhI1LhPzHkWnjG5NbubHN8zbyLziDNIMcybKB8nuMg39mQtvP3x4D2/g3ejdyIMLwhnNIdCU76i882CS2JlfMnI4DBU994BqIPmwkQozpkCJVO+JpIDvOYspVzQBoiChKpZshwPGQWcUUpZTmG0ub5brLx7sMxZnRuRBVKAyUeUJZOSegqQxZfe1RkmkBpEiHcUTpjQKVpoJPkRvCprKQhkNY09yJYDcE5aTHRoR
*/