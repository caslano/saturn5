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
 * \file   atomic/detail/atomic_template.hpp
 *
 * This header contains interface definition of \c atomic template.
 */

#ifndef BOOST_ATOMIC_DETAIL_ATOMIC_TEMPLATE_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ATOMIC_TEMPLATE_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/intptr.hpp>
#include <boost/atomic/detail/classify.hpp>
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
#if defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
#include <boost/type_traits/type_with_alignment.hpp>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// 'boost::atomics::atomic<T>' : multiple assignment operators specified
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
class base_atomic_common
{
public:
    typedef T value_type;

protected:
    typedef atomics::detail::operations< storage_size_of< value_type >::value, IsSigned > operations;
    typedef typename atomics::detail::conditional< sizeof(value_type) <= sizeof(void*), value_type, value_type const& >::type value_arg_type;
    typedef typename operations::storage_type storage_type;

protected:
    static BOOST_CONSTEXPR_OR_CONST std::size_t storage_alignment = atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment ? operations::storage_alignment : atomics::detail::alignment_of< value_type >::value;

protected:
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_ALIGNAS)
    alignas(storage_alignment) storage_type m_storage;
#else
    // Note: Some compilers cannot use constant expressions in alignment attributes, so we have to use the union trick
    union
    {
        storage_type m_storage;
        typename boost::type_with_alignment< storage_alignment >::type m_aligner;
    };
#endif

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_common() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
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
};


template< typename T, bool IsTriviallyDefaultConstructible = atomics::detail::is_trivially_default_constructible< T >::value >
class base_atomic_generic;

template< typename T >
class base_atomic_generic< T, true > :
    public base_atomic_common< T, false >
{
private:
    typedef base_atomic_common< T, false > base_type;

protected:
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic_generic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE explicit base_atomic_generic(value_arg_type v) BOOST_NOEXCEPT : base_type(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }
};

template< typename T >
class base_atomic_generic< T, false > :
    public base_atomic_common< T, false >
{
private:
    typedef base_atomic_common< T, false > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    BOOST_FORCEINLINE explicit base_atomic_generic(value_arg_type v = value_type()) BOOST_NOEXCEPT : base_type(atomics::detail::bitwise_cast< storage_type >(v))
    {
    }
};


template< typename T, typename Kind >
class base_atomic;

