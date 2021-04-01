//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2014-2014.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ALGORITHM_HPP
#define BOOST_INTRUSIVE_DETAIL_ALGORITHM_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

namespace boost {
namespace intrusive {

struct algo_pred_equal
{
   template<class T>
   bool operator()(const T &x, const T &y) const
   {  return x == y;  }
};

struct algo_pred_less
{
   template<class T>
   bool operator()(const T &x, const T &y) const
   {  return x < y;  }
};

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
    for (; first1 != last1; ++first1, ++first2) {
        if (!p(*first1, *first2)) {
            return false;
        }
    }
    return true;
}

template<class InputIt1, class InputIt2>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{  return (algo_equal)(first1, last1, first2, algo_pred_equal());  }

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, BinaryPredicate pred)
{
    for (; first1 != last1 && first2 != last2; ++first1, ++first2)
        if (!pred(*first1, *first2))
            return false;
    return first1 == last1 && first2 == last2;
}

template<class InputIt1, class InputIt2>
bool algo_equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{  return (algo_equal)(first1, last1, first2, last2, algo_pred_equal());  }

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool algo_lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                     InputIterator2 first2, InputIterator2 last2,
                                     BinaryPredicate pred)
{
   while (first1 != last1){
      if (first2 == last2 || *first2 < *first1) return false;
      else if (pred(*first1, *first2)) return true;
      ++first1; ++first2;
   }
   return (first2 != last2);
}

template <class InputIterator1, class InputIterator2>
  bool algo_lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                     InputIterator2 first2, InputIterator2 last2)
{  return (algo_lexicographical_compare)(first1, last1, first2, last2, algo_pred_less());  }

}  //namespace intrusive {
}  //namespace boost {

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_ALGORITHM_HPP

/* algorithm.hpp
AhxylPARfsbjmKsGAq8GXcNwh+nqO6Pv9DtrM115RUYcbW2oyvmAtJzbHdH5zhMtDQR5dC0jLrVZR+cV++xMsbBT1kePQOXpO9OVxb6K7VLXPnq5dwP2K2sAH3lJaR1e01tp1ppRRoQn7/Azr1J8I1ZowrfMFpfhiM0Ag8Cvb7dAkzwW7QEVqjCht86Jis14qvKAEjN4M077waYc2FHj4RhAfPF1P/01VFz9AoFaOrmx+2BYTSWFoc5r9KUSy0IJX5++3WuNhoXvAfwxH6vZKWnpabRtg+1Pdzf5JSt590w+R5RxO1MT4w6zAQiTap56KhPTSJE3JxnTYeRY5r7C8trDRqh+BvnbL86w7fKCco25Z1A7KP1XQNZCZRV8NsgPl6JFBs0oQngY1Vl6bEq1bQm+Qa/8uDjjgZ44tmiBoAOcxJdiAQlTmvFiBKVa+iy4r4R3Ux9+VfuyvC7JmCQv2diP2GHza7x8JFByVoq5snaFX9R+oa/6f4vR9Mfu3T2/95NxBwOznb16UjDiVryPvY+jysawYlrsyd9Am5LsAK3QLsQSJPg04QyDGQ==
*/