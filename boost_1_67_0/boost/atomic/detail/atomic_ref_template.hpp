/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/atomic_ref_template.hpp
 *
 * This header contains interface definition of \c atomic_ref template.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_REF_TEMPLATE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_REF_TEMPLATE_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/intptr.hpp>
#include <boost/atomic/detail/classify.hpp>
#include <boost/atomic/detail/addressof.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/bitwise_cast.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>
#include <boost/atomic/detail/operations.hpp>
#include <boost/atomic/detail/extra_operations.hpp>
#include <boost/atomic/detail/memory_order_utils.hpp>
#include <boost/atomic/detail/type_traits/is_signed.hpp>
#include <boost/atomic/detail/type_traits/is_trivially_copyable.hpp>
#include <boost/atomic/detail/type_traits/is_trivially_default_constructible.hpp>
#include <boost/atomic/detail/type_traits/alignment_of.hpp>
#include <boost/atomic/detail/type_traits/conditional.hpp>
#include <boost/atomic/detail/type_traits/integral_constant.hpp>
#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/fp_operations.hpp>
#include <boost/atomic/detail/extra_fp_operations.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// 'boost::atomics::atomic_ref<T>' : multiple assignment operators specified
#pragma warning(disable: 4522)
#endif

/*
 * IMPLEMENTATION NOTE: All interface functions MUST be declared with BOOST_FORCEINLINE,
 *                      see comment for convert_memory_order_to_gcc in ops_gcc_atomic.hpp.
 */

