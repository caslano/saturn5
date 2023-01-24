/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_VECTOR_TIE_07192005_1242)
#define FUSION_VECTOR_TIE_07192005_1242

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/vector/vector.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/vector_tie.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector_tie" FUSION_MAX_VECTOR_SIZE_STR".hpp")
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
    struct void_;

    namespace result_of
    {
        template <
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
                FUSION_MAX_VECTOR_SIZE, typename T, void_)
          , typename Extra = void_
        >
        struct vector_tie;
    }

#define BOOST_FUSION_REF(z, n, data) BOOST_PP_CAT(T, n)&

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_vector_tie.hpp>
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

    namespace result_of
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename T)>
        #define TEXT(z, n, text) , text
        struct vector_tie< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef vector<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>
    vector_tie(BOOST_PP_ENUM_BINARY_PARAMS(N, T, & arg))
    {
        return vector<BOOST_PP_ENUM(N, BOOST_FUSION_REF, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_vector_tie.hpp
to+IppUB8P4XjZdoRkRLI5px4AKosWBGXMA4+N9Ii4jm+H+0QxZgmZjzDT2wTJSRY/toCK1/eQmtpHh+Yj1qfwAQolt1n2ImAK3/m3qfFCqq9DXCz9b/nbfG9utvd09lVvAE4I+rRtyuj6vGdrFCx2WRWYCjyqnMRyfGMxlmfE3MiKvx6I5rg0/mmcxGmsyvE6hxkMb2XAvbmQy5j/3oYKnZLmR88Gm7ZnmeyuC94rxd4DfdqUy4W7Q3fUmuuUYtCNu5FzPCCM2PMTqks351WcTdOrTpbF+MmbdKhya/wMzPdWRB/VIwutxdxCF33L4pcfglZh4mTzivyyT2X4jNCEc3cHHHdZ8w0o6ZZ6uAKzjjfLNkCd8oESD+k0YJecI3bW3iiDjhW0oG1I8K+2thSSKSHViiR7VuEt2tBuCPc/uWiK4eXMBSvQChU58NWP3xA65E+u9nbkyUrlKgWv9kQQPMB+AuuX2J+rho5hxowFAOQTqWStZXb0M+5qDmVynPhfmFSaMJVMUlHV4WVwoVL4HrWllutPFJOIhd0M7uGAqaUvFcvz8kQjn26gPt3rKY9vjraUgt6FSpVpDyckthnjpy92VizIajIBYf0DyBhjIo4An5A0/HY7e+0owfPOEmux46lRQ46+mmmFtO0ZzwFanR2B0fFCfTkJCxhcteHbw7RTuhe322nPH2jlRXVGh25PAva9u8qxUDn9bb
*/