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
hQ5tPG65//iUjBO5x0uKGhkj+uAs/zEip2/8RPbg947pFOavr5A9+C3GjTLV+seq0jDdOLhcJ6OhXKvWTvqPJ02AJSnu+MXGvW1tbc376Uby0M3L8dvDdVpW1qI505dkzQp1T93Y3p59XL/vNYItNTZkPaYT+tjQDzUG9P+2RvAh9xhQxAUfFt30gS2737yi2duOu+Y0bQwooo20f+kXsuUsj/bSV/SUb5woGA17wVjYBybDfjAN9ocOOABWwMFwIxwKt8NoeDccBu+Hw+Fv4Aj4OzgGvgVj4Qk4Fn4Gx8HO2BIHu8IEOASOh9EwEU6DyXAGnAAXwYmwBE6CZXAyvBJOgdvhVHgdnAZr4HR4K5yhP58+J8C58zJ2sq2l1gbtb10f1JR34x/je3FT3on/X9cHtdS78BHeVetb31db/1r/Wv9a/1r/vsO/7+n7n2//lvn+76fz5T8i38EbO/F+De1wleYfmen7/s+YNn9Wblmp3VFcqvxweP+2+ptBotgyKfIEXNCmjXs8oHipjAeUFrp/z1rqPz4QwY+PiYgflcdfkt9Ot0/LisqV3j2Z2vj7Z3dnrUJ7Xrwffq9DGG/D9iqfr7Jcxwe7zm9LwgznQTk4gMszrlDD77JT5Zy3XPRK3Bx1bbH4Dqu4Bv+U1e7f1coP3XPOVJXyfV6r/GMS3b4wlKXomADJr/Iry/LpSABG//R4b7w0eJ673Fa487CD3yUjtN+rKnILy4pdEncL1PvAa+dznbLQ8x1zaKj/+Vyp8sq0UMZF0pHf8B/OZe7rcytc5dyA8dggfsONjIXYVHkQU8JAWKXR1170P9zOPC5TRH2sX6Ybl5EqOSsja9GyEM+5+ibJ+qyjme3NZ/qs1trB8gB6Qzzr6pukxs/1aeoYUaj7RVmPKX33Y0Gt56L8sGNEH7rHiCKX1hRfO/yyul7jwoddt3jgH5s4RtROnhHy7MimbHJ165j6ynzpYJgCR8LpcBTMgqPhMjgGlsBYWA7Hwi1wHNwF4+DNMB7uh+PhvTARPgKT4LMwGb4DJ8A2MtbTG06Cw+AUmASnwinwdLgGpsJNcBrcBafDh+EM+CKcCd+Fs+EnMA12JK9zYE84Fw6C8+AMmA7TYAZcDnPghfBs+AI8B34Mc+G3MA/2pMxWwHmwAN4E7fB1uBJ+DIvg32AxPJ16uwbaoQNWwRJ4HiyFm6AT3g7XwgfhufBncD18HJ4Hfw/Ph+/ADbBDB+4lPBleCLvDav43Bl4E4+HFMB1eApfBTfAcuBnmwUthFbwMXgm3wP1wK3wUXg7r4JXwXbgDtqet74S94NWwD7wWjoa74ER4HcyA18MCuBteBffAh+Be+DC8AR6F++Gr8AB8Gx6Ef4SH4F/g7fAreAeMoP7eCbvDu+AgeDccDu+BY2EtTIL3wWXwAVgAH4R2+JDy45FnJVwo+yvr/Xhe0/TA12Ef+AYcC9+Es+AxmA7f0p9/IekNRvIMY45z1HXyrIIjra4LcWyy6mDr3kWtY5OtY5Oh7l3U0Jjkvi/Zlwg5hrT/qnVs8n/l73v6/ndUuj//m//9/9tRvu//TfIdXyrPkGLknSSeyzG+7//0BQvmLcnUVrXlO4rzK4Jeo/2g5+x9V5VufUfH3v5rsTMtvg+zod+3vnz/nt5dze+7v2E/99gY9m6S/5qbvLbmPL3NNbaRVnlaSfnYy1lFXBrM2eKh5k23zjykvF3qsTXsD4a8pbYz5+1Nrqm1ypvsFC6bZbd43vR7U0dJ3gz7aQfMX9QoT/6OJfmv82sv3+EViE3y+RrXpI6yyp+sEAthXZoxbxMs8pZqyJuUgSkPd0geXk/yX3f1suThPMlDJfIK19SZ81A=
*/