/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2015 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_generic.hpp
 *
 * This header contains generic implementation of the extra atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/integral_conversions.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/capabilities.hpp>

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
template< typename Base, std::size_t Size, bool Signed, bool = Base::full_cas_based >
struct generic_extra_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< Size >::type emulated_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!base_type::compare_exchange_weak(storage, old_val, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val)), order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_add(storage, v, order) + v;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_sub(storage, v, order) - v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_and(storage, v, order) & v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_or(storage, v, order) | v;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_xor(storage, v, order) ^ v;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_xor(storage, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u))), order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u)));
        return base_type::fetch_xor(storage, mask, order) ^ mask;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(add(storage, v, order));
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(sub(storage, v, order));
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
        return !!static_cast< emulated_storage_type >(bitwise_complement(storage, order));
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

//! Specialization for cases when the platform only natively supports CAS
template< typename Base, std::size_t Size, bool Signed >
struct generic_extra_operations< Base, Size, Signed, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef typename storage_traits< Size >::type emulated_storage_type;

    static BOOST_FORCEINLINE storage_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val;
        atomics::detail::non_atomic_load(storage, old_val);
        while (!base_type::compare_exchange_weak(storage, old_val, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val)), order, memory_order_relaxed)) {}
        return old_val;
    }

    static BOOST_FORCEINLINE storage_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(-old_val));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val + v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val - v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val & v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val | v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type bitwise_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_val);
        do
        {
            new_val = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(old_val ^ v));
        }
        while (!base_type::compare_exchange_weak(storage, old_val, new_val, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE storage_type fetch_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return base_type::fetch_xor(storage, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u))), order);
    }

    static BOOST_FORCEINLINE storage_type bitwise_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return bitwise_xor(storage, atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(~static_cast< emulated_storage_type >(0u))), order);
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }

    static BOOST_FORCEINLINE void opaque_and(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_and(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_or(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_or(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_xor(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_xor(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_complement(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_complement(storage, order);
    }

    static BOOST_FORCEINLINE bool add_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(add(storage, v, order));
    }

    static BOOST_FORCEINLINE bool sub_and_test(storage_type volatile& storage, storage_type v, memory_order order) BOOST_NOEXCEPT
    {
        return !!static_cast< emulated_storage_type >(sub(storage, v, order));
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
        return !!static_cast< emulated_storage_type >(bitwise_complement(storage, order));
    }

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_or(storage, mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_and(storage, ~mask, order);
        return !!(old_val & mask);
    }

    static BOOST_FORCEINLINE bool bit_test_and_complement(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
        const storage_type mask = atomics::detail::integral_extend< Signed, storage_type >(static_cast< emulated_storage_type >(static_cast< emulated_storage_type >(1u) << bit_number));
        storage_type old_val = base_type::fetch_xor(storage, mask, order);
        return !!(old_val & mask);
    }
};

// Default extra_operations template definition will be used unless specialized for a specific platform
template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, Size, Signed, true > :
    public generic_extra_operations< Base, Size, Signed >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_GENERIC_HPP_INCLUDED_

/* extra_ops_generic.hpp
Y/jvzwvhddoIDpBf0xB1svKQ/V3wsCMvmLMndDDtf162ujvB7zxlvd/XjC0/EP1cM7bc8w9x71mX5xv3fcw3mvdF/0owOxDrecbFVOOmpznP4G+i3xfsFmhk8qXlGjMd9zF2kLCREJhg5vWel7DtDoxA4oDre6OR2x36xLZzP/2aZewP78SsGuHStUWHxH1X9/y3aa8PS7heCL7O/OwJgTU8w/ncEZ79qNPkeWcwfs7RNiT8nHj3vLKJ2wni5nzkKHdTM3XDrHR34ub6hmfOVvmJ2BnGN752Qf2u5z5LzuTzEfKM1rhF7/A/3ro7YOb/8F/lxhpZ9VPF3nnBS8mhug7Q5IlkZ7j0G2L4rJOvJO3+GEwPBC2P73Lmm8Eqea8plq4hrPVdzjnnmW7Sb2FxZWXh2cXOsaLGc4H4d5zGU98Vkp3SmaNxfVcUf/PQudb6m3e5R/wayruMl3ptLvVCZj+tj+JXLXX3R5egb4c+Rb99qXKN/5RtiLt+a0tFz3c1+W7WOzuy3qIL6jndGzAnvD9Az/ZbnyRmZgy56Si+o/Huo7+jeYwlD3j0lQ959G2ORJ250pDvbXV/Vwv7m+fai+CcSygaYMmvG6qZ7mX4h90nPRKpIyUfM+hSae9+39bUTRLPNGW5coo4ieTRTWKnsW/f+1a5H2u5+93dGtBXdKaxU9biVjGhz42HHeHHqGfsPkFNHKN3VWgebt+mlhxEtd/ZrIc4LPp3/freav84M9//tej/XNdeAXXTW/Rl6L8U/at+ewfUfraZC/1E9G85+uh21CJluven+g1C68szRZ9p1iH2F/1PGDHkmPozScweZrR5O/UG9ozZdsyasjquC6PhAs/+TLrYu40xT45+s3T6N8R2J/XBfPJhzkDGRnIGzMprap0To3ZmYGeMnNM2oNY5belqZ9NArVdixyeEenh/2xD5oOYdR9qBz+z0Iz4t+Cdr0dTPnQPD/Zjp9lK02mNstXd4oPaZmq38i6PPJHbCc1iDdS3AEHiCKL1uQD/IrnMe/1TrnEVFVir6aapHWKhm5Ei5Jx9Hydcc67E/JN9nf8is2vtDzHj+wODIWSY94Ge2mT0H9pmUqaKyAtmGF93N9h/HqrtcU7bmo5d8rO1iQPe1aV9L7R9v+lrFon/Tq330bQ8L9V4etN/zI9QTeXa9K21Sj4TM5paMm9flMh4brPPDMX2YH+7lMz/sP3Y+Q8J3wHfsfMFndc8fV+l9Ox/ZKiwvv7l+A6C9EyaiT9N8tLaedmyltmP2u97o0R5tirQ9pH3dbU+ee02Hqw5OPMGS3wCd++iB+oj8svFzyS+u2VL/dHxA7LfRfBN2n+pXB+v9tr7p/rvP656z+LXcb2J5veuGzmGY8Yn/HIaR1zt2qCW/mTp+nYh63l7nUpNONYVq3sLygooS99mCJo3ivpC1EyaNcBs13zlU7sd67qmZYOy3MWWxsdgf5ruWN1PuJ6o+7H9TnzXBDU839xnWua41pM5+zOoTLfndrW38z+ErpNvcLxzpVlQsW4RJO3Mu1/Ka+MuiUk0vdZNt1ghdLPof1vTt49S+o+89wbjpbNrh1aK/JOD1jiZz/wq5X6Jn/ap7+gpeZwNPNfcHy/1Ojn1JWrd5vpsUuE7cLQi49uiad7tB7n8/4FqXburVn8r9ysBA3mUC5jekUaZQN2l9czMsgHpt1koPt8uIvuu8etqz5740fWjzrXF5zXsmMI4zBePUzLHPttwjnyz1OKcwx+zTFedReWe7BnApgWgHi+C79neHrxx5h+1T7LPTrON7jru66WDe8w2in2LSN6BrVzTfqP3eJq/dJfoxOo5U+xrfcN66SezMkLwz3/iR5c4=
*/