
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
53UfkJpJ/1NDWIurWnesfwoahCqYmUmvCrt7REocaqFxb4Cg1U9VIqmfwbcChHkuc3i8kBLHgi7KaNA7/hUcQeD/ovYyRieVTE+wEcK5BNOoVflw7n1WzwHeTxhUYp3QMq6Tcoe6F2+faQjjBGYR5nwULq6eQbvT9tmg09LyXGNsmTJQbxTGyCWHsJIvrn6sAXyuoGqwoAeRT9bbYVl3tKqgLsKAwncAc5fVCpTUqqsmaa4g4xpq2cxhus4ipG9A7GZXuE6TXAJoBWC/tVUOEbAraqY7nIIXOkJLSNGWuMFySbVrUGe/HBycNw3x6JEpBpDtMyhzh+JMXCo/z3Ow2AAhM2W6h79SA55enh+jc4YxqmFv+P7iDhX4Z2tAbRFvp9fAcmFeB2I1VoSkqaUqXSVhsKFWWlkLf5JrM/IwGlAve3Pb+K2pLFdyAuwulPdEnshoLGcgVr8OAvHuTezPQIXUHflQqhQkIxzJOujlweaLpsEO/5SgAc+FYCjLkUcafx1UxyXCZcrDQN+oTEL0Y++BoFai24vJ6iT4V38MQux9qpMrhuZQo/V1q9SBNL/hACGBg69NLq5vz7wY1FXaII4s94+CItVNwB0tP/99meVKmJRq8aJHlVagiVgq7P5ik9iIA9wIoLC3Ct38
*/