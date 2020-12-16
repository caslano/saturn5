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
3kZ5nCurPK/Benpy5Yp7vu7FUXlflB9nqsl4wfMS0etuSEzitj3EfD4V5aMLWTWqZj7cBtr+cZTh9OplhAW9a4tw6He0ZYVMaZYPQh53o+eWpsqKoqhcSfE5IfiijfKyLC+0ynLDGbD0OY285BeSEmc807gd/0r5nM2yypZaKeacCB0GPRGO+3GUZ8GsbSS47mHh0RQEC75mu6MX+FHW88Nx1wfS9pQSlFJtwXb2xvvjeb8Ng880ipUpa0yal5zXvnQYjfpobqLvY91Ofd2hRNF58KmU14VSKiu1y9ctJGDKsMQHNcWLhoncJtzUNowwWblc/bUbM3UFmoLYFIx3QYktxbEa8RJMWWGEznLmx92+UxMZH0KvgYWYS7o3uexjvxy2DpjWwxtu1HZZWgvDyxS0cF01ev7LvoZYjGGUZaqyRcbwoRxyRt8lmDOK3Uief6B8zmd5VSpVNJAnLNTxmPxzlGfKyqZK61paPyb/Y46jyD/Ug/o+uwtZ2ixj7U354vigHVfrIAjb2/MCcidomxx5W//43nCW8rooqtQImfpW2J4djvb7ujEM8SiDq8BzteXd2uTCxI32D2f+ce7c2eA9CJYpFmx0/uTtPPmldFCrujVjy5H215gG9nNdDJeYdvVo0tk0rlCbxqc1aBzJkX7jGcZ/6TArhH7LGcaAWU6/fZ+/27qBjmW7N6HPhlfXXCMGO8gHEBp28txs6YmY/txsIX7NSoiLFPW5ZnkuVJqkakG3x6WmXqepLca3e+MG7uNVYbW7xflbwYX5hndAVP17CmEcZW0Rr4LV8ESf6QLLA6sGlIf61O7H01p5cC/2V2Z1xkUe/MUDE7yy+KdfZBJ43DXiUbAsN0le1LkvB7xZ+QUJ9QLdQrigy1lRHiJlxpicc/4/+ngfTg9OHw7pXXn24GjPSDivdJMyAIZzgkEdFsSiLioX4IxFYhsEvVZIjZYM2F/k8g2+9P5yb7h/wRkZwG3jhaMynNvf6c7QN5rfL6QyW3hfgO838XcqsFn02HCXs2m6qQCL3zF2rTLZVh54BH9/8lLdIBZ9/clK15rwQH/TTsbSJBubqvt+K7x3ORLFh/i2YDVOvt8G+Wix1aja4W56u3e77/MFIpxj4e6wTtoFrgn0jP3HWwF9ZxImJ9kbf3eX6MxZGJvBEwaD27U7b1/GMwri/xzjs0Y0jc0E2x6i6XGM/wfFX8wbq6paaAi5uetmdQiO0floumvEv7SiKYwqIQENlB7wd6T4i7xOG5MVCcBRKB7zPxXzr5s64XVStQnG4Eq2F4P3ERRfw/E6k0kjAd8uIuPZtQX504U4D16bTCndQJqldokyqkNji6IUiQC4t0ru16GJ8EZJZZo0B7x7oyKGhCEuH+LRb4NUQsoMEvTVdDv9trgOmamsEHk2b6fuiPgwPNdT/Lm6roysfJWHxy+YnwOD7WZcHpubRgilMA7r+PIxnOXiu9Gb437Q0tRFZUrmKkAGXtwP74vbqTDamrxuk/hXPp+AIf6jEd7VoFZGqxaPB8UI/1mKv1CXolKVkC2+ayCC/1qElyaVdc0d/+n2YG1t/cwC/nsRPhdcpKWRiD+7gP9FXB5bFk2eJi1+e3a0F/BBf4nizwup0oJbz39/ejkeo3+M2iblJuNaKHbslpvnHk9moW2wv1buFuuj6ybXuRDMH9YwumjcX7ekaS5mJhdSFCmbOj1omoAFO1eKv1DWJkvLvGxvCF0IW4J/AOJxbeHS8Fz5BAeTcJBG/GrEXyWFdkm0h5Olq5OBU/w5UVSqThs5X0o9OrSPpNiG1SKTlSkVm44OwY/O/nBwuHfciyG9RdPwFB7fyqYoTC/RgOgqhBhSe1E=
*/