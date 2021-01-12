//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP

#include <boost/compute/device.hpp>
#include <boost/compute/algorithm/detail/scan_on_cpu.hpp>
#include <boost/compute/algorithm/detail/scan_on_gpu.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator scan(InputIterator first,
                           InputIterator last,
                           OutputIterator result,
                           bool exclusive,
                           T init,
                           BinaryOperator op,
                           command_queue &queue)
{
    const device &device = queue.get_device();

    if(device.type() & device::cpu){
        return scan_on_cpu(first, last, result, exclusive, init, op, queue);
    }
    else {
        return scan_on_gpu(first, last, result, exclusive, init, op, queue);
    }
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_HPP

/* scan.hpp
GRnBiCyBG5HIPXhZP3IfXjV78OzeO192eG/dGmSL7psbgBQhO9tiBnchh5CvEXdv23BE9/Hp/r1Ye/dq1o/5LDt2X2Zq+3+uP7O//U/Tp9mJ7g9k/Hf1U2p/tb/aX+2v9lf7q/39dL9/5/gf5pYU6vD/Xxz/u2P5GyPW/6/UsfwNSDxyPXILA949vcJr5QvLcnJnlhUXVZQX5HAdcW4mVxFr5X8rbjrIueI+E/JjFfMGkyLH
*/