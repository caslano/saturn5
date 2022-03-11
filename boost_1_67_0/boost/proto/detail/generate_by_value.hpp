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