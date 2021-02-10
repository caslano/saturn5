/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_LIMITS_07072005_1246)
#define FUSION_VECTOR_LIMITS_07072005_1246

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/pp_round.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(FUSION_MAX_VECTOR_SIZE)
# define FUSION_MAX_VECTOR_SIZE 10
#else
# if FUSION_MAX_VECTOR_SIZE < 3
#   undef FUSION_MAX_VECTOR_SIZE
#   define FUSION_MAX_VECTOR_SIZE 10
# endif
#endif

#define FUSION_MAX_VECTOR_SIZE_STR BOOST_PP_STRINGIZE(BOOST_FUSION_PP_ROUND_UP(FUSION_MAX_VECTOR_SIZE))

#endif

/* limits.hpp
2KPDbjJlv0IPuM4BGi+l9k6jtgrIP894N6NcWxVB+jq5uELbJaVk7eVTFLrQUhVmkj0+dj4fwnucy8sGRUalylKtrdcJ7q6YJ5j/isG29JwUft4YRKdlqjsV76MMqPFjGMs5BlKSyQ1mOV6qMCClQ/gT99aKCJZzZ9wBh/DAy3MMuoLDgUJ78ZX+TMpF+w5QZ0QGdyT/I2dx8LPVQe0ZJDey8l6S0wW41H8swzinjOShcs1NcZtJw+LAjCxHccz0E+fj2ezoqJtfyjkItp3kJJkvZhK7q9WbqP10dtANl4Euw4nIPDcyGczDe/aJUVcUdUZf14Cl3uosNhkny+vpW/0klegGRUcfEPoNG1Hp9fkyl3f7IxCs0VS9l7Hdky2yOEmGBVlwo5yDO5o+TPqgTaJQf52QF5SpRqXQEZ7tdQfiZROOeECLg+YWvbhvUDognA4+kSNYr+NYZWcIsynaLmgZoGNUBNZ8gIam6wcddUSFDRv4DuQFwoGiOhW1ydTpcL6qmcJB0ptRKt1JW5utMoUcyoBjxjMxdZ/6rXa3R1am3sUAjw8kb8Wo++1BYAYlGNjJHDA3tFkHJvup/a51Sim5XipuEMyjOLqr80Q/4N/iRfOweQczlJk7Rwsy3K2r0wvl0M7MpM0I3z1f
*/