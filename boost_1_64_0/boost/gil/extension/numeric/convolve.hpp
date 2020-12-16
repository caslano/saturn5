//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2019 Miral Shah <miralshah2211@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_NUMERIC_CONVOLVE_HPP
#define BOOST_GIL_EXTENSION_NUMERIC_CONVOLVE_HPP

#include <boost/gil/extension/numeric/algorithm.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>
#include <boost/gil/extension/numeric/pixel_numeric_operations.hpp>

#include <boost/gil/algorithm.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/metafunctions.hpp>

#include <boost/assert.hpp>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <type_traits>
#include <vector>

namespace boost { namespace gil {

// 2D spatial seperable convolutions and cross-correlations

namespace detail {

/// \brief Compute the cross-correlation of 1D kernel with the rows of an image
/// \tparam PixelAccum - TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel - TODO
/// \tparam DstView Models MutableImageViewConcept
/// \tparam Correlator - TODO
/// \param src_view
/// \param kernel - TODO
/// \param dst_view Destination where new computed values of pixels are assigned to
/// \param option - TODO
/// \param correlator - TODO
template
<
    typename PixelAccum,
    typename SrcView,
    typename Kernel,
    typename DstView,
    typename Correlator
>
void correlate_rows_impl(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option,
    Correlator correlator)
{
    BOOST_ASSERT(src_view.dimensions() == dst_view.dimensions());
    BOOST_ASSERT(kernel.size() != 0);

    if(kernel.size() == 1)
    {
        // Reduces to a multiplication
        view_multiplies_scalar<PixelAccum>(src_view, *kernel.begin(), dst_view);
        return;
    }

    using src_pixel_ref_t = typename pixel_proxy<typename SrcView::value_type>::type;
    using dst_pixel_ref_t = typename pixel_proxy<typename DstView::value_type>::type;
    using x_coord_t = typename SrcView::x_coord_t;
    using y_coord_t = typename SrcView::y_coord_t;

    x_coord_t const width = src_view.width();
    y_coord_t const height = src_view.height();
    if (width == 0)
        return;

    PixelAccum acc_zero;
    pixel_zeros_t<PixelAccum>()(acc_zero);
    if (option == boundary_option::output_ignore || option == boundary_option::output_zero)
    {
        typename DstView::value_type dst_zero;
        pixel_assigns_t<PixelAccum, dst_pixel_ref_t>()(acc_zero, dst_zero);
        if (width < static_cast<x_coord_t>(kernel.size()))
        {
            if (option == boundary_option::output_zero)
                fill_pixels(dst_view, dst_zero);
        }
        else
        {
            std::vector<PixelAccum> buffer(width);
            for (y_coord_t y = 0; y < height; ++y)
            {
                assign_pixels(src_view.row_begin(y), src_view.row_end(y), &buffer.front());
                typename DstView::x_iterator it_dst = dst_view.row_begin(y);
                if (option == boundary_option::output_zero)
                    std::fill_n(it_dst, kernel.left_size(), dst_zero);
                it_dst += kernel.left_size();
                correlator(&buffer.front(), &buffer.front() + width + 1 - kernel.size(),
                           kernel.begin(), it_dst);
                it_dst += width + 1 - kernel.size();
                if (option == boundary_option::output_zero)
                    std::fill_n(it_dst, kernel.right_size(), dst_zero);
            }
        }
    }
    else
    {
        std::vector<PixelAccum> buffer(width + kernel.size() - 1);
        for (y_coord_t y = 0; y < height; ++y)
        {
            PixelAccum *it_buffer = &buffer.front();
            if (option == boundary_option::extend_padded)
            {
                assign_pixels(
                    src_view.row_begin(y) - kernel.left_size(),
                    src_view.row_end(y) + kernel.right_size(),
                    it_buffer);
            }
            else if (option == boundary_option::extend_zero)
            {
                std::fill_n(it_buffer, kernel.left_size(), acc_zero);
                it_buffer += kernel.left_size();
                assign_pixels(src_view.row_begin(y), src_view.row_end(y), it_buffer);
                it_buffer += width;
                std::fill_n(it_buffer, kernel.right_size(), acc_zero);
            }
            else if (option == boundary_option::extend_constant)
            {
                PixelAccum filler;
                pixel_assigns_t<src_pixel_ref_t, PixelAccum>()(*src_view.row_begin(y), filler);
                std::fill_n(it_buffer, kernel.left_size(), filler);
                it_buffer += kernel.left_size();
                assign_pixels(src_view.row_begin(y), src_view.row_end(y), it_buffer);
                it_buffer += width;
                pixel_assigns_t<src_pixel_ref_t, PixelAccum>()(src_view.row_end(y)[-1], filler);
                std::fill_n(it_buffer, kernel.right_size(), filler);
            }

            correlator(
                &buffer.front(), &buffer.front() + width,
                kernel.begin(),
                dst_view.row_begin(y));
        }
    }
}

template <typename PixelAccum>
class correlator_n
{
public:
    correlator_n(std::size_t size) : size_(size) {}

