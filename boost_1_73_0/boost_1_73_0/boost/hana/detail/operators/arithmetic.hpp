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
+lCEcMxm2KhKl4UboFlM2dZK/hiBA2Nd8mSWVK0v1jNNjvn+sZuDe9Cw+Doflx985ciuoUd1Ie3cbKMPkMPZjEaKyenysi9MLPM4oGKgcr+LWw7u7WGi8IRB4ZlC86716cfD/7QNC9TtEMZicelXcvG+Z9k/a63NNHvw3uSr3j/+gHIkUqIPGOCuGaARA7TsqJfrYPXJcIT1tOxRM6wdheoremkWfNN+/GBecpXYq81Pm2t2U+cvmIzG7ESJlfyose42zo9nARtzn+5qFEos15YwF04V3YjKZX32hFdFSzdc8dy5FgVsWj7zeohPXuseEQivEaRmmMb38HRvLz8kYllT3d0yh5PxFR6/QGcAt1MCFF9LSJ99kWO4RT/ATsEfDhP7VjtmkNVkYumq2ykjUjbR/rF3C3DRSvfmke+yuEvHCw0vflGOc0Hf+mFGSweaAuDyNvkDxiBIjIVZVqYu3lQ5wsQoIY8s8m2tn6qyqFs3wcOv6vxtPPUvjtQa7FrZEO7lRyj6TKtwqiROIeaL6Q3abXEeitwVZ2FX+mOAUKs0b2llbXIsvYYc0yb7BeEiDaPsei5LyACBwE9SFi0qkWJB2WlMnS/qEiQTVcl4JJeobi343hBm+s6P0gflUsmEZU5D4CQvogmvJw9T
*/