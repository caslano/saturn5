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
3SgyMJc6AHvrljbjzhrdtLSZBrW+RC8rFRfBhQ8j81oZTh56rQ07xzzdnj4RvOeRos5kG+L3qLRLvHkVsgjUjN8/JUMKDpq4QqHVRSs6pzo9ATr3aC+DbiKEcbGxzfC20AxdKq9LUKjLGNBYQ5A1rkPI6kDyQO2ssYG67GQpTWag0KyVsf+ZxLTbbaRHDa/J+92BMoM6LjpeoHIigbQ5RNc05RZ18DP5CErtTxScwgYEhOzcUD8GvCa2C6wPBUarg+8fWQ7SS3F92hKoANzvhxaL0Ukrf5pRhNGMqs9y2iALZPdoaI/XuVKJaEXASzqHcw+ea4tMGs5p8fTWButwNODA75luFhVNFNWsfp/11FFwMUUkorJ9IALhvspS+4zz0MHR8zX4rm2tH5LScWEUEx1m0t8D15IqL9mak/Knfol9pyrlHDtje9uYpB4VU63vw/vV82veQSi5iZiZIOqN506nuG1oG3s8N0cui0WZJFTIgxjR09bOzafn8mnj7FSrKMMaDkRRKySjRoOO/l89aNshqeRsSLtUsrDR+NjpRHKXR8RXv1ISZxIVwHcubkZ6pg5Bc9JMuKA1dHwYwMFVzXwfg0BTgrWisWaa0iDuWPACJRO97bDTAHzE4eW+amXVW0B8fdcRYuOZDJsW
*/