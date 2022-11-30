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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_CONCEPTS_HPP

/* concepts.hpp
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
*/