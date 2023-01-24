/*!
@file
Defines `boost::hana::monadic_compose`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MONADIC_COMPOSE_HPP
#define BOOST_HANA_MONADIC_COMPOSE_HPP

#include <boost/hana/fwd/monadic_compose.hpp>

#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/functional/partial.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        struct monadic_compose_helper {
            template <typename F, typename G, typename X>
            constexpr decltype(auto) operator()(F&& f, G&& g, X&& x) const {
                using M = typename hana::tag_of<decltype(g(x))>::type;

            #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
                static_assert(hana::Monad<M>::value,
                "hana::monadic_compose(f, g) requires 'g' to return a monadic value");
            #endif

                return hana::chain(static_cast<G&&>(g)(static_cast<X&&>(x)),
                                   static_cast<F&&>(f));
            }
        };
    }

    //! @cond
    template <typename F, typename G>
    constexpr auto monadic_compose_t::operator()(F&& f, G&& g) const {
        return hana::partial(detail::monadic_compose_helper{},
            static_cast<F&&>(f),
            static_cast<G&&>(g)
        );
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MONADIC_COMPOSE_HPP

/* monadic_compose.hpp
Jx9mX/uQIddN+wJxy8JJQTztvgLrA6zDtJIrT6EWvN1yzGXx3eSONXm15fvc3Ra2VtmYQ+2aL1xXwSpXAkCVwvX0lX5snP4FPbhTLas2prCC7+p2DtTOEdtf8vLxgsHtCQb5axzUWFY2/Srv3aZqLtgZLa1Hq2bNkwtiCRFkTXdG1+crie3d1WV7DiFlR9JO/PwQEqLn8wMZSsVKDe+y67TEj/kv6S0VM3n80M5ZGVFCV5L+7OHq1BTjXGfu7yIpWyqY2JOICzCvHi84akGOHmoXyC0MoRUk4prVTRTMjUUW9Mw0AwXEVRcERs9yhw8KBl2s1QVOpzZaDoKPdAPboAId9jsmV5/42le8JhkxP5RT5u4vUFvWL3nvKPG1v/6jFxg17p2+YLAcOF2XuiKEFn/ox/6do0FxpSnVPqrrkTaEe5o5LSKy6Z38rySW5cDf4iMFyBZkHMDTO2eY7ogyRMM/YDQbcPtJezHwl/JU8dhXgpdGKZ+iG5Oeqhar4TTUtU3pKyJW+ksxmOeIf6Lni3FDekv6rNIQ+nql2GZk+/2Ta12V7MowK7Z0DLX2VIurl3Qh/HloRhhCzOhtzHLPk3B6N3G9MrUz/VCuaeM0YpRpiZVZZN3SO+KTbA4gSe0mab11ckgqR7J0c7HHDwVeRbcPE78mXjC3tytbxjz+llPcx2skvsffEMIyYpzr4EYsEMWUp+UVr2623A0X
*/