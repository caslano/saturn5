#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/and_n.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/and_n.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file and_n.hpp
    /// Definitions of and_N, and_impl
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PP_MAX(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_MAX_LOGICAL_ARITY), <boost/proto/detail/and_n.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    // Assymetry here between the handling of and_N and or_N because
    // and_N is used by lambda_matches up to BOOST_PROTO_MAX_ARITY,
    // regardless of how low BOOST_PROTO_MAX_LOGICAL_ARITY is.
    template<bool B, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), typename P)>
    struct BOOST_PP_CAT(and_, N)
    #if 2 == N
      : mpl::bool_<P0::value>
    {};
    #else
      : BOOST_PP_CAT(and_, BOOST_PP_DEC(N))<
            P0::value BOOST_PP_COMMA_IF(BOOST_PP_SUB(N,2))
            BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_DEC(N), P)
        >
    {};
    #endif

    template<BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), typename P)>
    struct BOOST_PP_CAT(and_, N)<false, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), P)>
      : mpl::false_
    {};

    #if N <= BOOST_PROTO_MAX_LOGICAL_ARITY

        template<BOOST_PP_ENUM_PARAMS(N, typename G), typename Expr, typename State, typename Data>
        struct _and_impl<proto::and_<BOOST_PP_ENUM_PARAMS(N, G)>, Expr, State, Data>
          : proto::transform_impl<Expr, State, Data>
        {
            #define M0(Z, N, DATA)                                                            \
            typedef                                                                           \
                typename proto::when<proto::_, BOOST_PP_CAT(G, N)>                            \
                    ::template impl<Expr, State, Data>                                        \
            BOOST_PP_CAT(Gimpl, N);                                                           \
            /**/
            BOOST_PP_REPEAT(N, M0, ~)
            #undef M0

            typedef typename BOOST_PP_CAT(Gimpl, BOOST_PP_DEC(N))::result_type result_type;

            result_type operator()(
                typename _and_impl::expr_param e
              , typename _and_impl::state_param s
              , typename _and_impl::data_param d
            ) const
            {
                // Fix: jfalcou - 12/29/2010
                // Avoid the use of comma operator here so as not to find Proto's
                // by accident.
                // expands to G0()(e,s,d); G1()(e,s,d); ... G{N-1}()(e,s,d);
                #define M0(Z,N,DATA) BOOST_PP_CAT(Gimpl,N)()(e,s,d);
                BOOST_PP_REPEAT(BOOST_PP_DEC(N),M0,~)
                return BOOST_PP_CAT(Gimpl,BOOST_PP_DEC(N))()(e,s,d);
                #undef M0
            }
        };

    #endif

    #undef N

#endif

/* and_n.hpp
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
*/