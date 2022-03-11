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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_FRONT_EXACTLY_HPP

/* drop_front_exactly.hpp
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
*/