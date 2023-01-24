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
a9D57kL/pLz54iEYxY6hLnNbUdB35kDP01Ui90dtfVjC9VTS20L1wmsL90oj1pux11k5JNsg+NGtad9vFcbaw2oG2Y3xIWrEbCS/QTlAjyJHyXpM/EwhxxBFj5MbRZ+Zgaf2uQunm2jGcfSRKk9WJNSHoJGwMTFatIwUHPTXlp0qJIpiGE6avQh7IfGZ2uyDK45r1EIzpnlo1OdhDuowFBpqlKyIFhvRyCgl0blDCMoBwwHRgcDBR7NPN/AHX6g/+6odBiqPzh1AyA5khn2HETOdD5erPHjLGrbEe+LklXZse5b8MmSmx0XwwIJh2rTOrPsdfLX5i6NLr40X0mK1chisubkivPzFkc1n7x50RScaZZzmxOvTLjF1+w5WfxTISwJ56601XisycxdU7K8uOrlHw3jxV+MnGO3XmpTNRZzPOjVftZnL7HV2fv2kn0bd5uH6+ZmmONN9n1H0QZHB31NZ6UR9816Zr9i65qhBMDN/FMXaq0mOLsdmmOMhJZX3JFnuvlN9JusPOj0rPtasvJTKI1ctstUlbq7Llk229KdT/E8T7PsBs5OqsUZ0Tb7c4V6c9J5K4/GRSeHtQdPRuVw1LU5TscRWs014uJCmNDXhiYaICEUlbgHyifgzK6xU8mWun76OGgC7I5YWOfmpsyL8oXT1RKJ0RdokiujxNws6+y5kly8/m1s8Xu+jRMWohU2VrToeo5KyFezd
*/