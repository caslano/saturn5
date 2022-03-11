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