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
2y9z7VrGDil9Xznjz3Af1FZG7fxHWfOeEsXd4qcX/I3TzIu/ACyLTirpVqDamuERF+lbG0HToWb173C3d0xm+ZtE1TXAyzDPMj1NgDXTSC8fLxh4f7qMuG7ry/I7Duxo5FTVWA4rpw/TmZrpydt78dBMw7qw2Dc5yc87FpgIib42PI5GaTbZ/Zsxa1WVqJm4v9F5SUFqnuqFSbsA/46+ryZvg2Br0vh5nsVVCUfDJdPVPCRX7rz2c7Q+l1LpL+cbZu1ZBupKtoW/oxnH7TZCh17cDhRY5QDLDdjVsK4DeMTuK8IJGXOqTzNXDRMbtUtMk8uA8T2haQvYl8myokZKAieVBqe1GWQP3IgEox6rThJUe19eXtlmi3qBqHZyU6qycrbC2c9eZu3nWy7yNbhOGs2LrG8/xzPNyHqHmRp2ciFxLEkRyWRZmZy7wf0lohW3shPALBqlMFJOT1qtPeR933QdsSyl4PHdkw5+9rRSnGnDVT+DAHlL6rXU8v2/XJnXomrVut+dNGyePtF98jVbV6SMn8i9nOa87nF0myk36GYhNLD/L1AGhGU1CRg7ENfup3FKI+1J9F/FtbxrH4oh/+0ibqd42xx6AsK1ZsLwqp6VXwZ9kit4UX5j4rhvZ5Wx/Z+YNIJOyjLBP+pOp9LmF/U6kUMsB4um7RQXIlZxk89GFRSJWGy6raedcpUgo6ygpl/+UPDAoQLc1YXL
*/