#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/poly_function_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_NORMALIZE_ARG(Z, N, DATA)                                                   \
        static_cast<typename normalize_arg<BOOST_PP_CAT(A, N) const &>                              \
            ::reference>(BOOST_PP_CAT(a, N))                                                        \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/poly_function_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // poly_function_funop.hpp
    // Contains overloads of poly_function\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/poly_function_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_NORMALIZE_ARG

#else

    #define N BOOST_PP_ITERATION()

    template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
      : Derived::template impl<
            BOOST_PP_ENUM_BINARY_PARAMS(
                N
              , typename normalize_arg<A
              , >::type BOOST_PP_INTERCEPT
            )
        >
    {
        typedef typename result::result_type type;
    };

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    typename result<
        Derived const(
            BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT)
        )
    >::type
    operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
    {
        result<
            Derived const(
                BOOST_PP_ENUM_BINARY_PARAMS(N, A, const & BOOST_PP_INTERCEPT)
            )
        > impl;

        return impl(BOOST_PP_ENUM(N, BOOST_PROTO_NORMALIZE_ARG, ~));
    }

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* poly_function_funop.hpp
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
*/