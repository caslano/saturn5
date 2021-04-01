/*!
@file
Defines `boost::hana::insert_range`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INSERT_RANGE_HPP
#define BOOST_HANA_INSERT_RANGE_HPP

#include <boost/hana/fwd/insert_range.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/take_front.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N, typename Elements>
    constexpr auto insert_range_t::operator()(Xs&& xs, N&& n, Elements&& elements) const {
        using S = typename hana::tag_of<Xs>::type;
        using InsertRange = BOOST_HANA_DISPATCH_IF(insert_range_impl<S>,
            hana::Sequence<Xs>::value &&
            hana::Foldable<Elements>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<Xs>::value,
        "hana::insert_range(xs, n, elements) requires 'xs' to be a Sequence");

        static_assert(hana::Foldable<Elements>::value,
        "hana::insert_range(xs, n, elements) requires 'elements' to be a Foldable");
    #endif

        return InsertRange::apply(static_cast<Xs&&>(xs),
                                  static_cast<N&&>(n),
                                  static_cast<Elements&&>(elements));
    }
    //! @endcond

    template <typename S, bool condition>
    struct insert_range_impl<S, when<condition>> {
        template <typename Xs, typename N, typename Elements>
        static constexpr auto apply(Xs&& xs, N const& n, Elements&& e) {
            return hana::concat(
                    hana::concat(
                        hana::take_front(xs, n),
                        hana::to<S>(static_cast<Elements&&>(e))
                    ),
                    hana::drop_front(xs, n)
                );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INSERT_RANGE_HPP

/* insert_range.hpp
NYE2I3xMlzeFbv8x5WXo3NyyvAyLVDPI8TMpdcGtD85MtmSY274R1oRLaHYvNdBuJxZjNa20bKa/D4dCbSbjzo7/+DmgsirAhlgDuIgLMc4FtZZgrC3vgZRwivBtxjwwVIuFCu8W5eA+sOYBy+zAerVVelqkjptY+HRrkBx1ExSnmmMH7/v/5Kgr9snNsNi9EHeN/xG8PawBOj+a5Kf0EniO/Ahu/6byac++s3Rh0wwwBm6E6jv6j9dzQSU/Hp8j0h+0vvyhCU6HZJa9JHYjY9Mk6l1+Kn+kQe5Rpb7u9I3kSOzNd+K2fBSV4qb/iGfxN7hMzU+halGlxY5J+xxN6nxGUFDRpAPXCskH/FtwRIJOx7NUCDkxA6ErNeKABYqQYQ37h+84pxwJQLodNs5jrctFVc30X3nplvpp8crQi6hiPXhaWdUW8LyYwxqVkK0uxQZAG21bav5lnJbPs1JnyUA4qKb5rPz2ohiuv1Lktk63g+j0MykGutlf5/BDxy9B8cP0JDlnRmLZGuCks0RqTGhZWb9NlEYjU8EA5dymw+FUEf3LmMyrdO8ecQ==
*/