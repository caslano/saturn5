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
ARRc2OcY69RcWLiLf+N6g35knH9zxFadNIXjmGK2IM5UNT00sYtdNy3wVPr9HtE53eBPr+L27Ylu3aiKrDTvfhjHZvCKTcmuGlNJMZObFe6tX+FUY9fQ3F71zen7Cqpb03nBm1XB9ufGKIlpXTFg7yFzh6xyX9PWUkchBAP15ea+FfB7532UgtpUOrtf1ArF9oWa/MCd3YTaqQI36kvKd6iDfI+LZUeLFp7yVRSTNLee8qBPUxlTsK++5HRlo8L7PieWsOEvFGQFQKnT5PJ3trBoy+0rL3kToTQ38QJBdIAS/xhNR9w0n9RlHjhWYl2meX+EAU2t00fBtIl+iyVS3BRFM/zRPJQdnTm87xPFQ82T7hLO+U/yucXOHq7jOq8bchuc25R2/H92oWY33f5NYhDDLdPOidDPVOhtq753cV34NQeveVutyZVR7hpODQMaKA0fruo9AyWNIpxwzgju5GR3Q/kC7NNplJ744YIG73cnrAMIDeJHCY+SFQ0/3ioRO/mH29h5zniJaoXl6Y6W+2wOAQU7AJ95KW9jWhhn55/ZOq3Fk7OnWcUMOVcWQ+rst20EDMsGRuKeXPUgv0U5yPEm6v4g6IpuFYh5rbHvqjRNcuZHaE9pP1unP1pe92FSLwoUS/intc0JivLp1TzWae64q3W+3m9nAYgKs1ze7BIG0aB+oPkSvEUZhIB6T7McZsQeJIzqTrMcYsQQ
*/