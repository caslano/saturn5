
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMAprotected ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTYprotected

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PROTECTED(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `protected` (this can be
//               checked with `..._IS_PROTECTED` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PROTECTED(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PROTECTED_CAT_TO_EMPTY, \
            tokens)

#endif // #include guard


/* protected.hpp
fH1Eluajm2CkEl5e6rDJ5ex+2AA5eO0cP3D6pnBc4dhIq5lkiQJNnITfBUbWh5AYpOVfAls6IIdLLzNJqtO7lH80rnk//8g9I/Nww0IPp+yoeRJ85ioDy9PQyQEobGSmb/rjn51J3sm7vl7JW0Eezoa3TIQz7Wqi0/CH+Br0acKZNaeK3n1bB77V3MTXPStFDAUGh6Ke8BibJkxhtwfArtuR+EwhcwDVMZomyWH0SLkVnHK3J7hWkT7B0RuGHqIc0tZK3W27vMBwmXvc2dV1qZwfS+IbF7+tvxEDFe3BojJMQ6CSMtiEQiXwelRitedwT+kiQG8GoS8lTLM5LQGzuY8HftoMEsvjX3bOu11NvXLfUQEPwOL/XOqE9oan7+SiazdVf2dNxszLU4n/bkl5MWXP1fPoKftrD52/kCcG0e9ggkYBQDucERELava8o6PpHvvvi5gmBnAwIMrRcIQ95hpPM5WviIolWxm3oVn89aYrUMNl+9Ay0TgZGIJ/x+xwxh6cIBmGKhZZkCHmLyCFTA2vw/CaNmM4WsUzOdRidZuG+nMYFmg/ip+qOw==
*/