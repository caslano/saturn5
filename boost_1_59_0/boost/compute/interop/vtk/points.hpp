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
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
*/