//  boost/config/user.hpp  ---------------------------------------------------//

//  (C) Copyright John Maddock 2001. 
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Do not check in modified versions of this file,
//  This file may be customized by the end user, but not by boost.

//
//  Use this file to define a site and compiler specific
//  configuration policy:
//

// define this to locate a compiler config file:
// #define BOOST_COMPILER_CONFIG <myheader>

// define this to locate a stdlib config file:
// #define BOOST_STDLIB_CONFIG   <myheader>

// define this to locate a platform config file:
// #define BOOST_PLATFORM_CONFIG <myheader>

// define this to disable compiler config,
// use if your compiler config has nothing to set:
// #define BOOST_NO_COMPILER_CONFIG

// define this to disable stdlib config,
// use if your stdlib config has nothing to set:
// #define BOOST_NO_STDLIB_CONFIG

// define this to disable platform config,
// use if your platform config has nothing to set:
// #define BOOST_NO_PLATFORM_CONFIG

// define this to disable all config options,
// excluding the user config.  Use if your
// setup is fully ISO compliant, and has no
// useful extensions, or for autoconf generated
// setups:
// #define BOOST_NO_CONFIG

// define this to make the config "optimistic"
// about unknown compiler versions.  Normally
// unknown compiler versions are assumed to have
// all the defects of the last known version, however
// setting this flag, causes the config to assume
// that unknown compiler versions are fully conformant
// with the standard:
// #define BOOST_STRICT_CONFIG

// define this to cause the config to halt compilation
// with an #error if it encounters anything unknown --
// either an unknown compiler version or an unknown
// compiler/platform/library:
// #define BOOST_ASSERT_CONFIG


// define if you want to disable threading support, even
// when available:
// #define BOOST_DISABLE_THREADS

// define when you want to disable Win32 specific features
// even when available:
// #define BOOST_DISABLE_WIN32

// BOOST_DISABLE_ABI_HEADERS: Stops boost headers from including any 
// prefix/suffix headers that normally control things like struct 
// packing and alignment. 
// #define BOOST_DISABLE_ABI_HEADERS

// BOOST_ABI_PREFIX: A prefix header to include in place of whatever
// boost.config would normally select, any replacement should set up 
// struct packing and alignment options as required. 
// #define BOOST_ABI_PREFIX my-header-name

// BOOST_ABI_SUFFIX: A suffix header to include in place of whatever 
// boost.config would normally select, any replacement should undo 
// the effects of the prefix header. 
// #define BOOST_ABI_SUFFIX my-header-name

// BOOST_ALL_DYN_LINK: Forces all libraries that have separate source, 
// to be linked as dll's rather than static libraries on Microsoft Windows 
// (this macro is used to turn on __declspec(dllimport) modifiers, so that 
// the compiler knows which symbols to look for in a dll rather than in a 
// static library).  Note that there may be some libraries that can only 
// be linked in one way (statically or dynamically), in these cases this 
// macro has no effect.
// #define BOOST_ALL_DYN_LINK
 
// BOOST_WHATEVER_DYN_LINK: Forces library "whatever" to be linked as a dll 
// rather than a static library on Microsoft Windows: replace the WHATEVER 
// part of the macro name with the name of the library that you want to 
// dynamically link to, for example use BOOST_DATE_TIME_DYN_LINK or 
// BOOST_REGEX_DYN_LINK etc (this macro is used to turn on __declspec(dllimport) 
// modifiers, so that the compiler knows which symbols to look for in a dll 
// rather than in a static library).  
// Note that there may be some libraries that can only 
// be linked in one way (statically or dynamically), 
// in these cases this macro is unsupported.
// #define BOOST_WHATEVER_DYN_LINK
 
// BOOST_ALL_NO_LIB: Tells the config system not to automatically select 
// which libraries to link against.  
// Normally if a compiler supports #pragma lib, then the correct library 
// build variant will be automatically selected and linked against, 
// simply by the act of including one of that library's headers.  
// This macro turns that feature off.
// #define BOOST_ALL_NO_LIB
 
// BOOST_WHATEVER_NO_LIB: Tells the config system not to automatically 
// select which library to link against for library "whatever", 
// replace WHATEVER in the macro name with the name of the library; 
// for example BOOST_DATE_TIME_NO_LIB or BOOST_REGEX_NO_LIB.  
// Normally if a compiler supports #pragma lib, then the correct library 
// build variant will be automatically selected and linked against, simply 
// by the act of including one of that library's headers.  This macro turns 
// that feature off.
// #define BOOST_WHATEVER_NO_LIB
 
// BOOST_LIB_BUILDID: Set to the same value as the value passed to Boost.Build's
// --buildid command line option.  For example if you built using:
//
// bjam address-model=64 --buildid=amd64
//
// then compile your code with:
//
// -DBOOST_LIB_BUILDID = amd64
//
// to ensure the correct libraries are selected at link time.
// #define BOOST_LIB_BUILDID amd64


/* user.hpp
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
*/