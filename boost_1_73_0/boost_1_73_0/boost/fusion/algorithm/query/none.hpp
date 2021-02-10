/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_NONE_07062005_1128)
#define BOOST_FUSION_NONE_07062005_1128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/any.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct none
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    none(Sequence const& seq, F f)
    {
        return !fusion::any(seq, f);
    }
}}

#endif


/* none.hpp
dTXsdnqtCf6dfHzxB3oWLcL848O93+/nhbfnPfkz4f9N6If+5S8Gq/hfw+na3Xoy+Zsn/0df/Qv9+1Qnh176yd8mu97Tn/zN2+FPJqqXP+L3yeSpjv4FY8N/DvHlv0zwKz2hz/BlK14+rqLbu7W309r16m/fvvH2vcZRo17z2sEiCufeaB0ursPVbc3744yf/N+74OfPgyT8h5oXrr1gfqBAje+ixEvim/VDsAo9+n0eTcNFEs68IPFmYTJdRdf0R7Tw1nehdxPNaZP7g2+d3oea93AXTe8A5DHeeMldvJnPvLvgR+itwmkY/RAYy2C19uIb+pyAz6JkTQA36yheHFDfobcOV/cJYKD7YJ7EXvAjiObBNXUUrL279XqZvDs8nG5Wcxr94SyeJodTPf2Du/W9mck3GsR98OjFy7W3jr1NEtY8tKx59/EsusG/tCD0cLm5nkfJXS0dDXW1mB3GKy8J53PAou+iMJFhh95ILU8NzbwljTha458kXiTo6uEuvs80pHUElJvNakEd0TpQo1lMy1zzNnR8VtyYZ667UGvKC1y6Nel4Z168oMF4L5sjrzN66V0HSZTUvC+d8cf+1dj70hwOm73xN69/4TV73wDsU6fXpq2PqLOVF/5crsKEOl950f1yHoUz1efv
*/