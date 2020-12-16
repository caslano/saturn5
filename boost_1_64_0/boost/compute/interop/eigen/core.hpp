//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_EIGEN_EIGEN_HPP
#define BOOST_COMPUTE_INTEROP_EIGEN_EIGEN_HPP

#include <Eigen/Core>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_n.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {

/// Copies \p matrix to \p buffer.
template<class Derived>
inline void eigen_copy_matrix_to_buffer(const Eigen::PlainObjectBase<Derived> &matrix,
                                        buffer_iterator<typename Derived::Scalar> buffer,
                                        command_queue &queue = system::default_queue())
{
    ::boost::compute::copy_n(matrix.data(), matrix.size(), buffer, queue);
}

/// Copies \p buffer to \p matrix.
template<class Derived>
inline void eigen_copy_buffer_to_matrix(const buffer_iterator<typename Derived::Scalar> buffer,
                                        Eigen::PlainObjectBase<Derived> &matrix,
                                        command_queue &queue = system::default_queue())
{
    ::boost::compute::copy_n(buffer, matrix.size(), matrix.data(), queue);
}

/// Converts an \c Eigen::Matrix4f to a \c float16_.
inline float16_ eigen_matrix4f_to_float16(const Eigen::Matrix4f &matrix)
{
    float16_ result;
    std::memcpy(&result, matrix.data(), 16 * sizeof(float));
    return result;
}

/// Converts an \c Eigen::Matrix4d to a \c double16_.
inline double16_ eigen_matrix4d_to_double16(const Eigen::Matrix4d &matrix)
{
    double16_ result;
    std::memcpy(&result, matrix.data(), 16 * sizeof(double));
    return result;
}

} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(Eigen::Vector2i, int2)
BOOST_COMPUTE_TYPE_NAME(Eigen::Vector4i, int4)
BOOST_COMPUTE_TYPE_NAME(Eigen::Vector2f, float2)
BOOST_COMPUTE_TYPE_NAME(Eigen::Vector4f, float4)
BOOST_COMPUTE_TYPE_NAME(Eigen::Matrix2f, float8)
BOOST_COMPUTE_TYPE_NAME(Eigen::Matrix4f, float16)
BOOST_COMPUTE_TYPE_NAME(Eigen::Vector2d, double2)
BOOST_COMPUTE_TYPE_NAME(Eigen::Vector4d, double4)
BOOST_COMPUTE_TYPE_NAME(Eigen::Matrix2d, double8)
BOOST_COMPUTE_TYPE_NAME(Eigen::Matrix4d, double16)

#endif // BOOST_COMPUTE_INTEROP_EIGEN_EIGEN_HPP

/* core.hpp
e8r3K1vkPBiwSTDE/HjPGsHDcHpQpfHFG/HGYf2N6GZBN0zL+34jVm8pc13he3Ndie/NdYUy5rrCd31dAd9cV/T94IlV1hXRJx7XWFfgrbmuQGuuK9BGrKuK1r6uULZtXaF/xrrCd3Ndoa32dYW22tcVp41cV6C3ryvU3b6uKtrodVXRV19XAtNcV+CtfV1hnhjrCt+NdYXv5roiHqp5Y64r5BFPmK0tt6mlictnW+V7k9L38uPsuzTBZTN7gHP+N/SXqXaxRFblerfXMLoe8Fq9M1prQTcCYteYj6xrYgSL9f1tg4GBdW3Ny5dMDIkIVfrnNxn0V/R0u9XNTbowA0YdCw8Apg5C3qnltTcepNOnMayaGRPqO7GtxrP2BM+4n918MKNT2dpWD7ar+N5iqwcf+e0MJ39zfm9GHVt3MFp7lmsyJgPu1kickOHKO99DR+IgGoKd18NGYasbFmw4Hz4Kh+tkbe+3E1jNroS2rd6wV/O57hGtuFbd+yVgW+1ZEPeiDWP61t9pxzFjWVkXVdaKQWd3KXLAlPvQcHnN/KLin/nVg6pupms7jhs5tsVz9UvJAfxaBBZ2WQELm26xEBuqC0cHfi0Hdf1llISu76S21Yx30NDJXD6g64HiJHJY2M0uSwYws5DPXIAo6yTyyhzU9bRl4Ccui/W4Sm6OXMrdDhm+ClmWR5l733YxiN11QI1fladxRGrSzCLR+HEpXof92qkt6m9AiuXYpQuMCEbqYWx6UmZxld8TGoMIhdCThU3NOB+P1s7DsuYJiu4oGWvWaeo3Pz8Cp+o39421Y6odoNa9vI/jWvmTzaLOw2tHY6lp4K6Nxml+ivvWEU59v8s9mX3n+qIm/+CH+3AD19YWcD/bwHDzB2f+R31f2ljh5v4H7vWbgGttF/FCNle4iyNwT5P2PQ8kXEsMEnOPg3zjQe14sc+h3lujcdjgVfv7G9tG480YGl8aJ+w9xk15G/0zuYe4KXeBG2H3+BCi34MO49L2Js7kKd3BMCOTBtW2EhP628ZJWD6n+H79rTV9UKzMedjbrGHfmwnWiKTZw8XsDGlisOedeYqWA8z3irigrYsF45QpsoDd+kfVZjejPc+LS7Hnmf6UfV4vbL3swI5yO7SQXlcWwNlR4WGD5QSk1PEKi4nj7AHzfagNvuBLp7Xhh1FoRyXTDS4PX0uHTSMHzFW9ja4fpWmelJbvRaU9eepFbXxdU8uwtIYRaYL91CJBPY8IjHaUMtf1drLMJUVSmbMyy+dmjx08iEJ1X25ofQkjJ7adwGFF5vIp4JV8Niq+sHKy6Cm8IGEFLh2emBBSeUO/9RRdvxWnXuAEac5bmWe5C5aWlYFbC/3WAT3ut0MK0LTgY9Cbmy+N4e6sRX4StZzD3vluZnuuzQquLM6TXd2Fyd5gaWV5theZ0ajhH3pAj1Fo57adxnxg5kutl50I8WN0fhOm8/Mzj49/7xXzLFVxby7yJL9D5ATU7y+xm5ddt5tZLakzLfgzH9B/h8C2yyzqamVkjigZK+HMflYGS0FeAWBncoPTMSsVSIX55B5i4EkMo6fIPl9BEGPmypNNDO4QXJ/wBuoBOw2Xzk1fXJqf49/eRHsmnVTyG94xHu030ZjKk24f8rMGXbcPKcdMenWzgO85p2u8Yp9GHWubGGoE9O806ZqNy8Q6k67HCBvf0KDPrSj0T2t0jAHuRic2GnTht4mNQrkTnN7UisW5gz5v1nAYV/S5Qdftbg5sadAH4MnwJ73xgHYs3ibS13Erw/H5i0FEDI0HaTT8hogdUdNlZ0Dbuk2jab/dkNPYbFXnUAf0/rikg3+NvvDgNvoU2l54iKSjfZQ9v53RaFU=
*/