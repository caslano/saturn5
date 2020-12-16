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
N9SUaGqKNTV9mjqFAMeBmgqXvjzNpS/HuVA/3o36Hf1E/Q4n6itdqJ/gQv3pLtSf4Ub9Z/qJ+s84UT/FhfqpLtRPc6H+TCv1eEdn8uIS9d8S9d/rrIUYkZLBvMzPYF4WZDAvC93My9fusZoRFYzdHg72k0+5h4NVKECPCEBeAuR3ighrtQDKLkjwIllneS9BgtMswLMLEnzldgk8uyDBJ2Sdhv4IEoxbqDieIMGzLBCON0iQzMs/3m3lC/SjOcWD7f2kezwYMNhnBCAvACKE9oCwuAVOdoGCEVnnil4CBYdbgGcXKPj77RJ4doGCD8o6jf0RKPg+CxXHFyg4wgLj+AMFwbw8KdYk6EA7+0kH2nnSdSCg/kv9RP2XnKivcqF+ogv1k1yon+xkGA1U1N9rTIshmtKBktIhSOlAQSmUKsIkY1oMKQQwTqZFxIXKGhcq5zqvmPNkJ7ispG4rqNvKaVsxnU2LB/pJvX3gpJsWQP1D/UT9Q5L6k+LygGn1SD9Nq0dOrjpM/ob2/vE3tDtOq2oXKs92ofIc52l1rksnFLlMq4Eu02qQy7QqdptWe/uJMffKoX2dtfc0Y3b0E2N2SOpfZ0fY6+zrSXuqHu8fT9XjjnwfdqF+hgv15zlTP/Oke6pU5wxRndNlOmeg7pwhsnMGYucMEZ0DpYowyXTOwEIA49Q5ZS6dM8Klc0Y6d06509DirH1aFejTDNXUlwjqYdI+7Uh9hQv1p7lQP86Z+vGujPlf9o4DOqoieC3JTyF3xgAHtogRD4NwmKgBQS8a9dSoUVFjj4oaK1EvGhVsoBJDFOy9994N2IKNYMXeFfvFsycq1nNnttz+f7t3/0hQ1PvvJff/7uzszO7M7Ozs/v2LB0YwFyupH62hfj0N9WPU1I9Npt6gw8lrBCCToYMaptVlw+QqpGiAaTP1EzVUTlJTuYlGfTZVNsKpT0WzG6SzV/bKXtkre2Wv7JW9spetS3t+02nz+5bl/Ka5ly/j+U0ltD75AFWf+jCn7NlN/6+zm/CFYX5ol086yUnx7rD66KaDTxArNmmPbgIs6pOb1kxgsX1y09fHizKpT256KgFo++SmOYkytk9u2itRZoBObipIYFzGk5u6WwWGfpzc9I3y3A3dyU2TWzM5ucnQnNxU3Jr5yU3vHGfz5KZ7jsv85Kbpx2V+ctPWxw30yU0/H9v/k5vuO3Y5ntzk053cNOnYTE5u8ulObvqpJfOTm55osXly0yUtmZ/cdGBL5ic3jWsZ6JObPoz09+SmKyLL7eQmv+7kplGRTE5u8mtObvrkmMxPbrrrGJsnN51xTOYnN+10TOYnN61+zECf3PT80f0/uWnW0cvx5KYy3clNJUdncnJTme7kpueOyvzkpouOsnly05FHZX5y04SjMj+5KfeogT656f7m/p7cdHTzcjq5CQ731Bzd9OdU+0c3ARr12U2dUzM/u2nmVJtnN+05NfOzm9aZmvnZTb1HDvTZTdcc2f+zm/Y+cmDObgJTwecl9CBZy0lOmtmJ6bgk+2c3uW2c3eS0c3aTS3d2kyvN2U2WWRie5JQ9uyl7dlP27Kbslb2y17/lYvFnxffc5l6HAWjyAYUmR2Qc2Wq/wSXiu7lkRgh3ZXLEW3zG7+O5ffHYWFJg/GX2Cqx5aV/c7lcW9N/j+uhapJfUO/tiWm81+5oY/15GqyCmWRDTVAe0SR/vev3mvnj6z4jYoGdHQc/vF/WDHu/JA0TPgms4PYf3h57nLxggesYJet67kNETZgSFM6Ko8/AMKKpV0RMAeq65mst72NkyRHycs5p+zKua0BgrtabuBpIGnzyxcT6aVNWGtKowYAOWqskXfABrEFPaZ/k=
*/