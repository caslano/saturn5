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
PgyKHPcyt2AZuVNvrEulAJ3pLebAWSvARPRqFgroXPOSLkIlpVlxk016tFSkhRY1TEcpWpnqSROFexpDgdswDplax/Cg29B+hs6JfZIMetTZbCkNYXadForIhvCRO1NQWpgEC8Sjt+1IsyajOFuz7Pkc7U5dKR0o8/es/9SucdRbTjxD+i/IJu4q1b84NhxDor9/qe5Z+iK+C6dEjdVq50CXUFZo4ls3V1vM5W4XRotOJQT3qVjpCezHX9WkqFiLwpQ0t2pePzvoH5psC94rqidpnzlv6DwWXfCvs1aoLcSL2ng3bWYA1TQgvsjwQr0V95Lzw9Pu4+ouuYimal4HTpR3ncDq8Q0ZoyqFuaA40wbBXv9qhjFepE3c5WVxR21PxQuw0CWR56kEhL9btFFPnsKLab8VVEeOpWTxbTj59Q5eO9qFAzL5oBdQ6PPjA/30WTfhY4RBMkEWffez9h5txlS8/9FvRe++vvn4uHv37dt1G+rD7xc8CIwBZADSZLrlx2aq83/xfb9//LBmbxH4ro5tI97Gpa4cjtr8NmMr84BNC9MyMKgPiv2tHFSdly5Wl7WjWpMZw1Xqa2bYAZf5n4VcBqZIzf4oMfg6fteFqim4+lR2mblfXVt6tZ5p+6oyv3mhHs91MpBhyJxl
*/