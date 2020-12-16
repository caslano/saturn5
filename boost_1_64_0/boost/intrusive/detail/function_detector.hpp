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
J08tWLbt+c6vOUi0NmKPrEVY2jJj7q4Ff7l01Ok9io8srR+faC1C59dGfNJrFw7UGgX7GohPb+2CfW3BJ7+mob21C+sgfvJtvxg8Adpj/O19nw8LiO+4s9L4e7Xx983G37cbf39e/17J3zcYf68w/r7R+PtW42/P5rjKk+GvmVAfBPVNWBWzZmK8+m5PAFPAU9X3udRV+7z6HKwCh3p8XoT6rGeor/pA8B6wWH3bP6M+66eor3op+CB4LvgNsB58GFwKbgTv0/gnwMfAH4HfBp8DN4G/BjeDvwefBP8Jfhf8EGwFXcr0NJgKtoLpGu4Bfg8cAX4fHA3+EJwIPgvOBH8KloM/A6vAx8HPgj8Cr9H4z4HbwFUa/0WNXwNuBX+s8ds1fgd4N/gG+GXwTS9e27UkYi8Fj9P+SDHOzVyu+wl/HswHbwAPAVeAx4IrVc7EiA0SPFjlpEJjVc5V2q8t6ou/DDwIvA7sC14N9tewryfq459r0ZMlKu9ysDd4haZbHrF/gXWarge0VNNN0nSlYE9wGlhgrDk5BzwMPA88GZwFjgPPB88DZ4Png+XgBeBF4CUaXqDXazX8toTV7gMer+VJh2ZoeW7W8nxB9f1WMEPD3TWcB96m7XM7WAR+ETwOXK35tAbUjqD2m1XgOdBjxDu6pmcY+FupDzzgaeAu8EzwWhe9A/9IuAb8E3gZ+DLYDL4CXgX+BVwOvgquBP8K3ga+Bq4Fd4P3g38HHwXfBjeD/wS/A74LPgO+B74C7gX3gB+CWRT+I3AAGKA8w8EgeBgYAo8HU8BJYCp4FtgNnAWmgReC6eDFYAY4G8wE54DdwWawB7gI7AkuAbPBFnAEeBd4NPgt8DjwCfB48EfgieB2cCz4ClgC/gU8BXwNPA38J3g62IM2nwj2BieBo8AzwdHgZHA8WApOBs8GZ4LnghXgeeACcCZ4BTgLvAo8H1wBXgjeDF4E3gteDD4EVoKPglXgt8G54A/AevAlsAb8E3gp+IrGfwA2gcFguD+KwHmEi8H54HiwGjwTvAQ8CywDZ4GzwcvAcnAJOAe8AlwIrgAXgbeAV4K3gh/rmaoO4a+AbxB+HLya8FMg+id6fEdkLhFs1PslG0LX5Fep49E8vW+rdTy6BDwaXACOARfq+HSp3se1qu914BlgPXg2eBlYDjaAlZquCmzS+6AZbNB4XYOj84joIjQsZp/zlQZfSZJ8pUnyzU6Srz5JvpZ2+FYYfKuS5FuXJN/GJPlak+TbbvAthky+Ewy+XR3wFYbaXzs1O42zHKEdZ4V0HVXi9VN74LGtodq66ZNZR7Vz0//eWqqsKSGndZJ9TVXaZtoJ2j6p/fVVozcnt8Zq9ub211mt3PzJrrXasrnz6622b25bc/Xq5n1fd7V3876vvdp6ZrDd9VeFU0L7vQar6YyO12Hdhn6XPt62Hms0+sn6Rfu6LN3nvZiyzYDqoVXQRmg79CrkTOUehsZCldByaCO0A3oP6l8ackqg+dBKaCO0o7RrHdf/0y8E1X5y/v+L5jfU1NfV1Vy4qL6scl5j037vAej5+K/NYx2z+vjP1nf7pdAI/dY4yJtX/4LMzZ03cdK0yaVTp06O2Hb6ZMs8W2294Uf7I+E91TZHp3Jc348bH54lTVWN1jk6k7cw5PFeWmn6pD8l1/tbfa7MtH0GEWH4Z87Anu35Lmwm3OryfS8+cUdkZaVF++/eTfyX1Z/wQcvZaFZ7vs4Reu2Sp+0SmSOkvsRJfX3bPfUijnopn1c2yuv7JfZgjcZFfahPi/etemnUPmE71Pf5awHSgveCg0lbcmt0X5WNq246px4bf1XYN7gfPNht/P22pgr/FwP4VlF2TY8=
*/