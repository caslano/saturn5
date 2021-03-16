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
ccBDc8W0PQZ4EvBwIMtxRK603SOu7R4J215BaOscrQ+TM4cVO83dntUxewHNOv5vLqDR+wxTjLFXjeT8qCywyAENOdkXSi/ljcz1THH/hP83Hh7yb0JOb9Zl3y43JLDQ67WrXtn5EYXvbu26WtkZ1S3KzrIsK3xTcfbkV3ncJUxTKKtpqJ8VmutbWhv6ukEhptL+9bEeQm2Z5A97E76bKXksRM2eyJi34GCiKFdMt4Nz5X3BIblyjnqPXDk/PTQ=
*/