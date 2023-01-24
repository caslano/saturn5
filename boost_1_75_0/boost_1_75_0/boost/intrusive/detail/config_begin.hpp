/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_MSVC

   #pragma warning (push)
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4996) // "function": was declared deprecated
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4521) ////Disable "multiple copy constructors specified"
   #pragma warning (disable : 4127) //conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4267) //conversion from 'X' to 'Y', possible loss of data
   #pragma warning (disable : 4541) //'typeid' used on polymorphic type 'boost::exception' with /GR-
   #pragma warning (disable : 4512) //'typeid' used on polymorphic type 'boost::exception' with /GR-
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4706) //assignment within conditional expression
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4714) // "function": marked as __forceinline not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
#endif

//#define BOOST_INTRUSIVE_USE_ITERATOR_FACADE
//#define BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE

/* config_begin.hpp
GoZShzpJf9Lh0qdYeunIDeK8z1sCGq4Ws3g1s+nntWxsG/428g5pktKPZ+mRZizADsWHRO5OO/ah25wOuNiTns2+9IbHq0bnc1krn2tWGTGE+jup+SqvoYxiPQLUbeerzc8mv/nACBcfN+y5IB5szlefuIhgLGHMVONs/nzYc3eQe1F4pgJROlVdYuDxy+QYewr+GOIoafWDzsCUbYlku6m0+KxzxVuCsrABgP7TvlfTpre1D1jNrve52gaeG1vZc80sUYDFW0cKL5EcgOFI46DuHmpr3Z6x+K3lVm+ASdMbEPY4RP0Z6mxYtXdB1CW2e+mY7iiG95YlFtBO/gxauPmRWfME/tEL/SorQvlcY728m738mv+qYtDEFwAYgFgY4b1hhLxJS90Yg1vAEMvHd8ZugbrZAr7lrST4LOy3Awhg8P40roafuUVmw3hSHoPBGvKGhvm6u3IDroLgW78tcRt5LvHafqnfgBkHswK4b1FWWDPIzcehhcpQbAgU7W+5PBz1dUrkf4Lk/2F6zvrPVfV/d7SjOREOuwf4Ug2SqrFTzyTanYIVV5J/ROPAjFPcq+xGhP94Z4VXGvyp+SJJNFovSuTL+2eBpoAJdvFkDF+54M8kt5igtd+rimaKp/OjP1aHkqZalErOG45VMovkbGk1X9KKfucsRxIOHj16YJDJ/mQdLeKQo3093Dg/79x4rHfcWtPfRgHUn6Rs
*/