/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PP_IS_ITERATING

#if !defined(BOOST_FUSION_NVIEW_IMPL_SEP_23_2009_1017PM)
#define BOOST_FUSION_NVIEW_IMPL_SEP_23_2009_1017PM

#include <climits>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (1, FUSION_MAX_VECTOR_SIZE,                                           \
    "boost/fusion/view/nview/detail/cpp03/nview_impl.hpp"))                   \
    /**/

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion { namespace result_of
{
    template <typename Sequence
      , BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(FUSION_MAX_VECTOR_SIZE, int I, INT_MAX)>
    struct as_nview
    {
        typedef mpl::vector_c<
            int, BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, I)
        > index_type;
        typedef nview<Sequence, index_type> type;
    };
}}}

#include BOOST_PP_ITERATE()

#endif

///////////////////////////////////////////////////////////////////////////////
//  Preprocessor vertical repetition code
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

#if N < FUSION_MAX_VECTOR_SIZE
namespace boost { namespace fusion { namespace result_of
{
    template <typename Sequence, BOOST_PP_ENUM_PARAMS(N, int I)>
    struct as_nview<Sequence, BOOST_PP_ENUM_PARAMS(N, I)>
    {
        typedef mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> index_type;
        typedef nview<Sequence, index_type> type;
    };
}}}
#endif

namespace boost { namespace fusion
{
    template<BOOST_PP_ENUM_PARAMS(N, int I), typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline nview<Sequence, mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> >
    as_nview(Sequence& s)
    {
        typedef mpl::vector_c<int, BOOST_PP_ENUM_PARAMS(N, I)> index_type;
        return nview<Sequence, index_type>(s);
    }

}}

#undef N

#endif

/* nview_impl.hpp
lL4H1SUBbRizY1/7XqYYbhmgM7Pz505vV8yDNouZbZH/QsXibstzm/rimQbVEy0Lmfisu7AkjXT2O/LZdX3Vs+vOg8PuyLZugHM8+TcElWtcIloBcT1qiNc466xy4+lafE98ZkFY3NqbJega7hHPi4V1zV6pm2JwXzyfFvbm/JradA1/YIB5IC3N6qZmurd5KNYXYbfchY5TOrSzzC4sP2Qle4SDmpX3KXeVH8o1LuaxAY6L52ONkp9vhn+Un7l8hfGJeZQ8vkf/OTGBrn9vxHomTPWZKLSAdCmWPKaG12/QnZ4t+Rhhr1na1cMjXbQuZVDb03UZ7XQekscI98TnC1y47s4sE5SW9n8FjbBG1DMU91VVT/0TS3uEIkbIIerZFPcBv024TnsnB1p2ZjdHTm6hmAttMrN16TrdojyLqvN87Ru1mfJEa89sZOyE07SXKeq9Lp6i6rq0rHzxIpVXTG0rDjTIq5gdLZhZ/dg++WlfhZaGWcUZf6+nvSFaCWZPXg6uSHtDtLrMujcesJPKK26EtswyeD5TeXFo/ZjpDtjbUruUMIIfszP6wHG0V0M7wmziB8sgSlfSCE+YtSo5tS71kcMIFXgMQ7NbqC4OdQzfch8MpfYsZQR/Zv0rNj+hWICG2Uup2/rpwHmDqa3R3pqk5egx+W/aF1cwQiuDtAqv26ShulQxQihIo+9lobnRxrB0ns4j+lOe1XGc6aQVKzkiSLGYmurYv/Q7ulixJLRczHyr7fdQfLWM0JSZ7sqaQbSHRQsR9iuER9Ssr9urmKeWKE9YtnXlM9D+trb3dDFo9ZgtNi6YplgS2gajtMemXlG0L27gPZ2jIY5rnbRHAaZ0isU3Em0tjNoazd7YCGWZ3T3acpJibrRmzE6n/bZPWVs9aM2FNYOI8KVZB5aldbeJEdowSz+9bBTtKdEK6KSNjPKZTdeOUCNeA6T98raXXrEktDJppd3r/UtJxaCbiE8YxYfmRqvNzJU5V3e6xnXDeuql9Zp/6jjVs6cRClmkvZ/9YiblORjXZKO0Gb33faW94UhsF5Zn52P3KtKecowRGoE0c/oF4dSeaM2YPYzvvZXac6wRciq/B47XscikHn9Q7L8ZYZJOWlbfwTupzcbjOsHsZM+g6VSXCUbIx2yuSXeF0kWjgbRmrZvQ+YR9ohjXwjwR0+tQu6D1YJb7u/Ms5YmWh5WXtNZkpz36ZCNgsGQvKzWtRfcaU4zQl9makVtnUf+hdWcGMzqsozabKsaEMD4mEtCKMpsz8upO5b4ApuEcE/VsgfcFw4tuDKG9/XQjlAJp3ed/eUL76WTTS2tbJO88Soc/dHfAIK10ne116bNUsUbYBtJ01+/SvYZjnhEyiHQtk/cyU9dE0z3KIux3vbQeJ9ytaU+yNOX6IEx830nco6C910lL18jVnvKMM8JdX2nLM82fSvcvuCg5WLrRv7S0KubeJPpPWLOXw2bSXvt3I3Rk5i5dVH7WD82PTH0v5UELJVN/t9q12QiHxfxrBQDpDX51KfYdeO0AaWdOZZKfj0SrQKZuF8dOsbYKKxUyexC1GdpRVl6GmLMFyfYb4RxIq7ssYhnZASPEMIt3zltPMRwU7SJM1S5oftLU7YIWKk20i7hXPGSEIJ34TXC8V6xdsEsNem6IDfYQpDU9dmwTnV0cMUI1ZlUz9ShCz84SRLsIS2kXcT6Bto9ZWNC5z/RcDRtsMLOzkTtr0xnEMSP0ZFZwnysfnTOgdWSW0i6iLsdFuwhTnSWgKWfNbfBMwOl/bqxicEKMCWE0JtDiTojYhVHsaEknROzCUmIX5Z0UsQtLiV2ceZzCucJsX4WMdFYSiZaF2aUWj0xUF7Q=
*/