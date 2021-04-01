//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_VTK_POINTS_HPP
#define BOOST_COMPUTE_INTEROP_VTK_POINTS_HPP

#include <vector>

#include <vtkPoints.h>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {

/// Copies \p points to \p buffer.
///
/// For example, to copy from a \c vtkPoints object to a \c vector<float4_>:
/// \code
/// vtkPoints *points = ...
/// vector<float4_> vector(points->GetNumberOfPoints(), context);
/// vtk_copy_points_to_buffer(points, vector.begin(), queue);
/// \endcode
template<class PointType>
inline void vtk_copy_points_to_buffer(const vtkPoints *points,
                                      buffer_iterator<PointType> buffer,
                                      command_queue &queue = system::default_queue())
{
    vtkPoints *points_ = const_cast<vtkPoints *>(points);

    // copy points to aligned buffer
    std::vector<PointType> tmp(points_->GetNumberOfPoints());
    for(vtkIdType i = 0; i < points_->GetNumberOfPoints(); i++){
        double *p = points_->GetPoint(i);
        tmp[i] = PointType(p[0], p[1], p[2], 1);
    }

    // copy data to device
    copy(tmp.begin(), tmp.end(), buffer, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_VTK_POINTS_HPP

/* points.hpp
VpMPcW9RbTgEIgUKOtEfZJ4nV3u+1JXbBGk9/BDbjnjwIz8nnn1fH6XEeKTCflJU9yRkXtLU4QgDUivK8tZKw0ZhvowuvmRek6DqbF9qXDGkKvD+Mb5T8gAy/vuCei3KpxW8mND7Oy9aympyViGR6OHLmr7La7uzSkoED4sdW8XxK1pqTCwDHZFw+HLVqkSqAKdhgnnHA4PQDUMmx0l2YWUp2UWaBtMSrd8sP1RM1eOqPPtwqXsB5nK5jhVk3VBXJEDYGq+x8tUhKapr6uuNtNjulA2KNs78zGVrX026SZnZSL6dvHA+XjpnnYyj3I5+eY3kzmut/w+l5NWA10ZiGWMkT/9ykD75rcvE4r5kYmYsQGkXBnV3Qc/zmLi3LhiUXW/uwq6nXDlQaQi8SUOpncvMQE2ryy8mW1L+wH+xLFvpcGl7fXZW7LMGPrCNACPrTB0QWJBNyJ3By2sLAaxkO66jDgij6RgEgAuIDoLUgeNCobEwfKaH5/0EN8IfvV5tXqhN36OQfvtBHvveqv9i1JpEsSSDzxp3BpxT33Sv+/lgcj2kU1V6fimslQ==
*/