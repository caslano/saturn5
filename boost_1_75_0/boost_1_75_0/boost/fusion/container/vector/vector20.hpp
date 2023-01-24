/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_VECTOR20_11052014_2316
#define FUSION_VECTOR20_11052014_2316

#include <boost/config.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/config.hpp>

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_VECTOR)
#   include <boost/fusion/container/vector/detail/cpp03/vector20.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#endif
#endif


/* vector20.hpp
s/htMWX3GfLSn8vtPqnoaKg6Rh0ku8/tTdh9wH3WP0GVIo8EbaXp4BqlfgKGnj8kdSecIaT/MXset/kMKu0/wEQ2n6skujSQrHR5Hy0wmd2Ss+UqOa8Ber97o3Zx4N330K/fGyCn50Tl+DpePlEv/4Qon6jc9x5ahBinckWeCi4Ge1ASgx+swb/TBPxYgA/2bNJMlAgFXqzWzURPv6815niPzERsiq48gJaRkfynvB9/3qgZSjIw/uVjujddYuiNFLSZXPwb2Uw+OEHP99kTbCZvsifE/4LXoXaizcOatRPteyfUTlT/MKDCsT2ICj8+LFBhbGUjO9HWvy1N2YmG7Q+zE+W+z+1EPfYb7EQP7GvKTnTs0SbsRJf/h8a6+zg9tx+nMW88jmN+97gYc/tRBl9/zVl6043CWbqBYoFK8sfKkbXQKctbNeDOllXv8k9gfU1JUQvTBtjLhkSZTJn+4Zdl+qfFZfrv7goRe0yFTHA1OeXcVO/pzvblLwInLrsdeCgTgxpAewswIWYz/mEmi7c3YHPf7D3N9LmfI+H0pm2hM32fvSw9Cs4k/2aKdxXc4vMPEQ4B936DBKvQmxp/Tyv7BtNGIojb7fc14HW/FFZF4AFjVWciRVWe0KquNVS1y1DV7I28kNO3kKHWIeXfFiZTJQwv8BCdwLX0xDurh6R2hle94G67kOBm/8zV2aW41T1ts81doWQiqHEb
*/