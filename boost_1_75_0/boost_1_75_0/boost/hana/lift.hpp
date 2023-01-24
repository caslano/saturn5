/*!
@file
Defines `boost::hana::lift`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LIFT_HPP
#define BOOST_HANA_LIFT_HPP

#include <boost/hana/fwd/lift.hpp>

#include <boost/hana/concept/applicative.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename A>
    template <typename X>
    constexpr auto lift_t<A>::operator()(X&& x) const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Applicative<A>::value,
        "hana::lift<A> requires 'A' to be an Applicative");
    #endif

        using Lift = BOOST_HANA_DISPATCH_IF(lift_impl<A>,
            hana::Applicative<A>::value
        );

        return Lift::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename A, bool condition>
    struct lift_impl<A, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    template <typename S>
    struct lift_impl<S, when<Sequence<S>::value>> {
        template <typename X>
        static constexpr decltype(auto) apply(X&& x)
        { return hana::make<S>(static_cast<X&&>(x)); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LIFT_HPP

/* lift.hpp
SwUTorJnfVh4ZAPmWrgY3p+/1mD7XuEfZqEvhMhnKWP56peD719zCvtYHkrHn1nEyomN75UyMrPYe2fmKzGZYqeEg+/ODhUnu3BvT6Y7jjzEAPjL4estnjXgTL4fyyh2Y3nOp2FYXIHL5DvsnO5Tj5l8XdXb939Fvp4YfCD4gJx9mI+PD0ewyO3iJ3z/PTtN26S9ez5SVvIw8UmxzGjOAYxPx7kRqifwjHVSRBIza818t34s+vP9nYy78TTlKOFn5CtLjH87BHf8mPkaEMy7IAEc/dshEcT4pOjORrO+c5oIyZ+J0J1FutFgo50OnXE+WVFHEAxzgQrpy3ELZfa5YA8Q9nky+wsy+3yZfYHM/qLM/pLMvsHXY/9IZsf5CQ7mAnkbsLvlGvfD6vlch+H3smKKjQ73uUz82ZbTd9XeEXhpj69q7l5f1bLlZPru9FXNA7PitK/qo9MU5mvwX/KOr2oXmPkVvqqvwRScovBDj3u+07ZMpPmTSGs5mBnCLtWrVI+AwVKdgDtYqhf0x7phwh/rCO2Gx7t3R41EmtPMEi1mlu40sBEGPUvPc7JYm5GlaR34TK+FyofnHCGMHS0Qzkw2huFtworxuA3iOm3CbwjQFmvIZolaG4uw2gBL2BDIc4jTxCKcuSzNYGXJOgdLshSyaIMOwzu1thKMY+MW+CWiFojhvgEbfg4L4/NmBWnw55CO0+7Ac8JWh6Eg
*/