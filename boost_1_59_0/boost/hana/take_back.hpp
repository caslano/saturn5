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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_TAKE_BACK_HPP

/* take_back.hpp
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
*/