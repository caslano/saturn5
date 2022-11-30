//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////

//! \file

#ifndef BOOST_MOVE_DETAIL_ITERATOR_TRAITS_HPP
#define BOOST_MOVE_DETAIL_ITERATOR_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#if (BOOST_CXX_VERSION > 201703L) && defined(__cpp_lib_concepts)

#include <iterator>

#define BOOST_MOVE_CONTIGUOUS_ITERATOR_TAG

namespace boost {
namespace movelib {

   using std::iterator_traits;

   template<class T>
   struct iter_difference
   {
      typedef typename std::iterator_traits<T>::difference_type type;
   };

   template<class T>
   struct iter_value
   {
      typedef typename std::iterator_traits<T>::value_type type;
   };

   template<class T>
   struct iter_category
   {
      typedef typename std::iterator_traits<T>::iterator_category type;
   };

}} //namespace boost::movelib

#else

#include <cstddef>
#include <boost/move/detail/type_traits.hpp>

#include <boost/move/detail/std_ns_begin.hpp>

BOOST_MOVE_STD_NS_BEG

struct input_iterator_tag;
struct forward_iterator_tag;
struct bidirectional_iterator_tag;
struct random_access_iterator_tag;
struct output_iterator_tag;

#if (  (defined(BOOST_GNU_STDLIB) && (__cplusplus > 201703L))\
    || (defined(_LIBCPP_VERSION) && (_LIBCPP_STD_VER > 17))\
    || (defined(_YVALS) && defined(_CPPLIB_VER) && defined(__cpp_lib_concepts))\
    || (__cplusplus >= 202002L)\
    )
#  define BOOST_MOVE_CONTIGUOUS_ITERATOR_TAG
struct contiguous_iterator_tag;

#endif

BOOST_MOVE_STD_NS_END

#include <boost/move/detail/std_ns_end.hpp>

namespace boost{  namespace movelib{

template<class T>
struct iter_difference
{
   typedef typename T::difference_type type;
};

template<class T>
struct iter_difference<T*>
{
   typedef std::ptrdiff_t type;
};

template<class T>
struct iter_value
{
   typedef typename T::value_type type;
};

template<class T>
struct iter_value<T*>
{
   typedef T type;
};

template<class T>
struct iter_value<const T*>
{
   typedef T type;
};

template<class T>
struct iter_category
{
   typedef typename T::iterator_category type;
};


template<class T>
struct iter_category<T*>
{
   typedef std::random_access_iterator_tag type;
};

template<class Iterator>
struct iterator_traits
{
   typedef typename iter_difference<Iterator>::type   difference_type;
   typedef typename iter_value<Iterator>::type        value_type;
   typedef typename Iterator::pointer                 pointer;
   typedef typename Iterator::reference               reference;
   typedef typename iter_category<Iterator>::type     iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
   typedef std::ptrdiff_t                    difference_type;
   typedef T                                 value_type;
   typedef T*                                pointer;
   typedef T&                                reference;
   typedef std::random_access_iterator_tag   iterator_category;
};

template<class T>
struct iterator_traits<const T*>
{
   typedef std::ptrdiff_t                    difference_type;
   typedef T                                 value_type;
   typedef const T*                          pointer;
   typedef const T&                          reference;
   typedef std::random_access_iterator_tag   iterator_category;
};

}} //namespace boost::movelib

#endif   //

#include <boost/move/detail/type_traits.hpp>

namespace boost {
namespace movelib {

template<class T>
struct iter_size
   : boost::move_detail::
      make_unsigned<typename iter_difference<T>::type >
{};

}}  //namespace boost move_detail {

#endif //#ifndef BOOST_MOVE_DETAIL_ITERATOR_TRAITS_HPP

/* iterator_traits.hpp
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
*/