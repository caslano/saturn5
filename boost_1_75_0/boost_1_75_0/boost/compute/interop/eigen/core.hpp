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
K1RPe5451+LuG/Tgpmr5nXgNSm7oMQZ3RU+H3s/hkaRUHwqXaWMI0a7vhqKusDkpxUwQI483/7V6Bfz82/y7FSGWeImvP8jsZGeS9afn7YMJVhS4Y74J2oaolCYUejb8axTfi3S1Z92KJx0/aLGvYMPC9OZSvr7MO7ALvLF+oE1LkNYUy0H/dYqxxhkQyrwo8ztn11ER4EjD+j+KCS+6fkcdmtkcNVwo7srNzlLQnPB8ynyQNwt0CN7ARKtwiKNQZcqX9cwczIs6p9nCWtvRvspBKrZm8OIcJI1Q0Wrlxi2m0DgBFMdP/vMEqm7Sg29nP7h2aff66eM5sk3yEnle103Jj5DJqVzTupFXJRpwbThXdkHPGvtEm4lcVxg3vme2XL5R3D23IKm30+9jxW+N39BXwyfjwHI3zTwr9tvPl6SclBT9slhThNk1WkStWf8CnBB44iAXvrN+mcSy/1D+ZhwGpsZs1UGii2/iiDjMT7ox+aml5HSCIoah2KATyat5foy/lPuVvasHK1c13DymbGrLW244K5UcS4jmMn2CNSpzzzss/AQYm5gL0ne45Z9MCBGVjMgkbg+q9wTqnY4F3/rZGtdueiF9MpF0mmnojGPpoXYUo9np2v6L/PWZMYo8uY59LZrSJSklDwUKW5aviNMW7n8ya8kIyt7F3W+FJX5LEji9671vkReqJZNMuMxLO3bO47vOR1A6xEPQ
*/