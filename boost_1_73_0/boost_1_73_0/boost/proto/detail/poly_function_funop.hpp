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
YFBLAQIAAAoAAAAIAC1nSlJG6CmK3QEAAJsDAAAeAAkAAAAAAAEAAAAAAArhOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMjVVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS4RK4rvoBAAA/AwAAHgAJAAAAAAABAAAAAAAs4zsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzI2VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUos0lbm8AgAAxAUAAB4ACQAAAAAAAQAAAAAAa+U7AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMyN1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLhN00O6QEAADgDAAAeAAkAAAAAAAEAAAAAAGzoOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMjhVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSurUiMaICAAAHBQAAHgAJAAAAAAABAAAAAACa6jsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzI5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUrV74o2FAQAAAwMAAB0ACQAAAAAAAQAAAAAAge07AGN1cmwtbWFzdGVyL3Rlc3RzL2Rh
*/