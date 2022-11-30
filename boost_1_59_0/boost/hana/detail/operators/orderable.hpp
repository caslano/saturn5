/*!
@file
Defines operators for Orderables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/greater.hpp>
#include <boost/hana/fwd/greater_equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/less_equal.hpp>

#include <type_traits>


namespace boost { namespace hana { namespace detail {
    template <typename Tag>
    struct orderable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<(X&& x, Y&& y)
        { return hana::less(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>(X&& x, Y&& y)
        { return hana::greater(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<=(X&& x, Y&& y)
        { return hana::less_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>=(X&& x, Y&& y)
        { return hana::greater_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} }} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

/* orderable.hpp
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
*/