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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_RANGE_HPP

/* remove_range.hpp
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
*/