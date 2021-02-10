
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/statement/detail/preprocessed/switch.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_SWITCH_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/switch_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

        #define BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF_R(Z, N, DATA)                 \
            typedef                                                             \
                typename fusion::result_of::deref<                              \
                    typename fusion::result_of::advance_c<                      \
                        flat_view_begin                                         \
                      , N                                                       \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(case, N);                                          \
            typedef                                                             \
                typename proto::detail::uncvref<                                \
                    typename proto::result_of::value<                           \
                      typename proto::result_of::child_c<                       \
                            BOOST_PP_CAT(case, N)                               \
                          , 0                                                   \
                        >::type                                                 \
                    >::type                                                     \
                >::type                                                         \
                BOOST_PP_CAT(case_label, N);                                    \
    /**/

    #define BOOST_PHOENIX_SWITCH_EVAL_R(Z, N, DATA)                             \
        case BOOST_PP_CAT(case_label, N)::value :                               \
            boost::phoenix::eval(                                               \
                proto::child_c<1>(                                              \
                    fusion::deref(                                              \
                        fusion::advance_c<N>(fusion::begin(flat_view))          \
                    )                                                           \
                )                                                               \
              , ctx                                                             \
            );                                                                  \
            break;                                                              \
    /**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (2, BOOST_PHOENIX_LIMIT,                                            \
        <boost/phoenix/statement/detail/switch.hpp>))
#include BOOST_PHOENIX_ITERATE()

        #undef BOOST_PHOENIX_SWITCH_EVAL_R
        #undef BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else
            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<BOOST_PHOENIX_ITERATION>
              , mpl::false_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;

                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;

                flat_view_type flat_view(proto::flatten(cases));

                BOOST_PP_REPEAT(
                    BOOST_PHOENIX_ITERATION
                  , BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF_R
                  , BOOST_PHOENIX_ITERATION
                )

                switch(boost::phoenix::eval(cond, ctx))
                {
                    BOOST_PP_REPEAT(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_SWITCH_EVAL_R, _)
                }
            }

            template <typename Context, typename Cond, typename Cases>
            result_type
            evaluate(
                Context const & ctx
              , Cond const & cond
              , Cases const & cases
              , mpl::int_<BOOST_PHOENIX_ITERATION>
              , mpl::true_
            ) const
            {
                typedef 
                    typename proto::result_of::flatten<Cases const&>::type
                    flat_view_type;

                typedef
                    typename fusion::result_of::begin<flat_view_type>::type
                    flat_view_begin;

                flat_view_type flat_view(proto::flatten(cases));

                BOOST_PP_REPEAT(
                    BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                  , BOOST_PHOENIX_SWITCH_EVAL_TYPEDEF_R
                  , BOOST_PHOENIX_ITERATION
                )

                switch(boost::phoenix::eval(cond, ctx))
                {
                    BOOST_PP_REPEAT(
                        BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                      , BOOST_PHOENIX_SWITCH_EVAL_R, _
                    )
                    default:
                        boost::phoenix::eval(
                            proto::child_c<0>(
                                fusion::deref(
                                    fusion::advance_c<
                                        BOOST_PP_DEC(BOOST_PHOENIX_ITERATION)
                                    >(fusion::begin(flat_view))
                                )
                            )
                            , ctx
                        );
                }
            }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* switch.hpp
7V/619Q7h52COPfK/pTugAgsGwzDaESD+Mi7KcLmMWwXzz/3eTryW2vmuAsz9PPiJmTfdf3bd6E/DyIdbMX+jUFfjoK3SsinBFoTf2LQn8C9LOm6ou95PPVD55/U/gDO4ttC8Mgc9ytCbz0A+o3lYSZ4+Y/xDPlgCjsJ6k3oBY0CUDSKxOB2dmTlj5J10E4wLRcZMQQsye/bTN8OmC+778KcA0/Xi0+sOxPv+f5T6GM06Tfg+T0AGjxcVFfGp5n67aLGHFJvYVJWs8YgtEndzNCg4yOQVzHOWIR+3nmuk/s7+HBrLc59LBZ70Mgx6H5///w4ryolkvsx2z+3MxzDgUstbx4chJSFUCw30mJ4WY4BZszR3WhqgQYXOSgJX2Qx9GM/pIfUpZhKZWdIqYNBYUEjyDoYQA36XAsRyYE1mtKHYHgP/jbuAuyy4TDOgQQaqIhOrRl9G/qzc2t0TeMzD214JTSMQJkOV2jx8cQD0V+wIrXHQuMc+oD5qu8LWIzQH4Y2sxjWCJd7jeiMq8UHSgNmdR7F9wcaDmnoR6Xzp3KVlhje0Vgu+WX9l8weieEs/Ij7ZXQYbu1aHOQxXE5ivbtRH4OD6iYm0gMxLC6ojNj4XnENMI7DR5bILnyWB4/iR38CWylQIHrpzHSK
*/