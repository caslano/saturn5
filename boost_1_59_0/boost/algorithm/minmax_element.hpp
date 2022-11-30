//  (C) Copyright Herve Bronnimann 2004.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/*
 Revision history:
   1 July 2004
      Split the code into two headers to lessen dependence on
      Boost.tuple. (Herve)
   26 June 2004
      Added the code for the boost minmax library. (Herve)
*/

#ifndef BOOST_ALGORITHM_MINMAX_ELEMENT_HPP
#define BOOST_ALGORITHM_MINMAX_ELEMENT_HPP

/* PROPOSED STANDARD EXTENSIONS:
 *
 * minmax_element(first, last)
 * Effect: std::make_pair( std::min_element(first, last),
 *                         std::max_element(first, last) );
 *
 * minmax_element(first, last, comp)
 * Effect: std::make_pair( std::min_element(first, last, comp),
 *                         std::max_element(first, last, comp) );
 */

#include <utility> // for std::pair and std::make_pair

#include <boost/config.hpp>

namespace boost {

  namespace detail {  // for obtaining a uniform version of minmax_element
    // that compiles with VC++ 6.0 -- avoid the iterator_traits by
    // having comparison object over iterator, not over dereferenced value

    template <typename Iterator>
    struct less_over_iter {
      bool operator()(Iterator const& it1,
                      Iterator const& it2) const { return *it1 < *it2; }
    };

    template <typename Iterator, class BinaryPredicate>
    struct binary_pred_over_iter {
      explicit binary_pred_over_iter(BinaryPredicate const& p ) : m_p( p ) {}
      bool operator()(Iterator const& it1,
                      Iterator const& it2) const { return m_p(*it1, *it2); }
    private:
      BinaryPredicate m_p;
    };

    // common base for the two minmax_element overloads

    template <typename ForwardIter, class Compare >
    std::pair<ForwardIter,ForwardIter>
    basic_minmax_element(ForwardIter first, ForwardIter last, Compare comp)
    {
      if (first == last)
        return std::make_pair(last,last);

      ForwardIter min_result = first;
      ForwardIter max_result = first;

      // if only one element
      ForwardIter second = first; ++second;
      if (second == last)
        return std::make_pair(min_result, max_result);

      // treat first pair separately (only one comparison for first two elements)
      ForwardIter potential_min_result = last;
      if (comp(first, second))
        max_result = second;
      else {
        min_result = second;
        potential_min_result = first;
      }

      // then each element by pairs, with at most 3 comparisons per pair
      first = ++second; if (first != last) ++second;
      while (second != last) {
        if (comp(first, second)) {
          if (comp(first, min_result)) {
            min_result = first;
            potential_min_result = last;
          }
          if (comp(max_result, second))
            max_result = second;
        } else {
          if (comp(second, min_result)) {
            min_result = second;
            potential_min_result = first;
          }
          if (comp(max_result, first))
            max_result = first;
        }
        first = ++second;
        if (first != last) ++second;
      }

      // if odd number of elements, treat last element
      if (first != last) { // odd number of elements
        if (comp(first, min_result)) {
          min_result = first;
          potential_min_result = last;
          }
        else if (comp(max_result, first))
          max_result = first;
      }

      // resolve min_result being incorrect with one extra comparison
      // (in which case potential_min_result is necessarily the correct result)
      if (potential_min_result != last
        && !comp(min_result, potential_min_result))
        min_result = potential_min_result;

      return std::make_pair(min_result,max_result);
    }

  } // namespace detail

  template <typename ForwardIter>
  std::pair<ForwardIter,ForwardIter>
  minmax_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_minmax_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  std::pair<ForwardIter,ForwardIter>
  minmax_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_minmax_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

}

