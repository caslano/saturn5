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