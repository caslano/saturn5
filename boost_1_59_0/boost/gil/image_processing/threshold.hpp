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
QpJ3SWgtSFrYFvR0mibx68KQddReQYwGBBn8KANj7/TKpqPONahv5OSdFTZf0VyobApUZR+LFPco8MeFXt/ILqcxGANypQFQK2uj6CKd07SrsibFIfcgBw3UH3z79Ip+HOxDfleme9NNXHPclQQkd2Buc2K5eC12+QFWySok+kDulDhFR4kasVpLZmd8Ahs3EWhVk2D1EreYlJNpMaLC4Dl/vLFQrDboAOxTSNlEe4YoyHmdEH1PpHKG/ly34u9wT/V7NNNlxq/G8PvtGIAqDha9jAMXijs3mG0HksEi2oPyBD6v+hXilf1Br8EvexC/59CXufCFituE1REtGPM2iUvJ9MFs1cpyQkw96AQ/ViyVeF24RuPyrabKOp9vZgNLDisKmDDdIuOZ9pajkT1jJ3GLImpIG/ZGWR7PLpiHr8ywEt00hNmxZ60ouf/FbGnWpLX5TxiK8Wd7Jlk2wODQtkKM/aHyh9bygtlb3S/YeWARFlaKdNLePCG5YFHW8mI0XaMAyzsuA+jOW+ZiclD5nGdq5ZYuGKrTfUEn5RtcuFym4F4waG7+h1m3f5ofNzDykSzmdj0GtkhRtfV+jJYBjqqYCvtEIdKEsY2umhY6Qdy96fKElxRUTz7gLRWoDhdmWvIRQggNnNsMorv6C+fyo7U/C7Ja5VOR+OPDuLuCnRQzjqFy0jSH5W4UW4VRfwOm2RbdrUXIbbpFdHvkoOQpnVCN+wLpE8QDbfwafZx7/3LS0SX/tydhWXYPbb8QSctFToGWdxpfb563vM9mfS/BKegTGpCqzcDeY1OOBfl18e69o/U8LRo5dWLYTRi60c1NEVE9zhUacxzOgmAYgWIPDcXsWgTxF/H0tgDsmLFO3YFCAIycYv270nhnUPEz2s1XM/SgHfAuM3nN9CtzXZIgZZXmJDoLp5bCdE6A6ZwVsbxhwYp6MM8tNfneFUrqTDZirOzFIpbM+MuqZ6jgWYtg0Uw5nlvNluJm6SLq7iKyYnF5OS9JQL6bx1igF02SXIhgPY7f89u/eyCpj9gvjJd9IO/BuuB2bnzxH2ZuWgm/cfBAvHX7YgWi1GnLbXh82/Aor5eZJxibXt8OnhyEfpzo+KjfEU1RPJzH9Fak4lsia+Gm2xdpZHwDliW06+jgEXRASZsBy8Vk8urxpvjYuvaJC4zbzTbjKF2M2Y4zn9beqjfLLaMtbgCoiaHvtW3Qgc12pvMqrbyRi3Mt8bt2x+8X8zEePnWn7V0GzKSNJl4u1e9rjMHC8jXRTUMdYQnw5NNdDro7e66i+rbZEX0bzrB23XIQ8jlnQm7SeYbw3MRzcV4IB0fI7kPaR3/7u1wvCx2EvwcjgMnVJ2udN+1Lm3QbzDvymeg0GQdnL/6pFibHZ7qeioygXELrpUwimaHb1qqr55Ftz4rldSZWLzJKLFtI0uEw9tcDsQy+JWvgzJuCkor84MP9b6Ikl7p6lYOBQtR612BDjjbL/o3Jav0pUS4bMjvu1YrlMHxV3VFqZ/xO6xvv1i7B7Q9BqbUXpXKN4PFEpi2eBwC94yD3+GNAp75wPOwDBvUW34jRFnvYoDtcB29oI6l76wFkDtNLORBXD5NJ54ACGy5gnTm030l3ImQbBpyMPAyOe6Gfv2+edVei70M9RWjWvk77lA5Kec4vtkb8inNi13WlRXqiMCUHmduGMxWyN6wymYIUX0m3HCUypWhBMm0yU4SSqcKkr9REQfIX5UlbnaE19GF3e7W/kl5wckiQ96YJ0uOhGQNBiKvB7rA2yvH2Uw8OLuTnmNsvDUV9VKzf2EVQ3G9TeyEVXFpdYGX+DspF3tpPBkSBRBlIBlc6UukvLBd2RVofDP5dJ6JpusqNKNcNSytMGvGORgqke16D3HQA0NQWWqW2Q0L8G6vcRmtPZMl4a9sy1JKK0dYV+ANOaVYA43FizvDM4tv9gsa4PL+TpHs0AKhKUlCitjqXvSLILbsf6eYbRp8vgArZvTqJ3oiQlUBifSfqGcwacI3LD3S3AkxajA6ThtXMSYBqSV3mGKFkLWoHM2FdLRYrL5EfMN/th2wZPl8UUf+Ku8Zwa1uFjRWcz2GdaSX9eNfLZqucCOUOS039rRP0zW1e6MsxY3jP+5O4JWwt2gvooZCIs1Lfd2ZF79ESCNi8/QU1zH6NtL4hQJ3epxuMQSCWMQABLjRC0AokNXZv+OWL6t2psOk5NS+lnUEJfs1bdJ0PnkdhIjW8G2e4ceBC4JopEnwK4pb3ZgvKCtJp1K+73P67+UwDsns1+UTcl4xhN8NgIWowt/oFT0IqjvPHxqVGb1vO4tN/nw0Bz6PWjMCSrg8+Ce2LtltdLoEmOsgWBhzxnX0aoexXQYVukYEJ3nq2WxUqsSsyMhIJL+QKkfh+i0HxKiRlMexnv9rXuKr2sG1TkqBRleG/kPN7pSxTnLz4IxuW8tlLr+fq40//yrOBOLO8T5rHUaWDUuMX6cg7MLHpvq6v0uSNMi7yItaDJ6NI3is6nQL53ekjeXw88b9m9y92shh6+oYufJyz+XpUXz6fd/HzdrHVYXP17Kw9zcYtWGo6jTyhTTzPJ+pk7FRrs3dpuDgiwj29DH40ljXfmkhcE2xycNIuZpviHVMRgVSl3FZpgzj/g7WEJWStQ2dQ2Zy+7Aja5ag6alvS7jqWSSQnJbrGV613zASPktZYV5I5TMtJ5ZRDWRBf6kH0KUF90F36pa3pzibvTaUlC6xv+Lc3d3V0oz57NeJmqJcmO6I8iu0X16ZzvZ2Sr87LSlqrHlDdC79S2aezUwfObfQESzlWwIP/+UHQc6lUhgAL0qnJZSRuDC6zI/mF+X3cGR6eJ/0D5qwoxuFxIK+f8jSlQM/HTCo4OybyXv1l4n/eqa5Qn6o4fy7DezNW5xwlMpHJdR5WJDjqqq5HaSy5OAM2cc54gY8+q0cpE/GwG/rf9OfYRdP7F5J+RCyRKd0iHuHqTsjq7O8rwY7rwSzTASneGfdAov03IfA/s8SZIYEE9nHb0jzSH7wyHrqyZtwylapoapsFpN5zPsQvSwCk7XyRhzqfoEVyedrk+7PSgoglcnBJyqMfIhMKf7hWF6HBCFCAyOr4GuVoLk3jrJfGGY5mJDWhrVNTxLLrpUb6D0ifACXMq57p8rLub81qNyjUNS/8eTylum3QObTr6iZ2PCeA1O+jveIiY9BPsQ0DcEVvpN0jt5yxmRHzVOppoGapMw3eipDMlXgXSzZb8Rz7tHtM/jTs+GNqE0pI7Mdy49op4aixyiWCaStIzGg13ajhLxbRaTAqP9y0pWD2Q/CQBZXI89JF+rFBKk/YB1hp81Pszw2bKrzshl2ADnBsRrd5zZ/3GbqVMYupQS/Uf9ncHQW2ZDjzdVlwSQf5MRP/jOJByb0On8TgcS7oeXxCCnHOM7MxzgPfsPHOiJM+RV9Bv2nLiVsnjxavlkQNIfQhPeJ/qE65jiRdpghA3BwcGOH5oc15J66UPkGzOiF0B/YGk3Bzt1RKFL2La5AqF4s/M3P+VflRec+8Q0NJxyg0b3xEtKWf/McR546/qFNj4Pau9YtvtweEJ5pAy1NHgss0j8vUT6AIBAYyBn4VzsRmrkAGsro/HA+JiOwtwMZdpQ6zA6gONCDnirmFWFen/3pgvNLlqKtet1crOOJCtsADwMqjNigNLFbdgAgUMQES+uwn5zJHMhDgdfe79xtmt7jiIpfDpetSeamyUqHs4MRYY0tIbWnee4zSykDrNN46ZDYU0XVt+6E6f23ukP+G1gBMf8l7TPoGyF7ZtaO603urnzbamqXfbE6b4IrQVgqzz7rPsTWopx0bvwbsPNsFP4OcmQb7Sdui1FdihPSxai+1Ux+74QcHQhTRHVPm82CKdin91vjf5kx9A5TrTMkw3hgzAwX11u5CDuX0N/a4o4PobhcB4r/LNNQ14f48oAAZmOk2AYpP/OUrrGAu83GoAjSsQ4JnLNgNApL5eFyht3kFsmDbsgIaCNmiAmuIl+6gAovLtJ8P9Qt9tXnrbuxHYs4rmNDEAcxVdmGZphubM0g427wwJehig8qwZaHO3tdEyIHE7IJ7oY5lLboHhrhwiLaGFxkP3ar9RDdOrAcB0x1bQx7tvFh5cO28CQ648AqlcZXbSZPhu0nSNMF6yRmyVt9sFBbAxPYhTJ3W5mZFWzWiTa0InUkJM241/mPa1FN3y+tsweYkUlaGfR2xH5DveUhoTldgb0XJHcEBInYqU3MaBnBVM6JOLtMTE54w7bJIZZ9VJvVFpHAUMTQkFq9hK9pWCkqTTxkFTNP4ieeAkJJ1qImgcAGxGRF6RLVtZRgi/QZhXSDPFazp44CJZ5bqHWk4fXhehbTT8H5hoHu1Q3k66hjoVNm9pM40z6lxAjvAUDtrTJNf9We81eLjha62sU4Rq/8602ph//7RimX6kEWYf9FxsSHSiRYwI/8Q7NVjiN6ISyZIfdMRqO8+R+kwEymVo+kQ5nWbqGIJ2Ueaji1SpxCUnfx0b+XVelP7nJsNeT9ryLSoawI/4B6CmSEi3oCAOI9wps21r7eRVJJntHXcFI7z0TjVE1Rxam5M2YRWrjTN4uNyGqqDWJ+t4IUjUXhCzZU2j71ra1lfW9Vt42cLPZ4sxihbdzVu26KFOgJm76EMxDJo8hyzTa9qJk58xcyYPuAGvp0UB4LmZ9XCa5U1PbOXMEWE5os0fHIdf7tDgKUH3esRmQiZwfpIouGukNLWwjmWLFgfHrGOWTU5afw06XZMEBJLwJZwjeRzqLzP1ksYeYXMuPQCYTUCteuwaQb8zsSN5mgyO7GH8GvZMVxvaSC2c20cmmUgXlt0d4n8mEbmQ9zw1GLjhUnnJsH6SLseLLvpymbzg1+W9hu3qEBr5lvo0+hHDkTZ6P1S+HZguPQ9GKj28FW5Uw/z24qP21KtW4zv3XcdPcgKP0fMm7gfH6Rx8K6GFmgCjV7n7aKXeaViRS85wEnP86w06eYKiqWLfH078kzFz6ajA2KZzzdoobI5gvDgeYHoNo3UURhN4qKVskChUEkGkqz2Rk1YIrNcojDOzo7Bm4uY3B80jFBRXT0ZEJH460hjI1hhLEKwKzOmYtzBt1bPp3BW6/cgYvijtdcWI12Fm77mm9U5YmO9A75dzSB0Fzpvnms9qLFqupgFJ5J2+hXSmgvBF0XK3Qh/I/F+gxJO6uYdHdqGWOSoZ03dohby71zugtGAi7A3kP3DsTpl73al2aW3o7mEaTe1lQK1p5Rclgmio9SjdDZv2a9KQtF728YuK0hLsVBRxBr6nzDMelNwBOFhbEPR/Dri4fxPs61npgRjH/0PgVEHbVTVNy/0sf9VoWLCLip1nTloWVIQWjXCGmG1oDcmUmxKYRr9At+WlwFJJ3YH+mLzTQw3XRFwvJlN9k0qcRO0Cb42s7Z9ZHdjgcr9SDnMb81L4nn+zJ2hTcj2QW1O35ZTzynlDJ8xXiUi5FaeajuQq5ncryuyJufSon9qlcNw9013bg66qZMmkJAUkON7+i9FyiJlztDn9jeO7kA+b+oD2f24neuJKstQjHdzRDIJmb57i2EAloDrbl1kL4qZMZDZkiA/iISWXYw4G428iaL9inmDWx5X45AnU51pvisDUYcVs6IFuVdWs3Q7J4Xmmim6wjddJashNBc5hh57g/GqFWS/9I+dsnTF6YMxRZY9FmRcFooKTK2SAHhyzZtwHAoO0jrSaMGNQBHuaZ3zjN+VZ+5f2d/qLbpFujlVaTzOswYNJTGl+XDnCfOOqU7OZxVJnPt2f1fnUFGX+cU6QWKQqg6M+rVEOjl7+YA9rYWAzCX1KxR+qFludziVdXNsUQmjg+C+0ecMjJ39x9wi6HAdykxxnFJUzMmZZYiBljioK394aNjnPKr00dT7bxGxycDlejOdiBW7pF7xOkVbCDeaMxgeDm+rpOhUYZ2ExK0PMljc3H2PGM+kvhrxR+uQiGyumxs77t9sN26jUp+K2emAsu1bmtgK/Qldb5aPNTDarP+RtQHfbps6JVqi324Y9Pa93mBb3eRW5G0mgUEi9kyMtzFplA/iRnfEJeQ9a8AWR3hPxqiUZ7W9jQSrB9CaneoYhgGPX4pprG31vezO2dr07muPVIYD82eOt0rHs6a35vFxkoT47SOcpHyCYsLzRloyq5RyQe4kls9qZJp6zJHEG4y5Q5teUQfLEJcQujipcDZuCRaLmfj13Pyk+SJrAyTz4SowUOcpQAxNXbNizgc4JGpCF6sfNlnLDHuuNQLscn0cRJY5apguhe4ZJdGUiyjJV+U6BfsJIhfLbzYV+pEiYgMoDbu7s+7xhDSr7nFSO91jP/PyFJboXuUF0RdOEPD2lrAzIg8D6PXMypP3GOLUE//qPE9dsUivU0fC+JJwuDfqlK8P2gxej87lodBcuxF8KTzTs1Q0XX8AfHPXtiJh0DHnebclSMeIIG1TgMlSfIV9A/1IR9cwJoyK22cUV+eeTujlFAbTZkCMFQ1VelEAb4WojU3wQTSeyWnmTs45APBjcGqM3jDPDxFQxQqR2GewVcxKkpoI6q+rMZc4kPvgIXKtsz2U3jUPhCa4NMOR0vi6qiXwy6ub+ujTvx3LTDsM3arJFferUFRd2qcd/1ZLBJuUWDH4Ssvr+SB2XGx7Ii9p1crZmkSc+m2gx5LIjGfq63tOvBjjvq1RN2i9XoebGkvfs0zExi7jIl0XN4qLdigFiV7IfPsir80JCPmCe4x6SjiZQCw1DrN51U3IztVOwNc4wYj0ydQRsx+FPoXml6Wj7jV1xV1p7IakMnTnfoAGTxIPtthCDlY5Vt5B7Qf6NkFD2xLglB66d4iVVzHJBMDukzSyzGjnNAtnYyOgC9b/hJATw8x11w+xemA7MlnGV4ox1B+m5Mott6ArayRUt+71YZ/5EHWljyXOmjUO66NRXuWG9HiVjXP4tV1KeK5ahXI+ms4onsafgB7JCKSayKJKjlEhPswoo/7zaogNt0XMrvHXuu3z2QE4jBvjJhxxEFlW1hX0Dam4nvxPASVtNCqQOKpsJMqoQYI/9PXO03C9gSHU3JTfcqRiaKEqs8WSJdrQOTI1E1iL5q5VLXfxoBdRa2quL5RNjLeV5Zs1+XL1NdH5dsVMfKPjtBh9/+4s1xniH6BQ3ML8FMJnfKhekAJbsJ5PENEv6I+nFMI9XLAjxeQewXMZN0MzqtCagAT+WZ56y1RiCMnjwRbY0EDRAxwYfDHLidZCwcY/E1PaS6jo7Dd/v+Rs9QN9kwTxB+KymBDOfXMPE3Gw5xkP6hEUx60v/zSaM613EiYsf+MFexo4s/G8n6BLHIStrKZFks3i7hSy8eFwKTCF2QaCeovyoyjDK+2ybPCogpnN8THlo6c8VQIK9YUTplFp3yBcP8g7U6oXyhF+RUiWcU62XsVsOvaULjpksv5smcs87Qyyl70WLk2o/y6U8dN0v9GOHyjo9lE+Ve7G2tN0rglNqCuRFCryne65BUxscyKRHEilhmMQkmFVQnU/piudMykzgrdl4dKENh65V3dKrbCUhlU8jA30qJjB13zUzeLJSwUO5d/FCJswTann+ZZ4j+HSi5IFVCybDu4Nn1dn9jGVnqVYE63zkJSVkvfm
*/