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
9/eeoh9coBoI954UTAqmQMmtviM1BXzmLKNC0RyIgpyqrGYb/MIE6ILClnEKk2i+CsLPLtwVLCu6Og+yAVXIhudQkB2FmmaU7doyFak1yC1WwPo5UxprNppJ4WF7CprWperKGBCEKwlkRxgnG2xHNBRaV+qP8Thrao6TjHOZqXHWU+EVunw21QrRlOQBZKVBS2gUdcHEu1DKnG3NHSnCxarZcKYKdw8LG4p8LGtQlPOuHKYyqtoRKMQdW66JhArRM21uSgplut0VsnwSiLR2hbZNLbAd0oJxuUTiXWhETmsbb4nou3QsW8pf2bI99hykQFQw8GMI4gFsiGLKhZsguYyWCdz4i4UfJiuIPoEfrrp6V0H4EbXBsGsN9L6qqUIUNbCy4ozmT5r/VKc7XnIJk+Vidh3Nk/Ta/5rOg/l0FoTTdDYNP+PLUxi8g1DujMTfDWDA2cZoAN57p2feES6Yb2nZcM1SRbXZbvygshQWjy8h9K+nzosd1ocolHtWNiWIpkTjGP5r+q2hSisjewIVqyhngtqK8SqM5nEQO78wkfEmp3BuMLTSLD44bbdM4ovvsA3tOzgoUDcc5fMSMBe4FLcG2+hP2/jjNJ4sgnkSRKETSlSSyMygoBAH7TEyTLlDx9W0lLvWtu+93068
*/