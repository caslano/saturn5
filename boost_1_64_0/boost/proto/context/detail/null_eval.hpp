#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/context/detail/preprocessed/null_eval.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_EVAL_N(Z, N, DATA)                                                          \
        proto::eval(proto::child_c<N>(expr), ctx);                                                  \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/null_eval.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file null_eval.hpp
    /// Contains specializations of the null_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/context/detail/null_eval.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_EVAL_N

#else

    #define N BOOST_PP_ITERATION()

    template<typename Expr, typename Context>
    struct null_eval<Expr, Context, N>
    {
        typedef void result_type;

        void operator ()(Expr &expr, Context &ctx) const
        {
            BOOST_PP_REPEAT(N, BOOST_PROTO_EVAL_N, ~)
        }
    };

    #undef N

#endif

/* null_eval.hpp
KOdIjqpStQz13QUyhR7OrwqLmmuGbfzbbz2+JkXLqEoMvBmWeXDRPPFkLGqXIuKbiz5Sk8IWT553CkYMmyjn27iARoX4BbcoX1mK+WY7tXF09bDc90MYetiu+9EpCgR42xBg6mFn07Sy0/70yrQ6rXYaxC2HGDsTKZDbCWkiUNim5j4xrbzVmC2Pl5VBYbRmEeensCiFxEVDQY9CLu+/xUocfDkMCPddhBTqoNqaB0F3TsqoW0DybfW2atR59ZmG60/LpGWazAOe7xXyS8Sb6YinD7TIY5kI32V19fLtZM9Y40Dgs0iCaXFJoDtyNInn75TaeZxUZjvgA+PXQBW2a83KySu6Y+fjaEvaqAmaJo4GM6WeZBv9pAFltursQUjLd2GDdnaFjJvxN/K2QlujrSXCnPiLh82QM5ffbc0XfjJercKWSQrMYBfb2HjBAiqFK94zjjk0WkC180UpK2quwEDPFgHrPCFPg6sXT8PNmcAlD/p44oTx3uj/fF7apo1v7toIxHms+PUJLUEU8VLqBV3n7H0+WMpg27lLwb8CwLn9Ef2he7QwiM6gmw==
*/