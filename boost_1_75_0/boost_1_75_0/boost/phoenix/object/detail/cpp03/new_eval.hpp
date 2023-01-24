
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP

#include <boost/phoenix/object/detail/cpp03/preprocessed/new_eval.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP
#define BOOST_PHOENIX_OBJECT_DETAIL_NEW_EVAL_HPP

#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/new_eval_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (2, BOOST_PHOENIX_COMPOSITE_LIMIT,                                      \
    <boost/phoenix/object/detail/cpp03/new_eval.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename This, BOOST_PHOENIX_typename_A, typename Context>
        struct result<This(BOOST_PHOENIX_A, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type  construct_type;
            typedef typename target_type::type * type;
        };

        template <BOOST_PHOENIX_typename_A, typename Context>
        typename result<new_eval(BOOST_PHOENIX_A_const_ref, Context &)>::type
        operator()(
            A0 const&
          , BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(
                BOOST_PHOENIX_ITERATION
              , A
              , const& a
            )
          , Context const & ctx
        ) const
        {
#define EVAL_a(_,n,__) \
            BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) boost::phoenix::eval(a ## n, ctx)
            return
                new typename result<
                    new_eval(BOOST_PHOENIX_A_const_ref, Context &)
                    >::construct_type(
                        BOOST_PP_REPEAT_FROM_TO(
                            1
                          , BOOST_PHOENIX_ITERATION
                          , EVAL_a
                          , _
                        )
                );
#undef EVAL_a
        }

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* new_eval.hpp
WaemYNZwTW7XWNeBwI1YN3WZNSqn/LOsKdyseSySWHuL1vZSrKMxa2faFg32jAkMIVYM1oFm5LTDTrKuFLH2A6k4Zh3q4hTv55uXTMVrzDqtTdyZ3LjJeYZ1JWk4Q2PZNRs3N+tiJmtuu35FsK7vGGtO0JJws1insFgHMmamJdDmqwA3TrGOJvfliMCsncluCGPkhVhb0gfazBWdLNaSZiUxWT9+6m5pF+/nB9KzCHe3cFgYdwas81NSEGvr/PjA7mCd/q9j3Qbl9rBOpk1borEW1dDoU9GoLRqILqeLqF4ayckaLu2k7XcqiTV7LrHYHlmiGmklHHNpeljZJfj7wWGXp0eEG/DhLnF+fgRr+/+yboM1iVvEmraUgD3t0JPI0LhZO7aHNccmDO1n7QLtGrIOCIjz9o708ICm7eoS7x8AQJOsu8GHw6o4V272f591kATWfhJZx9BmjzNYOzCLpbRdbUUtTnHWBhysPSWx1vK0dkgMDASpeKS7R6SHG4ja8QGBeampuZg1iNcwD+8Sa3AAQAPT7jrrppqi+sr8fxNrWiuk/ayjXblYk0UViazpo2zDDrGucIF1M8Q6IM7XO8bTK8oDZuMAfQFm7WCTlxBUW5jYddaCwmTAGq7a6xprML4GrOH88H82N2OxThZn7SORdbQL2eIUZ03NXvggayP2EJvO2pOdmxGsbRwSgwJhyPbyAiE70t0N3C1M
*/