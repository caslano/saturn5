/*!
@file
Defines `boost::hana::unfold_right`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNFOLD_RIGHT_HPP
#define BOOST_HANA_UNFOLD_RIGHT_HPP

#include <boost/hana/fwd/unfold_right.hpp>

#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/prepend.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename S>
    struct unfold_right_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unfold_right<S> requires 'S' to be a Sequence");
    #endif

        template <typename State, typename F>
        constexpr auto operator()(State&& state, F&& f) const {
            return unfold_right_impl<S>::apply(
                static_cast<State&&>(state),
                static_cast<F&&>(f)
            );
        }
    };
    //! @endcond

    template <typename S, bool condition>
    struct unfold_right_impl<S, when<condition>> : default_ {
        struct unfold_right_helper {
            template <typename F, typename P>
            constexpr auto operator()(F&& f, P&& p) const {
                return hana::prepend(
                    unfold_right_impl::apply(
                        hana::second(static_cast<P&&>(p)),
                        static_cast<F&&>(f)
                    ),
                    hana::first(static_cast<P&&>(p))
                );
            }
        };

        template <typename Init, typename F>
        static constexpr auto apply(Init&& init, F&& f) {
            decltype(auto) elt = f(static_cast<Init&&>(init));
            return hana::maybe(hana::empty<S>(),
                hana::partial(unfold_right_helper{}, static_cast<F&&>(f)),
                static_cast<decltype(elt)&&>(elt)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNFOLD_RIGHT_HPP

/* unfold_right.hpp
H6NqqjoHOVQqT8nfmMl5EPAOIBeGYd+85lYK/T4Ew6thqVjQwKf8COKNbfUnukvHUk0hHgdrgfIYCCeDTxCs16dDk/eb8yl0f7KWfCrianOzf6XXkEz46sR2aJd1b8Ht7DEqnPEFlnbhor8c6z5IQRpsyv51ijtoct8Cdm9Qj23tCNsjoMY2w7fQBmuBbwlRa7a8Od+8FTKl7cOs4CADm/AI74mgw+lYPb6SU338pYhL0jHayGosLVLVIX4LrAVoSg7CHoBD/DqAKxSx8lwcxMBTLbkf98IsphdEBG9Kw5NzcQmmh9Ya3E5D6X/F8N2HmGEtZoS8Wv41dymfyapPOpzSAH/nQ3D68fu1oDuUNg3kpU0DzP+u72M46rovdb0/iXurRN5XETdX40+AIbTiYNKQDg++rpITVkPBfOv574KRvcKNaTVYINhu/GO3jA+4cfx/iHsX+KiK63F87+4mWWDhLphAkKABgkQBDSwoIUETYENQAxu22RAxwQem28UHwl7AR0jiTWwu1/XRamtbbaVqv7ZaS6tCUIobgnkoQlAqsWCNJdWJGzVATBaJ2d85Z+7d3YC0fvv5/f8/NHfvY+bMzJkzZ845c+ZMD38R26pz0KOc1hrA68crVhuoNKvNQYu4s1k3ik6vDcO7/uAwcWd/9QF8yUoujXKOF3GFnbcQp9gtI8Sd4eqDlDd8z8hi1nVU0L6XvElv+yox
*/