/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2011 Helge Bahmann
 * Copyright (c) 2013 Tim Blechmann
 * Copyright (c) 2014, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/atomic.hpp
 *
 * This header contains definition of \c atomic template.
 */

#ifndef BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_
#define BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_

#include <cstddef>
#include <boost/cstdint.hpp>
#include <boost/static_assert.hpp>
#include <boost/memory_order.hpp>
#include <boost/atomic/capabilities.hpp>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/classify.hpp>
#include <boost/atomic/detail/atomic_impl.hpp>
#include <boost/atomic/detail/type_traits/is_trivially_copyable.hpp>
#include <boost/atomic/detail/type_traits/is_nothrow_default_constructible.hpp>
#include <boost/atomic/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
namespace atomics {

//! Atomic object
template< typename T >
class atomic :
    public atomics::detail::base_atomic< T, typename atomics::detail::classify< T >::type, false >
{
private:
    typedef atomics::detail::base_atomic< T, typename atomics::detail::classify< T >::type, false > base_type;
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
    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT atomic() BOOST_NOEXCEPT_IF(atomics::detail::is_nothrow_default_constructible< value_type >::value) : base_type()
    {
    }

    BOOST_FORCEINLINE BOOST_ATOMIC_DETAIL_CONSTEXPR_UNION_INIT atomic(value_arg_type v) BOOST_NOEXCEPT : base_type(v)
    {
    }

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

// Select the lock-free atomic types that has natively supported waiting/notifying operations.
// Prefer 32-bit types the most as those have the best performance on current 32 and 64-bit architectures.
#if BOOST_ATOMIC_INT32_LOCK_FREE == 2 && BOOST_ATOMIC_HAS_NATIVE_INT32_WAIT_NOTIFY == 2
typedef atomic< uint32_t > atomic_unsigned_lock_free;
typedef atomic< int32_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT64_LOCK_FREE == 2 && BOOST_ATOMIC_HAS_NATIVE_INT64_WAIT_NOTIFY == 2
typedef atomic< uint64_t > atomic_unsigned_lock_free;
typedef atomic< int64_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT16_LOCK_FREE == 2 && BOOST_ATOMIC_HAS_NATIVE_INT16_WAIT_NOTIFY == 2
typedef atomic< uint16_t > atomic_unsigned_lock_free;
typedef atomic< int16_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT8_LOCK_FREE == 2 && BOOST_ATOMIC_HAS_NATIVE_INT8_WAIT_NOTIFY == 2
typedef atomic< uint8_t > atomic_unsigned_lock_free;
typedef atomic< int8_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT32_LOCK_FREE == 2
typedef atomic< uint32_t > atomic_unsigned_lock_free;
typedef atomic< int32_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT64_LOCK_FREE == 2
typedef atomic< uint64_t > atomic_unsigned_lock_free;
typedef atomic< int64_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT16_LOCK_FREE == 2
typedef atomic< uint16_t > atomic_unsigned_lock_free;
typedef atomic< int16_t > atomic_signed_lock_free;
#elif BOOST_ATOMIC_INT8_LOCK_FREE == 2
typedef atomic< uint8_t > atomic_unsigned_lock_free;
typedef atomic< int8_t > atomic_signed_lock_free;
#else
#define BOOST_ATOMIC_DETAIL_NO_LOCK_FREE_TYPEDEFS
#endif

} // namespace atomics

using atomics::atomic;

using atomics::atomic_char;
using atomics::atomic_uchar;
using atomics::atomic_schar;
using atomics::atomic_uint8_t;
using atomics::atomic_int8_t;
using atomics::atomic_ushort;
using atomics::atomic_short;
using atomics::atomic_uint16_t;
using atomics::atomic_int16_t;
using atomics::atomic_uint;
using atomics::atomic_int;
using atomics::atomic_uint32_t;
using atomics::atomic_int32_t;
using atomics::atomic_ulong;
using atomics::atomic_long;
using atomics::atomic_uint64_t;
using atomics::atomic_int64_t;
#ifdef BOOST_HAS_LONG_LONG
using atomics::atomic_ullong;
using atomics::atomic_llong;
#endif
using atomics::atomic_address;
using atomics::atomic_bool;
using atomics::atomic_wchar_t;
#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811
using atomics::atomic_char8_t;
#endif
#if !defined(BOOST_NO_CXX11_CHAR16_T)
using atomics::atomic_char16_t;
#endif
#if !defined(BOOST_NO_CXX11_CHAR32_T)
using atomics::atomic_char32_t;
#endif

using atomics::atomic_int_least8_t;
using atomics::atomic_uint_least8_t;
using atomics::atomic_int_least16_t;
using atomics::atomic_uint_least16_t;
using atomics::atomic_int_least32_t;
using atomics::atomic_uint_least32_t;
using atomics::atomic_int_least64_t;
using atomics::atomic_uint_least64_t;
using atomics::atomic_int_fast8_t;
using atomics::atomic_uint_fast8_t;
using atomics::atomic_int_fast16_t;
using atomics::atomic_uint_fast16_t;
using atomics::atomic_int_fast32_t;
using atomics::atomic_uint_fast32_t;
using atomics::atomic_int_fast64_t;
using atomics::atomic_uint_fast64_t;
using atomics::atomic_intmax_t;
using atomics::atomic_uintmax_t;

#if !defined(BOOST_ATOMIC_NO_FLOATING_POINT)
using atomics::atomic_float_t;
using atomics::atomic_double_t;
using atomics::atomic_long_double_t;
#endif

using atomics::atomic_size_t;
using atomics::atomic_ptrdiff_t;

#if defined(BOOST_HAS_INTPTR_T)
using atomics::atomic_intptr_t;
using atomics::atomic_uintptr_t;
#endif

#if !defined(BOOST_ATOMIC_DETAIL_NO_LOCK_FREE_TYPEDEFS)
using atomics::atomic_unsigned_lock_free;
using atomics::atomic_signed_lock_free;
#endif
#undef BOOST_ATOMIC_DETAIL_NO_LOCK_FREE_TYPEDEFS

} // namespace boost

#include <boost/atomic/detail/footer.hpp>

#endif // BOOST_ATOMIC_ATOMIC_HPP_INCLUDED_

/* atomic.hpp
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
*/