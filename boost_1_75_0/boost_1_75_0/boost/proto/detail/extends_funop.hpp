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
X4PXwXi6trwiKErh4/ufhb1jijlTAzNt0Vno9Iha4qTLmdGRLmln3ya0N1Q2YM/bcT/e971v2E8zj+/jQrn+y8qG+R+qRhn8zHdlf3l2GrbrwUpezQlpfPo8rfa5X1An5+TW1abe1oG1dcyiOhHrUw6+dyyLGoIehfPPgZtrp5VVS44Ly0/fTfgWDpniLbjBaXSnYcvvQfM8gzAv6ERy2A499BvxtSCbwCKrAnDP6n1LWcgopDqPiQ1J/OwJoTuVPdXyqnBxWWK3xvFoMkTf14zXwSZi8vvNUFczeLBl3bHlO+MwkJDj3H14WOOnGOndneOkuu3Fv7RjuIQ8SNZBPun1PHzoxlh/tf6X9dfrbyvf2KLY0vJjLL5y6fmpT25PqoRXSQ9siSAJWAsQ9BcMwOmR0seffv3D31Sfc1rMcWoFFYxjjtGM6oZC3sOjL3jVgKNMX4t2hFrpj1OL5k1yLWlF3xOWT7psMr+GBiY6Qrt/Be/xT+AxfvTa8Rv/C5Tz5e/7/LSDFgrleYkjRTB4s+e+CvPn0CdTCniOEQI+4r8C4aH1fMklthB9pPr8luxNsT/NK9AE5WsKVCCK0LcRn7SCKc68tx64sORNf94z1bPyIaJPpOnZatYoIPc+O83AgnQBYhU0RLUyohH9RS8FA9bUU5gfUvyw4RV3ghPTQeBiLTT/EcvipNdeBhOXUVpM4Q8+llWkV9yhOteC
*/