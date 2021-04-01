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
c7TEOopvNRUutU+6ui7yQKmnNMx6BDDwOAJG+9uKMxWIZaoYZFo0C5YH+btkdKziJFIQfrOuF0+DvH8Mw9dTr2zPybhw9zegiuT9RfSWFk913LSQbELCCDPKSHRTGbutwo/Gf6pmvZfrSYEzmoNfhonWdCRSY8yKOJ0Npf8VUY+URytzl8DVf5RzmfW9frbACV9cLd+VRGyiKi1WzVRDJhWnDff1zKqQyr/9zTIAWuIQH31DhOG9OoCtMtsJDW9ayoKpqUAEgzeLZbW9F0IwRv/MBkOfpRrxYQm5Sgw0/EWYaG0GOVEE+rb6h+03oxv5wm3zG3JtFHV3VtDHshpcA95aqQ4UeiVIY7h+g/wxC5ffF5OTE1E7Rzru7aAEO6yutFddeYuCTM3VKKYuCTxRHC78mM/Cy+wDj/D71hS35SUrTd+1g+4RRnpRbi7tAloXkikfP1onYibZGM2+xI+tRjmksYcXquRa+hpJ7leiU7rT7nBhkw1EfvrCsX8xXZbFz2ShxO/d+oE6Eh4VwbHwooOLx99jfHnt9Miof7UYzm6NVWvGnJnB2FVVKw==
*/