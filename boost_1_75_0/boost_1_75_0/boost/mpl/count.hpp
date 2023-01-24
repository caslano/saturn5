
#ifndef BOOST_MPL_COUNT_HPP_INCLUDED
#define BOOST_MPL_COUNT_HPP_INCLUDED

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

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/count_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct count
    : count_impl< typename sequence_tag<Sequence>::type >
        ::template apply<Sequence,T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, count)

}}

#endif // BOOST_MPL_COUNT_HPP_INCLUDED

/* count.hpp
BQZBeD4eq6YmAFTujf8GBn7J/8MSXjsgh/65VvY7wi4qrHegL9Avn43iEm5bABgcgP3Xm6HXdhWQJB/7GM4HKAZEA6LewTUTwcew5oUSw/4K4KwUkEQrXXxjA7JsN0m8kF0RczyZA/rWLsA3VfL9ueEGrk/dEEPA63aANXjJpz9AAOf4Gq2JDYNASWxte9PX20dAO0/n/v7BSl0e6bmTNBPPXiPOmnGx6rtoZRnFQlGoT6B+FtM2Cgpvd2bbwFlc+YMhVJg5H549jmMB/wSBjJWyEN8bvXoAW6WrxdBypkmPcP1k8WUGmQHjbnzJMzq+DFd0o9If+JlqzboUv/eWuRIDVWvTDoFOeyVhe80304BjvMOnoN4cnuCUBDCY93mtJ9B+EeDCMbvtEIaHKHbzBZDPtQtWc3/6lcng8eOUPUM2FJ8wdAv/c6hKytbhGUq4l3SW3Vq+gatnlxpeAeeWhVKMEA56A2celqBbflHN7PzCodUt/K9cTpddpcnKAzqB/D1HhovYvGjvwpyUg9pKlIxGP6Ptu5QxJ2+1Un6xuhxeDoxaekAd6+tX7v2zmJ/dxTZFBwm19YfzpBhJDWYPT/PXPdeblhZvpufDSVv8jzkrdA3LxtODfmivCuc95eAKCbJD8/O2BnegwNdXo3Pr85AXuZRh+8HcCvqttAbU8uOMFeeUg0k1wh0iK/idA7cja52NtUXGuKph/T2Y
*/