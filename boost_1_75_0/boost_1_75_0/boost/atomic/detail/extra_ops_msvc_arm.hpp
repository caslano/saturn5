/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2017 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_ops_msvc_arm.hpp
 *
 * This header contains implementation of the extra atomic operations for ARM.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/interlocked.hpp>
#include <boost/atomic/detail/storage_traits.hpp>
#include <boost/atomic/detail/extra_operations_fwd.hpp>
#include <boost/atomic/detail/extra_ops_generic.hpp>
#include <boost/atomic/capabilities.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

template< typename Base, std::size_t Size, bool Signed >
struct extra_operations< Base, 4u, Signed, true > :
    public generic_extra_operations< Base, 4u, Signed >
{
    typedef generic_extra_operations< Base, 4u, Signed > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_FORCEINLINE bool bit_test_and_set(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED) && defined(BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE) && defined(BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE)
        bool result;
        switch (order)
        {
        case memory_order_relaxed:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_RELAXED(&storage, bit_number);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_ACQUIRE(&storage, bit_number);
            break;
        case memory_order_release:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS_RELEASE(&storage, bit_number);
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
            break;
        }
        return result;
#else
        return !!BOOST_ATOMIC_INTERLOCKED_BTS(&storage, bit_number);
#endif
    }

    static BOOST_FORCEINLINE bool bit_test_and_reset(storage_type volatile& storage, unsigned int bit_number, memory_order order) BOOST_NOEXCEPT
    {
#if defined(BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED) && defined(BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE) && defined(BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE)
        bool result;
        switch (order)
        {
        case memory_order_relaxed:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_RELAXED(&storage, bit_number);
            break;
        case memory_order_consume:
        case memory_order_acquire:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_ACQUIRE(&storage, bit_number);
            break;
        case memory_order_release:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR_RELEASE(&storage, bit_number);
            break;
        case memory_order_acq_rel:
        case memory_order_seq_cst:
        default:
            result = !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
            break;
        }
        return result;
#else
        return !!BOOST_ATOMIC_INTERLOCKED_BTR(&storage, bit_number);
#endif
    }
};

#endif // defined(BOOST_ATOMIC_INTERLOCKED_BTS) && defined(BOOST_ATOMIC_INTERLOCKED_BTR)

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_OPS_MSVC_ARM_HPP_INCLUDED_

/* extra_ops_msvc_arm.hpp
24XVRfiJkBWEPSC9522I3UCgKfK+HW5J34BqCZUTiOQI40vQluV2V2gJw/GFMGg6ZW2Tq+27f/P4BctH9p5H9v5VWQDSO/GAPOuOwytp+A2COwy/IGPBF59AAGv8V4j6d8PfCHv3D4ow8EHx0DzfoIcEYdeQkKGGByS1sxefjlEhgU3L/bwFLTa9iYEH6h9QtQ4XYwUHC9CJQQU6iA+n54aay8H0/O9nC8G9tGi2861CYmjxtv1e2RuE10+01gYBHZREK8vbiQ0YG1XIETrYAVxFdH3T3vVF1YOAcgLwxY/tT0HYVjRkayFKvMfWU79EKFjRMq7uWk4S1+quBcwVMPquuJlptMBWPFWoG/337HNWkz7UP8C0QUKsJA7lqfaveb0VynymXvVIQvNd156W1QSof6p3qquhhdVG6qwfxsMeKKULrBXDTtn/JiQ6Vwd/o3C4Q3gj/wSYJRN85W01qtwTZcB3cMn2N1BcTJYokrlC+os370dv1UlM6LD2XG04PMwnOrP5qb2GJ0VBy6sP1sypssOhSdlZ8IXqcOGmh7tH68tGt6/ep+HYaljdlVWHu1UvGhhEjNe3I6mQkb51zNTXvOt26ijnZmFXZxajEZv8+6yR85GUo8/Ed9Jz/LkV5HU4DWOHsMPWZ5zD8jsWNxbzt0nxjO0Dg0QvSgXnyV/48TZJLgi30btXPe/yLEi8UM0M4OTNGS1aqdto
*/