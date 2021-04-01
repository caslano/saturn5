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
BUru1r3VWVNYIpINy0wTNZCCl+uYguS8FjO38ZT6n0G47IwflP0NORSJXYzRTFqnkodX3Z5OnMHwPyTne+9mjFeNcJllb7ETnv9HLq88IR5OsowQCstLTYytyx+Qw2MzIWjhdLiFWxOnqEv7lkMLxTkYanPbYqdZfkN7AV26zZzxzVW8Unzeaivqrt4FFySu1HKDknGo8F20jYEhjFByNkuxHlgkXHYWVJybQsKLyADmDuc41/uDmkfxugjspqg31CAC5blHwVpaBr3VASXSw3l9uoOg+65MtaVPyF1/+8WidHcmIKftBrDzJbp9SjQ1fVrihr/plMwNJBFbhPCS+F19y+kP2uqjFFJqjsqMh859WLwN9c+T97owiSt5n/LDHK+J5jgUdoMGhhTxWy09a5vmpvEVeWZhEXA1lSLPPIujdyAcUxKcDrJdgnK/VzEJKuAg5WJ36HuhJafACZKtf6NNB2NwebcGond8EepzSYwIj+n3j17Zp3veoMynNHS6yvWYkLNnYOAABCQjot9IldFvEIeeKBy7ei5ZX+d6q9LFr9GwTnqw3iKwKA==
*/