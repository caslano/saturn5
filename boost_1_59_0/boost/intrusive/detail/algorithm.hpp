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
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
*/