#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/construct_pod_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_pod_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_pod_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/construct_pod_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    Type operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, &a)) const
    {
        Type that = {BOOST_PP_ENUM_PARAMS(N, a)};
        return that;
    }

    #undef N

#endif

/* construct_pod_funop.hpp
ACcAAABjdXJsX3g4Ni13aW5kb3dzL3NoYXJlL2N1cmwvY3VybC1jb25maWfVGGlz0kD0e2f4D0/sqHUIoeh41xFpq4w9sMRbB5dkIWvDJmY3ULT+d9/u5qCECo5+0HRINi/vPnd79QrYA8Zt4Vc2rt78exdyg5VXX//6eOFTU3Tj8At15TJkhXcO+k9RfcTnKiE2FCTn/S1YTXIONzRJP5XyCJ8od5Wgj0o3dbOREt9wiZcS
*/