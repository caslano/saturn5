
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
Hztgf4F8jHyCfIp8hnyOfIH3KY77OOE4HeDsFud3uBj+Rxpb6zh1NIJ0wM4WY2qd2igj9SO8zZfs3eriA36IG+jvkhbvpRBrNqF8gCuj9PVlyG8G+jdp9RInwyI53UH1POfP8w1QSwMECgAAAAgALWdKUjDFKMLTBwAA1xEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTM4VVQFAAG2SCRglVhNc9s2EL3zV2DaQ52ZuLK+JY8mHY9iTzx1Y9VS0mMGIiERYxBgAdKO8uv7FgApWsqlp8TA7mL37e7bpRaVcFXKnfiQLKTeGfzzLA6vxmbuQ+IqK6w1NnkRdmucYMrsXbLoHSUWvaCU/Jr8ytbCQvDSyUwkCytKdSCB+B/cL5UUuor3qf8DAs5rfUi00TjuNX8uKmPUh0TJbX88nOEi/J0sNC+EP09rq1jjIrtZ3bOUK8UoIHIyyC1SUxRcZ2S/yqXe46Y9wn+jF97/r8LK3YFlvOKM7yphWZULb4/l3LGtEJr94nJT/ZIsXrwsuV9lpoYFcXXNPhsW8BL9a/ZFu7osja1ExkprKpMalYjBNbvjUuFMallJruQPXkmjEzGEytMDqx2cZFue9aRSYs8V2xlb8IohxkI6fwu5RIyu2Q2z
*/