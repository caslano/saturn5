//Templated Spreadsort-based implementation of float_sort and float_mem_cast

//          Copyright Steven J. Ross 2001 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org/libs/sort/ for library home page.

/*
Some improvements suggested by:
Phil Endecott and Frank Gennari
float_mem_cast fix provided by:
Scott McMurray
*/

#ifndef BOOST_FLOAT_SORT_HPP
#define BOOST_FLOAT_SORT_HPP
#include <algorithm>
#include <vector>
#include <cstring>
#include <limits>
#include <boost/static_assert.hpp>
#include <boost/sort/spreadsort/detail/constants.hpp>
#include <boost/sort/spreadsort/detail/float_sort.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost {
namespace sort {
namespace spreadsort {

  /*!
  \brief Casts a float to the specified integer type.

  \tparam Data_type Floating-point IEEE 754/IEC559 type.
  \tparam Cast_type Integer type (same size) to which to cast.

  \par Example:
  \code
  struct rightshift {
    int operator()(const DATA_TYPE &x, const unsigned offset) const {
      return float_mem_cast<KEY_TYPE, CAST_TYPE>(x.key) >> offset;
    }
  };
  \endcode
  */
  template<class Data_type, class Cast_type>
  inline Cast_type
  float_mem_cast(const Data_type & data)
  {
    // Only cast IEEE floating-point numbers, and only to a same-sized integer.
    BOOST_STATIC_ASSERT(sizeof(Cast_type) == sizeof(Data_type));
    BOOST_STATIC_ASSERT(std::numeric_limits<Data_type>::is_iec559);
    BOOST_STATIC_ASSERT(std::numeric_limits<Cast_type>::is_integer);
    Cast_type result;
    std::memcpy(&result, &data, sizeof(Cast_type));
    return result;
  }


  /*!
    \brief @c float_sort with casting to the appropriate size.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.

Some performance plots of runtime vs. n and log(range) are provided:\n
   <a href="../../doc/graph/windows_float_sort.htm"> windows_float_sort</a>
   \n
   <a href="../../doc/graph/osx_float_sort.htm"> osx_float_sort</a>



   \par A simple example of sorting some floating-point is:
   \code
     vector<float> vec;
     vec.push_back(1.0);
     vec.push_back(2.3);
     vec.push_back(1.3);
     spreadsort(vec.begin(), vec.end());
   \endcode
   \par The sorted vector contains ascending values "1.0 1.3 2.3".

  */
  template <class RandomAccessIter>
  inline void float_sort(RandomAccessIter first, RandomAccessIter last)
  {
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last);
    else
      detail::float_sort(first, last);
  }

    /*!
    \brief Floating-point sort algorithm using range.

    \param[in] range Range [first, last) for sorting.

  */
  template <class Range>
  inline void float_sort(Range& range)
  {
    float_sort(boost::begin(range), boost::end(range));
  }

  /*!
    \brief Floating-point sort algorithm using random access iterators with just right-shift functor.

    \param[in] first Iterator pointer to first element.
    \param[in] last Iterator pointing to one beyond the end of data.
    \param[in] rshift Functor that returns the result of shifting the value_type right a specified number of bits.

  */
  template <class RandomAccessIter, class Right_shift>
  inline void float_sort(RandomAccessIter first, RandomAccessIter last,
                         Right_shift rshift)
  {
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last);
    else
      detail::float_sort(first, last, rshift(*first, 0), rshift);
  }

    /*!
    \brief Floating-point sort algorithm using range with just right-shift functor.

    \param[in] range Range [first, last) for sorting.
    \param[in] rshift Functor that returns the result of shifting the value_type right a specified number of bits.

  */
  template <class Range, class Right_shift>
  inline void float_sort(Range& range, Right_shift rshift)
  {
      float_sort(boost::begin(range), boost::end(range), rshift);
  }


  /*!
   \brief Float sort algorithm using random access iterators with both right-shift and user-defined comparison operator.

   \param[in] first Iterator pointer to first element.
   \param[in] last Iterator pointing to one beyond the end of data.
   \param[in] rshift Functor that returns the result of shifting the value_type right a specified number of bits.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
  */

  template <class RandomAccessIter, class Right_shift, class Compare>
  inline void float_sort(RandomAccessIter first, RandomAccessIter last,
                         Right_shift rshift, Compare comp)
  {
    if (last - first < detail::min_sort_size)
      boost::sort::pdqsort(first, last, comp);
    else
      detail::float_sort(first, last, rshift(*first, 0), rshift, comp);
  }


    /*!
   \brief Float sort algorithm using range with both right-shift and user-defined comparison operator.

   \param[in] range Range [first, last) for sorting.
   \param[in] rshift Functor that returns the result of shifting the value_type right a specified number of bits.
   \param[in] comp A binary functor that returns whether the first element passed to it should go before the second in order.
  */

  template <class Range, class Right_shift, class Compare>
  inline void float_sort(Range& range, Right_shift rshift, Compare comp)
  {
      float_sort(boost::begin(range), boost::end(range), rshift, comp);
  }
}
}
}

#endif

/* float_sort.hpp
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
*/