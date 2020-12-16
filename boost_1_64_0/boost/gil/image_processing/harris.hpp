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
yaUngVtAMpcv3GGn8SH8cdww5vqPKnqAij6iov5QBJl0yjgs+H9Z0VcsoOrb77hx5II1aP/bXsC/ZdCHNQ16XdhCjgsZSwAWgmne1y/BPScLpJ2Ko0ec51IEnbB47kV45HsmM+OoKtCDDdRQy9EjAXOejd9oXdiOiNg+FcMJTge+WOpvgkg+ghjSLFrRS+XpoNI6hXocy6Jyt/TvTDKHrBoVeEiZ7K588x2nT3lutN86NyS3r0KrqYPcghQEkunInDeBGjMnQ97oFIQQW0YqeQs0rrsR//y6KOhMBT+CDNJhkIwflRHPjtV8oYDvoU4dC3Zpt3gENBl4YkfzDCberBY88TQ4gVvrmrIaSUtoTNVI6rfkDSXTMNbRc7hmOfoQ3v+o7L11dSy/ERJYdx58C4PY5N7pUYPosT+ZHhUjlJam0jzdQqiEGGKw7TEQLSMCPJ4raYo3eAhucdvkxQJ9ez8iwLgyv7I+p8uzXwUIS0Akurm2pUJPWzqyVSthzR3p+PaZ16bIjIu3dxmWYntH7J/4Kec4yiWBJccotjDcS1vDEyhikg/9Q3L/iG4l+ByVDsp+DSV7Kl1KeQj9i5FV5xtX5IpY7DUhIFaJJ5oWU7SfHQ1ODG1YwVZeqqls8bpf4Rs8zWZvZX2wGOtnUyXWerTXPiJRejGawRrltT/hb8Ioq0jg0djtlCPQHGuq/ofMhskCoFARjBh3itLMElKvW9S9Sp1k3gA1bkBsKGwyy8dpcayYKhiEvRMde3Q5gWcatcUsvSytup1GFuNIm4FuNwXvX5ysysiICXnhByWG++Vy/FPX9VehkK0TBoXo2Jx1XVLo/axC72AVuvcUT7sui7xyvwPSpqxm//pVZL9purbrCxkohuDL1h0tGdLi1t1kQ2ucHnUafYiu2v6kvckBqglFlfI8kXG5GFmvSXJM8CgkaDtelbRtk+XLz3TmMJ0TdTzBF4cyAZQ5cpSf26gvJY7K6DlWwweGrC/jhe0AHSim2VYHMlbvjeKj2f2DvvxWV1f/qiRuHBOXjnJ3trvE9qJBtUQCNEGUvvGHSA+hdA9KV7xE28wmZWwk/5ir3dcscLABN+C6Iy8WlqiDcZ/q3Wp8NVzF79/8cmtfjjL5lWJNOU4KdoJioqkZ8j8nMWKxyZqkEfsjYhq3nZriPjCd+qW7EaSn1bPZ5fzbBi3cFgju6JuFuq0YdoyE9Mna7HfelhLlSIbknbuk4w+kwd6HYJlOSL/c/+R38aSqSqOq2HbS5BKx1SBTAr4z+JHGtRo6qPplhOeGr17ZGH4Yn7bY5syQLuQh5FGbhNxns0LWO6gte1++NMc11heBFzdl/i57Ji/VwBpYS9A5YrbS3HGSdSw1Wyk8ofyEeTLVi7r5KsrpFx7nSU9Df1ePYc6keUDBH4Vmnj8/iHrMRqk4OyN2h18D6UTnFmpPkJlRQV6jFbKuuwahOa+vrgnInYgSmfuAlZzpYKLnTK4YE1H/AnqL5LIxESs4ARWL6OgaKvUyVTi2ccDI3dLapDWURE3m2OL7a5KoiUiUs9ItLfg+ExlkvSzTC/avggkQHJNjnjO6n9aezR1s7Sz30sYHSoh/WYDX9ROUFfyR9I9lZkMq24qhTh8xfVM9mH3lwGfxb2LbJ0IoWNZn8tYVHZeyzJ5VlQYkU5sqd4boqYb2VKW1yJxK+R9FN4DooI6dI05CvGiiJmo0rcXK/oCwklqZh0G2YsvW2E7QMjI/TWJ7jbGtRczO7oyNsNzNxZLmJFP6K8NqQb6p/VYLhHXekN4jtqqMisBLVt5qtSZ9hCqzoN7pFeK5JeMnVDE0UbqTSh9V6ZuXIf0Cpb99ABmDnZzNHijfbwY=
*/