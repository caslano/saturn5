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
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
*/