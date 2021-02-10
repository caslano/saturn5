/*!
@file
Defines `boost::hana::drop_front`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_HPP
#define BOOST_HANA_DROP_FRONT_HPP

#include <boost/hana/fwd/drop_front.hpp>

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFront = BOOST_HANA_DISPATCH_IF(drop_front_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        return DropFront::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_t<1>{});
    }
    //! @endcond

    template <typename It, bool condition>
    struct drop_front_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&&, N const&) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_HPP

/* drop_front.hpp
Q3AbXMZFhKdXhn3bKGM9q8fZSTmoj8DgYT9d6ZwJ4AD05U4SFL8NQNl7mChL6pI0HDWQaW2zHiO0GxJEuvs/S5pd8yhpqRBQ5kqfZ4jIMLJhZE9THYKlLzm7JnxQHRj2QKt1o2fa0tLNCxWuGhb1nBk2E7iVTC3285NLVW9oveAQEMbnWFGQUgjaQJ8WxTAWHnL616QsEJssLE7gsN5gsv1VPJ1i8LkqoioaTRpQgWB7sJeGc8Ix28OTCmFfc0Oi5laLybiQ78cCN3Q9qd5pPrjZQIx6O0cOSq2WDv8yqD+dFCVRg5ChLpPBVVBf3HlTgkohWyalkrSyziT715bKMGeS+sfGQUiaVH7Y2exQ4vh/eiiBRcAacLx/9LQzCSWQ/Td49mXUQI/csZhuiIdgFQ3V+RhTvKEOFDulvhlYBzYsVzydrvEINKworVhRQCUXRsrzxE/t/lhbAe4xip7KZRltht32adogxZSNbQVkZE+gthT80W7S5ZXJSdD5jQkGv5Yei+rtv3rTMmStXZ+lG80kbfZNEbWYmmy2LI9lll9TzTJcNuhwCJAli2MJkCEZOqaWxIQ1XcB6mMCXpAkoSqlDZRU2yMzpDq/Zfw7vzs5S2EyJvaZ0vNZt993Fh578MjIJ5XClAzGaTvpk
*/