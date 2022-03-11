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
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
*/