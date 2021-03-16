/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FILTER_IF_07172005_0818)
#define FUSION_FILTER_IF_07172005_0818

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/filter_view/filter_view.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct filter_if
        {
            typedef filter_view<Sequence, Pred> type;
        };
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::filter_if<Sequence const, Pred>::type
    filter_if(Sequence const& seq)
    {
        return filter_view<Sequence const, Pred>(seq);
    }
}}

#endif


/* filter_if.hpp
LtRx6Lz/+gxMgOIZTp4RYMzjlsXhv21kz+fCXp4R5Bkp1HYO9lkWyJ4vyDOSPKPAmOv3rM3/9GTPl+QZRZ6vwMg9glznE3rffsGe0WDmKOPnK/KMASN7Vq4Jm8rHL2LPWDDzNGu/M4Y844Q6noeMabCTPV+DqamUZxx5xos39/sEMOpxy3jyTBRqO/vc2jufPd+AUa9rTSTPJPHm8iQJ+/oziTyTwUQZntCUckns+VbYx/Nk8kwBk97ZOB6buKU=
*/