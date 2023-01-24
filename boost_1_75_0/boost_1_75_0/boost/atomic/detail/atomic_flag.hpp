/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_flag.hpp
 *
 * This header contains interface definition of \c atomic_flag.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_

#include <boost/assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/operations.hpp>
#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
#include <boost/type_traits/type_with_alignment.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace boost {
namespace atomics {

#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT) || defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
#define BOOST_ATOMIC_NO_ATOMIC_FLAG_INIT
#else
#define BOOST_ATOMIC_FLAG_INIT {}
#endif

struct atomic_flag
{
    typedef atomics::detail::operations< 1u, false > operations;
    typedef operations::storage_type storage_type;

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
    alignas(operations::storage_alignment) storage_type m_storage;
#else
    // Note: Some compilers cannot use constant expressions in alignment attributes, so we have to use the union trick
    union
    {
        storage_type m_storage;
        boost::type_with_alignment< operations::storage_alignment >::type m_aligner;
    };
#endif

    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT atomic_flag() BOOST_NOEXCEPT : m_storage(0u)
    {
    }

    BOOST_FORCEINLINE bool test(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);
        return !!operations::load(m_storage, order);
    }

    BOOST_FORCEINLINE bool test_and_set(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return operations::test_and_set(m_storage, order);
    }

    BOOST_FORCEINLINE void clear(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);
        operations::clear(m_storage, order);
    }

    BOOST_DELETED_FUNCTION(atomic_flag(atomic_flag const&))
    BOOST_DELETED_FUNCTION(atomic_flag& operator= (atomic_flag const&))
};

} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_FLAG_HPP_INCLUDED_

/* atomic_flag.hpp
WPz/Yp0f6neOrfRrDDb3N7LBLycL46DVRpT66YrAYJdShi7H2/5ndNkyQ7uaIuYWqvjgb+1Xk8cLuCIlBh5/0gZ6BG+jZaSpL/YTCZ3uw3N647bVnGgiLzcZsmKMoebmKDFK2GU75g2bJQ/LYkja3EiHCUxvRpkm3RN3PFvdUDcVbXiKsOkYx2tH1JOSpuknLArEHq62lCwucfl+hrj9MNbfKu65x0PkrvddMwBqDOl4i5K8/Ya+/LZjbdm3DNMUbmiuLPIdF3O+SjB9CVQmyt8WYHG11XS1wqKz0VnfACUHh7R6ps9CE4iZT/If4QVb058aETB0f7te1/km19fCl70kVPkR1Ro39PapOXsR3CKxWS0rlOzjaEmp9LKxuW4BWDXsmA+auiRtE4j847gEM2Y9xeCLZfYrXiT6nH0VrLLyLszdJTo5zyyt88JxRKKQqAW1QQwKCk9zLVtwjf4cviJKRZJgMmqBaSDqD4f9t6kPkJ5OBuIZ/2NyP9W9mTTJCDD7+/sp32sWH/JBukXwitz+uJkgpePXDO07Fu7ltff5U2MFJ133DrEZQleL7dd4D408xXXernj4I4oUtEGyia1Juze62PsUvFPq1yw9V1yvNGt9c91LRP/NhgrZst36E3eLdYjHUDGJYGKeaQ9K4GKILr3ctrO17flgNOUs+uQtbunIMDI26nJjLJe8sEvRZmbBVFGsfe4BTvjv
*/