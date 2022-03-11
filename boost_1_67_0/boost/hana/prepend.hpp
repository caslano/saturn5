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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREPEND_HPP

/* prepend.hpp
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
*/