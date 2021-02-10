#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
        BOOST_PROTO_EXTENDS_FUNCTION_()
        BOOST_PROTO_DEFINE_FUN_OP_VARIADIC_IMPL_(BOOST_PROTO_CONST)
    #else
        #include <boost/proto/detail/preprocessed/extends_funop_const.hpp>
    #endif

#else

    #define BOOST_PP_LOCAL_MACRO(N)                                                                 \
        BOOST_PROTO_DEFINE_FUN_OP_CONST(1, N, ~)                                                    \
        /**/

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/extends_funop_const.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file extends_funop_const.hpp
    /// Definitions for extends\<\>::operator()
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    BOOST_PROTO_EXTENDS_FUNCTION_()

    #define BOOST_PP_LOCAL_LIMITS                                                                   \
        (0, BOOST_PP_DEC(BOOST_PROTO_MAX_FUNCTION_CALL_ARITY))
    #include BOOST_PP_LOCAL_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

#endif

/* extends_funop_const.hpp
AAAKAAAACAAtZ0pS4qVnYn0EAACZCwAAHgAJAAAAAAABAAAAAAAeJDsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjY3VVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtrGIO6bAQAAIwMAAB4ACQAAAAAAAQAAAAAA4Cg7AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDI2OFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJPxcP5mQEAAKsCAAAeAAkAAAAAAAEAAAAAAMAqOwBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QyNjlVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSeYUV/IsBAABVAwAAHQAJAAAAAAABAAAAAACeLDsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjdVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSPzFW11gBAAA4AgAAHgAJAAAAAAABAAAAAABtLjsAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjcwVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUtd0anwbAQAA2gEAAB4ACQAAAAAAAQAAAAAACjA7AGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVz
*/