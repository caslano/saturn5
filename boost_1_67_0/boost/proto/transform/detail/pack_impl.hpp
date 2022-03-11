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