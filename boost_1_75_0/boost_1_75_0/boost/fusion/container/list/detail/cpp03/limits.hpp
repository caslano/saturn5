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
UsZt1O5kHMZlfN63ITIev9+ZjN/r5FrGia+7kfFE33pkHPYvyFjnTsZhLmWscyHj9U0aIuNH97mQ8QsdsYyf7ehExro5LmX8RBN3Mg7lMvZo0hAZm/Y6k/H3HerK2JA/I5TtQUvP5XvQkJBRYH0TC/moYp7n+9CXp7FfvBf84lgk502hipwDPMTNY4uwTMxTz4jhNZfzEbv9Y60Uj7dKpeweox7vDyq8738TeTFjkShoiQr6iL6wFRE01LCeNIv8kvuze0nycOr2Xm8Bbi9zU37jbsp8FdlrglkaAACOVN4vQWjx0GxaCm3bCsABwEh6ge1Dm+jt34DNZ//sIRhKcXiNXI9j83ahGES6UDJIfN+Z/H7dWZj/IO+p4DOAUJxED34iUdK3r7EoicRNx2y6JR5CiLTydkvs/6RAiNTXG4dI7ZrgEOnvQrzdq0kGCZFSLC3v+mJWpNh0Bg8aIqVYHjzvGCLN9KonRDLPQDzvDjwfTHk+p7kdz49wns/2sud5Fue5BhIFuTTj8zgjqTDaEtmcxi4pBPEkdklB43ocMRLd8ZFGN9ghCun0jda5YeTNORpKmhfia5turyf2JyH2Ai/ZRKEA3mV2O/x+6xAYzeEFV/xK7WlPJQO84WoMyzCaSdXEkUwKgYPNNHO/A4unvBIJR6ZUdYEpomYG+QCjjh0+kM681nTmtSr0tfW083eFTPGKMcMCOQvSqvMa
*/