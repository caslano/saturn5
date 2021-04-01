
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if defined(BOOST_PP_IS_ITERATING)

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

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/cat.hpp>

#define i_ BOOST_PP_FRAME_ITERATION(1)

#   define AUX778076_SET_C_TAIL(set, i_, T, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)< \
          T BOOST_PP_ENUM_TRAILING_PARAMS(i_, C) \
        > \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i_, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c)
    : s_item<
          integral_c<T,BOOST_PP_CAT(C,BOOST_PP_DEC(i_))>
        , AUX778076_SET_C_TAIL(set,BOOST_PP_DEC(i_), T, C)
        >
{
    typedef BOOST_PP_CAT(BOOST_PP_CAT(set,i_),_c) type;
};

#   undef AUX778076_SET_C_TAIL

#undef i_

#endif // BOOST_PP_IS_ITERATING

/* numbered_c.hpp
MpnMQzsv5T9CZPylOQcXL3bkOQkho/UP3hK18bRoEO9Gxd3oOSEOok6pLd0JTS6nGsF1OXaQKxUjVcfjNLYRIqQDwm18i1LHaukE+xgaeqPgPRFV+F3EwX94shTShZBXwjpARTjGSyhsY8qdXvLIkQG8VyiynTdOMNh1H0/K5nbXn+CJyFZgSDUEV9vWC8nVUrRb3x3Nr+XjAdFgFgulyK/4YvDp7ZoC8pSoE0A+F5g7V0Zz4aOAybb9jdr9g+wDq+4m9HtlVvyURndEKB05zuwGMiFaDaQCtvDAjZD0hUxZmU5SKUsB0qRBVBfcfuEQCl4zrpW3/IK8s/qNo8QU/T9jKTz3PuJ2dmIKq4+84qJsiRyqfjR5oNqp6FCRqxr1wgMXLCALQqLmzuj/ZrWlMGQnbfwljaLrv4TyiReILq11szPDtcSdKlFO47BcnhyfpqvTv7mD5c8duP9WcxchgqRzom1g5U8Cxrgkq3QKk7bE9mlrRCJq0cL6odKgTCGRPNfgM1s0eX1VZ9g+OWIGL1LHDchPDmh/Jz9WFOP1zFSr7oiANuvMUm4Wvg==
*/