/* PROPOSED BOOST EXTENSIONS
 * In the description below, [rfirst,rlast) denotes the reversed range
 * of [first,last). Even though the iterator type of first and last may
 * be only a Forward Iterator, it is possible to explain the semantics
 * by assuming that it is a Bidirectional Iterator. In the sequel,
 * reverse(ForwardIterator&) returns the reverse_iterator adaptor.
 * This is not how the functions would be implemented!
 *
 * first_min_element(first, last)
 * Effect: std::min_element(first, last);
 *
 * first_min_element(first, last, comp)
 * Effect: std::min_element(first, last, comp);
 *
 * last_min_element(first, last)
 * Effect: reverse( std::min_element(reverse(last), reverse(first)) );
 *
 * last_min_element(first, last, comp)
 * Effect: reverse( std::min_element(reverse(last), reverse(first), comp) );
 *
 * first_max_element(first, last)
 * Effect: std::max_element(first, last);
 *
 * first_max_element(first, last, comp)
 * Effect: max_element(first, last);
 *
 * last_max_element(first, last)
 * Effect: reverse( std::max_element(reverse(last), reverse(first)) );
 *
 * last_max_element(first, last, comp)
 * Effect: reverse( std::max_element(reverse(last), reverse(first), comp) );
 *
 * first_min_first_max_element(first, last)
 * Effect: std::make_pair( first_min_element(first, last),
 *                         first_max_element(first, last) );
 *
 * first_min_first_max_element(first, last, comp)
 * Effect: std::make_pair( first_min_element(first, last, comp),
 *                         first_max_element(first, last, comp) );
 *
 * first_min_last_max_element(first, last)
 * Effect: std::make_pair( first_min_element(first, last),
 *                         last_max_element(first, last) );
 *
 * first_min_last_max_element(first, last, comp)
 * Effect: std::make_pair( first_min_element(first, last, comp),
 *                         last_max_element(first, last, comp) );
 *
 * last_min_first_max_element(first, last)
 * Effect: std::make_pair( last_min_element(first, last),
 *                         first_max_element(first, last) );
 *
 * last_min_first_max_element(first, last, comp)
 * Effect: std::make_pair( last_min_element(first, last, comp),
 *                         first_max_element(first, last, comp) );
 *
 * last_min_last_max_element(first, last)
 * Effect: std::make_pair( last_min_element(first, last),
 *                         last_max_element(first, last) );
 *
 * last_min_last_max_element(first, last, comp)
 * Effect: std::make_pair( last_min_element(first, last, comp),
 *                         last_max_element(first, last, comp) );
 */

namespace boost {

  // Min_element and max_element variants

