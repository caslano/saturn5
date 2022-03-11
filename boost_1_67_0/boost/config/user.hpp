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