    template <typename SrcIterator, typename KernelIterator, typename DstIterator>
    void operator()(
        SrcIterator src_begin,
        SrcIterator src_end,
        KernelIterator kernel_begin,
        DstIterator dst_begin)
    {
        correlate_pixels_n<PixelAccum>(src_begin, src_end, kernel_begin, size_, dst_begin);
    }

private:
    std::size_t size_{0};
};

template <std::size_t Size, typename PixelAccum>
struct correlator_k
{
    template <typename SrcIterator, typename KernelIterator, typename DstIterator>
    void operator()(
        SrcIterator src_begin,
        SrcIterator src_end,
        KernelIterator kernel_begin,
        DstIterator dst_begin)
    {
        correlate_pixels_k<Size, PixelAccum>(src_begin, src_end, kernel_begin, dst_begin);
    }
};

} // namespace detail

/// \ingroup ImageAlgorithms
/// \brief Correlate 1D variable-size kernel along the rows of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void correlate_rows(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    detail::correlate_rows_impl<PixelAccum>(
        src_view, kernel, dst_view, option, detail::correlator_n<PixelAccum>(kernel.size()));
}

/// \ingroup ImageAlgorithms
/// \brief Correlate 1D variable-size kernel along the columns of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void correlate_cols(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    correlate_rows<PixelAccum>(
        transposed_view(src_view), kernel, transposed_view(dst_view), option);
}

/// \ingroup ImageAlgorithms
/// \brief Convolve 1D variable-size kernel along the rows of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void convolve_rows(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    correlate_rows<PixelAccum>(src_view, reverse_kernel(kernel), dst_view, option);
}

/// \ingroup ImageAlgorithms
/// \brief Convolve 1D variable-size kernel along the columns of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void convolve_cols(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    convolve_rows<PixelAccum>(
        transposed_view(src_view), kernel, transposed_view(dst_view), option);
}

/// \ingroup ImageAlgorithms
/// \brief Correlate 1D fixed-size kernel along the rows of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void correlate_rows_fixed(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    using correlator = detail::correlator_k<Kernel::static_size, PixelAccum>;
    detail::correlate_rows_impl<PixelAccum>(src_view, kernel, dst_view, option, correlator{});
}

/// \ingroup ImageAlgorithms
/// \brief Correlate 1D fixed-size kernel along the columns of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum,typename SrcView,typename Kernel,typename DstView>
BOOST_FORCEINLINE
void correlate_cols_fixed(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    correlate_rows_fixed<PixelAccum>(
        transposed_view(src_view), kernel, transposed_view(dst_view), option);
}

/// \ingroup ImageAlgorithms
/// \brief Convolve 1D fixed-size kernel along the rows of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void convolve_rows_fixed(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    correlate_rows_fixed<PixelAccum>(src_view, reverse_kernel(kernel), dst_view, option);
}

/// \ingroup ImageAlgorithms
/// \brief Convolve 1D fixed-size kernel along the columns of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void convolve_cols_fixed(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    convolve_rows_fixed<PixelAccum>(
        transposed_view(src_view), kernel, transposed_view(dst_view), option);
}

