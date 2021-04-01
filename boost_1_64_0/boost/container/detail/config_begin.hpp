//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_CONFIG_INCLUDED
#define BOOST_CONTAINER_CONTAINER_DETAIL_CONFIG_INCLUDED
#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#endif   //BOOST_CONTAINER_CONTAINER_DETAIL_CONFIG_INCLUDED

#ifdef BOOST_MSVC
   #pragma warning (push)
   #pragma warning (disable : 4127) // conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4197) // top-level volatile in cast is ignored
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4267) // conversion from "X" to "Y", possible loss of data
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4290) // C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
   #pragma warning (disable : 4324) // structure was padded due to __declspec(align(
   #pragma warning (disable : 4345) // behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
   #pragma warning (disable : 4355) // "this" : used in base member initializer list
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4510) //  default constructor could not be generated
   #pragma warning (disable : 4511) // copy constructor could not be generated
   #pragma warning (disable : 4512) // assignment operator could not be generated
   #pragma warning (disable : 4514) // unreferenced inline removed
   #pragma warning (disable : 4521) // Disable "multiple copy constructors specified"
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4541) // 'typeid' used on polymorphic type '' with /GR-; unpredictable behavior may result
   #pragma warning (disable : 4584) //  X is already a base-class of Y
   #pragma warning (disable : 4610) //  struct can never be instantiated - user defined constructor required
   #pragma warning (disable : 4671) //  the copy constructor is inaccessible
   #pragma warning (disable : 4673) //  throwing '' the following types will not be considered at the catch site
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4702) // unreachable code
   #pragma warning (disable : 4706) // assignment within conditional expression
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4714) // "function": marked as __forceinline not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
 
#endif   //BOOST_MSVC

/* config_begin.hpp
l49QTnLvsTnouDah7URYKXo/be3kURBYrhNBUIF75k1DLRY2wGQes80ZaCSAMiQIeT6PuvbayIeXD3E0TDuaZFvN2cOEQooUEB3Dt6suza0MkwuiHfP+YTPnq+/6GF0DJY/CBCsHKbMjhB3qihlj/0RpHU08Dv8glx3hA83+i9mVDgOQIJxDDx1AwdH4NrXnvLzySHrXngKoaj1ixDvcF5k95iF8E90nyVmjLtq5zIZSnPNY7zp3qBnLu63TpM8fK6Sl+X6qGl0KCFL4VWXptdPmn8NCDDKQ3TX6uGlH6bDA6hCTqfRJnxgfkRGI7cfoJBR/o5fVlTwq8ZQBTAyQubNAJHrs/dcCQitMl4KHCCHJ91Icr5ego/J4JP1zhhl0YKh+knDYvrv8kTsZ6k0LToGPsCzh/XPUbOetzNQbqxeiRkBmS7dr0o0Yxd7MGMNHGZjTUGkjeGVKS/9nZ48bsHqSYcm2hMsbrFydMC6LZAdGCTfB4U0g4bMMvJ7IZEKpYpA/Q4awwapb1s9EDigLoyYuIk1Mcb6pxe3adcaNqvM3FD8ViKTETKP3nQ==
*/