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
BaBc/afY4RY8OosXSRThIE2ZQy90xFjLMuTEM3VSwM/29eFZMeCwB/8ca6+XjuERsbzwNL8/MiDLBX5nWoFL+gXe01QgLimcQe9dkKIZZb4OJPGkVGcmb6hPoXwhWX6hYYtvKjpyLFb0dZcs+tohRdeOv2LR23/+TxTNx4v+3dFLFT06QVv0P8ZdsegJ/0zR547Gz79esuifmrRFN1yZ4C+8OKQfzkAZRA6VSOsfoptWZk9SaSgfZ7i4P4y3nWAGiPbtbi6hd+D9zrOis8vvlET+pOjspruBEyGosN5+ltsV8EAn++P31EvTf21wniVFltqzc7htgfqtZrzHe3YOLgJnYaHSp8U6XUNrvfNs7dnlXN1uGvxdru539GUlV/dj+vI9rq4B782cqHfLtWez+cWoHx8im0GriUgvFKPLlN6Fm7yjF5aiPepeyPc1D+TrPBseTw4122W99BgtB/0O2SNQGr2sZRHdvfXuQf9jZswzo9k+qIeUrjhG2d6vIJb1RI5b5rY13S78NVFoShbdkYbg7OyFydUw7w8KUnZ4Onzfs3C88l0SHg3f+bHvW0APbZVtTdUz/Q1mahh/UG876zXWJy2V7YjqqSI8iWKhZYZfgqb36NbGD1QsMHM+FPQQcZcmon+R2RblZyDiU4i7l+F+u/TjIg3yX7Iqkn8V4WkXIQxIzNVi+2vridqaQR1eWz4pPXcd2xF+B499
*/