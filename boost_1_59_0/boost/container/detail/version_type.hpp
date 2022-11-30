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
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
*/