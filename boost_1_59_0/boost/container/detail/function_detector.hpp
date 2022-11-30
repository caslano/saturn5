/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2009-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
/////////////////////////////////////////////////////////////////////////////
//  This code was modified from the code posted by Alexandre Courpron in his
//  article "Interface Detection" in The Code Project:
//  http://www.codeproject.com/KB/architecture/Detector.aspx
///////////////////////////////////////////////////////////////////////////////
// Copyright 2007 Alexandre Courpron
//
// Permission to use, copy, modify, redistribute and sell this software,
// provided that this copyright notice appears on all copies of the software.
///////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_FUNCTION_DETECTOR_HPP
#define BOOST_CONTAINER_DETAIL_FUNCTION_DETECTOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>

namespace boost {
namespace container {
namespace function_detector {

    typedef char NotFoundType;
    struct StaticFunctionType { NotFoundType x [2]; };
    struct NonStaticFunctionType { NotFoundType x [3]; };

    enum
         { NotFound          = 0,
           StaticFunction    = sizeof( StaticFunctionType )    - sizeof( NotFoundType ),
           NonStaticFunction = sizeof( NonStaticFunctionType ) - sizeof( NotFoundType )
         };

}  //namespace boost {
}  //namespace container {
}  //namespace function_detector {

#define BOOST_CONTAINER_CREATE_FUNCTION_DETECTOR(Identifier, InstantiationKey) \
   namespace boost { \
   namespace container { \
   namespace function_detector { \
   template < class T, \
            class NonStaticType, \
            class NonStaticConstType, \
            class StaticType > \
   class DetectMember_##InstantiationKey_##Identifier { \
      template < NonStaticType > \
      struct TestNonStaticNonConst ; \
      \
      template < NonStaticConstType > \
      struct TestNonStaticConst ; \
      \
      template < StaticType > \
      struct TestStatic ; \
      \
      template <class U > \
      static NonStaticFunctionType Test( TestNonStaticNonConst<&U::Identifier>*, int ); \
      \
      template <class U > \
      static NonStaticFunctionType Test( TestNonStaticConst<&U::Identifier>*, int ); \
      \
      template <class U> \
      static StaticFunctionType Test( TestStatic<&U::Identifier>*, int ); \
      \
      template <class U> \
      static NotFoundType Test( ... ); \
   public : \
      static const int check = NotFound + (sizeof(Test<T>(0, 0)) - sizeof(NotFoundType));\
   };\
}}} //namespace boost::container::function_detector {

#define BOOST_CONTAINER_DETECT_FUNCTION(Class, InstantiationKey, ReturnType, Identifier, Params) \
    ::boost::container::function_detector::DetectMember_##InstantiationKey_##Identifier< Class,\
                                         ReturnType (Class::*)Params,\
                                         ReturnType (Class::*)Params const,\
                                         ReturnType (*)Params \
                                       >::check

#include <boost/container/detail/config_end.hpp>

#endif   //@ifndef BOOST_CONTAINER_DETAIL_FUNCTION_DETECTOR_HPP

/* function_detector.hpp
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
*/