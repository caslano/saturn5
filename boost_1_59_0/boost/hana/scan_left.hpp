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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_SCAN_LEFT_HPP

/* scan_left.hpp
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
*/