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
n8TgF98UNr4elCoSz2BFrcjfUaj/fPcp1G3ekz5OY/LxTG0hv7yFhpGWAmeCKukGeKUGkALr1fAp13ZtUDG2zzXQy+rQV6DnLj0o71tuIH0t4mwwscZ+3HD3nSn+ge94jK9uHknny4WFz3xtyRNDxE/s73+Pu2Pm8cqf6RmrVBAlPk1l4dbnoM21gJXPe3DsQMBRWV11dR+4dQX7THRcws8U0MxVtoC192fpI1QO4ZMr4l3vz8G8tirmjd2M5h1Xe9h6eA4XkQf5+ctzKbxVYs64oA6LmOqJYp0UKiq2x+vBV71r9bBA7Nzv/XAQMF8xP3wlwGiCupxXf9SdgoT1/NpqlwsiYzKIkM+++X41+xr9e6VPaVkdPJ1RoM85Paa+pMioJMxlN3NvYG5HmRj/4yxvwZ17nHeJ8p//JI7Bfxy/Q6H2hetOYA3Y+l908y01A/Grx4H/XLUbv727MfruTtvHl5xR7e/u3CsmHcdXvEfxziiS5znVt1cPODP+SW3I/k3h/6ZS6i8DE+7gU0XgVnfu/oQTUDAQty83MP5b5BDxL9H++3+JPjL8m7r9m+pr/ItOuPzL2mOeiXDre9/CEzRryLCBr2wV/53C/G/fTVT/8k3zbzrx6N90hvpf1D3rX9Vw/bs2Lr13bA9tzNj9n+WT/98u4l/9c3VjVBMlI3ofV8qYKrjiHlEM/lpxKf8/09xTCmv+2VBv30z5
*/