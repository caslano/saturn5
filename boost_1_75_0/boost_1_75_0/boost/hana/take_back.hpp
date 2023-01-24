/*!
@file
Defines `boost::hana::take_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_BACK_HPP
#define BOOST_HANA_TAKE_BACK_HPP

#include <boost/hana/fwd/take_back.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename N>
    constexpr auto take_back_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeBack = BOOST_HANA_DISPATCH_IF(take_back_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_back(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::take_back(xs, n) requires 'n' to be an IntegralConstant");
#endif

        return TakeBack::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_back_impl<S, when<condition>> : default_ {
        template <std::size_t start, typename Xs, std::size_t ...n>
        static constexpr auto take_back_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<start + n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            constexpr std::size_t start = n < len ? len - n : 0;
            return take_back_helper<start>(static_cast<Xs&&>(xs),
                        std::make_index_sequence<(n < len ? n : len)>{});
        }
    };

    template <std::size_t n>
    struct take_back_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::take_back(static_cast<Xs&&>(xs), hana::size_c<n>);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TAKE_BACK_HPP

/* take_back.hpp
CYVfzCCqCw8iYU8lL3WCLXRhjTnAD0h7cHAH6ugDeRt5Q+ONyqpeV/QhvHWwWaXXCryMJW30grbs8ZWo/1lc1SiLoEApO6EIdt/61yDOhT5olLB8TWmQoY6ooUxe7IX1FGerO3HZuqts6gOQnTMMCOv5EMezE8DFVAfUmAgxFSZWgIlhbu80EM1w5MPgjmu5Gndhxt3+AnWxOO7okvLNw8MJG2MUYYz8OowwjIEH4Y7+qBGazVIiH0vKljwymXK4Yz9K1PsZmXBmgZvvA7jpPiMzyi3dugyp2OQV2BND+x02OhAxXcAkIBnLgpGyheazpsko6yq7MhgcjkKvCinamxZqlTVmH6wA+2CQVSCTmX0wXr0PJgvGPpisgQ8WxG5D1HRDzD6YzHQX0zH7YEHs+OB6HyyIjQjGCzOqBgaiQGNySIC/VYqWRa2kSKsshiXfeiCfku9yguUZu8fy7vDkidX5cVGWgCKZ3PUbHlp2WDZBwlmaAmxpNNJ6S3NXRixNbwuwNFfZ71AGUP9jAMzmYjybi9kdW9HmzRTdBBk1GWcfYNxLvtEF5GITUsDyLf/NhNzyhlgIqu5VoQvN18UW6AIKG5gRZCaxGXE49Ul3FTmLk7HdgD8TjOwGshaoej7abqFsOJrEbl0PAQZx+mwYR70CzsLYaGMNbOoE2FLXwLZFY0LbMAs4KdKHTzZVyI+DMZLCnsMOmc/LgWTL
*/