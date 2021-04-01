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
wA6x2fAN9F7Ir5tWVkvy1npcOCn6HgoaO05yrSdpCOgmRBM/u2HjHA4ROPwE1MsmE8GCrECsxlJnTdS0T4ON6n/N9+DjFEH6osAg+cGtSVOiXE5OClMkS7Om0God4vlQB1NkvRMHi6X+hu6X1xkOuKZSkVL/8o3c58k7jZKMmOhmBsrDlYa/uwkU833mRzlN7gCRcUqLclOq6qESY8via0lnSvNov6vMM/amYVPTEXz3dO19ZWiP35UncqjyYizGaZnk3UpiEpOSMGkJG0/K48+zUdvBph3CNiy3vRzBalC9SzaDVJCJPv4xszdYU4BqEuQGPzakdqsGmpVP/4shgP5kR3skJAIkvo4iEhGN3K3pM84g16viZB0iatvvg6okR+bXZb7HdIMdegFJktFYOEHnrxDVauHPqXPn257ztf8GHg0EdPnT6lvJCI8uBR+iOki/RkFVfcJ/O4nDH8qH8p8y4ZaYwxHdeFOER/+FKtcBlzoXai/NYhkeVYhBL2EoaQOE+0HF1QuvR+NltMdqiQjE/6CcKSNbNyFPIrxjcYaif8YH1b4HCJzcWA==
*/