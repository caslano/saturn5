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
dAR4XXdNhti+W9RxAI0eTfJutvxqoKJ8GrMlgVPdGkeVCJzZL6ScA1jnPRGDU12jp/+XCUXZwEAqvQTDezrhG/0z2YvACszo91TBdpU2rgKgc1N1sOEXG8Z6Y0UtuwWKJcFbR3EI61hov681BXLfRm5fn1hX/AEzBvdqM6Cza0xEfbzoUrrrYs3VCGYqSMYxGHb12v9T3IiZFh1EmZRYU/rNLHAHjWwPun/AJ6GEzHQHkU2eDhFDbcSKZcNvnpTeYUPVI9YkLTqfcg2/kg5NCnbI51hudrfT+d+yL1pYV1WqyDALy+UNtogPfn93arEwd7VhGI03rlJoWmWCgYJPZ0S2GArgOoMUZ2lzLmtTXT8ZR5RYcPYV+Qr/wdV5r2/4+yQd0fYaz6cpJpPuGkXSJhBRTQT8Ty1ns5OAMh6Y6pcoArZKHu8XvSLJSeZ/WSaWdjoYnMiPbOVrVDqVH+24n3uoWcSXUxTTaVPMptaplrVWWS1THcWE/imnoAgImZ+3B3wb1FieAM2ES1iaaYk59EeVtu50ygK+Gz6yENZnrkoW5zrhD6oT/CLWKA==
*/