namespace detail
{

/// \ingroup ImageAlgorithms
/// \brief Convolve 1D variable-size kernel along both rows and columns of image
/// \tparam PixelAccum TODO
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename PixelAccum, typename SrcView, typename Kernel, typename DstView>
BOOST_FORCEINLINE
void convolve_1d(
    SrcView const& src_view,
    Kernel const& kernel,
    DstView const& dst_view,
    boundary_option option = boundary_option::extend_zero)
{
    convolve_rows<PixelAccum>(src_view, kernel, dst_view, option);
    convolve_cols<PixelAccum>(dst_view, kernel, dst_view, option);
}

template <typename SrcView, typename DstView, typename Kernel>
void convolve_2d_impl(SrcView const& src_view, DstView const& dst_view, Kernel const& kernel)
{
    int flip_ker_row, flip_ker_col, row_boundary, col_boundary;
    float aux_total;
    for (std::ptrdiff_t view_row = 0; view_row < src_view.height(); ++view_row)
    {
        for (std::ptrdiff_t view_col = 0; view_col < src_view.width(); ++view_col)
        {
            aux_total = 0.0f;
            for (std::size_t kernel_row = 0; kernel_row < kernel.size(); ++kernel_row)
            {
                flip_ker_row = kernel.size() - 1 - kernel_row;      // row index of flipped kernel

                for (std::size_t kernel_col = 0; kernel_col < kernel.size(); ++kernel_col)
                {
                    flip_ker_col = kernel.size() - 1 - kernel_col; // column index of flipped kernel

                    // index of input signal, used for checking boundary
                    row_boundary = view_row + (kernel.center_y() - flip_ker_row);
                    col_boundary = view_col + (kernel.center_x() - flip_ker_col);

                    // ignore input samples which are out of bound
                    if (row_boundary >= 0 && row_boundary < src_view.height() &&
                        col_boundary >= 0 && col_boundary < src_view.width())
                    {
                        aux_total +=
                            src_view(col_boundary, row_boundary) *
                            kernel.at(flip_ker_row, flip_ker_col);
                    }
                }
            }
            dst_view(view_col, view_row) = aux_total;
        }
    }
}

/// \ingroup ImageAlgorithms
/// \brief convolve_2d can only use convolve_option_extend_zero as convolve_boundary_option
///  this is the default option and cannot be changed for now
///  (In future there are plans to improve the algorithm and allow user to use other options as well)
/// \tparam SrcView Models ImageViewConcept
/// \tparam Kernel TODO
/// \tparam DstView Models MutableImageViewConcept
template <typename SrcView, typename DstView, typename Kernel>
void convolve_2d(SrcView const& src_view, Kernel const& kernel, DstView const& dst_view)
{
    BOOST_ASSERT(src_view.dimensions() == dst_view.dimensions());
    BOOST_ASSERT(kernel.size() != 0);

    gil_function_requires<ImageViewConcept<SrcView>>();
    gil_function_requires<MutableImageViewConcept<DstView>>();
    static_assert(color_spaces_are_compatible
    <
        typename color_space_type<SrcView>::type,
        typename color_space_type<DstView>::type
    >::value, "Source and destination views must have pixels with the same color space");

    for (std::size_t i = 0; i < src_view.num_channels(); i++)
    {
        detail::convolve_2d_impl(
            nth_channel_view(src_view, i),
            nth_channel_view(dst_view, i),
            kernel
        );
    }
}

}}} // namespace boost::gil::detail

#endif

