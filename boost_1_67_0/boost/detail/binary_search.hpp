// Copyright (c)  2000 David Abrahams. 
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
// 
// Copyright (c) 1994
// Hewlett-Packard Company
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Hewlett-Packard Company makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
// 
// Copyright (c) 1996
// Silicon Graphics Computer Systems, Inc.
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Silicon Graphics makes no
// representations about the suitability of this software for any
// purpose.  It is provided "as is" without express or implied warranty.
// 
#ifndef BINARY_SEARCH_DWA_122600_H_
# define BINARY_SEARCH_DWA_122600_H_

# include <boost/detail/iterator.hpp>
# include <utility>

namespace boost { namespace detail {

template <class ForwardIter, class Tp>
ForwardIter lower_bound(ForwardIter first, ForwardIter last,
                             const Tp& val) 
{
    typedef detail::iterator_traits<ForwardIter> traits;
    
    typename traits::difference_type len = boost::detail::distance(first, last);
    typename traits::difference_type half;
    ForwardIter middle;

    while (len > 0) {
      half = len >> 1;
      middle = first;
      std::advance(middle, half);
      if (*middle < val) {
        first = middle;
        ++first;
        len = len - half - 1;
      }
      else
        len = half;
    }
    return first;
}

template <class ForwardIter, class Tp, class Compare>
ForwardIter lower_bound(ForwardIter first, ForwardIter last,
                              const Tp& val, Compare comp)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (comp(*middle, val)) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else
      len = half;
  }
  return first;
}

template <class ForwardIter, class Tp>
ForwardIter upper_bound(ForwardIter first, ForwardIter last,
                           const Tp& val)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (val < *middle)
      len = half;
    else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}

template <class ForwardIter, class Tp, class Compare>
ForwardIter upper_bound(ForwardIter first, ForwardIter last,
                           const Tp& val, Compare comp)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (comp(val, *middle))
      len = half;
    else {
      first = middle;
      ++first;
      len = len - half - 1;
    }
  }
  return first;
}

template <class ForwardIter, class Tp>
std::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const Tp& val)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle, left, right;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (*middle < val) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else if (val < *middle)
      len = half;
    else {
      left = boost::detail::lower_bound(first, middle, val);
      std::advance(first, len);
      right = boost::detail::upper_bound(++middle, first, val);
      return std::pair<ForwardIter, ForwardIter>(left, right);
    }
  }
  return std::pair<ForwardIter, ForwardIter>(first, first);
}

template <class ForwardIter, class Tp, class Compare>
std::pair<ForwardIter, ForwardIter>
equal_range(ForwardIter first, ForwardIter last, const Tp& val,
              Compare comp)
{
  typedef detail::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = boost::detail::distance(first, last);
  typename traits::difference_type half;
  ForwardIter middle, left, right;

  while (len > 0) {
    half = len >> 1;
    middle = first;
    std::advance(middle, half);
    if (comp(*middle, val)) {
      first = middle;
      ++first;
      len = len - half - 1;
    }
    else if (comp(val, *middle))
      len = half;
    else {
      left = boost::detail::lower_bound(first, middle, val, comp);
      std::advance(first, len);
      right = boost::detail::upper_bound(++middle, first, val, comp);
      return std::pair<ForwardIter, ForwardIter>(left, right);
    }
  }
  return std::pair<ForwardIter, ForwardIter>(first, first);
}           

template <class ForwardIter, class Tp>
bool binary_search(ForwardIter first, ForwardIter last,
                   const Tp& val) {
  ForwardIter i = boost::detail::lower_bound(first, last, val);
  return i != last && !(val < *i);
}

template <class ForwardIter, class Tp, class Compare>
bool binary_search(ForwardIter first, ForwardIter last,
                   const Tp& val,
                   Compare comp) {
  ForwardIter i = boost::detail::lower_bound(first, last, val, comp);
  return i != last && !comp(val, *i);
}

}} // namespace boost::detail

#endif // BINARY_SEARCH_DWA_122600_H_

/* binary_search.hpp
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
*/