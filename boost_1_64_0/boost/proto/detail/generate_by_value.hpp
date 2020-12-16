#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/generate_by_value.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/generate_by_value.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file generate_by_value.hpp
    /// Contains definition of by_value_generator_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/generate_by_value.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Arg) >
    struct by_value_generator_<
        proto::expr<Tag, BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, Arg)>, N>
    >
    {
        typedef
            BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, Arg)>
        src_args;

        typedef
            BOOST_PP_CAT(list, N)<
                BOOST_PP_ENUM_BINARY_PARAMS(N, typename uncvref<Arg, >::type BOOST_PP_INTERCEPT)
            >
        dst_args;

        typedef proto::expr<Tag, src_args, N> src_type;
        typedef proto::expr<Tag, dst_args, N> type;

        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                BOOST_PP_ENUM_PARAMS(N, e.child)
            };
            return that;
        }
    };

    template<typename Tag BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Arg) >
    struct by_value_generator_<
        proto::basic_expr<Tag, BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, Arg)>, N>
    >
    {
        typedef
            BOOST_PP_CAT(list, N)<BOOST_PP_ENUM_PARAMS(N, Arg)>
        src_args;

        typedef
            BOOST_PP_CAT(list, N)<
                BOOST_PP_ENUM_BINARY_PARAMS(N, typename uncvref<Arg, >::type BOOST_PP_INTERCEPT)
            >
        dst_args;

        typedef proto::basic_expr<Tag, src_args, N> src_type;
        typedef proto::basic_expr<Tag, dst_args, N> type;

        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                BOOST_PP_ENUM_PARAMS(N, e.child)
            };
            return that;
        }
    };

    #undef N

#endif

/* generate_by_value.hpp
A1cb8ekUj7O2rbCcC3tnbHMjrGobRnDpIj/JOqFRG3jwvBIVTYv/H9vg8Owb0epsG2Sv/8scJNtX4xg9YosN8/vDok+cCXCMrPq5yjMn2xjHXbh4Ec9Piu+YtJWp4sYBFmQeIMl34zn9x2hOQy2VF3U9R8L83uO88xcR/7a7Jb6QgTttLA5oOvKSpm1yOkECF5FHeHCBL5lteNU3HNFxb5bIKNNS3NVglKycrFiSk8sxmuQYUBTn4X3TtsEIP49/MC1jcWxQ2Eu1cMH3QpXxPpPoWY7pMyneZc0r0dZtxxBnOXIcU3gDeuddosx2M5CzYH2gkJVkqSffHWNersXzP/4ebKLWMLts+o72rTk5bdQxw3e0lVI6rMf/uEauhTXtUhzMWI6xD4AjwG8Y/wA+DfRvh9/i/2gezsvxUnpYajsIbZFG+i5uC9/TNYVzcUsqx626qgp1ZSAe4dbJwfjsuCOF5ZZ1WvfCajO7EyI8UZpeE1V4Z9PTeeZHtBllAy2BtFAX0lVKeo4889EuqOti4+FPpBLJpweik7MpIzZSz3xxkcNi+rwY4mp/l8Q5T+Wh4+uPnE2HFHCP5/eAU1IOBXCHI+4nXpDfA566es2jYkD2vvB7/OWsPJWBWxk6D98XeaAT1LcTGLTOJP6uHx3gsDRXGIuPcF0f37Xcq3WtWniGW6K35piJntoYv+w5o9xIIu522xqMExRRh5Sd6fDZITrvac6JMaJjOhu3mGqRDl4kkRvA4/ua8tAkcRxGtIS0ILpxGrvoP9EC/cgk7okXz/ZtXIwXj5+3NX0kbt6UF/DuGHfWeRjWe5I8f9fMcurO1tkmLNbErw75aW96/QhD6MLGKvKwPaPkM7RXdR93U/lOC2qnZWE2kA4s5tE7su9Mz6VjNP7TYpiNWFrKIr98QKnzCFJ1IgTBQhbb/4NQOdC6R9Gm2KXQN1K3msVBjLXj9UAp52AAY9uwp1JafSTVmbpiB5Pp6dlxDLOB8AHX+3ZRt2JCgUQV+pQnEPCeBHhzN7/t7OeW4xyW9TmhIChGw2KmA6yxzIM/qs/3SnovVaoPsJbXdwl5XYrvWfCqq/uugiMSNiS1Ni3k1C8X9XbMN03orabKpfkZuyA272BfxWWqt1BWdlIoyyLWPAYDgJMY7T8s6qwZj2PThQ5zGKb2Fqgrh9lekOIKxSxXTWh8x/jRycnZ8XxuQDg8nR/nBynIdqJa2OY++Fn0rg6eh2BCzyDh0s7B6WQhZsplCs97pnSnq6aJk5UUW7GGtP4gmMTkBAK77u/u5uRbxVvU9rPGcT8ayy0PqDNKxM6mC2cicIGM2ICP2hRCLZQT9r+lg+vvi88q119jwsyShNKhnPE4T9x3EB/jVbmmE9KgfUVcftTIAjc+hjIpYz3/DWlhbPCmrbWpLNIC3cnI5ukU5zQ8m86p5G1dWV8zQNk8GvbNxCG/RuF5zYy1tuUGqwKUR01Pr51LAdoK+J8p2lDYTd883en5zk4y6grD8tuOypO8NJTf+cX4zl/e+zn2Z4mfXvOH4yjDPXgZ3HCMZD3DxUW4GL50ehYDfmwjrcvLaOWlMPT98SM4WP1gM4HlYihPAU5hEGM5tsWMy3HWor4EYZ68pL2xV8Ao5b31sWJOG2Z7Z2qvxrLyfE2n3ubNwVYmOb90QUcxw1vvG9n8OzpUn1yjX/LmKA6Aa0LgQjAbcZBAvtCowdlg43b/gkbcX8aJuq0btoBaxnC7XOB1TLimr0IrsA9DXKp05lHu7SLuEUqjZ6GuQ+taCQe8S6d0tq7bQZw9inOp88GLqu1ZhLQQ+IykzxhwXkxxLNOem17FcR+W91BRflsucXjH+07YAPcswSk=
*/