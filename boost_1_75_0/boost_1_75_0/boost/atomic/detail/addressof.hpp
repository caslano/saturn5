/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/addressof.hpp
 *
 * This header defines \c addressof helper function. It is similar to \c boost::addressof but it is more
 * lightweight and also contains a workaround for some compiler warnings.
 */

#ifndef BOOST_ATOMIC_DETAIL_ADDRESSOF_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_ADDRESSOF_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

// Detection logic is based on boost/core/addressof.hpp
#if defined(BOOST_MSVC_FULL_VER) && BOOST_MSVC_FULL_VER >= 190024215
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF
#elif defined(BOOST_GCC) && BOOST_GCC >= 70000
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF
#elif defined(__has_builtin)
#if __has_builtin(__builtin_addressof)
#define BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF
#endif
#endif

namespace boost {
namespace atomics {
namespace detail {

template< typename T >
BOOST_FORCEINLINE T* addressof(T& value) BOOST_NOEXCEPT
{
#if defined(BOOST_ATOMIC_DETAIL_HAS_BUILTIN_ADDRESSOF)
    return __builtin_addressof(value);
#else
    // Note: The point of using a local struct as the intermediate type instead of char is to avoid gcc warnings
    // if T is a const volatile char*:
    // warning: casting 'const volatile char* const' to 'const volatile char&' does not dereference pointer
    // The local struct makes sure T is not related to the cast target type.
    struct opaque_type;
    return reinterpret_cast< T* >(&const_cast< opaque_type& >(reinterpret_cast< const volatile opaque_type& >(value)));
#endif
}

} // namespace detail
} // namespace atomics
} // namespace boost

#endif // BOOST_ATOMIC_DETAIL_ADDRESSOF_HPP_INCLUDED_

/* addressof.hpp
m8RUU16rNyNzbehFgXHkWpFXWRd6ef9trs0N4xkmUpnZIrJi6FDYC5x5jt1gPZCr9pNZlYQp3R6ZqeDgoCw4/crN5BiuiTqolMnufKL4vfN22jXZhKaLSmprvBBbLSK7h7Vdtsw/WP+wGKvTq6UtVMPn3iTpKikLb9Myt52E6BtTt/7YJBw+Tm58vd7HVStIXdioLVrVAe1442VOA3Are1MwMW/2azO9m89emJ9wHJvnjenRCNgD+VlWGyYt9DsdBjLHfh1y55bzcNVFwxbgZEZgJyxbakbnBUPjDr2AhTCxw5iSCZPrMuhSip99W7OgcToaN2NxavezJNIO2MJD5yfmAniagNDs4I+uZtSfc/w5gQt9MGAA3l5vHQppNLBIGJLGHehIfNSyM7DI+nSxIOrjTz6HVpc2t4jH6VnA5sz44mjuxsowXMLHChjEgBRiWSnvM0gf2Ox4xpvnX7sCo+EScc/9jlbz+CfdTrH/akpe9pH+qbcLUyXhQ3I1IsfXa/qAzh/Pguyrxlwvym0/lpS4JsPDVtVB4fZToV2kPDuf6O+e0VNUa3UawEZbdoNd6QmTNGsbUlwnKmm9t/VP+tnA33phLrpqvKK+BXcjxgYEqdkM9n/HFO2aE6Zq9txsRi2zabM4GobbD+GHsRBxFXvksZFPNHuGHnAcpZOYltZuEK27UJs1yzbwndJrLxZs6LNJK+h1dAKxehnm
*/