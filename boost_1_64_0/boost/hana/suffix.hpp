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
Tb0ghtRrsg73wkn8iLbK8QbkHCa7JZVU3vtP/TjaQpZlrRRDxyuR/N6pTRvFlgIXcYL2qEzesZbL3vF2iSv97sFBcHXZRtHHMLk46gyFHMW86wcrFYsLIYzYIj/qS6E9HGPmqJzbNn2jddNwVlpoVgD7Nu/BlP5Wwoiq95YdPXBqR/paMXacWS2GYABMODMU+6dO1oJj1DGKvknW9Db4eHWRF3BaQlagPdAswnjd/XZ3uvVtzhunBPwMW260O+T+Xe5FdB62yleVcJLVtrRa7qxlvYjScxFwQfkQgAHzVhJfcRd2it3tcfHczNh5+iFH+wlDr/AjFlTmrY0UvZaGAftxqd/0BZ3qTGd6FQm3Fmw1GwVtuG8atOkC7X0XaO9FaW9jhs66plVAGzSPkRrHa4/Snl+bumts2wLtqH5k2fc/L9sxKP3ATKNkpWsLDKiLoI3snvncQXmMZo10um1Fj95EUbuGOZXwTG8RE5XfJpdO3sQJo/7/t3gxkQ2D17QDl7VQc9n3w49Un8Kl0C1zLbWFDeUQ9uxQEl7OJghmWe7zJnJtK7kYan6m3PPOkrtVyP3DVG7nfKXlcKbcW50l975Rbp7H/iVEblOzRltedb1ZKjdO4yy30Jm2IcHNZpb5MSqz7hkfrIaxlXMvsIAi0IUvaz9gfKFeO74pKMX1ZDP3/ydUpnLMhqx7xvX/+/u6f8QVxb38pXQ/6VhfSVnpnqPcqKFlWai33ffwvFgwjgrYtu+d/c+oPN4FG70S2lYL7aRyo2x7l75Pm8Fq+d/9GYlbofIbzqTrmkHWzf8+v6I9YDXLvc7LqFzNeCcbUdfqf59f20dBLvolULlKh3yNdWu6epnculD3cVbkVAZH+C1QmX3HbO99Y1QX7i9At8Hxq8ekrDgjRpcU0RcUjGDVvrzM7egH45Tpm2LTjSrlsl2TraBdvpBj2CC1E6ouN+9ZiFlPH9RD93YP8TOY23Iv94rSlutqX7daciIHuXaLqNuVk4CbdEGMx+w1wEZFbXI9nDFS2SUQ60pKkZ+jzZY7e9dN5dYGfH6ZeSzoprQcn182x3zCWSH630Gu5W9cHdbYmL89nOxmMf/yN+HZcXwWHWdA+5jB3gfYC1cP/YwfVqxVAmSSs/DPwQN403poG9JdeJHuLpZQXi/RXXSRrr1HvaZFwoe401XPzi+PfnUXhD7n8mR3vU2eg9Ru4JgcTKW8p65jxChC7Pkrhc2nhmnrxKBZasK506nN53KUnkvWVu0gOlrP2RpckXeyqNdXVjqp6mDvS5AJk3xj7aReI2wtZKfAMpJSsSQ+ereOWCHze/7j504wuuu6F13djQpo4t6GcYfzFsyKPGB4zrzXDyfnUCBK3oroU3HfKQ1a7uY0e5SmtG4gTv8hpYnti/G0B/m8fErK01n6gZn3EVCWz+2b/i51IKG5Nh6H5+WyPLfvKci/cJ7GONyX/XB6Xi6I0TbypkU6rJTmgnhHeU5eIMQ8udR2blltuNJGs/FaTXK68uB7/9gzJtjJIfehN82SA0xH1q19xMSldXrWtH0vBe+Z5CPD6gSDF/ERnjfx4faN6a2s54wJ5LPEA9jHmJOCv2Km7oXVzjG8XKcdLjG+7/7MCfZiVbtOer24f5SwOgvnyaINnvV1K6pqEP+tfQGvEcNaltbiP8Sc9fhhhGUO1+RbXCuUodk5ruvfhucXJ+s9IOjhc8QxhJnSax7vv74Hz+8T5ezi9RfFeHvcBcO+spuvr3AdfRkdM8cGZwL6lMVrmRlFQyF8byv5TC8Nr3SLV1XwkqJP5nT9/Rjlu13vgj88vCp7lL0m0jkHz6eJHn0+jBhqbwyxf2+RYPQyfvdoogc=
*/