  namespace detail {  // common base for the overloads

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_first_min_element(ForwardIter first, ForwardIter last,
                          BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter min_result = first;
    while (++first != last)
      if (comp(first, min_result))
        min_result = first;
    return min_result;
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_last_min_element(ForwardIter first, ForwardIter last,
                         BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter min_result = first;
    while (++first != last)
      if (!comp(min_result, first))
        min_result = first;
    return min_result;
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_first_max_element(ForwardIter first, ForwardIter last,
                          BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter max_result = first;
    while (++first != last)
      if (comp(max_result, first))
        max_result = first;
    return max_result;
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  basic_last_max_element(ForwardIter first, ForwardIter last,
                         BinaryPredicate comp)
  {
    if (first == last) return last;
    ForwardIter max_result = first;
    while (++first != last)
      if (!comp(first, max_result))
        max_result = first;
    return max_result;
  }

  } // namespace detail

  template <typename ForwardIter>
  ForwardIter
  first_min_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_first_min_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  first_min_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_first_min_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

  template <typename ForwardIter>
  ForwardIter
  last_min_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_last_min_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  last_min_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_last_min_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

  template <typename ForwardIter>
  ForwardIter
  first_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_first_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  first_max_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_first_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

  template <typename ForwardIter>
  ForwardIter
  last_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_last_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  ForwardIter
  last_max_element(ForwardIter first, ForwardIter last, BinaryPredicate comp)
  {
    return detail::basic_last_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }


  // Minmax_element variants -- comments removed

  namespace detail {

  template <typename ForwardIter, class BinaryPredicate>
  std::pair<ForwardIter,ForwardIter>
  basic_first_min_last_max_element(ForwardIter first, ForwardIter last,
                                   BinaryPredicate comp)
  {
    if (first == last)
      return std::make_pair(last,last);

    ForwardIter min_result = first;
    ForwardIter max_result = first;

    ForwardIter second = ++first;
    if (second == last)
      return std::make_pair(min_result, max_result);

    if (comp(second, min_result))
      min_result = second;
    else
      max_result = second;

    first = ++second; if (first != last) ++second;
    while (second != last) {
      if (!comp(second, first)) {
        if (comp(first, min_result))
                 min_result = first;
        if (!comp(second, max_result))
          max_result = second;
      } else {
        if (comp(second, min_result))
          min_result = second;
        if (!comp(first, max_result))
              max_result = first;
      }
      first = ++second; if (first != last) ++second;
    }

    if (first != last) {
      if (comp(first, min_result))
         min_result = first;
      else if (!comp(first, max_result))
               max_result = first;
    }

    return std::make_pair(min_result, max_result);
  }

  template <typename ForwardIter, class BinaryPredicate>
  std::pair<ForwardIter,ForwardIter>
  basic_last_min_first_max_element(ForwardIter first, ForwardIter last,
                                   BinaryPredicate comp)
  {
    if (first == last) return std::make_pair(last,last);

    ForwardIter min_result = first;
    ForwardIter max_result = first;

    ForwardIter second = ++first;
    if (second == last)
      return std::make_pair(min_result, max_result);

    if (comp(max_result, second))
      max_result = second;
    else
      min_result = second;

    first = ++second; if (first != last) ++second;
    while (second != last)  {
      if (comp(first, second)) {
        if (!comp(min_result, first))
          min_result = first;
        if (comp(max_result, second))
          max_result = second;
      } else {
        if (!comp(min_result, second))
          min_result = second;
        if (comp(max_result, first))
          max_result = first;
      }
      first = ++second; if (first != last) ++second;
    }

    if (first != last) {
      if (!comp(min_result, first))
        min_result = first;
      else if (comp(max_result, first))
        max_result = first;
    }

    return std::make_pair(min_result, max_result);
  }

  template <typename ForwardIter, class BinaryPredicate>
  std::pair<ForwardIter,ForwardIter>
  basic_last_min_last_max_element(ForwardIter first, ForwardIter last,
                                  BinaryPredicate comp)
  {
    if (first == last) return std::make_pair(last,last);

    ForwardIter min_result = first;
    ForwardIter max_result = first;

    ForwardIter second = first; ++second;
    if (second == last)
      return std::make_pair(min_result,max_result);

    ForwardIter potential_max_result = last;
    if (comp(first, second))
      max_result = second;
    else {
      min_result = second;
      potential_max_result = second;
    }

    first = ++second; if (first != last) ++second;
    while (second != last) {
      if (comp(first, second)) {
        if (!comp(min_result, first))
          min_result = first;
        if (!comp(second, max_result)) {
          max_result = second;
          potential_max_result = last;
        }
      } else {
        if (!comp(min_result, second))
          min_result = second;
        if (!comp(first, max_result)) {
          max_result = first;
          potential_max_result = second;
        }
      }
      first = ++second;
      if (first != last) ++second;
    }

    if (first != last) {
      if (!comp(min_result, first))
        min_result = first;
      if (!comp(first, max_result)) {
        max_result = first;
               potential_max_result = last;
      }
    }

    if (potential_max_result != last
        && !comp(potential_max_result, max_result))
      max_result = potential_max_result;

    return std::make_pair(min_result,max_result);
  }

  } // namespace detail

  template <typename ForwardIter>
  inline std::pair<ForwardIter,ForwardIter>
  first_min_first_max_element(ForwardIter first, ForwardIter last)
  {
    return minmax_element(first, last);
  }

  template <typename ForwardIter, class BinaryPredicate>
  inline std::pair<ForwardIter,ForwardIter>
  first_min_first_max_element(ForwardIter first, ForwardIter last,
                              BinaryPredicate comp)
  {
    return minmax_element(first, last, comp);
  }

  template <typename ForwardIter>
  std::pair<ForwardIter,ForwardIter>
  first_min_last_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_first_min_last_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  inline std::pair<ForwardIter,ForwardIter>
  first_min_last_max_element(ForwardIter first, ForwardIter last,
                              BinaryPredicate comp)
  {
    return detail::basic_first_min_last_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

  template <typename ForwardIter>
  std::pair<ForwardIter,ForwardIter>
  last_min_first_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_last_min_first_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  inline std::pair<ForwardIter,ForwardIter>
  last_min_first_max_element(ForwardIter first, ForwardIter last,
                              BinaryPredicate comp)
  {
    return detail::basic_last_min_first_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

  template <typename ForwardIter>
  std::pair<ForwardIter,ForwardIter>
  last_min_last_max_element(ForwardIter first, ForwardIter last)
  {
    return detail::basic_last_min_last_max_element(first, last,
             detail::less_over_iter<ForwardIter>() );
  }

  template <typename ForwardIter, class BinaryPredicate>
  inline std::pair<ForwardIter,ForwardIter>
  last_min_last_max_element(ForwardIter first, ForwardIter last,
                              BinaryPredicate comp)
  {
    return detail::basic_last_min_last_max_element(first, last,
             detail::binary_pred_over_iter<ForwardIter,BinaryPredicate>(comp) );
  }

} // namespace boost

#endif // BOOST_ALGORITHM_MINMAX_ELEMENT_HPP

/* minmax_element.hpp
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
*/