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
zI15tnr6UrziBmSSJM2YWx/Km+gsCp7NnSm0Bzda3sKaCliYNOWS/gDmvz33qRj6kF/AGOck0VokrCGmEB7p2zSiLxls2r0qF7KoKnJEJyYddPSHmOwH8vLmT3JZR5jrcqdzIAL2u2IkId1ySeFvaQoHwt/q+Au+66qSj3Q3WgAx1QjvrwVlhw7fGBxiDfT+ULSC1Uduu54qJA++ZM/wbWZ4V6qwri72HiMR3f6LJs+4N40LvibFOW3GXzk7q5g4oCwM4118W6x4cXd32uLaUtyLa3EZHFqkxYo7g7sMUtzdB5fBdXAdbGCYtWRfNptNNrk3N/c+3Zy375z8/992+E4+tLDHPiSeY7C13vRh7NNGF9U71lUlLk8e5/xXR3x+YWjzyq9YP6B7/njj+WsqSWFXUBl/Xq26MYMmT/HIzaE0EMYYzqYReSSKPyPWJkvGpixFE2wmprdb5SPl7GX7vMFRTLG0kUsMJtvKcG5xh0uuFzUfccHRymg+F9lvr2V7ffYIcAEt+WqeP3W2NkluEh7KXJQWjyrqgADEd9Jny3Ack2JHGLnfa2KrsBYyXemgOlq+OONtBUmzfTm95IMdj3AA5m04ZTjg9MUIs3V4oTVMYHEjm790L8X4IuDrhk/ShcqmF9MFi1CljUAD4eSiRdfCWy+SIW5bf4bcdlcG/8KQFrTHx7618NZTKvgGsfDe0s7D94awMQTJzBZp
*/