/* convolve.hpp
aBZCZfD5Yjk/Mm5woNxIkmdZDkm3LZaVC4PHP07MnPK8f8QX1P9Cwq1ZLqyYgHNkpgPeJc/XAziAcMB1tjAn7rdMGIldmyqE2zZdG7TVd0yep/3T1Wj4PSVyChSt8F5TAR9O+NeAC0NhZRbttxwgzrmDNyj/10b5v+e1S9202l4zu2v4Sg1vY4XHkupIeZsIG9qtxxs6HXQLGjkdK+AiGjgdVeDqwrWA6wCXApcOdz/co3Cj4cbBTYWbCbcAbjFxEH85fhNBrx9cBL7T4GLh6sA1g+sMp/vF5OYx8vSyPMKcjM/Gdw+ybAn2/1a3i9gMBnBcEfB8W1rr46AIYU0WTJDalpDUyBHUlEprTUGwWAW8b4jsSf9436uxjMxCoUw7s2dI3r/Wf7ZjXW/12ZMuy/xfie/Lb+xYh2/Rn2vUMxAF49ITKIt+vLXU4k1smM05vIkVnEA2YbjIiLd5aFzN3H1IrrLe52qE/th+Y0XEmOhMmHLCm5zgWoX3nrsHZbTexy8zD+uSv/BcntNb048dwbORgb7Oby9waxNTMy5UM/eHKH+egHs6vy3xLOwxvWYcjOUcGvdW2MonOtJQ3snz8mhoXNhCJe0AtZLcLpiC3NaX3Ia2/fH962pWpRRtt6o7McbDm2/7XatQo+8aFWn6Hfqelug3mbZ5Yasi8ihzyTplrUc/QNnIz+vKc87efsn+XjG835TFha2KmfMZrkb1jMl6LiYSn2II0lOT8z/gKAEWmZ4x7ONaLpQGhYF8EbHNIBulXJhdlqvsUWqhqliFyuqEyaBYDKV+52uA6RK19zn/UP+WrVn9FPmfyI1MNjJ+EzagtdB+ZfxALviBjuAHRAzcsQK3p0lQKC1jF3LJLpzy13atLm7ETWrk2i7rRg8MTBZpzOdduGZW5LvKU6USIFM1wVV62tMW30mBhG7UgWVWNgCOZPIj7UqIu8ICISstsxNsHSUPpzZnB0aZjOGMT2SNFezF1781X7g14SpdyQzW0fFvpI700BT6j3rq60tFbdEI0Ansi7DlM1HIFneP5uKnujSaM/B87lTdbGOKdGtSjCdscFno3mh9oxCidvUZ15Re8PFVmmT/7Z5sMOCyUP9F7uK3gbH2wodmZ3a8iZqxhZzY3mYy/p4x1G/Iyosp3ca6OuT2X0It1kyLht2P21V48s5gFOKNIaK2jv4Itjx6x+VSaZ9AD2dWycgxAzwLXaumRCbEOx14hLo+fuQR6kCPVzu5010p7vRsKFm2VcOAoeaJpet5Kba+2TbAIduNUCWTJ159zjEWGTO3WOn5FpnP/kJ7eiJ58BWK1SK50dsc/QflETtutrnJHZ9omVggFuew6Nt+onyCMWvCml2tRH4kMr8S9nmN/ndgErQhjOj7Pv4AQrKH5dKiTNonylryYKbP8HyYT5mIFkntM3w9du6p8JakDD+hd9DjhFQBqJinPyuTvT4eqazNI0gBTVLMc74pYoBf9vB5ZtfHQBb1vNhTGJEwyM4Rn2TZ2EsmqTb7yq3H1VyrqtZp862vIoYQTHmehDmnlsSMWRPWEKmNSNY9H1DENSy2/uNIR3j0751COt+dKsM1311AwmYbVmixds83cRFNrlnhVoy5cFGvzGHxkCwtL4c4vzxioYW41EKcXg5xVHnEdyzEiRbig+UQ+5ZHnGAhDrIQe1iIbt0t7xMNmPgDpYWe4cVkXR6aDT58n7/qQjNOqyBM6VaLUlWL/cKEv4sUz32lFHv+e4ptbXptr6J39Del96XzSnrv/Y/0Dq66kt48i97j5ehBgaQgBbRqJWKilPuxt02WnmOWfKQaowANz+TW/GVEM4cE6iuULdkGlYgumiQxgNivG+U=
*/