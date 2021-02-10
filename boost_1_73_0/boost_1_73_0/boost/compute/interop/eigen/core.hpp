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
NRqrz8lJQz7V9n6K9ET4rQSMXaDoo5v51ew6XzpNhMiIQbI86D5FPcAPjyNmaEZEnmWP6oujJoSUdiC7Nf6TQK5+xnlOD2gl/zEKQbA09WxNBnOAnlnUDT3uRdE1TB+V+KXykJTpzdWVG4cuwpPoOEF71Kd4UT+X2FM4UmzyqLiAll0S3s3UIRKcsFjLJ2xTUAU+iCV/LID3STtQ0zk+MCepDoqm/lkaAN4Iwnr6SXRHBi0azmTX9q3047vn1Nt/PIbhVTbDB9n7ORx5G2I8mUAM/5Hdc98EMPeVD9c/ErnWSpvHM4/LVNPxovOGW4U4+hdQSwMECgAAAAgALWdKUtd89y+0CAAAbRUAACkACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvbGliY3VybC10aHJlYWQuM1VUBQABtkgkYK1Y227bOhZ911cQnodJOo6ctpiXg85gXCdtPCe1jchBESCAQEu0zQlF+ohUXBX9+FmbpHzJJKcFJunFrsR9W3vtC5ve99ibV/tJUlLHfvqT+z85fvDZCc1q8x9RuOcF8vwHC78geI/PXzA1YHupH/kp+yWpH+zES+XR1gf6nue/YO6enKS/BiR8n9NXPAmSUX5kNm0tV2vHTkan7N3527+zM3y8O++zC66l
*/