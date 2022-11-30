#ifndef BOOST_NUMERIC_CHECKED_INTEGER_HPP
#define BOOST_NUMERIC_CHECKED_INTEGER_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// contains operations for doing checked aritmetic on NATIVE
// C++ types.

#include <limits>
#include <type_traits> // is_integral, make_unsigned, enable_if
#include <algorithm>   // std::max

#include "checked_result.hpp"
#include "checked_default.hpp"
#include "safe_compare.hpp"
#include "utility.hpp"
#include "exception.hpp"

namespace boost {
namespace safe_numerics {

// utility

template<bool tf>
using bool_type = typename std::conditional<tf, std::true_type, std::false_type>::type;

////////////////////////////////////////////////////
// layer 0 - implement safe operations for intrinsic integers
// Note presumption of twos complement integer arithmetic

// convert an integral value to some other integral type
template<
    typename R,
    R Min,
    R Max,
    typename T,
    class F
>
struct heterogeneous_checked_operation<
    R,
    Min,
    Max,
    T,
    F,
    typename std::enable_if<
        std::is_integral<R>::value
        && std::is_integral<T>::value
    >::type
>{
    ////////////////////////////////////////////////////
    // safe casting on primitive types

    struct cast_impl_detail {
        constexpr static checked_result<R>
        cast_impl(
            const T & t,
            std::true_type, // R is signed
            std::true_type  // T is signed
        ){
            // INT32-C Ensure that operations on signed
            // integers do not overflow
            return
            boost::safe_numerics::safe_compare::greater_than(t, Max) ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "converted signed value too large"
                )
            : boost::safe_numerics::safe_compare::less_than(t, Min) ?
                F::template invoke<safe_numerics_error::negative_overflow_error>(
                    "converted signed value too small"
                )
            :
                checked_result<R>(static_cast<R>(t))
            ;
        }
        constexpr static checked_result<R>
        cast_impl(
            const T & t,
            std::true_type,  // R is signed
            std::false_type  // T is unsigned
        ){
            // INT30-C Ensure that unsigned integer operations
            // do not wrap
            return
            boost::safe_numerics::safe_compare::greater_than(t, Max) ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "converted unsigned value too large"
                )
            :
            boost::safe_numerics::safe_compare::less_than(t, Min) ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "converted unsigned value too small"
                )
            :
                checked_result<R>(static_cast<R>(t))
            ;
        }
        constexpr static checked_result<R>
        cast_impl(
            const T & t,
            std::false_type, // R is unsigned
            std::false_type  // T is unsigned
        ){
            // INT32-C Ensure that operations on unsigned
            // integers do not overflow
            return
            boost::safe_numerics::safe_compare::greater_than(t, Max) ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "converted unsigned value too large"
                )
            :
            boost::safe_numerics::safe_compare::less_than(t, Min) ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "converted unsigned value too small"
                )
            :
                checked_result<R>(static_cast<R>(t))
            ;
        }
        constexpr static checked_result<R>
        cast_impl(
            const T & t,
            std::false_type, // R is unsigned
            std::true_type   // T is signed
        ){
            return
            boost::safe_numerics::safe_compare::less_than(t, Min) ?
                F::template invoke<safe_numerics_error::domain_error>(
                    "converted value to low or negative"
                )
            :
            boost::safe_numerics::safe_compare::greater_than(t, Max) ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "converted signed value too large"
                )
            :
                checked_result<R>(static_cast<R>(t))
            ;
        }
    }; // cast_impl_detail

    constexpr static checked_result<R>
    cast(const T & t){
        return
            cast_impl_detail::cast_impl(
                t,
                std::is_signed<R>(),
                std::is_signed<T>()
            );
    }
}; // heterogeneous_checked_operation

// converting floating point value to integral type
template<
    typename R,
    R Min,
    R Max,
    typename T,
    class F
>
struct heterogeneous_checked_operation<
    R,
    Min,
    Max,
    T,
    F,
    typename std::enable_if<
        std::is_integral<R>::value
        && std::is_floating_point<T>::value
    >::type
>{
    constexpr static checked_result<R>
    cast(const T & t){
        return static_cast<R>(t);
    }
}; // heterogeneous_checked_operation

// converting integral value to floating point type

// INT35-C. Use correct integer precisions
template<
    typename R,
    R Min,
    R Max,
    typename T,
    class F
