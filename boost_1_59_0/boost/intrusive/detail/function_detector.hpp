/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2009-2013.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
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

#ifndef BOOST_INTRUSIVE_DETAIL_FUNCTION_DETECTOR_HPP
#define BOOST_INTRUSIVE_DETAIL_FUNCTION_DETECTOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {
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
}  //namespace intrusive {
}  //namespace function_detector {

#define BOOST_INTRUSIVE_CREATE_FUNCTION_DETECTOR(Identifier, InstantiationKey) \
   namespace boost { \
   namespace intrusive { \
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
}}} //namespace boost::intrusive::function_detector {

#define BOOST_INTRUSIVE_DETECT_FUNCTION(Class, InstantiationKey, ReturnType, Identifier, Params) \
    ::boost::intrusive::function_detector::DetectMember_##InstantiationKey_##Identifier< Class,\
                                         ReturnType (Class::*)Params,\
                                         ReturnType (Class::*)Params const,\
                                         ReturnType (*)Params \
                                       >::check

#endif   //@ifndef BOOST_INTRUSIVE_DETAIL_FUNCTION_DETECTOR_HPP

/* function_detector.hpp
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
*/