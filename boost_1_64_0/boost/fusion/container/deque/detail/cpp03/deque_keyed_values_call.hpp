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
VRE9dDAsGFZb7BapSmm6V4LS5gF0HIOMH3lRZW1RB/5rM9n0S0WGBykPCX4I1P7UAwmUZgECB5ZdZ07klS0FUXVBMa/QrnCDM3swKXAhOY062GSsTQamtbPHhU6WXWVEoXyyhojRKE9pLXSwVNyZzwgDZu0UxLeG+5C7M83lKrYNRAPgql46FkIZoYKJMPk7poNEQlRVlV5Utl0ptO9VqdZ9XPR3xs1M3R5E3WX3itZLHS2MAc994tf/jS9G3Vqt3TjQpYhXcq10XSapDPt8bSMOjZE4kfg1yuRFLRFrM4qvikHW/h/pzilfWTGQbevNfYFyM6+zhdr9vGrqwlIIsFeWkKguT78hwMCV7lZ19H7QqpZ8DdTBeQqj4QxqVDtqMoFO+KMEM/HNKw7yZn28atqZRg9pgQfEz8siosEzNZPTcEcHqwy6p/42u2SemnJq0NWkzqnHZmGMhFjBpLqYeBnT73lASQXn5rFeBPLmJxVaobM+QR55zenHCU+bouPfPLwuszbdzs4WdGIRjVAMvCzwD9hdSBDOvdYjEdyAxqSNL4uSBw6B2j6nXA==
*/