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
id6V5dX0Uhp/MWbLCqr2/dJMeoamqmqX5dNFJFWwhoOt/6AKblA9l3kT46m2Bd96z3q6Wy/DaoY0uvI4/X/NjP3C3Y24MgLgBYvwirJFq2ACZLfnPkEG71fmGPx0R4KZsOB/ImxtNvJW9vfASqGuWq33V54Ex/CvpOAds+vluJDaIQFCYjfhyjAxLHi1DLVW/GS2wNR3HVjNPFZ5WBehAGGVawDGAljj+2593H2MjgOsIw4VfMF5TZVSr5ZUOx7nE1meqVsEQO1SXSM6cYrKbwFQ5e1HW8eDFxGrJVlaYBlJJ0gm9Q4+lKlVFzsgLJ4D+96XRIdQLUy2v3o2/5kT2A7aBwFK/5ToacN7xDCqiDyMl+CiwOyFTCWdEK4dFBuJ71m/VyI8f/PiKbq5iK5JdokWoQHjkp+dW0hFuLxf4i8QRqmvfZHql50viUp88vO7/G6JvOEIBwUyHHnXhcW7V7oosBew7EvlLVKdtDPn8ynQOD7UJOyKOe0ydKHT3LxWLY8926KFCMiaaaNQddMP5xgB3KoIGX31k35ofuQzI18zBzWI2zqwSvfLQA==
*/