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
EvTBvEmsSSAlLDKxWU5Y7USirkk4WFzqdPEj6WSAvkcgeXJT2xbzYVZGAieoUCmNDIb7tpgxQn5ygBcQW+peh6tTApSEFMY7D4VB4pdE+ZrRp4G5korma9aCtMGuBiPdv1sO8dTcLnhnnd404brkpRpU+6aWYx8n+Rmvb2zzIJwc4rnIzm3fCO7YWnU9iL+IxlGz531QFDgXX3tGmdfSK57ZipQf2o9V9kViaY9xEZeqerQFNqOnK5kb3kyw4tqr2eCTAIo8PK61T3pG5mFcjBCPhhJejHMXey0mlDKbqvZs8KmF42phNeadZkDDTzLjR2beJJn7J3jZWyPjQ53HNF+1bZjsoyxf+oW54DLLaqvG+438L9+TtpMmNIyC1srss23WhJk/AWQi8bW6FOCv3QKfisX2MWywZiIkRq3Mw9QbWc/WCW63DT1Z+E+h91NvxtJEuDQl0jMcb70LiaMOd3wBqYrdrwn1iVFvnVQkAkfPe20Mr0y230fPaZ/C8QiP8bFdqAX/JGZ0xff9ErhHHU1HNLHRqS9RmwaeYQY764ITg1W5YIot6WA1AQ==
*/