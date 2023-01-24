//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_VTK_MATRIX4X4_HPP
#define BOOST_COMPUTE_INTEROP_VTK_MATRIX4X4_HPP

#include <vtkMatrix4x4.h>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {

/// Converts a \c vtkMatrix4x4 to a \c float16_.
inline float16_ vtk_matrix4x4_to_float16(const vtkMatrix4x4 *matrix)
{
    float16_ result;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            result[i*4+j] = matrix->GetElement(i, j);
        }
    }

    return result;
}

/// Converts a \c vtkMatrix4x4 to a \c double16_;
inline double16_ vtk_matrix4x4_to_double16(const vtkMatrix4x4 *matrix)
{
    double16_ result;
    std::memcpy(&result, matrix->Element, 16 * sizeof(double));
    return result;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_VTK_MATRIX4X4_HPP

/* matrix4x4.hpp
9neSK8MnZbS/3TV7uHfYMhU622j/2jUQfedklKRPkAZa1Bks4Wex6yzvGdrfPsh91eeveRT+zWBau+jYMvIKCUOAWEC07ld5tiDd+0AJQHHVKcel8M2QYhFoElzD1t1fu0YJ18hYqeIbY/9fP2cjRCyq7wOQB5NsBmQFP48AVaPeGv+V5vX8IQo6oNlO+H17ZrqshmV2/8H5c0r57U61RynhB4qh9u2nLkQxuAfJTWq1QVkNmuL6yJ1h4LnHCFDwn+bm6fV7ZtL/iLRh5OO8asCAbkn8XToZm8WCN3Asq263XkkrJIj+l1ZFO33ggz90xF7bdrQ8MDfwFDOGy/iO4Mx8wgX+Cu8GA4MaNdIeZ1xpDAKJYHW8yfxO4XdZ3VQCC1s3/94Hovvaac3SWmjbsvyXC4x108Qh1096PZPpDbsD22hLwcpqZYo6MkYngiwXqGNT5tod+e5DNaR9W+ep6eWPH869VZnZKJdz+xZvMpFOnsE0fE4JCHXc4YUHtBR6JN58Gtr/b3hfw+/0xvlXpR+qiQpLPyRYcZYQnzi0hPnr9z91rBBNOvPMVbzyY9lTaiYEyX8cdR40kx7/cNbJtJDyOm0tMdXIelstYMzuT3BGu/psPu4KkiHGBPXmMeRTr/cn5IYabwl7sXXqPN6JmFgvCOw3B2BuAugmJXChG5U5pjoqgvOafmqkzk0iH4Hm6coi1pcIPSwteLOq
*/