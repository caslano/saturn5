// Templated generic hybrid sorting

//          Copyright Steven J. Ross 2001 - 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
float_mem_cast fix provided by:
Scott McMurray
 Range support provided by:
 Alexander Zaitsev
*/

#ifndef BOOST_SORT_SPREADSORT_HPP
#define BOOST_SORT_SPREADSORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <limits>
#include <boost/type_traits.hpp>
#include <boost/sort/spreadsort/integer_sort.hpp>
#include <boost/sort/spreadsort/float_sort.hpp>
#include <boost/sort/spreadsort/string_sort.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {
namespace sort {

/*! Namespace for spreadsort sort variants for different data types.
\note Use hyperlinks (coloured) to get detailed information about functions.
*/
namespace spreadsort {

  /*!
    \brief Generic @c spreadsort variant detecting integer-type elements so call to @c integer_sort.
    \details If the data type provided is an integer, @c integer_sort is used.
    \note Sorting other data types requires picking between @c integer_sort, @c float_sort and @c string_sort directly,
    as @c spreadsort won't accept types that don't have the appropriate @c type_traits.
    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.

    \pre [@c first, @c last) is a valid range.
    \pre @c RandomAccessIter @c value_type is mutable.
    \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
    \pre @c RandomAccessIter @c value_type supports the @c operator>>,
    which returns an integer-type right-shifted a specified number of bits.
    \post The elements in the range [@c first, @c last) are sorted in ascending order.
  */

  template <class RandomAccessIter>
  inline typename boost::enable_if_c< std::numeric_limits<
    typename std::iterator_traits<RandomAccessIter>::value_type >::is_integer,
    void >::type
  spreadsort(RandomAccessIter first, RandomAccessIter last)
  {
    integer_sort(first, last);
  }

  /*!
    \brief Generic @c spreadsort variant detecting float element type so call to @c float_sort.
    \details If the data type provided is a float or castable-float, @c float_sort is used.
    \note Sorting other data types requires picking between @c integer_sort, @c float_sort and @c string_sort directly,
    as @c spreadsort won't accept types that don't have the appropriate @c type_traits.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.

    \pre [@c first, @c last) is a valid range.
    \pre @c RandomAccessIter @c value_type is mutable.
    \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
    \pre @c RandomAccessIter @c value_type supports the @c operator>>,
    which returns an integer-type right-shifted a specified number of bits.
    \post The elements in the range [@c first, @c last) are sorted in ascending order.
  */

  template <class RandomAccessIter>
  inline typename boost::enable_if_c< !std::numeric_limits<
    typename std::iterator_traits<RandomAccessIter>::value_type >::is_integer
    && std::numeric_limits<
    typename std::iterator_traits<RandomAccessIter>::value_type >::is_iec559,
    void >::type
  spreadsort(RandomAccessIter first, RandomAccessIter last)
  {
    float_sort(first, last);
  }

  /*!
    \brief  Generic @c spreadsort variant detecting string element type so call to @c string_sort for @c std::strings.
    \details If the data type provided is a string, @c string_sort is used.
    \note Sorting other data types requires picking between @c integer_sort, @c float_sort and @c string_sort directly,
    as @c spreadsort won't accept types that don't have the appropriate @c type_traits.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.

    \pre [@c first, @c last) is a valid range.
    \pre @c RandomAccessIter @c value_type is mutable.
    \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
    \pre @c RandomAccessIter @c value_type supports the @c operator>>,
    which returns an integer-type right-shifted a specified number of bits.
    \post The elements in the range [@c first, @c last) are sorted in ascending order.
  */

  template <class RandomAccessIter>
  inline typename boost::enable_if_c<
    is_same<typename std::iterator_traits<RandomAccessIter>::value_type,
            typename std::string>::value, void >::type
  spreadsort(RandomAccessIter first, RandomAccessIter last)
  {
    string_sort(first, last);
  }

  /*!
    \brief  Generic @c spreadsort variant detecting string element type so call to @c string_sort for @c std::wstrings.
    \details If the data type provided is a wstring, @c string_sort is used.
    \note Sorting other data types requires picking between @c integer_sort, @c float_sort and @c string_sort directly,
    as @c spreadsort won't accept types that don't have the appropriate @c type_traits.  Also, 2-byte wide-characters are the limit above which string_sort is inefficient, so on platforms with wider characters, this will not accept wstrings.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.

    \pre [@c first, @c last) is a valid range.
    \pre @c RandomAccessIter @c value_type is mutable.
    \pre @c RandomAccessIter @c value_type is <a href="http://en.cppreference.com/w/cpp/concept/LessThanComparable">LessThanComparable</a>
    \pre @c RandomAccessIter @c value_type supports the @c operator>>,
    which returns an integer-type right-shifted a specified number of bits.
    \post The elements in the range [@c first, @c last) are sorted in ascending order.
  */
  template <class RandomAccessIter>
  inline typename boost::enable_if_c<
    is_same<typename std::iterator_traits<RandomAccessIter>::value_type,
            typename std::wstring>::value &&
    sizeof(wchar_t) == 2, void >::type
  spreadsort(RandomAccessIter first, RandomAccessIter last)
  {
    boost::uint16_t unused = 0;
    string_sort(first, last, unused);
  }

/*!
\brief Generic @c spreadsort variant detects value_type and calls required sort function.
\note Sorting other data types requires picking between @c integer_sort, @c float_sort and @c string_sort directly,
as @c spreadsort won't accept types that don't have the appropriate @c type_traits.

\param[in] range Range [first, last) for sorting.

\pre [@c first, @c last) is a valid range.
\post The elements in the range [@c first, @c last) are sorted in ascending order.
*/

template <class Range>
void spreadsort(Range& range)
{
    spreadsort(boost::begin(range), boost::end(range));
}


} // namespace spreadsort
} // namespace sort
} // namespace boost

#endif

/* spreadsort.hpp
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
*/