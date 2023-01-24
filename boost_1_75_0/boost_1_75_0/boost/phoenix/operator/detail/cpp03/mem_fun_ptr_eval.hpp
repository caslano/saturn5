
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
o65fpHceL/XDMUm0qIOxXSrcQiAJ+u+RWowAn2szgF5FAJb+aubd30dOtkEvhaDSuuWmZaj69Uxy89qHl2Wz9019+exfn17cl1P7ht+6r9NhhX28p92gdCeYO8FLQFAT643uDL/B5Xuf5NQ1LIBgE9MB+Qr+CukKsRVOH97oFRvOa1fShLTesJzvlnPuw8Wn7tbwNSRRhAtkCvwzh/VYH8o5DEE4xjmE9r9omUjMITcjovxl9C9Yu667+bvWpNTCIV/6MX3gOHYRfYjvSh/C0pdDn+V3mXc5XT4IopEh+oWUhRz8bsO+Rc03BgEkA9B8CAQxc3DurWkPIH+FSMUVimOIYgcQRMGpbjFE+BiUHUThfcWVgyf8GyVnGRMHm8TxUqA4vKXFrZQWihcvbsWLu7s7y+KwUIq7F/cCL1YcFlmK++Kw2OLuUHx3T3OXSy6X3IcneebDzLdJ5pf/f4b02pCNmiCOIrDwV6T7O/6caPIutw/EVAfZ1AIddfIObIc8xNIX5z7c1DHgiLsFqhjCCMGXvBNlsfuJU1QJcVQX29s8ZSrhESnFaAwi3FmeTCkX52Ys9u8eYmOGXRhSv/THhVhemDPQxsf79EypBdSLv1aQHFn0YXP4nIJ+eifvgI8znMp5SjHBFLjRypUa28+ElcfN6C89rF6eHDv4VnEHLZfqE24IGgN3zZVv4LgfzSNngdL9lvL75DouPrAZ
*/