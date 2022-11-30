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
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
*/