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
c2s0rcXfNFX/b5Ak99D+oeECz1dADWBndZ/04VVW99AzVkmHdaLvk+QVcAsdpP430MaLRN+ipLXs7Iei2tTsplDQG/bh7dHxB3ijj98dOCMloxwiRcslrW8cOMmM5I+C3N25kn52gCog3N1zGBdMghS5WpOaAt5zltJS0gyIhIzKtGZLfGAlqIJCzjiFYTid+8GfDqwLlhadn41oQBai4RkU5JZCTVPKbls3FakViBw9oP+MSYU+G8VE6SI8BUXrlezc6CAIlwLILWGcLBGOKCiUquTHwSBtao6ZDDKRykG6LYVbqNUPWc0xmhXZgKgUKAGNpA5ofQdWImO5PrFEKKyaJWeycHZhIWCZDUQNknLeuUNTRmWbAoWoq5ajNaHC6JnShxSl1GjrQqz2FLGsnaO8qUuEw7KgXiaw8A40ZUZro28KsUXpqmxK/kLLdrFnIEqMCmwvAj+yYUkkkw5c+/F5eBXDtTebeUE8h3AMXjDv/F34wRlygyFqDfSuqqnEKGpgq4ozmu2B/9RJt9z4HIZXs4kfjMMkir1ZHGN80Xg0S2L/cpTE8A7stx/Aq2rDdRtszpaaBfCb+/7YPUKBfkookZvkhipW5kI3Hbkl0X10DoF3ObKex1i8ATRtO8BWFBuiGO/oXksFy40y
*/