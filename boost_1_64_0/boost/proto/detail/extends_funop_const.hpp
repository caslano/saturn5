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
skT54Eg0iz80DnSOV00ok8NmWlvNa+ugBZFHJnT1APm+hZB85qgygTTCX48nwbKfPBZvVmxc5eLGHHI4lqh0NfNDqfUHRZQIM6Yd3FWU+i+TJZ6o6sPiA1RJS7yrdTQoCcxoegHK4rbA04zv3pPQv5I6i++EiByXB2GQUcECl0Ontxc4BNIUG7ryf79mtQMnqyjBxpL1oKUqSwavbncN64mLtHnRTZ+weSPIseMna02XzHYPTYer8c3iofOA+tSl8FMum5ooDsqtmRA4s64ou5Yedu03MscfIm98mDOa9QBAUBJtPK6kS5aTs1Hsw7TET4+34Ak/XkYnJbDDH/GLHYb0FYxaD7hn6/Ao+kYl5RCpKj24d1SXdZ//kUhmS61c4M/UngfkzBkfo5joDrSraLp48PTHJMEUTgmxGig7zSjtTEvFyOPll5MeE3aZJxzcWX3PP8JKvL6vGeMGOpcgo++0zKlq5UHuF7zDce1GHuj+gfSd3dZ8h4crGg15GXfJGrXLAC/HiAvFLT5lLkkS99b5fVZZsz90VVl+Z469DmVi2vrR7VhvHQRiOw==
*/