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
sKk6nMLGc3kPu+A+YsQfdBW2rrv6wx0VJYGx9+KeLtBVXVVKHMVmtUs77eIheHAmOJ7wcqS4PeZ3Bx6qbqTdbDj9KrEir/eQgRojRX3nWGiu+YY9NVdhqLdcZ6bqQmCe+0A12XWwT0TpxB6lurcULz4OLi7zz3eJXkKIulqzb8fKQVRW2+Fq9l9To93WcPzGKadVpA2VyG+iPDGE9Lj1ccLEUMC6OAowoTnD8emN3ulGRQdPqY+Tn9Qo940Ip18vlYcG4p1TUpy5PuC2YwAQuV7vdAWNVzrrRnA83V/3Q3DiQt1H0Ezhz0PWJdlWpZTm4wXjURzaZ2XL3cs/nL/cByPqEaTw2QgAjLTu2RDDyKiOTQjvlD3b+2yfKuFeFX4Kayt1OXxRlc729qErBeeDZqeO7aj96n8pSkvfjnFCco68TpiF4PMXZspBiE6EVbIvreXEYjOreQa6jbzVWJQ0+PqMl2oqPq1CsS77x1taaBQggXmJ54bT7iSV5KQqpvPwUQSGV2ZkMNEfM/6p/rJXXwYnhN/s818P3prjUxgwf2LuoN/nqJT+5r+Tq0mib1/wx9bGyqnZta1Kt4rHTV5eO6nDp8IlqmNkdb+Wu4mfx00rnYU0g2/FOyCX2obKhiuzHIQTy6zH5liFvrL0Mz2dJd7s7hEe+cbq9+U3kimCyeH7+R8/WcmlRgf2N3Pz+WNL85yr8eFX/FysuUU3
*/