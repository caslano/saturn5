#ifndef BOOST_NUMERIC_CPP_HPP
#define BOOST_NUMERIC_CPP_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// policy which creates results types equal to that of C++ promotions.
// Using the policy will permit the program to build and run in release
// mode which is identical to that in debug mode except for the fact
// that errors aren't trapped. 

#include <type_traits> // integral constant, remove_cv, conditional
#include <limits>
#include <boost/integer.hpp> // integer type selection

#include "safe_common.hpp"
#include "checked_result.hpp"

namespace boost {
namespace safe_numerics {

// in C++ the following rules govern integer arithmetic

// This policy is use to emulate another compiler/machine architecture
// For example, a Z80 has 8 bit char, 16 bit short, 16 bit int, 32 bit long.  So one
// would use cpp<8, 16, 16, 32, 32> to test programs destined to run on a Z80

// Follow section 5 of the standard.
template<
    int CharBits,
    int ShortBits,
    int IntBits,
    int LongBits,
    int LongLongBits
>
struct cpp {
public:
    using local_char_type = typename boost::int_t<CharBits>::exact;
    using local_short_type = typename boost::int_t<ShortBits>::exact;
    using local_int_type = typename boost::int_t<IntBits>::exact;
    using local_long_type = typename boost::int_t<LongBits>::exact;
    using local_long_long_type = typename boost::int_t<LongLongBits>::exact;

    template<class T>
    using rank =
        typename std::conditional<
            std::is_same<local_char_type, typename std::make_signed<T>::type>::value,
            std::integral_constant<int, 1>,
        typename std::conditional<
            std::is_same<local_short_type, typename std::make_signed<T>::type>::value,
            std::integral_constant<int, 2>,
        typename std::conditional<
            std::is_same<local_int_type, typename std::make_signed<T>::type>::value,
            std::integral_constant<int, 3>,
        typename std::conditional<
            std::is_same<local_long_type, typename std::make_signed<T>::type>::value,
            std::integral_constant<int, 4>,
        typename std::conditional<
            std::is_same<local_long_long_type, typename std::make_signed<T>::type>::value,
            std::integral_constant<int, 5>,
            std::integral_constant<int, 6> // catch all - never promote integral
        >::type >::type >::type >::type >::type;

    // section 4.5 integral promotions

   // convert smaller of two types to the size of the larger
    template<class T, class U>
    using higher_ranked_type = typename std::conditional<
        (rank<T>::value < rank<U>::value),
        U,
        T
    >::type;

    template<class T, class U>
    using copy_sign = typename std::conditional<
        std::is_signed<U>::value,
        typename std::make_signed<T>::type,
        typename std::make_unsigned<T>::type
    >::type;

    template<class T>
    using integral_promotion = copy_sign<
        higher_ranked_type<local_int_type, T>,
        T
    >;

    // note presumption that T & U don't have he same sign
    // if that's not true, these won't work
    template<class T, class U>
    using select_signed = typename std::conditional<
        std::numeric_limits<T>::is_signed,
        T,
        U
    >::type;

    template<class T, class U>
    using select_unsigned = typename std::conditional<
        std::numeric_limits<T>::is_signed,
        U,
        T
    >::type;

    // section 5 clause 11 - usual arithmetic conversions
    template<typename T, typename U>
    using usual_arithmetic_conversions =
        // clause 0 - if both operands have the same type
        typename std::conditional<
            std::is_same<T, U>::value,
            // no further conversion is needed
            T,
        // clause 1 - otherwise if both operands have the same sign
        typename std::conditional<
            std::numeric_limits<T>::is_signed
            == std::numeric_limits<U>::is_signed,
            // convert to the higher ranked type
            higher_ranked_type<T, U>,
        // clause 2 - otherwise if the rank of he unsigned type exceeds
        // the rank of the of the signed type
        typename std::conditional<
            rank<select_unsigned<T, U>>::value
            >= rank< select_signed<T, U>>::value,
            // use unsigned type
            select_unsigned<T, U>,
        // clause 3 - otherwise if the type of the signed integer type can
        // represent all the values of the unsigned type
        typename std::conditional<
            std::numeric_limits< select_signed<T, U>>::digits >=
            std::numeric_limits< select_unsigned<T, U>>::digits,
            // use signed type
            select_signed<T, U>,
        // clause 4 - otherwise use unsigned version of the signed type
            std::make_signed< select_signed<T, U>>
        >::type >::type >::type
    >;

    template<typename T, typename U>
    using result_type = typename usual_arithmetic_conversions<
        integral_promotion<typename base_type<T>::type>,
        integral_promotion<typename base_type<U>::type>
    >::type;
public:
    template<typename T, typename U>
    struct addition_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct subtraction_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct multiplication_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct division_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct modulus_result {
       using type = result_type<T, U>;
    };
    // note: comparison_result (<, >, ...) is special.
    // The return value is always a bool.  The type returned here is
    // the intermediate type applied to make the values comparable.
    template<typename T, typename U>
    struct comparison_result {
        using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct left_shift_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct right_shift_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct bitwise_and_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct bitwise_or_result {
       using type = result_type<T, U>;
    };
    template<typename T, typename U>
    struct bitwise_xor_result {
       using type = result_type<T, U>;
    };
};

} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_cpp_HPP

/* cpp.hpp
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
*/