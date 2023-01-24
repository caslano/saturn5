/*
   Copyright (c) Marshall Clow 2017.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  reduce.hpp
/// \brief Combine the elements of a sequence into a single value
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_REDUCE_HPP
#define BOOST_ALGORITHM_REDUCE_HPP

#include <functional>     // for std::plus
#include <iterator>       // for std::iterator_traits

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>

namespace boost { namespace algorithm {

template<class InputIterator, class T, class BinaryOperation>
T reduce(InputIterator first, InputIterator last, T init, BinaryOperation bOp)
{
    ;
    for (; first != last; ++first)
        init = bOp(init, *first);
    return init;
}

template<class InputIterator, class T>
T reduce(InputIterator first, InputIterator last, T init)
{
	typedef typename std::iterator_traits<InputIterator>::value_type VT;
    return boost::algorithm::reduce(first, last, init, std::plus<VT>());
}

template<class InputIterator>
typename std::iterator_traits<InputIterator>::value_type
reduce(InputIterator first, InputIterator last)
{
    return boost::algorithm::reduce(first, last,
       typename std::iterator_traits<InputIterator>::value_type());
}

template<class Range>
typename boost::range_value<Range>::type
reduce(const Range &r)
{
    return boost::algorithm::reduce(boost::begin(r), boost::end(r));
}

//	Not sure that this won't be ambiguous (1)
template<class Range, class T>
T reduce(const Range &r, T init)
{
    return boost::algorithm::reduce(boost::begin (r), boost::end (r), init);
}


//	Not sure that this won't be ambiguous (2)
template<class Range, class T, class BinaryOperation>
T reduce(const Range &r, T init, BinaryOperation bOp)
{
    return boost::algorithm::reduce(boost::begin(r), boost::end(r), init, bOp);
}

}} // namespace boost and algorithm

#endif // BOOST_ALGORITHM_REDUCE_HPP

/* reduce.hpp
RIbaSLMcasQSBMSGBW55IOpi2Ur9RetxQOWlXg4wEg5yQ12k1v5pxBOkiQqS/IvT8x5xDJtV/C9eDw5iFDar2F+snneIkJkWFkCPHqIL1rjUFXpQLva42BVuUDoqSOIKIYgYtZgGSt7jgVpMlRZp9F7gIcL5AKiDmI2LbUYZTpXGGn2E+hmrH0uBQMwVkRjVBJVeWep/xf87Ev8t0KkFgjAQORETkbDIRJGDiIJGYOG/KBFEMXr20P5bmIlISMcFUoYafWYvoBn+iiXOkY4y8x/VeMx/VQf/C369R4AZXPq3o9w6UBQP6XHx/10vnmFhZJQW+PTn8MdpgGvTt4auljwRL+b2PuRpfQEvmtNduRuP0gdXmtS+dELmNQ468YSXHxOdmiq/vTPpdr/msHMXgzA4ETQDLSH+pAzgKYKNnvOat8vl5DqlGpXU1bltm5PvQTICiLkODGc04+Y2BYGYeoxEsIWOrGiEdNZ6CS90T3etbHh9ii8QXPQUlUemIax7kWfeFi1k6Ou/ZgNQ23EK+fU+GB6pCdhcOX9zWv+uJH3ZBtcTWhllvmZc8s1xvdHwN3zVwNHiTmnaxGd3/XQEojisD2ykYT1dyPGaUYqFCX9ySBu0Xx6/mVmtS/wrXXMU3xwufKUpB1H5QjHi4Pk1eU/kynwTAndWjtljV4KdgYwWAGbZawrLEO1JTshbhryh8fvl5rS9S73tCT8U
*/