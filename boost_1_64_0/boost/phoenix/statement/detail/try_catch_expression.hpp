
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
8v06Fsc9sv9QN/KeZbYh2Q99Cbb2qBqy/9aU67hacp6oLftxURYMkeUXSb2o65RrsvyY0nq9RKGql3HYEGOwGZpl/Vhk/YzH3jgBwzEWh2EcTsKJuBAn4TqMx404GZ/GBNyGiajqxYpv4BQ8gMn4GabgBZyKV3Aa/okzUI3LnoltcBa2w9nYAe/H4TgHU3EuzsQ02U6CVXjScf0YRn34YDlbfZgc84XIfP63mC9c5it/i/msuZxvRS7nyzTkL8jkPF/Pgo75suzx3Xy+bMN8kS7pDjKk67dZ0vUwXx9j/cl85W8xX/hN4os21p9bfO7z7StM/cl8WQH69v6x2h8Ly/NwOd69j2rZw1gRj6BWV1gXj2FXPI4R+Amm4qe4CD/Dlfg5Pq61/+nH3S9wO36Jr+Jp3Iln8S38Dg/h95iF/8TTeAEv409Ylsz/rPKFF7E5/opt8Tcci5dUunhZpYNX8BhexRP4J36NHCzSstEHf8OCWIg6KYMV0Q+boz+2xXI4FsujqrsgPI2V8GesjPU44FTBLlgV+2ANHIm10Yp1cC7WxcexHj6JzXAXNsd92Aq/x9bIMqY2SDCF4kBsiyOwI5rxPpyOvfAB7I0bsA8+hYPwdRyMb+NQ/AEjsX4hzht4L47A/jgSh+FYjMFovB/H4Xw04zK04FYcjy9hAh7ERDyKU/ASJuENTMEabHOp2A6nqnRwGibjDEzFWaoceL+qD5yDV3AuFijCeRcDcQF2wIU4GB/Ch3AxrsG/qXLjEjyCS/E4LsM/cTmWKcq+gf64EoPwEWyLq7AjPoZD8XEcjetVPeAGfAOfwP24Ec/iJryAW3BQMc6rGIuZmIZ/V/nEl/FFfAW34w7ci6/iCdyJFYpzPsRw3I3DcS/G4Ttoxf34GB7Al/FdfAffw0N4ELPwEH6B/8Cv8DD+iEdUvZagnR6L4lFVL5iF5fGYygd+iFXxODbCj7EFfoUD8LSqJ/xGbS94RtULnsWP8FssWZL9HVvhOWyHP+Bg/FHVL55HK/6Ez+HPqp4wW+0X+IuqX7yIBUuxvxbiPgkrYhushB2xMlqwCi7FOvgSNsYj2ASPY1P8A0OQa1hTM1yCzXEbtsDd2BL/gW3wV2yHJcpw/Yx1sAM2xu4qHuyBfbEnJmMvzMA+eBD74hnsh//EASpejEDVlj0Y6+MQDMFR2BmjcTCOw5EYg/PQjM9hLO7AySodTMCjaMVLOAWr+LO/qXhxpqo3nIVjcDYuwPm4FhfgM/gQ7sNF+D4uxmP4NzyFS1V5cK2qT1yHBQLYf1Q58HEch+sxBTfg/bhZ1Tc+hSvwaTyEz+BhfBbVeWxrQXkPr7yfVx2Lk0zEw3T128Z8FTADq+ILWAtfxAb4CrbH7dgfd2AKvoqbcZda37gbX8HX1XrHvWp7wX34Lb6FKhNvYxH8B1bD97EOHsF++AEuxCwVPx7Dvfgh7sePVbz4GZ7Az/EL/AKLUrZvsBKewRr4LfbC79CKP+BMzMaH8aJaX/grvow5uAv/VOsJr6t00FSY4zH6YEfqrgAOwIIYg74Yj6VwEQbgeiyLm7EcHsLymI2BeBErqXixKpbw5fobq2ItrI21sS/WwWSsj+uwMWZiE3wfm+KH2Br/iW3wF2yLdK813YsR2B4TsAMuxo64AsPwMeyBP+F9OIfzx0BciREqXRyEz+NgfAWn4NuYpNLHZFUunK7yX4T9A5viA3gfzsP++CCm4nx8EReoeHChKg8+hCdxCV7Bpag6hi9DP1yNibhG5RM3qHziEyqfuBHfxE34HW7G3/BZLKrOL1gGn8PW+DyOxhfQii/iXHwJH8ad+AzuwhdwNx7H17Ec+9UeHIx70YJv4Aw=
*/