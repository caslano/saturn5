
#ifndef BOOST_MPL_IF_HPP_INCLUDED
#define BOOST_MPL_IF_HPP_INCLUDED

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

#include <boost/mpl/aux_/value_wknd.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/integral.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<
      bool C
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef T1 type;
};

template<
      typename T1
    , typename T2
    >
struct if_c<false,T1,T2>
{
    typedef T2 type;
};

// agurt, 05/sep/04: nondescriptive parameter names for the sake of DigitalMars
// (and possibly MWCW < 8.0); see https://lists.boost.org/Archives/boost/2004/09/71383.php
template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    , typename BOOST_MPL_AUX_NA_PARAM(T3)
    >
struct if_
{
 private:
    // agurt, 02/jan/03: two-step 'type' definition for the sake of aCC 
    typedef if_c<
#if defined(BOOST_MPL_CFG_BCC_INTEGRAL_CONSTANTS)
          BOOST_MPL_AUX_VALUE_WKND(T1)::value
#else
          BOOST_MPL_AUX_STATIC_CAST(bool, BOOST_MPL_AUX_VALUE_WKND(T1)::value)
#endif
        , T2
        , T3
        > almost_type_;
 
 public:
    typedef typename almost_type_::type type;
    
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(T1,T2,T3))
};

#else

// no partial class template specialization

namespace aux {

template< bool C >
struct if_impl
{
    template< typename T1, typename T2 > struct result_
    {
        typedef T1 type;
    };
};

template<>
struct if_impl<false>
{
    template< typename T1, typename T2 > struct result_
    { 
        typedef T2 type;
    };
};

} // namespace aux

template<
      bool C_
    , typename T1
    , typename T2
    >
struct if_c
{
    typedef typename aux::if_impl< C_ >
        ::template result_<T1,T2>::type type;
};

// (almost) copy & paste in order to save one more 
// recursively nested template instantiation to user
template<
      typename BOOST_MPL_AUX_NA_PARAM(C_)
    , typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct if_
{
    enum { msvc_wknd_ = BOOST_MPL_AUX_MSVC_VALUE_WKND(C_)::value };

    typedef typename aux::if_impl< BOOST_MPL_AUX_STATIC_CAST(bool, msvc_wknd_) >
        ::template result_<T1,T2>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,if_,(C_,T1,T2))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

BOOST_MPL_AUX_NA_SPEC(3, if_)

}}

#endif // BOOST_MPL_IF_HPP_INCLUDED

/* if.hpp
S/rEskhRtUz3WNInlUUmq/TY98z0M8sil6j0Zyzpk8siK1T6Y5b0qWWRTSp9vSV9WlmkRaXXWNKnl0WSKn2eJb20LBJUjPENS/rMssiZKv0LlvRZZZE5Kn28SP8o2Khve8KnaKYjxuFsYUyYMAV8HeLX+8VywrEgRyFGxXSammwzePZ0Evs3xc5CZEhhoYeQgNlRN+Jkk+FWxYJIcpk01LtHbFRwyJlGlsdsxFg6DT/HVe8TP8eJQEra/OPQ0jgygFaTkBLOmDLmWr+IFUrX7x8sqjb1H/omTCBo4N7Dq4iAFZx9/FOq58bJpUnVcJ5Pk2cj1xr/jmepuLm66VDryGfT1xHhkUUsIkzYz5mEnTxHEpZv4GLPxX5TMQWZMpryx0V2xReQiK4On9M/pYRNf8agioV/audb+YfxPztj2IoWHIFh+xIIpkJObu3Nb9O8kt9SMrj8gopzgXSFX7/qhjStzkjwx2zFibOJE+dCde+PZombRWAjHn9M8arzsVyahESgBYWgRL8yWQg+9XNcbCyiPIOB8Y21MCOEtFCFpn4A1jv0fDzrOtJnfUx0e46ufy+t2zmdv2QFzMdF9mT9zyo7JV7iRL3YcWbF5iG8Xh71V3vtKC2Wy11Qzrei07KVQXTi+WIXcr2GP6noNGa6xil+3i0jdKrGeIGoQU5DbpErS+aOcbnxLTaq4hSghfVm04VA7AME2HNaD0dXYv7wJgHDRnuC/oTBNubfy/PS5V3S5L+mHFt5N1Nx2UyOOR07EvKOLRVTyC5V2aUDiTkt5hOH0Z2GKeXID6fMM/ab6Da/yyl83Lv8z9flMNWvZ5bGvRWlZpFF2UU1YfomouWkiEtzOJf2YHhPkVVME2tPIZ5M8GA/s/eRMRwsC66jntF95PCK+y72WWTFnipOj0wTWy0ebxcPxJSil/y7VulfCGXPV4L8XauZeku33Cci4q6nNMjf3Y1TV6LnWBYC9Ga2mk9CvGc0JNyUIL0dKZUR5795GbZA6uQVQEOz1aSdDc2Y2FaotIn4SQcx/NLwKyh/BcWv6k5RlKFhjsUK0XCgWhcDH8BPv/rpx88Jii0miMLAsCZ7qSnB0FlIeX4+kH1HbLS6R/RBjYTw+vBpR2NZ1q8o1+//Y4zPtrnG+hQROz/qPy8s/FgGD5lB24VqJ5/C+iQs9k9XRvpJEVsPR2lEXO0pD9BWNOYXGrGeco1Xb8Ssif0p9rP30TXGdxzOf4SvwFMNqdyAqp8nKm1fQo5avWXUsmgS1AZWCB6n755pQSTX+lfAG0dcxPcXTALbZOx1xHIcxnLsFS+0+QDRVlKeqDwWfeSCZ2fzYpQiKFSHVONw9xIdEfOhhHhlpADGHsDST6tnoGRKsHApG6WCQ7Sde8kqPPKcwfMh3cLwc78tGb4DBt4n92J4NYCSMJB7Ae4QSbLLBHgarLSTWrIkrM8rrIHTusbsldiftEvcpmjRs4P4rkfLNLGfV22dbAJHiY7oiMHVCDicT9/4LvOHiozZs0sEsxZnCIX7JNraYWabBz2EQuPHc4mSKYF5w80MTWRgesYxClSm1r9UuMnhsewmesp5IKZFudjxq9ZmicuXknAKEx0PwJKxZnF8UYXOBM5y7sRVzD2feg+WjK35cHcg5vyndy14fc9BVBBbdpbYOXhCySdci60PmifNL350Mi8f/PrIJYqU6vEsqB3lVqvCzfsBHHMmCrUY3FzQ0yrsu7s9tADrj4gqIMYkohqC4Ro+GLpX5Iv9sUJIMz0NsB7LohvwE4uaj+27V7gB0m2AhM8HB6gBR5ABPNO3BxmAswgnkHCjkAmVQeybTCAq3JSBQ4V++BJQhxpsnDILlJvMefo=
*/