/*!
@file
Defines concepts from the Standard library.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CONCEPTS_HPP
#define BOOST_HANA_DETAIL_CONCEPTS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/std_common_type.hpp>
#include <boost/hana/detail/void_t.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @cond
    //////////////////////////////////////////////////////////////////////////
    // EqualityComparable
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U = T, typename = void>
    struct EqualityComparable : std::false_type { };

    template <typename T>
    struct EqualityComparable<T, T, detail::void_t<
        decltype(static_cast<T&&>(*(T*)0) == static_cast<T&&>(*(T*)0) ? 0:0),
        decltype(static_cast<T&&>(*(T*)0) != static_cast<T&&>(*(T*)0) ? 0:0)
    >> : std::true_type { };

    template <typename T, typename U>
    struct EqualityComparable<T, U, typename std::enable_if<
        !std::is_same<T, U>::value, detail::void_t<
            decltype(static_cast<T&&>(*(T*)0) == static_cast<U&&>(*(U*)0) ? 0:0),
            decltype(static_cast<U&&>(*(U*)0) == static_cast<T&&>(*(T*)0) ? 0:0),
            decltype(static_cast<T&&>(*(T*)0) != static_cast<U&&>(*(U*)0) ? 0:0),
            decltype(static_cast<U&&>(*(U*)0) != static_cast<T&&>(*(T*)0) ? 0:0),
            typename detail::std_common_type<T, U>::type
    >>::type> : std::integral_constant<bool,
        EqualityComparable<T>::value &&
        EqualityComparable<U>::value &&
        EqualityComparable<typename detail::std_common_type<T, U>::type>::value
    > { };


    //////////////////////////////////////////////////////////////////////////
    // LessThanComparable
    //////////////////////////////////////////////////////////////////////////
    template <typename T, typename U = T, typename = void>
    struct LessThanComparable : std::false_type { };

    template <typename T>
    struct LessThanComparable<T, T, detail::void_t<
        decltype(static_cast<T&&>(*(T*)0) < static_cast<T&&>(*(T*)0) ? 0:0)
    >> : std::true_type { };

    template <typename T, typename U>
    struct LessThanComparable<T, U, std::enable_if_t<
        !std::is_same<T, U>::value,
        detail::void_t<
            decltype(static_cast<T&&>(*(T*)0) < static_cast<U&&>(*(U*)0) ? 0:0),
            decltype(static_cast<U&&>(*(U*)0) < static_cast<T&&>(*(T*)0) ? 0:0),
            typename detail::std_common_type<T, U>::type
        >
    >>
        : std::integral_constant<bool,
            LessThanComparable<T>::value &&
            LessThanComparable<U>::value &&
            LessThanComparable<typename detail::std_common_type<T, U>::type>::value
        >
    { };
    //! @endcond
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CONCEPTS_HPP

/* concepts.hpp
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
*/