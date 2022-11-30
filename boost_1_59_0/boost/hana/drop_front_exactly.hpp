/*!
@file
Defines `boost::hana::drop_front_exactly`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_FRONT_EXACTLY_HPP
#define BOOST_HANA_DROP_FRONT_EXACTLY_HPP

#include <boost/hana/fwd/drop_front_exactly.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/is_empty.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename N>
    constexpr auto drop_front_exactly_t::operator()(Xs&& xs, N const& n) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropFrontExactly = BOOST_HANA_DISPATCH_IF(drop_front_exactly_impl<It>,
            hana::Iterable<It>::value &&
            hana::IntegralConstant<N>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_front_exactly(xs, n) requires 'xs' to be an Iterable");

        static_assert(hana::IntegralConstant<N>::value,
        "hana::drop_front_exactly(xs, n) requires 'n' to be an IntegralConstant");
    #endif

        static_assert(N::value >= 0,
        "hana::drop_front_exactly(xs, n) requires 'n' to be non-negative");

        return DropFrontExactly::apply(static_cast<Xs&&>(xs), n);
    }

    template <typename Xs>
    constexpr auto drop_front_exactly_t::operator()(Xs&& xs) const {
        return (*this)(static_cast<Xs&&>(xs), hana::size_c<1>);
    }
    //! @endcond

    namespace detail {
        template <typename Xs, typename N>
        constexpr void check_dfe_overflow(Xs const& xs, N const&, hana::true_) {
            constexpr bool n_overflew_length = decltype(
                hana::is_empty(hana::drop_front(xs, hana::size_c<N::value - 1>))
            )::value;
            static_assert(!n_overflew_length,
            "hana::drop_front_exactly(xs, n) requires 'n' to be less than or "
            "equal to the number of elements in 'xs'");
        }

        template <typename Xs, typename N>
        constexpr void check_dfe_overflow(Xs const&, N const&, hana::false_) { }
    }

    template <typename It, bool condition>
    struct drop_front_exactly_impl<It, when<condition>> : default_ {
        template <typename Xs, typename N>
        static constexpr auto apply(Xs&& xs, N const& n) {
            auto result = hana::drop_front(static_cast<Xs&&>(xs), n);
            constexpr bool check_for_overflow =
                decltype(hana::is_empty(result))::value && N::value != 0;

            detail::check_dfe_overflow(xs, n, hana::bool_c<check_for_overflow>);

            return result; // NRVO applied
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_DROP_FRONT_EXACTLY_HPP

/* drop_front_exactly.hpp
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
*/