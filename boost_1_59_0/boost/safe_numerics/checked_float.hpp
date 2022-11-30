#ifndef BOOST_NUMERIC_CHECKED_FLOAT_HPP
#define BOOST_NUMERIC_CHECKED_FLOAT_HPP

//  Copyright (c) 2017 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// contains operation implementation of arithmetic operators
// on built-in floating point types.  The default implementation is to just
// invoke the operation with no checking.  These are overloaded
// for specific types such as integer, etc.

#include <type_traits> // std::is_floating_point, make_unsigned

namespace boost {
namespace safe_numerics {
namespace checked {

////////////////////////////////////////////////////
// layer 0 - implement safe operations for floating

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
        && std::is_floating_point<T>::value
    >::type
>{
    constexpr static checked_result<R>
    cast(const T & t) noexcept {
        return t;
    };
}; // checked_unary_operation

template<
    typename R,
    R Min,
    R Max,
    typename T,
    class
    F
>
struct heterogeneous_checked_operation<
    R,
    Min,
    Max,
    T,
    F,
    typename std::enable_if<
        std::is_floating_point<R>::value
        && std::is_integralt<T>::value
    >::type
>{
    constexpr static checked_result<R>
    cast(const T & t) noexcept {
        return t;
    };
}; // checked_unary_operation

template<typename R, typename T, typename U>
struct checked_operation<R, T, U, F,
    typename std::enable_if<
        std::is_floating_point<R>::value
    >::type
>{
    constexpr static checked_result<R> cast(const T & t) {
        return
            cast_impl_detail::cast_impl(
                t,
                std::is_signed<R>(),
                std::is_signed<T>()
            );
    }
    constexpr static checked_result<R> add(const T & t, const U & u) {
        return t + u;
    }

    constexpr static checked_result<R> subtract(
        const T & t,
        const U & u
    ) {
        return t - u;
    }

    constexpr static checked_result<R> multiply(
        const T & t,
        const U & u
    ) noexcept {
        return t * u;
    }

    constexpr static checked_result<R> divide(
        const T & t,
        const U & u
    ) noexcept {
        return t / u;
    }

    constexpr static checked_result<R> modulus(
        const T & t,
        const U & u
    ) noexcept {
        return t % u;
    }

    constexpr static bool less_than(const T & t, const U & u) noexcept {
        return t < u;
    }

    constexpr static bool greater_than(const T & t, const U & u) noexcept {
        return t > u;
    }

    constexpr static bool equal(const T & t, const U & u) noexcept {
        return t < u;
    }

}; // checked_binary_operation

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline bool less_than(const T & t, const U & u) noexcept {
    return t < u;
}

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline bool equal(const T & t, const U & u) noexcept {
    return t < u;
}

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline checked_result<R> left_shift(const T & t, const U & u) noexcept {
    return t << u;
}

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline checked_result<R> right_shift(const T & t, const U & u) noexcept {
    return t >> u;
}

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline checked_result<R> bitwise_or(const T & t, const U & u) noexcept {
    return t | u;
}

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline checked_result<R> bitwise_xor(const T & t, const U & u) noexcept {
    return t ^ u;
}

template<class R, class T, class U>
typename std::enable_if<
    std::is_floating_point<R>::value
    && std::is_floating_point<T>::value
    && std::is_floating_point<U>::value,
    checked_result<R>
>::type
constexpr inline checked_result<R> bitwise_and(const T & t, const U & u) noexcept {
    return t & u;
}

} // checked
} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_CHECKED_DEFAULT_HPP


/* checked_float.hpp
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
*/