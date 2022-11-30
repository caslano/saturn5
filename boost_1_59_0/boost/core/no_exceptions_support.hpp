#ifndef BOOST_CORE_NO_EXCEPTIONS_SUPPORT_HPP
#define BOOST_CORE_NO_EXCEPTIONS_SUPPORT_HPP

#if defined(_MSC_VER)
#  pragma once
#endif

//----------------------------------------------------------------------
// (C) Copyright 2004 Pavel Vozenilek.
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
// This file contains helper macros used when exception support may be
// disabled (as indicated by macro BOOST_NO_EXCEPTIONS).
//
// Before picking up these macros you may consider using RAII techniques
// to deal with exceptions - their syntax can be always the same with 
// or without exception support enabled.
//----------------------------------------------------------------------

#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if !(defined BOOST_NO_EXCEPTIONS)
#    define BOOST_TRY { try
#    define BOOST_CATCH(x) catch(x)
#    define BOOST_RETHROW throw;
#    define BOOST_CATCH_END }
#else
#    if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x564))
#        define BOOST_TRY { if ("")
#        define BOOST_CATCH(x) else if (!"")
#    elif !defined(BOOST_MSVC) || BOOST_MSVC >= 1900
#        define BOOST_TRY { if (true)
#        define BOOST_CATCH(x) else if (false)
#    else
         // warning C4127: conditional expression is constant
#        define BOOST_TRY { \
             __pragma(warning(push)) \
             __pragma(warning(disable: 4127)) \
             if (true) \
             __pragma(warning(pop))
#        define BOOST_CATCH(x) else \
             __pragma(warning(push)) \
             __pragma(warning(disable: 4127)) \
             if (false) \
             __pragma(warning(pop))
#    endif
#    define BOOST_RETHROW
#    define BOOST_CATCH_END }
#endif


#endif 

/* no_exceptions_support.hpp
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
*/