/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  exclusive_scan.hpp
/// \brief ???
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP
#define BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class OutputIterator, class T, class BinaryOperation>
OutputIterator exclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, T init, BinaryOperation bOp)
{
    if (first != last)
    {
        T saved = init;
        do
        {
            init = bOp(init, *first);
            *result = saved;
            saved = init;
            ++result;
        } while (++first != last);
    }
    return result;
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator exclusive_scan(InputIterator first, InputIterator last,
                              OutputIterator result, T init)
{
	typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::exclusive_scan(first, last, result, init, std::plus<VT>());
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_EXCLUSIVE_SCAN_HPP

/* exclusive_scan.hpp
k/RCuJV/x2R4MmYrwS8XZIMqyivJIKQL/m47GrbptRptCvRozSfqHHTMiDHJ30q4N3bVLpm33IQX2TvZtB8xnrRdDYx+G5MvE3DztWzSHlmITvGmHL4VvgsSi51845TaMtookgYwbDvFcC7BuYls5LrJVnmj1CdefrHJvTjkXAz+1Kz6Jl5nPcwNmHiDU75R8Q21/OhQwh16hL37sKkZRthbnPjpSVdPEQ12taB+IHlln5oDy0Lv941s1Fct+xREF1gSjL/0A2d37I6VXxtjf/Ixg52N8diUzeXh0ZjOsZ57DpjjwEwVK2PTEYBTKlDa6cStnbLlMXW+rlP0l6WjKSdHYjyM8XnkoFSNMXKD93qQH+fVLLVEH1mS8DC19TsuxPiV0+htG4ZvrTUCz0b49cG0pntG0s+Ocbue5OqI64hW9NxRJpQVW6oyjVlDxpMsKwf1t13tIvr+z5FpwJgxkLoNc5576CdwhyU6amuQ7VGV3JabXav9vYsAZ1ehWAOQefs6JBfysIRzt0Yo8gy6YpnXQy8lyBqVHB5ifDW/1CJKyvrT+Ej3kwgcvyYwVP713rksNYqrLPal6SFWo6dS2HI+9fLjb+PzISXhIGurO90HRd/ySBHeoZ0dbAueJGXYTue8PxNVtW1dGdMCVovB2fPTj35fDtMkpGbrboHY194hn2DfzG/fLDitKeku56NrFYj9xvfCX9wtMFkF
*/