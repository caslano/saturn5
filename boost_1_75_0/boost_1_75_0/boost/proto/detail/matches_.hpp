#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/matches_.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_MATCHES_N_FUN(Z, N, DATA)                                                   \
        matches_<                                                                                   \
            typename detail::expr_traits<typename Args1::BOOST_PP_CAT(child, N)>::value_type::proto_derived_expr \
          , typename detail::expr_traits<typename Args1::BOOST_PP_CAT(child, N)>::value_type::proto_grammar \
          , typename Args2::BOOST_PP_CAT(child, N)::proto_grammar                                   \
        >

    #define BOOST_PROTO_DEFINE_MATCHES(Z, N, DATA)                                                  \
        matches_<                                                                                   \
            Expr                                                                                    \
          , BasicExpr                                                                               \
          , typename BOOST_PP_CAT(G, N)::proto_grammar                                              \
        >

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/matches_.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file matches_.hpp
    /// Definitions of matches_ specializations
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PP_MAX(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_MAX_LOGICAL_ARITY), <boost/proto/detail/matches_.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_MATCHES
    #undef BOOST_PROTO_MATCHES_N_FUN

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    #if N <= BOOST_PROTO_MAX_LOGICAL_ARITY

        // handle proto::or_
        template<typename Expr, typename BasicExpr BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G)>
        struct matches_<Expr, BasicExpr, proto::or_<BOOST_PP_ENUM_PARAMS(N, G)> >
          : BOOST_PP_CAT(or_, N)<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr BOOST_PP_ENUM_TRAILING_PARAMS(N, G)
            >
        {};

        // handle proto::and_
        template<typename Expr, typename BasicExpr, BOOST_PP_ENUM_PARAMS(N, typename G)>
        struct matches_<Expr, BasicExpr, proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
          : detail::BOOST_PP_CAT(and_, N)<
                BOOST_PROTO_DEFINE_MATCHES(~, 0, ~)::value,
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_MATCHES, ~)
            >
        {};

    #endif

    #if N <= BOOST_PROTO_MAX_ARITY

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, N>, proto::basic_expr<Tag, Args2, N> >
          : BOOST_PP_CAT(and_, N)<
                BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
            >
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, N>, proto::basic_expr<proto::_, Args2, N> >
          : BOOST_PP_CAT(and_, N)<
                BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
            >
        {};

    #endif

    #undef N

#endif

/* matches_.hpp
rMAjY7+LHJx6yosvCzg8dUoULz7AJjbisMoE7TzuB4wt8fIZRp/UC4GhqiNkjTnT+KGKOuatRcb8vmbLNrirGn0Cx4/tLF7jial4TDlrZvTOmQx3rxmRb8vMEIhELGfvz37Q6R4oOcljlzga2M2codONjxluf2dlAPUS9km5cn30MET7jpwa2Xvp5sns4XD6axneyi+74UucNPaeL2O8kUY1RqdAmkNSVSIGIcHi528eOiRcoAjecld3ysZzS0schqy2SvJI25zWUBcz2sd8d42/VMt40HfiT5T9OOEeYHARcnk1MBeUO4cPwC+h3795zffXBPGqlOWmX0Gaxel1xQ6rr5lUrXZ1dOh+qOrQPQ69acTaKtBesWwmXA9OcaW/adC1Zrfq77QZGt+piKFb7BKsPeQyxN34K97BaSrmAMcWTJILBJfoM8u65afRu2eyiNMPjuyd5SsQ1s15znA9/7Bn6AnpSvUNfWOOf7xfgv9Jtmpe4k1WocGtN+em1LCzG+TTpjRjrO5qPkejkrhdSRAq2qWPIIorQ0QXjEvlZHqSb9V8IHZvWvCIBRB+b6lsir/5pC2XW6fOwOinmdf1spnj141hFSSFNzM1x66U7ptAd/xeQFH6OLVWozFXj7wrzpeYm1bj8RWcSbfwLTw9HKBAWQgq2RKBHzt+kLdnFn7N7EfqisAFoIylH7slaIhT5tEfM763yo+bnaOG
*/