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
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
*/