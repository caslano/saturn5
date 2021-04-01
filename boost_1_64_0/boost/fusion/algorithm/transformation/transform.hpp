/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TRANSFORM_07052005_1057)
#define FUSION_TRANSFORM_07052005_1057

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view.hpp>

namespace boost { namespace fusion
{
    struct void_;

    namespace result_of
    {
        template <typename Sequence1, typename Sequence2, typename F = void_>
        struct transform
        {
            typedef transform_view<Sequence1, Sequence2, F> type;
        };

        template <typename Sequence, typename F>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
        struct transform<Sequence, F, void_>
#else
        struct transform<Sequence, F>
#endif
        {
            typedef transform_view<Sequence, F> type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::transform<Sequence const, F>::type
    transform(Sequence const& seq, F f)
    {
        return transform_view<Sequence const, F>(seq, f);
    }

    template <typename Sequence1, typename Sequence2, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::transform<Sequence1 const, Sequence2 const, F>::type
    transform(Sequence1 const& seq1, Sequence2 const& seq2, F f)
    {
        return transform_view<Sequence1 const, Sequence2 const, F>(seq1, seq2, f);
    }
}}

#endif


/* transform.hpp
kCadc6+v1mR469IscGHJ48VWXReFmKVJuWuk00YSLnlc11IGe0+8kdSNj/wFk+vKcVGbJ0MKX3ZFyPDoDzKzsA6t95CpoyUnb5wtRuNmMmCwPeV4xrVdUwQoe0hcqF+R7phYz3RYikKNpK5lBRpWRNvKXwMrSsANdm7eU1bWTg/p887PESbC9cGDlL/HrLl6ed5HreR9xyG9ZkYKQ2O5VY8+zJSv1Lbk/wfOXMUaubJyrpq9Xtd6ZCbTqNmfpDRxVkmIDUe5RTitUhWBMge5f5llVw2Ret46njgJK3mRG1vpWQAm1x7im7NZGedrabpXZX2j2qXnz5p50KGnkEAGIt29Ww+gAWvurDASLnsoV3lmXWz1z9yMdqLyY7o5bti94DXCQEr+uJPJcCkWf2DYK1fPm5TlfsuS5shtJM8noAVk6xodqVNu7tzkcIXmEBLAcEdtocjNpTjhzsa85kV/B2r1T1tUAbNuqJy1hQYlQGv6wwjd4LigM8xA4x2VWKSpoRAVmbrt3m/2rM2Yv2lQLBfrzJTQlU3Ov85PKroIe8VEvovfYld9M+gA0Q==
*/