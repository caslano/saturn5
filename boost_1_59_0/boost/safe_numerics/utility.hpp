#ifndef BOOST_NUMERIC_UTILITY_HPP
#define BOOST_NUMERIC_UTILITY_HPP

//  Copyright (c) 2015 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <cstdint> // intmax_t, uintmax_t, uint8_t, ...
#include <algorithm>
#include <type_traits> // conditional
#include <limits>
#include <cassert>
#include <utility> // pair

#include <boost/integer.hpp> // (u)int_t<>::least, exact

namespace boost {
namespace safe_numerics {
namespace utility {

///////////////////////////////////////////////////////////////////////////////
// used for debugging

// provokes warning message with names of type T
// usage - print_types<T, ...>;
// see https://cukic.co/2019/02/19/tmp-testing-and-debugging-templates

/*
template<typename Tx>
using print_type = typename Tx::error_message;
*/
template <typename... Ts>
struct [[deprecated]] print_types {};

// display value of constexpr during compilation
// usage print_value(N) pn;
template<int N> 
struct print_value {
    enum test : char {
        value = N < 0 ? N - 256 : N + 256
    };
};

// static warning - same as static_assert but doesn't
// stop compilation. 
template <typename T>
struct static_test{};

template <>
struct static_test<std::false_type>{
    [[deprecated]] static_test(){}
};

template<typename T>
using static_warning = static_test<T>;

/*
// can be called by constexpr to produce a compile time
// trap of parameter passed is false.
// usage constexpr_assert(bool)
constexpr int constexpr_assert(const bool tf){
    return 1 / tf;
}
*/

///////////////////////////////////////////////////////////////////////////////
// return an integral constant equal to the the number of bits
// held by some integer type (including the sign bit)

template<typename T>
using bits_type = std::integral_constant<
    int,
    std::numeric_limits<T>::digits
    + (std::numeric_limits<T>::is_signed ? 1 : 0)
>;

/*
From http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
Find the log base 2 of an integer with a lookup table

    static const char LogTable256[256] =
    {
    #define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        -1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
        LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
        LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
    };

    unsigned int v; // 32-bit word to find the log of
    unsigned r;     // r will be lg(v)
    register unsigned int t, tt; // temporaries

    if (tt = v >> 16)
    {
      r = (t = tt >> 8) ? 24 + LogTable256[t] : 16 + LogTable256[tt];
    }
    else 
    {
      r = (t = v >> 8) ? 8 + LogTable256[t] : LogTable256[v];
    }

The lookup table method takes only about 7 operations to find the log of a 32-bit value. 
If extended for 64-bit quantities, it would take roughly 9 operations. Another operation
can be trimmed off by using four tables, with the possible additions incorporated into each.
Using int table elements may be faster, depending on your architecture.
*/

namespace ilog2_detail {

    template<int N>
    constexpr inline unsigned int ilog2(const typename boost::uint_t<N>::exact & t){
        using half_type = typename boost::uint_t<N/2>::exact;
        const half_type upper_half = static_cast<half_type>(t >> N/2);
        const half_type lower_half = static_cast<half_type>(t);
        return upper_half == 0 ? ilog2<N/2>(lower_half) : N/2 + ilog2<N/2>(upper_half);
    }
    template<>
    constexpr inline unsigned int ilog2<8>(const typename boost::uint_t<8>::exact & t){
        #define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
        const char LogTable256[256] = {
            static_cast<char>(-1), 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
            LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
            LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
        };
        return LogTable256[t];
    }

} // ilog2_detail

template<typename T>
constexpr inline unsigned int ilog2(const T & t){
//  log not defined for negative numbers
//    assert(t > 0);
    if(t == 0)
        return 0;
    return ilog2_detail::ilog2<bits_type<T>::value>(
        static_cast<
            typename boost::uint_t<
                bits_type<T>::value
            >::least
        >(t)
    );
}

// the number of bits required to render the value in x
// including sign bit
template<typename T>
constexpr inline unsigned int significant_bits(const T & t){
    return 1 + ((t < 0) ? ilog2(~t) : ilog2(t));
}

/*
// give the value t, return the number which corresponds
// to all 1's which is higher than that number
template<typename T>
constexpr unsigned int bits_value(const T & t){
    const unsigned int sb = significant_bits(t);
    const unsigned int sb_max = significant_bits(std::numeric_limits<T>::max());
    return sb < sb_max ? ((sb << 1) - 1) : std::numeric_limits<T>::max();
}
*/

///////////////////////////////////////////////////////////////////////////////
// meta functions returning types

// If we use std::max in here we get internal compiler errors
// with MSVC (tested VC2017) ...

// Notes from https://en.cppreference.com/w/cpp/algorithm/max
// Capturing the result of std::max by reference if one of the parameters
// is rvalue produces a dangling reference if that parameter is returned.

template <class T>
// turns out this problem crashes all versions of gcc compilers.  So
// make sure we return by value
//constexpr const T & max(
constexpr inline T max(
    const T & lhs,
    const T & rhs
){
    return lhs > rhs ? lhs : rhs;
}

// given a signed range, return type required to hold all the values
// in the range
template<
    std::intmax_t Min,
    std::intmax_t Max
>
using signed_stored_type = typename boost::int_t<
    max(
        significant_bits(Min),
        significant_bits(Max)
    ) + 1
>::least ;

// given an unsigned range, return type required to hold all the values
// in the range
template<
    std::uintmax_t Min,
    std::uintmax_t Max
>
// unsigned range
using unsigned_stored_type = typename boost::uint_t<
    significant_bits(Max)
>::least;

///////////////////////////////////////////////////////////////////////////////
// constexpr functions

// need our own version because official version
// a) is not constexpr
// b) is not guarenteed to handle non-assignable types
template<typename T>
constexpr inline std::pair<T, T>
minmax(const std::initializer_list<T> & l){
    assert(l.size() > 0);
    const T * minimum = l.begin();
    const T * maximum = l.begin();
    for(const T * i = l.begin(); i != l.end(); ++i){
        if(*i < * minimum)
            minimum = i;
        else
        if(* maximum < *i)
            maximum = i;
    }
    return std::pair<T, T>{* minimum, * maximum};
}

// for any given t
// a) figure number of significant bits
// b) return a value with all significant bits set
// so for example:
// 3 == round_out(2) because
// 2 == 10 and 3 == 11
template<typename T>
constexpr inline T round_out(const T & t){
    if(t >= 0){
        const std::uint8_t sb = utility::significant_bits(t);
        return (sb < sizeof(T) * 8)
            ? ((T)1 << sb) - 1
            : std::numeric_limits<T>::max();
    }
    else{
        const std::uint8_t sb = utility::significant_bits(~t);
        return (sb < sizeof(T) * 8)
            ? ~(((T)1 << sb) - 1)
            : std::numeric_limits<T>::min();
    }
}

} // utility
} // safe_numerics
} // boost

#endif  // BOOST_NUMERIC_UTILITY_HPP

/* utility.hpp
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
*/