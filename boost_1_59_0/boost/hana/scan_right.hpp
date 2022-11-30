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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_SCAN_RIGHT_HPP

/* scan_right.hpp
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
*/