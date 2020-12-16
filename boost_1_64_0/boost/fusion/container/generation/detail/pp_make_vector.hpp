/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_MAKE_VECTOR_07162005_0243)
#define FUSION_MAKE_VECTOR_07162005_0243

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/generation/detail/preprocessed/make_vector.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/make_vector" FUSION_MAX_VECTOR_SIZE_STR".hpp")
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
        struct make_vector;

        template <>
        struct make_vector<>
        {
            typedef vector0<> type;
        };
    }

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector0<>
    make_vector()
    {
        return vector0<>();
    }

#define BOOST_FUSION_AS_FUSION_ELEMENT(z, n, data)                               \
    typename detail::as_fusion_element<BOOST_PP_CAT(T, n)>::type

#define BOOST_PP_FILENAME_1 <boost/fusion/container/generation/detail/pp_make_vector.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_VECTOR_SIZE)
#include BOOST_PP_ITERATE()

#undef BOOST_FUSION_AS_FUSION_ELEMENT

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
        struct make_vector< BOOST_PP_ENUM_PARAMS(N, T) BOOST_PP_REPEAT_FROM_TO(BOOST_PP_DEC(N), FUSION_MAX_VECTOR_SIZE, TEXT, void_) >
        #undef TEXT
        {
            typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)> type;
        };
    }

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>
    make_vector(BOOST_PP_ENUM_BINARY_PARAMS(N, T, const& arg))
    {
        return BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM(N, BOOST_FUSION_AS_FUSION_ELEMENT, _)>(
            BOOST_PP_ENUM_PARAMS(N, arg));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* pp_make_vector.hpp
6wRLvTTbq7cN5nrSDgbb0ES2Qdte6u2IDZQ4i7XJF2ujsh0VEW7bUWiZHuMxzojsC7ftSDHYjkgvtkPm3ZO/b/Zquyokjv1hticMn0PleIyNct0utkk5ID3OuScxUdyOx2yD49GsczwWGRyPMTrHoxwP8np+FmU4truttTyq3rNHRna+fnt1U7WXxGlRH8vWmCBx7PsdtNO9vH6qhzMmSCQWWtfNdszJGO14bWaetLVL7NNIucQep6wv4/le4h+V0dZ8lZt1lNszyt73h34lNc4FGOZoa94pr4HUgaxQXX5DiYEfT2GhOBTnRVKv31jLnzbLnGrJs+5u7z+LHJdSvnaOT/KJ6qWZ45M6yT4K09lHSntH00ZB5LmG/7bbVi85z+i0repYLq3n3rdqgRLfv5dLLDnO7HTv8rlv1TSzeq7FT7srr/Etofk8Na7vXodbyCS4t7YO072KNWuvw0LrZ2S6V3XYoFOHRWRi6m2PyXT52uG4QR1Cg9zrsJhMSh11uHztoKqDVzF5fu7YO/r3gI3vVevH5DG+h60fk8foXvLli9Xj671z/WcCP3+snl8rJs+n1v3bdXjtpGvi693TKnzq0wXhI7ZdXEye8gD5TSi/Fc21bd8Xm0jWY1/GfDfBTtgUf4MhOBibYTY2xzxsgasxFB/AlvhnbIWHMAz/gm3wY2yLX2E7/BHbY23q0QGvxo7YGDs5xuDLbzr8SjsGX8bWN8EIbIPdsTNGSr174DjsiTditNT/N3g39sI12Bt3Ygy+gX3wQ+yLn2E/qc9Jkvw24zebrT60TcAxqc8Oqc8TUp+dUp/dOASflHZ7GpfjftyMB7AcD+I+fAYP4J+lvZ7Dv+PzGEbhL2AnfAkH4xFcjkdxMx7DcnwZ9+FxPICv4lf4Gv6Eb6Dym/NNPCfPguQ3WsBh2T7lOIirJd/vcnyMlu0ag90xEQegCWfhONyIGViGmbI90/FFnIHHMQdP4s3S3jOxGmfhd5iHSmVmy/bmYwQWYhrOwRU4F3+P83EbLsC9uBBfwlvwDN4q270IQ2rbYiVE4WLsibdhIt6OM/AOnInLcDGW4Hpcjvfjnbgd78IncAUexJX4HK5yxFqQ32I4jhSjeeZ2UuaP/Ss2w1MYgX/DYXgaE/Bt1edCflvxm8v9c7Fa5uldi11wPfbDjZiN9+ESvB/XYRk+iH/Ax/BBPIVbZD9sxQaU8xA2xXIcittR+jXze0gdU8O1X/MZ5X34oWzXR6r3Bfc2ft9n8r7P5X1nVe8z1fC+k/K+v8r7TqneV1rD+96R970r76tCc2CAx9gVxKzw6fnnf0pcCr2YFDwz/dniUvBc1WNsCk9xKeR5q1fxKC4lFoUvcSi6kZb0+O+PPeHts96LjTuRVkhcBlIZqZJURTpPajyHmBEkE8k8x/+82L/4F//iX/yLf/Ev/sW//Ju9O4GLoooDOL6EKJYZlnnlAYkKaLZeaZ5galia5BWltaywCIqwwkJoWptZapnRoaGZUZrSbYdFN5mVlRWVlpUl3VZWZlZWdvxm97+7s7OzsuDVMfPp9a39zM475s0y864xNmM7tFs9Qu5h6P8vmGSd7F4B4MDXAPi6g0ne5eJroyuSPsDphAxljkAH73vviH1M0rChg5POtKQzU8BhM1vsfbJzM0PuV+5xgqtPpI9J1XeSGKd8RqZM/u+W2ayTHpvyhY77TQ8FFXo/9yXNQ09PiowZ6CXpMRMy+VfZftJjSbflO2rRj/QE/8P7AHuZT/ePe5NO3Eo/0q79xA05tenD+tAVN1+SfJ8lcTetFzg2JJsvJHYKHrf7NFhsua7q605DVg3vzbB7+2Ltk2yW3OwMSVuxty/Zbi0=
*/