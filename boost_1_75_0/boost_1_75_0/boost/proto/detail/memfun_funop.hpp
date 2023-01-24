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
7F144a8++SzfY/xIy+6tvglz/sj/bC4cP01ZMF+yg1HmQYF5/uoNDB+m+oO5q032D0AM4yJVuAT8+yBnquxr1a3mNrh4ao7o85PdMTTelQgOAITNs38Y0keKgIr9CmumNY+tbhWHLYr8pOwu0+0GtXEA7M5eAXoDvnvT3LA3cGw4M5wULgiXRsn2xARahGhaKj3wDHu8+yksVdOzCEWt+/5c7T7Oe5BxXQiAACBOxOeB7ElokiUC9YyfqRJQOwdU3TsvW3yZUhMKdbctyHiVf+5Wo+7/wnllgS7B6hm+tE8r+PVOlSwjz7U5e0w1kZ9trKAJ1thjqshOQYRV6VYtvsxJJBVt6pj06COVoiA911YZpy2QNia2e6DDE0fjJLaEe4RhZyJQ38Zi/cZyflI2OCI9KTvCvJiNZrZEhdjk3JjLyfsrd9reI2HzwezQXFnj7VIjfZ6d66rtnQQ2cDkhA1Wq6y1z/SVuKZrN/J5mx3Svlel1qcbXJSDl3lWf44c7R1KnzjuuJaeO+PEmIpLIT7fJ9Q0h0FWTqWDXWIrysL/PetP1K2ZUuccnaeJBZ3OKXGuTmQEbhKpaIinEanMoIPNU7Vc/K1zvrXZEPOFOtz3HuENrPuTD5vN77JpsSsL3pVdAmYabEfZXGrlR5REvTt0w35097dgri30Qu48LCg05APsWT9CxlgwRGFfsoyl0iJ6oFeHhjPauJ4Yv
*/