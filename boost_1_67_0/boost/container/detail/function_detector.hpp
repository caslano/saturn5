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