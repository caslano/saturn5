#ifndef BOOST_NUMERIC_SAFE_COMPARE_HPP
#define BOOST_NUMERIC_SAFE_COMPARE_HPP

//  Copyright (c) 2012 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <type_traits>
#include <limits>

namespace boost {
namespace safe_numerics {
namespace safe_compare {

////////////////////////////////////////////////////
// safe comparison on primitive integral types
namespace safe_compare_detail {
    template<typename T>
    using make_unsigned = typename std::conditional<
        std::is_signed<T>::value,
        std::make_unsigned<T>,
        T
    >::type;

    // both arguments unsigned or signed
    template<bool TS, bool US>
    struct less_than {
        template<class T, class U>
        constexpr static bool invoke(const T & t, const U & u){
            return t < u;
        }
    };

    // T unsigned, U signed
    template<>
    struct less_than<false, true> {
        template<class T, class U>
        constexpr static bool invoke(const T & t, const U & u){
            return
                (u < 0) ?
                    false
                :
                    less_than<false, false>::invoke(
                        t,
                        static_cast<const typename make_unsigned<U>::type &>(u)
                    )
                ;
        }
    };
    // T signed, U unsigned
    template<>
    struct less_than<true, false> {
        template<class T, class U>
        constexpr static bool invoke(const T & t, const U & u){
            return
                (t < 0) ?
                    true
                :
                    less_than<false, false>::invoke(
                        static_cast<const typename make_unsigned<T>::type &>(t),
                        u
                    )
                ;
        }
    };
} // safe_compare_detail

template<class T, class U>
typename std::enable_if<
    std::is_integral<T>::value && std::is_integral<U>::value,
    bool
>::type
constexpr inline less_than(const T & lhs, const U & rhs) {
    return safe_compare_detail::less_than<
        std::is_signed<T>::value,
        std::is_signed<U>::value
    >:: invoke(lhs, rhs);
}

template<class T, class U>
typename std::enable_if<
    std::is_floating_point<T>::value && std::is_floating_point<U>::value,
    bool
>::type
constexpr inline less_than(const T & lhs, const U & rhs) {
    return lhs < rhs;
}

template<class T, class U>
constexpr inline bool greater_than(const T & lhs, const U & rhs) {
    return less_than(rhs, lhs);
}

template<class T, class U>
constexpr inline bool less_than_equal(const T & lhs, const U & rhs) {
    return ! greater_than(lhs, rhs);
}

template<class T, class U>
constexpr inline bool greater_than_equal(const T & lhs, const U & rhs) {
    return ! less_than(lhs, rhs);
}

namespace safe_compare_detail {
    // both arguments unsigned or signed
    template<bool TS, bool US>
    struct equal {
        template<class T, class U>
        constexpr static bool invoke(const T & t, const U & u){
            return t == u;
        }
    };

    // T unsigned, U signed
    template<>
    struct equal<false, true> {
        template<class T, class U>
        constexpr static bool invoke(const T & t, const U & u){
            return
                (u < 0) ?
                    false
                :
                    equal<false, false>::invoke(
                        t,
                        static_cast<const typename make_unsigned<U>::type &>(u)
                    )
                ;
        }
    };
    // T signed, U unsigned
    template<>
    struct equal<true, false> {
        template<class T, class U>
        constexpr static bool invoke(const T & t, const U & u){
            return
                (t < 0) ?
                    false
                :
                    equal<false, false>::invoke(
                        static_cast<const typename make_unsigned<T>::type &>(t),
                        u
                    )
                ;
        }
    };
} // safe_compare_detail

template<class T, class U>
typename std::enable_if<
    std::is_integral<T>::value && std::is_integral<U>::value,
    bool
>::type
constexpr inline equal(const T & lhs, const U & rhs) {
    return safe_compare_detail::equal<
        std::numeric_limits<T>::is_signed,
        std::numeric_limits<U>::is_signed
    >:: invoke(lhs, rhs);
}

template<class T, class U>
typename std::enable_if<
    std::is_floating_point<T>::value && std::is_floating_point<U>::value,
    bool
>::type
constexpr inline equal(const T & lhs, const U & rhs) {
    return lhs == rhs;
}

template<class T, class U>
constexpr inline bool not_equal(const T & lhs, const U & rhs) {
    return ! equal(lhs, rhs);
}

} // safe_compare
} // safe_numerics
} // boost

#endif // BOOST_NUMERIC_SAFE_COMPARE_HPP

/* safe_compare.hpp
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
*/