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
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
*/