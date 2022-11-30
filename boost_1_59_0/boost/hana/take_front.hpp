/*!
@file
Defines `boost::hana::take_front` and `boost::hana::take_front_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TAKE_FRONT_HPP
#define BOOST_HANA_TAKE_FRONT_HPP

#include <boost/hana/fwd/take_front.hpp>

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
    constexpr auto take_front_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using TakeFront = BOOST_HANA_DISPATCH_IF(take_front_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::take_front(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::take_front(xs, n) requires 'n' to be an IntegralConstant");
#endif

        return TakeFront::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct take_front_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto take_front_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t size = decltype(hana::length(xs))::value;
            return take_front_helper(static_cast<Xs&&>(xs),
                        std::make_index_sequence<(n < size ? n : size)>{});
        }
    };

    template <std::size_t n>
    struct take_front_c_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const {
            return hana::take_front(static_cast<Xs&&>(xs), hana::size_c<n>);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_TAKE_FRONT_HPP

/* take_front.hpp
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
*/