/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_ref_impl.hpp
 *
 * This header contains implementation of \c atomic_ref template.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_REF_IMPL_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_REF_IMPL_HPP_INCLUDED_

#include <cstddef>
#include <boost/assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/addressof.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>
#include <boost/atomic/detail/core_operations.hpp>
#include <boost/atomic/detail/wait_operations.hpp>
#include <boost/atomic/detail/extra_operations.hpp>
#include <boost/atomic/detail/core_operations_emulated.hpp>
#include <boost/atomic/detail/memory_order_utils.hpp>
#include <boost/atomic/detail/type_traits/is_signed.hpp>
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

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in gcc_atomic_memory_order_utils.hpp.
 */

namespace boost {
namespace atomics {
namespace detail {

template< typename T, bool Signed, bool Interprocess >
struct is_atomic_ref_lock_free
{
    typedef T value_type;
    typedef atomics::detail::core_operations< sizeof(value_type), Signed, Interprocess > core_operations;
    typedef typename core_operations::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool value = sizeof(value_type) == sizeof(storage_type) && core_operations::is_always_lock_free;
};

template< typename T, bool Signed, bool Interprocess >
class base_atomic_ref_common
{
public:
    typedef T value_type;

protected:
    typedef typename atomics::detail::conditional<
        atomics::detail::is_atomic_ref_lock_free< T, Signed, Interprocess >::value,
        atomics::detail::core_operations< sizeof(value_type), Signed, Interprocess >,
        atomics::detail::core_operations_emulated< sizeof(value_type), atomics::detail::alignment_of< value_type >::value, Signed, Interprocess >
    >::type core_operations;
    typedef atomics::detail::wait_operations< core_operations > wait_operations;
    typedef typename atomics::detail::conditional< sizeof(value_type) <= sizeof(void*), value_type, value_type const& >::type value_arg_type;
    typedef typename core_operations::storage_type storage_type;
    BOOST_STATIC_ASSERT_MSG(sizeof(storage_type) == sizeof(value_type), "Boost.Atomic internal error: atomic_ref storage size doesn't match the value size");

public:
    static BOOST_CONSTEXPR_OR_CONST std::size_t required_alignment = atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment ? core_operations::storage_alignment : atomics::detail::alignment_of< value_type >::value;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = core_operations::is_always_lock_free;
    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = wait_operations::always_has_native_wait_notify;

protected:
    value_type* m_value;

public:
    BOOST_FORCEINLINE explicit base_atomic_ref_common(value_type& v) BOOST_NOEXCEPT : m_value(atomics::detail::addressof(v))
    {
        BOOST_ATOMIC_DETAIL_CLEAR_PADDING(this->m_value);
    }

    BOOST_FORCEINLINE value_type& value() const BOOST_NOEXCEPT { return *m_value; }

protected:
    BOOST_FORCEINLINE storage_type& storage() const BOOST_NOEXCEPT
    {
        return *reinterpret_cast< storage_type* >(m_value);
    }

public:
    BOOST_FORCEINLINE bool is_lock_free() const BOOST_NOEXCEPT
    {
        // C++20 specifies that is_lock_free returns true if operations on *all* objects of the atomic_ref<T> type are lock-free.
        // This does not allow to return true or false depending on the referenced object runtime alignment. Currently, Boost.Atomic
        // follows this specification, although we may support runtime alignment checking in the future.
        return is_always_lock_free;
    }

    BOOST_FORCEINLINE bool has_native_wait_notify() const BOOST_NOEXCEPT
    {
        return wait_operations::has_native_wait_notify(this->storage());
    }

    BOOST_FORCEINLINE void notify_one() const BOOST_NOEXCEPT
    {
        wait_operations::notify_one(this->storage());
    }

