/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_TUPLE_TIE_10032005_0846)
#define FUSION_TUPLE_TIE_10032005_0846

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/tuple/detail/tuple.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple_tie" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/tuple/detail/tuple_tie.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_REF

}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* tuple_tie.hpp
phBf4nqmwS5ykEYI1seGGEXQcO587C2JLUHRH3XL0kbTlfW26Wl6mtgijPPpySiSJ5JIL67Bnhh2j8h2wzzdsDtDcpkjPvRSstIjRvCUzcVqzVww3Vn+NI4VRzpUrIk5LgkrkfIf/3v/eKtfn9AGui7Llub9hpivp2NxZKJjvdnZKvZLU5HDExCIjy7LAc+e8/wrJuRGcK4937NscLDmvbDAugKWdRi1VulCQWOI/cAvFegHn7b8uIvasy+GRAzFdB/sU+wW8JpxPoyoj9/srRhkQLNdZ067vnwm/GdElUV08XaWIg9ccOJUgbnq+JTEPuA5JJh8uTHYdvzPX8NOKmKcVz8n0D6b9LzHObbsPCYs0J3MhulDPx1I+9PIJFaCsWG3+MSlW/oaWAb03zFKqT6TGGhVNfNSBJJE7iSd05Tuc4DH2auDQ0WFy4CKOx4pyHsq6+5DQSxnrXMfVuHsbFNs/FEi+zJ89ERhZdAqnW+vfn7B0+x1VheBrJHSdp4DDhRlT2Zo812m/VuOU/WxUjgSEBoBFgOudS/y35NR5NhXbb9ZHj+lwyg20dZx0o2K2eeDPuSAm7d2V4EOJoodR7sSEKVYJdFSNB5sGnxroy7xsl6zzSBs/xuHl6cCIebIIz0wcjXdcY9Eh4n9KzkAKmSwqIiuB8yKtx5XxkAjAZEU2Ei78ecDjtK/yY3UZwz43pBrM44ZSGsO48/D
*/