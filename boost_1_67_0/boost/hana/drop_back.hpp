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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_BACK_HPP

/* drop_back.hpp
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
*/