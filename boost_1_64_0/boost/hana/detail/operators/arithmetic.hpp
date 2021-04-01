/*!
@file
Defines arithmetic operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ARITHMETIC_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ARITHMETIC_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/div.hpp>
#include <boost/hana/fwd/minus.hpp>
#include <boost/hana/fwd/mod.hpp>
#include <boost/hana/fwd/mult.hpp>
#include <boost/hana/fwd/negate.hpp>
#include <boost/hana/fwd/plus.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct arithmetic_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator+(X&& x, Y&& y)
        { return hana::plus(static_cast<X&&>(x), static_cast<Y&&>(y)); }


        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator-(X&& x, Y&& y)
        { return hana::minus(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator-(X&& x)
        { return hana::negate(static_cast<X&&>(x)); }


        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator*(X&& x, Y&& y)
        { return hana::mult(static_cast<X&&>(x), static_cast<Y&&>(y)); }


        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator/(X&& x, Y&& y)
        { return hana::div(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::arithmetic_operators<typename hana::tag_of<X>::type>::value ||
            detail::arithmetic_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator%(X&& x, Y&& y)
        { return hana::mod(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ARITHMETIC_HPP

/* arithmetic.hpp
/ubLTGzodYgRN1CfxwpEfYodE7z3miepRz/7MNB1MHqQPVNEWsGBvZdcAeiKdQcZf/7JmV4RSKVapNSwbsFmStaT8eq3tif1FuDJJuLdVjSrO22tOJiJlY3oyghs9X/+CSSbe9gxKeO3rd2nXqrA0VBzegC9mHgs6VkHjqMFQFdVKlun6xskKjoX6w+dyztzEV0IsOEVEmPSWJQYEnzLE3ekD53uZQAPs37dAiZ0Uvr5i13vBQhLnkMZSv8LekofmmQPyhEVE3KhOdXG6cNXd1eGRV04//JeGx3OwwDlJXznGjI+VYgWkOGMhGTkbZqZc+AYW+X7nWqRBmkuUPqV65h5bzZx5Q8P7/c7eCFcJSmGDbN6aAH3BtMSlFVWNlaKJYNi7AFec+F9gJjJGFN60oYiug1NwFd7RW/aK5D8d7CohmZFDPDLm/VOG59QT6wwz85Kd+m65YSHH9J9BLgTMHpNlRe0HygLwRtpeKEV4WYoOz/3PUp7crjcqbOxC23ADdUMPDj7/U/AchIT0c/MD+dqtuduIvBFJi9gALtD/4xzATavAg67mBXgqw==
*/