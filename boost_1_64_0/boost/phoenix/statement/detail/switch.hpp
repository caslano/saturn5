
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
25sK+V8JIC7ptxdgGNuoD/pxOT4zweW+SM7b9vowpK//X47s//bpUdoGI8dz1+eB8iyPemrUU28DnE5ZvT/7k+tB974r9njGEk9/pjUIcMRz3DUew3n3VZnvkMs7Q5b20iturmybs/B95llR1nVdWGJUu/HtXFsFGtpEjOdIY39JOce6rAfDcdNwfZvjob/vOS/9fbPd+vt639aNbW7deusF2iHXn38nHFH3IOU91Av7/p22qcu+oq3fFayTsN76/rtSS0/6ntysjUvWp6mPexvXUdVWGOiab7kbzsN1o5zLvF9DGc8h7uvSU3u5Pp5C6jxW8t5G7h1bSdtzcAVD3uPpPXgbz5OM99YH+7j3d3iadKyGdGzlSImbbKHx7ZbpGeOP7av/RzdZB2GEY6yDNEP8bDW21dg8Ie7W91iBhrYv4/o3jpW3ypHZdnz/kDRjVHORS/7OechfA8p/2jl/CWRNTyoX+TO2zXla98b1HN5PX7CB1H89Wc9hQfb0tSFKt/Pc0LgvBPWXtgg5tlXB42o9GNKhKUJfEeqe7Db2X+e2neRk17Yd4zGqnKwn4zEn0FBPMi+nbJfxjFKOsVJfYwifqDaVe5zLYX/YfBvfaNKP0Uz3cKz0M+Rb/sspf1sHyLdEZHv6gnBCHSsrOvIXn5g4KdUqLQu5qGfZ3h3jmLWjheTTOHZcpld0HXtuX8ZxrW98rh9oOK/YZ3Xp42eIXh/bK9tv5XCX909If6kVlRzlZeRqnteBOk9v1+IwmT4LdHkuN1BfsIP0VW2LWh8tQ5q0L8SwCUolJ9/y2dgtnstJn1r3+xy5HnS/zzEc46P0Z0YMD5V7HftzTsM5Xe6zjOXMkHL+Q7aldwknVVt4VUc5tfYXKWRenm247rMu/Twc5zDpkCL1IWVzvj4IjpD36sg2sFyOYenVDPm0pOitFVrd8cT6No9ntvuIyEH6jLXkeBaMX6hze7BTmnJsufV1mu26+HVit3LR6HY+kQFFxvc6SNxO7Z0JMtHYBzlGjqdSh27PTGuoeuaA4NRXWZa1yr1FLep48CC9r9g+rYwyTl2WjzOrB7qu25P7c7+Sg/VCJxEqqHQJX6nnUNU91ZuWJa3upudynFBu69H1PQylZTzggvKqDsc5PTvbL3k+JfvBCcI3al3XcM6zJYazcx6Op56uwUu6XoNLPk+TniXGZRyIYf89y/9PSLI67RexQ/REw2QbbS/jQtJqGvNt68Rl24tvnX91T7e1lt7ek5Tktp/c9L4hOt65rXHrUD3ic5LHs5JHv9oueZRHB8Y81svDvmscYyfPBLy288s9DesgYbxxHKD92YH78ch+r+n+LEHaX4zPJwzHbdKw5+Wy7VitF9FxL6X3o9Jv+V2OQ/uHud8znlPXVXWd6i8P56FC/mfqua9bYzlL4nekYZUbh2SXZ70q/67fktTbyJ2fpSdrZyRjnwNp33Jvc5U6k3n0579SZxKXlM+4/U+P1As2R441VsI/1X5b31PdyMFG9t/QArk73ni7H5PjitSLsQ5kDN+fN24sLa/l2/n4OEJPaLBcW4RjU/U/Dex5ln1BP0Ta85vHfUG7bnPZ7rNkO1V9d/kvb9cX0rYo7RyGe3dt+5bphw3TJT5Z94Z9weXZhG1MzWzWW8Zw/V1BbbRyS5u7SzuWbd6iI/Q+alENmdfluVuKJK7mzSROX+ZtrdaXNq+sCw/nK+P4tP0j9cqcIOskBi+oa/5GtnXiOjbJ8/i6RrfY78Kb3roNXbWbEa9+LyB/c6+jtXqRf3tfuR8DZbyaoS2K8VrR8TIWM8B5DNRUQ18pGQ9r4X5b2udc3j3j2idLZtTq2G+E/s2mp9R31xqr8ng=
*/