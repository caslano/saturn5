/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014-2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_impl.hpp
 *
 * This header contains implementation of \c atomic template.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_IMPL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_IMPL_HPP_INCLUDED_

#include <cstddef>
#include <boost/assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/intptr.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>
#include <boost/atomic/detail/core_operations.hpp>
#include <boost/atomic/detail/wait_operations.hpp>
#include <boost/atomic/detail/extra_operations.hpp>
#include <boost/atomic/detail/memory_order_utils.hpp>
#include <boost/atomic/detail/aligned_variable.hpp>
#include <boost/atomic/detail/type_traits/is_signed.hpp>
#include <boost/atomic/detail/type_traits/is_nothrow_default_constructible.hpp>
#include <boost/atomic/detail/type_traits/is_trivially_default_constructible.hpp>
#include <boost/atomic/detail/type_traits/alignment_of.hpp>
#include <boost/atomic/detail/type_traits/conditional.hpp>
#include <boost/atomic/detail/type_traits/integral_constant.hpp>
#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/fp_operations.hpp>
#include <boost/atomic/detail/extra_fp_operations.hpp>
#endif
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_UNION_INIT) && !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_CONSTEXPR_BITWISE_CAST)
#define BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR BOOST_CONSTEXPR
#else
#define BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in gcc_atomic_memory_order_utils.hpp.
 */

namespace boost {
namespace atomics {
namespace detail {

template< typename T, bool Signed, bool Interprocess >
class base_atomic_common
{
public:
    typedef T value_type;

protected:
    typedef atomics::detail::core_operations< storage_size_of< value_type >::value, Signed, Interprocess > core_operations;
    typedef atomics::detail::wait_operations< core_operations > wait_operations;
    typedef typename atomics::detail::conditional< sizeof(value_type) <= sizeof(void*), value_type, value_type const& >::type value_arg_type;
    typedef typename core_operations::storage_type storage_type;

protected:
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment ? core_operations::storage_alignment : atomics::detail::alignment_of< value_type >::value;

public:
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = core_operations::is_always_lock_free;
    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = wait_operations::always_has_native_wait_notify;

protected:
    BOOST_ATOMIC_DETAIL_ALIGNED_VAR_TPL(storage_alignment, storage_type, m_storage);

public:
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT base_atomic_common() BOOST_NOEXCEPT : m_storage()
    {
    }

    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT explicit base_atomic_common(storage_type v) BOOST_NOEXCEPT : m_storage(v)
    {
    }

    BOOST_FORCEINLINE value_type& value() BOOST_NOEXCEPT { return *reinterpret_cast< value_type* >(&m_storage); }
    BOOST_FORCEINLINE value_type volatile& value() volatile BOOST_NOEXCEPT { return *reinterpret_cast< volatile value_type* >(&m_storage); }
    BOOST_FORCEINLINE value_type const& value() const BOOST_NOEXCEPT { return *reinterpret_cast< const value_type* >(&m_storage); }
    BOOST_FORCEINLINE value_type const volatile& value() const volatile BOOST_NOEXCEPT { return *reinterpret_cast< const volatile value_type* >(&m_storage); }

protected:
    BOOST_FORCEINLINE storage_type& storage() BOOST_NOEXCEPT { return m_storage; }
    BOOST_FORCEINLINE storage_type volatile& storage() volatile BOOST_NOEXCEPT { return m_storage; }
    BOOST_FORCEINLINE storage_type const& storage() const BOOST_NOEXCEPT { return m_storage; }
    BOOST_FORCEINLINE storage_type const volatile& storage() const volatile BOOST_NOEXCEPT { return m_storage; }

public:
    BOOST_FORCEINLINE bool is_lock_free() const volatile BOOST_NOEXCEPT
    {
        // C++17 requires all instances of atomic<> return a value consistent with is_always_lock_free here.
        // Boost.Atomic also enforces the required alignment of the atomic storage, so we can always return is_always_lock_free.
        return is_always_lock_free;
    }

    BOOST_FORCEINLINE bool has_native_wait_notify() const volatile BOOST_NOEXCEPT
    {
        return wait_operations::has_native_wait_notify(this->storage());
    }

    BOOST_FORCEINLINE void notify_one() volatile BOOST_NOEXCEPT
    {
        wait_operations::notify_one(this->storage());
    }