//! General template. Implementation for user-defined types, such as structs and enums, and pointers to non-object types
template< typename T >
class base_atomic< T, void > :
    public base_atomic_generic< T >
{
private:
    typedef base_atomic_generic< T > base_type;

public:
    typedef typename base_type::value_type value_type;

protected:
    typedef typename base_type::operations operations;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::value_arg_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(v)
    {
    }

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(operations::exchange(this->storage(), atomics::detail::bitwise_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(old_value);
        return res;
    }
};


//! Implementation for integers
template< typename T >
class base_atomic< T, int > :
    public base_atomic_common< T, atomics::detail::is_signed< T >::value >
{
private:
    typedef base_atomic_common< T, atomics::detail::is_signed< T >::value > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef value_type difference_type;

protected:
    typedef typename base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(static_cast< storage_type >(v)) {}

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::integral_truncate< value_type >(operations::load(this->storage(), order));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_add(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_sub(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::exchange(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_FORCEINLINE value_type fetch_and(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_and(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_or(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_or(this->storage(), static_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE value_type fetch_xor(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::integral_truncate< value_type >(operations::fetch_xor(this->storage(), static_cast< storage_type >(v), order));
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

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::integral_truncate< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::integral_truncate< value_type >(old_value);
        return res;
    }
};

//! Implementation for bool
template< >
class base_atomic< bool, int > :
    public base_atomic_common< bool, false >
{
private:
    typedef base_atomic_common< bool, false > base_type;

public:
    typedef base_type::value_type value_type;

protected:
    typedef base_type::operations operations;
    typedef base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(static_cast< storage_type >(v)) {}

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return !!operations::load(this->storage(), order);
    }

    BOOST_FORCEINLINE value_type exchange(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return !!operations::exchange(this->storage(), static_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
    }

    BOOST_FORCEINLINE bool compare_exchange_weak(value_type& expected, value_arg_type desired, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return compare_exchange_weak(expected, desired, order, atomics::detail::deduce_failure_order(order));
    }

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = static_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, static_cast< storage_type >(desired), success_order, failure_order);
        expected = !!old_value;
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), static_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
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
class base_atomic< T, float > :
    public base_atomic_common< T, false >
{
private:
    typedef base_atomic_common< T, false > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef value_type difference_type;

protected:
    typedef typename base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef atomics::detail::fp_operations< extra_operations, value_type, operations::storage_size > fp_operations;
    typedef atomics::detail::extra_fp_operations< fp_operations, value_type, operations::storage_size > extra_fp_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool,
        atomics::detail::value_sizeof< value_type >::value != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment
    > use_bitwise_cast;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(atomics::detail::bitwise_fp_cast< storage_type >(v)) {}

    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_fp_cast< value_type >(operations::load(this->storage(), order));
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
        return atomics::detail::bitwise_fp_cast< value_type >(operations::exchange(this->storage(), atomics::detail::bitwise_fp_cast< storage_type >(v), order));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_fp_cast< storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_fp_cast< value_type >(old_value);
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_fp_cast< storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
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
class base_atomic< T*, void* > :
    public base_atomic_common< T*, false >
{
private:
    typedef base_atomic_common< T*, false > base_type;

public:
    typedef typename base_type::value_type value_type;
    typedef std::ptrdiff_t difference_type;

protected:
    typedef typename base_type::operations operations;
    typedef atomics::detail::extra_operations< operations, operations::storage_size, operations::is_signed > extra_operations;
    typedef typename base_type::storage_type storage_type;
    typedef value_type value_arg_type;

private:
    typedef atomics::detail::integral_constant< bool, sizeof(value_type) != sizeof(storage_type) || atomics::detail::alignment_of< value_type >::value <= operations::storage_alignment > use_bitwise_cast;

    // uintptr_storage_type is the minimal storage type that is enough to store pointers. The actual storage_type theoretically may be larger,
    // if the target architecture only supports atomic ops on larger data. Typically, though, they are the same type.
    typedef atomics::detail::uintptr_t uintptr_storage_type;

public:
    BOOST_DEFAULTED_FUNCTION(base_atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE explicit base_atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(atomics::detail::bitwise_cast< uintptr_storage_type >(v))
    {
    }

    // Standard methods
    BOOST_FORCEINLINE void store(value_arg_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_consume);
        BOOST_ASSERT(order != memory_order_acquire);
        BOOST_ASSERT(order != memory_order_acq_rel);

        operations::store(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(v), order);
    }

    BOOST_FORCEINLINE value_type load(memory_order order = memory_order_seq_cst) const volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(order != memory_order_release);
        BOOST_ASSERT(order != memory_order_acq_rel);

        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::load(this->storage(), order)));
    }

    BOOST_FORCEINLINE value_type fetch_add(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::fetch_add(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type fetch_sub(difference_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::fetch_sub(this->storage(), static_cast< uintptr_storage_type >(v * sizeof(T)), order)));
    }

    BOOST_FORCEINLINE value_type exchange(value_type v, memory_order order = memory_order_seq_cst) volatile BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(operations::exchange(this->storage(), atomics::detail::bitwise_cast< uintptr_storage_type >(v), order)));
    }

    BOOST_FORCEINLINE bool compare_exchange_strong(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order) volatile BOOST_NOEXCEPT
    {
        BOOST_ASSERT(failure_order != memory_order_release);
        BOOST_ASSERT(failure_order != memory_order_acq_rel);
        BOOST_ASSERT(cas_failure_order_must_not_be_stronger_than_success_order(success_order, failure_order));

        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, use_bitwise_cast());
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

    BOOST_DELETED_FUNCTION(base_atomic(base_atomic const&))
    BOOST_DELETED_FUNCTION(base_atomic& operator=(base_atomic const&))

private:
    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_strong(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_strong_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_strong_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< uintptr_storage_type >(expected);
        const bool res = operations::compare_exchange_strong(this->storage(), old_value, atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(old_value));
        return res;
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::false_type) volatile BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_DETAIL_STORAGE_TYPE_MAY_ALIAS)
        return operations::compare_exchange_weak(this->storage(), reinterpret_cast< storage_type& >(expected), atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
#else
        return compare_exchange_weak_impl(expected, desired, success_order, failure_order, atomics::detail::true_type());
#endif
    }

    BOOST_FORCEINLINE bool compare_exchange_weak_impl(value_type& expected, value_arg_type desired, memory_order success_order, memory_order failure_order, atomics::detail::true_type) volatile BOOST_NOEXCEPT
    {
        storage_type old_value = atomics::detail::bitwise_cast< uintptr_storage_type >(expected);
        const bool res = operations::compare_exchange_weak(this->storage(), old_value, atomics::detail::bitwise_cast< uintptr_storage_type >(desired), success_order, failure_order);
        expected = atomics::detail::bitwise_cast< value_type >(static_cast< uintptr_storage_type >(old_value));
        return res;
    }
};

} // namespace detail

template< typename T >
class atomic :
    public atomics::detail::base_atomic< T, typename atomics::detail::classify< T >::type >
{
private:
    typedef atomics::detail::base_atomic< T, typename atomics::detail::classify< T >::type > base_type;
    typedef typename base_type::value_arg_type value_arg_type;

public:
    typedef typename base_type::value_type value_type;
    // Deprecated, use value_type instead
    BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED
    typedef typename base_type::storage_type storage_type;

    BOOST_STATIC_ASSERT_MSG(sizeof(value_type) > 0u, "boost::atomic<T> requires T to be a complete type");
#if !defined(BOOST_ATOMIC_DETAIL_NO_CXX11_IS_TRIVIALLY_COPYABLE)
    BOOST_STATIC_ASSERT_MSG(atomics::detail::is_trivially_copyable< value_type >::value, "boost::atomic<T> requires T to be a trivially copyable type");
#endif

public:
    static BOOST_CONSTEXPR_OR_CONST bool is_always_lock_free = base_type::operations::is_always_lock_free;

public:
    BOOST_DEFAULTED_FUNCTION(atomic() BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_DECL, BOOST_ATOMIC_DETAIL_DEF_NOEXCEPT_IMPL {})
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(v) {}

    BOOST_FORCEINLINE value_type operator= (value_arg_type v) BOOST_NOEXCEPT
    {
        this->store(v);
        return v;
    }

    BOOST_FORCEINLINE value_type operator= (value_arg_type v) volatile BOOST_NOEXCEPT
    {
        this->store(v);
        return v;
    }

    BOOST_FORCEINLINE operator value_type() const volatile BOOST_NOEXCEPT
    {
        return this->load();
    }

    BOOST_FORCEINLINE bool is_lock_free() const volatile BOOST_NOEXCEPT
    {
        // C++17 requires all instances of atomic<> return a value consistent with is_always_lock_free here
        return is_always_lock_free;
    }

    // Deprecated, use value() instead
    BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED
    BOOST_FORCEINLINE typename base_type::storage_type& storage() BOOST_NOEXCEPT { return base_type::storage(); }
    BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED
    BOOST_FORCEINLINE typename base_type::storage_type volatile& storage() volatile BOOST_NOEXCEPT { return base_type::storage(); }
    BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED
    BOOST_FORCEINLINE typename base_type::storage_type const& storage() const BOOST_NOEXCEPT { return base_type::storage(); }
    BOOST_ATOMIC_DETAIL_STORAGE_DEPRECATED
    BOOST_FORCEINLINE typename base_type::storage_type const volatile& storage() const volatile BOOST_NOEXCEPT { return base_type::storage(); }

    BOOST_DELETED_FUNCTION(atomic(atomic const&))
    BOOST_DELETED_FUNCTION(atomic& operator= (atomic const&))
    BOOST_DELETED_FUNCTION(atomic& operator= (atomic const&) volatile)
};

#if defined(BOOST_NO_CXX17_INLINE_VARIABLES)
template< typename T >
BOOST_CONSTEXPR_OR_CONST bool atomic< T >::is_always_lock_free;
#endif

typedef atomic< char > atomic_char;
typedef atomic< unsigned char > atomic_uchar;
typedef atomic< signed char > atomic_schar;
typedef atomic< uint8_t > atomic_uint8_t;
typedef atomic< int8_t > atomic_int8_t;
typedef atomic< unsigned short > atomic_ushort;
typedef atomic< short > atomic_short;
typedef atomic< uint16_t > atomic_uint16_t;
typedef atomic< int16_t > atomic_int16_t;
typedef atomic< unsigned int > atomic_uint;
typedef atomic< int > atomic_int;
typedef atomic< uint32_t > atomic_uint32_t;
typedef atomic< int32_t > atomic_int32_t;
typedef atomic< unsigned long > atomic_ulong;
typedef atomic< long > atomic_long;
typedef atomic< uint64_t > atomic_uint64_t;
typedef atomic< int64_t > atomic_int64_t;
#ifdef BOOST_HAS_LONG_LONG
typedef atomic< boost::ulong_long_type > atomic_ullong;
typedef atomic< boost::long_long_type > atomic_llong;
#endif
typedef atomic< void* > atomic_address;
typedef atomic< bool > atomic_bool;
typedef atomic< wchar_t > atomic_wchar_t;
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811
typedef atomic< char8_t > atomic_char8_t;
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T)
typedef atomic< char16_t > atomic_char16_t;
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
typedef atomic< char32_t > atomic_char32_t;
#endif

