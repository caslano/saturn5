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
nmtiMK4Q/2Ec6+7GQQHm14u/ZCDesvDc8bWhfT4m8eNxVw8UH2RcUlD70TZ3x4o2yxo7TYmTBsWTnfX2SWae9rVODEjZjFD0+hkQm5tHe4zssuto2v/AaChl8Wb4wnuwT/Kq4SIy6XuUto+e4TkAkANIARQA8by3desVXfSPRY5jnWB918MPU8AwjoqwfRAISroPEmYBCJ8dqCyNA0E+z7cYHW/P1iyAgAeoHISxKu2QvCkoiXPXYlZWPbIDf7Vjln24WBW59Wg+oqtlV4BlKivapvF+1X5V+hzPvr5Jc42KpHBt0MUnHPWF3kMjfg69AS0Kz17kfJ5mhNZBOrqMeC54NUmvVCsa1V1MoPS8+PhLNwC4WCUkBF5rtYmfQWwAckJxIIBaCi+mp8geNIe3uDAotLdrCDLSTctSBGKjf4f2Y+cv9QENZgEqLYwHUJZHGBEyi+stcGjTH2shylbOb4RpPUDoyZwcxzMU0iUUtJR6RUrWJDIcPnh1iZjLcmN8MlGhjgiZaA7GE4a+ldY2SkEI4USQAUx+/j+h7XTJKdugU5dniidSsvstnEHjZyh2vjG6ID4vaRdeAPO+fijVaS/QrEIHHipRZGpLB0Xb0O4/7324GPTZXqV+2hKjuMRHK4Ai/C16783oI1L9z8X1/2xN5/hn+pa2drB2tTL/8S+k+KHXcPPXqERz3aYzLnMNjGicS8loH71doV+F
*/