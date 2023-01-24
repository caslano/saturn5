/*!
@file
Defines `boost::hana::reverse_fold`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REVERSE_FOLD_HPP
#define BOOST_HANA_REVERSE_FOLD_HPP

#include <boost/hana/fwd/reverse_fold.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/fold_right.hpp>
#include <boost/hana/functional/flip.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename S, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, S&& s, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                static_cast<S&&>(s),
                                hana::flip(static_cast<F&&>(f)));
    }

    template <typename Xs, typename F>
    constexpr decltype(auto) reverse_fold_t::operator()(Xs&& xs, F&& f) const {
        return hana::fold_right(static_cast<Xs&&>(xs),
                                hana::flip(static_cast<F&&>(f)));
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REVERSE_FOLD_HPP

/* reverse_fold.hpp
3mwdsfeevJI+U5G/t/LiAcPuyI33Lm2spAenxZRd2L5bdD+557Bnxypp97EbZO9f7hBtGpHWsv+NSvrnpy/7z7i9xDBgpfPu395X0gt2Pj3UIkcjumja0nSaUxXdpesUj1V3kgzP/rqWOnBgFX12bdq6S2FzDQ4Ts6+OmFpFDyo9uiNm7AqDdPzDA+tjq+hcTduYaS5JhjPWV5a8T66i+z+/vuXc8i2GxNLD67dkVdEZH5amjoyJEaE9d+vZbBW9aNzz6Ctu0aKIZ6FrIu0+0/1vtwsdHbLN4NVnzOu9np/pXwYUxk733CEK7ep3wmLyZ/rxUP39RX2TDFP+8Gyxf9Vn+uLsv66svbpXxNSumjx//2e6X+2nZpc/J4pWl+Ux8zM/07kLXlzx3vqd4de8qbsPsJ/pdTmh3tcO7hRF/qnvYd2smnYrVo37+HCvodp5Qvohr2ra+m685wzVLMPgkGf6ZSHV9NOFZ84+WrrPMGpG9YcVcdX04GOT1k6YojSMsTromXq0mvboMalZXs1+w63zYxM75FTT8fv7rM4dsl5k2+HutAsfqull++bTV2r3G/ZN1DzY27qGfuAv1UYI14lW55rCfhHX0E0uqosGSvaKxt4M9ng/twbNL39TQMJWUdoLq+0Lv6uhR0xX+RuOLRXNS3xX6Hqqhr4/+uXNqxZK0efM0MlNH9XQy5LWB/kW6A0xWusxfaxr6X2r
*/