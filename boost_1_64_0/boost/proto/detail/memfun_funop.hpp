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
C8e9aiaxZ62D1F1m4lQM8qFMTd4aTsWo+gvIl8rjcC+92hOCC6+61e84hsmUxfObkhrLic94jInEJhq6drmMlJ75BBfgNE0R+obPy5xs9zaFVZ1mul2KzuFY9lmu9KenPheBYGLFv6JuIAWtXzynXPUtzEVQ8aTlNEgOL9G5a8qt8wG05wQwJJyNDeRA760axuDkq4zwebLokHlZ+6sByHDEulAe1PsFt6xdJuGzMvdCgQNBFo2a7BDy60VTPC5riB+oXdveB3pOKztDAWYTAcjYqUVwQ4iYCt4CtipAMEyV3lE3vzriS+RcpPl7XGu2aT02hxeUaxOJkmb5LyfCB4IxwtBY2A4gr64EiClZ0+KCdrhBb/aRC6wk+xzzExQAdtMeOh7do3vEp3EVGTp/QRHDYYisSk8TozA+TLm7deuH/amGe7W3EQdE7fsPFgPWT4ZqJiOMTrSpkQC/nhNNAhDa3irAr1tQNbFRkRy90szPlvHLkQZN2jFxnXyBjjkKrlkK4ktg46xZrihK7eVQ3a5QXfj3KAWD399Cianokv3aU/qs1qSzMWUqdQ==
*/