/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_LIMITS_07212005_1104)
#define FUSION_MAP_LIMITS_07212005_1104

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_MAP_SIZE)
# define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_MAP_SIZE < 3
#   undef FUSION_MAX_MAP_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_MAP_SIZE 10
#   else
#       define FUSION_MAX_MAP_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_MAP_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_MAP_SIZE))

#endif

/* limits.hpp
njTclKR9ru7glbvduMLhHVzh9A7+rpnSbtb3+1R1xcAzrPp4Ix87mwNCm2q8aFTjjlwrhTvo27bWbTDUUOl8VWLlJpInhu3xAc8JW/K+/6ZIzv8AUEsDBAoAAAAIAC1nSlLGGC2KSQYAAJUUAAAcAAkAY3VybC1tYXN0ZXIvbGliL2NvbmZpZy1kb3MuaFVUBQABtkgkYK2Ye2+bSBDA//enGCVSZVdOfEnT3PXUe2BY2zQ2UMDJuaq0ImYdb4vBApzHKR/+ZgHbgAFXulKlYO9vHszM7s76lC98ly1gRCSFmFSemmMq69pAHVJFt+iodYqj3Gf1QO/tz7ta8BaOXjT5o3jhPZEwwuAbm8fVNKWvkP5Dqa94P2akB3uRV9qB4yKv0E5EaGblo3im9Jihr8I38V9PSH6l4hG/QTEhKQfrl5A/LGNoyx24+PDhNziDy18uf+mC4viceWDFzL9n4UMXPrrJN38vnefn84j92QUWg+OdZ6rsJY8gChbxkxMywGePz5kfMRecCFwWzUN+jx+4D/GSwYJ7DGTdmKnasAtPSz5fCiUvwQaiZbDxXFg6jwxCNmf8MdWxdsIYggWKo3KXRzEq3MQ88M/RNoOYhatI6BDmHS8KwHl0uOfcoyEnhmUcr6Pfe735JvTQ
*/