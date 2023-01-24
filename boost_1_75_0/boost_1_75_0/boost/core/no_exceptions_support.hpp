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
#    if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
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
Ql1oTd+URtPS/sP0JLd++mgdq5OdxG6vUbvkVdZnJfkmw1lGODadtD9Mgu1mbcW4OIr9TrJBSspHnQrdVcRrQ45+DDorfawxMXEtaP2JvZH815gLQW4xMSF2fgaf38orEZK9awQegOjdJKIsckrdVarkVQo04xfvkB8SXsEauh/eMKksO+ljeySQWhQD6jCNr5ybfysaOAYf5g6RJUWAwNmFvSkPGX6aq/gCpdwssYko8jW/dwnJdhx2g5KLHfylrSHHr6AYvg7CVRJ/tutmDG1gm2Jl9zcdsgQfWT91RTezw8UqTpdyswNQbA7r/YIWP+ZrX58UeIBrioEM9f3R7zX72OOD8Csea4mGyOZ+hjbCi7+AsgafRVj7SZmHX/S8yKm5ijAXTXn9hUMiUi5dxSu+aWAO//ztJCNOirl84J3mk2QmWPuriBV68/iATmEqqqkuKsjCd61Dl4VSomxWaR1CCRGCFeMbRGFPxoGHcjdlka3/MM2RKsCgnI+e/1lkJ11EB3wWenJh7xgBoI04NurMbJIelSgMGqEasaATJpuFK8MVBZdQclw3/RgNN7+MvlcPgxLz0OiPL531Rec1QnfGsD3+f5r3cL+D0vslQ3+tXGm4husUpQweaSAqxRxjcsspZyNrVGmPUGxzETdq6naZ9xZM+uBGCnMs0kHNqyACUR7OYXrcISuTOYEhqeMjJiKcf1cA+dIgP3vk
*/