//
// Copyright 2019 Olzhas Zhumabek <anonymous.from.applecity@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_NUMERIC_HPP
#define BOOST_GIL_IMAGE_PROCESSING_NUMERIC_HPP

#include <boost/gil/extension/numeric/kernel.hpp>
#include <boost/gil/extension/numeric/convolve.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/math.hpp>
// fixes ambigious call to std::abs, https://stackoverflow.com/a/30084734/4593721
#include <cstdlib>
#include <cmath>

namespace boost { namespace gil {

/// \defgroup ImageProcessingMath
/// \brief Math operations for IP algorithms
///
/// This is mostly handful of mathemtical operations that are required by other
/// image processing algorithms
///
/// \brief Normalized cardinal sine
/// \ingroup ImageProcessingMath
///
/// normalized_sinc(x) = sin(pi * x) / (pi * x)
///
inline double normalized_sinc(double x)
{
    return std::sin(x * boost::gil::detail::pi) / (x * boost::gil::detail::pi);
}

/// \brief Lanczos response at point x
/// \ingroup ImageProcessingMath
///
/// Lanczos response is defined as:
/// x == 0: 1
/// -a < x && x < a: 0
/// otherwise: normalized_sinc(x) / normalized_sinc(x / a)
inline double lanczos(double x, std::ptrdiff_t a)
{
    // means == but <= avoids compiler warning
    if (0 <= x && x <= 0)
        return 1;

    if (-a < x && x < a)
        return normalized_sinc(x) / normalized_sinc(x / static_cast<double>(a));

    return 0;
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(push)
#pragma warning(disable:4244) // 'argument': conversion from 'const Channel' to 'BaseChannelValue', possible loss of data
#endif

inline void compute_tensor_entries(
    boost::gil::gray16s_view_t dx,
    boost::gil::gray16s_view_t dy,
    boost::gil::gray32f_view_t m11,
    boost::gil::gray32f_view_t m12_21,
    boost::gil::gray32f_view_t m22)
{
    for (std::ptrdiff_t y = 0; y < dx.height(); ++y) {
        for (std::ptrdiff_t x = 0; x < dx.width(); ++x) {
            auto dx_value = dx(x, y);
            auto dy_value = dy(x, y);
            m11(x, y) = dx_value * dx_value;
            m12_21(x, y) = dx_value * dy_value;
            m22(x, y) = dy_value * dy_value;
        }
    }
}

#if BOOST_WORKAROUND(BOOST_MSVC, >= 1400)
#pragma warning(pop)
#endif

/// \brief Generate mean kernel
/// \ingroup ImageProcessingMath
///
/// Fills supplied view with normalized mean
/// in which all entries will be equal to
/// \code 1 / (dst.size()) \endcode
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_normalized_mean(std::size_t side_length)
{
    if (side_length % 2 != 1)
        throw std::invalid_argument("kernel dimensions should be odd and equal");
    const float entry = 1.0f / static_cast<float>(side_length * side_length);

    detail::kernel_2d<T, Allocator> result(side_length, side_length / 2, side_length / 2);
    for (auto& cell: result) {
        cell = entry;
    }

    return result;
}

/// \brief Generate kernel with all 1s
/// \ingroup ImageProcessingMath
///
/// Fills supplied view with 1s (ones)
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_unnormalized_mean(std::size_t side_length)
{
    if (side_length % 2 != 1)
        throw std::invalid_argument("kernel dimensions should be odd and equal");

    detail::kernel_2d<T, Allocator> result(side_length, side_length / 2, side_length / 2);
    for (auto& cell: result) {
        cell = 1.0f;
    }

    return result;
}

/// \brief Generate Gaussian kernel
/// \ingroup ImageProcessingMath
///
/// Fills supplied view with values taken from Gaussian distribution. See
/// https://en.wikipedia.org/wiki/Gaussian_blur
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_gaussian_kernel(std::size_t side_length, double sigma)
{
    if (side_length % 2 != 1)
        throw std::invalid_argument("kernel dimensions should be odd and equal");


    const double denominator = 2 * boost::gil::detail::pi * sigma * sigma;
    auto middle = side_length / 2;
    std::vector<T, Allocator> values(side_length * side_length);
    for (std::size_t y = 0; y < side_length; ++y)
    {
        for (std::size_t x = 0; x < side_length; ++x)
        {
            const auto delta_x = middle > x ? middle - x : x - middle;
            const auto delta_y = middle > y ? middle - y : y - middle;
            const double power = (delta_x * delta_x +  delta_y * delta_y) / (2 * sigma * sigma);
            const double nominator = std::exp(-power);
            const float value = static_cast<float>(nominator / denominator);
            values[y * side_length + x] = value;
        }
    }

    return detail::kernel_2d<T, Allocator>(values.begin(), values.size(), middle, middle);
}

/// \brief Generates Sobel operator in horizontal direction
/// \ingroup ImageProcessingMath
///
/// Generates a kernel which will represent Sobel operator in
/// horizontal direction of specified degree (no need to convolve multiple times
/// to obtain the desired degree).
/// https://www.researchgate.net/publication/239398674_An_Isotropic_3_3_Image_Gradient_Operator
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_dx_sobel(unsigned int degree = 1)
{
    switch (degree)
    {
        case 0:
        {
            return detail::get_identity_kernel<T, Allocator>();
        }
        case 1:
        {
            detail::kernel_2d<T, Allocator> result(3, 1, 1);
            std::copy(detail::dx_sobel.begin(), detail::dx_sobel.end(), result.begin());
            return result;
        }
        default:
            throw std::logic_error("not supported yet");
    }

    //to not upset compiler
    throw std::runtime_error("unreachable statement");
}

/// \brief Generate Scharr operator in horizontal direction
/// \ingroup ImageProcessingMath
///
/// Generates a kernel which will represent Scharr operator in
/// horizontal direction of specified degree (no need to convolve multiple times
/// to obtain the desired degree).
/// https://www.researchgate.net/profile/Hanno_Scharr/publication/220955743_Optimal_Filters_for_Extended_Optical_Flow/links/004635151972eda98f000000/Optimal-Filters-for-Extended-Optical-Flow.pdf
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_dx_scharr(unsigned int degree = 1)
{
    switch (degree)
    {
        case 0:
        {
            return detail::get_identity_kernel<T, Allocator>();
        }
        case 1:
        {
            detail::kernel_2d<T, Allocator> result(3, 1, 1);
            std::copy(detail::dx_scharr.begin(), detail::dx_scharr.end(), result.begin());
            return result;
        }
        default:
            throw std::logic_error("not supported yet");
    }

    //to not upset compiler
    throw std::runtime_error("unreachable statement");
}

/// \brief Generates Sobel operator in vertical direction
/// \ingroup ImageProcessingMath
///
/// Generates a kernel which will represent Sobel operator in
/// vertical direction of specified degree (no need to convolve multiple times
/// to obtain the desired degree).
/// https://www.researchgate.net/publication/239398674_An_Isotropic_3_3_Image_Gradient_Operator
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_dy_sobel(unsigned int degree = 1)
{
    switch (degree)
    {
        case 0:
        {
            return detail::get_identity_kernel<T, Allocator>();
        }
        case 1:
        {
            detail::kernel_2d<T, Allocator> result(3, 1, 1);
            std::copy(detail::dy_sobel.begin(), detail::dy_sobel.end(), result.begin());
            return result;
        }
        default:
            throw std::logic_error("not supported yet");
    }

    //to not upset compiler
    throw std::runtime_error("unreachable statement");
}

/// \brief Generate Scharr operator in vertical direction
/// \ingroup ImageProcessingMath
///
/// Generates a kernel which will represent Scharr operator in
/// vertical direction of specified degree (no need to convolve multiple times
/// to obtain the desired degree).
/// https://www.researchgate.net/profile/Hanno_Scharr/publication/220955743_Optimal_Filters_for_Extended_Optical_Flow/links/004635151972eda98f000000/Optimal-Filters-for-Extended-Optical-Flow.pdf
template <typename T = float, typename Allocator = std::allocator<T>>
inline detail::kernel_2d<T, Allocator> generate_dy_scharr(unsigned int degree = 1)
{
    switch (degree)
    {
        case 0:
        {
            return detail::get_identity_kernel<T, Allocator>();
        }
        case 1:
        {
            detail::kernel_2d<T, Allocator> result(3, 1, 1);
            std::copy(detail::dy_scharr.begin(), detail::dy_scharr.end(), result.begin());
            return result;
        }
        default:
            throw std::logic_error("not supported yet");
    }

    //to not upset compiler
    throw std::runtime_error("unreachable statement");
}

/// \brief Compute xy gradient, and second order x and y gradients
/// \ingroup ImageProcessingMath
///
/// Hessian matrix is defined as a matrix of partial derivates
/// for 2d case, it is [[ddxx, dxdy], [dxdy, ddyy].
/// d stands for derivative, and x or y stand for direction.
/// For example, dx stands for derivative (gradient) in horizontal
/// direction, and ddxx means second order derivative in horizon direction
/// https://en.wikipedia.org/wiki/Hessian_matrix
template <typename GradientView, typename OutputView>
inline void compute_hessian_entries(
    GradientView dx,
    GradientView dy,
    OutputView ddxx,
    OutputView dxdy,
    OutputView ddyy)
{
    auto sobel_x = generate_dx_sobel();
    auto sobel_y = generate_dy_sobel();
    detail::convolve_2d(dx, sobel_x, ddxx);
    detail::convolve_2d(dx, sobel_y, dxdy);
    detail::convolve_2d(dy, sobel_y, ddyy);
}

}} // namespace boost::gil

#endif

/* numeric.hpp
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
*/