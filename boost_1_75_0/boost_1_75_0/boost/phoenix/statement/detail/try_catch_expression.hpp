
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
hiWNXt/75HLwpjBdRxK20MPq95/CObKQh/Lghh3og4p5xEsrSJuLh/HY27FjqtI5bQwwseSvyfieTvvdmODAxtCTK8JFjXyOAdPX/QkKqHzHXXfVFdochVB8wJea7fYLe6+68CHVEqqljF4LxQST8IJjo7ykDgL83c22cMMHUZKlHjCFHztwIMvrAwV0zZB6qCl+8lb78xjRo9LdHWnB/Q6+c3rvizhZoxPTFMlyD9WeVpus8E58aOL2bM+HbIlLzBg6IJsSa8gi9M6lTWwNP1PJIQJ5/edDalJTpQfQT1MFxkToXM79it2Rb8SdyHT+a7Pec3M0ss3dPaSCW/bvN6tpxvbz14UaeeyIfCsU9KEAyX7Qo+JSt7qN8+ztzdV8wbyfo62S6syH6VJuuPdW2kaGnaZRTTCP6Rdfu2wueoT9+/Z3v0if7fb2nwfQUe3cDKQKW6yvP4euzaE7Tfenv9iTLPX3WvjaWDb5yAeEEWV8Z5Nf+HCrk9DScC/3BBo10rR0tCdkuL72p6/w1ZUvpbvzSmd+H8GNIrDuUmlqrtS5aSlgLlxuabq3ZU18GjbjOfrP6EandYBjL+3ONvZw4/6IHi+6eub872K2QQOdKvfm5RmKtx0eI6004hvI1bSznaD+NIPBCBPC+eWGu/dK2AGrSOjpwZ5tMLfceZxbR3imA+3STq8s1KLKoMGyzfKjf9NFn6pG6DZulUZk
*/