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