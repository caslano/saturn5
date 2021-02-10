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
OofoFLxwvsE7D8IT1AZFrxLIbSOJQhYS6KphlJQ7zn/oTbfc9AzGs3gShKdRliST7MKPg9N57CezSQovwD6EhDRG369ssBldGgHAa/flS/cAF8xbRnK1zq6IprwSpt4oK4XIyRmE3iffehp+sQ9o1uUaI26Z3ma+IFLTihY5auGayH6KsB1oMg+jaRIk1k+UF6wtCRwZGr006w9W57AQuP6I3cBswV6NqmEonieZOcAEv4K9ntXwfef3xE/GcTBNgyi0pjkWKIdGUK6NdPC29CY429y7b4SliMRoAL09jNB6GCGew9t2g1dWkr9booygBq2iBhoRFlVgSEfT9AHnqe/HgxfDRTW1+uwPXcs6MLI0DBXV9HrLxIVQ8P1/iBTdNgcipZBuF980jtJoHE0Sy2MMep8pvpk9/0/v03TiWy6vrD6HnQ5+e5BiyqkeYKpoNTCLQ/jXAvhSCnT/Ht+7HHXxrntCZvEeQxGNEXT2fXVMoDg4YG8bELnN8VIQtxAre2isEWeHB7aBSshVT2IXfquCe/wnqv/LQ4odSCOx0tXANt2yIVjEnaKpnJbws1osuO3shPe79eW/xT72PO/EfmdXlBP7K2YFIzlvmy3p/yy3ol3ivQsvmHjHwSRI55ZXlv0fwWv3lQsRZ2uU
*/