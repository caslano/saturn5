
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval_result_of.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD(Z, N, D)                 \
            typedef                                                             \
                typename                                                        \
                evaluator::impl<                                                \
                    BOOST_PP_CAT(A, N)                                          \
                  , Context                                                     \
                  , proto::empty_env                                            \
                >::result_type                                                  \
                BOOST_PP_CAT(child, N);                                         \
        /**/

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (2, BOOST_PHOENIX_LIMIT,                                        \
                 <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval_result_of.hpp>))
        #include BOOST_PHOENIX_ITERATE()

#undef BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_ITERATE

        template <typename Context, BOOST_PHOENIX_typename_A>
        struct mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {
            BOOST_PP_REPEAT(
                BOOST_PHOENIX_ITERATION
              , BOOST_PHOENIX_MEM_FUN_PTR_EVAL_RESULT_OF_CHILD
              , _
            )

            typedef
                typename boost::result_of<
                    child1(
                        BOOST_PP_ENUM_SHIFTED_PARAMS(
                            BOOST_PHOENIX_ITERATION
                          , child
                        )
                    )
                >::type
                type;
        };

#endif

/* mem_fun_ptr_eval_result_of.hpp
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
*/