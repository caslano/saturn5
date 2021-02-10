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
alC1tvXKwGEb7da+bD1YUZJwVbzr9Y8OXco7MpC8vT1y/TVzrCVZ9Mt3QTiLbpMsoW6WhA4vXgRzlU1IB6VR56JJClhAh4L5IrptTaPlPpVDE8f+j98f/NB++t2+XeMqSK/XEyo6O7o7iPdHnZM3+yh+7i9Bs/Dj/SSe7od+uggm+0j/lIyhNf3befvg6AcbVpWHxqE6eIP5q+dJw/DSRh2q/DVeIWg0tNiaF721/zSne86o3Ugsv8vI2zZFNNZ+zXnksPb1SGpjShrae+4BOUt6Wq+/prkFofIX0JZedU7eNz7lVhV/MABxvTYcDMa1hsGauOGMkC9OsFMci/3XsbM6EedfU2/MMkPThTnMKRPCRoc+Ppi/aE0JVAa904Q9i28wrMfKzntKh/pBZm/FqPOgIwKEaJ0mAV7PmUuQomiF0c3pvFwOukmLXKKJdrqP8rDje8q9gkYFVCX+JuwvchVHt+znDJo/CMJYscnuC3ZOZq5PCOj2X1OeG0wV4+zC+FDe5pHZqDh9NxieOmYBl+5VPZd7jBpdIIbTYDDZM+WgRj8cfz6POHMvO+tztCZKeF5Yu9kIETFvR7x+ibooUbZnIThL1qeuAYiqjlGcVnpl4+cblvi/MT3emJrJORC2ztkecjTcPmcBW7fr
*/