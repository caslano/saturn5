
#ifndef BOOST_MPL_IDENTITY_HPP_INCLUDED
#define BOOST_MPL_IDENTITY_HPP_INCLUDED

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

#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct identity
{
    typedef T type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, identity, (T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct make_identity
{
    typedef identity<T> type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_identity, (T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, identity)
BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, make_identity)

}}

#endif // BOOST_MPL_IDENTITY_HPP_INCLUDED

/* identity.hpp
Jzh4aHyx31uZFEn+zc6U/F5UkSm+/pQOtRanNH7yu/T1G3zaMEL1rO9nErypBdm+nIVljnB8NmF6ptWu7FP6/Rhd5KEAfsnHZvpu49zbP2Q2d76QppQrYtOULORHTwImrR+/W5hVeUXeKh2nHagjkL5eVnFhPp+G6XxL4wWqTzM1W9QWMao23X950jT+aMuAdzqjltTYhL44zfChAUR3/OtrweGBK65jHwqT+EVoR/g3dKXPsyNIm6jP0H6rmV+kfU0JbvyPsJI74RUeUJK/xn4qD1t6YZuz5VXs5w0OJrjesL/fF71QtMoe1al2r/zUGLEJI1SJa7G0n381GPD7SERTydcfZWeuo7zy+Di6wfJdsZ6Sst/qmcyJZGTGoKzUQowqcb8P0lDgoj1gApn0TPaoaVRyGej4Mei4gbiohdxD8FufFEMROujVgnuo3T6Fm5NAc3myGNfVJy6m6zp20bzu928t5QUrshZv79z1tKmrXY3ZNPNeKFEpSL1DJUqMW1RB0jHCiE+wA4hkFzWsQAIzd1U4qGanPF9cJscWQjkkHfUGMT1XyKV978Rdkgwxya8blvmDDBvXDrGQwhluG2xve7iBbPqtiLVwnBT7FbnRbOb4yLXv1O31H3WGf7mHENnA6PSTL931c1o2VR+p3qrijzTwkQyFP9wOGx1sxWRjG/we3MIRP/IKCcTeDt7BeT7pGC78JYqCmq64
*/