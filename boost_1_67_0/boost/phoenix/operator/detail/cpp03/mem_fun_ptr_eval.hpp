
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