/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010-2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

    #define BOOST_PHOENIX_ARGUMENT_N_TYPE(_, N, name)                           \
    typedef                                                                     \
        expression::argument<BOOST_PP_INC(N)>::type                             \
        BOOST_PP_CAT(BOOST_PP_CAT(name, BOOST_PP_INC(N)), _type)                \
        BOOST_ATTRIBUTE_UNUSED;                                                 \
    /**/
    
    #define BOOST_PHOENIX_ARGUMENT_N_INSTANCE(_, N, name)                       \
    expression::argument<BOOST_PP_INC(N)>::type const                           \
        BOOST_ATTRIBUTE_UNUSED                                                  \
        BOOST_PP_CAT(name, BOOST_PP_INC(N)) = {{{}}};                           \
    /**/


    namespace placeholders
    {
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, _)
#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, _)
#endif
    }

    namespace arg_names
    {
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_TYPE, _)
#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, arg)
        BOOST_PP_REPEAT(BOOST_PHOENIX_ARG_LIMIT, BOOST_PHOENIX_ARGUMENT_N_INSTANCE, _)
#endif
    }

    #undef BOOST_PHOENIX_ARGUMENT_N_TYPE
    #undef BOOST_PHOENIX_ARGUMENT_N_INSTANCE


/* argument.hpp
0/Ou7s2hEY3o4I1DBr52QM4jora/TEThQggn3gHtTnKTHjjIMIBJZ01JtVEa4OKZ4JbDMgCa5co4DSq5KZm78YnccO4H0IczpkT8V9yqh9SZGZmoDqlTCA2Rcc8O2APTi8OltJSmwiqyAucOaDdWppd05lJAfnkkSEOWGCf/aGPwBEryEBbzgC9rbQjIcoYbiH6n7DsrLb4eXKyEeXFB6JmrY27WOLgBxUjnH46wncpziFoZ4c/bWbvMCYHXMMS5ltBgbYQD+toBGG2nA3qIW0IziYNusorcNAdQnl+OJnvrqa/iZOsmeGuxi0gn64PM86G1Am9MgbJeA/ukarLkYvnv44XBy/GwMZ6H0hFNDOasXrC3/vjX9D/ZnTVOFHM4ZIbPWkc5FZmxm349Q4y8DJZ9BMJb78VLGl0wveuEcAd1XAmwAYYgtXXkEmxkhG+f0TGO+NoHCXrFi6ZMI6/byrv8ZP/ANMFyl3N27wWWeI8s3lVcvU3stZFGACxoGKLGJnL5glqGj74Wt7+7q3B3j/IzYlr2ex9n9w0TXkI+tWNhxwkXFP2hV1IT7w==
*/