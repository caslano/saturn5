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
c9kkCGv41FqzGbhYKUndGWNeNgG59Ojbn+2iV0TKRSWy7C4GUKqCpUc3FccNiSQ/yARy64kIVGWOjwSMWhDGF4LSJmiujw/oV/YXQmgh9j0BA/jkpeCowCEB454ccGvtKhDZriJw75N+AHesDs2SsMwfK6fudiMFlLNNQsxjLpuYRzTpJKI56YldSRdDDA+cYcFX9jXddXQDAmh7CzeQToOPHkbrZyzdbvLWo8EPtTG03nOQlRc8Dj/Lr2mOHaKRoXqN4joibkEs60qlzEvAmEXypCYobh2xbsy1rWdoh3DKUwj5vo8H+w+r4jdpn1BFXbynBQ+PKr/taB2Z8kipRM8Hdcx6yYoC0I6zoRcLjjEgk3yGA8B4wd/lxv1Ee5B2BYMxsCn07J1C2wpfdaYESx4gGIWOXTh4E3XiYr+Du9vqQ54iSn2nCVB0fUUhDucNzu43SG1l8uoErrQ3maAOexLoInbZUSJXVRAPgDJoTbn2URWvGvYGGDxeJHGWfr4SEFtv92F2cFNFzr5LCVFFc8HQbZS+dtK6L7z8roi6SC3uLKtN416hgpfM5w==
*/