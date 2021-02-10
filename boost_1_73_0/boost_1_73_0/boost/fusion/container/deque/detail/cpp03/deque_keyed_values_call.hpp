/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_KEYED_VALUES_CALL_04122006_2211)
#define BOOST_FUSION_SEQUENCE_DEQUE_DETAIL_DEQUE_KEYED_VALUES_CALL_04122006_2211

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

#define FUSION_HASH #
#define FUSION_DEQUE_KEYED_VALUES_FORWARD(z, n, _)    \
   BOOST_FUSION_FWD_ELEM(BOOST_PP_CAT(T_, n), BOOST_PP_CAT(t, n))

#define BOOST_PP_FILENAME_1 \
    <boost/fusion/container/deque/detail/cpp03/deque_keyed_values_call.hpp>
#define BOOST_PP_ITERATION_LIMITS (1, FUSION_MAX_DEQUE_SIZE)
#include BOOST_PP_ITERATE()

#undef FUSION_DEQUE_KEYED_VALUES_FORWARD
#undef FUSION_HASH
#endif
#else

#define N BOOST_PP_ITERATION()

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(BOOST_PP_ENUM_BINARY_PARAMS(N, typename detail::call_param<T, >::type t))
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
        #if N > 1
                        , BOOST_PP_ENUM_SHIFTED_PARAMS(N, T)
        #endif
                        >::construct(BOOST_PP_ENUM_SHIFTED_PARAMS(N, t)));
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        template <BOOST_PP_ENUM_PARAMS(N, typename T_)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(BOOST_PP_ENUM_BINARY_PARAMS(N, T_, && t))
        {
            return type(BOOST_FUSION_FWD_ELEM(T_0, t0),
                        deque_keyed_values_impl<
                        next_index
        #if N > 1
                        , BOOST_PP_ENUM_SHIFTED_PARAMS(N, T_)
        #endif
                        >::forward_(BOOST_PP_ENUM_SHIFTED(N, FUSION_DEQUE_KEYED_VALUES_FORWARD, _)));
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#undef N
#endif

/* deque_keyed_values_call.hpp
Jp/LFdwTi4h10M37j+j6hogM++DdN5qs7hJ+NpgmAKMgzprgkoyrJg8kzqF5GKe1REcgcgou/nfB7C0V9JZfij9y6C18UKNVXPpTi2rxIjQuvI5vlSTGIZ7n0nh9IVFgQsEdA2LJwOvrLEnh9frbbPEFbzR2drztdbKkk+L4XmDebA+HF51Bczgseb/9lk/Eixf+iQexkvm9Pzy4nfnhZSkfPng1yKpTe3988KolhcffslLkIOJn+QGnDIePRZeI5qXfvCoprZdN3XsYjbBjMES33jCmNoiGyb+gNuWSjOXNFAamuoFlCKxd8QPbRvG9jSVP4hFoFYTHJONVIhIKeeONyJIC2oQus3cAScrW16f4C2gScJ+k4BaBUj1bpPRKLvBUKKCz8BRGVrRAKwtXqmlqyiZDL9F8zWC/7qJrcWmDLBZuDwk6wYq88PsuhEPYIIvOTXsmxz+MuhVm0bnhZHihqcV5+OIAk1KTAexU+YlJEaTW9qsoiIpkovqWZQTRDDpNPAQP8Vrw31BLAwQKAAAACAAtZ0pSXfb+DkUFAADhCwAAIgAJAGN1cmwtbWFzdGVyL2luY2x1ZGUvY3VybC9jdXJsdmVyLmhVVAUAAbZIJGCtVmtz2kYU/c6vuEM+FDJCgJuE2ONmSh03
*/