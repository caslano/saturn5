/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105)
#define FUSION_DETAIL_IS_MPL_SEQUENCE_29122006_1105

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/is_native_fusion_sequence.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    struct is_mpl_sequence
        : mpl::and_<
            mpl::not_<is_native_fusion_sequence<T> >
          , mpl::is_sequence<T> >
    {};
}}}

#endif

/* is_mpl_sequence.hpp
aiDPDiFMYnvH1enGSSeo5ZnYsj/YJ1RYH1+RgI3lF/H4j9EoZeyK7+79s7P5ycQv/vO4v6UXNusAdC3qDtintJg9nY3zWakVzRAgoI+H9mg3PiQXgmu14QAIivP4pQZzyznLXWCBDGZCE9knIlmlgjVOCzLMdpCFeENVFtn0OcptSWL9dTXkXhsCD9dXY3hAG/dYhDWkZC6TYhSww0V4fWcf0oYPV+G9vYRBeE2Ut8JmEQBfX+qn8BF/1PE7xXIR3AB+cTHYGFzM68g6Pa05nzv+t3f8mXppSuBN24eo9ovDuqo0CxGFsYnwjKTh3dIpPeLvV/Kz4Q1kMvc+3XGzErxwRQD2/hlkq85WQNvB1gHhPYle8/prAV/twyFjGbLmamxevtyWEYhhxTAV8vYy4CUG27x8GbcjaCc0LaMOXr/qwDL4C4Bb9YgnHd4XaxUL5iH4Rd8Hr0Z4SVTOmZcI+OH9bQj3vTiq9pbz7q6+445eGO682mDhIF+X7dceX5z2dX9XX3fOTIrWj/2/wr1sdrx8A+7xn0J4RXjgzmllAX9e7z+Lt3F+CdkM0Lm9xQeihPaapoF+aPa9wXoH7gPhGxJjmDbRmVw2mHa/vYSYO52OnYie2yIR0fBPY9vBNuvLV1qsI4p5H4IvGDsbw9efX0xsy66jMjLRzpcSSkBlDB9fpRrirkPgNw0hcPeNykkkJ28izWVSDl29F+blwB/PEhADB5WjiFauJGc1Luf85HBYMq2Y5EV/D8IHog2rzTER4eHgOBjs1GWoOwt/uquDMkobaiTqyL37V6/dHWbPNI/o9xBeEClpYck5jB8O0TBpYV/9a4tNxFuXE0t0TAlfkyX2+Xaf+FXMFyh1mRk7gs7OwXi/O28/E2FtJcwiMR4bwqPlZjNNZQbnP9KWkUlmuhSmKS5icb7o45EVxM0Jj0kWSS3cstWI/rXOl814m8H+hLCalGJtytGP2OP14QoZ54z7E8IrYgU1SfAJ/urNZbjLnvTxB7q6h+A8NzKN+LqzzV48rypfczc24B23lo4apkboEF32cnawnGuHXT7Wrq8Zj06IWBqdLR8Y0vlo/Qf3BICF2CcmJW4AO1goHy8GwwiAtzp76tdwvU3InHLXVHx2eAhxNqbzYhfhJUk2RKcalc03wb1LLp2PeemwntkSZNKNvuc9GMZKV28Ws6A2NTo7uZhVVI3/ctbET4Bvqbe3+EJ0FMV5kUd4/VJpHBTugL/e1/C8sNpm5jDsxQHX9ZG+rllS55Jt++iNdSuAY0dX18/juhZus/WJAxzWn24u/qzTL/dRxdrQBrg+pEz9Eq59HWOdDy5Y24yrWteLN5c6MOGDDsYUwiqideDJ6wzYYeEIx2evf3E1Jj+ffmftIrwmUloXRWETPO5cCvsWwicSrTbCZRiUcNAYOniwTF5czWBqNHP6bagcQawOVHAVNjf7e9UXpYb9np2Mdx4zyAndYRkVLtqi4OZ+WEvm+bXs+OLqqMM+0uk+WaUEK27ELk5mBxgMdwQtNhMXuUpFiRF6D71VPgvsBxBnJD5qqRNlI/BgFby7vgDWUGBvqevB0ea5B87H38BnbOZispq7LWXU03Fdixulw97VlZGVFDRzCi8TcPaZnFtg/BFUhh7OG1xJapsylubodr0b9GviqxHeEiuMcsybEX9wVK8y6riHEnBctBafiMmF66zLCL9XrwoWGPOOFhOJYpk6a92Iqdcg/dr/HlRPQ4YxHpix8NKyvGB/Ed9/89nV7EH1cHw+5vx0iw+EC1NCLBIeU+pdOfh7w1rUYgpRiZeiXR4xxdvG/2YP1iJUV0GEoMEUbhAQfzM9C2w/v9liKSmM1YYaSWY=
*/