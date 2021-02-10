/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/fp_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of floating point operations
template< typename Base, typename Value, std::size_t Size >
struct emulated_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE value_type fetch_add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static BOOST_FORCEINLINE value_type fetch_sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }
};

template< typename Base, typename Value, std::size_t Size >
struct fp_operations< Base, Value, Size, false > :
    public emulated_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_FP_OPS_EMULATED_HPP_INCLUDED_

/* fp_ops_emulated.hpp
5daK4lwVe2b5U8563SuWWLCtJbB3JQmUSMjmUXN4ro8YsOV3FhR5kE+ygEcbbFUFt58hQ/hyS5GDEkTn/GJEMipt3WgJBNSEVQiwOWxdqKpyNTKaZzq++6wbijFqti4J8u3Rbw0F0HS9h0tdSIZN2TSyFkpWjUlXz/W51NUlD8EG6r9I2MoS/vMCC3biKEign8MeY5kECytxbcvz7mE/Y932EPfT9+wYTXjt2wXaPr9LBAMgxH3qM2A5x+1lBZskG/SNzicw5wKYuXaM9OjRWRcIHq37ZEt0pckFHY09c1HGZVSKKTSVIq9AE62cO3yxjBMgyvhfS8tDcr22fnp9jjs23VQZuoRuU5LtU6V9CoQEpCS1D6U2cRfuVwtbrRNW67/zf0cqDh8vp1NQF55NgQT/Cz3YPlWrAl9VGFTjEdCr9Rt4f/pPEcQR9zgkjcI9+C+DmRZBiHauC7Z3k8ADA6F10ejYUE7oKvIuWISwMUdoHdSkdXMWeNAjAc0rfTTs3+jDS4OiNn2jSuoCPgcCDGgablo3aXYeVOLlGEz5papVDyo5oKpqcpc1lmEYRAny+hE87YonUbDi0TwukGq1gMZiZdvQpaSWomdT25aiD/QhhhK0kNhsXnDoYjDEbWjqwDQQzswHn0ETfeP6
*/