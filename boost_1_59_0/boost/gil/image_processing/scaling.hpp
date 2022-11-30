//
// Copyright 2019 Olzhas Zhumabek <anonymous.from.applecity@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_SCALING_HPP
#define BOOST_GIL_IMAGE_PROCESSING_SCALING_HPP

#include <boost/gil/image_view.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/gil/image_processing/numeric.hpp>

namespace boost { namespace gil {

/// \defgroup ScalingAlgorithms
/// \brief Algorthims suitable for rescaling
///
/// These algorithms are used to improve image quality after image resizing is made.
///
/// \defgroup DownScalingAlgorithms
/// \ingroup ScalingAlgorithms
/// \brief Algorthims suitable for downscaling
///
/// These algorithms provide best results when used for downscaling. Using for upscaling will
/// probably provide less than good results.
///
/// \brief a single step of lanczos downscaling
/// \ingroup DownScalingAlgorithms
///
/// Use this algorithm to scale down source image into a smaller image with reasonable quality.
/// Do note that having a look at the output once is a good idea, since it might have ringing
/// artifacts.
template <typename ImageView>
void lanczos_at(
    ImageView input_view,
    ImageView output_view,
    typename ImageView::x_coord_t source_x,
    typename ImageView::y_coord_t source_y,
    typename ImageView::x_coord_t target_x,
    typename ImageView::y_coord_t target_y,
    std::ptrdiff_t a)
{
    using x_coord_t = typename ImageView::x_coord_t;
    using y_coord_t = typename ImageView::y_coord_t;
    using pixel_t = typename std::remove_reference<decltype(std::declval<ImageView>()(0, 0))>::type;

    // C++11 doesn't allow auto in lambdas
    using channel_t = typename std::remove_reference
        <
            decltype(std::declval<pixel_t>().at(std::integral_constant<int, 0>{}))
        >::type;

    pixel_t result_pixel;
    static_transform(result_pixel, result_pixel, [](channel_t) {
        return static_cast<channel_t>(0);
    });
    auto x_zero = static_cast<x_coord_t>(0);
    auto x_one = static_cast<x_coord_t>(1);
    auto y_zero = static_cast<y_coord_t>(0);
    auto y_one = static_cast<y_coord_t>(1);

    for (y_coord_t y_i = (std::max)(source_y - static_cast<y_coord_t>(a) + y_one, y_zero);
         y_i <= (std::min)(source_y + static_cast<y_coord_t>(a), input_view.height() - y_one);
         ++y_i)
    {
        for (x_coord_t x_i = (std::max)(source_x - static_cast<x_coord_t>(a) + x_one, x_zero);
             x_i <= (std::min)(source_x + static_cast<x_coord_t>(a), input_view.width() - x_one);
             ++x_i)
        {
            double lanczos_response = lanczos(source_x - x_i, a) * lanczos(source_y - y_i, a);
            auto op = [lanczos_response](channel_t prev, channel_t next)
            {
                return static_cast<channel_t>(prev + next * lanczos_response);
            };
            static_transform(result_pixel, input_view(source_x, source_y), result_pixel, op);
        }
    }

    output_view(target_x, target_y) = result_pixel;
}

/// \brief Complete Lanczos algorithm
/// \ingroup DownScalingAlgorithms
///
/// This algorithm does full pass over resulting image and convolves pixels from
/// original image. Do note that it might be a good idea to have a look at test
/// output as there might be ringing artifacts.
/// Based on wikipedia article:
/// https://en.wikipedia.org/wiki/Lanczos_resampling
/// with standardinzed cardinal sin (sinc)
template <typename ImageView>
void scale_lanczos(ImageView input_view, ImageView output_view, std::ptrdiff_t a)
{
    double scale_x = (static_cast<double>(output_view.width()))
                     / static_cast<double>(input_view.width());
    double scale_y = (static_cast<double>(output_view.height()))
                     / static_cast<double>(input_view.height());

    using x_coord_t = typename ImageView::x_coord_t;
    using y_coord_t = typename ImageView::y_coord_t;
    for (y_coord_t y = 0; y < output_view.height(); ++y)
    {
        for (x_coord_t x = 0; x < output_view.width(); ++x)
        {
            lanczos_at(input_view, output_view, x / scale_x, y / scale_y, x, y, a);
        }
    }
}

}} // namespace boost::gil

#endif

/* scaling.hpp
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
*/