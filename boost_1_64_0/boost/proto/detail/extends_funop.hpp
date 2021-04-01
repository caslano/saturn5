#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        BOOST_PROTO_EXTENDS_FUNCTION_()
        BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PP_EMPTY)
        BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PROTO_CONST)
    #else
        #include <boost/proto/detail/preprocessed/extends_funop.hpp>
    #endif

#else

    #define BOOST_PP_LOCAL_MACRO(N)                                                                 \
        BOOST_PROTO_DEFINE_FUN_OP(1, N, ~)                                                          \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES) && !defined(BOOST_PROTO_NO_WAVE_OUTPUT)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/extends_funop.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file extends_funop.hpp
    /// Definitions for extends\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES) && !defined(BOOST_PROTO_NO_WAVE_OUTPUT)
        #pragma wave option(preserve: 1)
    #endif

    BOOST_PROTO_EXTENDS_FUNCTION_()

    #define BOOST_PP_LOCAL_LIMITS                                                                   \
        (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES) && !defined(BOOST_PROTO_NO_WAVE_OUTPUT)
        #pragma wave option(output: null)
    #endif

#endif

/* extends_funop.hpp
75pHE6R+ghf1g0kPwUEDUd2E1UZ1qBAsBY2zbTLOACM0ELXL6FGizzgSqUCp9tXtq3UCm0Url/Nlbf0lCvFduR4J51NPpMgrV/5yjWW5EwIImoh3AsDS9+05Yh9+97CZ+iYvnXtqzlIFgizBBzzrZxbFOHjVeKJDb7DUoqnQUCAd9bZqvNmuZjv12+c/OC7/3TQA3UynyCM6VR3CfnuhBpg2i/qHLtnDLQijP+pD+IhgmQLqwhYK0Tc744f6XzRuedUX4OxzaVcpduWHK22YY96iBkoUK8zsI4zlPQ+gMOgBHfujsaXqe6qixpvufW4qi1BADZh1VuzpKuOMjXS+jCjlh+6YoxJWnBgG3uF4RvZiyB+1K+cKSXa6ru6OgTFQd+d6f39aMtZwwTAzOrw7BsTDoCrP07UBkI2kA0susSDGhYE75g0AM9wRYB5NlgSD76UrIMfut0Ke1vKu4upuMCeZ0ByusWfK+yOwWqJDqKZoTczO2GDiwXkmZn6lD1sHtMGnWBSX24bwSh0w88OLpSI7c3d4Z9to6/9Ex3nGtyms0788C0oRGlYsqg==
*/