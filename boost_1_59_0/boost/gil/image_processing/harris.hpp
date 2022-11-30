//
// Copyright 2019 Olzhas Zhumabek <anonymous.from.applecity@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_HARRIS_HPP
#define BOOST_GIL_IMAGE_PROCESSING_HARRIS_HPP

#include <boost/gil/image_view.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>

namespace boost { namespace gil {
/// \defgroup CornerDetectionAlgorithms
/// \brief Algorithms that are used to find corners in an image
///
/// These algorithms are used to find spots from which
/// sliding the window will produce large intensity change


/// \brief function to record Harris responses
/// \ingroup CornerDetectionAlgorithms
///
/// This algorithm computes Harris responses
/// for structure tensor represented by m11, m12_21, m22 views.
/// Note that m12_21 represents both entries (1, 2) and (2, 1).
/// Window length represents size of a window which is slided around
/// to compute sum of corresponding entries. k is a discrimination
/// constant against edges (usually in range 0.04 to 0.06).
/// harris_response is an out parameter that will contain the Harris responses.
template <typename T, typename Allocator>
void compute_harris_responses(
    boost::gil::gray32f_view_t m11,
    boost::gil::gray32f_view_t m12_21,
    boost::gil::gray32f_view_t m22,
    boost::gil::detail::kernel_2d<T, Allocator> weights,
    float k,
    boost::gil::gray32f_view_t harris_response)
{
    if (m11.dimensions() != m12_21.dimensions() || m12_21.dimensions() != m22.dimensions()) {
        throw std::invalid_argument("m prefixed arguments must represent"
            " tensor from the same image");
    }

    auto const window_length = weights.size();
    auto const width = m11.width();
    auto const height = m11.height();
    auto const half_length = window_length / 2;

    for (auto y = half_length; y < height - half_length; ++y)
    {
        for (auto x = half_length; x < width - half_length; ++x)
        {
            float ddxx = 0;
            float dxdy = 0;
            float ddyy = 0;
            for (gil::gray32f_view_t::coord_t y_kernel = 0;
                y_kernel < window_length;
                ++y_kernel) {
                for (gil::gray32f_view_t::coord_t x_kernel = 0;
                    x_kernel < window_length;
                    ++x_kernel) {
                    ddxx += m11(x + x_kernel - half_length, y + y_kernel - half_length)
                        .at(std::integral_constant<int, 0>{}) * weights.at(x_kernel, y_kernel);
                    dxdy += m12_21(x + x_kernel - half_length, y + y_kernel - half_length)
                        .at(std::integral_constant<int, 0>{}) * weights.at(x_kernel, y_kernel);
                    ddyy += m22(x + x_kernel - half_length, y + y_kernel - half_length)
                        .at(std::integral_constant<int, 0>{}) * weights.at(x_kernel, y_kernel);
                }
            }
            auto det = (ddxx * ddyy) - dxdy * dxdy;
            auto trace = ddxx + ddyy;
            auto harris_value = det - k * trace * trace;
            harris_response(x, y).at(std::integral_constant<int, 0>{}) = harris_value;
        }
    }
}

}} //namespace boost::gil
#endif

/* harris.hpp
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
*/