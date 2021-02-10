//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_VTK_BOUNDS_HPP
#define BOOST_COMPUTE_INTEROP_VTK_BOUNDS_HPP

#include <vector>
#include <iterator>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/algorithm/reduce.hpp>
#include <boost/compute/container/array.hpp>

namespace boost {
namespace compute {

/// Calculates the bounds for the points in the range [\p first, \p last) and
/// stores the result in \p bounds.
///
/// For example, this can be used to implement the GetBounds() method for a
/// vtkMapper subclass.
template<class PointIterator>
inline void vtk_compute_bounds(PointIterator first,
                               PointIterator last,
                               double bounds[6],
                               command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<PointIterator>::value_type T;

    const context &context = queue.get_context();

    // compute min and max point
    array<T, 2> extrema(context);
    reduce(first, last, extrema.begin() + 0, min<T>(), queue);
    reduce(first, last, extrema.begin() + 1, max<T>(), queue);

    // copy results to host buffer
    std::vector<T> buffer(2);
    copy_n(extrema.begin(), 2, buffer.begin(), queue);

    // copy to vtk-style bounds
    bounds[0] = buffer[0][0]; bounds[1] = buffer[1][0];
    bounds[2] = buffer[0][1]; bounds[3] = buffer[1][1];
    bounds[4] = buffer[0][2]; bounds[5] = buffer[1][2];
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_VTK_BOUNDS_HPP

/* bounds.hpp
PpK8TIYQxzP9XBj7TER0wtxBBJd+nDiYzx/EoHAo747ZX/S8CXah3CrUI/tsuP3N6xenR0+HxaMXGPmIenvi8g5Gaty1h+SptsXvaFIQ4+5uLKCSPtd1LXZ0kiBGJEC3qA3QFGkZzAo/Tdu7vOm3SYjliunJKyB95yf/cXz54ujs2+PMgIhRrmmMNiUhfP/oR/fDPXwQaaz6UAJ1GPKVS36W0Qlj8iBuYjObyR3zaPviwcPP3NzdmWbfcHdeVJpu+5P7gJmCqkzwUATBfu2GX4hIWR46RBwQn6g7Ria6WyPb7dqUefkXnZ6IaUJSbOZ32HHQRSrrpQXu4FEGbwXX2aOeJfuuASM6l6G6JhWQMubuYEI2S1ttAAgMSd4DyC5yP8fnwGJQVkQimcatvAs2Kl4BxX2hrL2tr2CWkHSXU6fiKLE0n0F4CTJUxDR+qaTvl4fSdK3ICuRzvU56ZaYirmwAC+hi4J07wV0ld8QD49mGxNOIeut1U+dAo7qVRFd4zzRCz3DUMG1qTLAUX0Kmpjl7Vk/Ef7LH75iybaCQe1Cn2A7cY5krGne8nDqYJkSb8lWSrmCZKiHPGopze/zwIfbtsX/7X+3e0juO7MKHESWjmcOAiOkUQW+dGXrcprT5spc+2DBP7q8gSmgB
*/