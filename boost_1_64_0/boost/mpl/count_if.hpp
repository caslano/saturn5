
#ifndef BOOST_MPL_COUNT_IF_HPP_INCLUDED
#define BOOST_MPL_COUNT_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate >
struct next_if
{
    template<
          typename N
        , typename T
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >::type type;
#endif
    };
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct count_if
    : aux::msvc_eti_base< typename fold<
          Sequence
        , integral_c<unsigned long,0>
        , protect< aux::next_if<Predicate> >
        >::type >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, count_if)

}}

#endif // BOOST_MPL_COUNT_IF_HPP_INCLUDED

/* count_if.hpp
YFwt0fPTq7FeJZEE/UWVFcR4ZgrGX5E+542/Iu33/eNekbLvAyEaDQfCFO+khrh9/utlqt+bd8Xlz5rfRPPnnR7XUPLdfXR+Y+s/X3LN90/87Bjm+1u0aFhCyiJck2MQmFCUxQQRKN9GJtUBuYOmaDjOJ3QnygRZEg9IoSidkrjN5Fb90zltvlnVAfN25CePcta55o2yij16TdquXwD8j+qnsnx9q8L2ypv4tG6yrkWCFNWwVvRvHreenGq9dOk8avLqwM84PhwGthDMNjktcIM2nCMf9NQeaFe2bdC3WZJuLkyzLnr/xaOgML5FEAmbwxN9OmUS09hE35QdvYxI9Y52QIwehfANDwOxE6j+Ec7/k+WEkoG+IQZ85sCnD7V+h0ssH5f28An6xLP8XRLRtOHvUuTxOS+hTqqGU95Uh/lQMD1Hta8e9yKP/6pDjvsoehUmSN5N92rpPdd84GBr222H/HSqJ76ttbdR9dnH9UlBfY5w/u0F5/jBNmXb4wfojtJ0d5GclNEj4HHKD21BoJMKrnnwBKiA8FPJ33rWOUaLzwjV3cMbDveSDfpCOd/wHf6ix/AkXkEEymvpiE5ALngpGiZnjNxTeicP3CNAYO1soD5+yS7yUtXpaajR9x44hpNNcZ5jO4+l1r/EgmCkH4ZwVnswRZZKI+QyTzOAiWzEbhjwtYx447nT6OOHh27c1nmELGiPwj9e22qdZzHHh0F2aI5pcDJ6MS4qJj2CsSOh/YZeci0iNWDyDo/0eAqDBSk7vPI1FZFT5QBYTRYLlusoZqxgCVvnO+hFnGVb/J2qEUltUyKzeFPVtDWZpNYApj3VKZJlENU4BknqKyGpA/tZQHo6RWELyBcgdCUUUypjh7eSJkz6DKyTBevIuVBYoZS1ELbDXRGlG0VB9iSQQUYL+7n+xXOBxUxJ4pqT621ZDd/0nHwXRmRAQp1zMnKPmpMj0xFMmGNKhvSSonsjFb2RSr0BzKknpJpVyyEQhr2I0o2i6BoRelyj41o8/wsem//VaPlQ84f7HnMOcMy11qz6dII+DaIiJ993bM7KnPafz97V9nmFVZuObj9qVh35fMKPXj7y98d3x/1urrif1//B5cNYC/SF1wXoz8CbjwjQnYHbqgXoyMBlKg03oHlrjQDvMrDnCQEOMPDNpwV4k4HUbwqwk4HBSwV4HsyhQoAfMHDlSgEehVhVIsBaBrpuEmAFA48uY6BoiZkjL8Xmge/h5Sbzj5vxcq354na8zDKTKvGSZ174OF6mmFN+iZeLzC9/Fy+jzFt24WWIOU8+DTB/+BBeepmrvoOXbmbP1XjpaC6myeSz9TTk3h8t/RbNM6FH4tovpHXl/c+nnfshOyqa/kYKczR0OTFbgNUVjfRvbnW1ST951evq6Se/uqKOA80F22XjraKFwPIX+V/SYuDuM+ZN1dWHP8WOQAsnMjOfFs6CHOl2GuKsyDVc3Uz/RpJ2VPAv846qdc2coqqCSuONhTopm3KjQKCVG9rNOsgEA6XwZ/O5FZx9Gs2MhN9h4HfppdhmyFVRWgv8kAWXesmOu7+lxv/+s6dYjW+v/7ewvCdX4WxBNzgcP0FNii76mZiYQEU66YdHFzjs8Ylr7M1fLo45r1UzF/rPH+vzxYLEuLVam4ux/e4iBTYyTnwFeaPMfdfSSdtCOMw228tWKI5tGp6iUTj/aCj3/eIcib7h0kXn4V6sTVNzzdWvogj6UHa77w90zLeE5Nv9mBD6hKZ7WBc5kT3X0j/m/kpUg76r7Msu5BRLKcU+laLASpE2iVJ8X6fYhxSyYjMy8nyLKc1elWaGleZKLuU2nWavM006a22hzQ3e9TeEt8jBAOY=
*/