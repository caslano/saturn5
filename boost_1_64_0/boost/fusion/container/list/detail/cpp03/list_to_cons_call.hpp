/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PP_IS_ITERATING
#if !defined(FUSION_LIST_TO_CONS_CALL_07192005_0138)
#define FUSION_LIST_TO_CONS_CALL_07192005_0138

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/list/detail/cpp03/list_to_cons_call.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_LIST_SIZE)
#include BOOST_PP_ITERATE()

#endif
#else // defined(BOOST_PP_IS_ITERATING)
///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(BOOST_PP_ENUM_BINARY_PARAMS(
        N, typename detail::call_param<T, >::type arg))
    {
        return type(arg0
#if N > 1
            , tail_list_to_cons::call(BOOST_PP_ENUM_SHIFTED_PARAMS(N, arg)));
#else
            );
#endif
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)


/* list_to_cons_call.hpp
/L+uuvXn/75qc/5vzv//+/P/Jnn+f98V9a8+vXBC21PeGPDX+t9eeDz2+X9uTWzzf1tNbPP/uurY5v++6taZ/28y5/87ZP5vzv13zNx/SVFyq8z/m3EdtV+TbElFTl9jzv/NZCYzmclMiUvbZf4/JP75vzTP/95mkeeIaTHMERM1F4x2zpeouV20c7j/6lwt2jlZQ5vI5iyi71luQcbcg9+uFM4zOL/Aucjab1SG/j5lGvJkZM4N9HMBfoPS+PuTG5C/Qd6GHOI7kxF/Y3IhsvoZfAOyZaj6GVv0bC36TqT+G5GRfxcy8E1IM5nJTGYyk5nMZCYzmclMrZNa/f1/ZId7jqsmAd//k9YAPrbxG38qv/xysB94KfgLnGDNpym+fvvxo07KHGI/fszJ9F+vCPNefp3yXn7SXpWVKAdFuyoqyitU7+AfIvu33Znqd+U77yUdc5YUlhcXWFS+8Ab5uNQAOJd+73JZHu3h8L9X38kyfK/ufl2WX2E/fOFKHeEyk9PQNigTHARuxTkWT0sdUbshckVZx+xQPnrUq09VcL3sWlsV+4cG6ko7F/j1Wn6jnYfTznW0M4sxEkcg/4FzvFUaOx3OgoLBDqfHUxFFPIHfLpiliidI6Sy3Nwry2zGSdtTxffzpyDbkKch/wg6fkR2OvBrHxHGjo9mrQG9PtrIvQxk6n+2pHPPUuF3+Yzn4exc5DiKvxuOqlI/lKudJOzpo6zIDF6dM5N7I05D/Rl2yTg9RlxNGHhdvXTCW/eMzgXUZmBRclzYH4R3tUHXxVHtirUs31qWfNTBOypylrvjrExjvD7A+ByN3Q05Dbof6ZJ2hrU+Bq8Tlcck1imu8047yfJ0dI3YNtiMJdnh1dhS6PLIR0cQp9d47vB1H0Y4m2nEYck/kIcjJUv8a2MHLLgG2yNcc762Kfc5Kj7u8UmfjQrpQhyOnImcg7wYbrdXGNuJyistG5VqK0MZttHF/SZb3sEyUm2tkoxw+FVufBmKufDtwPV0cW2UU0xX9+ntrx1xFuy6fqNgqcaxX4vZcae11fCvKwjtXt9aO9X533OpzsycNe+WQvbdEv75vTZLbx37DmM13lmTUDfS98t2fiw/0x2L5LHwW5DOiu63/2QTdL6dujInqDh4M9gTtYCo4DdwPLAZ7gYtBG3gl2Be8G+wHvg7uD34OHgBuAw8E20DfQeBe4ABwEDgQnAQeDE4GDwGngungXHAwOB/MAM8BDwMXg5ngpeBwxm41Wvj8BwxlvbpKv0ms11GM+ToaTAWzWM9jwGxwJHgCOAY8BTwWnAOOBc8Fs8E7wHHgXeDx4CpwPPgaOAF8AzwBfBO0g7+BJ4J/gCdxj5PJYB9wKjgQnMZ2yGE9spD5fIj/99cjCcxgPc5gzFs1OASsAYeDc8EjwHmqcnwsZ7qgnAtxng28CBwPXgyeBC4Cp4CLlXL4bAXOEJTj5d4kZ4ETwbMpfw7Hy0JVOY0hyrmc5VzBcq5kOVexnKuVGD0+T4AHC2L0KnBeN7ASTAM9KjlvCLlSypVRrlwl10i5wwRyeVK/gvnsjwJFjr+h4HCBXBHHYTGYAc5WyeVSbn+B3EyO41PZfw7w0whjEN3Lcc7t8MOFiUN81N0Si7gB53vAgR8mLiZx8+2tE5eY82FiYhMXohxdfGJUsYkpaOeByKIYxdHLI4tTbPgwfKzi0uWtG6+4DjbkDIGd0OMBmz6MLHaxaXlL/OLW5dHHMFqatD7WDivCxzLaVrRuPGM0sYy5KyKPZ1yPGMbNyO3X4rtGyJOR5yMvQ16PvBnZ+hD2vn7IjHU0k5nMZCYzmclMZjKTmcxkpkSn7eP/z3PJ7v84/f/SHgCb+qM=
*/