//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_DETAIL_ITERATOR_HPP
#define BOOST_CONTAINER_DETAIL_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/intrusive/detail/iterator.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/container/detail/mpl.hpp>

namespace boost {
namespace container {

using ::boost::intrusive::iterator_traits;
using ::boost::intrusive::iter_difference;
using ::boost::intrusive::iter_category;
using ::boost::intrusive::iter_value;
using ::boost::intrusive::iter_size;
using ::boost::intrusive::iterator_distance;
using ::boost::intrusive::iterator_udistance;
using ::boost::intrusive::iterator_advance;
using ::boost::intrusive::iterator_uadvance;
using ::boost::intrusive::iterator;
using ::boost::intrusive::iterator_enable_if_tag;
using ::boost::intrusive::iterator_disable_if_tag;
using ::boost::intrusive::iterator_arrow_result;

template <class Container>
class back_emplacer
{
   private:
   Container& container;

   public:
   typedef std::output_iterator_tag iterator_category;
   typedef void                     value_type;
   typedef void                     difference_type;
   typedef void                     pointer;
   typedef void                     reference;

   back_emplacer(Container& x)
      : container(x)
   {}

   template<class U>
   back_emplacer& operator=(BOOST_FWD_REF(U) value)
   {
      container.emplace_back(boost::forward<U>(value));
      return *this;
   }
   back_emplacer& operator*()    { return *this; }
   back_emplacer& operator++()   { return *this; }
   back_emplacer& operator++(int){ return *this; }
};

#ifndef BOOST_CONTAINER_NO_CXX17_CTAD

template<class InputIterator>
using it_based_non_const_first_type_t = typename dtl::remove_const<typename iterator_traits<InputIterator>::value_type::first_type>::type;

template<class InputIterator>
using it_based_const_first_type_t = const typename dtl::remove_const<typename iterator_traits<InputIterator>::value_type::first_type>::type;

template<class InputIterator>
using it_based_second_type_t = typename iterator_traits<InputIterator>::value_type::second_type;

template<class InputIterator>
using it_based_value_type_t = typename iterator_traits<InputIterator>::value_type;

#endif

}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_DETAIL_ITERATORS_HPP

/* iterator.hpp
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
*/