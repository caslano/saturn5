/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the extra atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_MSVC)
#pragma warning(push)
// unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable: 4146)
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of extra operations
template< typename Base, std::size_t Size, bool Signed >
struct emulated_extra_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = static_cast< storage_type >(-old_val);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = static_cast< storage_type >(-s);
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val += v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val -= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val &= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val |= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = s;
        new_val ^= v;
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type old_val = s;
        s = static_cast< storage_type >(~old_val);
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        storage_type new_val = static_cast< storage_type >(~s);
        s = new_val;
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        Base::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!add(storage, v, order);
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!sub(storage, v, order);
    }

    static BOOST_FORCEINLINE bool negate_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!negate(storage, order);
    }

    static BOOST_FORCEINLINE bool and_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_and(storage, v, order);
    }

    static BOOST_FORCEINLINE bool or_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_or(storage, v, order);
    }

    static BOOST_FORCEINLINE bool xor_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE bool complement_and_test(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return !!bitwise_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = Base::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = Base::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        storage_type mask = static_cast< storage_type >(static_cast< storage_type >(1u) << bit_number);
        storage_type old_val = Base::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, Size, Signed, false > :
    public emulated_extra_operations< Base, Size, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_EMULATED_HPP_INCLUDED_

/* extra_ops_emulated.hpp
lKGv8oJJLcEc4vV5uk6rBW2r2PVxXeQbO6JL2G4jFwepYzJMV9XRyjUM2riHx24gUb4X+a36K4+RiNOhxq4/TotwFAveBV1KuKlc7qyiOg7S/ihPudI9TTcu82Pg03OCRhmRXt6Y4i8OTW2Am7OEphP/WTHY/vWX7hjCxMNkqEfQXKnmy4dnUJip+XHM4AZfHa3xITPZJB6JkW840jqX+oC0lnNerIhAmDHan98+HAUAifTG5kJyRjPd0GyUVmy68M1ZuKW34CNfmkBVXwCTeV9MRgkN1n0NHruY8exPde+UP3ZGTpu/ea3fcLFD7kOfTqL8+pGvpshnX9Kj3CmtAWlVvdWqfpO9eM05y2EXQ4VB6zCRnsNUaQhzGSmUxNPQ8fr9d5mwci05U2WNWpeee6oc+dMmrEYT1hzp04aw9SccVSLg/pS00sD2XOSGBm5bjtO7+XtPKEw41T8yKAybAg9hZZUSjhgpM0LzcJpoAqUN0Xmd9pg89SO8UgUSBG458uCMCA2BgfRbrEzMfOjsmMP14Y1PX03Pcxn5BUsPNbGrDRfXoR01/0AleJaVFXpMtfpRICfUpmYdHXj/HYIYU3dTQuFKdwplq7EnFyQAg9zonkfr2R7tplDnzohYv+YHq5sDDwPNANWT/b1RwpSqj5V4g9DnY3rRZ8JhR0M0+mQX1JKqYXm3E7IaEHrUO0YtuROrK3HHcEQlJb5L
*/