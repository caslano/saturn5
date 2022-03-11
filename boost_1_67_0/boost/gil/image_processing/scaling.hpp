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