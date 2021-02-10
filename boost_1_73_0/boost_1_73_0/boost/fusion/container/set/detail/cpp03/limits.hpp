/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SET_LIMITS_09162005_1103)
#define FUSION_SET_LIMITS_09162005_1103

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_SET_SIZE)
# define FUSION_MAX_SET_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_SET_SIZE < 3
#   undef FUSION_MAX_SET_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_SET_SIZE 10
#   else
#       define FUSION_MAX_SET_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_SET_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_SET_SIZE))

#endif

/* limits.hpp
JKdIR3TWGXn0rSkNsVaOdSFW8uHPRFAl8BEETdP+Piy7rUXatWboV5pxkPrTPhfcKZiXBckKHLdiTWqPyB8T1iymbgJ7PHXBkNMtKDzJHVyvhONnCRtWXv+2nHbYk6sW/yLipYjD5MPRzPfKC1w/W6H2b/yVSF43tDhM8R9IfhoCCNwk5mEWcy/ia4wQheNvuycvwGNMyo2FybU57l9xU1WmM5KHAJGE6QZFkKYaHxro7aYPN71SiVuV/sqJksQnIDGnbU3pVBrywMO8bJ4470rIHgqCMlRVOLmGnFzFBwnOYp9HTpz0hD8SjRnpuWJatCAIRgCE8QTTgTUMxO3UQGUVvNzn0l+98eH71y1QCK1IyFgkof90Qs1/1AY2VcuY3g5giwa46KaT2vihTNsc0fMftcEHpG+SZHNxSoYftHKtmwuqVSCHZhZIpRpzzuVPIk7AhnusuUDfqiZMD3srAeifwJGpvX1er+r9oezvJ94/Zm64jaAScXnOIWHTab0cKV+CiV+/cd1wCjNGCh4HIs+bktu74pfYk0V/hSwzlbXa4k9f+qEUEzy+ZJjia8mHTg19gr8JbbGVafAGr3cCnMksOCko3YptGO96gerMMO9JwJk14bphaRMdFsNr33lssrWThygjBIL8VeOM
*/