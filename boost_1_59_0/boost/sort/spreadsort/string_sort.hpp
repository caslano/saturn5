//Templated hybrid string_sort

//          Copyright Steven J. Ross 2001 - 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
*/

#ifndef BOOST_STRING_SORT_HPP
#define BOOST_STRING_SORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
#include <boost/static_assert.hpp>
#include <boost/sort/spreadsort/detail/constants.hpp>
#include <boost/sort/spreadsort/detail/string_sort.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {
namespace sort {
namespace spreadsort {

/*! \brief String sort algorithm using random access iterators, allowing character-type overloads.\n
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \tparam RandomAccessIter <a href="http://www.cplusplus.com/reference/iterator/RandomAccessIterator/">Random access iterator</a>
   \tparam Unsigned_char_type  Unsigned character type used for string.
   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] unused value with the same type as the result of the [] operator, defining the Unsigned_char_type.  The actual value is unused.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
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

  template <class RandomAccessIter, class Unsigned_char_type>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last,
                          Unsigned_char_type unused)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last);
    else
      detail::string_sort(first, last, unused);
  }

/*! \brief String sort algorithm using range, allowing character-type overloads.\n
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \tparam Unsigned_char_type  Unsigned character type used for string.
   \param[in] range Range [first, last) for sorting.
   \param[in] unused value with the same type as the result of the [] operator, defining the Unsigned_char_type.  The actual value is unused.

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

template <class Range, class Unsigned_char_type>
inline void string_sort(Range& range, Unsigned_char_type unused)
{
  string_sort(boost::begin(range), boost::end(range), unused);
}

/*! \brief String sort algorithm using random access iterators, wraps using default of unsigned char.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>
   \n
   <a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
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
  template <class RandomAccessIter>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last)
  {
    unsigned char unused = '\0';
    string_sort(first, last, unused);
  }

/*! \brief String sort algorithm using range, wraps using default of unsigned char.
  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>
   \n
   <a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] range Range [first, last) for sorting.

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
template <class Range>
inline void string_sort(Range& range)
{
  string_sort(boost::begin(range), boost::end(range));
}

/*! \brief String sort algorithm using random access iterators, allowing character-type overloads.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>


   \tparam RandomAccessIter <a href="http://www.cplusplus.com/reference/iterator/RandomAccessIterator/">Random access iterator</a>
   \tparam Comp Functor type to use for comparison.
   \tparam Unsigned_char_type Unsigned character type used for string.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
   \param[in] unused value with the same type as the result of the [] operator, defining the Unsigned_char_type.  The actual value is unused.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
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
  template <class RandomAccessIter, class Compare, class Unsigned_char_type>
  inline void reverse_string_sort(RandomAccessIter first,
                RandomAccessIter last, Compare comp, Unsigned_char_type unused)
  {
    //Don't sort if it's too small to optimize.
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last, comp);
    else
      detail::reverse_string_sort(first, last, unused);
  }

/*! \brief String sort algorithm using range, allowing character-type overloads.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_integer_sort.htm"> windows_integer_sort</a>
   \n
   <a href="../../doc/graph/osx_integer_sort.htm"> osx_integer_sort</a>


   \tparam Comp Functor type to use for comparison.
   \tparam Unsigned_char_type Unsigned character type used for string.

   \param[in] range Range [first, last) for sorting.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
   \param[in] unused value with the same type as the result of the [] operator, defining the Unsigned_char_type.  The actual value is unused.

   \pre [@c first, @c last) is a valid range.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
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
template <class Range, class Compare, class Unsigned_char_type>
inline void reverse_string_sort(Range& range, Compare comp, Unsigned_char_type unused)
{
  reverse_string_sort(boost::begin(range), boost::end(range), comp, unused);
}

/*! \brief String sort algorithm using random access iterators,  wraps using default of @c unsigned char.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms.\n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
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
  template <class RandomAccessIter, class Compare>
  inline void reverse_string_sort(RandomAccessIter first,
                                  RandomAccessIter last, Compare comp)
  {
    unsigned char unused = '\0';
    reverse_string_sort(first, last, comp, unused);
  }

/*! \brief String sort algorithm using range, wraps using default of @c unsigned char.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] range Range [first, last) for sorting.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.

   \pre [@c first, @c last) is a valid range.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
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
template <class Range, class Compare>
inline void reverse_string_sort(Range& range, Compare comp)
{
  reverse_string_sort(boost::begin(range), boost::end(range), comp);
}

/*! \brief String sort algorithm using random access iterators,  wraps using default of @c unsigned char.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] get_character Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.

   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
   \pre @c RandomAccessIter @c value_type supports the @c operator>>,
   which returns an integer-type right-shifted a specified number of bits.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
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
  template <class RandomAccessIter, class Get_char, class Get_length>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last,
                          Get_char get_character, Get_length length)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last);
    else {
      //skipping past empties, which allows us to get the character type
      //.empty() is not used so as not to require a user declaration of it
      while (!length(*first)) {
        if (++first == last)
          return;
      }
      detail::string_sort(first, last, get_character, length, get_character((*first), 0));
    }
  }

/*! \brief String sort algorithm using range, wraps using default of @c unsigned char.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>

   \param[in] range Range [first, last) for sorting.
   \param[in] get_character Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.

   \pre [@c first, @c last) is a valid range.
   \post The elements in the range [@c first, @c last) are sorted in ascending order.

   \return @c void.

   \throws  std::exception Propagates exceptions if any of the element comparisons, the element swaps (or moves),
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
template <class Range, class Get_char, class Get_length>
inline void string_sort(Range& range, Get_char get_character, Get_length length)
{
  string_sort(boost::begin(range), boost::end(range), get_character, length);
}


/*! \brief String sort algorithm using random access iterators,  wraps using default of @c unsigned char.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>


   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] get_character Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.


   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
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
  template <class RandomAccessIter, class Get_char, class Get_length,
            class Compare>
  inline void string_sort(RandomAccessIter first, RandomAccessIter last,
                          Get_char get_character, Get_length length, Compare comp)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last, comp);
    else {
      //skipping past empties, which allows us to get the character type
      //.empty() is not used so as not to require a user declaration of it
      while (!length(*first)) {
        if (++first == last)
          return;
      }
      detail::string_sort(first, last, get_character, length, comp,
                          get_character((*first), 0));
    }
  }

/*! \brief String sort algorithm using range, wraps using default of @c unsigned char.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

  \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>


   \param[in] range Range [first, last) for sorting.
   \param[in] get_character Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.
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
template <class Range, class Get_char, class Get_length, class Compare>
inline void string_sort(Range& range,
                        Get_char get_character, Get_length length, Compare comp)
{
  string_sort(boost::begin(range), boost::end(range), get_character, length, comp);
}

/*! \brief Reverse String sort algorithm using random access iterators.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

 \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>


   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] get_character Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.


   \pre [@c first, @c last) is a valid range.
   \pre @c RandomAccessIter @c value_type is mutable.
   \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
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
  template <class RandomAccessIter, class Get_char, class Get_length,
            class Compare>
  inline void reverse_string_sort(RandomAccessIter first,
    RandomAccessIter last, Get_char get_character, Get_length length, Compare comp)
  {
    //Don't sort if it's too small to optimize
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last, comp);
    else {
      //skipping past empties, which allows us to get the character type
      //.empty() is not used so as not to require a user declaration of it
      while (!length(*(--last))) {
        //If there is just one non-empty at the beginning, this is sorted
        if (first == last)
          return;
      }
      //making last just after the end of the non-empty part of the array
      detail::reverse_string_sort(first, last + 1, get_character, length, comp,
                                  get_character((*last), 0));
    }
  }

/*! \brief Reverse String sort algorithm using range.

  (All variants fall back to @c boost::sort::pdqsort if the data size is too small, < @c detail::min_sort_size).

 \details @c string_sort is a fast templated in-place hybrid radix/comparison algorithm,
which in testing tends to be roughly 50% to 2X faster than @c std::sort for large tests (>=100kB).\n
\par
Worst-case performance is <em>  O(N * (lg(range)/s + s)) </em>,
so @c string_sort is asymptotically faster
than pure comparison-based algorithms. \n\n
Some performance plots of runtime vs. n and log(range) are provided:\n
<a href="../../doc/graph/windows_string_sort.htm"> windows_string_sort</a>\n
<a href="../../doc/graph/osx_string_sort.htm"> osx_string_sort</a>


   \param[in] range Range [first, last) for sorting.
   \param[in] get_character Bracket functor equivalent to @c operator[], taking a number corresponding to the character offset.
   \param[in] length Functor to get the length of the string in characters.
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
template <class Range, class Get_char, class Get_length,
        class Compare>
inline void reverse_string_sort(Range& range, Get_char get_character, Get_length length, Compare comp)
{
    reverse_string_sort(boost::begin(range), boost::end(range), get_character, length, comp);
}
}
}
}

#endif

/* string_sort.hpp
fxhWavoMogUyH+g4UYmVLv0QQjls0irXe1eg02qvoPhdG9DWTS3QmwlFA0+LnzYel/7E1Z5R/9MwHJ9AWWI9KzKJ2EEG27sAgbuIKi3fRbQqdT1NzH+bDiNGPyZBn9W/TT5M4Ydlmn+v7t+m+ffBuXZyoAgZYp5Qo2OEFum7g5q/BlnEzZ+kwYiEUuv45ZO1WoAQ1UY6k+QygaorIgTQ2vXX6g14nAtlhPucOlWIT6qabRyIYKB3BbBIpY9skdxV7mqAbu+KbMbOov6F6Gb0OwPWNShymx5YRkeFFlgbDawtoU7TtUTzv6Z3KwGSmsM8A/PzdH2xkoEIEOvVYn0yhMOTG5U070yP0gPYCp2DOwpqUwONvsDe+alaYK8+uSl1i8+/jx78+6hPyHmh7m9gtvW26DUpabGcpOyp/iYrs26NgbecepBqAMztwoz8FnCZxljdhC2ppes00oGntSKHWPQ3erNdnOibcFsqI1KOeR1apAhErXvYPGL16tXsL7ZhtTGxmFEuWjWMoxJoIFR0a1A42w3D3CeaxPI1ieVrvLNMJI8W9OgyXteXWoDyAhPJPzI+z0YEqNpX7yYRouV1GM9lUIGhBf6e5AyLi9+kMxlMjxdp4mjut65qI1IOHOa0VW1EhSfp690JoPfVHVKrSj62vPGbVBMTGZtJpL9RA96FklaDB925X9DUScqdOUS99J4g52mwCKQ49tcSOV+3f4tF91+RSMTdZ5/GHJ/t37/j015lJv1bt3+HmJ5OpGeRQ+/4/D2iNyfQk3YFlTcTeT9rTNZ10HvmoBF+J+H5NPg9mcPi1JnHEnPiLhfsC5N7xLNF6+kZ3qtAiMZbiHQcdlyOiD6XVtj+mu0Rc96Mq1llyBGfRaBjMPDoD3UWLqdGnAZDER7nHes6DZmeomUTMfdNglEH1lYSow5UjE3tza8yAVPtEpTLLByhzsFZrgzpbzMu1pdbl68XO3W7fqkMkkLtaJHHAHYhPMcx9TdTwmFxOTVnpincLBEX9UesNTb3eoK+DVV4XqUuLl9vSUWDoqeVQ1FD0v37bOstLeoZekO58UfIAEJS+jX1lJdN/JKVcMec8hIalGFbBZxtijNOecvmQ7XM/6/BMW/p4wAoS6HILsVhixjnKz0ixkVKWsQ4W82Unj/W5J0wQSV6LeVilsjuKNP9YwYcl4j7RLNfK9aZ9feScafKxI4tqbbYKLNnC6zXzugS0OyxL6yG35r0Bq7BYn/H7G+VR54FEBL4OAxMTK1Xk/UIWcNLn6ZB4EcYK3TNmXVKjXfg6DSlvqajgR6ShnnNzm6TMqR4LMkq0nSYtWJvmtTv6EcomoxF9fwbLIS16AqNv05IV2jd1S9ihTm6TuIi63WRmjasPaUv08NpB+khWOF8ONNjTGR9tXBOzcdz6Rzs2QuigHAPolkKDohX7jHgdV+3n1XeGZ3cOFF+ESysRrjtdMrDvRwOjKyRcDr7PabpjoeQlwZjoiNSeRBkmPovdiZdhdK2igd7JWJfbLiGKNLylsd6pJ/EUT7Tuwj7Se3jTQPzi4YtkOm9yqHXLTib0IrY4FNfe+RrOpicCXKJ+u1yJfXbBky2Iu/Ufmf1hAiI+y3W3232Gl0uMDg7NOa532neyoMLLjI9s4nX7zZY0fyvPblPUR0ViKOzDEiREuPg3YhWqM3wAndE2WJuexPw51QUEmDS94jNr/EEu8rMYr6+mwmy92OPiXGvggJ77Fng/MyVzX8QvxxEUGKGkc1TeILL9MXIReUESvWnkalM34w/hHt7I5unc6aBUot+Yh6hmVDdSzPe4qL3EEhi/DaYp6fKNyEgXDkzp1k6va0eKYP2cn3uKsTrlVX66t1VdjwtQXWl+gr8IZrbt99dDQm+lytXbkdYUCp/KddIMPJZABF7WTTQpjfq6byipqewpkZHVGfd9BfOwzl8WN8ZFKNmpNvKyihjqtW0cA8ja9bHjDtC/6tMdiX263gXGYygElklqprcBmajfaJZU6leblU1OlHVe+WJqszxOV19UC6YcX66DX4isxR6gTh9WyMbeDpCZcrw6Ov4NnKFTTnL6q7eS++w7rFhfB2qta05JKR5gsUyeaVk4oC4lI7WDKhdTKclIWZsFSP+EmfBLXK4UFWBEcvR91J5zPazge1Xbcy1uH59xhPcbLYky+LQ2k7DtwHLsjIWfR3rDT4A/+llzcf9QPXEuSewtmO7TbBNuHGkwdAP+ToUF5V7j28zvl4Q5q1icmP/QKWW6g1i/l86ZezU/wBdgkJHMDNiGMp58iPlrLLoUl7j98gKt5cGzYTJd9Hmq4/1LTWfv/wtPS/GR8XTkvQjWIRjim6kJAd+yuptxdirxdnoYr0dDy33rbQlf+KIC3w4/xTKUl/o7I2lan2GtJYnKkz1qNN+VnGaz5DWMt36LIQYm2iA6HjeFo+xedPqkxQ7ORsqFGdXJEJxFpw2GyoQx25PZHOdnA0nx0MxBsIwIk/ikXkka7Tdd4Jm6cdXQBk5xXTK6tuu9o7H8ybqPaq2xVKjsyaxKnBCD7iLTxSYQyQV9xIVFxTueGGJ+OBRtTXmgSSRdbUfZ0++bVAVYj3jf8wQS/6RkYhohSbt+LfVegbPFW30SY0fFFpTNxdH2usGZalooJaQYk2t1dRtmtqgqbugmcyKQ11Yu0catepCIgGi/tdk7PLXNHW9RkQLYu0hJHppWTR6C2UQ1/Y9YVD3vW8i1hnhEO8g/pz2zs1QMe2lV1fgqRpPtHN3im8uhcrFQoLpl4l+q08YYZsZ9a529Wrds3q1+fQaEwxv8megGUbqXGBBewxAnvHywzcTIg72orHsRcIsjFFA3iViOgIsADF09XGDowCi+WbIdg22VWg+uux9s5CbLMnKVP9Bzd8ac0m6MtXfDOHKEzhTfR8rTj0CMVosbdVcOjX3C5ovj3cUUHvF+VmjRPijEXBsP3uuGFZ5FWDuRiNgFgcrwEemvkN3We+IRsDNDVaA5xuNgIUcrAB7Wd+pvTOGh47DzA3twLh5MAUR8HyDFWANRyPgJAcrlpzJJdo5Uw40kz9WXfXVuXQHVnTMFY2A+6xxinyXSXdgTuMdeNAap0jJY8GO6ENYY94R7ifrtOg1GPY9Qrn7hCHufoEQysK5WjW87XrXscShG1M7sV7R6hHoKzVk6JeG8Vk1es40UJCoGi0apMfP/q09OYn+AAQs+9OaYlC3DifGZjFloFMm+t5XJ8iCPmtEUQeaDYOKcDY9ycUVOrRqFCCLA92Udv8Z3nUsNe+3igXH1XizCtJjmfUA/zZF8X0SIdX3aIbtAOfVqkfGMxBN9VNHhk0WovMLWYr3TQyDMlN2a3+dRbSd89lDOJ/Nx/v7yfcltKsgn33t8hSWBBpvYryi1Q6M8Zsojxbmm6gjKC68FDZIareWaTSXnzWay9BtLvedYswXsNfSo/xoZ86IERwmG63zkvDOcsx3io9X0c6bNVeP4MjTONChVg0rUd92d9V/gEHzEwEbek4HrunUC50aG5Jq1VPMjNsoI4GtaCXiThbsWK0FVmqBF7XAGi2wtr0wz+6uehTQ551CLgrhubR3oAuvqXs1dZ+mNmpqk+S0YDe+g2IR1Ys3JpyUeOd4lF5mH9M1jtcY9ddy5MWofyWiFZvuMoZCQWZOobt6MN3IwI56KoqyBsZYBl8nLSdAJ3AJzSeVcNCOD4dxZlF/EL3M5jFDo44UMntA6WUp0lrB7qyB5oiTwSko6A9MgGnVaIO3GuvAXQX9SZ3DOxa0E8asEFY92v3I2xgbZmW2rMXKjvDKLqKjfqD+JjaYt8gx313PJYG+aFmMD97MlW8WPEAZM/Q3c8zHT/Q3OWQmZ4/NoJf94y/nuxKlxFzJGb3cS/UiLz+p58pWHrmK+ptiU7P1d3jJjHfMZzQIVHuKfqSgVo8C3PgOKZW+NuU+uVSD4qOcFJsECoTJ3PObE+a27qLMQHtg8en3wG7sgbWX/ewe2G3tgfMLUmjJjuE3PNMMdIw3eb5SWX2Um0eTj87Q5PMiMJZtAqyvxhxH3mGLaHd11nHMia6D7PTq4BbN6xbhv4Z3FDv5dnlHQRLprkKr9Qhe+bbPm+9dx8zX2SZX/rcAP4v+CSBdUOs7Ae4j7Y9/gAQ4oZTIoyVIZ2wR84nksonOoZ2zd/Xq4Gpe0avFtXuOG2FYZyOyaNa+T/p6knIHOZMYsgdqvbJtSq53HURY87LN1njM5S6VeSGY40+NN3n70wQOMyFTHzmB1sTlDEqxia3PEbSOYti14rmSg86HdIeLQHnIxrSWuOiPCalUbrJrHjCdwZ/2HXM/AtMEH0vL3VHoSIJqRcjS3Vp5q1beppUf1so7jGWzUiX+e91XGDatUhC15PFtBlNUdUb8h3tE/B09wnZTs9bI6uQgzMpknbPASdN1BTtKCuRupjPn9gM48cXgu04Am7nQTC2hVGOWQ3eWcEE8rOw+qTReMPwn6X4BSiCu3PqrbUCS4tIZNmjq/nGaTR/8IhjDO7xLR2C3+qKLK0DeakufdrECCVYOQzTjQ33xMkkU9mO90DXsTWjS951G5CW8IAoOvMrq2vt6RjaDXWmbN6+6du4MkAGXfckY2UR9bt6ibwzjuMHG49Iypg+VQDjEkJ+p4IdDiQoqO1msg2pYlxcrIr2rIkQYG2sZUAl9s0n+QJx5LsifK4n8OYMNQKvh7SiNUJSysviIsexInLGSFwRE3sxEurgnrZa5fzBVXSeOoM7EEOERH3dxWJWwFijT52fWF0G12Eb1pImdz7PwGUq2PxrGEMM4Bhe1BHR7Agjr/YP80ngc3UlS2WW9JZqmyLGU+dCSpFK5uHnx4jJkcd8akWN2tVtPcG1iPSg7l+yhkiMNKV0LT3IO2ToMVm+BRjH3LSKzFmN1R25ttiVLtiEYChtqM/V59hc8gZVxk+TeejDXV5J3T3dfybA5jsithFcX52qBJhyT6vkIm1mrnNNFDp4l5eC9oIcQaASenkc1G1Dhafb5O+55CgaFdCRtHsPshbjoW2pfBrrB79dpKYlSfX9kI4vC1ZsiOsvAET2NhamwAw2n0H9sjtVytxS0F4V4r9xrbkK+gWVJNIKPgnLBm0XN1EZBmG7ZcA6qi9twdnHmReQMt4O5s6EydzU0Hs1muasvskP42f5imk3KDM/EASp1jDxsCyn1fBDoFPqHut8VaXZGNmIPwkmXFhkOcHiOzpDchOfQYOldQmB67DGCCFYX9L6yE3ob951GL3M1OOA7VxuPN7FqkRwZHgGt8qCRdZD1u9XScIocJW0j95uHyoRW1kCddjgpjzlsp4wnLDJTUftG7E0mrCCniuCJT3vphwG7FeYJBw0lw+sX7uVy5uOw60/vAnaZ7LgS5lNJzQe4p/g7847QZPbHNrcV5gGbMXKRl3j8jGV7cU5SU9KlTQE3gnL2BWR6ronO/Q52dHG/nBReb8ayDtYD0aAi4a6agVepzCuaS2PVCz6v8OBouQrT/Ksc2unK1bSA7coYHAGHPiXQ3egt71SuiY6ze/2dyhg53SwwhfejnfPt18pd52uoTNHraLNT+yFNl/mgBgZBzAii83Jw4HhKoksXUn9K2PjBAxS23ElLOd4UfXsLY2BxjjeBJn0s9LwRTGNta6fB/t3oRPn9s8wjvNiMs/EYvWIt7aBYTLfBCmiviieeNTnaJrPZBeX/sUAdYIHGJ/JCVDcYwM8Ur3eBih+axV/CZda8SGVeaZXZK5GTKv6QtjoYXvEpXgVsgENG0bSA0Y7zihVUVu0dhKgdmGpDubL6gCoYvPstbZUx0FZpjXH/sllki9GALiZ/CXmvfRyB0b/Tp3+BrJa1Dl5AfbECcdbvCRSCW/ajxVdthebBs7K8vpbspUdCxF7dru6WLSs4ELuN27LBastrtBBSz7XCZFwrmwLhgBlP5OI/mKPhoca4dM+4UowzDFTQiXNlpX0qqk8+aaj5T+EAIXAe156gEUzoBbUWJuBSJCAMOknAuhnLhMmhUk1tNj45VYVtB+tjbiPYc2R/wQdaoFbzN/i2VKZqkxvMhbrFXXUZVkGHnbDIp4C0uKtBqfjec1dF7NbSk3LpJtgpg4ug+ds0/2E6TBiSfCKlyrFxegN1bpx+LXiMO5TLI/cV2tR81jAYwgz/uwmX3AUWz3ynHtjrC3QsGBRVd5l2/Tr1wH+QNuKGWC9x59OdRn6gg9Lo+Ek0QW9IpUd/wzNHjkZuPWjTlzJliHbFprFq4nZLNfGdyP1UuT9yP1V+ZfQeq+LqWiISJu/1Te6Yl0q16ZObvJMPLhiiunV1m0/dNe9iffI+3/fzw12aBQXHVbGRUbVVP8ZJ1zu1DCKutYCI9aacZmqGRul+EakUBn3krv4WOynQ5A0cdFfPBk3X5XvK2cJsr8C2/MCu/Mnb4gX53pu/LlpsR5x4ZIz9VQ6vNvkgJgtSJIyzu+oTaKjJsXZXvYeHyQ2JIfZN3juvnx5o9L0//zw5rjuoVS3/QZX+g/HKwAQa59DGuehl7EorWd+S79+b/x4676uj7PNdhZzRpY1zxAbEv4n1KuUFDIZT5FYBj0KVwv2IZgMBexpTM+TzMmKs9JPLj04GNaMYaHX9vFQq11tZqwzVUyO1x73+1vmpsEsLHNboOV0b5/TVzb+YxjhS9xONyrnUBM7WhmxteqBDQwLlc1G+7tr1LuS73hHh+lChX/i4TjWD949J0wfolBfySMrcIG3FwsNqVDAWIz9kMGPxUMEBU8Mzy1Rr6Rk2jKxl9HnLOSzIM5ZVsBDPXd0XRP4KYNju6m5SyJdAXnfLz9Xe0mFBmch4O83W0gzxwscwuoYvzF2s8LwXCltxX5iGuhfn3C7rnJOqObTutcWMO0DtlWhT4fwBLHFO6qAkHIU/fk9JPQFOfLuVwdoovtup9NUf42xS92Ci2E3Z+GjhE/4Tb3mT+xHYn0l1K9A/HxHJ5d8HVREO+sqI8820qgYZapOliLVbLJblGJ+09ECuwD72DIHV+pONvUsY6pWRSuqQlzmXtEC66LNggTBJtFtEn8KANOsBgjeuSG1apC6NbrSA513pqopO8aaKr69gbU64HfvDX+F2DKyaYWwvNeEF+r6xoJZO+idrWQSRvRwC+3164RiA57C9otfV1Oh7HUbWyE/gb5S+3seyWWlJPVaOZPHcs9Gc6/YxrtwvMjdIJCx9nJX8cdjGhmc74U4jRfRvNLW7qGWVjaKUWiL+dijDZmk6E+h2mSG9gJiIxd9Rfsm0oS4qkyOb5ZF0g6mZOYSPryE6NEKSossTkQEiYCVIkloV6nOfxPqJS57oZNWUblLrOFhM72iDuCylFHmY5HUhi6MECQ/pm7FqCw4E5XwYWa6PQcqqv9bHYg2aK/+3kc0818qvTM2uaZbX1k+I/MIqPaivkGtGrlXfVnU0IT+i+4fAnqTEBxNwDoGV/HHTg2LjAJdtaqQjfUFvY1QNzJeyHI1sUxmbSbQ6jhuC+IIdLzfJiiQCG10KNnkytS5OXAvHRZSxlRZCQiOa2s429E5j1DaqIPYcNWfnV50J97CD3jQ3fnHNC9j4D3+HjU8gbS+RT/tgAZiqVTaZiq1ti77mw/XzQe0FtUW0YQnTnBLOFL/W
*/