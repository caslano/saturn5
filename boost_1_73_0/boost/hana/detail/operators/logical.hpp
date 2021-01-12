/*!
@file
Defines logical operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/and.hpp>
#include <boost/hana/fwd/not.hpp>
#include <boost/hana/fwd/or.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct logical_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator||(X&& x, Y&& y)
        { return hana::or_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator&&(X&& x, Y&& y)
        { return hana::and_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator!(X&& x)
        { return hana::not_(static_cast<X&&>(x)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

/* logical.hpp
teiMXByJAqT4Ym6XPeLVJbGoDu7jdXAPJIcD/BSsqIVtiX9sKR2cq853xiG+c2WeHXlZXdS71igQCupl/c7Uu3Um9iqJfTVi60FfpT0t1PMkDygVFSlfWbWZ3FiZsd4eJ/yajl25Xn7NkX487iiE1rvPLz5UFS8W9dmsKUd3e0C0Igg1q0hNBDuvSu/i2Haaq/WiuFXI0t1CfiY2fQXN56lONPAtlfUv98ZqE9p1JovIwaMY
*/