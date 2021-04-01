//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_DETAIL_ITERATOR_TO_RAW_POINTER_HPP
#define BOOST_MOVE_DETAIL_ITERATOR_TO_RAW_POINTER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/to_raw_pointer.hpp>
#include <boost/move/detail/pointer_element.hpp>

namespace boost {
namespace movelib {
namespace detail {

template <class T>
inline T* iterator_to_pointer(T* i)
{  return i; }

template <class Iterator>
inline typename boost::movelib::iterator_traits<Iterator>::pointer
   iterator_to_pointer(const Iterator &i)
{  return i.operator->();  }

template <class Iterator>
struct iterator_to_element_ptr
{
   typedef typename boost::movelib::iterator_traits<Iterator>::pointer  pointer;
   typedef typename boost::movelib::pointer_element<pointer>::type      element_type;
   typedef element_type* type;
};

}  //namespace detail {

template <class Iterator>
inline typename boost::movelib::detail::iterator_to_element_ptr<Iterator>::type
   iterator_to_raw_pointer(const Iterator &i)
{
   return ::boost::movelib::to_raw_pointer
      (  ::boost::movelib::detail::iterator_to_pointer(i)   );
}

}  //namespace movelib {
}  //namespace boost {

#endif   //#ifndef BOOST_MOVE_DETAIL_ITERATOR_TO_RAW_POINTER_HPP

/* iterator_to_raw_pointer.hpp
Sxu2stq3C8yOAfu2Ln6tvVJMDPmbI4050jOHhSwVN/gs6yyEISl7zqoupvg6CYWJgon0EcWlxebBBYf5J0ZgCahhRqyQgbczQGJL8Ogv470XF0pmkojojSDzs4RJYBey8OeThGbof3WwWhzwieJ+mCA6qexhTsDFMs6RO3M4GxbMqd0HILJfkSNDFbnaRLrcKq7wBb/6itICGmdRbaX6ClpMGc6Nz1C6sotR8PE6a0sXP56YgQV2CpstjdbASAE/BoPcIAg/owNHyU/RIORaMYzjlojwo9x6bAFe/5dPjy6UEcjET+oFdsNDxXdKILynJo8KlinCj6GkxX2dnaKMJ9RYjxjD//iFSyzbfCMwJBMoA7SFmUfg1iTiKKr5F2KKqGMQbLlZidK4QFJ1icp+nbD2OZIxUI/QG01chaEadZXCLqTuB/t3Akh8OKaGK4/xQIXJHrkcQAMdJa50s3IoIgSRaugCxB/XTTaqTPVZeJSHucoEqfc4DT376p7RBncv0L3Y8qayMJLxPnvByeSwitDYXG34k/CdoiLKrYDqH3PlGjJSPUGOe3Za8A==
*/