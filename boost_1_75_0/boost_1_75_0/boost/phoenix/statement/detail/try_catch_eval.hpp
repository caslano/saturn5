
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/statement/detail/preprocessed/try_catch_eval.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EVAL_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/try_catch_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif

/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

    #define BOOST_PHOENIX_TRY_CATCH_EVAL_R(Z, N, DATA)                          \
            catch(                                                              \
                typename proto::result_of::value<                               \
                    typename proto::result_of::child_c<                         \
                        BOOST_PP_CAT(A, N)                                      \
                      , 0                                                       \
                    >::type                                                     \
                >::type::type &e                                                \
            )                                                                   \
            {                                                                   \
                eval_catch_body(BOOST_PP_CAT(a, N), e, ctx);                    \
            }                                                                   \
    /**/


#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PHOENIX_CATCH_LIMIT,                                      \
        <boost/phoenix/statement/detail/try_catch_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

    #undef BOOST_PHOENIX_TRY_CATCH_EVAL_R

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Try, BOOST_PHOENIX_typename_A, typename Context>
        typename boost::enable_if<
            proto::matches<
                BOOST_PP_CAT(A, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, BOOST_PHOENIX_A_const_ref_a, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_TRY_CATCH_EVAL_R, _)
        }

        template <typename Try, BOOST_PHOENIX_typename_A, typename Context>
        typename boost::disable_if<
            proto::matches<
                BOOST_PP_CAT(A, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, BOOST_PHOENIX_A_const_ref_a, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            BOOST_PP_REPEAT(
                BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
              , BOOST_PHOENIX_TRY_CATCH_EVAL_R, _
            )
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        BOOST_PP_CAT(a, BOOST_PP_DEC(BOOST_PHOENIX_ITERATION))
                    )
                  , ctx);
            }
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* try_catch_eval.hpp
ysErEG599SgpiGOJvDf0Z9M9bcBBzTbz1MrVZg6De3sFizvZSlhryFXF3UCqWs2A88UfJSnJ+y1s6NsrclUUY9IadVcOfeiHT2Qwi++6uhJalMS1Nh1vZCh5y73UDuvBXaCZg6/EmPwtVzo7t1JvNNGynZtoJAUanphMRLxuV4huK1hq05+eqfFQvayiw6UAz4P+wAKyb2MXkl2a8QdFs0oZ6POi6RxRpEtXn5nKSxhOGH0S/NQ7o4q95u0eZqRRr90qui30ZPQs7+og9u7hKH1Xj2NTWCi1+8OVgtn6lJhKBxeRKrqTV/lOeIF3t5ee97IaoAareGVaNxsCc4fEuF42kCev7nEt9ATAn8Mviv03SlmeTX51JiDHVA/YGPaf7GYfrr3XlmWqEvSOW3Kmkgshcee2cX32tt15u3Jd54uBTj7GGDXJbiwZfYDVtkQXfK3d7zTkn3rrm80cNHwEN9N4LXlpP0Z3N2xktzTMrv8g0cyAfGQ1lGehCvPbE1X52XiTh+W8/KglfRnDuDvMo1HotW9zDGttbIElP3h2Uhy+8QPVybKAPu2Cz4tUdMqVm/pXIVtzO1vTh5ccFJ8XAp5+e+Vbic3X75+ws9wLaZ+Kln72pjSm68LVu+Mia1EJvJTGVvcALWmj/eBig2mjx0rn/aKerEbg1ua9cPO0KOlCvFxuHmgrKqoSYxYbLjYScvl4Kag3VN9SciqP
*/