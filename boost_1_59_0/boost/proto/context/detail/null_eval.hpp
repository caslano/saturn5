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
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
*/