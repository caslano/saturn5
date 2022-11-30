#ifndef BOOST_SAFE_NUMERICS_NATIVE_HPP
#define BOOST_SAFE_NUMERICS_NATIVE_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>
#include <limits>

// policy which creates results types and values equal to that of C++ promotions.
// When used in conjunction with a desired exception policy, traps errors but
// does not otherwise alter the results produced by the program using it.
namespace boost {
namespace safe_numerics {

struct native {
public:
    // arithmetic operators
    template<typename T, typename U>
    struct addition_result {
        using type = decltype(
            typename base_type<T>::type()
            + typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct subtraction_result {
        using type = decltype(
            typename base_type<T>::type()
            - typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct multiplication_result {
        using type = decltype(
            typename base_type<T>::type()
            * typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct division_result {
        using type = decltype(
            typename base_type<T>::type()
            / typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct modulus_result {
        using type = decltype(
            typename base_type<T>::type()
            % typename base_type<U>::type()
        );
    };
    // note: comparison_result (<, >, ...) is special.
    // The return value is always a bool.  The type returned here is
    // the intermediate type applied to make the values comparable.
    template<typename T, typename U>
    struct comparison_result {
        using type = decltype(
            typename base_type<T>::type()
            + typename base_type<U>::type()
        );
    };

    // shift operators
    template<typename T, typename U>
    struct left_shift_result {
        using type = decltype(
            typename base_type<T>::type()
            << typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct right_shift_result {
        using type = decltype(
            typename base_type<T>::type()
            >> typename base_type<U>::type()
        );
    };
    // bitwise operators
    template<typename T, typename U>
    struct bitwise_or_result {
        using type = decltype(
            typename base_type<T>::type()
            | typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct bitwise_and_result {
        using type = decltype(
            typename base_type<T>::type()
            & typename base_type<U>::type()
        );
    };
    template<typename T, typename U>
    struct bitwise_xor_result {
        using type = decltype(
            typename base_type<T>::type()
            ^ typename base_type<U>::type()
        );
    };
};

} // safe_numerics
} // boost

#endif // BOOST_SAFE_NUMERICS_NATIVE_HPP

/* native.hpp
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
*/