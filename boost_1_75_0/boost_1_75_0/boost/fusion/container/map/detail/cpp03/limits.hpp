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
elrnG5MuArrf9fXWMtKuP9y5vaXIflVdsAxtpLlKOrfnV9DX+7Pp8UJPYD7pOWbrlKY4HtsZAqy9mcFXSG+8IXnLzJqs3mhiThTo5glJ/+5usWNmB5ZXcD0FYJdX6UcbXQEzEx88l7gPxYwr0t9zjtIGaCa2AKnMRPPGX15nR4XOYqRm0KzxTaRs6SzzsArnNORXmoy21uMqk26lvaXbNbjnJgtg0NL+dR6wtO9v7wnMROecXE69FgDlOKUtrIREEAkCm47XDQDb+yCT5Nq3sZVFrRGUC+jYeUH+cLzsMWv7epU2musuV1zYQOu6wGiS7wTwhtP7iQWixGuuUieMST+9AKwOMQ3GMxz4Kw1uYn5yAQwaMsdTwXqrMr2Qx5tGST21MUYQhm3FbgSrC3wyTL4XRwFRXuy9d3i1TfkD0q97pAiuB/5hnvT54L/Ufzle4c91wk3/IF0EYMQfoQmBLJprXxtQWl+O/k4DM6v4PCtQ/0mPtTRmYhNiPCDZm94fuARiMP7TBg64/gLfMD8ehegZy+zxdkfH9hb1iDgVK9egdIvOUshvE2buVdQ4vE2cPvfQ6WKdUVRsulQU6rGF4eyjBOI2MpfYC8av22FxsZJwBSWepYJ4UwVX1TUmytFG4J1z6nS9XfB/9Znd7Dg+jDkl9t6Lr4STZ6va5Uo+pyBUX1j2h7YtEr91hIm47Vhh8FzZIXdG7yOe9IfS
*/