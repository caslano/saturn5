/*!
@file
Defines `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_HPP
#define BOOST_HANA_GREATER_HPP

#include <boost/hana/fwd/greater.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Greater = BOOST_HANA_DISPATCH_IF(decltype(greater_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater(x, y) requires 'y' to be Orderable");
    #endif

        return Greater::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond
    template <typename T, typename U, bool condition>
    struct greater_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less(static_cast<Y&&>(y),
                              static_cast<X&&>(x));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater(hana::to<C>(static_cast<X&&>(x)),
                                 hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_HPP

/* greater.hpp
6aifGFkKHHFCkzZDgh/oP2tskCTDIXUatOgS/qExYJsEaQ4oc8wpfUbM/Mi1kXWixMiyR4ESR1Q5ocfwR/96QG6aRZZZY4cku+Sp06DLgDGzP9Y2tklQ5phT+sz8RHuIEqfAEVV6BD9VL3MssswaOyTZ5ZAKLboMGBPuGRNW2SZBmgOO6TDzM+PxM3kg9TN5oPAzfadNj+Dn2sAca2ywxQ5JMuQ5pEKdFmMWfmFOsMk2aQ4oc0qfmb4csEKMOHsUqNJm+pf6zzJb7LBLhQZdBoR/pc9E2CbNPmWO6RP6tfOAq7JOlDgpsuxR4IgT2gwJBtrAGhskybBLkUMqNGgxIPwbc4AFllglQZocBxxzSoc+od/KCVdlhXXipChQpc2Q6d8ZF5bZYIsMu+Q5pEKDAeGh9rDAEqtE2CbHAcfUOOWMDqHfawcx4qR+L0+/lx+GTP9BO9hgix0y7JKnQpfwH9VLhAQ59jnmlDM6jIiO1EWWElVOaNIm+JN6mWORtT+p/0/q/5P6Sf5J/RT/JA/U/yQPDFj6szaQIMcBx5zSYeYv5gjrRIkR54gqPYKxetlghyS75DmkQpcxm39V11/V9Vf9/av6KP9Vnv+qzr/qNyNm/mbcWWGdKCn2KFGlSZsh03/Xfxb/rh1/l/O/a8PfteHv6v+7efh39f9d3oNzBAsssck2CdLsc8Axp5zRoU/oHOcI5lkhSpwSR1Q5oc2QuXOeI1hjgx0y7JLnkAp1WoyZPdc5glUibJKgzCkdQqFzBDPMc1WixNijxBFVmrTpsTylDVPawNaUdpAkM6UdFKe0hQoNBlPycm55IcI2OfYp06HPiJnzyANR4qTIUqDEESc06RGE5YRF1thihwy75ClSoU6DFgPC55UbIueVF/YpUzuv/NBhxMz55IcV1omR4ogqbabPrx0sssYOSYpUaNAiPG1MWCXCJjnKHFPjjD4jQhdQP/NclRXWiZKlQJUTmgyZvqAxYo0dkmTYpUiFLgPGhC+kTayyyTYJcuxTpsYZHUaEZrSHFaLEyVKgRJUmbXoMmbuwOcMOSfIUOaR+YfmhS/gi2sMCS6wSIU2OfcocU6ND6KLyxDzrRIkRp8QJTdoMmZ7VHjbYIUmGXQ6p06LLgDHhi2kXS6wSYZMEOfY5oMwxp5zRYcT8xeWMKDHiZClQ4oQmc5cwj1hmiwy75ClySIU6LbqMmZ3TNiKkOaDMKR1GzF9SG1gnSow4KbIUOKLJkOlLmUdssEWSXYpUqNNgwMKl1c0m2yTIsc8xNU7pMGJmXnu4KuvESJFljwIlqjRpM2T6MvLDBlvskKRI5TLywYAxC5eVE1aJsMk2+xxQ5pQz+oQup11clRViFChxRJU2Q86u7T7zDvcUsSkW/nLOYOcN8rXsvcdjQsHxO4J/PncZnjyT+Xf3uuXJb5rnDMIfOGewuHiuYPeKoWDbsvWxdt1V3ZatNs8ZnF7xXMERhZKxf4M6P+P4yqnNcwV1+yw63uKLHfcN5/jnbztx69cs2+J08gyo5UsvOmfQsW1k8r2Dctp2leu455XUcb3gn8+PBmLhDXLG/nX/9Z1E2T45set10zbZZfdUy/rXCf75TGlXu2L//u2odr+pYPrBU8HSQ6aC45J5eb5zBaeMbb+wGAo2tbczec3s+c8VLBFl0DxXEBdzHFChMSkH7vni+AnBv/5o5U/mhxgTN8Uke49CPKPPwhuMrVimxroczl3H/f0m5kDJ3JyMxV/k/Nbn/Oezs8VJvv+uHjG4jpyI8cn2Y/OK6OQ5W9svi2F9XB6eMzj+0TmDEWesds/p89U5g3kx1pTj03MG2bpyzZga17l3nDNYe+s5fTd/zmBP3hM=
*/