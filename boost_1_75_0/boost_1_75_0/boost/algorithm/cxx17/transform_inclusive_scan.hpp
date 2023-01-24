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
8e3sOV5ulgxD7qNyX9tkyViRvowXUfuTtSeyRo5Vy9RyifLWeoLitiUlC6hwfyL99wtszmC4NevxjLGTmc3PBarfC+rt/WaWSTHgwfx0TpEluUqy8NZLuMpzsmYNKTVUEXXdX0u0lOVimyLXSTniC4WRlgv6rb6TO+uVAoeB5CqDziOP9BUmczwK0r7ZyBNvS0ns1k45oU9wVOK5R7Nfjg+ivy/kSBEJNCuyUQ3bhhivR51iw4MAPwAhX4pJhaIvBRZS8328PwSmHtEr8Ec/Gxr2e0wl/7OVxRCihTkuFZ7U2aRMMVzREF6ukfeSaD0Xkd19l95ircGqEod2APgiGVrGaa/o99HjUZzEz+phvVTOQhs6Q4qAHZTOfS0QLuUp4dUZ/DgIIhWBIemW0DxUEpOKpnfUB9lD+g3XrjSqn0Yy5Hui9QnkjWiaWv7o8yb1Nsd2FKS0OncvlvFz8ku1WbBqNNVIboBQaiAXaNNtsL/SmTan7nrMi6HdOaCy+F7nJykYErcOb75c1QIL6sv4TCmsgAZBMDkKdVYeV7oRdl2nNRHYzJgLYEkqChtq8jBY2uF5ZmFsQMXjh2NIsdKJAnTffiwbqpN9BGl32F2T+0KKZkuGYmR9OCyXFA7sfSkqWXJr0rIAiT78xG1Xia0i5logxnhYzFP4WW+2O74VM5Dq3O8seFJKGrZUyVeMQ/NbWNDv+/l5NnQk2O0B
*/