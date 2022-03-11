//
// Copyright 2019 Miral Shah <miralshah2211@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_IMAGE_PROCESSING_THRESHOLD_HPP
#define BOOST_GIL_IMAGE_PROCESSING_THRESHOLD_HPP

#include <limits>
#include <array>
#include <type_traits>
#include <cstddef>
#include <algorithm>
#include <vector>
#include <cmath>

#include <boost/assert.hpp>

#include <boost/gil/image.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>
#include <boost/gil/extension/numeric/convolve.hpp>
#include <boost/gil/image_processing/numeric.hpp>

namespace boost { namespace gil {

namespace detail {

template
<
    typename SourceChannelT,
    typename ResultChannelT,
    typename SrcView,
    typename DstView,
    typename Operator
>
void threshold_impl(SrcView const& src_view, DstView const& dst_view, Operator const& threshold_op)
{
    gil_function_requires<ImageViewConcept<SrcView>>();
    gil_function_requires<MutableImageViewConcept<DstView>>();
    static_assert(color_spaces_are_compatible
    <
        typename color_space_type<SrcView>::type,
        typename color_space_type<DstView>::type
    >::value, "Source and destination views must have pixels with the same color space");

    //iterate over the image checking each pixel value for the threshold
    for (std::ptrdiff_t y = 0; y < src_view.height(); y++)
    {
        typename SrcView::x_iterator src_it = src_view.row_begin(y);
        typename DstView::x_iterator dst_it = dst_view.row_begin(y);

        for (std::ptrdiff_t x = 0; x < src_view.width(); x++)
        {
            static_transform(src_it[x], dst_it[x], threshold_op);
        }
    }
}

} //namespace boost::gil::detail

/// \addtogroup ImageProcessing
/// @{
///
/// \brief Direction of image segmentation.
/// The direction specifies which pixels are considered as corresponding to object
/// and which pixels correspond to background.
enum class threshold_direction
{
    regular, ///< Consider values greater than threshold value
    inverse  ///< Consider values less than or equal to threshold value
};

/// \ingroup ImageProcessing
/// \brief Method of optimal threshold value calculation.
enum class threshold_optimal_value
{
    otsu        ///< \todo TODO
};

/// \ingroup ImageProcessing
/// \brief TODO
enum class threshold_truncate_mode
{
    threshold,  ///< \todo TODO
    zero        ///< \todo TODO
};

enum class threshold_adaptive_method
{
    mean,
    gaussian
};

/// \ingroup ImageProcessing
/// \brief Applies fixed threshold to each pixel of image view.
/// Performs image binarization by thresholding channel value of each
/// pixel of given image view.
/// \param src_view - TODO
/// \param dst_view - TODO
/// \param threshold_value - TODO
/// \param max_value - TODO
/// \param threshold_direction - if regular, values greater than threshold_value are
/// set to max_value else set to 0; if inverse, values greater than threshold_value are
/// set to 0 else set to max_value.
template <typename SrcView, typename DstView>
void threshold_binary(
    SrcView const& src_view,
    DstView const& dst_view,
    typename channel_type<DstView>::type threshold_value,
    typename channel_type<DstView>::type max_value,
    threshold_direction direction = threshold_direction::regular
)
{
    //deciding output channel type and creating functor
    using source_channel_t = typename channel_type<SrcView>::type;
    using result_channel_t = typename channel_type<DstView>::type;

    if (direction == threshold_direction::regular)
    {
        detail::threshold_impl<source_channel_t, result_channel_t>(src_view, dst_view,
            [threshold_value, max_value](source_channel_t px) -> result_channel_t {
                return px > threshold_value ? max_value : 0;
            });
    }
    else
    {
        detail::threshold_impl<source_channel_t, result_channel_t>(src_view, dst_view,
            [threshold_value, max_value](source_channel_t px) -> result_channel_t {
                return px > threshold_value ? 0 : max_value;
            });
    }
}

/// \ingroup ImageProcessing
/// \brief Applies fixed threshold to each pixel of image view.
/// Performs image binarization by thresholding channel value of each
/// pixel of given image view.
/// This variant of threshold_binary automatically deduces maximum value for each channel
/// of pixel based on channel type.
/// If direction is regular, values greater than threshold_value will be set to maximum
/// numeric limit of channel else 0.
/// If direction is inverse, values greater than threshold_value will be set to 0 else maximum
/// numeric limit of channel.
template <typename SrcView, typename DstView>
void threshold_binary(
    SrcView const& src_view,
    DstView const& dst_view,
    typename channel_type<DstView>::type threshold_value,
    threshold_direction direction = threshold_direction::regular
)
{
    //deciding output channel type and creating functor
    using result_channel_t = typename channel_type<DstView>::type;

    result_channel_t max_value = (std::numeric_limits<result_channel_t>::max)();
    threshold_binary(src_view, dst_view, threshold_value, max_value, direction);
}

/// \ingroup ImageProcessing
/// \brief Applies truncating threshold to each pixel of image view.
/// Takes an image view and performs truncating threshold operation on each chennel.
/// If mode is threshold and direction is regular:
/// values greater than threshold_value will be set to threshold_value else no change
/// If mode is threshold and direction is inverse:
/// values less than or equal to threshold_value will be set to threshold_value else no change
/// If mode is zero and direction is regular:
/// values less than or equal to threshold_value will be set to 0 else no change
/// If mode is zero and direction is inverse:
/// values more than threshold_value will be set to 0 else no change
template <typename SrcView, typename DstView>
void threshold_truncate(
    SrcView const& src_view,
    DstView const& dst_view,
    typename channel_type<DstView>::type threshold_value,
    threshold_truncate_mode mode = threshold_truncate_mode::threshold,
    threshold_direction direction = threshold_direction::regular
)
{
    //deciding output channel type and creating functor
    using source_channel_t = typename channel_type<SrcView>::type;
    using result_channel_t = typename channel_type<DstView>::type;

    std::function<result_channel_t(source_channel_t)> threshold_logic;

    if (mode == threshold_truncate_mode::threshold)
    {
        if (direction == threshold_direction::regular)
        {
            detail::threshold_impl<source_channel_t, result_channel_t>(src_view, dst_view,
                [threshold_value](source_channel_t px) -> result_channel_t {
                    return px > threshold_value ? threshold_value : px;
                });
        }
        else
        {
            detail::threshold_impl<source_channel_t, result_channel_t>(src_view, dst_view,
                [threshold_value](source_channel_t px) -> result_channel_t {
                    return px > threshold_value ? px : threshold_value;
                });
        }
    }
    else
    {
        if (direction == threshold_direction::regular)
        {
            detail::threshold_impl<source_channel_t, result_channel_t>(src_view, dst_view,
                [threshold_value](source_channel_t px) -> result_channel_t {
                    return px > threshold_value ? px : 0;
                });
        }
        else
        {
            detail::threshold_impl<source_channel_t, result_channel_t>(src_view, dst_view,
                [threshold_value](source_channel_t px) -> result_channel_t {
                    return px > threshold_value ? 0 : px;
                });
        }
    }
}

namespace detail{

template <typename SrcView, typename DstView>
void otsu_impl(SrcView const& src_view, DstView const& dst_view, threshold_direction direction)
{
    //deciding output channel type and creating functor
    using source_channel_t = typename channel_type<SrcView>::type;

    std::array<std::size_t, 256> histogram{};
    //initial value of min is set to maximum possible value to compare histogram data
    //initial value of max is set to minimum possible value to compare histogram data
    auto min = (std::numeric_limits<source_channel_t>::max)(),
        max = (std::numeric_limits<source_channel_t>::min)();

    if (sizeof(source_channel_t) > 1 || std::is_signed<source_channel_t>::value)
    {
        //iterate over the image to find the min and max pixel values
        for (std::ptrdiff_t y = 0; y < src_view.height(); y++)
        {
            typename SrcView::x_iterator src_it = src_view.row_begin(y);
            for (std::ptrdiff_t x = 0; x < src_view.width(); x++)
            {
                if (src_it[x] < min) min = src_it[x];
                if (src_it[x] > min) min = src_it[x];
            }
        }

        //making histogram
        for (std::ptrdiff_t y = 0; y < src_view.height(); y++)
        {
            typename SrcView::x_iterator src_it = src_view.row_begin(y);

            for (std::ptrdiff_t x = 0; x < src_view.width(); x++)
            {
                histogram[((src_it[x] - min) * 255) / (max - min)]++;
            }
        }
    }
    else
    {
        //making histogram
        for (std::ptrdiff_t y = 0; y < src_view.height(); y++)
        {
            typename SrcView::x_iterator src_it = src_view.row_begin(y);

            for (std::ptrdiff_t x = 0; x < src_view.width(); x++)
            {
                histogram[src_it[x]]++;
            }
        }
    }

    //histData = histogram data
    //sum = total (background + foreground)
    //sumB = sum background
    //wB = weight background
    //wf = weight foreground
    //varMax = tracking the maximum known value of between class variance
    //mB = mu background
    //mF = mu foreground
    //varBeetween = between class variance
    //http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html
    //https://www.ipol.im/pub/art/2016/158/
    std::ptrdiff_t total_pixel = src_view.height() * src_view.width();
    std::ptrdiff_t sum_total = 0, sum_back = 0;
    std::size_t weight_back = 0, weight_fore = 0, threshold = 0;
    double var_max = 0, mean_back, mean_fore, var_intra_class;

    for (std::size_t t = 0; t < 256; t++)
    {
        sum_total += t * histogram[t];
    }

    for (int t = 0; t < 256; t++)
    {
        weight_back += histogram[t];               // Weight Background
        if (weight_back == 0) continue;

        weight_fore = total_pixel - weight_back;          // Weight Foreground
        if (weight_fore == 0) break;

        sum_back += t * histogram[t];

        mean_back = sum_back / weight_back;            // Mean Background
        mean_fore = (sum_total - sum_back) / weight_fore;    // Mean Foreground

        // Calculate Between Class Variance
        var_intra_class = weight_back * weight_fore * (mean_back - mean_fore) * (mean_back - mean_fore);

        // Check if new maximum found
        if (var_intra_class > var_max) {
            var_max = var_intra_class;
            threshold = t;
        }
    }
    if (sizeof(source_channel_t) > 1 && std::is_unsigned<source_channel_t>::value)
    {
        threshold_binary(src_view, dst_view, (threshold * (max - min) / 255) + min, direction);
    }
    else {
        threshold_binary(src_view, dst_view, threshold, direction);
    }
}
} //namespace detail

template <typename SrcView, typename DstView>
void threshold_optimal
(
    SrcView const& src_view,
    DstView const& dst_view,
    threshold_optimal_value mode = threshold_optimal_value::otsu,
    threshold_direction direction = threshold_direction::regular
)
{
    if (mode == threshold_optimal_value::otsu)
    {
        for (std::size_t i = 0; i < src_view.num_channels(); i++)
        {
            detail::otsu_impl
                (nth_channel_view(src_view, i), nth_channel_view(dst_view, i), direction);
        }
    }
}

namespace detail {

template
<
    typename SourceChannelT,
    typename ResultChannelT,
    typename SrcView,
    typename DstView,
    typename Operator
>
void adaptive_impl
(
    SrcView const& src_view,
    SrcView const& convolved_view,
    DstView const& dst_view,
    Operator const& threshold_op
)
{
    //template argument validation
    gil_function_requires<ImageViewConcept<SrcView>>();
    gil_function_requires<MutableImageViewConcept<DstView>>();

    static_assert(color_spaces_are_compatible
    <
        typename color_space_type<SrcView>::type,
        typename color_space_type<DstView>::type
    >::value, "Source and destination views must have pixels with the same color space");

    //iterate over the image checking each pixel value for the threshold
    for (std::ptrdiff_t y = 0; y < src_view.height(); y++)
    {
        typename SrcView::x_iterator src_it = src_view.row_begin(y);
        typename SrcView::x_iterator convolved_it = convolved_view.row_begin(y);
        typename DstView::x_iterator dst_it = dst_view.row_begin(y);

        for (std::ptrdiff_t x = 0; x < src_view.width(); x++)
        {
            static_transform(src_it[x], convolved_it[x], dst_it[x], threshold_op);
        }
    }
}
} //namespace boost::gil::detail

template <typename SrcView, typename DstView>
void threshold_adaptive
(
    SrcView const& src_view,
    DstView const& dst_view,
    typename channel_type<DstView>::type max_value,
    std::size_t kernel_size,
    threshold_adaptive_method method = threshold_adaptive_method::mean,
    threshold_direction direction = threshold_direction::regular,
    typename channel_type<DstView>::type constant = 0
)
{
    BOOST_ASSERT_MSG((kernel_size % 2 != 0), "Kernel size must be an odd number");

    typedef typename channel_type<SrcView>::type source_channel_t;
    typedef typename channel_type<DstView>::type result_channel_t;

    image<typename SrcView::value_type> temp_img(src_view.width(), src_view.height());
    typename image<typename SrcView::value_type>::view_t temp_view = view(temp_img);
    SrcView temp_conv(temp_view);

    if (method == threshold_adaptive_method::mean)
    {
        std::vector<float> mean_kernel_values(kernel_size, 1.0f/kernel_size);
        kernel_1d<float> kernel(mean_kernel_values.begin(), kernel_size, kernel_size/2);

        detail::convolve_1d
        <
            pixel<float, typename SrcView::value_type::layout_t>
        >(src_view, kernel, temp_view);
    }
    else if (method == threshold_adaptive_method::gaussian)
    {
        detail::kernel_2d<float> kernel = generate_gaussian_kernel(kernel_size, 1.0);
        convolve_2d(src_view, kernel, temp_view);
    }

    if (direction == threshold_direction::regular)
    {
        detail::adaptive_impl<source_channel_t, result_channel_t>(src_view, temp_conv, dst_view,
            [max_value, constant](source_channel_t px, source_channel_t threshold) -> result_channel_t
        { return px > (threshold - constant) ? max_value : 0; });
    }
    else
    {
        detail::adaptive_impl<source_channel_t, result_channel_t>(src_view, temp_conv, dst_view,
            [max_value, constant](source_channel_t px, source_channel_t threshold) -> result_channel_t
        { return px > (threshold - constant) ? 0 : max_value; });
    }
}

template <typename SrcView, typename DstView>
void threshold_adaptive
(
    SrcView const& src_view,
    DstView const& dst_view,
    std::size_t kernel_size,
    threshold_adaptive_method method = threshold_adaptive_method::mean,
    threshold_direction direction = threshold_direction::regular,
    int constant = 0
)
{
    //deciding output channel type and creating functor
    typedef typename channel_type<DstView>::type result_channel_t;

    result_channel_t max_value = (std::numeric_limits<result_channel_t>::max)();

    threshold_adaptive(src_view, dst_view, max_value, kernel_size, method, direction, constant);
}

/// @}

}} //namespace boost::gil

#endif //BOOST_GIL_IMAGE_PROCESSING_THRESHOLD_HPP

/* threshold.hpp
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
*/