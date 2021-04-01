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
aa0DQGHZamIbuwbFwXTccUNlIWYBSlREmr63+hhYsta11aw5AI9OFiJ03JNxD23fygUkCVZbDsNbkyp9Yeug0V09FqOhYysUIgPDP5DhoFCBTHjZ/gSYBUv4w1GBufLLm1FrU/V5GlbZBtRUEbXCUZZ8e1XouOhaoUPP0HrRIps4JHi2v3CPmHI72w1l7gEOsN4CSuY6VD7GStCiCTcC459Unj5cpmb9guM9VJHwY9OdaaiIpmdd5vg0aQqrTGxdm0BBTymq066M3lQSv27m+XQb1Gb1ea2eCkIk0NxeZadjuVm5RoX3xgks8QnTf0B3/Jgp1RY9jmRgdwh0bcJG5bm8yR/LYa69Pwtf+LDS9z1XKgQcVtVuZSbfZ/jWwfbFNisdFlaVGLqZcI1h//Nn2WYJZR9gQBZKgsEIvL6StFHO0rhoVOH4ZFhjWk6+TRvO2rAvREwnqMWa17CJdO51Ll5eXYVe6mdkH/X36/Cls5krhlSk0X1KRypJTrr0VDn3JEkSdaK4+npmckWgls8Dxm5iRfTP3ZzSXsKPrAVGf1klJ9tOdion6a2V6Q==
*/