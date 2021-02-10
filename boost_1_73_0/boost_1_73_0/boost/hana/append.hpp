/*!
@file
Defines `boost::hana::append`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_APPEND_HPP
#define BOOST_HANA_APPEND_HPP

#include <boost/hana/fwd/append.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename X>
    constexpr auto append_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Append = BOOST_HANA_DISPATCH_IF(append_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::append(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Append::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct append_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(static_cast<Xs&&>(xs),
                                hana::lift<M>(static_cast<X&&>(x)));
        }
    };

    template <typename S>
    struct append_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto append_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<i>(static_cast<Xs&&>(xs))..., static_cast<X&&>(x)
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return append_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                 std::make_index_sequence<N>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_APPEND_HPP

/* append.hpp
gJ1vVzHNESsgTlIMajR223dP2s/eNRk6eLRJ7xZAagoiqqVidJPmiP16hDN5EVeSrgzn/ysCLvd1kqA5C21XBMvjRYI6VbcjYKy4yMq0tOWuItCY75hKthTJm3vaMPhmYcVKZy1t3xUdKwq9aK+g0Z9DpRKdetiWyaAPWAWM9l7aOZ8kOvlq6cS0GbaqVJM1Yc6awpA1r0reTrc3mlivOyen/bOeEM+flVKb0YRUh3VoghVraSIVkP8lNCE9akOaYJs/mSb6ehOaGYGLCRp2ytdcdyLqWVx4+OAhy0701coUySKFv0H65kh7yLqjudZRuEpKICRolqDonq+mIyjcN0hD9FkX6Bh9LFMw+pgRr6RuQ+OmmY7Qi6AgVCkRMfrYKqvt2M9KWxA/1XYW2tG3blNqe4IRKGzKtrfZo4YGkGMHlhuWIFFUvfjZGo07GPc2w7FBP73uz733zWYzp5PmEQPuwTqT9xc967w/Pu9Mum+/cSbWWWVt/jVR+EuzMlh7RhnkV2RQ7Bflj7Afl4ogv0YExX5Lt0G/dQmEOHqA5BGT24RiYLXVbOx6pDYDoCucJQhiGgIQR0989/fgcSsza1tks4oRq9kvFQrT02rtUjV4pPRovRal/hWrtVil82VG6BFTo1ExdzcxP8sc
*/