/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_LIST_LIMITS_07172005_0112)
#define FUSION_LIST_LIMITS_07172005_0112

#include <boost/fusion/support/detail/pp_round.hpp>

#if !defined(FUSION_MAX_LIST_SIZE)
# define FUSION_MAX_LIST_SIZE 10
#else
# if FUSION_MAX_LIST_SIZE < 3
#   undef FUSION_MAX_LIST_SIZE
#   define FUSION_MAX_LIST_SIZE 10
# endif
#endif

#define FUSION_MAX_LIST_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_LIST_SIZE))

#endif

/* limits.hpp
AmVnucAZubCiENRRDvSruNYAXbc0IMtO6E9t8yQQbKBJp5STBKQC6YMOSk9NBH0KJIVNGUjecnfrdsY5wnlHyHmEKqo/nUzINoMplOLdaSIxG20Rn0fl+iHeK+wmAZLmOZfE0Ac0qtxttFSuqTXcpD+Eitie+Sk5pmlPS8WTV7HSdJfUJ1W3mSwSdDbeNaYSOMhyDLxkSxx50VS2Ed094Ydmep6TjA6rCN09khX83jhF6T4p1xcaDUoSpNkss3s=
*/