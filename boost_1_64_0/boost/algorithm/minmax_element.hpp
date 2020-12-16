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
FyhaHcDrucAPASutQVbgCBmHADtUCbW4iYbVhcShqAyvwBnhwQtsoRTQhTREwEHS5xlbIOImxhZ1+wtBYIswi6SAvwkp5wSlV7i1RmQSQzkMFMv9W8HdK0BSqVxEKOUkiajXLzUxQuvQ3Th197ygPy4QGqBBq0PSFwNSPdNdLZLwfj5hhLFIAA8PUuenlQlqmAYz3lcqUEGwqMXZGfQToewPSuu4/GpnJ3pJ8B8I6BtEL5Gp6DWkHAz4uZPSGwEkcb8PBWORx2fdfyUBjNO8/vXovBNf5aKN+GogAVXQO2I4SW9IG9BdDJmzqahOLlqB+YWJ9RDPt4C0HG6bmFnofdAZh8ogF9U541lUuYStEs7SAtCygkW1AWSYU0OfglJ9UKJGc1EzNeJcLhfFUbezcU6cy640G+3jbEIyshTVod3kZ0zbj2w6UOw5XLsBfHAdqWW8idplqdlqPb3L4mNsCTfgKj5C+3LsccpggWE/fPdf/gggpFXSPmq9oY+zuaiBU9HffGlDMPYtKo1ZHYw9wt3RwePq9Ga0XdTEraPFQQGpEWChxThapB6DdHEQPg4wcjGBgzpm4EYc8i6qCxZtIPakQ+OrY7hAItKbMvqNUFagUID7ZMeG2wMYSTHYdUSZ0AizKFmW6kVT6EUcDAdlrE/dht6JOYEM1icUoibRiptLNM2JUzpjNN69/pePWD8Qe9jKlwH99EBtxBbTE7eD5tKbAvWk2iKSkNZjLDAn6Cucz5pEU0xFsUe4yN54g9PfnGopEHtQwNiApvSGVG9oqEAaTBgxnfP44zQIAt5cCxZzqGrwTkwT9SJNlpZJjZajXDzuDtjAm+AhrftQJR6KZX0fCTyEKkBcAn1DFElILpGlFYEo8iEsAaa/tSPJTqa0qz8fV5PzFdSazjvPJKJ1CGtLA5x03N6i///7b/tj/+b5bP960nLzGbc7P/3uViwJcZtk0SA6NbQPNn0OUa+6g+sTZ91NXiIcJOUcbMDzB7prYe5NqIrCz9P+w1mod/HVVuj8xIvT+QBY+k2kz/+efUHmfxz/5SPol9974jj1y/2HHN31y7m39tYv1xxyfLr65Wm3Hka//FHV/6B+ueWnPfTLWw86Pj39ct5Pu+uXv7nliPrllT/9Z+qXsQ8dR9Ivp+FTN/0y85ZPR79cfPNR9Mu9Bxz/Wv3y3jxLv7x84WTW/38spusVpF4GWL+8xKUPp8GZhME5gpJ5NaQr/jcoQK6Qpn+dYkCdyGN9UuiFFF2MFQsEJBLqJL+NdriFSsnqR5bQN6MPJbXJpNqZI9ROIb8DUaxAiih2dNadv7xtnURlc1FWgl7YKPSnPKmJynK1TirLizsURX89RXFUgiCnwdj9E/7SkCDt1xWQqJk+qEXomy689Q2wYioUUjfX0oJK4qR6ykU1VEc8GNM3Ti0sDrD2CUiEpin0zn54OwGaC9WR1Db56a4C0jAHYemI2oA8F1ag/njWtlUvYs1IrfVnnWE1as2nqmoHuEntlFotvfUk1IQPOq1bTO1VLqqldQy06Njjf3Dfs5tXestTKmhSyTo5KL2GeqCSIslPOT43Jz502YOjUKdEadyNU6CNohQWokKLdJAKyj2BRkXYOU1mHYs1qgSWtqx5zqk5caTvqYDUgKLoJnToOGtUhIrTBTqde03tkx6uLMa62vboyIOsc2Jlvf6x2beSvuXTaZDQLmEaT9SproAulr2m0spIJsycyUgWmDmLMcNrRVL2GbFyLPL8VYYhNQjkDhH3Hpg621CBViTgxYvSeBKIFRiV6gDm2cAmqaxmq3WEgC8wHkWr54jxoGZrydoiE3nGsYhmYIdxg52CIkplpk2848WfVPU=
*/