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
H1M/UiivdKbF6B7C8CxXYly/pYGXjM3vQBW+PbG08cX7ZSGhbcT26YWf+zXSHu8OtmLRHx3MUkziIablNZpflidxNHnRdXrx6PsSEqLRSU9fuJ812T4yxV9dEqMGJcr5JYea+Vs1szVQLrKJo0roGpKJL3snFM7oTbOO1RhEClt2LrLOo3j/gNm+mSlYnCz6+AfYsYIMBoa5fudIR59gVl6FNCX9wsgXnZgzi0zCr4faLyAbr4uJd/FuTCcDGIoYNwDdb75TTSg4UTFsqSM0LU3YTymMe41Z79kdvxr9spzE/OLxcs+E0+hPR0GWdYv8eugdUfp3kUpoHh8Ko7XIOMpMeYpfDbiKhrag6A9n3PsiooTiEBVRr3kgpGoF1PyjaeE1W757egg9hO+e795n+NL4UiKVps+e9XB2nfSTfa+EXyrM28/yyQycEnB0wlxBJ+1XGS3S8vgs+jrn+0JewAimKjKQ/V5SzCdF/0f72COP2G32OjNMo+n9a5/s/P52CBwfxjhLOWnKxs+2bhes/Pr2CwQv5lkp0oPJX+G1z1d+fJgZPBNwSkJXy+N0d+xjRlG2OxefVTLty+ImUsnEMbi/Aw247N6TFcoWsPT/oaHwFXfVNXmQtETA1qfnE3xqw95jEYC4Cqqs2stNSMOSRuzwvm/ImgWemRArYNe8FXD7OR+E68iyCY395r0nYZlHo5qkce7WA9ic/knF
*/