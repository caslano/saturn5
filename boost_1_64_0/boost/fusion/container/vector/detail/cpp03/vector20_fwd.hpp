#ifndef BOOST_PP_IS_ITERATING
/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_VECTOR20_FWD_HPP_INCLUDED)
#define BOOST_FUSION_VECTOR20_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector20_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector20_fwd.hpp")
#endif

/*=============================================================================
    Copyright (c) 2011 Eric Niebler
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    // expand vector11 to vector20
    #define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector20_fwd.hpp>
    #define BOOST_PP_ITERATION_LIMITS (11, 20)
    #include BOOST_PP_ITERATE()
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

#else

    template <BOOST_PP_ENUM_PARAMS(BOOST_PP_ITERATION(), typename T)>
    struct BOOST_PP_CAT(vector, BOOST_PP_ITERATION());

#endif

/* vector20_fwd.hpp
FvmPvGfefiJpXPjyY+/SrjVamT+nJGNvq5yzdYtjRz67avLv8rl/10OZ/8zf9s9MfH33fbX++c2Ym9dt3c13jGt+aK/dA/oU1Ms49bPDH+/68QtP+2rbHfizhkCfBZjf8/f9jMC8bbrve/vmzzgCb2tu/ozAV9t6323HB4Uq8xv/dk2O5d8jmr03+VdT+g797DbfzzjcbcTlOkuuv+webcRHSRvxJOyAYzAax2IMJmMqjscHcSJuxBT8DCNJcr1Dcq+/NkaQLBKjq5iC7rbvcv0i1zV2j7bv7aU8HTAWu+MQ7IFjsJfke54k1xNcZ7jX05y/T5Ms0oa6DRZhFDowDp04CItxCs7HdFyAebgI5+NiXI534BpciutwGW7G5fgG3onv4l14Gu/GP+Mq/BLLpA3nPZiMq3EKrsUcvBeX4XrcgBtwC27GrfiY1Bt/u3/Hy+96tpf76bxPLj53yfY9gzPweZyNB/BOPIiH8RC+hi/gUXwJj+PLUv4KrMSfyT36I1L+n2MsHsV4PIZZ+AauxDdxN76Fb+Jx/ADfxj/jOxhJmf+AvfCP2A8/wHj8EMfiR5iM53AW/gkz8S84H89jCf4VV+PfcD3+HR/Gf+A2rMQf42d4CP+Jx/EiXsLPUWmU/BWG4b+wI17Gbvg19sFvsQSVtvMrsAGuxUZ4H4bibtTasstvT6xvMq7tJPk8TMHrMVVt+8wf8r7xpPoeMfCnpM30+3gr/g674e9xOJ7GJPyDfnxdWd9IUrJHOZZdRx/4uAKH4EqUPgDkdxfLyPv0fQDMlffl4Uy04yKch2q+92j55njkO7cu78cCHIJ2VPNdreWb45FvG3lfW5yJHXERRqK1tnIw0/awc22/2hSH9Xc/K9rKezzbD18kKe2EraQYknebYK0d8D7efxGV5zaRpARdm98y0h6StO+lba/WrjeSlEKS9rte7XaPsd52ShlJEdE8e8AoTMFMkr7N7hl59rKTVEE6SYpYwHMfVNviklJImSbtb6XdrbS31be11drYriRp7Wd5D8nSi/ror28fa94udmd/77aw4SR9m9dykv65xSXSqf5e7VnVdqylpHLSKaX+SeG/CLHEkFJITtJW0oukk6RKUoNjwecTwSk4BafgFJyCU3AKTsHpv2+6ts//7brW/9/t+b/y3OQl5Tl1d6795PG+vg8A5XntrJZc+0Vr/2/WD4BV14YgxUc/AGnLjP0AuNcWeF8A9a+iL4Br3eY/0BjoQNvwF7ljjie++8WvCk9nxhd+XblvM/c4pE2+1K3UeSVJfz+im7TJ74GdsSfGYS8cgX1wNMbiWrS+FWJJIMVEGdvdJ8q1dNV1dIpcJ3ONLO3f9de3WhzgRZJ2nYq9jO3Kw+X60vO6MvOt4LVgcApOwSk4BafgFJyCU3AKTsHphz/VJc25Ztf/DBnk+sfmSLd/9z4AlGt8pxKv7orJljLYlPXnzi6mDFXX+C107QRKddf4TeQav1sL5i/Vxy/LSizVj1sn8XASR5lutyth3zLfitOsynwC850U3eGO9dq/VB2/jte3u19TUrvH+GeXpKxjpKyJUtZK1/IeG2wjBs6Pdg0Sg2Ysr8f4YjMkVvtGeeMN0uYgeZkh34JCXdb+jC+mH3NlV1vlvsD2/Y+89us3511a3OTFsC71vxzj+/6IeZtp3/FN5vFivuOzzNugBx6HZX5/xHfbevO27L7i/gIfu8U8zivw+z6Bxq8F2mbdvC8B3/etzO9/BR7PuHWBa7vOztjz6+dfKfjZPy6e6BLzB5vvOEffcXASX7NUu59V5jG2QITE17TCdmjFKGyN8dgGR2Nb/AzTSJWyvjGyvhBMkfV1lPVFYgvshC0=
*/