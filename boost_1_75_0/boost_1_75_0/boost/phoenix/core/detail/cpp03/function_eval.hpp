#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)

#include <boost/phoenix/core/detail/cpp03/preprocessed/function_eval.hpp>

#else

#if !BOOST_PHOENIX_IS_ITERATING

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/function_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

        #define PHOENIX_GET_ARG(z, n, data)                                     \
            typedef                                                             \
                typename boost::add_reference<                                  \
                    typename boost::add_const<                                  \
                        typename boost::result_of<                              \
                            boost::phoenix::evaluator(                          \
                                BOOST_PP_CAT(A, n)                              \
                              , Context                                         \
                            )                                                   \
                        >::type                                                 \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(a, n);

        #define PHOENIX_EVAL_ARG(z, n, data)                                    \
            help_rvalue_deduction(boost::phoenix::eval(BOOST_PP_CAT(a, n), ctx))
        
        #define M0(z, n, data)                                     \
            typename proto::detail::uncvref<BOOST_PP_CAT(a, n)>::type

        #define BOOST_PHOENIX_ITERATION_PARAMS                                  \
            (3, (1, BOOST_PP_DEC(BOOST_PHOENIX_ACTOR_LIMIT),                    \
            <boost/phoenix/core/detail/cpp03/function_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

        #undef PHOENIX_GET_ARG
        #undef PHOENIX_EVAL_ARG
        #undef M0

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#else
            template <
                typename This
              , typename F
              , BOOST_PHOENIX_typename_A
              , typename Context
            >
            struct result<This(F, BOOST_PHOENIX_A, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;

                BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, PHOENIX_GET_ARG, _)

                typedef typename
                    boost::result_of<fn(BOOST_PHOENIX_a)>::type
                    type;
            };

            template <typename F, BOOST_PHOENIX_typename_A, typename Context>
            typename result<
                function_eval(
                    F const &
                  , BOOST_PHOENIX_A_ref
                  , Context const &
                )
            >::type
            operator()(F const & f, BOOST_PHOENIX_A_ref_a, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, PHOENIX_EVAL_ARG, _));
            }

            template <typename F, BOOST_PHOENIX_typename_A, typename Context>
            typename result<
                function_eval(
                    F &
                  , BOOST_PHOENIX_A_ref
                  , Context const &
                )
            >::type
            operator()(F & f, BOOST_PHOENIX_A_ref_a, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, PHOENIX_EVAL_ARG, _));
            }
#endif

#endif

/* function_eval.hpp
uF2LDw/uPcBFjz1ClrzrPtL//SPtf8CGCNYDP29sH9srH2+TsR39AQ0DxmM++Wg5/WihoUu4DrcQw4N7D3DhsYdkibvum9ldR/uf52p1XKH4mWObP5bG9kc0DBjPGf2jlUkGrsMtxPAAFx57Svyug8ZCPOpg1piwXup1CZVK8OOPv/7Yjr9G9xIMxsb6aOeQgetwC9wOuPDYg9KAyoVHHfQ9xPoITWrs//jI/B2MLW00Xmi1wr/I2P6E7iK4r2BIDt5HJx9dwnW4hbjroDS0E1Y0th8mDzlybBmL5dKg/8vcb39CjzFibDAwlxBdkmOjTca2NXvILY0te3aWNpn+YmP7Rfdbzm7LWiyC589/3bGhuR7G9sseb3l8sffzxrbw3yyPrXL8deXkG5TTSeA6cfvRHyoHX1X2f1vZ/U1l+79XNv+fyvr/VXn3r5U3/1x59X9UX/5vkf/5j7A8zjscwp81tn90Oah/7Hc6VomEGFtByYLhhZ7+t1X5tyA1T4j8a/CHfw1Avv8X//f/7Pv2n+L7T0seDwxP8PznPN7+5Z//aeGWn376CTZr5VCIGOGdwdcqRDr4Ohm7uMBgG5hINGOxRiQC2wAXLOjTilogkHe5DBzOsNP5GWO7OE8s31jNZDQMxq+VXDT64fb2Z4yNMb9f+K/jv46/6PH69et/+If//Z/+l3/4x/8VXVKfF0a//47eYf4/5fPCP/P4
*/