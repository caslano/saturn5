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
Qf/fsTPcgBeMlXzJgUmy0dF8Gfi+e75ZtiedkBTjHN2TFpqblHBic/RKakqR9DFMd05aSRZzYnmEjrX9euJE9EpiKqi0Bd3Z2T5pJXXnkzR0nEg4lWRHmQyKbpH0PMY5ons4NNtOJZ04QdlEY4TXRD0jZxyo86ip9MyWuSdOUEv8Npwmt4dFjJpGpZFqEjfdiGtm15qonuKl5wGb3YUZ+NN1mIE/fQsz8KdNMAN/mqi7jZI/dQoHDszTh6R5+HiqEQKTyL3c04E96Yi/oPdJD/tz+jBemgN2jkC901SASDIL9PBj4Qo89SaR6S2Ip7cA+cK+b+z4e77TBSn4kf4INvdKYh33Gg76olRef7hvffS1oP8P5jmnDBLeLEuhkYSS5soSrPZg4enRZN4NNo2ZSdHPKB+j9h1GqhaqcXj8pusNZx1D82CennAd54qZqCupd+pUcQ7QH/cdZ3Um12GoJy0uLoaT9bhUiQDHjxkVBTix/iu9R/jrtbjXs333nVw8lQhf1/DK4qA7fQTSXDEJ6S2ZjH66OhxNPPMjGn9uFJqi9xOavUsC/aozGS2/Oh1JqS5Fl1eORyfkJ6Kdm5Yg1d3L0IbLC5CK2kx0+vwc9IeUFlpyYTVac2UDUlWiIUWlw3jPpYqU9FSQpqYmshyC0PORCNFnDkdWv4xBPrNGo0dzpiOTpVPQ4wUzkbPUL8h/8SwUPw4/F/yIUPb0
*/