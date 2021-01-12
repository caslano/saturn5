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
FQjVzMxSY8+1Tr9kGzRAbN2DAGz0aU4UPLxRYoxy7SO64yw+W8ZmZPvKe4x8whKRT3j1SAKGdic6fVhUOJ4XSprBoADTQNt2CVe18Y2IJrWGJ51UZZrvnUXR1EuS2Z3iR9GbMzBSpxdzd3DAczANsEwrcX9/gnEj1j+Md/r2R81q/46zlDTOtV5wnf1I4vp4Ri6TlJJJFhkeWcgqoCpRtUGuaXflaGZQzKZikj3OHx0ROXlE
*/