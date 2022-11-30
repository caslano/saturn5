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

# include <utility>
# include <iterator>

namespace boost { namespace detail {

template <class ForwardIter, class Tp>
ForwardIter lower_bound(ForwardIter first, ForwardIter last,
                             const Tp& val)
{
    typedef std::iterator_traits<ForwardIter> traits;

    typename traits::difference_type len = std::distance(first, last);
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
  typedef std::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = std::distance(first, last);
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
  typedef std::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = std::distance(first, last);
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
  typedef std::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = std::distance(first, last);
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
  typedef std::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = std::distance(first, last);
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
  typedef std::iterator_traits<ForwardIter> traits;

  typename traits::difference_type len = std::distance(first, last);
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