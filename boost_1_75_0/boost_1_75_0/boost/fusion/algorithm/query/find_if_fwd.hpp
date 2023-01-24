/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED)
#define BOOST_FUSION_FIND_IF_FWD_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>

// Forward declaration of find_if algorithm
namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if;
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq);

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq);
}}

#endif

/* find_if_fwd.hpp
R4jvZSJPUOtBWA/Kxag8jlpk/kpMpXsxYMdzBn0qjTtc/qtiFRmE5536bibXml+wf6UJriGbbFUO0RqQRMFPgIPEM0Zd+FaSoNr36y3k+SaeouZCUTOcyDsxfNoocaR8qarA82qV/vRmEs7Kyth/2v9orZXDa7rpPZ8W27LnX73Zzp7rdT67hnp+HvXcCT0/P6Tn53LPU/5xz2O0VjKNPW+0tOx5j/b2XK/zh4+p55XIQo/KhJ6X/sfY86lvUM9vt/zTnkdprcz52NDzMyP0/JY32tlzvc5zuOd7kf8e5Yaer/rN2PMVr1PPP475Rz3P8d8S51K+1Bpa+5Gh89NjWnb+xdeh88eMnZ8VofOGKu/5iPqegTKA2Fwm/zKY/OslktHLBhq8Hl9vxepFHwSrvylKDLYQfB1+Ls6kPPmxK1iTzl//HG0yTMK7/6JJAI6dJsHuGEpOZ93qKDjWwFIZrt1tKZadn3VD8yEPOKr9WvzAoIRI11JQQtVEUWY9RDFrZhoPoIex1aew1ptotIojx3zh8fCGrjVaEJGhHigLyMByRsr9Qg4wu5sbJT9Tf64lfny3icP+bYWwf/CrVWp9U73VEGDvGHeMArXJaHMvhJSp4TK13HmKXnY/lGGvFDRLfmlLJiOSTRS920ROAc0mGhZ5lA8vOEQvGB6BL7TgaTBe/6gM9M6jrhBkjFKJNk++B0keN6pEelZTnxS5
*/