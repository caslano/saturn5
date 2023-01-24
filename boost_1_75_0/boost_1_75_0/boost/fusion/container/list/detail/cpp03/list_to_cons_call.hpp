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
aQuhtKkxbbnnFdrUjLZATpuW0qa2oy1EpO3++QptGzUNoK3yHKHtSlOBtmq6zKuitFXjlcpz5xTa4JrQpuW0wYE5QBs85LSpRNoG5Su0hTSEtgRK2/MibbFUD5KoHsRiPZDOET0oUPG7lq1qogexdnqQJOpBsVmhaF5QAyjafJZQdDhQoCicUhRNKQrHFP1wllCkLJXDXctDlKJwO4qiRYoOLFQouta0ARR1phQ9LVKkpRSFUoq0ZPyjFK1V8buWpb6EIq0dRaEiRaMYRWMaQtGSPwlFxQECRbUU7WpKUS1G+9t/EorWq/hdiw+lqNYO42qRotdlhaKKwAZQ5EUpekKk6AylqJpi/AymSEUpKlTxu5bMJoSiM3YUVYvIVjOKnmoIRa/8QSj6yv//4+1N4KKq2oDxGWCYQdDBdNK0EpWMMosyDbKMUdCZBJ3MhbKF3oywzKgGwzKVAIVuo5RmtplvvZVZGeUCLikuKaa5VS5tUm/LnWixzD2933mWc++dYVD+7/f9/v5+cuae9TnLc85znvMsJojqGaJ9DFE9QjThO4KozmLEqt/ZCKL6EIj2mSHq+5SE6N34FkB0oIEg6maGqJohqmOIqhGirxsIonqLEasOY4iqQyCqM0O0VMf+Ti2BKIchmhdngmgeQ7SQIZqHEN3IEO20GLHqRzEE0bwQiBaaIfq+QkJU0aoFEK06QBC1MUM0jSGqYoim
*/