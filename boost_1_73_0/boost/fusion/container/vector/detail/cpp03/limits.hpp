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
rpHnzDbt2O/lfgsZs5jyImbPE847JD88WZ8bxF1/11Kexd94cXOHzY8ay3gkD38hfo9wI2V8L8+7Vcx6uTHtu+lDfiT3n+AxXqo2MXLMUuW5O51u7JI4i0WwB2t4/3lySo9UF7LhennODMKL3sTrRfSFkjZ78Gez2Onu5sbknc9H035eInaz3AxWL5JVxu4aMRvr1lbfJslzWzq+/eca17Mkrra6dg28R/y+lt7JUuxghu5l
*/