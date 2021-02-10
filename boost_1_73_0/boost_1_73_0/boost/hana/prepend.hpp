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
GPVzjz0yRA+j83K+UhNloQCYj4e8YOnyF7uNkHoMau2HAAmo5XTgp3SH4ZFNPLmmgCHk6jRl7yzlvOl4CTD5gL01KLBa9jbhDqDXCgMjsZaHQR0SuBO8+hMvF5jkBwZ3G8WJkpAe9DsxbP/PP+tDWwUvq7fkJ52sJ3/CJtJZpH0MgiFu23xBKYIvaAJu8RLELERBTDnvJP0VJfzEzAqicQ+6I/Tek9PAEU+pbUDmFL7QKCym1MUmyLvi000vwpKN8z1y/HZXlCY0tE83sZ1t4u9ZlWZBsqJ0e7bPaW6QxNY4FzOgRpswmNZpOHRvSY8UzTMJ49YPgd5Irkel45YCbTid0UmvZ3jtM31ynAoikpLBYjgnQOBsvapbz7XLtV3aOJHhDtJsoqU6Wrqhn+JtZtmw7IpbRPbj3Nu59hrKhmBfB9btWwjKVW46avKsewCMbFv+NHbaQkdrOUp/xlPwe+3vye81HqbPFxlAceGnhbMj/CiiyKOmkRPa6F9i1SXlcll7ymIX4Vb/TLkOyZk425PZhYwEV3+5imIvvieJ0B5frVHYsRPcU3kD+O9SN2og6ZcD2L04M9go2yZkzMflG8d2E1kyj5Zk9JXmp3KG7JNfRTgGgnQ+dGWqQi77H+tIxQAdnp0cPm0/Bamb
*/