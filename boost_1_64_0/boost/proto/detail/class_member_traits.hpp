#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/class_member_traits.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/class_member_traits.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    // class_member_traits.hpp
    // Contains specializations of the class_member_traits\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (0, BOOST_PROTO_MAX_ARITY, <boost/proto/detail/class_member_traits.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#else

    #define N BOOST_PP_ITERATION()

    template<typename T, typename U BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct class_member_traits<T (U::*)(BOOST_PP_ENUM_PARAMS(N, A))>
    {
        typedef U class_type;
        typedef T result_type;
    };

    template<typename T, typename U BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
    struct class_member_traits<T (U::*)(BOOST_PP_ENUM_PARAMS(N, A)) const>
    {
        typedef U class_type;
        typedef T result_type;
    };

    #undef N

#endif // BOOST_PROTO_DONT_USE_PREPROCESSED_FILES

/* class_member_traits.hpp
NO4XfZq2WbgdPRkj9wc0M4Sz+E3sdwo3ZMXtM5Kj6cAqkfdjUvWB/kB4KmzKGZiwnjl/JLbYZomsA8OHnf3YNyvrET5nhCMm3NpytAICkAhZQW21W5HugRYh/aq4a2Sz9L+6D2z9doKsuKBkVrs/gUFytWISy1QjLBihqyQRO9/cQcFTE1cbHduMoI+2JmW7PRNzQZdpr9y+q1NEsZVarCJgGDN+xXsy+KNx+BoN9d8RXa2+ZJgXLVTYYa4rbKcnhL1k/ffrCfo8pKu4PLhMksIlImbVAdieubOw+vT2TeeRkU07z1YfW8dyLrqh0wjD3O+LUeXNl+tMb7FwYDvXMIB6FLR/YyEk1fkvzqT7HFNBKT+Zr1Y9Nw985eNty7y9Hp+l1vuhqBT/mwGGMq4oEZpHvhFcGzxUdc9MUkVoLeuA5OD/zmAt3DgsXPf/lK/m64QG1snkeUqqBwy2pnHq6Fu30LvfoFyX1Bx4a00KKGDcM1oxzIx892oJ+x3bjW27L8VuYiCJI3C5Dgk4+nhDDK4tA1EIe6aOePhv3rVAXoJTC/rlxDfNJrWSSw==
*/