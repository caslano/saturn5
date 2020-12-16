/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_ops_generic.hpp
 *
 * This header contains generic implementation of the extra floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_GENERIC_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_GENERIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_fp_operations_fwd.hpp>
#include <boost/atomic/detail/type_traits/is_iec559.hpp>
#include <boost/atomic/detail/type_traits/is_integral.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_GCC) && (BOOST_GCC+0) >= 60000
#pragma GCC diagnostic push
// ignoring attributes on template argument X - this warning is because we need to pass storage_type as a template argument; no problem in this case
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Negate implementation
template<
    typename Base,
    typename Value,
    std::size_t Size
#if defined(BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH)
    , bool = atomics::detail::is_iec559< Value >::value && atomics::detail::is_integral< typename Base::storage_type >::value
#endif
>
struct generic_extra_fp_negate :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = -old_val;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return old_val;
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = -old_val;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
    }
};

#if defined(BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH)

//! Negate implementation for IEEE 754 / IEC 559 floating point types. We leverage the fact that the sign bit is the most significant bit in the value.
template< typename Base, typename Value, std::size_t Size >
struct generic_extra_fp_negate< Base, Value, Size, true > :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    //! The mask with only one sign bit set to 1
    static BOOST_CONSTEXPR_OR_CONST storage_type sign_mask = static_cast< storage_type >(1u) << (atomics::detail::value_sizeof< value_type >::value * 8u - 1u);

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(base_type::fetch_xor(storage, sign_mask, order));
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        return atomics::detail::bitwise_fp_cast< value_type >(base_type::bitwise_xor(storage, sign_mask, order));
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        base_type::opaque_xor(storage, sign_mask, order);
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_INT_FP_ENDIAN_MATCH)

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct generic_extra_fp_operations :
    public generic_extra_fp_negate< Base, Value, Size >
{
    typedef generic_extra_fp_negate< Base, Value, Size > base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;

    static BOOST_FORCEINLINE value_type add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = old_val + v;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE value_type sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        storage_type old_storage, new_storage;
        value_type old_val, new_val;
        atomics::detail::non_atomic_load(storage, old_storage);
        do
        {
            old_val = atomics::detail::bitwise_fp_cast< value_type >(old_storage);
            new_val = old_val - v;
            new_storage = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        }
        while (!base_type::compare_exchange_weak(storage, old_storage, new_storage, order, memory_order_relaxed));
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_add(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_add(storage, v, order);
    }

    static BOOST_FORCEINLINE void opaque_sub(storage_type volatile& storage, value_type v, memory_order order) BOOST_NOEXCEPT
    {
        base_type::fetch_sub(storage, v, order);
    }
};

// Default extra_fp_operations template definition will be used unless specialized for a specific platform
template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations< Base, Value, Size, true > :
    public generic_extra_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_GCC) && (BOOST_GCC+0) >= 60000
#pragma GCC diagnostic pop
#endif

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_GENERIC_HPP_INCLUDED_

/* extra_fp_ops_generic.hpp
b4V+ZxHt+X7kPKLEihpZFc+gP4wagH4iqhS11r6HOojKPYnwo8LyLNpV1si0uIzrbnAkeuc5RttPgphdgn4XPILaj9km9DF5PLcKeRIoPeNIZGLsg3lV2IVzofu8o5WYXeZ17hHm29DvRoXPQDpShR4mLsY96guu82zm4TdsNxyVg32uh3I9A7WT60Oo8HlJaUs4+wcVPjdpxpLI2UnruL5sOO5Rv0S/C7rPUtqJnQOog7b5uRGZHTnn4gbuQB3Uc5bmY5bQl/s2RyCjA3ZDvw16nb10APPtsNeIyBlMeVwXoRxnMRlZIL2WEnbUatRQ9Osw34S6E/0s9PthFdyB2RGuD8JuyyJnNg0YWf+5TWFZIrNwtwuzbqMiZziVw3Wo+1Ap6JdjpzN0yxtZjrpM5Y7sWBaRPbKf67TzsI/qhX4G9DrraSnmpZhfhqpGPYPyOv/JGkP4sbuW622wHfoDMBcm/ICwoeaqTJOxXG+EpdAt36QasyNc74B70B+Eicsx4zoHOs+QGos+D5bDlLGkBwyfKbWV66GY7YFzYJWeMZVwfkRmylr0I9HPHYPsSNR61H2o3ajDqLSxsdYA1AxUFWojagfqMKrdOFYCoeajVqN+idqG2jPuOzks3/2++333++73//r7t+3/t7f/fwvy/+z9/1OzGZvrGvOhwciapva6pinD3v+fWrPGfNSkgnMrSqqKC1ggGxHiV1y40GM9tH6HU7fdzb6LwaLv67l2Z4Kx39WsYR4o+sGee5Ancb+/3B8u+nzjvpPnvooU9Dly/3jRlxj7mWZ95LN8fzwuueFrVtzr8cZ6rGPJd+6pNfvC/Pd05+hc2UA9gzEb1cE+V6LmPUyfNG7SqALSXSUpOtKGFxNJe7XfxqTV7aJPq7HfWuzPK1tUZdbU3ir3UyPnTKjemTYDjuI8xZo4EybHd1Kei5k817EvlV+symxXGe7LNO/tc8ZZcp9Gmp9PvNVNZ7MuO6a1rT/HnedMvJPk/iSNd9h9X8+9avnmfh9dG425uD/TM8+1Rt9I7heKvsS4zyZNxD6/eVXLyosLWDFn9ianiZsJ2JH1K/wWFhWW4qljP1oXsTORdAyaNXysqZX3NErfU14972mux3ua75GHyz32fC2tY5/xSj2/brbWJSP1fW6UMK8s6aeZV+oSrUV86hDcRNchT4m+i18dgv3oOuRJ0ff2rUN+K/ePN+8X93XWIdsc4SlR++46pPd/qA45jH7jf+G6A+91BH7fyf3WF/h9J//21hH4fSd/X9YX7Dhn62eZcYHbf3Xd9J1vDHvmTr/1BUe/XsB7XYDf9/+jX8dxtOsFjnZdgPf6Dv/1IHpOCu1vZG4633WufRv9FpYO82E7aM6pV3cD1Z3znPjjZBsA/sNs2BeizJwufmkdTHuj7hvBkeq+g7rrCHNhFhwGO8ExsAscB7vDZbAX1PhoXUC95xGflhqfFDgSpsKJoQbOkbrmR51zo51R0eese82D+s6B6rxnw89d1zlO91ymcx7TPYfJ/KVz3tI5X+l3LrvnHKXOT7rOaLdVnpmL1HlIv/Pa659vPAh1jrHW/GJCX9QIv7Pcj24u0Tl/OKufmTdkzvDY5gvrniusf55Q5wh9zn9v+HzgWqiyjM3c30ZfmcYQ5Zzfy0OljDVzesznOefyoufxOo/nzHhUOWrt+O/m4L77/ed+/7bxf2nJmd/W2f/DzPhf1g7Jr5nGJwEV6MefoGOP+bRRI8bly16FGjFBDErCY7Fq6YtXlDjW4arbZnL/ZFmnTnTNGntzv95zvMNnGVZLv5hnOM4yxF/MxN+oMUhnHUe3UllHTeDz9h4Rn/hUFldF4sGYoiQSD3XTxow=
*/