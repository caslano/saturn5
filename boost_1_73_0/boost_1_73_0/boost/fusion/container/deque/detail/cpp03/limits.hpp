/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_DEQUE_LIMITS_26112006_1737)
#define BOOST_FUSION_DEQUE_LIMITS_26112006_1737

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

#if !defined(FUSION_MAX_DEQUE_SIZE)
# define FUSION_MAX_DEQUE_SIZE FUSION_MAX_VECTOR_SIZE
#else
# if FUSION_MAX_DEQUE_SIZE < 3
#   undef FUSION_MAX_DEQUE_SIZE
#   if (FUSION_MAX_VECTOR_SIZE > 10)
#       define FUSION_MAX_DEQUE_SIZE 10
#   else
#       define FUSION_MAX_DEQUE_SIZE FUSION_MAX_VECTOR_SIZE
#   endif
# endif
#endif

#define FUSION_MAX_DEQUE_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_DEQUE_SIZE))

#endif

/* limits.hpp
po2xx5DEuO5oFmlBW+vB7C4GMv7xPXclYeM48ZfID732Ps69557VCzXLIjmjo08XHwfDo4DPn48vgpPaCzxWmXziTfvlzztq9JKePQL3F+DA2Vmc6/w/GdqnVwfBHRU/sLrG+bkgbbo3uQua9LzJHTWcSVBGOeTrIHgu0DXnxv/abHkd8CWewIwtj/LFRqt5bKlx1KTu/v5batFeZ6/r0XuRKZnQyMpsKvXco8PIPfk9Fuu1b+Q7j6Qlkfilq3GsDJl8ZldCS8J1okKZGRmRMBRJE2o1xY3KyMaSZipBn8/OJ4PhB49WsQpjdrLJl2TifJlEFItbSVqGUt0WPhZCW8pnMIfzSBkLh0ur8sxHbElW6tSwDw4vEpOTuBUqEVMEEpZiaxfmoN0OlzpB9u0oD007rOD7sU23SCZIIhUbyheWbE5LIz3ilR6leaRmfEZB8HCxnCbKxN59NgiVRe1ck5FJwr5gp6Qp0pY0Ksvj8TJaIGNl+WTyzHCoVZynOwtRR/YyW+oMgVAHLIpylNmjJYZIu8UOeRWirKkr8Hdbc59vRHmGZKjeH9FgVKepMMp49GUwPjn7NKYv/YuL/nA8obM/qT+csLO/B8P3aL1CME1yvdDSILgmlS4SJaMy5s872jVMfwEhloIxO+6E
*/