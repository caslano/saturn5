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
fG3kouxT1tq49zSP5bkOgD2QDp9O36vFtJmmkw2Ve2i8tX3W51KVN0joWTGYhYVlYplUKpdJdcCYzhJLUTUuBzKnpdfQ0Htk0Ju8PdkATIT0j29SnomKO6XX5B/ZHWM3vWnpicgVVrs8wbeB3JZIK+QsrDSp1UoYuLq4eBi47sV8PyC+Wa4cZL8tj+p/3uT3RDwKwCFIv7PqYj9H45KfnbtldTlm1YXeFXHUE7wkNECfbJE7lbvVJiUiF0qF4hGoSjv1mcocI0p/y9Yn+ZD5u7fIGCvq+LecbV0gBft5W2cNaup8wJ9D730DEbKB3Gc2jN4ZTGS4NkBD9RxLABB3oyR+GOXQuy89LOZ8g3U/8Gby7g547HnL1KV0itVoAz7M47wAjVJsvg59b3FfB2LTexoy0kkUxZsQjWNI758ZSe6fG6Kbkt7m8loOAMbbpl0GH2rlHErgqLDQDSRmvpAX8qCcFQ6NdCqt/7HjuQ2S8iEtejsp2izYYgxnlm+63ub28I8CcIXUxYxbPVinnW9G5eR6esfhFH273+ZG4sIfYMY1V1KuGdvNO6p2o0KhE9ji27BW7e3Rx2DfI27dUO9TZsuT/Q2BsmDEqAx85C+RdSkmTnLD+DYHNG9U9AEnHAJeLeUrU0N+LYDssZz7Btu+zH2Hx3JeCMBj7zhthE1BzKoyOwA+hH2bUUyoEicD+zLBLZ+kyoMkSprxmo2r
*/