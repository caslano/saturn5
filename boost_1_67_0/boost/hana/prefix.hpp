/*!
@file
Defines `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PREFIX_HPP
#define BOOST_HANA_PREFIX_HPP

#include <boost/hana/fwd/prefix.hpp>

#include <boost/hana/append.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pref>
    constexpr auto prefix_t::operator()(Xs&& xs, Pref&& pref) const {
        using M = typename hana::tag_of<Xs>::type;
        using Prefix = BOOST_HANA_DISPATCH_IF(prefix_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::prefix(xs, pref) requires 'xs' to be a MonadPlus");
    #endif

        return Prefix::apply(static_cast<Xs&&>(xs), static_cast<Pref&&>(pref));
    }
    //! @endcond

    template <typename M, bool condition>
    struct prefix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr decltype(auto) apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::append, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PREFIX_HPP

/* prefix.hpp
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
*/