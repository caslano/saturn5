/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2002-2003 Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_DEBUG_MAIN_HPP)
#define BOOST_SPIRIT_DEBUG_MAIN_HPP

///////////////////////////////////////////////////////////////////////////
#if defined(BOOST_SPIRIT_DEBUG)

#include <boost/spirit/home/classic/version.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  Spirit.Debug includes and defines
//
///////////////////////////////////////////////////////////////////////////////

    #include <iostream>

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The BOOST_SPIRIT_DEBUG_OUT defines the stream object, which should be used
    //  for debug diagnostics. This defaults to std::cout.
    //
    ///////////////////////////////////////////////////////////////////////////
    #if !defined(BOOST_SPIRIT_DEBUG_OUT)
    #define BOOST_SPIRIT_DEBUG_OUT std::cout
    #endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  The BOOST_SPIRIT_DEBUG_PRINT_SOME constant defines the number of characters
    //  from the stream to be printed for diagnosis. This defaults to the first
    //  20 characters.
    //
    ///////////////////////////////////////////////////////////////////////////
    #if !defined(BOOST_SPIRIT_DEBUG_PRINT_SOME)
    #define BOOST_SPIRIT_DEBUG_PRINT_SOME 20
    #endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Additional BOOST_SPIRIT_DEBUG_FLAGS control the level of diagnostics printed
    //  Basic constants are defined in debug/minimal.hpp.
    //
    ///////////////////////////////////////////////////////////////////////////
    #define BOOST_SPIRIT_DEBUG_FLAGS_NODES        0x0001  // node diagnostics
    #define BOOST_SPIRIT_DEBUG_FLAGS_ESCAPE_CHAR  0x0002  // escape_char_parse diagnostics
    #define BOOST_SPIRIT_DEBUG_FLAGS_TREES        0x0004  // parse tree/ast diagnostics
    #define BOOST_SPIRIT_DEBUG_FLAGS_CLOSURES     0x0008  // closure diagnostics
    #define BOOST_SPIRIT_DEBUG_FLAGS_SLEX         0x8000  // slex diagnostics

    #define BOOST_SPIRIT_DEBUG_FLAGS_MAX          0xFFFF  // print maximal diagnostics

    #if !defined(BOOST_SPIRIT_DEBUG_FLAGS)
    #define BOOST_SPIRIT_DEBUG_FLAGS BOOST_SPIRIT_DEBUG_FLAGS_MAX
    #endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  By default all nodes are traced (even those, not registered with
    //  BOOST_SPIRIT_DEBUG_RULE et.al. - see below). The following constant may be
    //  used to redefine this default.
    //
    ///////////////////////////////////////////////////////////////////////////
    #if !defined(BOOST_SPIRIT_DEBUG_TRACENODE)
    #define BOOST_SPIRIT_DEBUG_TRACENODE          (true)
    #endif // !defined(BOOST_SPIRIT_DEBUG_TRACENODE)

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Helper macros for giving rules and subrules a name accessible through
    //  parser_name() functions (see parser_names.hpp).
    //
    //  Additionally, the macros BOOST_SPIRIT_DEBUG_RULE, SPIRIT_DEBUG_NODE and
    //  BOOST_SPIRIT_DEBUG_GRAMMAR enable/disable the tracing of the 
    //  correspondingnode accordingly to the PP constant 
    //  BOOST_SPIRIT_DEBUG_TRACENODE.
    //
    //  The macros BOOST_SPIRIT_DEBUG_TRACE_RULE, BOOST_SPIRIT_DEBUG_TRACE_NODE 
    //  and BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR allow to specify a flag to define, 
    //  whether the corresponding node is to be traced or not.
    //
    ///////////////////////////////////////////////////////////////////////////
    #if !defined(BOOST_SPIRIT_DEBUG_RULE)
    #define BOOST_SPIRIT_DEBUG_RULE(r)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, #r, BOOST_SPIRIT_DEBUG_TRACENODE)
    #endif // !defined(BOOST_SPIRIT_DEBUG_RULE)

    #if !defined(BOOST_SPIRIT_DEBUG_NODE)
    #define BOOST_SPIRIT_DEBUG_NODE(r)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, #r, BOOST_SPIRIT_DEBUG_TRACENODE)
    #endif // !defined(BOOST_SPIRIT_DEBUG_NODE)

    #if !defined(BOOST_SPIRIT_DEBUG_GRAMMAR)
    #define BOOST_SPIRIT_DEBUG_GRAMMAR(r)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, #r, BOOST_SPIRIT_DEBUG_TRACENODE)
    #endif // !defined(BOOST_SPIRIT_DEBUG_GRAMMAR)

    #if !defined(BOOST_SPIRIT_DEBUG_TRACE_RULE)
    #define BOOST_SPIRIT_DEBUG_TRACE_RULE(r, t)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, #r, (t))
    #endif // !defined(BOOST_SPIRIT_TRACE_RULE)

    #if !defined(BOOST_SPIRIT_DEBUG_TRACE_NODE)
    #define BOOST_SPIRIT_DEBUG_TRACE_NODE(r, t)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, #r, (t))
    #endif // !defined(BOOST_SPIRIT_DEBUG_TRACE_NODE)

    #if !defined(BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR)
    #define BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR(r, t)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, #r, (t))
    #endif // !defined(BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR)

    #if !defined(BOOST_SPIRIT_DEBUG_TRACE_RULE_NAME)
    #define BOOST_SPIRIT_DEBUG_TRACE_RULE_NAME(r, n, t)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, (n), (t))
    #endif // !defined(BOOST_SPIRIT_DEBUG_TRACE_RULE_NAME)

    #if !defined(BOOST_SPIRIT_DEBUG_TRACE_NODE_NAME)
    #define BOOST_SPIRIT_DEBUG_TRACE_NODE_NAME(r, n, t)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, (n), (t))
    #endif // !defined(BOOST_SPIRIT_DEBUG_TRACE_NODE_NAME)

    #if !defined(BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME)
    #define BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME(r, n, t)    \
        ::BOOST_SPIRIT_CLASSIC_NS::impl::get_node_registry(). \
            register_node(&r, (n), (t))
    #endif // !defined(BOOST_SPIRIT_DEBUG_TRACE_GRAMMAR_NAME)

    //////////////////////////////////
    #include <boost/spirit/home/classic/debug/debug_node.hpp>

#else
    //////////////////////////////////
    #include <boost/spirit/home/classic/debug/minimal.hpp>

#endif // BOOST_SPIRIT_DEBUG

#endif


/* debug.hpp
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
*/