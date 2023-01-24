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
enfr11gNA3xnjcZlv8IZtCRPrLEaQ7Q9JH/SZzPXMFsB8q81vHjS1C1Oy9fiHa6xtrAQW92ahZhNgqbBd5mb2aDAx1YUG7sJzCtrwdSB9hc1/OfKboZQqSQCDgAFmkjPptuDZFKNh/mLH4dYZgTiFN3kriTMDIOC5WL800pihBzmcNfF4yj+6ffAKw/dA3+bfxS89KEfkfbY+Z14/xES9lPCBkj4EhK2UsJ7kLAOEj6mhBcg4R1IeIMSfvoaH9/Ro/I7IlDLvqenh58l/Cz63sBroYRnDBj3KL+yUuRdmdJj8jG3cjhnUHOez6u6lQTcxGNUltQMAYE7CLRuEvRMvorMZ2fYnT7vftysOQKF23dPSTEZPArvh+lLpSKaR+H9UAekkQ/Bffr2zGkQndjt9uc3BO3nfyRWBaOqBIYXV8xuiPdexHqjfXRvOReiS2QBLH77xjvR1F+9VRVwrozZBu9j4R1r27baSngs/6DoaQPgzc0UY+GFslwq8sbqMAMdHGRpB5oN9tN7DJa+xwO6DqUmqb95PPrn/QMWAxSKRq1m2yX1h2+YB/6G1qFFDL2yIMbQqybq85uL5XJ48pWmfGW/YCfyUNcFpnx7LPOJBUBN3FQDsev9Y2pyNQfSH4p0/0gzxN3Lyq+xzU/H+LA3Veei4+dqZbvuIXQ2ZCn51bTQtZzaFVMtxe8R/ViUrYypdVX8GW9bOF8sRukc
*/