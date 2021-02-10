#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/memfun_funop.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/memfun_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // memfun_funop.hpp
    // Contains overloads of memfun::operator().
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (1, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/memfun_funop.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<BOOST_PP_ENUM_PARAMS(N, typename A)>
    BOOST_FORCEINLINE
    result_type operator()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
    {
        BOOST_PROTO_USE_GET_POINTER();
        return (BOOST_PROTO_GET_POINTER(V, obj) ->* pmf)(BOOST_PP_ENUM_PARAMS(N, a));
    }

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* memfun_funop.hpp
bWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMwOVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLLiJD7pQYAACceAAAdAAkAAAAAAAEAAAAAAI2kOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMVVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJbL3oLBAIAAFoDAAAeAAkAAAAAAAEAAAAAAHarOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMTBVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSf7rFb50BAACpAgAAHgAJAAAAAAABAAAAAAC/rTsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MzExVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuIIGjeaAQAAswIAAB4ACQAAAAAAAQAAAAAAoa87AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDMxMlVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLS64jligEAAJoCAAAeAAkAAAAAAAEAAAAAAICxOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMTNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSiTTEqdoMAABpHgAAHgAJAAAA
*/