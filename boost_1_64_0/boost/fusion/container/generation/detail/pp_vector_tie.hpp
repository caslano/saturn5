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
1sMuclFFyVi7E9CMTfEibI4jQnx2yzLG1BzQM9q/cUzNZ8Z4mlqNp4k1nrWMzdiMzdiMzdiMrRbb4Zr/n8tj8sGa/79N1QYwVtoA3pc2gC2E85S5gs3VcwVzbRcTf0Et5kmq10GW+dTSBpCXkyHHaubX9y1xSJ90V1kjPEr625cQYgjXE84nfWtbuNJHG4EygzD0dLnbFviab31wWd/dzmAFacPwfaYMHtC8l8AuAw188z/XNPf1vavXN+8ZLuvNyvrmHXACabe3dKVdMqxMQnWnv7iG9DsxUTMHc36Qci3RKVcZPyBlQL2jFJpJuUhbTB+LkmPdtRvkPKr3pcS8bTyqcQXEaGrFZ0PU+3pKTVNG1VJGDql/eYQLKaNdrbRlVBDyOX7mVCmjgtrXPe26/Oq07pTHhPWkuSvejcq1UnKSX1qp9O7zGcmHOtsZysGOpkVrlyuOMOKMaLKuLccgObzn05WPqLDAa6hFmH4+osP0z3WyTlmk+o3P8Y2NKZGFnPm8N0fxjsOpcn3f6p4LL+WTqCqfVlIvT28iabVkWB1WC29EcMcHcgyOKkfxHydE2qQeSbug7noQa/F9V/2aZk2Xfcu88fKZ0jKouiYKTfK56v0OY73Hzi8CV9on+sXnP4aoWFUm3nUdpC5kyJz+GGUXqbsDlHXto13nsWCqRTO9O7dw2v7XEoj2m+Pc2+y6Rqd64h0s8e6VeDvLWvYdCe3Y1xksXnue3ZKZb7PVIm7qjMTtG0s0wvW7oxxIeRGsf1nMlfn+8cr+MhdsEAeqDJamImtOoS309PjKQtqIffUvo1jKp6+k5TNJS3PCsXJuYpWDxKjT0lv5i8YpyckJ5ZyofwNSIgPP+xlm9tQcn9Nd43G98+o9+dPkZVuk9lwT2DdFE5fnFIeSF0+cVTrn+MHjA8/xaZKWtIaBaYnjQCXatBQWZNU1HXJuPdccawL4p+GzhoH1bKiZY2jSoFSv2tT3pBDq1x7cGBasvTtYf0Ow9vpg7fLB+hWCtZsH628I1v5e+/b92rbLH+p3LAfrL3kmRfm8ZNnUz8vrn/+97d5148OrGp0cvF1+N8fn3Mp9LvknlPIfjdD1oyBjvFpjLMZiB0zGTjgKu2AWnoILsSuWYDcsx+64CXtgFZ6GW7A37sYsk9zH4hKJ/2icKPHfL+8DWIv98UEcgg9JOh7GifgITsd1OAcflfQ8htdjhcRXSpB7T+5J3fFF8d8LJb6bJL/L0Iy3YF+8FTNxBU7D2/AqLMOVeDuuwTtwB66S+O7E33A1/olrZC58OUbjXdgB7/bOuZb7PnRIeajnXM+T9C3ARLwaM/AazMKFOAWvxTyUdfS5buUeTe7dOC7ngvcooEnG0HXFAXLcgTgcB6EVk3AGDsHLcRjegmdiGSbjQzgcH8OzcDueLfGPwHrENRKPwXOwNY7C9piCiXguZuMYzMWxaMdxWIjn4WxMxTl4PpbhBXgnTsR78UKsRAvuQyu24fdgEp6M6dgDM7A/2jAJs/F8nIILcCouwhxchdNwNebh+2jHbTgdf8N8PInyLcA2WIgdcAZ2wZnYDy/BYTgLJ+BsLMDLcC46+WcxXo6rcQ7ejVdIeUab5D4LY2SNhzBCU6knZtV+Ttmvcw37Vcp+8TXsJ/cR/A1k0+x3vXc/guwXU8N+KbJf5xr2KwlxvyrZLz7IfmlHmQ6oT/Cf/N71kpkRdX73evnMiFq/f/0pvqPtf2M++3/qPeybyONOQr1LqBuE/oRUwixCOaGKsIvQaFaEqQsheZbRl2ZsxmZsxmZsxmZsxmZsxmZs/83tcPX/Tyt05Bys/v+3VP3/s6QNbLS0VYwkJCvt+g391wrOtdA=
*/