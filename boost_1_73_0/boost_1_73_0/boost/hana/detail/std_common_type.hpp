/*!
@file
Defines a SFINAE-friendly version of `std::common_type`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP
#define BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>

#include <utility>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Equivalent to `std::common_type`, except it is SFINAE-friendly and
    //! does not support custom specializations.
    template <typename T, typename U, typename = void>
    struct std_common_type { };

    template <typename T, typename U>
    struct std_common_type<T, U, decltype((void)(
        true ? std::declval<T>() : std::declval<U>()
    ))> {
        using type = typename detail::decay<
            decltype(true ? std::declval<T>() : std::declval<U>())
        >::type;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_STD_COMMON_TYPE_HPP

/* std_common_type.hpp
dNEIb+RSCR92vs6jqgr5puYiS1e6rvHFYBAYWdMXbYpYqMPXKJvG2Ry1gzBAbQ/qKOes41Sw/ZMBPsAdAnwLftDvLfwzCeJHh8rCSffgieNnkGOmmTX1Y5SccGxcTuVasTi+TD6k4qfJDIyBKzTzr9tXk2k6hkyMsj2F3lHncvfhh5JhOpuLaTKaHYrTT3OAjSbjrHekDHpIr6ceQFuUA5gfNqkddlVYbxdiU63nvR4P1tyiKOPLe+XQiUSuXNClzmVQx/sgSvpHOuXS7ff+cMjwtTZEKAZjko3olB9QnAax2Zz3TT2cnEcOdNqxXYH9nPWYYNTUllp5bG+bx3WskHbJ56ykn6aTPdaK0XiezsYJTg7z2c1wnm25LcQ1Uv/x+zeYlzsSiyVqY9VReF/tr38RH9IZJ1pcJ79OZrvDSZJBMr6BByiMfr4VyXS02YsjVXu1h77HsQ1+3FcEOxqLWfphMkzm7GN4mQ5/68T/r6du8w/2e5Om3IH+/8J2DbG4RAYxuFgmqrgGw2iulyoLctlQ0JGAWLKc98mpMretCee9f58/5yE8hM4DFhsPWL7oYQ+Rq3Ihc5wlChFLhfGe/55T/j1/VoUDOuVfVslUPv1yN7QmgBwiC07JZab/CT77uBaeHyIYFiKQMjmH
*/