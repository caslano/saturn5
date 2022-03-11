/*!
@file
Defines `boost::hana::scan_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SCAN_LEFT_HPP
#define BOOST_HANA_SCAN_LEFT_HPP

#include <boost/hana/fwd/scan_left.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/prepend.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto scan_left_t::operator()(Xs&& xs, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanLeft = BOOST_HANA_DISPATCH_IF(scan_left_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_left(xs, f) requires 'xs' to be a Sequence");
#endif

        return ScanLeft::apply(static_cast<Xs&&>(xs), f);
    }

    template <typename Xs, typename State, typename F>
    constexpr auto scan_left_t::operator()(Xs&& xs, State&& state, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanLeft = BOOST_HANA_DISPATCH_IF(scan_left_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_left(xs, state, f) requires 'xs' to be a Sequence");
#endif

        return ScanLeft::apply(static_cast<Xs&&>(xs),
                               static_cast<State&&>(state), f);
    }
    //! @endcond

    template <typename S, bool condition>
    struct scan_left_impl<S, when<condition>> : default_ {
        // Without initial state
        template <typename Xs, typename F, std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply1_impl(Xs&& xs, F const& f, std::index_sequence<n1, n2, ns...>) {
            static_assert(n1 == 0, "logic error in Boost.Hana: file a bug report");

            // Use scan_left with the first element as an initial state.
            return scan_left_impl::apply_impl(
                static_cast<Xs&&>(xs),
                hana::at_c<0>(static_cast<Xs&&>(xs)),
                f, std::index_sequence<n2, ns...>{}
            );
        }

        template <typename Xs, typename F, std::size_t n>
        static constexpr auto apply1_impl(Xs&& xs, F const&, std::index_sequence<n>) {
            return hana::make<S>(hana::at_c<n>(static_cast<Xs&&>(xs)));
        }

        template <typename Xs, typename F>
        static constexpr auto apply1_impl(Xs&&, F const&, std::index_sequence<>) {
            return hana::empty<S>();
        }

        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F const& f) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            return scan_left_impl::apply1_impl(static_cast<Xs&&>(xs),
                                               f, std::make_index_sequence<Len>{});
        }


        // With initial state
        template <typename Xs, typename State, typename F,
                  std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f,
                   std::index_sequence<n1, n2, ns...>)
        {
            auto rest = scan_left_impl::apply_impl(
                                static_cast<Xs&&>(xs),
                                f(state, hana::at_c<n1>(static_cast<Xs&&>(xs))),
                                f, std::index_sequence<n2, ns...>{});
            return hana::prepend(std::move(rest), static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F, std::size_t n>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f, std::index_sequence<n>) {
            auto new_state = f(state, hana::at_c<n>(static_cast<Xs&&>(xs)));
            return hana::make<S>(static_cast<State&&>(state), std::move(new_state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto
        apply_impl(Xs&&, State&& state, F const&, std::index_sequence<>) {
            return hana::make<S>(static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto apply(Xs&& xs, State&& state, F const& f) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            return scan_left_impl::apply_impl(static_cast<Xs&&>(xs),
                                              static_cast<State&&>(state),
                                              f, std::make_index_sequence<Len>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SCAN_LEFT_HPP

/* scan_left.hpp
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
*/