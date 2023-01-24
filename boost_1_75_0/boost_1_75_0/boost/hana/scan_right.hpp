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
VWFB7UZXj08W1CJ05aOraaUFNRdde9F1F11dqiyoMHSdQtdjdA3/bEF9i66r6DKhq0e1BaVE12V0Ta6xoLToOouuWnS51VpQ49G1EV0n0cX7YkH5oGs1uhh0VaDL12RBTUHXenRVoGsMJaCWomsXutLQdQtdVehy5QmoUehaiq5d6CpEF80XUPvR9QRdAywE1Hp0XUcXX4BgdAWhS4OuE+j6hK5RlgJqHbrOoqsUXfZWAmpi0Iig2ZYbpl15kSY+8Pu3LhNnvquEb0+NHDx97vL+02VB0xcrFdNnzVs0E/460fRonwHLIjA8fZ6Xz4DpI6TDh3osmcP9baEhPO6Cf21QOmr4pHHw6jN8W8tj+MRJblOGD4Uy0GK7+jz8DrewcR58ZpxqJ+S+cUby8N8P8m5Mbyrk+TTKG43bEAk5u0XycBvSxvUw7qRGeVKMO0XIfWeO5E2BvPDG9aZAxTmN8zA9eaM8/OeFqAWN83C9JSgv9yPKWzZnpmImHDLiUdE8M+yGvz2EbCElrc9bHs1VxXZ6gUVd/urVq+fMwt9ItONx7SxTzHYbPRS3Hd0obypuO6Zh3iSungrlCevyuHqJKC8X8uAjMG5z8Ifrw+15VOpTPslbiL95JETzz9XZXC+a8kR6lVyHtwp/ZyIX5UndUR7uhBt8Bo1y7SOgBiMD4BFBOuaJdBstKh4E3DVEgL+B6EFEguwopw8cjL+T
*/