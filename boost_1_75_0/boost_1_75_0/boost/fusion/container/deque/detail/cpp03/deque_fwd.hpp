/*=============================================================================
    Copyright (c) 2005-2012 Joel de Guzman
    Copyright (c) 2005-2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PP_DEQUE_FORWARD_02092007_0749)
#define FUSION_PP_DEQUE_FORWARD_02092007_0749

#if defined(BOOST_FUSION_HAS_VARIADIC_DEQUE)
#error "C++03 only! This file should not have been included"
#endif

#include <boost/fusion/container/deque/detail/cpp03/limits.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/deque/detail/cpp03/preprocessed/deque_fwd.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/deque" FUSION_MAX_DEQUE_SIZE_STR "_fwd.hpp")
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

    template<
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
            FUSION_MAX_DEQUE_SIZE, typename T, void_)>
    struct deque;
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif

/* deque_fwd.hpp
sqZKqy7BdfbQTDjvlkHW2k8vicbm7Gu0sVjL+sGmfNd8uDVr54ONUuIIJ/ypMYTZPOADmN+zCSitYsJNVzyjdhT3Tpmmyc77ipjkwvHx1ACzdmzoxhfKF9MZsW5xA1W0uM6kD/lCw6S6BErq9oomd5xjsH2i/Mqxm56n+fGRUZ+hqKhAfOrzVAnEKLww+nZEVbf2nAWsloqiyPyUZEcz2Z0bane9JusCDhk1rIqTsjurhsFzMQOFDOUX2Z1TA9fFkTC8SuaB1gu++WQlR2VZK9Syf0UBxsq+BsAKYukfZwCPjkou5yWjw0DcyVFjKQ1B9kqGmu9M7m8pPU3Pm+JQS6mKmwsqeMNQwWSsANjxs1WowDG7HAaXnxLheJQVnBPqmCq7Y+68wcLw5Udn6PIIi7XacmbEcETpOThdnE/DoC97bmTFrsFitxmKTdSKXe1TTHax5l2OGmRPTSzPKP2t6Hqbcsbm3YY8ZdaTgbJy0BEBdL4e8GjIKldXvA4wPbHc0xPJculKFUq25NRQA9YZtIGAdZGfMptNjRVwFYfqcuxgo60Adog7q1q99vUorhSddUiNhx9Z7s8S8N6eYbKnzogtull2OdYpGTtczWVnvknCUsq/QGJ/MMNn8+FJyIrOpJhYu3OIKd5jyXRnsGYOgKngadFIOT4DDtldGesA5R4ml1xAZzYWtp22sk6vQ9q4py/C0jWPsBm7B4Sn
*/