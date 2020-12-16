/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_VECTOR_N_CHOOSER_07072005_1248)
#define FUSION_VECTOR_N_CHOOSER_07072005_1248

#include <boost/fusion/container/vector/detail/cpp03/limits.hpp>

//  include vector0..N where N is FUSION_MAX_VECTOR_SIZE
#include <boost/fusion/container/vector/detail/cpp03/vector10.hpp>
#if (FUSION_MAX_VECTOR_SIZE > 10)
#include <boost/fusion/container/vector/detail/cpp03/vector20.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 20)
#include <boost/fusion/container/vector/detail/cpp03/vector30.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 30)
#include <boost/fusion/container/vector/detail/cpp03/vector40.hpp>
#endif
#if (FUSION_MAX_VECTOR_SIZE > 40)
#include <boost/fusion/container/vector/detail/cpp03/vector50.hpp>
#endif

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

namespace boost { namespace fusion
{
    struct void_;
}}

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector_chooser.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vector_chooser" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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

namespace boost { namespace fusion { namespace detail
{
    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename T)>
    struct vector_n_chooser
    {
        typedef BOOST_PP_CAT(vector, FUSION_MAX_VECTOR_SIZE)<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)> type;
    };

    template <>
    struct vector_n_chooser<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, void_ BOOST_PP_INTERCEPT)>
    {
        typedef vector0<> type;
    };

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/vector/detail/cpp03/vector_n_chooser.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, BOOST_PP_DEC(FUSION_MAX_VECTOR_SIZE))
#include BOOST_PP_ITERATE()

}}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    struct vector_n_chooser<
        BOOST_PP_ENUM_PARAMS(N, T)
        BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(FUSION_MAX_VECTOR_SIZE, N), void_ BOOST_PP_INTERCEPT)>
    {
        typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> type;
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)

/* vector_n_chooser.hpp
+L1yrKhllZO8lHP7xcrJdv+2jbrd+1pkX4hrY9wXikzWZbfJ9i3ms3+2c/YLnZ1jc3y232SdS0zW+ZDJvpGq5cENvpZPgsk5RvstkJuUvZiMmNyOQdmvf3IuMydDfoMVGPZrm5wn9OfBvEw7Ra38PNLtfKad55rIMZOVwm6mbnfjsWTc7iw7LctxLhjFfhjd1NlH1eaWbAP1uoLOMmenJTv2XXX+rXyu1FPrIG3+DSj9s6v9cycrGvvnNvyGyOAflWkZKUTq7F9sy+Jgl/2q8qzixfXGeH3JobJk/1Y/y+azi1x7TfYnexW/K/T9iJbJOqXIuieSFrG86OucsRKptqR0x2nDluXTcwrXYyHM9NwiZWjuXMDdZNgLV/yHvTuBi6LsAzi+nqmRYamgooCiiSdeSZ5445FSoVIegByCAq4cCmpKvVaYlmRq5BWlpab1kplHWqLZa6UVmqWZJh6VeYVHZqn5/mb3z+zO7iy7+FbvxX7e5/3GODvzzDPHzu48//+DN6hDgdRBObAnGDOkGnKt1u+p0YsF8jtWpxohpuOmnOlcbeVtc9121/nu6G5/35npbt+OQY6/c8jxbXs+WNrkd9N+GpMWa7P9WZKsawqltuy7m8r2e6vbbwqDj0lPDedUcvnaqm6jk98A5POBRWtz3ebWMi/0qBzvhyjleIPRR63X+MjkeMuXoX/h+AjTfNeQ413n+1Gc5vuRTi5Y2Sce5mXFjJf3NcXBxdNSzPcVc2pSD7bRqPSl8LFcG/ws+1jNJWud83onO6l43BNfHI8VqES2r9ou5oukcoUrviQo1XXhe7FyvJ5raDcugvbaqH/e69+Haa7llmOjoiXvhO31we57Y3XNd85xcl+h/TywHU/B6GHeqLGSD28MZS/B8hGNTNsWPcGcHDjNmOr8eK6uOZ5jbe4TlEWY9+dH7JcED3N+uxnm9dgc46nqMa6UvsXXHw/7fNbDadvCRmpOZy7tDyrfTeK5/qi/4Q6MyVDSW7uc33motza39YDi89/TPqf0COZ193O+fiXRcmnyhg/1dp5jWnI8k+TAvl3OchyG6NerP0d7qdrjdAO1LprzK7uOfXsUMW+m4/WWuh1ON3C9HarUtW+Hhsr3S019HjKdB0plSpvz3MdbP5f7/Lq27UBh3iIH6y1tvnEfF46F4s8Cn3r2+def4/0BjYvrEtYh4L7wXg8OCjdOMCont+vjdHB9knpY7hELTdOUxShhpdpry5x69vvjK+pi1NaFveB6W+xX20L72VzTy367FzJvrmZdpd/mazrbvPgu623W1iPHy/5YOKhcozT1MB8BpTn29rtwDFzGgAqO+ob+cX0l9fvUlj7v+lxT3vXqBW5ZsY2Odbu0pf07tRL7xznua9vLVP8uvzS9J/TKtKfW9nvE8+xts2fwOW9azgf7ws6sTqh36ua83N6HGr190VFed8d9Yd1N8x8IWdrn1OsJ7bNbFHx2/sYz9zjus6vfh7X0+d71+7w67jur38fXcZ9j/b7Fpe/jm2raLzNXLv7yu10BAY/teig9/pnXzhoMq03TU+vO+vmxBxY98kSz4cvc21c9ye+K1ZXp4wI9dv7k9ePJLwJX1hsyuuE0R31qHfd13t1Pmd6/98Y+4R1/z6r1Sosp36V2TnPcJzjF1Jf32uZPjzVceaajz0thWR9sCqvjuK/zRVNednkOjmcoBs6hO2EmxSD5b31xAwbiRhyJmzEKt2IGvoeP4jZ8AfNxMW7Hv+MO3Igf4BbciV/gh3gc/4Hf4y68iDkGeS6Nx6Ve7jBH6rVH6vUZ+uPneD8WYCjuw9H4BcbifhyHX+JT+BXOxoO4EL/GV/AwfoJHcC8exW8=
*/