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
nbq1P0jl+oSEnUGdwFC1Hz6C87TGb1t5Frm5Gzmcn9lQ8phkzP4b3BZi1ultEttVkRbUXwUbT1X1RWJ7+Z8fo37+An4fPpyqgVNMPJPH6I+idWvPCwVd5J8rIsQ6/Buxbk7GYUHbFb5ISbvIv9Trp+26p0/a7iP4Onit/jZ5yj51elLYArC19qdyrZ2sOO8f+L9pKRMGA4j5Qj832CyQUrtQP1c+HKjxATZ34OBdpOi8d3TgVsn6fFGxsxtlGDrM4plKmsb4qtns32ZvwDBM47g67JIFv/zdhIOP0ulTwXjnvpEqpRtn2u59n+P0HYLpF7V+4zbGlJPtEZjQL/yTdsaj7hh243/owghB2OffRGCq1J08wboFQWGv3Oy15/b24rhA9f7euylhsXbqb5P8WKWJ/OI9m32gdb5rkt1MpfNkwXubmzPa6lBEBBLL/hD0g/s1+uISKXWGStoHbgm6+jYU6nLrrVQ671SIy4P3wW9jYtDxxFlb4G6v4sQoFoMU74LeQWJod0muV7JEaj0furPAsPMTT0apq7uqNJ5PyB65m6DR8DDnEOjd7ykw2ruSIp6UtCO5l8AoIWVVX4096trqlkwHk7tl+l8/TirWD23fPLpZmaF4AcgsZ2VJe1cq2tSNW1iY13Df78QNB6Sp0d7Rndts4oad6b52SzfOTPfy1hauM92/biMc5jrKm95Vmne2txs4MYnBl2FHiz5cFUKQdw0zNNOCrK+MmjjIwh3f6A0ZRl81uIZYX5AQA+f1vXieB1l3eAOnG8t7MHCf7cApxUJ5XryrxmHlwnMvyluMuw2M9uyLco96IxNHADGHwUflxgaGtwdt/dZIufxk5U6zC0fyjDdATYz5pAywr71JHxYxcdB+b9/bj8UTM2o8oZt24vHUDNb4fW0cnptRbRlu1oNT3gw9ePMuzPnhYzFRKrq+TixfApC36BZdGHJAGtSXlZgzunBiuaCnsoBb2N+Fa8eW+0cXTrx2jzf/btmJGU4rbbDvVl0YPKcN3MUWbqj1P7yzeusWrrd+R2/bxpr1e+B2LUxn/f6hjeus330HWrjO+h2/Qxtn1m92xy4M6hfx1doY1C/2SeMHGW5jv+DbyTPkTsX+/LHnKVMUwVxZPz/5NnX9LKwsC+kyooyud/0M5J2IJi9iPrdF4pSJ5fOD19js2gq//qlrEfGQx/i1MB2zHXnX8XZdB+C4vu9FJPAUlYAM6IYinvM0DqPH5LlpIM9dkSHDy4KiCPLEOq3GyIXjpZRgwX/97bpvc+kGLPxJaTnM7W1FqAfGztVn/jFWvPqoy4+ZFurk1Zoc1/KKIHCjNDTrRB5ZRG1w5YZ6J/9JrTyBlSV2WYVmdkR/aepjWubjipaPzIqr0k+TPLByOsdMP3bA/PUey2UgbrBS00159r9DlRNaeeTaZZol1uTa8mCFLHaW2MnyvC5UxIBWyxO9w9A1OHkZVZHHCtTmR3mW8daClg/Pcos88crEtpSIAPWoVoohW17psy/W5DhWEAUxyYnN9qFhyVQgaB5ey4qcDxr58eMgyTKvMOXgyKlIspQYXVe1ekmsokqqIMmzOlLMsdk6FsiG/8PdIe67dZ1Y6RdMNUKjnDMcXxAcE/yMfgznbqa75Gf0C/wbtuhn5Xn+j/w7n+z4V36er79hYDEC3sJkpt6b6dDJ9kD6uRnrwlM3M4ySA4Y19nXYw2xpYaGVxnvaW7sw57W4sVe2dWFwRMM+eGGHgTP2Xm8fNeh8jRSDU9Wn38DAGXtmxG9RcdBwN3KWb2jSh517PWtXCwct/3F5BtndiVlY4uFvBzPzvDFpOM4Tk7Lvy25k8EmDNdQfsKR36MBqXUV5r3g=
*/