#ifndef BOOST_NUMERIC_CHECKED_RESULT_OPERATIONS
#define BOOST_NUMERIC_CHECKED_RESULT_OPERATIONS

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Implemenation of arithmetic on "extended" integers.
// Extended integers are defined in terms of C++ primitive integers as
//     a) an interger range
//     b) extra elements +inf, -inf, indeterminate
//
// Integer operations are closed on the set of extended integers
// but operations are not necessarily associative when they result in the
// extensions +inf, -inf, and indeterminate
//
// in this code, the type "checked_result<T>" where T is some
// integer type is an "extended" integer.

#include <cassert>

#include <boost/logic/tribool.hpp>

#include "checked_result.hpp"
#include "checked_integer.hpp"

//////////////////////////////////////////////////////////////////////////
// the following idea of "value_type" is used by several of the operations
// defined by checked_result arithmetic.

namespace boost {
namespace safe_numerics {

template<typename T>
constexpr inline void display(const boost::safe_numerics::checked_result<T> & c){
    switch(c.m_e){
    case safe_numerics_error::success:
        std::terminate();
    case safe_numerics_error::positive_overflow_error:    // result is above representational maximum
        std::terminate();
    case safe_numerics_error::negative_overflow_error:    // result is below representational minimum
        std::terminate();
    case safe_numerics_error::domain_error:               // one operand is out of valid range
        std::terminate();
    case safe_numerics_error::range_error:                // result cannot be produced for this operation
        std::terminate();
    case safe_numerics_error::precision_overflow_error:   // result lost precision
        std::terminate();
    case safe_numerics_error::underflow_error:            // result is too small to be represented
        std::terminate();
    case safe_numerics_error::negative_value_shift:       // negative value in shift operator
        std::terminate();
    case safe_numerics_error::negative_shift:             // shift a negative value
        std::terminate();
    case safe_numerics_error::shift_too_large:            // l/r shift exceeds variable size
        std::terminate();
    case safe_numerics_error::uninitialized_value:        // creating of uninitialized value
        std::terminate();
    }
}

//////////////////////////////////////////////////////////////////////////
// implement C++ operators for check_result<T>

struct sum_value_type {
    // characterization of various values
    const enum flag {
        known_value = 0,
        less_than_min,
        greater_than_max,
        indeterminate,
        count
    } m_flag;
    template<class T>
    constexpr flag to_flag(const checked_result<T> & t) const {
        switch(static_cast<safe_numerics_error>(t)){
        case safe_numerics_error::success:
            return known_value;
        case safe_numerics_error::negative_overflow_error:
            // result is below representational minimum
            return less_than_min;
        case safe_numerics_error::positive_overflow_error:
            // result is above representational maximum
            return greater_than_max;
        default:
            return indeterminate;
        }
    }
    template<class T>
    constexpr sum_value_type(const checked_result<T> & t) :
        m_flag(to_flag(t))
    {}
    constexpr operator std::uint8_t () const {
        return static_cast<std::uint8_t>(m_flag);
    }
};

// integers addition
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator+(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = sum_value_type;
    const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    // note major pain.  Clang constexpr multi-dimensional array is fine.
    // but gcc doesn't permit a multi-dimensional array to be be constexpr.
    // so we need to some ugly gymnastics to make our system work for all
    // all systems.
    const enum safe_numerics_error result[order * order] = {
        // t == known_value
        //{
            // u == ...
            safe_numerics_error::success,                   // known_value,
            safe_numerics_error::negative_overflow_error,   // less_than_min,
            safe_numerics_error::positive_overflow_error,   // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == less_than_min,
        //{
            // u == ...
            safe_numerics_error::negative_overflow_error,   // known_value,
            safe_numerics_error::negative_overflow_error,   // less_than_min,
            safe_numerics_error::range_error,               // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == greater_than_max,
        //{
            // u == ...
            safe_numerics_error::positive_overflow_error,   // known_value,
            safe_numerics_error::range_error,               // less_than_min,
            safe_numerics_error::positive_overflow_error,   // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == indeterminate,
        //{
            // u == ...
            safe_numerics_error::range_error,      // known_value,
            safe_numerics_error::range_error,      // less_than_min,
            safe_numerics_error::range_error,      // greater_than_max,
            safe_numerics_error::range_error,      // indeterminate,
        //},
    };

    const value_type tx(t);
    const value_type ux(u);

    const safe_numerics_error e = result[tx * order + ux];
    if(safe_numerics_error::success == e)
        return checked::add<T>(t, u);
    return checked_result<T>(e, "addition result");
}

// unary +
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator+(
    const checked_result<T> & t
){
    return t;
}

// integers subtraction
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator-(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = sum_value_type;
    constexpr const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    constexpr const enum safe_numerics_error result[order * order] = {
        // t == known_value
        //{
            // u == ...
            safe_numerics_error::success,                   // known_value,
            safe_numerics_error::positive_overflow_error,   // less_than_min,
            safe_numerics_error::negative_overflow_error,   // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == less_than_min,
        //{
            // u == ...
            safe_numerics_error::negative_overflow_error,   // known_value,
            safe_numerics_error::range_error,               // less_than_min,
            safe_numerics_error::negative_overflow_error,   // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == greater_than_max,
        //{
            // u == ...
            safe_numerics_error::positive_overflow_error,   // known_value,
            safe_numerics_error::positive_overflow_error,   // less_than_min,
            safe_numerics_error::range_error,               // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == indeterminate,
        //{
            // u == ...
            safe_numerics_error::range_error,               // known_value,
            safe_numerics_error::range_error,               // less_than_min,
            safe_numerics_error::range_error,               // greater_than_max,
            safe_numerics_error::range_error,               // indeterminate,
        //},
    };

    const value_type tx(t);
    const value_type ux(u);

    const safe_numerics_error e = result[tx * order + ux];
    if(safe_numerics_error::success == e)
        return checked::subtract<T>(t, u);
    return checked_result<T>(e, "subtraction result");
}

// unary -
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator-(
    const checked_result<T> & t
){
//    assert(false);
    return checked_result<T>(0) - t;
}

struct product_value_type {
    // characterization of various values
    const enum flag {
        less_than_min = 0,
        less_than_zero,
        zero,
        greater_than_zero,
        greater_than_max,
        indeterminate,
        // count of number of cases for values
        count,
        // temporary values for special cases
        t_value,
        u_value,
        z_value
    } m_flag;
    template<class T>
    constexpr flag to_flag(const checked_result<T> & t) const {
        switch(static_cast<safe_numerics_error>(t)){
        case safe_numerics_error::success:
            return (t < checked_result<T>(0))
                ? less_than_zero
                : (t > checked_result<T>(0))
                ? greater_than_zero
                : zero;
        case safe_numerics_error::negative_overflow_error:
            // result is below representational minimum
            return less_than_min;
        case safe_numerics_error::positive_overflow_error:
            // result is above representational maximum
            return greater_than_max;
        default:
            return indeterminate;
        }
    }
    template<class T>
    constexpr product_value_type(const checked_result<T> & t) :
        m_flag(to_flag(t))
    {}
    constexpr operator std::uint8_t () const {
        return static_cast<std::uint8_t>(m_flag);
    }
};

// integers multiplication
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator*(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = product_value_type;
    const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    constexpr const enum value_type::flag result[order * order] = {
        // t == less_than_min
        //{
            // u == ...
            value_type::greater_than_max,   // less_than_min,
            value_type::greater_than_max,   // less_than_zero,
            value_type::zero,               // zero,
            value_type::less_than_min,      // greater_than_zero,
            value_type::less_than_min,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == less_than_zero,
        //{
            // u == ...
            value_type::greater_than_max,   // less_than_min,
            value_type::greater_than_zero,  // less_than_zero,
            value_type::zero,               // zero,
            value_type::less_than_zero,     // greater_than_zero,
            value_type::less_than_min,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == zero,
        //{
            // u == ...
            value_type::zero,               // less_than_min,
            value_type::zero,               // less_than_zero,
            value_type::zero,               // zero,
            value_type::zero,               // greater_than_zero,
            value_type::zero,               // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == greater_than_zero,
        //{
            // u == ...
            value_type::less_than_min,      // less_than_min,
            value_type::less_than_zero,     // less_than_zero,
            value_type::zero,               // zero,
            value_type::greater_than_zero,  // greater_than_zero,
            value_type::greater_than_max,   // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == greater_than_max
        //{
            value_type::less_than_min,      // less_than_min,
            value_type::less_than_min,      // less_than_zero,
            value_type::zero,               // zero,
            value_type::greater_than_max,   // greater_than_zero,
            value_type::greater_than_max,   // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == indeterminate
        //{
            value_type::indeterminate,      // less_than_min,
            value_type::indeterminate,      // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::indeterminate,      // greater_than_zero,
            value_type::indeterminate,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //}
    };

    const value_type tx(t);
    const value_type ux(u);

    switch(result[tx * order + ux]){
        case value_type::less_than_min:
            return safe_numerics_error::negative_overflow_error;
        case value_type::zero:
            return T(0);
        case value_type::greater_than_max:
            return safe_numerics_error::positive_overflow_error;
        case value_type::less_than_zero:
        case value_type::greater_than_zero:
            return checked::multiply<T>(t, u);
        case value_type::indeterminate:
            return safe_numerics_error::range_error;
        default:
            assert(false);
        }
    return checked_result<T>(0); // to suppress msvc warning
}

// integers division
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator/(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = product_value_type;
    const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    constexpr const enum value_type::flag result[order * order] = {
        // t == less_than_min
        //{
            // u == ...
            value_type::indeterminate,   // less_than_min,
            value_type::greater_than_max,   // less_than_zero,
            value_type::less_than_min,      // zero,
            value_type::less_than_min,      // greater_than_zero,
            value_type::less_than_min,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == less_than_zero,
        //{
            // u == ...
            value_type::zero,               // less_than_min,
            value_type::greater_than_zero,  // less_than_zero,
            value_type::less_than_min,      // zero,
            value_type::less_than_zero,     // greater_than_zero,
            value_type::zero,               // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == zero,
        //{
            // u == ...
            value_type::zero,               // less_than_min,
            value_type::zero,               // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::zero,               // greater_than_zero,
            value_type::zero,               // greater than max,
            value_type::indeterminate,               // indeterminate,
        //},
        // t == greater_than_zero,
        //{
            // u == ...
            value_type::zero,               // less_than_min,
            value_type::less_than_zero,     // less_than_zero,
            value_type::greater_than_max,   // zero,
            value_type::greater_than_zero,  // greater_than_zero,
            value_type::zero,               // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == greater_than_max
        //{
            value_type::less_than_min,      // less_than_min,
            value_type::less_than_min,      // less_than_zero,
            value_type::greater_than_max,   // zero,
            value_type::greater_than_max,   // greater_than_zero,
            value_type::indeterminate,   // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == indeterminate
        //{
            value_type::indeterminate,      // less_than_min,
            value_type::indeterminate,      // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::indeterminate,      // greater_than_zero,
            value_type::indeterminate,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //}
    };

    const value_type tx(t);
    const value_type ux(u);

    switch(result[tx * order + ux]){
        case value_type::less_than_min:
            return safe_numerics_error::negative_overflow_error;
        case value_type::zero:
            return 0;
        case value_type::greater_than_max:
            return safe_numerics_error::positive_overflow_error;
        case value_type::less_than_zero:
        case value_type::greater_than_zero:
            return checked::divide<T>(t, u);
        case value_type::indeterminate:
            return safe_numerics_error::range_error;
        default:
            assert(false);
    }
    return checked_result<T>(0); // to suppress msvc warning
}

// integers modulus
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator%(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = product_value_type;
    const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    constexpr const enum value_type::flag result[order * order] = {
        // t == less_than_min
        //{
            // u == ...
            value_type::indeterminate,      // less_than_min,
            value_type::z_value,            // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::z_value,            // greater_than_zero,
            value_type::indeterminate,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == less_than_zero,
        //{
            // u == ...
            value_type::t_value,            // less_than_min,
            value_type::greater_than_zero,  // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::less_than_zero,     // greater_than_zero,
            value_type::t_value,            // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == zero,
        //{
            // u == ...
            value_type::zero,               // less_than_min,
            value_type::zero,               // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::zero,               // greater_than_zero,
            value_type::zero,               // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == greater_than_zero,
        //{
            // u == ...
            value_type::t_value,            // less_than_min,
            value_type::less_than_zero,     // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::greater_than_zero,  // greater_than_zero,
            value_type::t_value,            // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == greater_than_max
        //{
            value_type::indeterminate,      // less_than_min,
            value_type::u_value,            // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::u_value,            // greater_than_zero,
            value_type::indeterminate,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //},
        // t == indeterminate
        //{
            value_type::indeterminate,      // less_than_min,
            value_type::indeterminate,      // less_than_zero,
            value_type::indeterminate,      // zero,
            value_type::indeterminate,      // greater_than_zero,
            value_type::indeterminate,      // greater than max,
            value_type::indeterminate,      // indeterminate,
        //}
    };

    const value_type tx(t);
    const value_type ux(u);

    switch(result[tx * order + ux]){
        case value_type::zero:
            return 0;
        case value_type::less_than_zero:
        case value_type::greater_than_zero:
            return checked::modulus<T>(t, u);
        case value_type::indeterminate:
            return safe_numerics_error::range_error;
        case value_type::t_value:
            return t;
        case value_type::u_value:
            return checked::subtract<T>(u, 1);
        case value_type::z_value:
            return checked::subtract<T>(1, u);
        case value_type::greater_than_max:
        case value_type::less_than_min:
        default:
            assert(false);
    }
    // suppress msvc warning
    return checked_result<T>(0);
}

// comparison operators

template<class T>
constexpr boost::logic::tribool operator<(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = sum_value_type;
    constexpr const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    // the question arises about how to order values of type greater_than_min.
    // that is: what should greater_than_min < greater_than_min return.
    //
    // a) return indeterminate because we're talking about the "true" values for
    //    which greater_than_min is a placholder.
    //
    // b) return false because the two values are "equal"
    //
    // for our purposes, a) seems the better interpretation.
    
    enum class result_type : std::uint8_t {
        runtime,
        false_value,
        true_value,
        indeterminate,
    };
    constexpr const result_type resultx[order * order]{
        // t == known_value
        //{
            // u == ...
            result_type::runtime,       // known_value,
            result_type::false_value,   // less_than_min,
            result_type::true_value,    // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
        // t == less_than_min
        //{
            // u == ...
            result_type::true_value,    // known_value,
            result_type::indeterminate, // less_than_min, see above argument
            result_type::true_value,    // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
        // t == greater_than_max
        //{
            // u == ...
            result_type::false_value,   // known_value,
            result_type::false_value,   // less_than_min,
            result_type::indeterminate, // greater_than_max, see above argument
            result_type::indeterminate, // indeterminate,
        //},
        // t == indeterminate
        //{
            // u == ...
            result_type::indeterminate, // known_value,
            result_type::indeterminate, // less_than_min,
            result_type::indeterminate, // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
    };

    const value_type tx(t);
    const value_type ux(u);

    switch(resultx[tx * order + ux]){
    case result_type::runtime:
        return static_cast<const T &>(t) < static_cast<const T &>(u);
    case result_type::false_value:
        return false;
    case result_type::true_value:
        return true;
    case result_type::indeterminate:
        return boost::logic::indeterminate;
    default:
        assert(false);
    }
    return true;
}

template<class T>
constexpr boost::logic::tribool
operator>=(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return !(t < u);
}

template<class T>
constexpr boost::logic::tribool
operator>(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return u < t;
}

template<class T>
constexpr boost::logic::tribool
operator<=(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return !(u < t);
}

template<class T>
constexpr boost::logic::tribool
operator==(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = sum_value_type;
    constexpr const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    enum class result_type : std::uint8_t {
        runtime,
        false_value,
        true_value,
        indeterminate,
    };

    constexpr const result_type result[order * order]{
        // t == known_value
        //{
            // u == ...
            result_type::runtime,       // known_value,
            result_type::false_value,   // less_than_min,
            result_type::false_value,   // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
        // t == less_than_min
        //{
            // u == ...
            result_type::false_value,   // known_value,
            result_type::indeterminate, // less_than_min,
            result_type::false_value,   // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
        // t == greater_than_max
        //{
            // u == ...
            result_type::false_value,   // known_value,
            result_type::false_value,   // less_than_min,
            result_type::indeterminate, // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
        // t == indeterminate
        //{
            // u == ...
            result_type::indeterminate, // known_value,
            result_type::indeterminate, // less_than_min,
            result_type::indeterminate, // greater_than_max,
            result_type::indeterminate, // indeterminate,
        //},
    };

    const value_type tx(t);
    const value_type ux(u);

    switch(result[tx * order + ux]){
    case result_type::runtime:
        return static_cast<const T &>(t) == static_cast<const T &>(u);
    case result_type::false_value:
        return false;
    case result_type::true_value:
        return true;
    case result_type::indeterminate:
        return boost::logic::indeterminate;
    default:
        assert(false);
    }
    // suppress msvc warning - not all control paths return a value
    return false;
}

template<class T>
constexpr boost::logic::tribool
operator!=(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return ! (t == u);
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator>>(
    const checked_result<T> & t,
    const checked_result<T> & u
);

template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator~(
    const checked_result<T> & t
){
//    assert(false);
    return ~t.m_r;
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator<<(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = product_value_type;
    const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    constexpr const std::uint8_t result[order * order] = {
        // t == less_than_min
        //{
            // u == ...
            1, // -1,                                           // less_than_min,
            2, // safe_numerics_error::negative_overflow_error, // less_than_zero,
            2, // safe_numerics_error::negative_overflow_error, // zero,
            2, // safe_numerics_error::negative_overflow_error, // greater_than_zero,
            2, // safe_numerics_error::negative_overflow_error, // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == less_than_zero,
        //{
            // u == ...
            3, // -1,                                           // less_than_min,
            4, // - (-t >> -u),                                 // less_than_zero,
            5, // safe_numerics_error::negative_overflow_error, // zero,
            6, // - (-t << u),                                  // greater_than_zero,
            2, // safe_numerics_error::negative_overflow_error, // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == zero,
        //{
            // u == ...
            3, // 0     // less_than_min,
            3, // 0     // less_than_zero,
            3, // 0,    // zero,
            3, // 0,    // greater_than_zero,
            3, // 0,    // greater than max,
            3, // safe_numerics_error::range_error,    // indeterminate,
        //},
        // t == greater_than_zero,
        //{
            // u == ...
            3, // 0,                                            // less_than_min,
            7, // t << -u,                                      // less_than_zero,
            5, // t,                                            // zero,
            8, // t << u                                        // greater_than_zero,
            9, // safe_numerics_error::positive_overflow_error, // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == greater_than_max
        //{
            // u == ...
            1, // safe_numerics_error::range_error,               // less_than_min,
            9, // safe_numerics_error::positive_overflow_error),  // less_than_zero,
            9, // safe_numerics_error::positive_overflow_error,   // zero,
            9, // safe_numerics_error::positive_overflow_error),  // greater_than_zero,
            9, // safe_numerics_error::positive_overflow_error,   // greater than max,
            1, // safe_numerics_error::range_error,               // indeterminate,
        //},
        // t == indeterminate
        //{
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
        //}
    };

    const value_type tx(t);
    const value_type ux(u);
    assert(tx * order + ux < order * order);

    // I had a switch(i) statment here - but it results in an ICE
    // on multiple versions of gcc.  So make the equivalent in
    // nested if statments - should be the same (more or less)
    // performancewise.
    const unsigned int i = result[tx * order + ux];
    assert(i <= 9);
    if(1 == i){
        return safe_numerics_error::range_error;
    }
    else
    if(2 == i){
        return safe_numerics_error::negative_overflow_error;
    }
    else
    if(3 == i){
        return checked_result<T>(0);
    // the following gymnastics are to handle the case where 
    // a value is changed from a negative to a positive number.
    // For example, and 8 bit number t == -128.  Then -t also
    // equals -128 since 128 cannot be held in an 8 bit signed
    // integer.
    }
    else
    if(4 == i){ // - (-t >> -u)
        assert(static_cast<bool>(t < checked_result<T>(0)));
        assert(static_cast<bool>(u < checked_result<T>(0)));
        return t >> -u;
    }
    else
    if(5 == i){
        return t;
    }
    else
    if(6 == i){ // - (-t << u)
        assert(static_cast<bool>(t < checked_result<T>(0)));
        assert(static_cast<bool>(u > checked_result<T>(0)));
        const checked_result<T> temp_t = t * checked_result<T>(2);
        const checked_result<T> temp_u = u - checked_result<T>(1);
        return  - (-temp_t << temp_u);
    }
    else
    if(7 == i){  // t >> -u
        assert(static_cast<bool>(t > checked_result<T>(0)));
        assert(static_cast<bool>(u < checked_result<T>(0)));
        return t >> -u;
    }
    else
    if(8 == i){ // t << u
        assert(static_cast<bool>(t > checked_result<T>(0)));
        assert(static_cast<bool>(u > checked_result<T>(0)));
        checked_result<T> r = checked::left_shift<T>(t, u);
        return (r.m_e == safe_numerics_error::shift_too_large)
        ? checked_result<T>(safe_numerics_error::positive_overflow_error)
        : r;
    }
    else
    if(9 == i){
        return safe_numerics_error::positive_overflow_error;
    }
    else{
        assert(false);
    };
    return checked_result<T>(0); // to suppress msvc warning
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator>>(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    using value_type = product_value_type;
    const std::uint8_t order = static_cast<std::uint8_t>(value_type::count);

    const std::uint8_t result[order * order] = {
        // t == less_than_min
        //{
            // u == ...
            2, // safe_numerics_error::negative_overflow_error, // less_than_min,
            2, // safe_numerics_error::negative_overflow_error, // less_than_zero,
            2, // safe_numerics_error::negative_overflow_error, // zero,
            2, // safe_numerics_error::negative_overflow_error, // greater_than_zero,
            1, // safe_numerics_error::range_error,             // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == less_than_zero,
        //{
            // u == ...
            2, // safe_numerics_error::negative_overflow_error  // less_than_min,
            4, // - (-t << -u),                                 // less_than_zero,
            5, // safe_numerics_error::negative_overflow_error. // zero,
            6, // - (-t >> u),                                  // greater_than_zero,
            3, // 0, ? or -1                                    // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == zero,
        //{
            // u == ...
            3, // 0     // less_than_min,
            3, // 0     // less_than_zero,
            3, // 0,    // zero,
            3, // 0,    // greater_than_zero,
            3, // 0,    // greater than max,
            3, // safe_numerics_error::range_error,    // indeterminate,
        //},
        // t == greater_than_zero,
        //{
            // u == ...
            9, // safe_numerics_error::positive_overflow_error  // less_than_min,
            7, // t << -u,                                      // less_than_zero,
            5, // t,                                            // zero,
            8, // t >> u                                        // greater_than_zero,
            3, // 0,                                            // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == greater_than_max
        //{
            // u == ...
            9, // safe_numerics_error::positive_overflow_error, // less_than_min,
            9, // safe_numerics_error::positive_overflow_error, // less_than_zero,
            9, // safe_numerics_error::positive_overflow_error, // zero,
            9, // safe_numerics_error::positive_overflow_error, // greater_than_zero,
            1, // safe_numerics_error::range_error,             // greater than max,
            1, // safe_numerics_error::range_error,             // indeterminate,
        //},
        // t == indeterminate
        //{
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
            1, // safe_numerics_error::range_error,    // indeterminate,
        //}
    };

    const value_type tx(t);
    const value_type ux(u);
    assert(tx * order + ux < order * order);

    // I had a switch(i) statment here - but it results in an ICE
    // on multiple versions of gcc.  So make the equivalent in
    // nested if statments - should be the same (more or less)
    // performancewise.
    const unsigned int i = result[tx * order + ux];
    assert(i <= 9);
    if(1 == i){
        return safe_numerics_error::range_error;
    }
    else
    if(2 == i){
        return safe_numerics_error::negative_overflow_error;
    }
    else
    if(3 == i){
        return checked_result<T>(0);
    }
    else
    if(4 == i){ // - (-t << -u)
        assert(static_cast<bool>(t < checked_result<T>(0)));
        assert(static_cast<bool>(u < checked_result<T>(0)));
        return t << -u;
    }
    else
    if(5 == i){
        return t;
    }
    else
    if(6 == i){ //  - (-t >> u)
        assert(static_cast<bool>(t < checked_result<T>(0)));
        assert(static_cast<bool>(u > checked_result<T>(0)));
        const checked_result<T> temp_t = t / checked_result<T>(2);
        const checked_result<T> temp_u = u - checked_result<T>(1);
        return  - (-temp_t >> temp_u);
    }
    else
    if(7 == i){  // t << -u,
        assert(static_cast<bool>(t > checked_result<T>(0)));
        assert(static_cast<bool>(u < checked_result<T>(0)));
        return t << -u;
    }
    else
    if(8 == i){ // t >> u
        assert(static_cast<bool>(t > checked_result<T>(0)));
        assert(static_cast<bool>(u > checked_result<T>(0)));
        checked_result<T> r = checked::right_shift<T>(t, u);
        return (r.m_e == safe_numerics_error::shift_too_large)
        ? checked_result<T>(0)
        : r;
    }
    else
    if(9 == i){
        return safe_numerics_error::positive_overflow_error;
    }
    else{
        assert(false);
    };
    return checked_result<T>(0); // to suppress msvc warning
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator|(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return
        t.exception() || u.exception()
        ? checked_result<T>(safe_numerics_error::range_error)
        : checked::bitwise_or<T>(
            static_cast<T>(t),
            static_cast<T>(u)
        );
}
template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator^(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return
        t.exception() || u.exception()
        ? checked_result<T>(safe_numerics_error::range_error)
        : checked::bitwise_xor<T>(
            static_cast<T>(t),
            static_cast<T>(u)
        );
}

template<class T>
typename std::enable_if<
    std::is_integral<T>::value,
    checked_result<T>
>::type
constexpr inline operator&(
    const checked_result<T> & t,
    const checked_result<T> & u
){
    return
        t.exception() || u.exception()
        ? checked_result<T>(safe_numerics_error::range_error)
        : checked::bitwise_and<T>(
            static_cast<T>(t),
            static_cast<T>(u)
        );
}

} // safe_numerics
} // boost

#include <iosfwd>

namespace std {

template<typename CharT, typename Traits, typename R>
inline std::basic_ostream<CharT, Traits> & operator<<(
    std::basic_ostream<CharT, Traits> & os,
    const boost::safe_numerics::checked_result<R> & r
){
    bool e = r.exception();
    os << e;
    if(!e)
        os << static_cast<R>(r);
    else
        os << std::error_code(r.m_e).message() << ':' << static_cast<char const *>(r);
    return os;
}

template<typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits> & operator<<(
    std::basic_ostream<CharT, Traits> & os,
    const boost::safe_numerics::checked_result<signed char> & r
){
    bool e = r.exception();
    os << e;
    if(! e)
        os << static_cast<std::int16_t>(r);
    else
        os << std::error_code(r.m_e).message() << ':' << static_cast<char const *>(r);
    return os;
}

template<typename CharT, typename Traits, typename R>
inline std::basic_istream<CharT, Traits> & operator>>(
    std::basic_istream<CharT, Traits> & is,
    boost::safe_numerics::checked_result<R> & r
){
    bool e;
    is >> e;
    if(!e)
        is >> static_cast<R>(r);
    else
        is >> std::error_code(r.m_e).message() >> ':' >> static_cast<char const *>(r);
    return is;
}

template<typename CharT, typename Traits>
inline std::basic_istream<CharT, Traits> & operator>>(
    std::basic_istream<CharT, Traits> & is, 
    boost::safe_numerics::checked_result<signed char> & r
){
    bool e;
    is >> e;
    if(!e){
        std::int16_t i;
        is >> i;
        r.m_contents.m_r = static_cast<signed char>(i);
    }
    else
        is >> std::error_code(r.m_e).message() >> ':' >> static_cast<char const *>(r);
    return is;
}

} // std

/////////////////////////////////////////////////////////////////
// numeric limits for checked<R>

#include <limits>

namespace std {

template<class R>
class numeric_limits<boost::safe_numerics::checked_result<R> >
    : public std::numeric_limits<R>
{
    using this_type = boost::safe_numerics::checked_result<R>;
public:
    constexpr static this_type min() noexcept {
        return this_type(std::numeric_limits<R>::min());
    }
    constexpr static this_type max() noexcept {
        return this_type(std::numeric_limits<R>::max());
    }
};

} // std

#endif  // BOOST_NUMERIC_CHECKED_RESULT_OPERATIONS

/* checked_result_operations.hpp
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
*/