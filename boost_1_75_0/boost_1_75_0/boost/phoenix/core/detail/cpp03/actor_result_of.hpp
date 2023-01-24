
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_result_of.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_RESULT_OF_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_result_of_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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

        template <typename Expr
            , BOOST_PHOENIX_typename_A_void(BOOST_PHOENIX_ACTOR_LIMIT)
            , typename Dummy = void>
        struct actor;

        template <typename Expr>
        struct nullary_actor_result
        {
            typedef
                typename boost::phoenix::evaluator::impl<
                    Expr const&
                  , vector2<
                        vector1<const ::boost::phoenix::actor<Expr> *> &
                      , default_actions
                    > const &
                  , proto::empty_env
                >::result_type
                type;
        };

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                          \
    <boost/phoenix/core/detail/cpp03/actor_result_of.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <typename Expr, BOOST_PHOENIX_typename_A>
        struct actor<Expr, BOOST_PHOENIX_A>
        {
            typedef
                typename phoenix::evaluator::
                    impl<
                        Expr const&
                      , vector2<
                            BOOST_PP_CAT(
                                vector
                              , BOOST_PP_INC(BOOST_PHOENIX_ITERATION)
                            )<const ::boost::phoenix::actor<Expr> *, BOOST_PHOENIX_A> &
                          , default_actions
                        > const &
                      , proto::empty_env
                    >::result_type
                type;
        };

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_result_of.hpp
0BpatZpHpTqTSqu5nFOuUB0dwk9qYDI1bLaOzoicWWFIgBgTCmNcToTDDjOZITotJhQcP35MGc2K/uYxGBR0upbDgW8FUTEYkoMD3rt3jFev2G/eCNbWRBsb0p0d/ea7C6PhXK9PGAxxgz6mh+iiKIab62vdyQk8eG5vbiw83vV4bOHzHCKRWSKT7ewk/IE43Es8bhRGxWJCQkwGjA0uT777dnk8nzwyZxafVOITiUJKZS0YLLpcpp0NcAlLpWG4lMnCUglczzodOZ931O369bp88nLY60PXsolEUbs9arNZ5QoTl3vu9QbEopBQEBbww3xehMcNs1kwwgibdfr9dz9jbNPDJxbnrdaU0Wg52AmJhVGpOCgU5Fyugs9bDodriUQtmWwVi61KJXJ2BrjDfv/m5qZeKCZ8fiOXdx4IuNQau0QCDc0jFvthkGJRVCSKiYRwhfbkh+k/JBI/+dyxBWSygs0GY3Ox6HC/JdWqc7WqGg43zs/bV9lOqdytVmFgMI/7dDoYXiGVKmayl6GQXSq1iASFbNoCDUQssYvFLrHYKxIhC7EoLBY5eDx4qMzGJhLfM4yVh+HgwHl8bNxYd7OZEbk0Z7Xmvd5uPt+vlAeNRq/Z7DYarUq1Va1ej8atcs2v0xnZbLdaXcxmqtW8wrVn0LGsYrFNJHaKRB4Ym1AYEAqBWH14GDAZp/+QWCRa/teDBgO0DsXRkfzg
*/