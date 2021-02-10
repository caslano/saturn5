/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2009 Helge Bahmann
 * Copyright (c) 2012 Tim Blechmann
 * Copyright (c) 2013 - 2018, 2020 Andrey Semashev
 */
/*!
 * \file   atomic/detail/bitwise_cast.hpp
 *
 * This header defines \c bitwise_cast used to convert between storage and value types
 */

#ifndef BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_

#include <cstddef>
#include <boost/atomic/detail/config.hpp>
#include <boost/atomic/detail/addressof.hpp>
#include <boost/atomic/detail/string_ops.hpp>
#include <boost/atomic/detail/type_traits/integral_constant.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#pragma GCC diagnostic push
// copying an object of non-trivial type X from an array of Y. This is benign because we use memcpy to copy trivially copyable objects.
#pragma GCC diagnostic ignored "-Wclass-memaccess"
#endif

namespace boost {
namespace atomics {
namespace detail {

template< std::size_t FromSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To& to, atomics::detail::true_type) BOOST_NOEXCEPT
{
    BOOST_ATOMIC_DETAIL_MEMSET(reinterpret_cast< unsigned char* >(atomics::detail::addressof(to)) + FromSize, 0, sizeof(To) - FromSize);
}

template< std::size_t FromSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To&, atomics::detail::false_type) BOOST_NOEXCEPT
{
}

template< std::size_t FromSize, typename To >
BOOST_FORCEINLINE void clear_tail_padding_bits(To& to) BOOST_NOEXCEPT
{
    atomics::detail::clear_tail_padding_bits< FromSize >(to, atomics::detail::integral_constant< bool, FromSize < sizeof(To) >());
}

template< typename To, std::size_t FromSize, typename From >
BOOST_FORCEINLINE To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    To to;
    BOOST_ATOMIC_DETAIL_MEMCPY
    (
        atomics::detail::addressof(to),
        atomics::detail::addressof(from),
        (FromSize < sizeof(To) ? FromSize : sizeof(To))
    );
    atomics::detail::clear_tail_padding_bits< FromSize >(to);
    return to;
}

template< typename To, typename From >
BOOST_FORCEINLINE To bitwise_cast(From const& from) BOOST_NOEXCEPT
{
    return atomics::detail::bitwise_cast< To, sizeof(From) >(from);
}

} // namespace detail
} // namespace atomics
} // namespace boost

#if defined(BOOST_GCC) && BOOST_GCC >= 80000
#pragma GCC diagnostic pop
#endif

#endif // BOOST_ATOMIC_DETAIL_BITWISE_CAST_HPP_INCLUDED_

/* bitwise_cast.hpp
eQX0VijMsSGCXjWB5G23y+74/cCxrIVdGt0lLG7tJBzkrVS+7467Yi4IKQpPDA5J0OTTa9HBnZIHhOcvy9V6ed/TrjBv9/+s2STXqxgROoMIRR166eBoLInUWmNTT0EPVCcWFH5EspyhDC77WDxfzOAlZEesaYkdKtNQXmC0Ov/Q5/LKebrI1gkbXkKbh41NfX7jO2pxWKc9RzGgQ+1HDBXukUD0+PFxgtWhYoi631Iq9RX6aUA/fReapyS+j/N11eTYjct5iv3jEKGD83r1fu00AB3Qf0jpPFDPdBxGQkFJ6pA6inKU0Trrfk7Y76aN4qRGQfgzDgs5wg42/ylhv9Aa5fCyy24VciPsHiup8GZG1EztqtifClSAQsC6h/7R/wrqp0QeX78MnCSaPxO2mJRd4idRV5PG6az0PJPQb6X4Fb0IA/FmhqNxgLbKS843N6HHYGxo9Ow2/O9H8323+ZqwsIYTWZOIZNHfBzcS+l/gLGRDS7TV4+HM2lxRZXhbVfIDNpJukP68UL37Ce2nDXzWIIt9PmhzUlhSP/r7Kml6QhcJ0SVDdJ69P79+o5ETn9+RbiweLTBNC+pXR7dSGI2XS4Tm3sX1gV6LmiZsr/WHoDVas2/ZE49jwNH811OAcLTDeis8tSbl24wA
*/