//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FILL_N_HPP
#define BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/fill.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Fills the range [\p first, \p first + count) with \p value.
///
/// Space complexity: \Omega(1)
///
/// \see fill()
template<class BufferIterator, class Size, class T>
inline void fill_n(BufferIterator first,
                   Size count,
                   const T &value,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<BufferIterator>::value);
    ::boost::compute::fill(first, first + count, value, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FILL_N_HPP

/* fill_n.hpp
M+etYa82SQMrpaosXlWvtRpyE+GC9JAutQgRz0T5roT5/Kwkz27P6P/Xei2R2OGO8EqMzwHoCTdOnpfOnK9RBcGVxP2ixajUIy8DT5rqP/L8nr+VPF8Hmv1yLd298Vxb7fOkMv98DIfeoXd/5qBFLWyvkCN0OfGYfbH1CrT8DVC5VmkjbXqpAHmgd78eMZC2K+0ewfMjwlq7OfnCEiXlUw3ugKX5PDGuCzCPAtNEJId12ZbojXT4/FV4gZQMxdrwhc3GbNiFJP79g3rlxFVvPtfYLbUyZoNoQ3C8fHAIl5Syms5FhAdIR+wJZVAjIKliSpJdl3Jg99yBO7JkhAnaWR69EwvRFR6Upwk2iOcEO/njIBjibR4+dUUiSma9xN7iZfgDyIWKqNewtMVrgQ2qBF+Q/VSAnRad64df1T3FODZD4yPfxC9yKe6cLeRW/nZsESYsX32REmhAQYYyUp5FLZozF7vpTxj5jBY7uDljC6tc0JQ6HFDkbE/O0zAUbu/LyKJMo+DJbImAjRwH+Akf4qdWrZeyCsCS/+zBJnVcdBc6Y4MZs1X9/SpIAA==
*/