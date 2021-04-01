#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/pack_impl.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/pack_impl.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file pack_impl.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), <boost/proto/transform/detail/pack_impl.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else
    #if BOOST_PP_ITERATION_DEPTH() == 1
        #define N BOOST_PP_ITERATION()
        #define M BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N)
        #define M0(Z, X, D)  typename expand_pattern_helper<proto::_child_c<X>, Fun>::type

        template<typename Fun, typename Cont>
        struct expand_pattern<BOOST_PP_INC(N), Fun, Cont>
          : Cont::template cat<BOOST_PP_ENUM(BOOST_PP_INC(N), M0, ~)>
        {
            BOOST_MPL_ASSERT_MSG(
                (expand_pattern_helper<proto::_child_c<0>, Fun>::applied::value)
              , NO_PACK_EXPRESSION_FOUND_IN_UNPACKING_PATTERN
              , (Fun)
            );
        };

        template<typename Ret BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct BOOST_PP_CAT(expand_pattern_rest_, N)
        {
            template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_INC(M), typename C, void)>
            struct cat;

            #define BOOST_PP_ITERATION_PARAMS_2                                                     \
                (3, (1, M, <boost/proto/transform/detail/pack_impl.hpp>))
            #include BOOST_PP_ITERATE()
        };
        #undef M0
        #undef M
        #undef N
    #else
        #define I BOOST_PP_ITERATION()
        #define J BOOST_PP_RELATIVE_ITERATION(1)
            template<BOOST_PP_ENUM_PARAMS(I, typename C)>
            struct cat<BOOST_PP_ENUM_PARAMS(I, C)>
            {
                typedef msvc_fun_workaround<Ret(BOOST_PP_ENUM_PARAMS(J, A) BOOST_PP_COMMA_IF(J) BOOST_PP_ENUM_PARAMS(I, C))> type;
            };
        #undef J
        #undef I
    #endif
#endif

/* pack_impl.hpp
T+vMa8XY09Qg6Ux8HhyvsISkvQa7WY9o9bJNUY9V3Cli6R45GjoAEoG3FRajk4b/JdCfQfNHvBgheF4Beo4gEwFJpghZJ8l4VBE60uNC3xzMqo2wUy6kqIxmjut4IZZQw8pbsV+IbjvHWmG9g+/4Ar9cKSelIgNIDwexXO+sUI2bksg9XfAGN7+M0j6WomHrGsrfi07L+3nnBn5zJcIogqpmyj+VhZ+eZDPp6NYzmnwMVXG5n3pTrJ/U79BfJNmQTuLSssXrQ9Q4JFqH4Ufrrq+YYHT4NXk5kWalNghlKSGEeNvL5IYjYWOpUIfJMmG1SHExfast35zTeFOj8Nbiqadzk3dp3bOQReL7QW4ui7R5TJ41sAHzew/VGaNWbtK1ehiYP3WgNYPEc7h3pETYJmrcLKuoT0x5q35mxzwKlaOAummqD0Fum1FxKEqLZJ7a3mrzQHPWr89SqwA1i+pcT83YOVbTuzZ9wIdg1BJxzXnNBvqawRU1LZpTalBfR9BUGsxSVGZfrZl7LebrPbP9l3Iz52SxFPTMFJef/pGJa7vLQ3iZup3F1dV6Ow==
*/