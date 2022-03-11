/*!
@file
Defines `boost::hana::scan_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SCAN_RIGHT_HPP
#define BOOST_HANA_SCAN_RIGHT_HPP

#include <boost/hana/fwd/scan_right.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/prepend.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto scan_right_t::operator()(Xs&& xs, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanRight = BOOST_HANA_DISPATCH_IF(scan_right_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_right(xs, f) requires 'xs' to be a Sequence");
#endif

        return ScanRight::apply(static_cast<Xs&&>(xs), f);
    }

    template <typename Xs, typename State, typename F>
    constexpr auto scan_right_t::operator()(Xs&& xs, State&& state, F const& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ScanRight = BOOST_HANA_DISPATCH_IF(scan_right_impl<S>,
            hana::Sequence<S>::value
        );

#ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::scan_right(xs, state, f) requires 'xs' to be a Sequence");
#endif

        return ScanRight::apply(static_cast<Xs&&>(xs),
                                static_cast<State&&>(state), f);
    }
    //! @endcond

    template <typename S, bool condition>
    struct scan_right_impl<S, when<condition>> : default_ {
        // Without initial state
        template <typename Xs, typename F, std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply1_impl(Xs&& xs, F const& f, std::index_sequence<n1, n2, ns...>) {
            auto rest = scan_right_impl::apply1_impl(static_cast<Xs&&>(xs),
                                                     f, std::index_sequence<n2, ns...>{});
            auto element = f(hana::at_c<n1>(static_cast<Xs&&>(xs)), hana::front(rest));
            return hana::prepend(std::move(rest), std::move(element));
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
            return scan_right_impl::apply1_impl(static_cast<Xs&&>(xs),
                                                f, std::make_index_sequence<Len>{});
        }


        // With initial state
        template <typename Xs, typename State, typename F,
                  std::size_t n1, std::size_t n2, std::size_t ...ns>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f,
                   std::index_sequence<n1, n2, ns...>)
        {
            auto rest = scan_right_impl::apply_impl(static_cast<Xs&&>(xs),
                                                    static_cast<State&&>(state),
                                                    f, std::index_sequence<n2, ns...>{});
            auto element = f(hana::at_c<n1>(static_cast<Xs&&>(xs)), hana::front(rest));
            return hana::prepend(std::move(rest), std::move(element));
        }

        template <typename Xs, typename State, typename F, std::size_t n>
        static constexpr auto
        apply_impl(Xs&& xs, State&& state, F const& f, std::index_sequence<n>) {
            auto element = f(hana::at_c<n>(static_cast<Xs&&>(xs)), state);
            return hana::make<S>(std::move(element), static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto
        apply_impl(Xs&&, State&& state, F const&, std::index_sequence<>) {
            return hana::make<S>(static_cast<State&&>(state));
        }

        template <typename Xs, typename State, typename F>
        static constexpr auto apply(Xs&& xs, State&& state, F const& f) {
            constexpr std::size_t Len = decltype(hana::length(xs))::value;
            return scan_right_impl::apply_impl(static_cast<Xs&&>(xs),
                                               static_cast<State&&>(state),
                                               f, std::make_index_sequence<Len>{});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SCAN_RIGHT_HPP

/* scan_right.hpp
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
*/