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