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
4VCKId/IT5NsZhelvOFkWM0pEx3GCcYNh8zrZH1wE+bv81gmLPls9qPyJ2op54q4LLZWLCBxSYYevN+j6gplXTbX3WrVFcm6Qq4rsuqKZV2tVNtDXb3mcQgXmQwQaBdf7CBFdRFDayFPPQzP3DsewwyTc0Pr2RgHXZon0q6CCJWvTA85wBJ6XwetgJS1PD2p1uenyqHKSJtz3YRFpLSgqfRW73AyffCRkwyqIIhvHiSxpHi+BXCKb8WNH14GiAW3KfRyqkMDcpMR7BgNwY4NQ7BuPxOQHgljqVq3PT/YXe8ng/LbcmsEcDzON/lDD8POW9Ue461ZxRMolemdQr5z8z2Gro4vtqrSuaqYq4qsqniuKuKqQqvq5ws8CrzkYnHVx1wV4KpMrvJK8FSK7DDlowx3r6ETPVSiP2QdzV67gRLWZVjjuIDHEaYRp8eytMdwr39vACYO+BYGsiHk63QBH44pVod/DKcO5XHESgd16O0Zrh+o8k3Z9gG2GVpdm9IGNCiTgEGNLefFEUD2BjWdHQA6WHupFNkTRzgA4C72+AWgECpLh5SrkY9Zdkmr4xRSVEukkJE+X2ZrkAoLcSpkGxno82G23qig7/ZWpyKKIJ22iBGPDbtgA2wniubeULzYAJWp4fh03RhsoPUM8pjUCtJycmwydkGSzc5GWYH3bCCayzwwKCcMasiB8vFWT27LoGyThfbfxtKctRsa
*/