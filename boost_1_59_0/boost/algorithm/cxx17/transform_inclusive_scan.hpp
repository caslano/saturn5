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

template<class InputIterator, class OutputIterator,
         class BinaryOperation, class UnaryOperation, class T>
OutputIterator transform_inclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result,
                                        BinaryOperation bOp, UnaryOperation uOp,
                                        T init)
{
    for (; first != last; ++first, (void) ++result) {
        init = bOp(init, uOp(*first));
        *result = init;
        }

    return result;
}

template<class InputIterator, class OutputIterator,
         class BinaryOperation, class UnaryOperation>
OutputIterator transform_inclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result,
                                        BinaryOperation bOp, UnaryOperation uOp)
{
    if (first != last) {
        typename std::iterator_traits<InputIterator>::value_type init = uOp(*first);
        *result++ = init;
        if (++first != last)
            return boost::algorithm::transform_inclusive_scan
                                              (first, last, result, bOp, uOp, init);
        }

    return result;
}


}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_REDUCE_HPP

/* transform_inclusive_scan.hpp
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
*/