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
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
*/