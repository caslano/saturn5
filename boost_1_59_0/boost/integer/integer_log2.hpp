// -----------------------------------------------------------
// integer_log2.hpp
//
//   Gives the integer part of the logarithm, in base 2, of a
// given number. Behavior is undefined if the argument is <= 0.
//
//        Copyright (c) 2003-2004, 2008 Gennaro Prota
//            Copyright (c) 2022 Andrey Semashev
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
//
// -----------------------------------------------------------

#ifndef BOOST_INTEGER_INTEGER_LOG2_HPP
#define BOOST_INTEGER_INTEGER_LOG2_HPP

#include <climits>
#include <limits>
#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/core/bit.hpp>
#include <boost/core/enable_if.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/make_unsigned.hpp>

namespace boost {
namespace detail {

// helper to find the maximum power of two
// less than p
template< unsigned int p, unsigned int n, bool = ((2u * n) < p) >
struct max_pow2_less :
    public max_pow2_less< p, 2u * n >
{
};

template< unsigned int p, unsigned int n >
struct max_pow2_less< p, n, false >
{
    BOOST_STATIC_CONSTANT(unsigned int, value = n);
};

template< typename T >
inline typename boost::disable_if< boost::is_integral< T >, int >::type integer_log2_impl(T x)
{
    unsigned int n = detail::max_pow2_less<
        std::numeric_limits< T >::digits,
        CHAR_BIT / 2u
    >::value;

    int result = 0;
    while (x != 1)
    {
        T t(x >> n);
        if (t)
        {
            result += static_cast< int >(n);
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
            x = static_cast< T&& >(t);
#else
            x = t;
#endif
        }
        n >>= 1u;
    }

    return result;
}

template< typename T >
inline typename boost::enable_if< boost::is_integral< T >, int >::type integer_log2_impl(T x)
{
    // We could simply rely on numeric_limits but sometimes
    // Borland tries to use numeric_limits<const T>, because
    // of its usual const-related problems in argument deduction
    // - gps
    return static_cast< int >((sizeof(T) * CHAR_BIT - 1u) -
        boost::core::countl_zero(static_cast< typename boost::make_unsigned< T >::type >(x)));
}

#if defined(BOOST_HAS_INT128)
// We need to provide explicit overloads for __int128 because (a) boost/core/bit.hpp currently does not support it and
// (b) std::numeric_limits are not specialized for __int128 in some standard libraries.
inline int integer_log2_impl(boost::uint128_type x)
{
    const boost::uint64_t x_hi = static_cast< boost::uint64_t >(x >> 64u);
    if (x_hi != 0u)
        return 127 - boost::core::countl_zero(x_hi);
    else
        return 63 - boost::core::countl_zero(static_cast< boost::uint64_t >(x));
}

inline int integer_log2_impl(boost::int128_type x)
{
    return detail::integer_log2_impl(static_cast< boost::uint128_type >(x));
}
#endif // defined(BOOST_HAS_INT128)

} // namespace detail


// ------------
// integer_log2
// ------------
template< typename T >
inline int integer_log2(T x)
{
    BOOST_ASSERT(x > 0);
    return detail::integer_log2_impl(x);
}

} // namespace boost

#endif // BOOST_INTEGER_INTEGER_LOG2_HPP

/* integer_log2.hpp
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
*/