/*!
@file
Defines `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_BACK_HPP
#define BOOST_HANA_DROP_BACK_HPP

#include <boost/hana/fwd/drop_back.hpp>

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
    constexpr auto drop_back_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using DropBack = BOOST_HANA_DISPATCH_IF(drop_back_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::drop_back(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_back(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::drop_back(xs, n) requires 'n' to be non-negative");

        return DropBack::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_back_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_c<1>);
    }
    //! @endcond

    template <typename S, bool condition>
    struct drop_back_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...n>
        static constexpr auto drop_back_helper(Xs&& xs, std::index_sequence<n...>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs))...);
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            return drop_back_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<(n > len ? 0 : len - n)>{});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_DROP_BACK_HPP

/* drop_back.hpp
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
*/