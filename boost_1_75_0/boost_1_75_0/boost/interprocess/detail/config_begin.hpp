//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_CONFIG_INCLUDED
#define BOOST_INTERPROCESS_CONFIG_INCLUDED
#include <boost/config.hpp>
#endif

#ifdef BOOST_MSVC
   #pragma warning (push)
   #pragma warning (disable : 4702) // unreachable code
   #pragma warning (disable : 4706) // assignment within conditional expression
   #pragma warning (disable : 4127) // conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4267) // conversion from "X" to "Y", possible loss of data
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4355) // "this" : used in base member initializer list
   #pragma warning (disable : 4345) // behavior change: an object of POD type constructed with an initializer of the form () will  be default-initialized
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4511) // copy constructor could not be generated
   #pragma warning (disable : 4512) // assignment operator could not be generated
   #pragma warning (disable : 4514) // unreferenced inline removed
   #pragma warning (disable : 4521) // Disable "multiple copy constructors specified"
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
   #pragma warning (disable : 4197) // top-level volatile in cast is ignored
   #pragma warning (disable : 4541) // 'typeid' used on polymorphic type 'boost::exception'
                                    //    with /GR-; unpredictable behavior may result
   #pragma warning (disable : 4673) //  throwing '' the following types will not be considered at the catch site
   #pragma warning (disable : 4671) //  the copy constructor is inaccessible
   #pragma warning (disable : 4250) //  inherits 'x' via dominance
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

/* config_begin.hpp
Q31GxdIe+i9/NXotcWLZ/i5A9dxdeS/GBTWRHoq6f5PyTKP+TAPbpdMIWrfdBwR+hTP9w/hW2h/eyH+sdxylv/kAcgBfXxCyASdV/2V8G2s/b4qwIOmbDf2DDEqM0zIPvCpqc5eXGgPa7cg+sD7whF4fn+LQB5meF5euWASZFTR/7jDSr+Fc0LKz/012Klxt5u5yjziKvMS8KL57DzVJWxVczb9LCeX89L2myUZpVUovVCuK5ITurKw5bUit87kwSxYgbnr2uXz3ludMWxw0fkFE5wL6c/cDqnPjcmPuJEsIecvR61j9OQ4LBfQV5b9jQkEPexHPve4lvu5zVlMHJXX+iPVBGIUICFWXtteCm4xyW9KfANoFAYYvJMZVMZ7gnVtQ9/bHlrhd7ru8Nf712zB272c++LMl0DIIdB2MjDtgtb49IyL6+8qGtS7e8qqWqGOJf18UsYOkGIKp10x5wN3JCfhzURnQltbNvxFqXtFwMEoc/0KURAsismqEECRE7yQiRAui97oh2uqdjZ6o0TvRid67DaKX1ftqqy92WWVZu+53n+7jfZhz5sx/5sycM0+/c/7pPWIGt1gufODYKhNGLGEV+eIuI66T/MMhtqWTCeP+Jfo13l8adlLjxOoFcpSUarge3NV0XgeL/EO1M2E//RNxi4VQLgjemRP8F+OjB4/D3P+v8/vpv6HnrgB0cQT58ru4geyB1h7u
*/