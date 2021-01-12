/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  transform_exclusive_scan.hpp
/// \brief ????
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T,
         class BinaryOperation, class UnaryOperation>
OutputIterator transform_exclusive_scan(InputIterator first, InputIterator last,
                                        OutputIterator result, T init,
                                        BinaryOperation bOp, UnaryOperation uOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, uOp(*first));
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_TRANSFORM_EXCLUSIVE_SCAN_HPP

/* transform_exclusive_scan.hpp
MpKoEeHa1fj2tyLg9WV9FdLqX63kJGq5JNff+Dtr1wLfVHXGc5M0DW1KAlSs0kHVqtWidrRKSysrUlqcyFJLW50IbHMu69AhJIKzQLq0lPQSQeem25ji5px7yhxKlQmFQouv+RgqDqZs0+3WisPHAB2S/b//ufcmrez5W/u7ueee85336zvf+R6Jy6zx45rO7n8lOvXqyHjREXbjay7bNCh1xNZKHsW/Ga5/DObNITMnGm9G
*/