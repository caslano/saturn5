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
LAl+/B0J7qfBr1vB+0EsfwzrGYT8nRz/fC8CvzAZ7cGNYRLyu7hC3oaC9LQCOf8OGaoWjAkfxGo2U09DPbtTkQR/EqpyvxZPzsEuKecZCGe2a950WGKvhOuKrCHBG+fAzbBqN3GPy7WphaS88zyt6PmDpaITX4PmRq4QH83Q45re5C81Q7OG6BKhedi91CGXH7Y8zs2tNjZ7RQR5CBHJjtVJU9mK7vBAbv0clyW0OmBz/WqtlObxU0hVBLQmoMVf/Vbu2FzTx1tcKlyVrt625nDxcO/BGbgnnvG2dYQbArcKbivcIbhTcP+CuwVXC7AiDeHC4TrB9YMbAZcC54BbD1cIV7a7ty0EriZcE7hwuAO9kFn8doV7p5s+j4T/NbjX4ebCvQ/3KdxXcF49EBauNdxguFFwWXAT4d6H2wB3AO483DW4aj29bW3hnoLrD2eHy4D7Am433FG4H+HmwX0I9wfcXbggpKM6XBO4KLgucM/D/QuuQm/ohWsA9wRcL5TB0/h9Di4D7p9wS3CX8Xy4KXDfwK2D+wQuB+4nuAdR3s8MxR1Rw3DPFNzK4cjPKxioj1D32EjEO8rbNtMOPyxy/ZNxDxX8LfE7Ai4RrskYdRctmZHjLdkUb9tZ+Dvh98oEb1t90Nyycy2Zv8HvzrHhNbZNcp++mHTC130qdg04hL3Kqkeo5B0mINFxdIYiEDq+B8DbjAX13ud7Cw6w3nBKBcylMjE41m7G1nq85tr0dXgROQQLI5/iTszNA0HTq0yHDJbG3+uML5AeMC/IEr3s6iD7NlDhFUig63jP0eMsJkiMp3emqfH0UTzTeBo/OGjy93gZesw7NE3zJzDx5gdZeikwAZIGY2zyWygbOSsgLqbAC/jmkfK2hQ+1dJyO+9J1Uz3RDRXXzjSRpQWv5BHE0HhZFk0OmTdF3N5bRUERUS9LNJqLzG3c92nz4gRdZuuhoerIiw8CRj/n8eq6zRy4sqsSuHiQT13RJzO2+EF6zq3sODd41V4FD1Dr/1TrcPgLpfHc3Pjnqe7z4Zu8FFV09SqeClrAgVF5HkoOZQGpfYffx+Ahcmv63GAzxwVm2x4O0iZw4PHSd9L/fPsCVOQM4DpMW+s+7Y8loHGBiMBMpyKNq3f+Xt9w8HOVds/5sOcmSiK5dVrAaqzU33NC8z54cfWevR0rKuglxWhgEVfTMWLHgHvPMYXlgFyayPHtcUm9H9JqvAf85zNN96Rvy2tFoJI3TU1JXYEskPkhEcy3j9D0fPLv/IBMfMCWXCF9IqyzyuCOFq/kYYi/nsa/4iOOf15S/F8lfUDSKCXd/RYktI6AEfJ4BY9cn6NEokqcIQlfiF+Hy+MhlfgLLcs0poQ2OG+7LgKGSEGVLg5JVCskUw0HMlVHC8ZyEXmhgiNQH8UNsslB1jm6V2+LXcNq3n+pAaIZYEP//3U+bEQxQFptl0MmWDBiTmB6EOhmFpSEubD0HOO44bjCScHDSLfczsKqGMKLTQ6aUVr2AlKC9sT7i9ogIRF+K/Fjr63nMYmUx5uMXd1onTbplbj0XVXjIiKTL+LgZOChk2K+AK/fDniDNoRswo91Y6af2x9q/F+Uwl0JAs/Of8j1GtoFY2Rcrb9g4rTm/Y/H8AmegWfI3FmJcUrrBAD542EfHvDBHoPgvP8MYsgF1L4BI5D8xhMa0/6PYRM0rFPF20Mc10yAWfgNmH0h7Djn2hOd3cUr43R0UBcszf8eHXklKOuy7LWiWDz3zKRgdtQuaHGuvmQlLsgNywn3st9/j5Uuz6Xu+tv2fmC8u1PNjmNmdtGw7dd37rg811MEmAdRPnoBRgh8mZ2qootgibRFwolTwCALX2QX8Xo=
*/