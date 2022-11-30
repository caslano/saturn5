/*!
@file
Defines `boost::hana::remove_range` and `boost::hana::remove_range_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_RANGE_HPP
#define BOOST_HANA_REMOVE_RANGE_HPP

#include <boost/hana/fwd/remove_range.hpp>

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
    template <typename Xs, typename From, typename To>
    constexpr auto remove_range_t::operator()(Xs&& xs, From const& from, To const& to) const {
        using S = typename hana::tag_of<Xs>::type;
        using RemoveRange = BOOST_HANA_DISPATCH_IF(remove_range_impl<S>,
            hana::Sequence<S>::value &&
            hana::IntegralConstant<From>::value &&
            hana::IntegralConstant<To>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::remove_range(xs, from, to) requires 'xs' to be a Sequence");

        static_assert(hana::IntegralConstant<From>::value,
        "hana::remove_range(xs, from, to) requires 'from' to be an IntegralConstant");

        static_assert(hana::IntegralConstant<To>::value,
        "hana::remove_range(xs, from, to) requires 'to' to be an IntegralConstant");
    #endif

        return RemoveRange::apply(static_cast<Xs&&>(xs), from, to);
    }
    //! @endcond

    template <typename S, bool condition>
    struct remove_range_impl<S, when<condition>> : default_ {
        template <std::size_t offset, typename Xs, std::size_t ...before, std::size_t ...after>
        static constexpr auto
        remove_range_helper(Xs&& xs, std::index_sequence<before...>,
                                     std::index_sequence<after...>)
        {
            return hana::make<S>(
                hana::at_c<before>(static_cast<Xs&&>(xs))...,
                hana::at_c<offset + after>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename From, typename To>
        static constexpr auto apply(Xs&& xs, From const&, To const&) {
            constexpr std::size_t from = From::value;
            constexpr std::size_t to = To::value;
            constexpr std::size_t len = decltype(hana::length(xs))::value;
            constexpr std::size_t before = from == to ? len : from;
            constexpr std::size_t after = from == to ? 0 : len - to;

            static_assert(from <= to,
            "hana::remove_range(xs, from, to) requires '[from, to)' to be a "
            "valid interval, meaning that 'from <= to'");
            static_assert(from == to || from >= 0,
            "hana::remove_range(xs, from, to) requires 'from' to be non-negative");
            static_assert(from == to || to <= len,
            "hana::remove_range(xs, from, to) requires 'to <= length(xs)'");

            return remove_range_helper<to>(static_cast<Xs&&>(xs),
                                           std::make_index_sequence<before>{},
                                           std::make_index_sequence<after>{});
        }
    };

    template <std::size_t from, std::size_t to>
    struct remove_range_c_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const {
            return hana::remove_range(static_cast<Xs&&>(xs),
                                      hana::size_c<from>,
                                      hana::size_c<to>);
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_REMOVE_RANGE_HPP

/* remove_range.hpp
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
*/