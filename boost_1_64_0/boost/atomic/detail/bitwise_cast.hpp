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
rWEpLIbD4EB4EtR7emG57Q+OF3MjK2tF+PiVSfxGS/xOkfiNFv8TlZxlg1XiPw6OFf+/tLz+l8FUeDPMgDfBFnA57A1XwAFwJZwAV8Gzxb35JpHkQ+sQ8TxP4jlf4rcANtN6iac596XPlmn/Hex4Qi5k3nnj9QC0/T0IW8JHYQ58DNruv4Pd4BOwDD4JJ8I9sAI+BWeIu1r4NLwAPgNvgd/CW8V+O3wOvgBfhJ/D38GDYt7J7vvB3vBlOAi+CsfA1+A4+Aashm/BC+Hb8Fb4DlwP34Pb4PvwOfgBfAnuh/XwI/g+/DP8An4K27jIU1gKD8Bq+AXcDA/DnfAb+BD8Fu6GPI9O51JzPoc0lnRub++Lgvpye/PHBVtCN8yBUbADjIXDYBwcBePhPJgAz4N94OWwEbwWNoZbYRLcKfYPwVT4GEyHB2AGbEccMuFw2AyeAlvAM2FLOAW2hvNhW3gdzII3wBx4MzwOroe5cCvMg/fAjvAp2Am+ADvD38Gu8AAshEmkRxHsAU+AA2B3WAJ7wpGwFzwD9pF4r1ByRgO+IeU+GS6R5DxHym0VbA2rYXtYA4vhbDgYzoGz4Vw4F14CL4Lz4JXwXHgTPA+ugOdLeV0IN8EL4TZ4Mdwr/g/AxUrOIcD1Er/Gtj+J34kSvxKJ32DYEw6ReA2Fw2EpPBmOhmfCYXASHC7xHS3xHQmXwpPgclgGV4r9AXhIyR592es/HWWXs48lPvdb3vL3AGwOH4Rt4EMwF+6GY+Gj8BL4ONwKfwvvgU/CJ+Ae+DR8Cn4An4ZfwWfgN3AvdNtzvDAWPg+T4AswE74IW8GXYBf4MuwPX4VlsB7WwLfh+fAduBC+Cy+BH8Dr4HtwhegP2PE3e6epE/L89vPeLc9/peTHVZIfV0v6XwNHwnXwdLgEToTXwgoxr4HXwXlwKVwEfwGvgDfCG+AyKTc3wXVwOdwBV8CdEs4DcBWsh7fA7+Gt0GNhL/lY5tsXCy+XchUDS+Q5xkk7fRbMgxPkOSbCk+DZsBxOlvYYvbxPZU8oPCPE+3Sm5Q23Gup6BLvC2bAbnAf7w7lwGKyFo8T8AFyKWiThfyThy5yuvhbY+Q7Ph1lwIcyDF8K+8CJYAhfBSngpvMz2D6+BV8Cl8EpYBxfDh+HV8HF4DXwWLoG/h9dDeW7Zf0gahnjuR6Qf8ShsCh+DzeAe2AYStk6H38LeYj5A9PLcsgeQPA3x3LfK+/822BTeBVvCdbAdXA/z4R2SvhtgMdwEB8PNcAzcAk+FW2EV3AZnw+1wGdwBl0v4Uo5kfx1pFKIcbZR6sEXe71thP7gDDoR3Sbt5N6yF90g5SjZ7u2j/pJ61kbMc9tWb+yfDPjAN9oW94AA4EBZLO3MiPA2WwAlwsDzXVFgLK+R5KuFqOAzeBofDzWK+HY6Ad8OR8AExfwSWwd/C0XCfmP8OngJfhWPgO2L+R3g6/BCWw0/F/K9wHDwMx8Pvxdx+1okwDlZKepeiilcGpnc07CvpXSnlrAoeD6thJZwFUVp/uegPwPlK9uXAXRJeovbvvU4VGZanwSxYDgvhmbA7/Bksh+PgmXAarIAT4Bo4CW6Ak+EmWAG3iTvpd/LiD9/v/I30Ox+ATeCDsJnoTTu2M3z5e1b67c/BDvAF2A++JP33l+Fs+Cqsha9JuPlmXwB5Lv2sbH7nQPt6E3e2/i1YAN+W9HgHlsL34EnwAzgJ/gkugB/CpfBj+Ev4Cbwd/gX+Gh6Az8Mv4X54CH4PKRv6ffcNbAG/g4VQ2eUduuAI6IGTYDSsgbFwMYyHt8JEeDtsBOtgEnwUpsAXYBr8ADaBh2BT+C3MhHGkQ3PYAraEHWFreDzMhjo/zbo=
*/