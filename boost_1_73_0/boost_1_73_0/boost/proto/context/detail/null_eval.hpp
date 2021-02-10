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
YXRhL3Rlc3QyMDM0VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjElKaivAQAA6gIAAB8ACQAAAAAAAQAAAAAAZto5AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMzVVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSIoyxcgQBAACZAQAAHwAJAAAAAAABAAAAAABb3DkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAzNlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLJKwDQMAIAAMUDAAAfAAkAAAAAAAEAAAAAAKXdOQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyMDM3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUmONxl6sAQAA6gIAAB8ACQAAAAAAAQAAAAAAG+A5AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMzhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS0NBcBp8CAAC6BQAAHwAJAAAAAAABAAAAAAAN4jkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAzOVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIdPzDaAgEAANwBAAAeAAkAAAAAAAEAAAAA
*/