/*!
@file
Defines `boost::hana::prepend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREPEND_HPP
#define BOOST_HANA_PREPEND_HPP

#include <boost/hana/fwd/prepend.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lift.hpp>

#include <cstddef>
#include <utility>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename X>
    constexpr auto prepend_t::operator()(Xs&& xs, X&& x) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prepend = BOOST_HANA_DISPATCH_IF(prepend_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prepend(xs, x) requires 'xs' to be a MonadPlus");
    #endif

        return Prepend::apply(static_cast<Xs&&>(xs), static_cast<X&&>(x));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prepend_impl<M, when<condition>> : default_ {
        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            return hana::concat(hana::lift<M>(static_cast<X&&>(x)),
                                static_cast<Xs&&>(xs));
        }
    };

    template <typename S>
    struct prepend_impl<S, when<Sequence<S>::value>> {
        template <typename Xs, typename X, std::size_t ...i>
        static constexpr auto prepend_helper(Xs&& xs, X&& x, std::index_sequence<i...>) {
            return hana::make<S>(
                static_cast<X&&>(x), hana::at_c<i>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename X>
        static constexpr auto apply(Xs&& xs, X&& x) {
            constexpr std::size_t N = decltype(hana::length(xs))::value;
            return prepend_helper(static_cast<Xs&&>(xs), static_cast<X&&>(x),
                                  std::make_index_sequence<N>{});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_PREPEND_HPP

/* prepend.hpp
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
*/