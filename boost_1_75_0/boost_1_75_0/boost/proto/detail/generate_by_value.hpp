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
kHcFmeqtssiBmtor2Nhp3TtYe7UdaTd/R10O6sTwHqg8shMkhmf4ywlFyfj+YFTwZZw6YYq+nfc22WUVEtZk2pxPihUF4p8zSmyEuLtBbH5a7Jugtq2afgChJFYLSW+q0EwY37ZRV7Gb5FtH9HakI5h6uU0SlKMJ9LKDSjRR5ANol6ZPDTfq326k/kX3476uImZatWZScEVo87XF0Fca6Gy0w4tTG9ZV05HnQgoY4dT2NVqhrFbYQtWEuHlejOWabBp3Pkn2lQeNkA0/TJ3GNDlTeH2xjdXuq3Unapl6adMH/u9ScPmEhh8/vuJlmKN7x6r34Iiw9pijlZLZ7HKqG0bk9Tsml0tYY6/2WLG8GX1tDDO4HHt/3wuiPpTHPGF8D99H0Eu2M85kezJFD0Bmz3vkttn2GUM0YDuaYpsejx1ln+vxECqXqf4Pbn9BdslA6iwbC0SivzdxAFv62IMHsMRLhNiW0lBh8snaYbDW7HJJZFRwdlRM/cHuGDWy+sdn575eavSEPhnlAQLG2GQJORqThC/0nFXxfGmikwSrLh9POEuFQ0Ib4t94DuROYXkGdH85ehGC2QQiBIM2OWWa04RVtYXBqQcJkTImgX5VnWV3f2i/0LKq+UWQHNHPv2JtFvHiWY24dHScsT2qDF+csanNuqPuSvAsJXoBfJo4oAbIfqxMVK+jtWZcGyBhlD1gUSBdIaEywm5SFrQJ
*/