    BOOST_FORCEINLINE void notify_all() const BOOST_NOEXCEPT
    {
        wait_operations::notify_all(this->storage());
    }
};

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
template< typename T, bool Signed, bool Interprocess >
BOOST_CONSTEXPR_OR_CONST std::size_t base_atomic_ref_common< T, Signed, Interprocess >::required_alignment;
template< typename T, bool Signed, bool Interprocess >
BOOST_CONSTEXPR_OR_CONST bool base_atomic_ref_common< T, Signed, Interprocess >::is_always_lock_free;
template< typename T, bool Signed, bool Interprocess >
BOOST_CONSTEXPR_OR_CONST bool base_atomic_ref_common< T, Signed, Interprocess >::always_has_native_wait_notify;
#endif


template< typename T, typename Kind, bool Interprocess >
class base_atomic_ref;

//! General template. Implementation for user-defined types, such as structs, and pointers to non-object types
template< typename T, bool Interprocess >
class base_atomic_ref< T, void, Interprocess > :
    public base_atomic_ref_common< T, false, Interprocess >
{
private:
    typedef base_atomic_ref_common< T, false, Interprocess > base_type;

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
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::exchange(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(wait_operations::wait(this->storage(), atomics::detail::bitwise_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};


//! Implementation for enums
template< typename T, bool Interprocess >
class base_atomic_ref< T, const int, Interprocess > :
    public base_atomic_ref_common< T, false, Interprocess >
{
private:
    typedef base_atomic_ref_common< T, false, Interprocess > base_type;

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
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::exchange(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(wait_operations::wait(this->storage(), static_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};


//! Implementation for integers
template< typename T, bool Interprocess >
class base_atomic_ref< T, int, Interprocess > :
    public base_atomic_ref_common< T, atomics::detail::is_signed< T >::value, Interprocess >
{
private:
    typedef base_atomic_ref_common< T, atomics::detail::is_signed< T >::value, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef typename base_type::value_type difference_type;

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
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::exchange(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type fetch_and(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_or(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_xor(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_xor(this->storage(), static_cast< storage_type >(v), order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type fetch_negate(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::fetch_negate(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_complement(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::fetch_complement(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type negate(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::negate(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type bitwise_and(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::bitwise_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_or(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::bitwise_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_xor(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::bitwise_xor(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_complement(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::bitwise_complement(this->storage(), order));
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_add(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_sub(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_negate(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_negate(this->storage(), order);
    }

    BOOST_FORCEINLINE void opaque_and(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_and(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_or(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_or(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_xor(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_xor(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_complement(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_complement(this->storage(), order);
    }

    BOOST_FORCEINLINE bool add_and_test(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::add_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool sub_and_test(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::sub_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool negate_and_test(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::negate_and_test(this->storage(), order);
    }

    BOOST_FORCEINLINE bool and_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::and_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool or_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::or_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool xor_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::xor_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool complement_and_test(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::complement_and_test(this->storage(), order);
    }

    BOOST_FORCEINLINE bool bit_test_and_set(unsigned int bit_number, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_set(this->storage(), bit_number, order);
    }

    BOOST_FORCEINLINE bool bit_test_and_reset(unsigned int bit_number, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_reset(this->storage(), bit_number, order);
    }

    BOOST_FORCEINLINE bool bit_test_and_complement(unsigned int bit_number, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_complement(this->storage(), bit_number, order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator++(int) const BOOST_NOEXCEPT
    {
        return fetch_add(1);
    }

    BOOST_FORCEINLINE value_type operator++() const BOOST_NOEXCEPT
    {
        return add(1);
    }

    BOOST_FORCEINLINE value_type operator--(int) const BOOST_NOEXCEPT
    {
        return fetch_sub(1);
    }

    BOOST_FORCEINLINE value_type operator--() const BOOST_NOEXCEPT
    {
        return sub(1);
    }

    BOOST_FORCEINLINE value_type operator+=(difference_type v) const BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) const BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type operator&=(value_type v) const BOOST_NOEXCEPT
    {
        return bitwise_and(v);
    }

    BOOST_FORCEINLINE value_type operator|=(value_type v) const BOOST_NOEXCEPT
    {
        return bitwise_or(v);
    }

    BOOST_FORCEINLINE value_type operator^=(value_type v) const BOOST_NOEXCEPT
    {
        return bitwise_xor(v);
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(wait_operations::wait(this->storage(), static_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};

//! Implementation for bool
template< bool Interprocess >
class base_atomic_ref< bool, int, Interprocess > :
    public base_atomic_ref_common< bool, false, Interprocess >
{
private:
    typedef base_atomic_ref_common< bool, false, Interprocess > base_type;

public:
    typedef bool value_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!core_operations::load(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return !!core_operations::exchange(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!wait_operations::wait(this->storage(), static_cast< storage_type >(old_val), order);
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
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
class base_atomic_ref< T, float, Interprocess > :
    public base_atomic_ref_common< T, false, Interprocess >
{
private:
    typedef base_atomic_ref_common< T, false, Interprocess > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef typename base_type::value_type difference_type;

protected:
    typedef typename base_type::core_operations core_operations;
    typedef typename base_type::wait_operations wait_operations;
    typedef atomics::detail::extra_operations< core_operations > extra_operations;
    typedef atomics::detail::fp_operations< extra_operations, value_type > fp_operations;
    typedef atomics::detail::extra_fp_operations< fp_operations > extra_fp_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::integral_constant< bool, atomics::detail::value_size_of< value_type >::value != sizeof(storage_type) > has_padding_bits;
#endif
#if !defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS) || !defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    typedef atomics::detail::true_type cxchg_use_bitwise_cast;
#else
    typedef atomics::detail::integral_constant< bool, has_padding_bits::value || atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
        // We only need to call clear_padding_bits if the compiler does not implement
        // BOOST_ATOMIC_DETAIL_CLEAR_PADDING, which is called in the base class constructor.
#if defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
        this->clear_padding_bits(has_padding_bits());
#endif // defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_fp_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return fp_operations::fetch_add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return fp_operations::fetch_sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(core_operations::exchange(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type fetch_negate(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_fp_operations::fetch_negate(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_fp_operations::add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_fp_operations::sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type negate(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_fp_operations::negate(this->storage(), order);
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE void opaque_negate(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_negate(this->storage(), order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator+=(difference_type v) const BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) const BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_fp_cast< value_type >(wait_operations::wait(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
#if defined(BOOST_ATOMIC_NO_CLEAR_PADDING)
    BOOST_FORCEINLINE void clear_padding_bits(atomics::detail::false_type) const BOOST_NOEXCEPT
    {
    }

    BOOST_FORCEINLINE void clear_padding_bits(atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        atomics::detail::clear_tail_padding_bits< atomics::detail::value_size_of< value_type >::value >(this->storage());
    }
#endif // defined(BOOST_ATOMIC_NO_CLEAR_PADDING)

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_fp_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_fp_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
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
class base_atomic_ref< T*, void*, Interprocess > :
    public base_atomic_ref_common< T*, false, Interprocess >
{
private:
    typedef base_atomic_ref_common< T*, false, Interprocess > base_type;

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
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= core_operations::storage_alignment > cxchg_use_bitwise_cast;
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        core_operations::store(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(core_operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_add(this->storage(), static_cast< storage_type >(v * sizeof(T)), order));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::fetch_sub(this->storage(), static_cast< storage_type >(v * sizeof(T)), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(core_operations::exchange(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, cxchg_use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::add(this->storage(), static_cast< storage_type >(v * sizeof(T)), order));
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(extra_operations::sub(this->storage(), static_cast< storage_type >(v * sizeof(T)), order));
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_add(this->storage(), static_cast< storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        extra_operations::opaque_sub(this->storage(), static_cast< storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE bool add_and_test(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::add_and_test(this->storage(), static_cast< storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE bool sub_and_test(difference_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return extra_operations::sub_and_test(this->storage(), static_cast< storage_type >(v * sizeof(T)), order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator++(int) const BOOST_NOEXCEPT
    {
        return fetch_add(1);
    }

    BOOST_FORCEINLINE value_type operator++() const BOOST_NOEXCEPT
    {
        return add(1);
    }

    BOOST_FORCEINLINE value_type operator--(int) const BOOST_NOEXCEPT
    {
        return fetch_sub(1);
    }

    BOOST_FORCEINLINE value_type operator--() const BOOST_NOEXCEPT
    {
        return sub(1);
    }

    BOOST_FORCEINLINE value_type operator+=(difference_type v) const BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) const BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type wait(value_arg_type old_val, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(wait_operations::wait(this->storage(), atomics::detail::bitwise_cast< storage_type >(old_val), order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
        return core_operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = core_operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_REF_IMPL_HPP_INCLUDED_

/* atomic_ref_impl.hpp
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
*/