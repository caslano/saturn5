/*!
@file
Defines `boost::hana::suffix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SUFFIX_HPP
#define BOOST_HANA_SUFFIX_HPP

#include <boost/hana/fwd/suffix.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/lift.hpp>
#include <boost/hana/prepend.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Sfx>
    constexpr auto suffix_t::operator()(Xs&& xs, Sfx&& sfx) const {
        using M = typename hana::tag_of<Xs>::type;
        using Suffix = BOOST_HANA_DISPATCH_IF(suffix_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::suffix(xs, sfx) requires 'xs' to be a MonadPlus");
    #endif

        return Suffix::apply(static_cast<Xs&&>(xs), static_cast<Sfx&&>(sfx));
    }
    //! @endcond

    template <typename M, bool condition>
    struct suffix_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Z>
        static constexpr auto apply(Xs&& xs, Z&& z) {
            return hana::chain(static_cast<Xs&&>(xs),
                hana::partial(hana::prepend, hana::lift<M>(static_cast<Z&&>(z))));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SUFFIX_HPP

/* suffix.hpp
sKt6f8LCfdciExTZxB0GLLWIBLI4Or23qwI7iC5O9Jkq+cjDn8ARlK1gTABTxDHcES7LOVrQUfbApvHqRa16zxqNQbQzM26RMowIY31xmQfd5IcdHmgGIbSuGBZBC/KWan3SSNCDwr+Wgq36v+S4QM0kPclKp5ejj8BNCqH6+EL7QBAFUdzr70rXsu8F8kfDWUNIcnVtuYheg4RrqAZAokuSdrPlQ2hdlbEbAMbw17XItIKmOPmQa50mKJ9oy7zYdmi6+x2hOm963tBUjBXASY5Vp1ygIoZSseFHm6yiL4wNGF0iINnQ0kN41wGxxPJUwH7nYc6D1GAOeeB3PYxnp5d/AVGMSH5CF+NmqTciSl3oFJkWG5ThlMkt3ZrcAGeAa4exxtRlUbavQ3uApmIIUeH9Uid3Bi3FY17qolLJHpIxZ03kU4wyzRXykbTBU7F3Si4L29WpAXYWlNEMdFlSj/4PI/vB4AW+a7Dr87b8Ng00wUmtv/4LAs8Eom+KKLUwj7c2FGf2NwX5lAtF5UVvGpdiUgZdyY6ECD7s76uaUiP6YwArFw6E82SUHg==
*/