namespace boost {
namespace atomics {
namespace detail {

template< typename T, bool IsSigned >
struct is_atomic_ref_lock_free
{
    typedef T value_type;
    typedef atomics::detail::operations< sizeof(value_type), IsSigned > operations;
    typedef typename operations::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool value = sizeof(value_type) == sizeof(storage_type) && operations::is_always_lock_free;
};

template< typename T, bool IsSigned >
class base_atomic_ref_common
{
public:
    typedef T value_type;

protected:
    typedef typename atomics::detail::conditional<
        atomics::detail::is_atomic_ref_lock_free< T, IsSigned >::value,
        atomics::detail::operations< sizeof(value_type), IsSigned >,
        atomics::detail::emulated_operations< sizeof(value_type), atomics::detail::alignment_of< value_type >::value, IsSigned >
    >::type operations;
    typedef typename atomics::detail::conditional< sizeof(value_type) <= sizeof(void*), value_type, value_type const& >::type value_arg_type;
    typedef typename operations::storage_type storage_type;

public:
    static BOOST_CONSTEXPR_OR_CONST std::size_t required_alignment = atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment ? operations::storage_alignment : atomics::detail::alignment_of< value_type >::value;
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = operations::is_always_lock_free;

protected:
    value_type* m_value;

public:
    BOOST_FORCEINLINE explicit base_atomic_ref_common(value_type& v) BOOST_NOEXCEPT : m_value(atomics::detail::addressof(v))
    {
    }

protected:
    BOOST_FORCEINLINE storage_type& storage() const BOOST_NOEXCEPT
    {
        return *reinterpret_cast< storage_type* >(m_value);
    }
};

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
template< typename T, bool IsSigned >
BOOST_CONSTEXPR_OR_CONST std::size_t base_atomic_ref_common< T, IsSigned >::required_alignment;
template< typename T, bool IsSigned >
BOOST_CONSTEXPR_OR_CONST bool base_atomic_ref_common< T, IsSigned >::is_always_lock_free;
#endif


template< typename T, typename Kind >
class base_atomic_ref;

//! General template. Implementation for user-defined types, such as structs and enums, and pointers to non-object types
template< typename T >
class base_atomic_ref< T, void > :
    public base_atomic_ref_common< T, false >
{
private:
    typedef base_atomic_ref_common< T, false > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::operations operations;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

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

        operations::store(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::exchange(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};


//! Implementation for integers
template< typename T >
class base_atomic_ref< T, int > :
    public base_atomic_ref_common< T, atomics::detail::is_signed< T >::value >
{
private:
    typedef base_atomic_ref_common< T, atomics::detail::is_signed< T >::value > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef typename base_type::value_type difference_type;

protected:
    typedef typename base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::integral_truncate< value_type >(operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::exchange(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type fetch_and(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_or(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_xor(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_xor(this->storage(), static_cast< storage_type >(v), order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type fetch_negate(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::fetch_negate(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_complement(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::fetch_complement(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type negate(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::negate(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type bitwise_and(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_or(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_xor(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_xor(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type bitwise_complement(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(extra_operations::bitwise_complement(this->storage(), order));
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_add(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_sub(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_negate(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_negate(this->storage(), order);
    }

    BOOST_FORCEINLINE void opaque_and(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_and(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_or(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_or(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_xor(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_xor(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE void opaque_complement(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_complement(this->storage(), order);
    }

    BOOST_FORCEINLINE bool add_and_test(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::add_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool sub_and_test(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::sub_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool negate_and_test(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::negate_and_test(this->storage(), order);
    }

    BOOST_FORCEINLINE bool and_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::and_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool or_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::or_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool xor_and_test(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::xor_and_test(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool complement_and_test(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::complement_and_test(this->storage(), order);
    }

    BOOST_FORCEINLINE bool bit_test_and_set(unsigned int bit_number, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_set(this->storage(), bit_number, order);
    }

    BOOST_FORCEINLINE bool bit_test_and_reset(unsigned int bit_number, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_reset(this->storage(), bit_number, order);
    }

    BOOST_FORCEINLINE bool bit_test_and_complement(unsigned int bit_number, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(bit_number < sizeof(value_type) * 8u);
        return extra_operations::bit_test_and_complement(this->storage(), bit_number, order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator++(int) BOOST_NOEXCEPT
    {
        return fetch_add(1);
    }

    BOOST_FORCEINLINE value_type operator++() BOOST_NOEXCEPT
    {
        return add(1);
    }

    BOOST_FORCEINLINE value_type operator--(int) BOOST_NOEXCEPT
    {
        return fetch_sub(1);
    }

    BOOST_FORCEINLINE value_type operator--() BOOST_NOEXCEPT
    {
        return sub(1);
    }

    BOOST_FORCEINLINE value_type operator+=(difference_type v) BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_FORCEINLINE value_type operator&=(value_type v) BOOST_NOEXCEPT
    {
        return bitwise_and(v);
    }

    BOOST_FORCEINLINE value_type operator|=(value_type v) BOOST_NOEXCEPT
    {
        return bitwise_or(v);
    }

    BOOST_FORCEINLINE value_type operator^=(value_type v) BOOST_NOEXCEPT
    {
        return bitwise_xor(v);
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::integral_truncate< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::integral_truncate< value_type >(old_value);
        return res;
    }
};

//! Implementation for bool
template< >
class base_atomic_ref< bool, int > :
    public base_atomic_ref_common< bool, false >
{
private:
    typedef base_atomic_ref_common< bool, false > base_type;

public:
    typedef bool value_type;

protected:
    typedef base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!operations::load(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return !!operations::exchange(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }
};


#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)

//! Implementation for floating point types
template< typename T >
class base_atomic_ref< T, float > :
    public base_atomic_ref_common< T, false >
{
private:
    typedef base_atomic_ref_common< T, false > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef typename base_type::value_type difference_type;

protected:
    typedef typename base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef atomics::detail::fp_operations< extra_operations, value_type, operations::storage_size > fp_operations;
    typedef atomics::detail::extra_fp_operations< fp_operations, value_type, operations::storage_size > extra_fp_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, atomics::detail::value_sizeof< value_type >::value != sizeof(storage_type) > has_padding_bits;
    typedef atomics::detail::integral_constant< bool, has_padding_bits::value || atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
        this->clear_padding_bits(has_padding_bits());
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_fp_cast< value_type >(operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return fp_operations::fetch_add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return fp_operations::fetch_sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(operations::exchange(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type fetch_negate(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_fp_operations::fetch_negate(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_fp_operations::add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_fp_operations::sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE value_type negate(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_fp_operations::negate(this->storage(), order);
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_add(this->storage(), v, order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_sub(this->storage(), v, order);
    }

    BOOST_FORCEINLINE void opaque_negate(memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_fp_operations::opaque_negate(this->storage(), order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator+=(difference_type v) BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE void clear_padding_bits(atomics::detail::false_type) const BOOST_NOEXCEPT
    {
    }

    BOOST_FORCEINLINE void clear_padding_bits(atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = operations::load(this->storage(), boost::memory_order_relaxed);
        while (true)
        {
            storage_type new_value = old_value;
            atomics::detail::clear_tail_padding_bits< atomics::detail::value_sizeof< value_type >::value >(new_value);
            bool res = operations::compare_exchange_weak(this->storage(), old_value, new_value, boost::memory_order_relaxed, boost::memory_order_relaxed);
            if (BOOST_LIKELY(res))
                break;
        }
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_fp_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_fp_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_fp_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_fp_cast< value_type >(old_value);
        return res;
    }
};

#endif // !defined(BOOST_ATOMIC_NO_FLOATING_POINT)


//! Implementation for pointers to object types
template< typename T >
class base_atomic_ref< T*, void* > :
    public base_atomic_ref_common< T*, false >
{
private:
    typedef base_atomic_ref_common< T*, false > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef std::ptrdiff_t difference_type;

protected:
    typedef typename base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

    // uintptr_storage_type is the minimal storage type that is enough to store pointers. The actual storage_type theoretically may be larger,
    // if the target architecture only supports atomic ops on larger data. Typically, though, they are the same type.
    typedef atomics::detail::uintptr_t uintptr_storage_type;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_ref(base_atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit base_atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::load(this->storage(), order)));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::fetch_add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::fetch_sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::exchange(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(v), order)));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_strong(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    // Boost.Atomic extensions
    BOOST_FORCEINLINE value_type add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(extra_operations::add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(extra_operations::sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE void opaque_add(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE void opaque_sub(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        extra_operations::opaque_sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE bool add_and_test(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::add_and_test(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    BOOST_FORCEINLINE bool sub_and_test(difference_type v, memory_order order = memory_order_seq_cst) BOOST_NOEXCEPT
    {
        return extra_operations::sub_and_test(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order);
    }

    // Operators
    BOOST_FORCEINLINE value_type operator++(int) BOOST_NOEXCEPT
    {
        return fetch_add(1);
    }

    BOOST_FORCEINLINE value_type operator++() BOOST_NOEXCEPT
    {
        return add(1);
    }

    BOOST_FORCEINLINE value_type operator--(int) BOOST_NOEXCEPT
    {
        return fetch_sub(1);
    }

    BOOST_FORCEINLINE value_type operator--() BOOST_NOEXCEPT
    {
        return sub(1);
    }

    BOOST_FORCEINLINE value_type operator+=(difference_type v) BOOST_NOEXCEPT
    {
        return add(v);
    }

    BOOST_FORCEINLINE value_type operator-=(difference_type v) BOOST_NOEXCEPT
    {
        return sub(v);
    }

    BOOST_DELETED_FUNCTION(base_atomic_ref& operator=(base_atomic_ref const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< uintptr_storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(old_value));
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) const BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) const BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< uintptr_storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(old_value));
        return res;
    }
};

} // namespace detail

template< typename T >
class atomic_ref :
    public atomics::detail::base_atomic_ref< T, typename atomics::detail::classify< T >::type >
{
private:
    typedef atomics::detail::base_atomic_ref< T, typename atomics::detail::classify< T >::type > base_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    typedef typename base_type::value_type value_type;

    BOOST_STATIC_ASSERT_MSG(sizeof(value_type) > 0u, "boost::atomic_ref<T> requires T to be a complete type");
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)
    BOOST_STATIC_ASSERT_MSG(atomics::detail::is_trivially_copyable< value_type >::value, "boost::atomic_ref<T> requires T to be a trivially copyable type");
#endif

private:
    typedef typename base_type::storage_type storage_type;

public:
    BOOST_DEFAULTED_FUNCTION(atomic_ref(atomic_ref const& that) BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL : base_type(static_cast< base_type const& >(that)) {})
    BOOST_FORCEINLINE explicit atomic_ref(value_type& v) BOOST_NOEXCEPT : base_type(v)
    {
        // Check that referenced object alignment satisfies required alignment
        BOOST_ASSERT((((atomics::detail::uintptr_t)this->m_value) & (base_type::required_alignment - 1u)) == 0u);
    }

    BOOST_FORCEINLINE value_type operator= (value_arg_type v) BOOST_NOEXCEPT
    {
        this->store(v);
        return v;
    }

    BOOST_FORCEINLINE operator value_type() const BOOST_NOEXCEPT
    {
        return this->load();
    }

    BOOST_FORCEINLINE bool is_lock_free() const BOOST_NOEXCEPT
    {
        // C++20 specifies that is_lock_free returns true if operations on *all* objects of the atomic_ref<T> type are lock-free.
        // This does not allow to return true or false depending on the referenced object runtime alignment. Currently, Boost.Atomic
        // follows this specification, although we may support runtime alignment checking in the future.
        return base_type::is_always_lock_free;
    }

    BOOST_FORCEINLINE value_type& value() const BOOST_NOEXCEPT { return *this->m_value; }

    BOOST_DELETED_FUNCTION(atomic_ref& operator= (atomic_ref const&))
};

} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_REF_TEMPLATE_HPP_INCLUDED_

/* atomic_ref_template.hpp
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
*/