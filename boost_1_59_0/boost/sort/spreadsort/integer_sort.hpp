//Templated Spreadsort-based implementation of integer_sort

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari

Doxygen comments by Paul A. Bristow Jan 2015

*/

#ifndef BOOST_INTEGER_SORT_HPP
#define BOOST_INTEGER_SORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
#include <boost/static_assert.hpp>
#include <boost/sort/spreadsort/detail/constants.hpp>
#include <boost/sort/spreadsort/detail/integer_sort.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {
namespace sort {
namespace spreadsort {
  //Top-level sorting call for integers.


/*! \brief Integer sort algorithm using random access iterators.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors, or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
  template <class RandomAccessIter>
  inline void integer_sort(RandomAccessIter first, RandomAccessIter last)
  {
    // Don't sort if it's too small to optimize.
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last);
    else
      detail::integer_sort(first, last, *first >> 0);
  }

/*! \brief Integer sort algorithm using range.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] range Range [first, last) for sorting.

   \pre [@c first, @c last) is a valid range.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors, or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
template <class Range>
inline void integer_sort(Range& range)
{
  integer_sort(boost::begin(range), boost::end(range));
}

/*! \brief Integer sort algorithm using random access iterators with both right-shift and user-defined comparison operator.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] shift Functor that returns the result of shifting the value_type right a specified number of bits.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).
*/
  template <class RandomAccessIter, class Right_shift, class Compare>
  inline void integer_sort(RandomAccessIter first, RandomAccessIter last,
                           Right_shift shift, Compare comp) {
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last, comp);
    else
      detail::integer_sort(first, last, shift(*first, 0), shift, comp);
  }

/*! \brief Integer sort algorithm using range with both right-shift and user-defined comparison operator.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] range Range [first, last) for sorting.
   \param[in] shift Functor that returns the result of shifting the value_type right a specified number of bits.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.

   \pre [@c first, @c last) is a valid range.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).
*/
template <class Range, class Right_shift, class Compare>
inline void integer_sort(Range& range, Right_shift shift, Compare comp)
{
  integer_sort(boost::begin(range), boost::end(range), shift, comp);
}

/*! \brief Integer sort algorithm using random access iterators with just right-shift functor.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n

\par Performance:
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
  * <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>\n
  * <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] shift A functor that returns the result of shifting the value_type right a specified number of bits.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
  template <class RandomAccessIter, class Right_shift>
  inline void integer_sort(RandomAccessIter first, RandomAccessIter last,
                           Right_shift shift) {
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last);
    else
      detail::integer_sort(first, last, shift(*first, 0), shift);
  }


/*! \brief Integer sort algorithm using range with just right-shift functor.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c integer_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n

\par Performance:
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c integer_sort is asymptotically faster
than pure comparison-based algorithms. @c s is @c max_splits, which defaults to 11,
so its worst-case with default settings for 32-bit integers is
<em> O(N * ((32/11) </em> slow radix-based iterations fast comparison-based iterations).\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
  * <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>\n
  * <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>

   \param[in] range Range [first, last) for sorting.
   \param[in] shift A functor that returns the result of shifting the value_type right a specified number of bits.

   \pre [@c first, @c last) is a valid range.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \throws std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
   the right shift, subtraction of right-shifted elements, functors,
   or any operations on iterators throw.

   \warning Throwing an exception may cause data loss. This will also throw if a small vector resize throws, in which case there will be no data loss.
   \warning Invalid arguments cause undefined behaviour.
   \note @c spreadsort function provides a wrapper that calls the fastest sorting algorithm available for a data type,
   enabling faster generic-programming.

   \remark The lesser of <em> O(N*log(N)) </em> comparisons and <em> O(N*log(K/S + S)) </em>operations worst-case, where:
   \remark  *  N is @c last - @c first,
   \remark  *  K is the log of the range in bits (32 for 32-bit integers using their full range),
   \remark  *  S is a constant called max_splits, defaulting to 11 (except for strings where it is the log of the character size).

*/
template <class Range, class Right_shift>
inline void integer_sort(Range& range, Right_shift shift)
{
  integer_sort(boost::begin(range), boost::end(range), shift);
}
}
}
}

#endif


/* integer_sort.hpp
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
*/