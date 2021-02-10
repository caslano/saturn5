/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_ops_emulated.hpp
 *
 * This header contains emulated (lock-based) implementation of the extra floating point atomic operations.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

#include <cstddef>
#include <boost/memory_order.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/bitwise_fp_cast.hpp>
#include <boost/atomic/detail/extra_fp_operations_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

//! Generic implementation of extra floating point operations
template< typename Base, typename Value, std::size_t Size >
struct emulated_extra_fp_operations :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;
    typedef Value value_type;
    typedef typename base_type::scoped_lock scoped_lock;

    static BOOST_FORCEINLINE value_type fetch_negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return old_val;
    }

    static BOOST_FORCEINLINE value_type negate(storage_type volatile& storage, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = -old_val;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE value_type add(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val + v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE value_type sub(storage_type volatile& storage, value_type v, memory_order) BOOST_NOEXCEPT
    {
        storage_type& s = const_cast< storage_type& >(storage);
        scoped_lock lock(&storage);
        value_type old_val = atomics::detail::bitwise_fp_cast< value_type >(s);
        value_type new_val = old_val - v;
        s = atomics::detail::bitwise_fp_cast< storage_type >(new_val);
        return new_val;
    }

    static BOOST_FORCEINLINE void opaque_negate(storage_type volatile& storage, memory_order order) BOOST_NOEXCEPT
    {
        fetch_negate(storage, order);
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

template< typename Base, typename Value, std::size_t Size >
struct extra_fp_operations< Base, Value, Size, false > :
    public emulated_extra_fp_operations< Base, Value, Size >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPS_EMULATED_HPP_INCLUDED_

/* extra_fp_ops_emulated.hpp
C6NZ4o1CPwwdylYlJ4o7AQWDIdlcvpZq6KHQ+L8B+924U2XbFKWkk/r4CpWSyguelRg6YPecuRElAgp8MYW1kmtOnwXXN26Wstl8ej73x4lr0temjj4jS17ZLe965XtEzyMVzyj3l2CkV/A1Ci6SeeB2FiTZUeffbtejmxOyDDEvJRwAzC8n7mN5AEfDv+3b9/DJLm3UCSG1M3/m/Ua2HWy3M5xF89Hwh44n6Qatf78W1B5HnXbWn+8G7/p51/sPUEsDBAoAAAAIAC1nSlLDSX9EcgMAAG4HAAAqAAkAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9NYWtlZmlsZS5leGFtcGxlVVQFAAG2SCRgrVRhb9s2EP08/YpDE6D2IFtdP61FOsx11tSbkRSRhyBAAIGmKIsLTQokFcdAfvweKcmugQ35Uhk2KfLu3ru7dz77+cc9yRm9+hTxW+DBGhy+WfOP4P6/jYvihboPnB6wvgKR0dHjpRjTqx4vNIoeRY9xEfZF8QrMQyAWfrLg+FCELU6SM/jNTbO3clN7Gs3H9MuHD7/ShN6/e/8upUumpVCUe6HXwm5Suijjye81e36eOvFbSsITU9MYaFVLR85UfsesIOyV5EI7URJzVArHrVzjRWrytaBKKkHz
*/