typedef atomic< int_least8_t > atomic_int_least8_t;
typedef atomic< uint_least8_t > atomic_uint_least8_t;
typedef atomic< int_least16_t > atomic_int_least16_t;
typedef atomic< uint_least16_t > atomic_uint_least16_t;
typedef atomic< int_least32_t > atomic_int_least32_t;
typedef atomic< uint_least32_t > atomic_uint_least32_t;
typedef atomic< int_least64_t > atomic_int_least64_t;
typedef atomic< uint_least64_t > atomic_uint_least64_t;
typedef atomic< int_fast8_t > atomic_int_fast8_t;
typedef atomic< uint_fast8_t > atomic_uint_fast8_t;
typedef atomic< int_fast16_t > atomic_int_fast16_t;
typedef atomic< uint_fast16_t > atomic_uint_fast16_t;
typedef atomic< int_fast32_t > atomic_int_fast32_t;
typedef atomic< uint_fast32_t > atomic_uint_fast32_t;
typedef atomic< int_fast64_t > atomic_int_fast64_t;
typedef atomic< uint_fast64_t > atomic_uint_fast64_t;
typedef atomic< intmax_t > atomic_intmax_t;
typedef atomic< uintmax_t > atomic_uintmax_t;

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
typedef atomic< float > atomic_float_t;
typedef atomic< double > atomic_double_t;
typedef atomic< long double > atomic_long_double_t;
#endif

typedef atomic< std::size_t > atomic_size_t;
typedef atomic< std::ptrdiff_t > atomic_ptrdiff_t;

#if defined(BOOST_HAS_INTPTR_T)
typedef atomic< boost::intptr_t > atomic_intptr_t;
typedef atomic< boost::uintptr_t > atomic_uintptr_t;
#endif

} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_ATOMIC_TEMPLATE_HPP_INCLUDED_

/* atomic_template.hpp
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
*/