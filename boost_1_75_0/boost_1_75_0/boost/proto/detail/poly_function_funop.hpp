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
0tSe0z2qPHWqQ13v9ItJ5lPxnd5fcyKztk97oWhQVLdSHq93UHQwODdOnvVsESPaB7ZTO/P+PCYMx08GT/r5HgePpNucD/juirSOgpPLPCQ/oZkCcStJ00WVvWwlhYEzR9J9hYYh1qXhN/2Xuzttm18mobhDrDTNU3ymTaTtH3ljLgCmNQah1D6bShK8YQ+nO3yelJ+ipaLDFzZM7/9gxL9LOTvL6nKdpfwaQ8FsiesGnvq0WaEN/xRoItXvWLpxUuXF+/pNzGWuZ8tQGrOmwzZDOwHeCvBIXCXaFpy1SlTfJ1Wt6zUcrdVGBHaQiAs718yhOOYwTiWHbX9OX32j1L72c+Ce1PRt/0qRNGzXM6eOmaChc8Zo9mSvaf9ZARz5TK3M6efZLubzfqZGmID07Wm/4X2ueyo3Gc/qHUWQmXOI7U4DEbdkNa/xH1v4NqI6a4Ncd0PX88viBjptXCsvF5drUKzw481UN9z9KC/VkSaCDPPuz/esDIWRaMpYLSrmSSeBAvFzZScRIkJ/HbDt8Sid4c+HIc8iLSOcgJ5fPG7aXtpuSWtQqO3qke3Jve299cV9C2/z0+o6YoI0vaWVlIRfltNz79fHmEuL5LKgy9pN97g/6u1lVW6fB3Srp7gMOYDBFesXg6yabaSkLa0brM/jrXUTG7PVYUaDzYPViCOl6pNemyc7Ite5RK+VIkqePlUiL5ckeWenCFvz
*/