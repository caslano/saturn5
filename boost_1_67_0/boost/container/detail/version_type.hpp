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