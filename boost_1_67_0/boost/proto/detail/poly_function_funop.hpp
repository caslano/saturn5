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