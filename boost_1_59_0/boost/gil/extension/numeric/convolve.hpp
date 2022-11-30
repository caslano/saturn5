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
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
*/