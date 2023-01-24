/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_FUSION_NVIEW_IMPL_17122014_1948
#define BOOST_FUSION_NVIEW_IMPL_17122014_1948

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
# include <boost/fusion/view/nview/detail/cpp03/nview_impl.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, int ...I>
        struct as_nview
        {
            typedef vector<mpl::int_<I>...> index_type;
            typedef nview<Sequence, index_type> type;
        };
    }

    template <int ...I, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, vector<mpl::int_<I>...> >
    as_nview(Sequence& s)
    {
        typedef vector<mpl::int_<I>...> index_type;
        return nview<Sequence, index_type>(s);
    }
}}

#endif
#endif


/* nview_impl.hpp
AosDzRDrRMu617bRg71hhA4/Dar0bp4dAttuzJmBP08LUxmSlf5oDYggZkl+OeIMiSy/ozNUq4ffLXKI6dmV7XO7pepekQwuGF1X7g4PQpf+GuNwUhjLTRtd6XRzaI6if+bzOooupSjOHPtQkq2Gbf+JJ9it026LGZIuiPepihx5WjOWfCEVsBg7quwVXz+XsLi65hpfCfCAYP9L5bt55S05g6Ic16bNfp6i32/Xgfj39I+vLurmFZReJndTafgeHUrHi9FFMlhJjJvlCG1jw1yMCFvGXNOm73wM43obYW1h+O07WF4sNSIWCi9yxGpfGO4m9O1P+XkNPA46mMqO+XY3dXeneyf1uFNcOWFVN8HYFainv5VJPRBl8DYEuRn/IT36pNi8TNNlpfxMTTHIiRE4GBsAL30F974qFWmhNqUhp4fPrBkZf9penaUyjhtPTbrSW7xP+MT/ICeRpxvB/xF8itpJn+hS4i7F+rNKeeO12h7c1XckF7TGV4kLwsde+5c0nLQhvc+k7aoEm0HuZ+x/9xDtjspiX3bgwb4PyXt4fnwxLDpNeilFsv8qsEi6jXz4+ULg2OdYZS0Foy0BcTjkg0AD7/Jv6UE9GT80lKV/+sELWQCUkgTN7+CsFh7rxZ1HSF88hQshzlV8aEsgguxghqRDuv9DTpiTcwnPmri+w54y9ejI9AqY9rapcCMGjHr28MYarcg0Tm0T
*/