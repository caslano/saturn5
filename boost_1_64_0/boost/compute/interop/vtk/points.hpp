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
TxcWXRAyL9ykAyeOz6JrAfvqvRtg65kG2IWb9mNlHGBg95nY9vkG7/DfYmMsN2+aberh+fs78BhyCu6WCk5cOKt6sCPQISg48SDz4ikm7kk05zdNrfptfP/2xKPcCcMu7gD7Tm1ttCHs7u4g6Wi3Rk9zR0FTynJHyXeQ0WgJgHKK+n19AwRdyEfvIjCaphFA5P3hd2M4vvnR7oqv8e9m/KD2u8Rn7t7GtXRz9zAx3e/3XunAmf6577uniYFfLfaAz7kXMNAF9t1L/6ON7b5vvjfhDJ2gUR+wRTZxUhbimR5mGP1mdUQto0ZXk1HeGL6vjqEqh/yPajQkD/rzj2h0WX1I/9FHid7SW8K/G2/17+iJ0YM668YgPYyDMeBaOknvOGidOsnbnAAdOsm9Uv/KabxnI98Xxtk3oXPWbmCV+AD30zC4XcUb2hqdKxHlKoayb30QMJhvmiVMsY21FJxyllVjyT7cUTDSBK+ZU4aaP5urYPl8PNLkKRQ0nKFoLiUhq/W6if3Q4TervklO6OWOU0ZWKO5WsdkMBN5S8U5ueW7MXiPMwTHG5k7atS7N4mJyCDFNunOqnPuVQRHGuZdbCEwnOMYkfl3LZ+ITg51W1sPq+1YkMAabT4HHOzhh5qR+HltqpJonsVtXcCNvr9fSKmI7qIIC0XtQlhXEAVTxnmOldpLkRcnsyWgJWaKt3VOIj5+LWq+SqHV77c3GmdH2/DJMrVWq2mHtziI273S8OD+/uiqlkkxVzoG3GH57RVgFeUz3rHO01Wa3/ozlrJQwN01nAk7iD5c079FUb9HzU7mxb4dRWss5NWlPjDNOfhDlr20YB1Lt7Q9VlhdYjhOxhyi9WtYKDipcbPu0wmOnyPJ9UpPlW1XgeH5RlS1ZGDbquac5v428VZETULtFee6mvigf7XvnWZWz0/n8Yn245aJ4Amp9z71Vz4/j5qnthomWH27cynNwlj7OcQf0WXYWauwE3vxW/S2uOPXcMI6tSXFHyXKhxHM7C39GlS+30jgMsjRgYZpo8JtsCt+lt+o2xo7jBb4dWXS3zbhmFtZmWX+XnGfxJrPKN+55seMGbiSziUvUCdz76+m4QU6n9biwltaYtuAc1QipLmeHSAdxlt6mn/MT189T13VQIXRRTCrSZd4sSHZkQd5LH1T570vaHD8IWcTQEyJ/sLF/k/6unuu7YeRW7Amhf1N2nbF5NEXYTgcChNBC7xC6UwwOIL693u+WxECojmO/iQ1u+LXBFEEkihBN9N7rJ8EPEPxAiB8RHQRS6B1CDz300ASze3vP7e7dG8IHXwjvPDO7t2W2zOzM2mCO1NhgvqnbSvNNB99vfpMbJrFbMWXcbxoddZrEO/QnaLbyw37mZUlS+kx/m7+KvKXvNW3xUZjRFAyZFfEalYM/rslXVGEQunHKuJpVFQLUmvnymNHeDguDnHuun7ETxiWVzuvA70byosyqTEgFprm6pqI9/fKazgdfiQWdL2c8yL2sChLmqJMbmDTfjC2dp2I+T6osdUJWqRvOnthzyA9+QO/rBydxmVSFR0NeXKBqZYVNf71QL2vSTwO3zNyMCS0FNPKwm9+Sp5Wb5K4IzazsTcJPwRp7b9d5jlGD555becRSm7LAQdDrmm/4oM7zYF45BffKkHhqMxna+I6aLW8Xzjn125/Ti6s4L318nOiW/UaDte8Rdygc9hSarGa/u4sw12DD/zhw/TZ8xPvZrXBeVYYzj3LyRwbaztDwQyDcxhB2vrZuwDzvBhIDX47l2TUEkYOP5vtMO6qbOGVAnfj/3gPrdtSd1Ga6x6Xc+onF37Kj2rjGzGLZUbu4YVfe5W19OMgzYuYRTvpHwhw=
*/