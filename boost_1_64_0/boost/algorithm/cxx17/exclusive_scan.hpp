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
VR2eCZI/Qh4bt5egNVx4YyqZWG+boZQyWVtXWG4MLcSeg4I4I+WWfDV7lllBkI9LNk5xWanvCBs+DzYNZmnxinxidtkPauoluWbw6MS15RhAALPTNJxMBd9GJ7vNxowzvQVeMPhPbcxUC73zYOWMVOuPwoGo9K1EIQk/Bz1rPSnS9CxJmhxog2VdrNa+SuT+h5vOD0hcZcu9nkWpYV0iqU7FbNl0AO/LXPeIrZMfyZZdLZtwrq0CelxktGlmmtTlQlGbONwuM1m2SB1b3ZYmPvWXjoW8+/ZijqadlnUF7471Dum4QE3OIgo1JoZSQSy1DqdJoziC/n58twQ7XAEPubTxmOfcp0GRpyyfxeW5V/QoTvjaB9T8Oq2iVTTMLiLOm1xx5muUiy1NTqR7NYQuL/31MeJzcjvAuhZVZpJClgBKEXzuPIibTemec7oy//ysEBADm/nKiTyQWT8s0eEB6IaSsrj1OfqpIOumrOG5zpNDYmciNFpNamXtuqutY+mWIutR0iQqwpaalK7eKjb1/fl3K6xdj5Xc4gtZKo9DWCc+pMPqK70LMWwANQ==
*/