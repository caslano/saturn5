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
tQDR4TXaubayJx/vN2IKhbibe7oIlXig7xLD4RUVCxc+M7atCojQTzfLmIVBHncA6jcep0j4HwyEgzqNhZRpjCerxfOmfmwm6n9M5NzygbiBsQE2bRNPZ1p9txU7WLCEegY9cLTjOOpq19evu5FJ3FKL7FgYTJjYJjtFDoG3Nf46E+A+j/i5XZSI0Rt2nExbFrajeRrQ8n7Q4AQ7Wy9HZJ/oyM7lUwNd+jw/flE1rKrP80Yyy0Ljb3uiMpXE/PC8tSzH+LJYiMMcE84N7Tsmb5jUlz5WJAQp8YN+nppanTTT9grZKIEQIodaP+So6x1Tjg5XLBBQ0d/+ODMoI2YlPcUytrMTec7b/QJoLWvCK/H3/c88u9TH+T6TNi+s1TP4Z+v0xIGWHT0e6TichXu/q06fVH9E++mHyeg+t4Q27pt8eH+2H23oi8v7oi6laWJGzudUBIdBcMHWNPSxFkWyqE0rwsvgm54FpfOKALbZKGzm0OvA+WHnhNX2j0PeYjfehhTmQj2k2vtf516zArr/Vl+XlKhyVAt8v5wBymsIQOB561mnXc6s015H0g==
*/