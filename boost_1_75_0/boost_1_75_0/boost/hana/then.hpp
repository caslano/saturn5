/*!
@file
Defines `boost::hana::then`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_THEN_HPP
#define BOOST_HANA_THEN_HPP

#include <boost/hana/fwd/then.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/always.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Before, typename Xs>
    constexpr decltype(auto) then_t::operator()(Before&& before, Xs&& xs) const {
        using M = typename hana::tag_of<Before>::type;
        using Then = BOOST_HANA_DISPATCH_IF(then_impl<M>,
            hana::Monad<M>::value &&
            hana::Monad<Xs>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::then(before, xs) requires 'before' to be a Monad");

        static_assert(hana::Monad<Xs>::value,
        "hana::then(before, xs) requires 'xs' to be a Monad");
    #endif

        return Then::apply(static_cast<Before&&>(before),
                           static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename M, bool condition>
    struct then_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Ys>
        static constexpr decltype(auto) apply(Xs&& xs, Ys&& ys) {
            return hana::chain(static_cast<Xs&&>(xs),
                               hana::always(static_cast<Ys&&>(ys)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_THEN_HPP

/* then.hpp
fxqWeWP+Y1jyG+6U3MY0HBbfMQ2HJR92Sj+CjyLJ5WYvHh3ODZef7ALeayErG8GNUj4epBXD6wcpezQZpPYV8A4PmOdiLt4dTXDbNMId3AB3kxn38Uce90iMLZpKcTFk9s5ULiYVouyjVebICzG1XOwu/54DvnauPiAHP+6ZmovPRveWvhwDJ0j/M2oFZJAVV5yB/XAnVKckFaHrhoDdB4Kmu9hzz2GFmFL0n+bWWEnDlqzZ0hu4fAfKMuPloC7Ki1B1VjK6YT8nDqvv5xF/0s+qck6Rp/tzcS9nzocsNt+w5HRDnbGSxpt1vOArHc8ixstQ8W867jK8gY5n62L/1XhhHdeNwjp+JqJB9OnKDRx9yoeHxez6UUTbhylA293ST4G2D4kk/lk+Gz4UAm2lZ1k4wqS7jhpgX4Bdus6GjeKMkEkarI0t0sZ+ZYQgqzA4+B+0PZhbsIIbaLuMXTOq4YIVDAtWYb22y9gBo+q1XcYGjAJtDw7mFqxCzX2HhCN4rcoHQxRbb4imTOeWmcKQddWWqPcOmvVwLCQbU3kyEqhE8dm765HN1sCxydIonozNXw8BNVSPB27XKwRxz+B2rYcNXQE7Tly/Wu0fSVarsg+gBddZ2ciG5iwCkO9jcxbcYKh90KqXV/KnOWxQyF4t/7cBt5WYB9ykC/3KosUWmUOPBWi1krH7JHi4r85ubNKSULaXKTiYDV0GIUZv
*/