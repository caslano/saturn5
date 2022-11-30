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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_UNFOLD_RIGHT_HPP

/* unfold_right.hpp
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
*/