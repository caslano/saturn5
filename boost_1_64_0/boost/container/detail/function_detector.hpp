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
W73bBTBZc+dj8Ib/QQWunyoyjXvhfcHv3+75PlULhunaF/X6u/1e92o8LJHMndmBxuU7wfRkvsw+DbTMhaUKaw7+GHABZiKTMftaYmA0zEzmx8zUPdcBs5J5M3t0aN5omI3Mn9kbX00QLI8skFnjtB6tYZIOznl2L/BvDpOT8f0mFJ/+GRZFxvMc8G7gnzA1mZxZyVdTl8N0ZDzPzkdWroclkeG+4Jtt3fvQC6Yn82JxmXtn7YIZyEKY+WzZdAOWTsbnF6f7eTbMIqy5ImZYCZiVjM8oadbjzjCbsOaOh3c+wm6RubIaEj1a/wHLJSvOLMW6cz8sT8hlUaOQKFi+MAfz08U3YLKOzv1s3XNRf1gUmSezeR7DkmEqMg9mtkmjH8M0ZL487snE6bB4Yc3G61oOgyWR8Ro8YuO6wVKEPGdc3LcAZiTjcz95I8cKM5EpWNzenDrrij5XyHD/kkXne8UXrrG473EwO05xsY1iM7CmstN/39mckLpI6recloK4RDLcL52ieyL//cvbYj8TGY6z07Tfk8urA2CZZJHMMj4snQyzk4UxcyhuV4VJOtNnB7PXLzOHwKLIfJhtqx4mhanIQpmF9wzLhunIApl9rWGdBksi82OmmXovEmYgC2K252GFsbB0snBmCx6dWAGzknky2zLocDDMJux3M63fY1gemZyZ14SRvWCSLnQMMnul/3gKpiDja94bXW8uTEXGe3Yw8P4YmIaM9+X581ENYfFkAcyabtY2gemFNe9o2h2CGci8mE2o9+UwzEjmz6yJu5cVZhb2i+48JBtmJeNzSG32Lh5mF2qf2dOrHixf2K95xooGMHlX5zhJqiMNpiTjvf7fGlUiTEPGZ6tPflMA05EFM3u67s9tML1gD3JzImFGshBmqxddXQKzCHFTot7ugdkE++R6ZCrMQebNzFztaE2YJN55v8/NKs2FRZGFMrs61y0SpiHzdep1yyRYPJmC1xBTogQshSya2ZV7i80wi5DLuLJTR8NsZHzuex/5v4c5BFtUy1gdJu/mXENC9yfPYSqyUsy6rrlhh8WTlWbmcWLIVJiBjPdalRz3BZZOVp7ZmtSQKTAbWRizDQtvl4c5yHjt9356/BYm7+7c6wex6x/AlGRBPM+hs/vDtGRKZksWlM6BpZCFMzOMPlEZZiLjufzwud0TWCYZ79nm2svsMDtZILNp6ffXw/LJ/Hl95yrOg8l7OB8v7l5L2sFUZAHMFhe0zoZpyfyYta57vOgeM5EMfTlD1kNbcQ/MQBbN7Of77+fDrGTa76b7bhVcNt2CKRLovofF/eqzcRY+G5VkuBaco8/NyUdKRsHUZHJmuzymFP2NrY4s4d/9LtKa5ddqx8KsbL9vtvTloE9Y8zwZ3rfaaE3HuDFuMBsZev3NumYtuA7LI/NgZq5wqy8sn0zBTLlT1Q2m6EnHPLNid5LmwGqR8Vzsz8Z0hanJXJl9yogsQH0aMsm/v4W7QjZkcImi4zql13/3kX+RTTDMHgEz9kI/dd+tILf2OaxpIbP8u+aNb+f7ugpNYZmJRcfSd0tdFnAfZiOLYbbW/dxEmKwPnQ/MujR9GgZTkrkze3X//GuYmkzOLId+Qw7TkQUzcwzVVoTphTXbJzYcCTOQeTAbKMuKgRnJ/JjVH//pAcxMJmMW8MTtV1imYD921iyFZZN5MjucunwSLEewh3VuTYHlkXkzk1WYvQqWTxbOLCphTUuYoq9zDQ/HXDkLU5H5MjsSO/QcTCvE/XY4ogksgQz30N9Mado4AZZExmuvt6TRZlgKWSiz44eHF+1nIpMzm/7oiC/MQsZrD+5ifwWzkvkzyzZqbsJyhLiKVb02Fn0+kOk=
*/