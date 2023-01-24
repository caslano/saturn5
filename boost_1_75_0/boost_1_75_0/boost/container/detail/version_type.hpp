//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
//
//       This code comes from N1953 document by Howard E. Hinnant
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BOOST_CONTAINER_DETAIL_VERSION_TYPE_HPP
#define BOOST_CONTAINER_DETAIL_VERSION_TYPE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/container/detail/config_begin.hpp>
#include <boost/container/detail/workaround.hpp>

#include <boost/container/detail/mpl.hpp>
#include <boost/container/detail/type_traits.hpp>

namespace boost{
namespace container {
namespace dtl {

template <class T, unsigned V>
struct version_type
    : public dtl::integral_constant<unsigned, V>
{
    typedef T type;
};

namespace impl{

template <class T>
struct extract_version
{
   typedef typename T::version type;
};

template <class T>
struct has_version
{
   private:
   struct two {char _[2];};
   template <class U> static two test(...);
   template <class U> static char test(const typename U::version*);
   public:
   static const bool value = sizeof(test<T>(0)) == 1;
   void dummy(){}
};

template <class T, bool = has_version<T>::value>
struct version
{
   static const unsigned value = 1;
};

template <class T>
struct version<T, true>
{
   static const unsigned value = extract_version<T>::type::value;
};

}  //namespace impl

template <class T>
struct version
   : public dtl::integral_constant<unsigned, impl::version<T>::value>
{};

template<class T, unsigned N>
struct is_version
{
   static const bool value =
      is_same< typename version<T>::type, integral_constant<unsigned, N> >::value;
};

}  //namespace dtl {

typedef dtl::integral_constant<unsigned, 0> version_0;
typedef dtl::integral_constant<unsigned, 1> version_1;
typedef dtl::integral_constant<unsigned, 2> version_2;

}  //namespace container {
}  //namespace boost{

#include <boost/container/detail/config_end.hpp>

#endif   //#define BOOST_CONTAINER_DETAIL_VERSION_TYPE_HPP

/* version_type.hpp
IAggjARRKJDSGXJMdOBg0GBnq8nRMGE6VcSxrsjFFW6bI12NiF4SxeumYTXdRzd/KtcFBXnl8nZ9SUJQDV7SdmHQdKaZTIw3YDqzakATGlkxFiXk9oe5Ttf38tb68es+r6g4Of15X1UvWFyvUwH87hpiVx6uPLzYq8cRCSf65+cX2sNPlUpoBRMajYvm7IEaHBBCMJvN8sNAKjD5/Oc/f1j3wIGVAMocvwBLdc6JAJwWWasvfqc9ASWRv0460vXlDw4Piew+AH4RARwc7rN3W6FVRCA1YSCQgSgmjzbMu92SxhjYjTg6SonjrKgpzzjX48q1LpBvjihUENlRuRJy2xksBXlk4ZxB0lfIZYG17qQjJzNbl6DjdGmqmCWC6cwYA6czxSwJjM6bWYQSlS7WfSQ/j5dW8ljVSQj+42rFPpJWCUBdvXgEwJMgHD2ubktR59DJPQCqHAOQZICKkXpqP3v9/BdCMBwOSdO0bhVg7U7APiz1AhSov2AE14DzQtZ3w/1XZKxc1kpH83A8GhWrAH0Qgv392xxPAjQB0ur/xWrhYsVgI5L0uhG9XkizKRmNM69Fx40rYcG+Hp5fe29QtwdA/iY+tfPT/bdwkkGd5lsnBXh9ragKyhq44sTYAGaJMQLmG4VK4e+iZsfPa3kRV/dVhxpBZ07fd4bESr68/BpTxc9eEvcFtUSkbsi0pjiByI8DyECohGaYGSmh
*/