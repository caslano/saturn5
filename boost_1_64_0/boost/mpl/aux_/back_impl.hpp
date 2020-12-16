
#ifndef BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

// default implementation, requires at least bi-directional iterators;
// conrete sequences might override it by specializing either the 
// 'back_impl' or the primary 'back' template

template< typename Tag >
struct back_impl
{
    template< typename Sequence > struct apply
    {
        typedef typename end<Sequence>::type end_;
        typedef typename prior<end_>::type last_;
        typedef typename deref<last_>::type type;
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1, back_impl)

}}

#endif // BOOST_MPL_AUX_BACK_IMPL_HPP_INCLUDED

/* back_impl.hpp
knokuzFaYj2gC0BFt0NZ8SJxAmgMTW+B66CY1aSWMU2oGa3orz39daG/K+mvL/3dSH9D6S8m3hEfH++M509sfPDHFR/5Exd/ep9a+3+OH4WP1jk1Oj7ab5uGx1f74uviqPkvMYvD5i/5c9j8eJ/eLDK+5oRm0ds/ODUK/r0j9Hv7Lr+ymZZ2VMWv+yJ8/444orfvjiaR2zekJGT55hPNq+LtjW4avb6lMdH7m940fH/f+jx8f7+IiV5/dkoE/MMm0fNfEjq/z8VwajKmeP+DFZHlUz5PUPqmByuqE5+5Q7LSH2f1huaW8uJ/3L62nyqWoKsF4GcpnIiLXKnNVeU4AHwXGpNIhcDAyHxforw4MFMs23oBGP7G+dLf2KOQBvripVvrpIGWmW7Vh9k7OdBo46T6LpX1XYL6cG6++D0e0Syf9mEox+MC2P95/lzxdp+KmLf7nKKD7TjrjU/Y49SwChZseOizz0PxUWMtxYjQyCoe0dwTqy7KGEgFW5yzyiGvle2pcgeYERqjVGPdcplIRDPViVyUyBnINtptS/WoUEhX2Is45QAshC4CiQSUpr2IU85AJ98IjKhvkm8iKVr34gbnleA2RtF7zTw+p1lQWiwhn+oLp976AKFKhOUc5jq7C34C2oGsUeuYJ+r+ucJfLML2GFz6ZJQ+lkunct6ldwqUoyhpRyZdDrLu8VX4aIyKSCvfSK4VMN1T20HKIOwxiv+E1SGd1rOS4A/6/SFQXLrDJO1Ir8j93pndCjeYVF8WVz4FlZc4ZeUIn0x1nqI6a1FK6kfSjj6ncsud2TflCzP969xsR2uOaSs99k6g9sGfSS3fyN/LGo/BjawWMK2a+qZxdQ+huhyuzv+8WFNHSTqgMLji4GKLjMPMv1NTpOY7q5V57YfFFcpRyEuaP3Yj/Fwj5Dc1hMM913INamnMtQSuJjZmr1PsZ8pGgsE8wSqaLP7AetWrF9hex/IgayNNXJ74P3AV9HHXoSIXMIGv4r4KPaX5q8P4DlCuTbWki8HxDPP3/26Zx9n8aPrfIDr9zq4fnv4XfRqWHzCfbxQav/t334c+H1sfJX0IxxmqHSreadny4Hin3xyh9OaRluHiqR+h95Xi39WNpB9bgfQ6/l1aNH2JB/4PdbS+xDyX9MFKwNHKSBF3iqGFMPT4NRt6XEuqaN6knRxhaesMr0Vbv7HT1tlerWbpviLNo8RSP8Qp5BEBmQ+62tV4vBAJQFdjliuimAZkLjY58wGHke/wvxJSR6HoQMEKFGu5LrgbFQWZZydjQaFMIIT+y2TBRB0cRMVZIJSsC3YGugUuojZZExCHqVfugiIcAdOBcqLv3Dv/1yQyEoLHBsaoVjGM6lPRAK/+lTvRsv90a/8F89oG+uZL83soxprfZzC/BCir5vdDehBGjba8vqVGWxRjU6Otrq8MPHHwqRAiTV1qGi6nhYL57Sjntwzzm7ZUTUOKGmxzG6Ns6kmwY1Q9/F2VScgsZQeQTdwEf38Osi8nAQLGh+qfzUmw4p+SO3IYNNpjydoL4AKNidiamyUHV8uxFycpfiywlVXWZhPKHoitJj9l6b9rgX9Uukt30iw3YyGS6/h915Hr+OwVUlVTyI7UflPs+0J6isGeK58eFk930lNW7Mun2zSjAOiS46qsoXif6F/MSj0WG1OUOlVqV/l+Kr1nfC0gTpSp8lPk+2Gi1pOqVCfXarSMfSTGJ8vl4XLVA2H0X2Cvj8cdwiJXdqbU/MXSyMP9XGpW5E+tJtS/WVFDvaPfiZ6BhrtQtm0qztgUONNz33Mv92RPNQzV+FuRwF15+4CwunN6VCqZtHtbUffn/MTrSXiXuOpC2ed6KCwRNtY=
*/