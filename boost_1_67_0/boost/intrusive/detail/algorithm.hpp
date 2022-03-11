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