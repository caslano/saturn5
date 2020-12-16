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
8P2s3hSeWcOCWyIn/nBFLY+drmrziXabQweu8yRSD8jppp+YmdQP45GTEqYw1k2YRSyH5HkDX2CJC3wIAy7+a3xrm+Y7cxzf4SLK8BglzHKNpky13Ewq++QLZp20Ct3QRVOEQmeTw1Z8/oY51kmaumkKeSPnmHotDtTMtw0v8nrYKoQRTGDY+LXNSELKN/7wwSo+Xdo2zwNiYcHlQTnCJ9MndXIRo83faVdt2XvaeGcTvoQ4sj1MMBz9QFixVMNBXx/+6Laoc6S7oK5hF0dZHLsxyS1r0AqGe0j/bNyAeCBvu69Om4BYnsvd8LY7n22pGJSnItYE5Qt0MKS/P6P+XlsL9N7SHn1uhx27PR/x71el7/RsHL27N+7srKlzNXq7ibDp71en74SNvtOZHwJQZfio79F3dfanvhK8PgME56lRN6fv11LfEXp8HBmyba8pu7YsQ8Tk8QUXfr2C9/EL15BnjAsIcpmdm2++f7H+TgF0zfcv0XdaJDWNL9N3WsixziJWmcq+YpZ5fmXy+atUjvuXMarpel8z64m3yQy8XzfL6Y2ypt/fMMvxTlmD+5tUhqBWaU0hVgj74kyXf4vK6RaifOhsjuH+NpWD43Uhw/2ddtkCooxY+XcN3lJ1Vv49Kke0MwDieQLUtL+v2lbA6Y5iu2jKLrTKcFNAl/2AysiKnI3deU3zh5omYvCRiQGNN3j5IyrHnTsMYDZvzzXt/bHZH3rSrin/SV1OvEAILkKJeflPqZyknUSxKf8Zlc8dRRB4vQUui6zp88WR8qbdPzfLsB9s8P6CymB1zuN+KU2OpvyXVF6UGMD5uniOlf9Kl1PXKCDsdlT+a1P+7KPz0ULmI5CfwfyGYCAh5XGwrjwBgcC9kjk2P36r5mhmgy/N99/J78DuiJnYxLVGiAs40EFgLPt2h6uIb3J7qOMHPn0NfDPtQpSRX+8HQi8OB1y/Kjtg+AB+JhL5WNgiP7XqOCtaBfQ5waPMd+Aj14sSu8KqyaOymLUB1IrOp3ndw04RBggccyxKrdHKSQ9Y7sNOkfYg9jPE+BA0zuLIPhJG0Ro+UHsF6cbG+RPHM+WkNhww2N7jGWgdMNbT7+yvm7ZziRwiOR6TU+9Jgxa8a/NzM1O8emdN0XrolVj9ySop4XkIPYvH2i0qe2UvaHGfo4/MGHitnI52Rd9E5jrTXrsLr3MoTqpCpAU3knsv6reM11uxZoiKhOcpszyAK3fV4gA9AqXuGdhXMlEct0GupuiunuqwfkWwcUMvdS2RPEnBuspe6XNYz8WZVwpjOkDiexU6QLIB8gNJDZacPlYVKHsb3D9a8X5Mu8i070QBLPOB4YLvdJV8PsLoN+QmwalFgRoVOStxNK9lh/Ye2h58c4fRquCixL0y6YbZ7G0uEzTkxSH4MwYtJHAIERhc+IWOW0DXlte3V2q5MXB0FW/vZ3e4zEQJxgkWFSx3NaTNGfV5g15uQTRxLclF37YpDkO/cE5cZYLKZO8ujzD8crjlZIdIf4OU/H0gouFpxZJcYYxDGJSlW2AeDXuPQoY4tV1ge8EPt3iTRTb2F0WhiKzVoifuBEAKvMOcrGrnNG9njm0dRN5GngVEjJsNZe38Bqd7JA8TJIJJCmpnb3vEx33RaGdsITdN4kVhIIj8x4aCp6q/nQ2OJ7ScHAc/eaTRYNNCk04KBmKx8e/EnN97OY6puLDTIM1zPIHfXz87EgMJWK6r8Iw1dFuejeoqqt7KmTLN6x+BCkfOlNSr9SLr4JziU2TQy6wsKBw8kT8aizJeRy4qPBcs068fIFVTmDhc9uo8U/h7dWtxgN8Gve0tNXMWFa+es9rheh1HJpGb+DinavIEzCQ=
*/