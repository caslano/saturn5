
#ifndef BOOST_MPL_SET_SET50_C_HPP_INCLUDED
#define BOOST_MPL_SET_SET50_C_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/set/set40_c.hpp>
#   include <boost/mpl/set/set50.hpp>
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER set50_c.hpp
#   include <boost/mpl/set/aux_/include_preprocessed.hpp>

#else

#   include <boost/preprocessor/iterate.hpp>

namespace boost { namespace mpl {

#   define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(41, 50, <boost/mpl/set/aux_/numbered_c.hpp>))
#   include BOOST_PP_ITERATE()

}}

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS

#endif // BOOST_MPL_SET_SET50_C_HPP_INCLUDED

/* set50_c.hpp
NvtkqpLnk71zUW3sM9iP2+zpK6lm30Zr800HP8fy0tLQbVarX/b5uAfYNzFCorF9uW5hPwmtOnXbd5Amx7f/9ttvgxT/sB0blurbMW6ixLxvu/Oyw+SN1/M+7s6bECZv7zB5igvh64v5ltC6YT1+Ap+Vuqi3OZwSLBl5nchbj2U3e2sE1/Uxfv9C0fBZXbLPL9vZL7TvMm2/f5QbXO9nxEiqrWZbexnSVyjftixivdtlQ70nhdR77MXB9d5hqPf65wJ1Mk5invxccD3tFJQ3SV1mRvcyiouheeNZzpCXIw1lfbMulBOJA+cM/K+1evpks3rS6iWb9XJnP0m1U7HC8aAP7MLyK58z1kvw/y8lpC7SQ+pipaEu9lq++fGW0Z03yZgXemz1DeRlZYbm8Zg25f+pLLsWPvslNR8zjrQ6ymId1WwrqTaJ5/DxPE+1LQ+qI69tXs/PPDXDX+U479LqQeqcSl/Z/7mBviay/yiBvsa9oPV/FkyvspZWlFb1pq/TDF8V3ybTt8u2k1RLo2+p9C2TvhU6neWoSLg4Q3uyzF/oo9qna+I8sfB9hFs/f2zM/Wqf6xvVX69Y1bpH/ksdg36zp84R88f+qvljSt9sjcR7Et6jLECKRSqTNDuN87tOB5PAM8EM8CywHDwbrAbPAW3g+WA9uIB9vynb8PrP+4IF4DCkBCVD+9yaCaaC+eBwsATcA6wE08AqcE/wMHAkaAdHgXPAMWATmAGeCO4FngxmgWeAE8Fzwb3BC8FJ4CJwMng7OAV8CNwXfAScCr4I5oMd4H7gGrAA/BgsBjeAJeAmsBRUNq4SjAUPAoeDM8AcUBrQ1bovv+eBM8FysBqcDtawnhZLvF6Dq7kfBiLdJGl2GOvpSHASaAXzQBv3Qx14MGgHDwfrQRmcDTpBB3g0OAecC7rAY8GjwVNBL3gR2AReBs4FbwFbOI/vGLANnA8uA4+j3xslXk/BU7l/k5DWS5rdg+XGg/eD+4EPgqXgI9y/j/H4WQLWgU+C88CnwOPANvAk8BnwEvBZ8CpwKXg9+Dz4IPgi+DTYDq4EXwbfB1eAX4Kvgj+Bq8Cd4GcHmAC+Dg4CV4OjwLfB8eA7YC24FnQw3wN+AvrAddz+SonXSnAS99t2SIWSZtfz+d03gP3BG8EE8GZwtKQdH5n8Ph68JTBmwusamMj1GsdMLuOYyeVc3xUsl4eUyXJpLNcPaYKk2Tcs9y24Pfgjx2o2gangL2DhNtq8zfRC7X1aeWANkgfpDKSbkJYjGcdk1uG7Mi5TOS54bCapaPPxmfUR3r01BsuuLe3TqzGalCxtnKYEZYxjNc34bT7fzxVuzKYqq3vMpgZpOfI9yHNma+M2zghjN61YJtz4jb0I35EeQOpEkoqxzUgTiv9fYzrmt/+7R7G96oT/P9v+//Pt+6MSJWmD2rb/591LiXumv+aeaQPntD9SrJ0bV4LrkKRpFikRKROpBGkWUvCYdc/nxa19H2Gk8WqcAyOOWfPch/Pe1o1TCxMmTJgwYcKECRMmTFj04v+b/A6nw99iwth/KsbNlf60serYv8NnCM23W20+JcpASsMyP0xFv7S6DB743+SU+Ww+eN6MQVq/rdYpSxlcLiXcctajmxx1c6yGxaUsao/Z8nqNLpnSV3FpIvYHx6ZS+gSPTY1A6peHftvHtLEpdWS43ubzY1i4zm2XrR63Q9ltU+a6HfaUdPyOfOeoUSPTlYyRub0ZX9uJY1d9oePhOJTuz2L6M5b+jKY/0uOh/siuaPqjz+fIY9xCf/qzI9J2ecg3+uN1+23+gCvWuTZnk7xF3RRVd2fqnjZEklgmMH53DAaSfQ2Oej/9mU5/HqE/A+k=
*/