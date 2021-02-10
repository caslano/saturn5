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
VW5o6KtvRAEr2tJZg4D+DWWltF/Zr9yoUFZRVKtu66VdK3FHEIgerC9165TYx0uS0RB8iMPDJfUdiZhWBE9HUHtFG4+ppC2RG5abVIZMKqyH4HnqlwQRTV1Cs4AlYbIP52rBNma7Ot44o1pMeRqwFB/aFiU3S122i7Fay1W3locuJ983OYxG1hyamAt37JHhJLFSIrNeEb7xsWaKyHls6ZyUtnwpAFMuIWMR/hlbEgq9+UxIVMrSrzToybr5oMC3qJsS+d4h2TDX0EacVlr4Dbhp6d5rG1Y8pWcgB+lYZWqykm+EEEQKwUyld5Uu56ObUETnuuu10QCSjA8mWuUBnS5337nR5bQFRZO97J0iE1X5k4pCljWHw4ZJIN+lo3EtL+kcQhMz4W/NT0woA8Ka5LZlwYrUXILUogwDRBo6PdX22rwWFwFtbE7m4y2IwCFAJUgV/fiaAbLPdAyFrWC2tXvXxiKHo5uypWSAqmgZEJA7hpGnST5pNKlm0uTS7X9M0ltefVhUHkI3MijZ7eP0lpOA0W9FlMCJyGh3m3V+q5YlcqOyPPZKVcHcQ+mVs1PAWmI2cxkb+KlJ9p96q8oFy/U91mlKjU1IZ3E5SkX06xO02ll8L5W8rEyEtzyZZiid76hjMXT759A+Y5r3
*/