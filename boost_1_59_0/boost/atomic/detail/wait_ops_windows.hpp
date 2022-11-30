/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/wait_ops_windows.hpp
 *
 * This header contains implementation of the waiting/notifying atomic operations on Windows.
 */

#ifndef BOOST_ATOMIC_DETAIL_WAIT_OPS_WINDOWS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_WAIT_OPS_WINDOWS_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>
#include <boost/memory_order.hpp>
#include <boost/winapi/wait_constants.hpp>
#include <boost/atomic/detail/wait_operations_fwd.hpp>
#include <boost/atomic/detail/wait_capabilities.hpp>
#if defined(BOOST_ATOMIC_DETAIL_WINDOWS_HAS_WAIT_ON_ADDRESS)
#include <boost/winapi/wait_on_address.hpp>
#if (defined(BOOST_ATOMIC_FORCE_AUTO_LINK) || (!defined(BOOST_ALL_NO_LIB) && !defined(BOOST_ATOMIC_NO_LIB))) && !defined(BOOST_ATOMIC_NO_SYNCHRONIZATION_LIB)
#define BOOST_LIB_NAME "synchronization"
#if defined(BOOST_AUTO_LINK_NOMANGLE)
#include <boost/config/auto_link.hpp>
#else // defined(BOOST_AUTO_LINK_NOMANGLE)
#define BOOST_AUTO_LINK_NOMANGLE
#include <boost/config/auto_link.hpp>
#undef BOOST_AUTO_LINK_NOMANGLE
#endif // defined(BOOST_AUTO_LINK_NOMANGLE)
#endif // (defined(BOOST_ATOMIC_FORCE_AUTO_LINK) || (!defined(BOOST_ALL_NO_LIB) && !defined(BOOST_ATOMIC_NO_LIB))) && !defined(BOOST_ATOMIC_NO_SYNCHRONIZATION_LIB)
#else // defined(BOOST_ATOMIC_DETAIL_WINDOWS_HAS_WAIT_ON_ADDRESS)
#include <cstddef>
#include <boost/atomic/detail/wait_on_address.hpp>
#include <boost/atomic/detail/wait_ops_generic.hpp>
#endif // defined(BOOST_ATOMIC_DETAIL_WINDOWS_HAS_WAIT_ON_ADDRESS)
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {
namespace detail {

#if defined(BOOST_ATOMIC_DETAIL_WINDOWS_HAS_WAIT_ON_ADDRESS)

template< typename Base, std::size_t Size >
struct wait_operations_windows :
    public Base
{
    typedef Base base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = true;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        return true;
    }

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        storage_type new_val = base_type::load(storage, order);
        while (new_val == old_val)
        {
            boost::winapi::WaitOnAddress(const_cast< storage_type* >(&storage), &old_val, Size, boost::winapi::infinite);
            new_val = base_type::load(storage, order);
        }

        return new_val;
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        boost::winapi::WakeByAddressSingle(const_cast< storage_type* >(&storage));
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        boost::winapi::WakeByAddressAll(const_cast< storage_type* >(&storage));
    }
};

#else // defined(BOOST_ATOMIC_DETAIL_WINDOWS_HAS_WAIT_ON_ADDRESS)

template< typename Base, std::size_t Size >
struct wait_operations_windows :
    public atomics::detail::wait_operations_generic< Base, false >
{
    typedef atomics::detail::wait_operations_generic< Base, false > base_type;
    typedef typename base_type::storage_type storage_type;

    static BOOST_CONSTEXPR_OR_CONST bool always_has_native_wait_notify = false;

    static BOOST_FORCEINLINE bool has_native_wait_notify(storage_type const volatile&) BOOST_NOEXCEPT
    {
        ensure_wait_functions_initialized();
        return atomics::detail::wait_on_address != NULL;
    }

    static BOOST_FORCEINLINE storage_type wait(storage_type const volatile& storage, storage_type old_val, memory_order order) BOOST_NOEXCEPT
    {
        ensure_wait_functions_initialized();

        if (BOOST_LIKELY(atomics::detail::wait_on_address != NULL))
        {
            storage_type new_val = base_type::load(storage, order);
            while (new_val == old_val)
            {
                atomics::detail::wait_on_address(const_cast< storage_type* >(&storage), &old_val, Size, boost::winapi::infinite);
                new_val = base_type::load(storage, order);
            }

            return new_val;
        }
        else
        {
            return base_type::wait(storage, old_val, order);
        }
    }

    static BOOST_FORCEINLINE void notify_one(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        ensure_wait_functions_initialized();

        if (BOOST_LIKELY(atomics::detail::wake_by_address_single != NULL))
            atomics::detail::wake_by_address_single(const_cast< storage_type* >(&storage));
        else
            base_type::notify_one(storage);
    }

    static BOOST_FORCEINLINE void notify_all(storage_type volatile& storage) BOOST_NOEXCEPT
    {
        ensure_wait_functions_initialized();

        if (BOOST_LIKELY(atomics::detail::wake_by_address_all != NULL))
            atomics::detail::wake_by_address_all(const_cast< storage_type* >(&storage));
        else
            base_type::notify_all(storage);
    }
};

#endif // defined(BOOST_ATOMIC_DETAIL_WINDOWS_HAS_WAIT_ON_ADDRESS)

template< typename Base >
struct wait_operations< Base, 1u, true, false > :
    public wait_operations_windows< Base, 1u >
{
};

template< typename Base >
struct wait_operations< Base, 2u, true, false > :
    public wait_operations_windows< Base, 2u >
{
};

template< typename Base >
struct wait_operations< Base, 4u, true, false > :
    public wait_operations_windows< Base, 4u >
{
};

template< typename Base >
struct wait_operations< Base, 8u, true, false > :
    public wait_operations_windows< Base, 8u >
{
};

} // namespace detail
} // namespace atomics
} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_DETAIL_WAIT_OPS_WINDOWS_HPP_INCLUDED_

/* wait_ops_windows.hpp
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
*/