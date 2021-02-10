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
gDmcX7gHrvk54r3Ycv8W2xRkFRirSZfPmn8K6RCU/vFH1duOVOtqK59Hq0adpWq0VZsl0sdRYjKt7kQJWGmd4AnqgRoYVWEwIUDVqM1ijMeXHCjThk6uvzbj4Ap43VmiITWKHUA8kS+R9DQP8go8FnrAqdAW0nLcWHpXaQxriwtU9eJUL8yuwldUB89fyqjZl/HZdPDn4+9eH52fkyPJWFGmgCw0lloIszhKTDpLPnSfkgV9Q3JWEVDCvbvn0mGRFl8G4MJUVFfjyt63YoqaI26cj9+fDI4Nd1WdALJc42+Q3aYiqCQCXsNYvXIes98N+gEH3d4K3YJfAJy3p4PtJ2o5iAqY8lSPDiGo1F9TgWDdZprlEe0xHnwvy6lpLeEn1w1Dzh+RpLI+ZMEX457cGQOrhrjI1T9/fWgaVlIERYMhfQlVHandQSHj9ZUs6id5w3qp/cpwH2v4+rB4Wl/xW68uXrwchlfVVdMRIdw/f/3q+NvTgxS71AvS80S4ysYLtzB4WcnRm4vnHvCLWX82RfvL+hP86fLpybfH5xfO6W4S5ga+1z+apHYkN7VydMRb954NRJe66yxVGZ46VxF3F0Xxn1b109SGnQVhw7EcROMYq4wlXliPhw5tnXQK9ZfptsX+eFucnhlpLWJG
*/