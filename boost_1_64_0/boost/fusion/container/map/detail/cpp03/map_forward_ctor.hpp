/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAP_FORWARD_CTOR_07222005_0106)
#define FUSION_MAP_FORWARD_CTOR_07222005_0106

#define FUSION_FORWARD_CTOR_FORWARD(z, n, _)    BOOST_FUSION_FWD_ELEM(U##n, _##n)

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/map/detail/cpp03/map_forward_ctor.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_MAP_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_FORWARD_CTOR_FORWARD
#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    map(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type arg))
        : data(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
    template <BOOST_PP_ENUM_PARAMS(N, typename U)>
    BOOST_FUSION_GPU_ENABLED
#if N == 1
    explicit
#endif
    map(BOOST_PP_ENUM_BINARY_PARAMS(N, U, && arg)
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES) && \
    N == 1
    // workaround for MSVC 10
FUSION_HASH if defined(BOOST_MSVC) && (BOOST_MSVC == 1700)
        , typename enable_if<is_same<U0, T0> >::type* = 0
FUSION_HASH endif
#endif
        )
        : data(BOOST_PP_ENUM(N, FUSION_FORWARD_CTOR_FORWARD, arg)) {}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* map_forward_ctor.hpp
vIgcQ9oVsR2SjpQhFche5ChyXjF/QzzIemQH8iJyFGnmo04kD9nic2Oh3eIWt7jFLW5xi1vc4ha3uOW7zP9HBNNJyf9nxPD/vH1UML5lqGLrN8gPt04x/BXJljgxxQ82JM9XXXL4Pdwo5FtTsiFlitUGTGhgrreBQf0ot8d3Bb/T10zxPU0V35M51Ro7U1Lgj8xRRzSgHzrzOz1oh7++jHmFRbxaUeBhxzCPGamvzNifl6Y6x/40U+z8WvVdmfqucpqj/Zhfe2yaU4xSbAS7Pp0WsMuNdXBjHf5/Yh1mm7EO12+cvOXmLgv/PbHyin98GHtmVc2xDqVROi/CDQ75fDLkQ8iEbeBc+Siy5aPwwEEwB06A8+SrzIWzYR68Cs6H18KF8mHnQ+nXOZFzpYP+KdI/TfpT4Eh4qXw40+FS+ZbukG9pG5wJH4Tp8HF4OXxWPqfn4exq35fOi+h18H31ku+rN+wg39Fg+YxS5DOaKZ9RtnxGPvmMVsCRau8o+cIS4a3yFb0Ak+SjHwv/LV/bqdgxATaFE4PfVNH5D651+BZFC/UTYvbTeXAgvED91AYmK5bAA2PhShgHyxRDsPvUKNen4uZ/cf0p/yf+lPNKyB2PJCO+Eten4Ra3uOXEy3f1/v+8LN8Jv/9vPPs/0D4q+A5VNz13pyPmt4v0jlbCOHue8VyyOucUmS+PZFNXfo4vp07PkLERvlm/VXrz9cyaG5hzcNQrnXX4jmhNOQRi9Zw/TM/5A+GQrrR1fPg7pfOySvLr8p5QpHc4S+zvJwb7e69suF0xQJv1Tl7VhAg2ZPA2KnuwofMu6cH386jPzM2t9xbsNtpyr8fq3fFV2NoWlkJvSyMhYvAdGyrjha46vNOjd1RkQ1Z+rpZZ3nfKKdCyFPt7rsE5hxJzmddvqL7Fu2+i4hzP8//+JuR3/0n23/NCft8e8vs3Ib9PnWz/PSTkd37I720hv38b/G35bqs7J+LOiZzgnIjz91y//bmSW8y5kuZPbou75PPRn/3wmjtf/0t2p+drniuZEKXriK4vu0LibksVd7sCJsCV8BLFW06Fq+F0iPrqXNqqL1/1WXNaZ+uZ3gPbwRwYD3NV/wLFcS6CSdArPUUwHRbDudAHc2GJJWetrhFcO9AbkrP2PM15nK/43paa82gFL4WtVX8buBi2haWwA7xFcwxbYGf4c9gFPgLj4QHYVfG/3RX32wP+RXMtxhxMbxgD+8KeMAH2hf3gQNg/GF+r64yuP7tC4mtnKn49HXbUHNBEzQEtgnM0J3WF5mgy4GaYqfqpWNcI89pB/f449OOqf4jidofCCzUn1FtzQgM1J5SqOaEFmhNarzmhuzQntBsmwlcUR3xMc0OnoXQMjINJ8CI4Fl4Ox8FCOB5u1FzRvZor2gMnwYNwMvwCJsMzsX0K7A6nwovhNDgbpsBCmAqL4XRYCtPgAc7jzAfV+i3Ghs4DJS7+9uaCJhRFng9KLz6xOaFEX83zQjt9Jz43tLPk+zk/1NBvF57MOSLze4UncY6o2YqTO09U1zmiiqXM3yLHkdal0VGJpe48kVvs5b/1/J9TVHTCz//Gt/0GGXmUUnjWCj5u+or8mWiKzRyAs7gBqUoN+TvZGIoLC4znL3MO4cftuS6H5ABMQc5CJmsOoWqs/5k2NTXD/DhedW2YVFz7s3XguamsUaT7+Uj31ZHuSyM9T9X/ucn5PjnSc1mk545IzxeRnpvq/3zk/LwW+TnlOfM+v+qdzORljc/82Y/G9+yxpCl16H5e+1T7Oq+R/X6+SPfzJbAHXAKHwqVwHFwOJ8MVMA79x9fzDsL10bXeCwXvg2y+MPu9D/c9uuex3evIx+Xo33I=
*/