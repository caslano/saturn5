
#ifndef BOOST_MPL_KEY_TYPE_HPP_INCLUDED
#define BOOST_MPL_KEY_TYPE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/key_type_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/apply_wrap.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct key_type
    : apply_wrap2< 
          key_type_impl< typename sequence_tag<AssociativeSequence>::type >
        , AssociativeSequence, T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,key_type,(AssociativeSequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, key_type)

}}

#endif // BOOST_MPL_KEY_TYPE_HPP_INCLUDED

/* key_type.hpp
ZZh7zrMs64wE2iqD2/FbyRLAL+9J3iIITNNECsIfgmYdcWOcHbhY/B7FmJPOJH//US81/FWFsJaanWWDL3xBLVWXaUd23z8YC1+5N4wcGFjP7D0mbof/mYSMS8/ycot1UL8u60FcLrhXQ+FvsegZEGNURM9met7z949fvEA0mTcjU/2sN3wUQkAMQziNxxrNZcr9fOAgXd5QOiX/7qTe3DIA+hG6VSXQmbZ/tGbg24gJpzs6b/TTDtKvJd2mlFYqYTiZJZuyX4Tgwrbn2ZGanBSZWEkf2TYQ64C1d8krsUdbumHRPdO6WLab4N11TQz4PSpaCxt3C+076iQBhWjeNtKvVnfXpQREfcB/tn5iwC3NfF3JnkE6xzVS2jFDHlRSJYpvaTBGSuYSwWMvPNpMi28C2su7kM59cRB6CflAY1u95a00PfyXQiPRGjp4yf+VlZAfd7t6OYUgpBTdU7kSjJNC3R1ctsTTKX27VJe3u9V5pbVuRYINUT5MC4AXiv9pmwa7NtbfaPWf2awIQ4G725M+lvdB9AWW1KmPdDmBsdSOxmzJf+SnFYR90g==
*/