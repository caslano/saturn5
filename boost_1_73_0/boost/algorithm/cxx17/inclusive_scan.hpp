/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_reduce.hpp
/// \brief Combine the (transformed) elements of a sequence (or two) into a single value.
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP
#define BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, BinaryOperation bOp, T init)
{
    for (; first != last; ++first, (void) ++result) {
        init = bOp(init, *first);
        *result = init;
        }
    return result;
}


template<class InputIterator, class OutputIterator, class BinaryOperation>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, BinaryOperation bOp)
{
    if (first != last) {
        typename std::iterator_traits<InputIterator>::value_type init = *first;
        *result++ = init;
        if (++first != last)
            return boost::algorithm::inclusive_scan(first, last, result, bOp, init);
        }

    return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator inclusive_scan(InputIterator first, InputIterator last,
                   OutputIterator result)
{
    typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::inclusive_scan(first, last, result, std::plus<VT>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* inclusive_scan.hpp
FuwSFNkqNx0iogv/6HM79XtH6LOT8cjUD4S/Hbuv4jk/bpNNiYwNOBtLUiIW75Ib/lGJg7mGq1wZzHX+TBanNS78o2yVKUdlGsZM6rz3/FlNxglD/XOsJj9KMxURG/DGImBqhGD3ul1rfIhjIa66+QguXCBF6eKFs4iGz0efVcO0u/+sh7v5ZxChZ7lc0N5MAwmx1YKNZ54+P+rFGZsR+qgyL73ILagTWY1/uR4UIU6rcnGh
*/