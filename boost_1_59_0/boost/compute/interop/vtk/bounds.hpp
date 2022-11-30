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
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
*/