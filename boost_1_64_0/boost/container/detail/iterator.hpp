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
GgjZ//N8g6Vwo76v9jzfFBgiq4ojz5nm/FrgfWTVinCly0wtyChA0Lsucqs13N7REkg2z3v9dPNB+lE6DSsMgiR2LHXnfBjLgk6BP1BpFahoHG5zTG5YVpZ9Y+g5mLn1n/xmtJUhVsUmA9CT1oM7bFe8jBHgnb8/9Y5ZUSoYpMYyFifuUe4jvwOGPWfeMnDLUTazrAjwZpBfxKpSlUbh1h+HiGCr121sbcD8uCetw77b31KsxYxfavq/w1sDqOyAQ07p5/mPuLoa48Saha3Wq5pl8JoIj1B4i4n7uRq7lIv+P6rbThUVJo5UIkLk+WowrxQHEzzIAvMoz/pcNye+hfhyqjY7h8LImv63BRUswyhJjM9R1WZfqrXGfqd+mIVV0S0ojKSBJVmeJHRbuw91Y0N1iKwvAHCtWMdiCx+Klxy+2R0UEJtxyTK/lIKk7TKTyiep6F6wVOZOYP/OkG6F5CiNaDgJ6lNgmqIAYWkzf4gXL3ypzDNHx7b3flo6SQAtTUF+f0I9eP8eRRObc0B5wWpVFbl9oFAQD6kf9quyBRFHRYMVNUIn0UzOIQ==
*/