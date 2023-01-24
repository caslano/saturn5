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
bFke+Bf1q7L+W9N6Z/HxAMdA1evqj3v8AXdCsDd0LhnhvrbpdeSD1ykaOlIzQEWtxAus5wL2CgsAhCfv4Qn22DuwWZmbJl3IK04JNJUaIZxnUmhhR6tzXi462BqZzFqOPs0kHyZCweUjyDxs4PABvuEfHjvnsnKlSKZzDdyYQQHLFLlT7SrfYSS70RVuCRLWnij5g9uoPgwFa37OzcZKuDPeXc/v3sbv5vYSnv//bp4rp3ZnAA1BWlejkvzMaQ6Z30ypRlimBUHRxpZoDVDKEMI4JQw00QJCoYMGpxdYUzRaNLSh9eMYivOc2CDkblhOt5MVA3jmWqGjhAvOQWyPU9cbcjjWC2WhpQK9QdiaFicfmxyB6KgFTi5ghehGxjC40hnzj6y+OxrV602RNh/rDezqGkLFHQMRKhoAXK8LTDHsiggFyOxkF4EAuJamqkljnuGxROxNbsFRddo6svmBoq6YFFnGwhwVb7r6ahRPeZeRFwDUfPI9/JN3NOo+ecMvwFMScPK8bFAge7GXmhiFvf7jvdwKc5isih5Pn88CZmouTJPUXjzHyeeKuS1XY27j6vaVXEG3zki+5KSkGMH2L5MSFF9yxqt/H0YCz0/8OGtUhEHrwB6tpztpl5w7iue+HkPH7FEU+zOG9PT86p10+jwftssYb75xyV/65GsPpjS2JtBWCNeEzin+MLF3Dd6Y2OEH3POx0Fb/lS8U
*/