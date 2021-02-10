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
IF2jflMR0z8emLtZaK6DlpUxzXgv5nR3Ue9fyfft7pl5fBSHWJ1YW5/5WFsY022ymBQ4X18/oKeflV/bFJVUfPj/FVFJLEKpzosAyH+KfNhobd2G6UoZJwYIoKZ4XfSPsCEhoau8FpYE8X+prIxxcP8jxSVhzvLMnRafWIQkpjnDBy5tZIUo5W4MaSpcAoUibfLGSjn7v0zQ4rhJzsbJ/0dydtBufXiMnBWryxCqWqbKUDIlz6bo+S4+wH8snXeexSLNnfkl56TgrHdYLwUYTgTvkKFugwqEOCeqqFEWhlUasSqfQN5qOk89HoOjzKoxIqwWhPaTJ66KSSJs97EFEjm65WuOKbZXASVFTBari01rTfoGC7Pi6G068SA4JSiNPg/F/ScKvCmbK0yHYVUqQ1+9kIMcRh6/DTFQKQ8HPESJIEX/f/aX/8iTLKoJXOra6MpH+8BO6LGqStMjDrrZbXD0/ctsOa+xxCjQMJ8vGmwdWSzzVbujRc4cjQZrD4SFrhQm1GGyzB/TIzeGTkV6B6B2S9QL2hm+a8K7xb0nZoH9Q8+imzBTNVZhsvxe58znb0kgKvRw8fBzeatJwUYCqqPOZrc38k+vOhcjH8W5QMfnDnuLmmzZ8Ii6evKXUY0px+Z3o9V5BBxgNDRo
*/