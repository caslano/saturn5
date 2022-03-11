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
dBLpDtMogDG1NPbrIlQYoZEBf9Rc0kVBKqwp9tsA5sL/kxpRlFyQz11o/JEK0Zt87vo5j82fHUaKzS06b+8sdj3D/P6ruumeehE5QEiwa6s0p7+yHFRfXfPXrjVVfRQqfpRylvJAk4i3DTCqn9Y6iHJ5dTdozUCCX4DmJwhjOMBQW9X/WQ1KP8KUqUgfQIFLGsWbP18SASh/nysKnvWdB9EP3eIQqjiU70g7WPLIFVnW6zR7PcVB+jg0s/e7UN535QVHewoo8Av8L2fgdnAvcIN9BtGHOkpWW8Incx7NzZUrkhfJljFnH8S0trq7XH8f8k/Nri+sIU0N8XvtErVWOJnrQofmvCce9IsNY3snWR6Z7HWQ32uPwK5fzBe/doGRXycrYmGopXPlHjl4iT2SIAuDx+3AFjSlpMu1BXbJtuc0guxZbpv8sFwAEHMU8D/IAIcASMTyBaHSwdAA0n8rB8L4z0pRBAYG+V0mCygwCAAM/CeS+m00AwMBBQH6IwdCy2uNxOeFTy+rE5nxx4nmrpLJl9+VOXcUfQdA1J4BkMLF2Lkf3ou1eB1214Bf7BdOxYop7p03v10XjUZXUYZq+qYkmpueEx4M6CmtPr/kjRT3TM33WiQlU5QLCg0m8SMCAyPDPl0+JOVq8JG+SEhEO4C1mvtdAJLNL9LgDQ1g0a4GNIVfpDIGDWDJpuotlZGtIgYDYMam5E+L2qgXSglJke565SEetYrhQGfPjcR6QyXuazLbN3mv5PI+jk671313obf4AohCvz3ibqIuUmUP+G2fD95VnhV+gjJ/OUNHI7ZXLvLowcvfQCAn6k8A+JnX5hXkb9d17pW5O+17PlKITbPMev4Kfxy9yCFY46iFHICM/5f2osmbDMEaJu+NmiEZrJftE+CvWm+GOtGGojl0ALfix23u+X/RKoRQCYoa1yTe9yrHQQYp7hI1oUa0/zQLG+Q1rZtdHR/Y+MUcosvc7jsNQhlY82c10s7q8P0Uf6HvhMiDbfnOsw5jnLvUARujO8Kd/Czz1LP/OynS9xMQIbkv3BhvHNZyJZVzsyRrYCitil/uV0jDDCqVJC/evKqMJeley57XjY6LwEQGkiyzGhKt7iKhxGV6HlVXkqJNgqRUecyfR9s2BvBYX3nGAH4bIJRDHpO3gvRvfZlx4S0nf9Mt/W4JKbUQpux8Ni3I1W8n+0LGwDO3815+kVmQpNCH/IGJZK3R5PzZg9FlN7EbJQOJGfSDGUFKTkLSLS5GjrlCzd4YzUI2eDaH/cqIcHbtEH8AsiUgRwGYU1DyMryBTkR/Ww6io2MKmcGj3tvf9R4TGloGA4spTLCn3NrVbfRPq2MYoIbgyi8tPgF3BIwS0ND9QoYIeaF7xX5Wewcoz8OdIHTUZmb4PSsy2eCXM8hIpVP4CyRybhr4HQ55wMg0HjgKDfYUivJ8638Y91CQnTaNd2fQZmpCchHgMWc1nwS5j/VQ2VZpTFJse9n/2JeeWjGyQH5HnOJH97F3jvmLXZ5OSO4pk+Q1Nukv4IgHhJhegkmYTi6rX9vfiomw/MMwkT86McDAgUG+YyJsPzGRXxG532AiqHi83zERFObvmAiTTUYlPp2OV2QFPd//iRTjY5/GX0gxmKNa/1yKUUyR60S5tfxdikFfYXG5Xu+kXlhVEt2G5VZ7R/wz9DNSMN23Esal5h7NgXJmxe73oT9xtvbO+ll+sa9/3IND2dqXCu1c92zFkDhQc68/eo1KZl/puP6syxgBa14YXs2wyXWgbF189miwzbGf9AxYVer51IjODEGP6+rpVc91X2tGI0y7SfpZWc2jYOv2PSpirvBhzKNii7xfUXxpXeSze203+UYsZWHSoD4oJK6upTc254pY7SPfHkrapWks+Zglbft88rEbtWiwUWjqBAn7qouE8r9AkS8UzAcVekKFZMQe30GRaSgzGU9GJG4JuSWB2ja5Dy9vC26zeVzEoj6NMqA65p3HPHILgiXixmN8Zt7YuSXVoH4Wb5hGlyWhZndVdfeYVIV+bSEmL1I5eWY6jN+6m6FYQQWubPg3PwHEGPO5k4r8d4I0CnJqbn2nc9dz7NYwkRqu5N6Pb0zKyx7JvMHrZMiS/Hwpl63egvFCj7c12Drs1RSJFsP3gw+b+A6MKDtUrZnTu3qMlu+j8GW5igeLi4A6BmUCuSsw+pVS4c4I9sbgr3mFW/o1yzd05MccS3iLUNubvAP2QiqdmT2JDjbT4OwGHTegjGHjgkD7vLP24utCrIgFBO87Zu/WmhAOTdWCpcZECYPxLBzQEJ1zazZjixK8amywT8tQ0/OYnIyfjeql4H2+5HxNVYs6qA0aSzcjJ028cy5/tl2ohEwsuPsd4aPSFe8lH39Ko23d/RmS+Bmxl3L88mzIGHxonqVa07ElNjls/fyszmDLY/9KMmjVaOixbP7s1IhmuFzRaQr4MJgi/wsXQv8TGEn6AYxIFQzfQ55hHrX9rcAI4z9oftP/CIwAQEHAQUCgfgw6z/eWz5OqQ/xWkYGESvLDkoFCwOflmyGn+0dgpMAl/uMOm49irjz5SwII3IGvm4EIC4ankymbomsSwvnzoR/fOF/mSeZOhYQQRlN/jv8yYPFxQM4xliSQxiSJXtAwLeHESZ2KYSCaorT/2tTCHiLhwkt/6uAJQHNUxth4n6Ss/7JvSv2O5cYs1DIPlryW/utNEb2uWl84E9bbfnGPSJap5JsRGtYnAIa0vrqGxPAn56Ij6dzXyubGOQ71EKn5G7divHd8bFWpN4YQOOuiB77ziSkBpzOLOOocpbPSGqXwG4UsXJURj2PQe0ee8d3N0/unJhqRUg6FRnMkQ+q6bCHf/tpI51bykB+XuTN5n2923S78/YnRSt3C6birLnXK4NnlvoemsrnyI+Mgt3Fah7SvY9FuXRFjzhOguswukrhIjN5eqdznUa7sWhRhqw8CPsU6qocunusjNPCzIwNiSknVlwfvk8qbyhwgD4DH16t9bGBLK4ux8YYmiDnMb7fUyn4N7FdA+y9rD5j8+qmV/PDXBoHA0d8bVL1X6KHekkzMUFWzrA+y/W7KCCk4bUbPcbYJodDEWq2ASa732YWYr6QunJrYJ18ixDE1XVEwy0vZhL2PgrIFbSleUCTYVwHceYP4v4ajYsY0nz+R5QhB7YCsGURTYvblpbSsDVPXtNaUUHoCHHTgLiOCuH5Um35tbIVyIIOLGWx/yVfTEtGpFg4yzkpaCWnYXLtebg5xGUDLv5dQIKvRuzJPqgSnKm+7jLuuBDs+ZO2SqLmLOyG3sKtUmyLx7a1p0HhHXyKk8lgS7N7lJRjfzLMTv/X2fd6ZwZ30Lva12jH2tabZeTWxuBRln1j0YydrrF4zf3URY+9mfY+UFwmKdf17oJrDaQITBwiHndCcubcLdsLloA0lZngNgHCRnKBFRRchA4G5SFYvW3RFwzqfNyeKDT4amkT2mtWfA0y+HUqdYkJuwTS2k1/sURRDlS1D83qIPRNuBo61tiuMkot3NjiWgMEqNq0IuggMiw/iqmEp7bfLapXgLpFmDVEsq9YTd5p70RVPkSbqV5ZdvboLddAvhHhBHGHfCr/6ZMneIsDct4VbyTK3gaY5Jo9YRWS5tR0R9LZWgs1CgpkjxjYooU6CzmL4Xae7AvAMbTBDvE1PoNfcoOGgkSUxeMWridzq7jUJV+Jsk1qL0r2XcnmS2ejXrFta/vQ9cU1Kcd/FGHozjLBSZ4pWXAp7DHuyab7JBte2HCZmruIyjigQATRGiTZDWjgJFU7FTDCDUZsOahaCB+m2XBHM1KL0i7Uw1UwQ+Z39R143qsopmzQGWWyRg7pEjoKQKlJtpN/pEVpGD1oPzY9GGyimKDN18OSNDDn6FDcUKvleD1WbjkLJhUp6vIaf/C8b73W2TGo9rA0yzO9oEZoytjYortcGBKAP0sgbX1tQ09ZXflHkDGtDy2D+9u92U0wK602uGTgKmR9SjCC+rZJNCZcPiF1Cj67M8bBFccOkt6dXXodjCt+u6vBeSYxdQl4QtW1Y5bcaFDsKOow26/EDPOK76f2t8AjtP+yO+4/iDCAwCGDQZ3iE4/t1JSgo1K+TvP8Kj+BBfBvjUfB/oiOIyKjECjZR7R0ZlVUEDHxykX9izfgdOLIToTIaZYt3Ef2SufFK2eSHNaMAoZ8ma+wZHEnEHDS9UC1pHJFPIVO4pxsfpPEpt+X7NiQ+ey7K4zeDNF9rWspzRnFUrF9siq9Jj6a94MzWXFbm9G2jwOJoXsx1JXTW/v8nMmqn4VyE6m0vySiuUw1JGmfQiJBMHXgBVM9fGk5+IbY4/z5/PuSElK6fJVCci2QSfBWVAdo+d7ZgbYz5NVxcL/hMI/0DIaznXgrdEyCUJtGjpzX2VYxHZ5ekCbVy2tQinkxcrxlNdXECOBk7fqVOB59cl/4GrBvQYpMBwFFG3qBagLAIoXOQ4AVYJ3++f+8rpzDaV+gELpnYpmjvxRDLS4l6p4eaeTZo5eGbefbEkVdJuTdSIouM1e6CRgZIWqyzjdMZ9soGyE/9xMvRHVJ9H1aVRYGON2VrmtvWJahXOmM1bwMwhmFnE05+8CO9AHd8ZDk0L1+ID9V5kCBjvq07pXHJUJDneGi13vgv1msvA+Q0daROuU76R8/6md7k3NJzGyO9IqEA7/EyYVlchQTBzyceUM7pzPRNhwm6OhdAohk8kaoNoJtFpfIpeyXbF/mBsECaVPUrCkghozsMeLWShwrnfiiJoE6eIpeKVgzdUueqYlYGt5Py+Jury7wJ6usJJOZFzq9151mXxBwXCi1ijsrvPsix9O1/6CIJC2vdKVP1LCHPvhImpFuxFYYSlyBb5H+sOE2IS1WuICI8N+Q6IfJe3DMPseOR6FAsqKTEzidC7M+FCeIRNbL4CuiTNa8VAH3/IU4/hY8VElhhkx63ARBmPMVAg2Gv8wQYl97GIA4GQiSTLgMt66cu3RMTGLVfFX+s+K/okeGT12YzDvso+0Pm1XPmiIZ9KlLI2X4UEcydCwdKgbVzwQI5pEQJfkvQ/c/2DEEMJ4IULlqRohQnSFB5EmDWifXXpDFNukEKiQJIKek4zcCrmv7UQqlaKVw0xNuaEEQKfTmPWmjwYrXAlQ1EgjzAnwArlwTvlfNNs0YsbdLQwiA0CTeSzKe3SU8CkJpc6PheYXvxLpR8+YK8SzQllOr8bTfv2L4iQBVEB5vb1bkBx5rLeSWSipl/goFwM3b5Iz+CZdh5G87ib+YlnC+XuzDU2N8ArC0EI2A4mya7HewimWSfIu9OURkPlFbKYOwYzPIvfMSb++/lR5j/YZM6AIP87jsZCDBwENBnfoT5Bz8CAQX2b+oMZFRexV8IElmFZ3UGEpHXtytnXT3rPyTNtw3ct/0FPgL1Z/jIhbKcwR/kGfDP8gzFqWiN38kzYKAWMbwtWuROtu/PjmlOpsvkLVVDJ0Yqq5uGm6m2kpOPiIhP2qvjHwhufWTUGdUG3cxGmsNcWsMz2WKHuRur006F1/Y+j0EnslyQ1p7cbnC25+vRTVG/5oxH1OrdLlqmm7RMZYs1IbqLKs3dyGEPbH4nWh0uOl9HzkbZXCdFzZ3httC8IGexTaNVUd2+Be8JErNBmFFX2r6UlHs2RV1s16dYU6Iolnx/wdivHlPPapSfe2U4uJgUtjdpeXB+o1BXJPsteICiTET1cmPygpNctqxAuUjIJ5ZVnNYt59t9gSFIFvbx7OldkCbBy7HHw4MGd1MPgoLBZ0FGKuf6zxjezxDej8jqzbM6o2/zCqlZgJvkrgn29Jdo0vfodnaJDpmDHR5joFCyvBYW6lC1AbSqTFRnFmjS9Zclk9yCLi5SirS/kyBhpvkHnSB/QpB8Oyd+IUiIfqozQP6dIMGX1QFDouP1+kuEJC9qMAZF3r9086dGg3SjiggsZnW/4dNiUeSzDeOPJeRAY9fod3Rkmspf54jP5qjCjh3WGucCGm57KPBeX/iBr5P1TNcTHf4JIFPxym02rVtUyj4OC4WGWy9KPsXAHywEdnYjZltFp10P5JKV4acvw8Q6MfX9oN3V4vg6PSdQwu5x/W8IEqyMZocReuy96stHzkHHwomF6yva5SJpq/XFCtR1XoLB364LkBH3dPJuwRWCAi9oJh5AyAQFbhNMHr3CYqeP05G5hF5n5dg37YBJR/rn72pY3gLJb+jsmVn7yWQtTq/DZAg3lHSj84Vbl2LKhr6bDzHzmzTCDsz/uRgY0KV1X5GTxjwyN6hI5J20dBfmnKUph60ryt2MFPVYFxa4bU+t15epZiFwJgddFNISzPX+0khCgsmXhAJXIP4AQgafbBpBwDKFK2RdyBPzC0BiACtf3rU/O8c/eUDrcskELf4Br/wJEKGqTvrS/957fFXEnHtDeoHlkaSs6kVarfW9tJYhPLf5+nVq6yBhGXo16jEH0GhUs+GoVvNXCL5npMTj7BM25LgPEgibjO57IzEYGRjjsYy/mhvybyRJWGj/I0mi4ehNA+NH2sVH/vESd83aFhH+Rg7i8OnJygwq3/atY4X4cnBqBBelaNJ0pVCoC2E3a9r648DLaPOnrSz/endi3+ZWM8xjKSwl/LjsayAciikeZm25Xa3F1gSYNUSTq2bK5I+Qda+D+lBLp84Cl+FP7PNnKDPZ43py7qtLUvMgykWqkk/92vmce8SvohC/EnklEIZIfY6BOo1GVZY/IQQhyCkUQzyQIYJNvDZ+RctACL+ZERX4wK6MTgZWv24rMl5kOm+Ja+QDMcAcHGZVTX50VVOlXf5YZdBTN1XvFyKVGnlcWZGlB7+XFrGO46RUhB9VdRScwBWeNy0cDNZ5Ucl00qiR3HxBPEqkb7UmzyJpteAyI/9FHhGH5+HdlIutMWct7UmYEHQKAblOiCGxZl3YBwfFejZP3KW03t5oeVeva7OF2tX+t56xhE0p6Vo7kOFJu0MGhdj7kFarbjMaNsxz859HfEgIjZc1tvn0F+ojINhaB7IexVfmqbFf/pNoE2bW/0ybVPrgwghetXWqI0SVR/nDwZFPcxkmFyarn+UI1IGh9LFCk4zui2WqjjUSzrA/mgK3IuRPn5q3k5kQnGgDzVm9t51vGb5HmzAM3lTTTz7BuRfBLL12TaXOaFUmpqT9CvuBUMpRfrIxlzG6ZtqES2dRogMAI11lTahatjinNEiZULu77RilA0TL/IXBWY3fe0xU6ibCxG3SP4d9yM0D9wK4cDty0cUkfrNTo/MO5VYxrQLJR2QknsXm/aM3sZXZCV8rLW61YHQe+4qZdm8u2wOMP9txD+jpl6ZKobC4SanXFrqsTvv2SZUuTJ9acsiO01r0nCzbMzz15/jQjdycNqzzO5LOnIlfhD/ORjWO+fK4jAtXG0SHfSEfwtRE9Z0H+FqLVYesbbgS8bVhDiRUbIp8vB//NnLLK7uvu22DDPXrasyufwkqdj/V4+mm6XEm6AnvT8nbB6IfVKN0unzsiKZ0DkvE2zWkwky1i2MIbz9LvbsBSsAhj4lO2mLLZeNKE8YsfHrXHBnjbNPQvP7GaK3hK7lVLVfMubdZA5b24ynY3ax/LDXtwUY2y2v3OQsi6sYqbS26s9WNJb7maz0qU6SuEU8jhXq3Mkl+MoWZEzWKFtSomqvIPvBHkMPWQrR/BHhCy/z/Djzh/fYTsLDyCjIzCbIyCLLy8wnQMrLy0bLSMzIy8jHR8XPhcrAwMzHQf/sRaeiZhFgZaQQE6Jlp+ARpBOlomWj5+Hjp/4fAE0EA0AsgABD0NgAIrg0AhDwHAMKQBADh0gKAiPwBQG/yAUAUYAAgKkoAEE0dAIjW+K/BEyYGlv8FT/674Akdy38ET5TZo7CYYTjbF3X0IBAACIBIduv8XohZgfZSDTH1zQVMQp5MI1eKAjGNso/XHByAZK1wrXCu5U9PW57HaeHHnm4dC8eed+TX0+XM4J4nLxvn3G7tYt6+F/6Y7+B1ITDKkAo3qJ3C+xpjBe+KVrrtzqST6VS8Cl7L+5XQmIk/5ARBHXweJt9x/j7DqPGjUSaUKcsIwCY4b9nllmqwJNHmujU9M8IjTNAkIHHmhHJr9XqCzT1zspWgzBz8oJf8eAwZ74zKz0/2loo4tPoCWcXaUqJcmvkQ47VkbKCOAft4Hf2yIP4Cl1CT7hkDOZrnjdyiOEesIO1R5OpU3WlYcyZW+bc9JWO/V1v+zOKOyj8dsVaQwGDog7nNlBxGPUW7L6ncrNgF7VDgmJETUvkWimxFuUQxJqe/P3dSzVnLXhNGURgpeoq16+aowrmxEGTSVSGv8EUAZ6H6xfIsh0Z/PrU4r8HJ8spxOLen6z2jP2AY76teqFdwvlCvURgQ8kIUlpoCE9MqWXMfNrW4rYxp1AfK4NIYV28FSDl//pFHBGNmRxWKAxMYrOpMiuDYIc7jq54RfjgNSNNadtAeu6oXppWM8Ttuui+j53uj0n1oP+028vUpvp4eyBzBl1DEWsFUA21QSpX1xODyaX1LcbDXNBpUSaHEdNVcBlqD35vn1/klQZJjQjW4U7eXZZ4wMbd07tUbXWu/TzQgELkp+C7km67K1qm75aJnr8rPjVXWpxXUyF40Zzdo+mF7M0wcUQ2b9/twItrJoIg9YAd7R4DGWsFncoaRi13A2tglm8cQIWs4F9kv7VH63Redv5UIYyWZWVhzqzeQWBlSFbL0YEpqc4zV/iRzlCNpTokANBjGogV1OZhLEfSie6HI6mJ+25tFtpDnUtcgi0l/8fQ11ePOgK5xfQTBaZc+zZfYEXuH1UXDO88ABCz704Kw6FrMkSKnz6lJ1lny6H1TFT//k0rFBt9IM+Us998Vnunms2UmFA+TDjuGlwjaFIJ4MBXKK9phXtFGzaoSCqNfGJDmUyzfNaGIeqoSqnGNxgVso0WUulaR7EEWKlMJSPHbXJWGwnelDtD3XdTEVbYv8fmoiasAvkjsr9TI44nKG5ENiMbw2WXqj9+PNBZVbOHCdWggDOr3Jc4zjbFs8qQstKIzzH42/1q7+yEKiz9/u1SCtOvVtqY1zeVS7THvBzILFGO47cPtrw5G12yRN3JQl2qArzaz7k6dAltblnYZXNO93Qy7RRWyaa+W7Jrt7aUqZ6ZE8rL5zWD2UBuhbytkjN5ukXJvlNCsQN8=
*/