
#if !BOOST_PHOENIX_IS_ITERATING

#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/operator/detail/cpp03/preprocessed/mem_fun_ptr_eval.hpp>

#else

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/mem_fun_ptr_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2016 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    #define BOOST_PHOENIX_MEMBER_EVAL(Z, N, D)                                  \
        BOOST_PP_COMMA_IF(BOOST_PP_NOT(BOOST_PP_EQUAL(N, 2)))                   \
        boost::phoenix::eval(BOOST_PP_CAT(a, N), ctx)                           \
    /**/

    #define BOOST_PHOENIX_ITERATION_PARAMS                                      \
        (3, (2, BOOST_PHOENIX_LIMIT,                                            \
        <boost/phoenix/operator/detail/cpp03/mem_fun_ptr_eval.hpp>))            \
    /**/
        #include BOOST_PHOENIX_ITERATE()
    #undef BOOST_PHOENIX_MEMBER_EVAL

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else // BOOST_PHOENIX_IS_ITERATING

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A, Context)>
            : result<This(BOOST_PHOENIX_A_const_ref, Context)>
        {};

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A_ref, Context)>
            : result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>
        {};

        template <BOOST_PHOENIX_typename_A, typename Context>
        typename result_of::mem_fun_ptr_eval<Context, BOOST_PHOENIX_A>::type
        operator()(
            BOOST_PHOENIX_A_const_ref_a
          , Context const & ctx
        ) const
        {
            return
                (
                    get_pointer(boost::phoenix::eval(a0, ctx))
                    ->*boost::phoenix::eval(a1, ctx)
                )(
                    BOOST_PP_REPEAT_FROM_TO(
                        2
                      , BOOST_PHOENIX_ITERATION
                      , BOOST_PHOENIX_MEMBER_EVAL
                      , BOOST_PHOENIX_ITERATION
                    )
                );
        }

#endif

/* mem_fun_ptr_eval.hpp
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
*/