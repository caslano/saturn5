/*!
@file
Defines operators for Comparables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/not_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct comparable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::comparable_operators<typename hana::tag_of<X>::type>::value ||
            detail::comparable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator==(X&& x, Y&& y)
        { return hana::equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::comparable_operators<typename hana::tag_of<X>::type>::value ||
            detail::comparable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator!=(X&& x, Y&& y)
        { return hana::not_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_COMPARABLE_HPP

/* comparable.hpp
x8d6/nvpoIagEp3E9X0lYs4pw09eBVOXTldJcQYL4ry3J+s+2qI/iJi6pkpn6bU8ZM+/rfSKgCwDJYKeOzKE1kPhKM7Xt6srpMKRatJjNeW4IozBnf2u+FiPjJnfJBKjFo1v1uXz1PJd+SMKQ4YO8lltQW6e0bswIVA6NfoD84RX+mMVOQRRSARZI4tujITGUjY1lbKVPqApPXqnl8wCDfWGgrZE8ZhP8oowNACy9Il95/saUoppsLzkEiYncnK+sRxibQaDy2sNlUWO51CaUgZDKQZZb0orUZZuSDXLqTq4DG/FlG7Xl3Ct2qvGYteaQPY6AzGHldOkOFMq8ERcWKjLz/yZuthiioIuppTlH1GYeCWKuDbjLJfUidn9pCnFa0eRmy1AqvDKDJ07Nz5IHINxIEOGMj+1eCpCFowh7XelV8r4sF0UjFXG/5miMaIzYS3LcJXcyDcS9ypiHWTEtuRrzSjJTIgyO6hX7P4o7Kayl8Z3ZV5D0VLO7JDkj8p+fbxM9MG0m/MWWuaow7gxytIlz6Dscl7MzRZ8z3OeHVFgTTHhGgo7WMp5chhaelWOLxKs1ezqSSZqumShNxhRlsHp4F0/DosbK6GZhGMBY3zVg0V8ZWZZsP8DqMqNb6Nufc3U3M5Ovr3Vnp+b
*/