    BOOST_FORCEINLINE void notify_all() volatile BOOST_NOEXCEPT
    {
        wait_operations::notify_all(this->storage());
    }
};

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
template< typename T, bool Signed, bool Interprocess >
BOOST_CONSTEXPR_OR_CONST bool base_atomic_common< T, Signed, Interprocess >::is_always_lock_free;
template< typename T, bool Signed, bool Interprocess >
BOOST_CONSTEXPR_OR_CONST bool base_atomic_common< T, Signed, Interprocess >::always_has_native_wait_notify;
#endif


template< typename T, bool Interprocess, bool IsTriviallyDefaultConstructible = atomics::detail::is_trivially_default_constructible< T >::value >
class base_atomic_generic;

template< typename T, bool Interprocess >
class base_atomic_generic< T, Interprocess, true > :
    public base_atomic_common< T, false, Interprocess >
{
private:
    typedef base_atomic_common< T, false, Interprocess > base_type;

protected:
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_generic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR explicit base_atomic_generic(value_arg_type v) BOOST_NOEXCEPT :
        base_type(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }
};

template< typename T, bool Interprocess >
class base_atomic_generic< T, Interprocess, false > :
    public base_atomic_common< T, false, Interprocess >
{
private:
    typedef base_atomic_common< T, false, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR explicit base_atomic_generic(value_arg_type v = value_type()) BOOST_NOEXCEPT :
        base_type(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }
};


template< typename T, typename Kind, bool Interprocess >
class base_atomic;

//! General template. Implementation for user-defined types, such as structs, and pointers to non-object types
template< typename T, bool Interprocess >
class base_atomic< T, void, Interprocess > :
    public base_atomic_generic< T, Interprocess >
{
private:
    typedef base_atomic_generic< T, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR base_atomic() BOOST_NOEXCEPT_IF(atomics::detail::is_nothrow_default_constructible< value_type >::value) : base_type()
    {
    }

    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::exchange(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(wait_operations::wait(this->storage(), atomics::detail::bitwise_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};


//! Implementation for enums
template< typename T, bool Interprocess >
class base_atomic< T, const int, Interprocess > :
    public base_atomic_common< T, false, Interprocess >
{
private:
    typedef base_atomic_common< T, false, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(static_cast< storage_type >(v))
    {
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::exchange(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(wait_operations::wait(this->storage(), static_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};


//! Implementation for integers
template< typename T, bool Interprocess >
class base_atomic< T, int, Interprocess > :
    public base_atomic_common< T, atomics::detail::is_signed< T >::value, Interprocess >
{
private:
    typedef base_atomic_common< T, atomics::detail::is_signed< T >::value, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef value_type difference_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef atomics::detail::extra_operations< core_operations > extra_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(static_cast< storage_type >(v)) {}

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::integral_truncate< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(core_operations::fetch_add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(core_operations::fetch_sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(core_operations::exchange(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type fetch_and(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(core_operations::fetch_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_or(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(core_operations::fetch_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_xor(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(core_operations::fetch_xor(this->storage(), static_cast< storage_type >(v), order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type fetch_negate(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::fetch_negate(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_complement(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::fetch_complement(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type negate(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::negate(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type bitwise_and(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_or(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_xor(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_xor(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_complement(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_complement(this->storage(), order));
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_add(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_sub(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_negate(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_negate(this->storage(), order);
    }

    BOOST_FORCEINLINE void opaque_and(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_and(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_or(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_or(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_xor(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_xor(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_complement(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_complement(this->storage(), order);
    }

    BOOST_FORCEINLINE bool add_and_test(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::add_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool sub_and_test(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::sub_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool negate_and_test(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::negate_and_test(this->storage(), order);
    }

    BOOST_FORCEINLINE bool and_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::and_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool or_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::or_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool xor_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::xor_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool complement_and_test(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::complement_and_test(this->storage(), order);
    }

    BOOST_FORCEINLINE bool bit_test_and_set(unsigned int bit_number, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_set(this->storage(), bit_number, order);
    }

    BOOST_FORCEINLINE bool bit_test_and_reset(unsigned int bit_number, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_reset(this->storage(), bit_number, order);
    }

    BOOST_FORCEINLINE bool bit_test_and_complement(unsigned int bit_number, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_complement(this->storage(), bit_number, order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator++(int) volatile BOOST_NOEXCEPT
    {
        return fetch_add(1);
    }

    BOOST_FORCEINLINE value_type operator++() volatile BOOST_NOEXCEPT
    {
        return add(1);
    }

    BOOST_FORCEINLINE value_type operator--(int) volatile BOOST_NOEXCEPT
    {
        return fetch_sub(1);
    }

    BOOST_FORCEINLINE value_type operator--() volatile BOOST_NOEXCEPT
    {
        return sub(1);
    }

    BOOST_FORCEINLINE value_type operator+=(difference_type v) volatile BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) volatile BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type operator&=(value_type v) volatile BOOST_NOEXCEPT
    {
        return bitwise_and(v);
    }

    BOOST_FORCEINLINE value_type operator|=(value_type v) volatile BOOST_NOEXCEPT
    {
        return bitwise_or(v);
    }

    BOOST_FORCEINLINE value_type operator^=(value_type v) volatile BOOST_NOEXCEPT
    {
        return bitwise_xor(v);
    }

    BOOST_FORCEINLINE value_type wait(value_type old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::integral_truncate< value_type >(wait_operations::wait(this->storage(), static_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::integral_truncate< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::integral_truncate< value_type >(old_value);
        return res;
    }
};

//! Implementation for bool
template< bool Interprocess >
class base_atomic< bool, int, Interprocess > :
    public base_atomic_common< bool, false, Interprocess >
{
private:
    typedef base_atomic_common< bool, false, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(static_cast< storage_type >(v)) {}

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!core_operations::load(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return !!core_operations::exchange(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type wait(value_type old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!wait_operations::wait(this->storage(), static_cast< storage_type >(old_val), order);
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }
};


#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)

//! Implementation for floating point types
template< typename T, bool Interprocess >
class base_atomic< T, float, Interprocess > :
    public base_atomic_common< T, false, Interprocess >
{
private:
    typedef base_atomic_common< T, false, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef value_type difference_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef atomics::detail::extra_operations< core_operations > extra_operations;
    typedef atomics::detail::fp_operations< extra_operations, value_type > fp_operations;
    typedef atomics::detail::extra_fp_operations< fp_operations > extra_fp_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool,
        atomics::detail::value_size_of< value_type >::value != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment
    > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT :
        base_type(atomics::detail::bitwise_fp_cast< storage_type >(v))
    {
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_fp_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return fp_operations::fetch_add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return fp_operations::fetch_sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(core_operations::exchange(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type fetch_negate(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_fp_operations::fetch_negate(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_fp_operations::add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_fp_operations::sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type negate(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_fp_operations::negate(this->storage(), order);
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE void opaque_negate(memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_negate(this->storage(), order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator+=(difference_type v) volatile BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) volatile BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_fp_cast< value_type >(wait_operations::wait(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_fp_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_fp_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_fp_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_fp_cast< value_type >(old_value);
        return res;
    }
};

#endif // !defined(BOOST_ATOMIC_NO_FLOATING_POINT)


//! Implementation for pointers to object types
template< typename T, bool Interprocess >
class base_atomic< T*, void*, Interprocess > :
    public base_atomic_common< T*, false, Interprocess >
{
private:
    typedef base_atomic_common< T*, false, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef std::ptrdiff_t difference_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef atomics::detail::extra_operations< core_operations > extra_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

    // uintptr_storage_type is the minimal storage type that is enough to store pointers. The actual storage_type theoretically may be larger,
    // if the target architecture only supports atomic ops on larger data. Typically, though, they are the same type.
    typedef atomics::detail::uintptr_t uintptr_storage_type;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_ATOMIC_CTOR explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT :
        base_type(atomics::detail::bitwise_cast< uintptr_storage_type >(v))
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(core_operations::load(this->storage(), order)));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(core_operations::fetch_add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(core_operations::fetch_sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(core_operations::exchange(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(v), order)));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(extra_operations::add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(extra_operations::sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        extra_operations::opaque_sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE bool add_and_test(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::add_and_test(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE bool sub_and_test(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return extra_operations::sub_and_test(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator++(int) volatile BOOST_NOEXCEPT
    {
        return fetch_add(1);
    }

    BOOST_FORCEINLINE value_type operator++() volatile BOOST_NOEXCEPT
    {
        return add(1);
    }

    BOOST_FORCEINLINE value_type operator--(int) volatile BOOST_NOEXCEPT
    {
        return fetch_sub(1);
    }

    BOOST_FORCEINLINE value_type operator--() volatile BOOST_NOEXCEPT
    {
        return sub(1);
    }

    BOOST_FORCEINLINE value_type operator+=(difference_type v) volatile BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) volatile BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(wait_operations::wait(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(old_val), order)));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< uintptr_storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(old_value));
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< uintptr_storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(old_value));
        return res;
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_IMPl_HPP_INCLUDED_

/* atomic_impl.hpp
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
*/