
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EXPRESSION_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EXPRESSION_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/statement/detail/preprocessed/try_catch_expression.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EXPRESSION_HPP
#define BOOST_PHOENIX_STATEMENT_DETAIL_TRY_CATCH_EXPRESSION_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/try_catch_expression_" BOOST_PHOENIX_LIMIT_STR ".hpp")
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
    (3, (0, BOOST_PHOENIX_CATCH_LIMIT,                                          \
    <boost/phoenix/statement/detail/try_catch_expression.hpp>))
#include BOOST_PHOENIX_ITERATE()

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

        template <
            typename Try
            BOOST_PP_COMMA_IF(BOOST_PHOENIX_ITERATION)
            BOOST_PHOENIX_typename_A
        >
        struct try_catch<
            Try
            BOOST_PP_COMMA_IF(BOOST_PHOENIX_ITERATION)
            BOOST_PHOENIX_A
        >
            : expr_ext<
                try_catch_actor
              , tag::try_catch
              , Try
              BOOST_PP_COMMA_IF(BOOST_PHOENIX_ITERATION) BOOST_PHOENIX_A
            >
        {};
    /**/

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* try_catch_expression.hpp
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
*/