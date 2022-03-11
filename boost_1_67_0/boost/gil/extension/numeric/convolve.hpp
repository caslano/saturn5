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