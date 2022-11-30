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
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
*/