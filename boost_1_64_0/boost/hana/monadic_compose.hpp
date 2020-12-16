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
36ZKttHf9g71+6v51jxffUPdQ+Un1ML6qP9E/V3Z60w0bIhvf2hxjibgg4nBIfH9mPavUwFjptsTk1cixvdX4aUN8MjnZeqYsgRlg6uoss2ZshRlC7pstMFKdVmOMnFVU7ZNRbodhSrT7Tjc39QmG21fjtR+odutvakA2377rf422dhW7GxiKlTAcVUdJ0EWXrMqQz12+rvJT4JdgMFe3cS+0i+RBGvjZJVXFmspfbtW+21lwOBMjCx/wHBeu/2WrnpFGlf03cTI0mpqbJurejxqfG9eoHOrHOA5HireHdgjtuP4TeSFGL9oYMaYinRZg3of0GWHvEyPzcPV+L9YlUGonuJR2NRZwffxSwZ67BlGXWcVZc95qa2jH4v19zV8/+nL7Xf9UKy/X4nvb321/a58Ftrvj1DfX2+/K/+E9vsjFT+/zX5Xvgjt90cp/B+y37XfgW7ro/H9RRp/+649VLpD04/HKFzf4mVHZ+16uI/KpfFtXobvFt/r2fcnd/BjDn+upfFYNb74bvjUDJVdc6APHm7bjOsWfrdtvpXFpYbQNFqVPU61+TuszDT6Fqas+a5TZtqMOs73JxP84Hv8+zmi/2sLr6aK0X+8mt/v8TJD35Z9n5Ux+s/5Af/+ZIL/gPP9nP7+RDWXelwQDmN4fmLnxL8N2nVNfNd2PGiR2c+21H6E73oNs2/ja5lvJxic/Xay/XZOwV2hvgGfofMktV/pb3iiA/3j/Pu1u+8n+PfrdN9Pmnm8iZK19d6i49hvKEdQvt/+UJcZ91vz/dm3RN/1d7imw15zYHCdB41lvaflYXR8qAzahthldeyWL916vq004sup/U2PVlFXsYkdh3HQ37QVFEZipFJF23h0z0aZfUcbmtw/z8M3ZbGi7SFXg0SGVxbSxHPDXGnLHBTpmDAvxu+BV8qiSD390eTseaXizbVkRXqhSjGMrDywGV1LK8nKi/kAbU4fXb4qgytX0rVH61h0qX/lmlw17UA/tVUP0gfrfoBXdB83tIyCfphvGxiY6ZCVmFg2zwd+1b01zy+kTg3f1nk5vmtLH953M1av1X1dtaF4zHgbeDTEfvsh5qeNVJiu2G9vRF3dAGWwstX2AXykLcCATv/+aj22J+j3p+L385tbw639Fv4Av/tRS/3uJg5dgRxb9yM7MyAnEyY1qx1ccy0H7syJS8CtXcHhYDDZh2Nx9QBn7Nfm0jW5kzjcpen+4boc7tJ0H3x9wM3aBxmoDu5lNwCcYyPoIryzgXvNDS3cfh+GYv297kaAIftVXUZxAhdugjJmw2oaQvg/f1OUz9gNuziSmxsYh8KAyn99C1PuUiEaL7sVypktPjJrLfbb8Zlbz8AEJ3pj+4/b9GBWyhA24gaqa4+4nQvXb+/49qbcmAOacor/+Nc7oFzbBOoS+n7xGL53+x19//Cd8F3ZMRpE9vtP74zvWDGmszRf37yL/j53vnbvZsrYSPK2Xf0eqlyRd3lg8Z7mO1jT1KGy3XuZMsgB/bF4+71R1tk4muIubtZP74NybmvHyqb3s2XmvGRlVzyAlYEun583Laiy7sY21MdE195XnUJ5Gy/TCNJd2bFllKm7w/As1gJc8w/P09g0D1ZlE+UZ81Tehz+o79yGmb2zXRwOHH1RGge1Xwc6X8qGyg+7CE8E8/a/pPIJj3cQ+rMt0zd25lObODEwqqpIZQlVvVmzbmymhsP6nkibVHq1DIU00Eu43UzWrQ/6BuUGcOrlwvfqMpENFJAjU8+QG226KDBdJ+y7DcdRCSj9y9hrMh3qjVVy7dfWOd1YxGkZ5zhXKOakYmVGs+8ffbvSiZcQ1VGWF5kYnz9NqY3O+VbXUPZ0BDI=
*/