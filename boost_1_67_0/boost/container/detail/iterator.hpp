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
using ::boost::intrusive::iterator_distance;
using ::boost::intrusive::iterator_advance;
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