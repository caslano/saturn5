/*!
@file
Defines `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_AT_HPP
#define BOOST_HANA_REMOVE_AT_HPP

#include <boost/hana/fwd/remove_at.hpp>

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
    constexpr auto remove_at_t::operator()(Xs&& xs, N const& n) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveAt = BOOST_HANA_DISPATCH_IF(remove_at_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_at(xs, n) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::remove_at(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::remove_at(xs, n) requires 'n' to be non-negative");

        return RemoveAt::apply(static_cast<Xs&&>(xs), n);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_at_impl<S, when<condition>> : default_ {
        template <typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_at_helper(Xs&& xs, std::index_sequence<before...>,
                                  std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<after + sizeof...(before) + 1>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const&) {
            constexpr std::size_t n = N::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            static_assert(n < len,
            "hana::remove_at(xs, n) requires 'n' to be in the bounds of the sequence");
            return remove_at_helper(static_cast<Xs&&>(xs),
                                    std::make_index_sequence<n>{},
                                    std::make_index_sequence<len - n - 1>{});
        }
    };

    template <std::size_t n>
    struct remove_at_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const
        { return hana::remove_at(static_cast<Xs&&>(xs), hana::size_c<n>); }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_REMOVE_AT_HPP

/* remove_at.hpp
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
*/