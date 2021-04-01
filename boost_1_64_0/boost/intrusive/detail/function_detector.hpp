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
FHEql25+PfD0yY6ve+25ftdS2X7RJlK6YDWhP3IuI0HsA/3n359R0lPk31FyQ+ga9Ey+IizIS4lhJYJ0gMCo9IPEjKpncNvMR/ZxeMx2XRNxfjWr3rge0Ch16f4pgK/DId2YjXBOzJF0cKUthRkvSrPolUsyt8mtDz0XsSonoGTqRtUYLYIjLJ4qvabWpCQWQ6LTeMd11ydIbguqBVp7AiM4akbNJk+FiXlbZr0xaUK59zpknSiZ/+q/3dWtVJVxCcLomDNQuwcEaSKpG/MevkJROpCkgehexJAsaaLgG+5rZuUu78D8T8UTiclE9Y4knNRSCPDZCPKY30ERjU4aPvtqYRHftoBNIwQGfHLjrpjPecLxEKX3CpM4Q/kKmaQNM8bicF+qIrM8Q9rejV6yqvJoQbe2Lhh3l+vtXgsWvWTVvt3RegEBGc8ihe1Mnx9peIHvgkICPXr+9tFakWZZzRiroVvwLOjTpCVraipS+gKcTeXnvrJXdhdcNuwbWjroMfVQSfRGEczVi4fa1rBX61RGYDOajsJ8/1yxGpRXoMUvLGP8Xc93UNHxYQ==
*/