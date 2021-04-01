/*!
@file
Defines `boost::hana::first`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FIRST_HPP
#define BOOST_HANA_FIRST_HPP

#include <boost/hana/fwd/first.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) first_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using First = BOOST_HANA_DISPATCH_IF(first_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::first(pair) requires 'pair' to be a Product");
    #endif

        return First::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct first_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FIRST_HPP

/* first.hpp
n9/vFCZ6u8ClBuyn+NaclC3F3Y0KNkpD3E7UOmLEqU42qY+y7ku6avOnkZZkyutlpv5o3dbJA2x6qOSHRanldhs+t43l5yi6cEC/znPxR1k4sqruQyRcv12OitBt3eDE64Zo7CuP0J2pr2q7XSDkfob3DIG0AVWkvOj64U9zQXRFATrEl+J69RSTdNI7i6lY5dj9gWqbzfifx1sOka4+bnC4t/zsqQlSwt40I8Y1ZMczp7nl7kxi1/rD/oZBCVAxuJ9SSezGG/1qWK9foSV4nZM/ifg+fUO2o7clN+Qg3saPh8hGZXplMzlUoCnk9Pn5FNxLTc6aRMk78Mii9jJ7Jl5BCuTi9QC2neuJN7xqjSSaxLvC6pL/06SN3pR3OFS/F1f7tZEB7zicaTwYLui7WG49rFOJWXIsTVCwFccC2DhKEyfRTCIbKcpOWDaOSeTQVWuMu0tOKbBo/OPpNELo3nYfYq53yd690I1vfOSWiQvBjIkxY4l3sKv0JNss8Sa/0b14rgMQKqlhuDnlTGVha1I6lrxdKDj1KjIJf8SFNpSYBt8hkk9yMvrMpw==
*/