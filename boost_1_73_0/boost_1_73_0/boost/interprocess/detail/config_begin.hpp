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
Y7IyuBhM3KMmHJDYkj5Ck6IIo5Ibf8849By6XxMzPU8LKOXS1nIesOPvYkKwgdTPSTq/W21oRES6r0IdfKRzGNbTUj6sI2tlqzWUQ6koxNJ0g7lEdQyqpJxZVxLD/2YRrHICGy4K/ag8T7JVRYEfLA9LcylpyEuQouxPWSWlUjYvtaSEjspbHJbkSh7A/5EQ6vz+0eI+2Bipgk0EgcixICSFwb8scW2SbMSrWrwHUxdMIcgVhH7IguGwmwyoOB4Br6X0dw0oEQWxA2tuX+oWnWRUz7cybaXZbGX1QlyYxinzPPSDYsvxWiz6PjZ+SfxRxdh+cCrvkNB9JR8z9nGWlAPRcTAP4vP7WEZrp1rBTe+qkJo/HlK1DSo/QGS8NmBt/mQSs7smunaDLtpY2XIlL8kKLBQ6x/QMmx2S2fOYrcFKtwYmfV95EnYt0dqPMvI2+nGthz4bw7D0OExxWp0n00d9L/ZhSYNEpNggabN6m2Y2abpCJ/SwtP2QC1jaELZp4y5ajeEZfkQHWpFyOVs/cQnIJZpVSiNSR+Mr/HLZCpZh1YPNl4U5zMklOXCUW9NTVnr6UPscux774nXqp7aq7GV3suxDc3O6JKUKHkOFiJS/w5spbxA9ANmiE3dSXhN+bWcT3SzJ69ukAJkp
*/