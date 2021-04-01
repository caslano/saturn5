#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/transform/detail/preprocessed/construct_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/construct_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file construct_funop.hpp
    /// Overloads of construct_\<\>::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                         \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/transform/detail/construct_funop.hpp>))
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
        return Type(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif

/* construct_funop.hpp
0q7vsxcJVS0TdgIE/WwsjTMWmZEJB/fUissARZ+FqurM19VtVnunC/E6bi1qCJJCsFkGpb66zmI0ZcWozoq4Us9FJ7qW5pTC5MCSrF3rH1IfmoU4AilEA/m4H4AB2HZqawPDSU7xAToT4AFHNAjc/oiY/63Jcg79Xmj5ggZ/pmj4NEg35q3QV09qvr8famWDhmXeB5PSnYX0qLz/Ejadt3t1NZ/kYq6x4WHS/+4vmdq3l4jCCfb6FpSb9oPCp3w/E75kG8wcupA1pWMDsWkAIDKq/VjNBZv9ayfskfY3OOnvh0iKf06OfuuLIjoaQH/7P75mS2B35e2pwbQtV7i3iErxMK6PdSfwRFZrwW1cmxp0DyCG4KryRYb7/rF0uP44l0aH61OK/gUAmhWvd/9b5M7uRTLfVX777rBzTL6B/TRu0NSwdJWL2VjQE9d4KjI3rIDmpc2hMyQCUpQyPR6yGAGTBJKPqtG5nGZqEoQcveHrb1YpWADWSiKdyAFhaIciuL4hPaJWVG7Nkjd+P3ATzodpJoStMl67i0+OmQ7qWxXBREIyUqISCG4cPw==
*/