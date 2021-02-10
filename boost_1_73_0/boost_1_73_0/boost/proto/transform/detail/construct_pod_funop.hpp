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
JGBQSwECAAAKAAAACAAtZ0pS3+etns8CAABJBQAAHgAJAAAAAAABAAAAAABcLj8AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODY5VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpKXSS7NAQAAZwMAAB0ACQAAAAAAAQAAAAAAcDE/AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDg3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUnw893rLAQAA7wIAAB4ACQAAAAAAAQAAAAAAgTM/AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDg3MFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIUMGsFnAEAAIkCAAAeAAkAAAAAAAEAAAAAAJE1PwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q4NzFVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSBekqnqgBAAChAgAAHgAJAAAAAAABAAAAAAByNz8AY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODcyVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoL40bA0AwAAFQYAAB4ACQAAAAAAAQAAAAAAXzk/AGN1cmwtbWFzdGVyL3Rlc3RzL2Rh
*/