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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_UNFOLD_LEFT_HPP

/* unfold_left.hpp
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
*/