>
struct heterogeneous_checked_operation<
    R,
    Min,
    Max,
    T,
    F,
    typename std::enable_if<
        std::is_floating_point<R>::value
        && std::is_integral<T>::value
     >::type
 >{
     constexpr static checked_result<R>
     cast(const T & t){
        if(std::numeric_limits<R>::digits < std::numeric_limits<T>::digits){
            if(utility::significant_bits(t) > std::numeric_limits<R>::digits){
                return F::invoke(
                    safe_numerics_error::precision_overflow_error,
                    "keep precision"
                );
            }
        }
        return t;
    }
}; // heterogeneous_checked_operation

// binary operations on primitive integer types

template<
    typename R,
    class F
>
struct checked_operation<R, F,
    typename std::enable_if<
        std::is_integral<R>::value
    >::type
>{
    ////////////////////////////////////////////////////
    // safe addition on primitive types

    struct add_impl_detail {
        // result unsigned
        constexpr static checked_result<R> add(
            const R t,
            const R u,
            std::false_type // R unsigned
        ){
            return
                // INT30-C. Ensure that unsigned integer operations do not wrap
                std::numeric_limits<R>::max() - u < t ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "addition result too large"
                    )
                :
                    checked_result<R>(t + u)
            ;
        }

        // result signed
        constexpr static checked_result<R> add(
            const R t,
            const R u,
            std::true_type // R signed
        ){
        // INT32-C. Ensure that operations on signed integers do not result in overflow
            return
                // INT32-C. Ensure that operations on signed integers do not result in overflow
                ((u > 0) && (t > (std::numeric_limits<R>::max() - u))) ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "addition result too large"
                    )
                :
                ((u < 0) && (t < (std::numeric_limits<R>::min() - u))) ?
                    F::template invoke<safe_numerics_error::negative_overflow_error>(
                        "addition result too low"
                    )
                :
                    checked_result<R>(t + u)
            ;
        }
    }; // add_impl_detail

    constexpr static checked_result<R>
    add(const R & t, const R & u){
        return add_impl_detail::add(t, u, std::is_signed<R>());
    }

    ////////////////////////////////////////////////////
    // safe subtraction on primitive types
    struct subtract_impl_detail {

        // result unsigned
        constexpr static checked_result<R> subtract(
            const R t,
            const R u,
            std::false_type // R is unsigned
        ){
            // INT30-C. Ensure that unsigned integer operations do not wrap
            return
                t < u ?
                    F::template invoke<safe_numerics_error::negative_overflow_error>(
                        "subtraction result cannot be negative"
                    )
                :
                    checked_result<R>(t - u)
            ;
        }

        // result signed
        constexpr static checked_result<R> subtract(
            const R t,
            const R u,
            std::true_type // R is signed
        ){ // INT32-C
            return
                // INT32-C. Ensure that operations on signed integers do not result in overflow
                ((u > 0) && (t < (std::numeric_limits<R>::min() + u))) ?
                    F::template invoke<safe_numerics_error::negative_overflow_error>(
                        "subtraction result overflows result type"
                    )
                :
                ((u < 0) && (t > (std::numeric_limits<R>::max() + u))) ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "subtraction result overflows result type"
                    )
                :
                    checked_result<R>(t - u)
            ;
        }

    }; // subtract_impl_detail

    constexpr static checked_result<R> subtract(const R & t, const R & u){
        return subtract_impl_detail::subtract(t, u, std::is_signed<R>());
    }

    ////////////////////////////////////////////////////
    // safe minus on primitive types
    struct minus_impl_detail {

        // result unsigned
        constexpr static checked_result<R> minus(
            const R t,
            std::false_type // R is unsigned
        ){
            return t > 0 ?
                    F::template invoke<safe_numerics_error::negative_overflow_error>(
                        "minus unsigned would be negative"
                    )
                :
                    // t == 0
                    checked_result<R>(0)
            ;
        }

        // result signed
        constexpr static checked_result<R> minus(
            const R t,
            std::true_type // R is signed
        ){ // INT32-C
            return t == std::numeric_limits<R>::min() ?
                F::template invoke<safe_numerics_error::positive_overflow_error>(
                    "subtraction result overflows result type"
                )
            :
                    checked_result<R>(-t)
            ;
        }

    }; // minus_impl_detail

    constexpr static checked_result<R> minus(const R & t){
        return minus_impl_detail::minus(t, std::is_signed<R>());
    }

    ////////////////////////////////////////////////////
    // safe multiplication on primitive types

    struct multiply_impl_detail {

        // result unsigned
        constexpr static checked_result<R> multiply(
            const R t,
            const R u,
            std::false_type,  // R is unsigned
            std::false_type   // !(sizeochecked_result<R>R) > sizeochecked_result<R>std::uintmax_t) / 2)

        ){
            // INT30-C
            // fast method using intermediate result guaranteed not to overflow
            // todo - replace std::uintmax_t with a size double the size of R
            using i_type = std::uintmax_t;
            return
                static_cast<i_type>(t) * static_cast<i_type>(u)
                > std::numeric_limits<R>::max() ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "multiplication overflow"
                    )
                :
                    checked_result<R>(t * u)
            ;
        }
        constexpr static checked_result<R> multiply(
            const R t,
            const R u,
            std::false_type,  // R is unsigned
            std::true_type    // (sizeochecked_result<R>R) > sizeochecked_result<R>std::uintmax_t) / 2)

        ){
            // INT30-C
            return
                u > 0 && t > std::numeric_limits<R>::max() / u ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "multiplication overflow"
                    )
                :
                    checked_result<R>(t * u)
            ;
        }

        // result signed
        constexpr static checked_result<R> multiply(
            const R t,
            const R u,
            std::true_type, // R is signed
            std::false_type // ! (sizeochecked_result<R>R) > (sizeochecked_result<R>std::intmax_t) / 2))

        ){
            // INT30-C
            // fast method using intermediate result guaranteed not to overflow
            // todo - replace std::intmax_t with a size double the size of R
            using i_type = std::intmax_t;
            return
                (
                    static_cast<i_type>(t) * static_cast<i_type>(u)
                    > static_cast<i_type>(std::numeric_limits<R>::max())
                ) ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "multiplication overflow"
                    )
                :
                (
                    static_cast<i_type>(t) * static_cast<i_type>(u)
                    < static_cast<i_type>(std::numeric_limits<R>::min())
                ) ?
                    F::template invoke<safe_numerics_error::negative_overflow_error>(
                        "multiplication overflow"
                    )
                :
                    checked_result<R>(t * u)
            ;
        }
        constexpr static checked_result<R> multiply(
            const R t,
            const R u,
            std::true_type,   // R is signed
            std::true_type    // (sizeochecked_result<R>R) > (sizeochecked_result<R>std::intmax_t) / 2))
        ){ // INT32-C
            return t > 0 ?
                u > 0 ?
                    t > std::numeric_limits<R>::max() / u ?
                        F::template invoke<safe_numerics_error::positive_overflow_error>(
                            "multiplication overflow"
                        )
                    :
                        checked_result<R>(t * u)
                : // u <= 0
                    u < std::numeric_limits<R>::min() / t ?
                        F::template invoke<safe_numerics_error::negative_overflow_error>(
                            "multiplication overflow"
                        )
                    :
                        checked_result<R>(t * u)
            : // t <= 0
                u > 0 ?
                    t < std::numeric_limits<R>::min() / u ?
                        F::template invoke<safe_numerics_error::negative_overflow_error>(
                            "multiplication overflow"
                        )
                    :
                        checked_result<R>(t * u)
                : // u <= 0
                    t != 0 && u < std::numeric_limits<R>::max() / t ?
                        F::template invoke<safe_numerics_error::positive_overflow_error>(
                            "multiplication overflow"
                        )
                    :
                        checked_result<R>(t * u)
            ;
        }
    }; // multiply_impl_detail

    constexpr static checked_result<R> multiply(const R & t, const R & u){
        return multiply_impl_detail::multiply(
            t,
            u,
            std::is_signed<R>(),
            std::integral_constant<
                bool,
                (sizeof(R) > sizeof(std::uintmax_t) / 2)
            >()
        );
    }

    ////////////////////////////////
    // safe division on unsafe types

    struct divide_impl_detail {
        constexpr static checked_result<R> divide(
            const R & t,
            const R & u,
            std::false_type // R is unsigned
        ){
            return t / u;
        }

        constexpr static checked_result<R> divide(
            const R & t,
            const R & u,
            std::true_type // R is signed
        ){
            return
                (u == -1 && t == std::numeric_limits<R>::min()) ?
                    F::template invoke<safe_numerics_error::positive_overflow_error>(
                        "result cannot be represented"
                    )
                :
                    checked_result<R>(t / u)
            ;
        }
    }; // divide_impl_detail

    // note that we presume that the size of R >= size of T
    constexpr static checked_result<R> divide(const R & t, const R & u){
        if(u == 0){
            return F::template invoke<safe_numerics_error::domain_error>(
                "divide by zero"
            );
        }
        return divide_impl_detail::divide(t, u, std::is_signed<R>());
    }

    ////////////////////////////////
    // safe modulus on unsafe types

    struct modulus_impl_detail {
        constexpr static checked_result<R> modulus(
            const R & t,
            const R & u,
            std::false_type // R is unsigned
        ){
            return t % u;
        }

        constexpr static checked_result<R> modulus(
            const R & t,
            const R & u,
            std::true_type // R is signed
        ){
            if(u >= 0)
                return t % u;
            checked_result<R> ux = checked::minus(u);
            if(ux.exception())
                return t;
            return t % static_cast<R>(ux);
        }
    }; // modulus_impl_detail

    constexpr static checked_result<R> modulus(const R & t, const R & u){
        if(0 == u)
            return F::template invoke<safe_numerics_error::domain_error>(
                "denominator is zero"
            );

        // why to we need abs here? the sign of the modulus is the sign of the
        // dividend. Consider -128 % -1  The result of this operation should be -1
        // but if I use t % u the x86 hardware uses the divide instruction
        // capturing the modulus as a side effect.  When it does this, it
        // invokes the operation -128 / -1 -> 128 which overflows a signed type
        // and provokes a hardware exception.  We can fix this using abs()
        // since -128 % -1 = -128 % 1 = 0
        return modulus_impl_detail::modulus(t, u, typename std::is_signed<R>::type());
    }

    ///////////////////////////////////
    // shift operations

    struct left_shift_integer_detail {

        #if 0
        // todo - optimize for gcc to exploit builtin
        /* for gcc compilers
        int __builtin_clz (unsigned int x)
              Returns the number of leading 0-bits in x, starting at the
              most significant bit position.  If x is 0, the result is undefined.
        */

        #ifndef __has_feature         // Optional of course.
          #define __has_feature(x) 0  // Compatibility with non-clang compilers.
        #endif

        template<typename T>
        constexpr unsigned int leading_zeros(const T & t){
            if(0 == t)
                return 0;
            #if __has_feature(builtin_clz)
                return  __builtin_clz(t);
            #else
            #endif
        }
        #endif

        // INT34-C C++

        // standard paragraph 5.8 / 2
        // The value of E1 << E2 is E1 left-shifted E2 bit positions;
        // vacated bits are zero-filled.
        constexpr static checked_result<R> left_shift(
            const R & t,
            const R & u,
            std::false_type // R is unsigned
        ){
            // the value of the result is E1 x 2^E2, reduced modulo one more than
            // the maximum value representable in the result type.

            // see 5.8 & 1
            // if right operand is
            // greater than or equal to the length in bits of the promoted left operand.
            if(
                safe_compare::greater_than(
                    u,
                    std::numeric_limits<R>::digits - utility::significant_bits(t)
                )
            ){
                // behavior is undefined
                return F::template invoke<safe_numerics_error::shift_too_large>(
                   "shifting left more bits than available is undefined behavior"
                );
            }
            return t << u;
        }

        constexpr static checked_result<R> left_shift(
            const R & t,
            const R & u,
            std::true_type // R is signed
        ){
            // and [E1] has a non-negative value
            if(t >= 0){
                // and E1 x 2^E2 is representable in the corresponding
                // unsigned type of the result type,

                // see 5.8 & 1
                // if right operand is
                // greater than or equal to the length in bits of the promoted left operand.
                if(
                    safe_compare::greater_than(
                        u,
                        std::numeric_limits<R>::digits - utility::significant_bits(t)
                    )
                ){
                    // behavior is undefined
                    return F::template invoke<safe_numerics_error::shift_too_large>(
                       "shifting left more bits than available"
                    );
                }
                else{
                    return t << u;
                }
            }
            // otherwise, the behavior is undefined.
            return F::template invoke<safe_numerics_error::negative_shift>(
               "shifting a negative value"
            );
        }

    }; // left_shift_integer_detail

    constexpr static checked_result<R> left_shift(
        const R & t,
        const R & u
    ){
        // INT34-C - Do not shift an expression by a negative number of bits

        // standard paragraph 5.8 & 1
        // if the right operand is negative
        if(u == 0){
            return t;
        }
        if(u < 0){
            return F::template invoke<safe_numerics_error::negative_shift>(
               "shifting negative amount"
            );
        }
        if(u > std::numeric_limits<R>::digits){
            // behavior is undefined
            return F::template invoke<safe_numerics_error::shift_too_large>(
               "shifting more bits than available"
            );
        }
        return left_shift_integer_detail::left_shift(t, u, std::is_signed<R>());
    }

    // right shift

    struct right_shift_integer_detail {

        // INT34-C C++

        // standard paragraph 5.8 / 3
        // The value of E1 << E2 is E1 left-shifted E2 bit positions;
        // vacated bits are zero-filled.
        constexpr static checked_result<R> right_shift(
            const R & t,
            const R & u,
            std::false_type // T is unsigned
        ){
            // the value of the result is the integral part of the
            // quotient of E1/2E2
            return t >> u;
        }

        constexpr static checked_result<R> right_shift(
            const R & t,
            const R & u,
            std::true_type  // T is signed;
        ){
        if(t < 0){
            // note that the C++ standard considers this case is "implemenation
            // defined" rather than "undefined".
            return F::template invoke<safe_numerics_error::negative_value_shift>(
                "shifting a negative value"
            );
         }

         // the value is the integral part of E1 / 2^E2,
         return t >> u;
        }
    }; // right_shift_integer_detail

    constexpr static checked_result<R> right_shift(
        const R & t,
        const R & u
    ){
        // INT34-C - Do not shift an expression by a negative number of bits

        // standard paragraph 5.8 & 1
        // if the right operand is negative
        if(u < 0){
            return F::template invoke<safe_numerics_error::negative_shift>(
               "shifting negative amount"
            );
        }
        if(u > std::numeric_limits<R>::digits){
            // behavior is undefined
            return F::template invoke<safe_numerics_error::shift_too_large>(
               "shifting more bits than available"
            );
        }
        return right_shift_integer_detail::right_shift(t, u ,std::is_signed<R>());
    }

    ///////////////////////////////////
    // bitwise operations

    // INT13-C Note: We don't enforce recommendation as acually written
    // as it would break too many programs.  Specifically, we permit signed
    // integer operands.

    constexpr static checked_result<R> bitwise_or(const R & t, const R & u){
        using namespace boost::safe_numerics::utility;
        const unsigned int result_size
            = std::max(significant_bits(t), significant_bits(u));

        if(result_size > bits_type<R>::value){
            return F::template invoke<safe_numerics_error::positive_overflow_error>(
                "result type too small to hold bitwise or"
            );
        }
        return t | u;
    }

    constexpr static checked_result<R> bitwise_xor(const R & t, const R & u){
        using namespace boost::safe_numerics::utility;
        const unsigned int result_size
            = std::max(significant_bits(t), significant_bits(u));

        if(result_size > bits_type<R>::value){
            return F::template invoke<safe_numerics_error::positive_overflow_error>(
                "result type too small to hold bitwise or"
            );
        }
        return t ^ u;
    }

    constexpr static checked_result<R> bitwise_and(const R & t, const R & u){
        using namespace boost::safe_numerics::utility;
        const unsigned int result_size
            = std::min(significant_bits(t), significant_bits(u));

        if(result_size > bits_type<R>::value){
            return F::template invoke<safe_numerics_error::positive_overflow_error>(
                "result type too small to hold bitwise and"
            );
        }
        return t & u;
    }

    constexpr static checked_result<R> bitwise_not(const R & t){
        using namespace boost::safe_numerics::utility;

        if(significant_bits(t) > bits_type<R>::value){
            return F::template invoke<safe_numerics_error::positive_overflow_error>(
                "result type too small to hold bitwise inverse"
            );
        }
        return ~t;
    }

}; // checked_operation
} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_CHECKED_INTEGER_HPP

/* checked_integer.hpp
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
*/