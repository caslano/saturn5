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