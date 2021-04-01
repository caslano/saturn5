/*!
@file
Defines `boost::hana::ap`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_AP_HPP
#define BOOST_HANA_AP_HPP

#include <boost/hana/fwd/ap.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/applicative.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/variadic/foldl1.hpp>
#include <boost/hana/functional/curry.hpp>
#include <boost/hana/functional/partial.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A, bool condition>
    struct ap_impl<A, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    //! @cond
    template <typename F, typename X>
    constexpr decltype(auto) ap_t::operator()(F&& f, X&& x) const {
        using Function = typename hana::tag_of<F>::type;
        using Value = typename hana::tag_of<X>::type;
        using Ap = BOOST_HANA_DISPATCH_IF(ap_impl<Function>,
            hana::Applicative<Function>::value && hana::Applicative<Value>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Applicative<Function>::value,
        "hana::ap(f, x) requires 'f' to be an Applicative");

        static_assert(hana::Applicative<Value>::value,
        "hana::ap(f, x) requires 'x' to be an Applicative");
    #endif

        return Ap::apply(static_cast<F&&>(f), static_cast<X&&>(x));
    }

    template <typename F, typename ...Xs>
    constexpr decltype(auto) ap_t::operator()(F&& f, Xs&& ...xs) const {
        static_assert(sizeof...(xs) >= 1,
        "hana::ap must be called with at least two arguments");

        return detail::variadic::foldl1(
            *this,
            hana::transform(static_cast<F&&>(f), hana::curry<sizeof...(xs)>),
            static_cast<Xs&&>(xs)...
        );
    }
    //! @endcond

    template <typename S>
    struct ap_impl<S, when<Sequence<S>::value>> {
        template <typename F, typename X>
        static constexpr decltype(auto) apply(F&& f, X&& x) {
            return hana::chain(
                static_cast<F&&>(f),
                hana::partial(hana::transform, static_cast<X&&>(x))
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_AP_HPP

/* ap.hpp
zFrU1klT3KbP8ZP/b4Oqfqb6zuQpKRQaaX1ndyTZDGU2cU3X5gRivIqrzHpKoUXCV8D/65yh4JQzFX78BYvxJl1SFm5DBHbbi5R1Zg2ow3gqG/G2sub/2D6+zYKn+DB40wTlpHusK1o5+u09zOabLFJGT/pQA76MMQA0YdjWTURoDGQglt8X10ujphCwetJcxvkYajQQNx2tK2Rxatw8MIzqGQP22n8ZCQuGEe3el/nedFVPJYKZvfZn/rwB4IPQceTn8X8LLcrcnlfz1MRfWFEagDFncCEZJwOI3GlydStQLVY2dJeKwJpxUzI7x+BeFGP50vgGP3T/MRd9250zEYkJs0iNIu2Cs5XFXJNwO9IINeCX/X6/YzBY2h5pfE+nU9Gg4BirHQSKUo3F8sC6uBXX+VH0z+ED6OYNbC/jv6avD+GZPHuaOcZ5U7IxYAc7jLGa15QDTUzhfeLN1PYKD4gAstd58aemAaALf9TAhM06tiNqd57ZLumybo+hwigFOYdvax6v6xh2MtPQ1Nc0Tw1SZ60Bogr7fwLelavac65By5Dzcdfhwi7euw==
*/