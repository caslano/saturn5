/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_LIMITS_07072005_1246)
#define FUSION_VECTOR_LIMITS_07072005_1246

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/pp_round.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(FUSION_MAX_VECTOR_SIZE)
# define FUSION_MAX_VECTOR_SIZE 10
#else
# if FUSION_MAX_VECTOR_SIZE < 3
#   undef FUSION_MAX_VECTOR_SIZE
#   define FUSION_MAX_VECTOR_SIZE 10
# endif
#endif

#define FUSION_MAX_VECTOR_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_VECTOR_SIZE))

#endif

/* limits.hpp
YCegtGPTRhy9rV9DQV94X9P/4VcQwHeuOYGrtMZDVnZW98yNx26V1c4etp8Qbw086B5NAxBXMcK/6dfyk7TAp4tKMPLryMH06cIRiyn4G1o9dSSBw6/4nOI9o52+iPeR1QSAwRTkb0oKJAhQFeMQuIP3EtUaMIzUWF/PeMafRS2DKuHJ+p2srC16OngpPFeQpfF8PHHIJuRpkAARXIGfKNtRw1/P9UHHjhX6vwTgTREyPuzQ4/fGsiHtXbRGF81nJ5Rk11uocxCMqA1JnHOQs7W1E1IgzkyLVjm13/ggmoCLl2/fHZnk+/mbKUktMdcaszkhVs5GeuztfWi+9bXxeHjF4T5/ivYU8FGnQKROcGIceswkOW2fNjYm2Ga9Duxjk7BP6gym9sWMy1oqf3hjMpszZ2CqWMESdF8UQaakIEbT0Gxnf9YQVVXvZNIxr07thoQ9u4ncMwy2CuSA1lSVtuIvTJshdelRtfNfAbBqkQTlSxPf4gZdlLaaXTYSFdG33ssVf+zMzRQikKn85MB093P8AzNQD1/jN4sCoBCG/jDuPR4YdvTtW23s9g==
*/