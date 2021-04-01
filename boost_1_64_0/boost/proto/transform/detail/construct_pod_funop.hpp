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
EyqS4+lpVwjtqsLk+pxJI5J6Tu9qmywk+M4lwxvLsd4jrzCYWXxnlxs+I7F0YCmxVs9u7NtCbtzofYDrz5nh3sL+PYNedpVauJMBOdL8pygN7YdG7ol0hstapFlA+yHKIGhzSvSnXbwjs4R4m2VRoZCy0OzkwYMbPSGwT2Lm752NDTvqVtmrz/EFdMyJQhlGxhY78ZI6FHEyKMCsbd6w8inq9mM4VZy5EhlySQNI2yFW4ubglfEj1AmHpniZ7wwpovERWqp0VNJAhxlzLDHSc9kJO+sVsljlpT2+O+yuQfQ2mrDzVwPSkkb9FAXOjIFMqvV2g/OqxfMSU84udvB+xDlNI94C4G1YObioTrc50fqfUNcN5M2sUDQ2KFScl9Onx1DE4ILU3dj6NpCkGt+MlrIrrrNX14pihvW8YbsstSJwSsB2icq29wUO3pLM4xM9S35j2+FUYOW37IhbRcsIOIB5V0gW0QA/TMqIIcyad0Fh9NBTNke+egYJg9XMB/6Aq+FmvwCofBdNOWZh50exawB3z/EckDSkrD+M13A47npgzR2JrO9cGhuHnQ==
*/