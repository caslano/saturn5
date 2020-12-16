
#ifndef BOOST_MPL_PAIR_HPP_INCLUDED
#define BOOST_MPL_PAIR_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct pair
{
    typedef pair type;
    typedef T1 first;
    typedef T2 second;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,pair,(T1,T2))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct first
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::first type;
#else
    typedef typename aux::msvc_eti_base<P>::first type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,first,(P))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(P)
    >
struct second
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename P::second type;
#else
    typedef typename aux::msvc_eti_base<P>::second type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,second,(P))
};


BOOST_MPL_AUX_NA_SPEC_NO_ETI(2, pair)
BOOST_MPL_AUX_NA_SPEC(1, first)
BOOST_MPL_AUX_NA_SPEC(1, second)

}}

#endif // BOOST_MPL_PAIR_HPP_INCLUDED

/* pair.hpp
89hyYPCcb4DeDFtmzHwGPScHjasj1lnmoWQmWsWTqBVrkfmAeBJBomJ6PZWXMBkY7sIUMxWgO7bcWHFR9IYHZxAZkAzOoW+K6sMbheoBzNsgGYnYNfocuYBk3q403aoKGR4Cpcaxrcp5GSNx7V9sifTlfa3p7bwhmSPMgcH40m1AokdTSxU/cXMTohGogu00fjMvuex5KCKv/So8VFiL3BpiFeIdRFhEKZT1UIDOlFqDMzSFDFA8Kv31UXNJN4ZcY7aYSxExLm2dLs2jSrtvg5QmN1StkH1cCIfPvAPf5WHFCh9668lageHRtNEX5FfIbT6/fRTgT8renb3Yr0fukzZpGri8ZtdAz7bmhEczbZfvP/zUIt9euL8+uL9+ke6nzWiZsbkJZLGZ+pmpKiqCfdhb1M8EMO+Tn0pH3JEfGL9YjeHfJ+Pomc3JoNulxsbVapqEC3IsaacydbX7UC4aroeUIfVgLky90sWLkbKxnEQDXNw/9aPsNN1eD5HDajzyDITcuHahzDS65mDmQUKPBoyhARFUYqVUhnOQvIYo7VJY9fknzWDHS7uGl/sqDlQVNZbIDEr2n0Wel0Yw1aS4Ac1jcdng/mDdDw1TcSgcjxE/Qe2Rp3KdaonI0Wj/gZIIH27FsiTiOEH8KJaBsD5mPtq6YP604bSNcVm1cnAPCzKEuuytRgnJzq/Cz67GvS+89ZN3MmMnZ1QUoo0sM201RJ3c9yKvTwdEVPxlejQtyDCPduztfMtT5MCaO9D0Ml9c/uswN1JYQ596pcJfNcLcYhM6OTjlcLJJU4LV5v6vdWKca7OI/s7brUu9lQSCdTrvKWWdaN3sNlOfOmGkzlc/E8A8Vf2MA3mk+tlRU9XBJI8ESR8J3vJR23Ym6OESaoRR5VvC5Rsw3pCeFxiHz2Yu2vFgXHu4jLYAtXPeP2eag1KAkX70ICO1AaktXEaT5jZGalZI+Yz0mzAj7QDSjnAZbbTYwUgrFVIBI50ASq1Aag2XFdRUtTLSLQqpkJGygdQCpJZwWWFNVQsjjVdIIxjp9QcYqQlITeEyiqc1MdJxCmkkIzUBqRFIjeGykTVVjYzkVUjHMtIKIDUAqSFcdmxNVQMj/QlzWr/eaX0WvHvZBrSd0xCeldn1ljJztmW0Nid3C6whLKOFouDJsTxO8x/L5t1phKGHfNg0sZPrMRz5gfMNjxnBPX+9GqndkZNpYoFH6TaPD7lh9Zp/bO4/30RJeESHQt+buCKfIwI9F5OoEq8emO3Fggvyve7UqmxQ/ofxXlOyKi8TVmoowDioVs2Jmow/3s2VRD6xVpf+PFnC3W7ZbiTbovWYbmyblazkZLc5Gf7W/ZZK4vZYuptoXWnIjeGn8x6zkqspCU/yUCVXcyVPIQI9J3MlXVRJDFuCC/IH2dm/YpbJftVh0ne4odYrlQifW4DvK0n6YJ1T8prei/HYzGQFfsbz7o7luq+liuOeTPKwkDEe0xiFIg1fsGD80CXSkLTxnWVGmaWQUiYxiQCysU3tBmV/qlNiHS+tBTmhYqgmV77er36saA3haIaRkAkP1hwY3fiLAIxBKEPtRn0F1st0/DCL/b4Ukxyho1LUCD4JccRMc85ecQS63RoVGcmuXIZCqBzMCcYPpdRIBWh/2+RhxgwE7TgoR8PhFcwAWh97DCP3WhjoTnGZjx1vvH6PqudgbM/1mwUMxVTbLb94IxwsdlcfLeDzBnOx1h5lrb8NKvmmMWc7bTqLxZOTzmT11E/Htrn/24/sB9rNg9fwc0/jifF5mJbb9vP8is1rFbZxhlzm3P6ysno+qtOHh1VPpuvP4KD5WRamZvV82SViUVUYnMXis4nEJxh/9RA=
*/