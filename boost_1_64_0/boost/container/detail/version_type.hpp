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
m6X86DiV5zeKDDBwwsiMVHFSuNP65wJ+r3mQSZQVpi1ykzuoxh+WAppy6cPWrex+3mm0IJXhOo9uFCDoYw/Ec36EvxyjlNSiUq4UoGR2s+XxMfpzHWHDZyGDHs6BOJ1Po/nxNOx/oQvDvDWxJKCDtV2oRQ0q+kma63+B9nbj9R1ULsM3VOv9sEbMZJnYtLNNIPy7PjOkAen0Bfcf5R2TFg9sPzrCDEBQ04uLQPxXHymRQvI/vEPhwaIA7FhqBjWhPco2IYhjAhPiPGv7ozT3F3XnNz0cIETbqIRG0JoVk0JTsOQMajg/RYscj4NvRwRxln0cvLLtI+ZW8PmQ0BkAUGUz02utBzdqfRp5CgH1HLXJ5Zq1eDYjF+iZh5q1FBi4JUP1DNaHan/jqM4/PrQtmvnrZd5P067+M40WbikR8zXssH8thEfoXLSnj/+egIkTYJ+v5q+SYA/+QSN0OOclo3AnPxWt4qeYYuzthueGw8lMf41CuOwxMbjyeoVTmkhCgi9w0XoiYI3SFxNxH78cdpJ+91PF9OLF7G3VprvXkoG+LyQaiyWZXfse4w==
*/