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
nA6L4SlwETwbLtb3U6rpogxeAZfBXXA5fEj1j6j+VbgCNsOP1bArXA37wjXwWHgWHAnPgcfDc+E4iL/0bDJd+wSTNbzus8nIGxLOn8BM+ACcAB+EZfAheCZ8Ai6Dj8Bq+FO4WvV74B54AP4Mvqbyb8PH4aeq/xf8BUywRS/+SzbrZ2Ttjfivo5Pv1X9Pa3n4a9gN7oXD4D44B/4GLoAvwG3wt/Bm1T+n+hdVTzmEXuJT9Feq/ruqfwruh00TSDcwDb4Ij4IvwfHwIJwHX4FnwT/A8+Af4Y3wALwJvg53wzfgfvgmfBG+Aw/Cv8DP4PswnXB/oPEx38xBJw/q+2L+F99RTZ/ItYSzYTs4B+bAefq9KNTvw3w4FS6C0+GZ8BR4ucbbQlgMUfKeS2CVyl+l8teo/DZYpvFaAe+AS+Ev9fk+WAVfgCvg71X/D1gNs2zyC+wAHX1X1feCq+AEuBmWwe/Acng5XA43wNXwfHguvABeAC+El8Cz4OVwLbwWngNvhOfCW+Bl8Ha4Be5Ue7V+qvOPiXs7tn56vY1/4Y0wB94EB8LvwyHwZv1+3gJPg7fCufA2uALeDtfAH8Dz4A/hevi0fld3wv3wTvgqrIXvwHvg53CXfjfvhSF4H2wBfwIz4P0wCz4AO8CHYA58GPaEj8C+cA88SvWDVT8d/gyWwUdhheqr4ONwld6/Bj4Gb9T798FfwF/BJ+Be+CT8LXwKvgKf1u98qaVzOOEa/X42g8SRXM8ilwl/BTvBvbA33Af7w9/AAXA/HAGfg1Pg83ARfAFW6PMPYU4Cdqh7XfW76pTP1L3l+sIpJ6EdoFkJg3CM6otUfwAmwXdgMvwYNoV/h81gAnaGYDPYAnaHLWEfmAonwzQ4F7aGxTATLoFt4QrYDq6E2fAc1a+H7eEFqr9E9VfBjvB7sBO8HnaGN6n+FtXfofqfwRz4uOqfUP1Tqn9W9W+rufdV/7HqnfIuF2bCLrA77Ab7wDw4GPaAJ8CecCrsBytgPqyGR8E1cAC8Dk6GN8Ep8HY4Ff4UToP7YAH8EA6GiwO0O+ESeCw8Bw6FF8Bh8MdwhGMejoSvwlHwczgWJvHex8EUeCLMgBNge9gEOumk0szvIA9rugzBYk2XM5CTeXNwMJwJj4Wz4QQ4By6Ac+EieDrcBOfBi2ERvBrOh1tVr+1p5ivEb09P0nrHZJgKp8AM1at55gbEb88XqPmToMxPhK1Vr/VZHTcnDD712X76HekP+8F8ONB1RukAOA4OhJP0vtqrY9r4xcfeDsgFYEeYBDvDdJir368u+t3qCnvDPFd7Zq/am+rTThis4TsGtoFDYQEcpvXi4bAcjoDLVH+W6s9R/QbVXwpHwlvhcfBBOErrYcfDfXAMfBOeAN+G48170fE3/e19L3ybpJ13BewFr4R9IXnbxF+Nmu/uE38XIudwEwzAi2FLeAnMgpthF/gdmAcvVXt3oGrV3tEaf068b1N7O+H/TrAL7AW7wsGwG5wJ8+By2B1ugj3gFtgLfh/2hvfDPtqe6Av3qf53qn8N9oMfw/4w2SauYDt4FOwHB8BaAsYZpYc9x9R7hqmeX/o/dXbpN3VuqZ5Z+j93XqnPWaWN55QewTmlG4clylmlz3Ae6duo5MuCVh/UeFQpqga1FbUL9TzqECpjC2eYoiajilE1qO2o3ajnUe+iki/HHtRkVDGqBrUVtQu19/LGs08br8ar8Wq8/s3elQBGVZzh9/ZIIAmQhJCES0LITSDh0oiIMQQN93IakJoEEkwgx5YEDBUwUEpRUIMHIIqgVfEWj1ZU1KhVKYKiotJqFa+WtiheVFqvfu/Pv/++ffveJikRrd0Hk2//N//MvJk=
*/