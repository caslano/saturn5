/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR50_05052005_0207)
#define FUSION_VECTOR50_05052005_0207

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector50_fwd.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/iterator/deref.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/container/vector/detail/at_impl.hpp>
#include <boost/fusion/container/vector/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/detail/begin_impl.hpp>
#include <boost/fusion/container/vector/detail/end_impl.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/vector50.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/preprocessor/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector50.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector50.hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;

#define FUSION_HASH #
// expand vector41 to vector50
#define BOOST_PP_FILENAME_1 <boost/fusion/container/vector/detail/cpp03/vector_n.hpp>
#define BOOST_PP_ITERATION_LIMITS (41, 50)
#include BOOST_PP_ITERATE()
#undef FUSION_HASH
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* vector50.hpp
LFbSKFIyaS2piFRCOkEqJ7U4zjjfx/1xbzU9XaH3/3Tqd+nv/5X+/2cp71I4UdaRVxqM8K/0AZjH9dTx77H8u7WX4d9zbIm52Vm5ztiAd4OqHv+/9MYAi2H8f1kShcn15nmN3P/Tztr3+/nLPf6/+X247/fz5s8dPD8vuMFx37v/8FXf/WHFD59vqvhye37TT4ZUxqJLncu2qF/LeD2Lklj0CdgNJ2I4TsIxGI0TcCoWY/BJ2pmRtOuHdu2IkmuD63UhhhSZp537Q+U8L+d4w/k8Wc7V5ST9eZlzspxzjefaIDmvck51O5/GnfSf0/yTf/JP/sk/+Sf/5J/8k3/yT1dmukL3/4Q71sz9/3gl9psOLGs77+/zltltlbGU2r9vNP770rSsfn3l+cD3xGtYHc8PXCIwmdrIv9sd/z5r3OR+feVfnc8Ong+yqHEna+XZQX0njvdiE8j75Fhd3IljEVXHdurjNE56WG6Zbrmywl6PwV85DkJCbfOxayxRl3fsmoGS/0nyr1zH1vghTlK2lzP/pAxbYg6BHpmZtqy83GrGRMnYQerYK/r1t0tbgkWy/hkSK2QZ5MifWo1P4mFRns2HvF1jhawmsUKRg9QYR0N5Tkh5Rkt5IkmnmSc6XC1Pso2qzV5W9TMn9/hKY91PlPYEfSWvnpJXsVtejoDOaufXS/I7JPkNkXewAyX2N3Kslh9Rtl7n4xpDGG6I+TWua7jE7o+UGOwRsq5l2nZWBmFxHp5eHEMSe+2xbnd7yK/QJT85bC85v9B6Wr8nDUidSN8p+Y3V8suVwFhvzhGSn6GOm8jYe3YSnxm27UnJ/02JGTwk8Zdl2r6kPDf1Ot5OW0/zsXeMsYKECspn4fp2EaYx1sbjLUoete1qSKwE3olnlXJfr5VbIjIdZT/NPBcbB6ZUHQfmqqZThjrHzElckEhhnOPoFIw0jqNTZrKuFSbrwJfc1jVaXS9nDq0M/ffPX5zC5q4cK2M/OsdYS5XxaNR+/tMq8yjByVYtplL5XoQ2nxoXvbypLF/KW6idW5WN4/ieXRenK9sK9fGnbBeX8bC2q387h3NTPuNdvIxNmLekspwF6me56mfF6ncpl3ymnfMZBE7qIRJlrENp6yTzqPHPEtetlU3+wdl26BSfjWKfyWR7BA3V2g7t1pajjoloGD9N9rNmcnw2leOzRDs+87KVgdlq8NgcXLmPS9x+rpx3s0jRStz+eGfenHOdw0bEJ2fTJ1M8o/BVea2rrMvGjjIkmrW5MJThiJShVMpwmDSVMiRMcJSBK2x8YoY9NZFTFINypSXpfm9UGW+qO35cx1kznKNGSfsBG0kpTrKUwT5RLcNSX8axdc03UMvXMDbMKcl3gJwbw0gx5FvmzDcjVTd+h2yCEeOmeD+Gh7Q7StW3PZhmdcRVq+ePSNk2Msai8TeQxPg/Jdtmj9RL5CTn+CJJiVnxyYsWZ+fZamabKH9b1PPKIkNZfpSyfC1lOSNlsU7WyuIoSg3tH+5l0faX0xIHn8DGDsFYnMkCo6c4y5Kn/DK1L3OUY7encsh5f8cs43m/2KVcreQcbTwXaeflti2Uz7mBks8OaeOR5mRnOtcrRrvOuZyXcyS+Xn9ezuI/nd9L1fJ1GVdpkZy71eXmVH4n1qUOI7VzrZwLdNcJ7bwt8ySpeYep56wlMoacWmYKzfcM4+Sx+vJZtH6sdGmfqrywPcU2W1KHd6DTZewIudZ1sEgMdy6Dv+vOz+XKdq3BmOzL/U62pmK4zd/VeoqZ9v1dsPk7X8/9wpm/+/YUq+17LHhNxXYvylc+H15e3mKhrd57R/9+4myHfbZ/XbxftTCLPAOQe/hQ/dge8q5acSo=
*/