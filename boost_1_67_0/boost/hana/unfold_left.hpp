/*!
@file
Defines `boost::hana::unfold_left`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_UNFOLD_LEFT_HPP
#define BOOST_HANA_UNFOLD_LEFT_HPP

#include <boost/hana/fwd/unfold_left.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename S>
    struct unfold_left_t {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Sequence<S>::value,
        "hana::unfold_left<S> requires 'S' to be a Sequence");
    #endif

        template <typename State, typename F>
        constexpr auto operator()(State&& state, F&& f) const {
            return unfold_left_impl<S>::apply(
                static_cast<State&&>(state),
                static_cast<F&&>(f)
            );
        }
    };
    //! @endcond

    template <typename S, bool condition>
    struct unfold_left_impl<S, when<condition>> : default_ {
        struct unfold_left_helper {
            template <typename F, typename P>
            constexpr auto operator()(F&& f, P&& p) const {
                return hana::append(
                    unfold_left_impl::apply(
                        hana::first(static_cast<P&&>(p)),
                        static_cast<F&&>(f)
                    ),
                    hana::second(static_cast<P&&>(p))
                );
            }
        };

        template <typename Init, typename F>
        static constexpr auto apply(Init&& init, F&& f) {
            decltype(auto) elt = f(static_cast<Init&&>(init));
            return hana::maybe(empty<S>(),
                hana::partial(unfold_left_helper{}, static_cast<F&&>(f)),
                static_cast<decltype(elt)&&>(elt)
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_UNFOLD_LEFT_HPP

/* unfold_left.hpp
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
*/