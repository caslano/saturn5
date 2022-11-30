//
// Copyright 2019 Miral Shah <miralshah2211@gmail.com>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_GIL_IMAGE_PROCESSING_FILTER_HPP
#define BOOST_GIL_IMAGE_PROCESSING_FILTER_HPP

#include <boost/gil/extension/numeric/algorithm.hpp>
#include <boost/gil/extension/numeric/kernel.hpp>
#include <boost/gil/extension/numeric/convolve.hpp>

#include <boost/gil/image.hpp>
#include <boost/gil/image_view.hpp>

#include <cstddef>
#include <vector>




namespace boost { namespace gil {

template <typename SrcView, typename DstView>
void box_filter(
    SrcView const& src_view,
    DstView const& dst_view,
    std::size_t kernel_size,
    long int anchor = -1,
    bool normalize=true,
    boundary_option option = boundary_option::extend_zero
)
{
    gil_function_requires<ImageViewConcept<SrcView>>();
    gil_function_requires<MutableImageViewConcept<DstView>>();
    static_assert(color_spaces_are_compatible
    <
        typename color_space_type<SrcView>::type,
        typename color_space_type<DstView>::type
    >::value, "Source and destination views must have pixels with the same color space");

    std::vector<float> kernel_values;
    if (normalize) { kernel_values.resize(kernel_size, 1.0f / float(kernel_size)); }
    else { kernel_values.resize(kernel_size, 1.0f); }

    if (anchor == -1) anchor = static_cast<int>(kernel_size / 2);
    kernel_1d<float> kernel(kernel_values.begin(), kernel_size, anchor);

    detail::convolve_1d
    <
        pixel<float, typename SrcView::value_type::layout_t>
    >(src_view, kernel, dst_view, option);
}

template <typename SrcView, typename DstView>
void blur(
    SrcView const& src_view,
    DstView const& dst_view,
    std::size_t kernel_size,
    long int anchor = -1,
    boundary_option option = boundary_option::extend_zero
)
{
    box_filter(src_view, dst_view, kernel_size, anchor, true, option);
}


namespace detail
{
template <typename SrcView, typename DstView>
void filter_median_impl(SrcView const& src_view, DstView const& dst_view, std::size_t kernel_size)
{
    std::size_t half_kernel_size = kernel_size / 2;

    // deciding output channel type and creating functor
    using src_channel_t = typename channel_type<SrcView>::type;

    std::vector<src_channel_t> values;
    values.reserve(kernel_size * kernel_size);

    for (std::ptrdiff_t y = 0; y < src_view.height(); y++)
    {
        typename DstView::x_iterator dst_it = dst_view.row_begin(y);

        for (std::ptrdiff_t x = 0; x < src_view.width(); x++)
        {
            auto sub_view = subimage_view(
                src_view,
                x - half_kernel_size, y - half_kernel_size,
                kernel_size,
                kernel_size
            );
            values.assign(sub_view.begin(), sub_view.end());

            std::nth_element(values.begin(), values.begin() + (values.size() / 2), values.end());
            dst_it[x] = values[values.size() / 2];
        }
    }
}
} // namespace detail

template <typename SrcView, typename DstView>
void median_filter(SrcView const& src_view, DstView const& dst_view, std::size_t kernel_size)
{
    static_assert(color_spaces_are_compatible
    <
        typename color_space_type<SrcView>::type,
        typename color_space_type<DstView>::type
    >::value, "Source and destination views must have pixels with the same color space");

    std::size_t half_kernel_size = kernel_size / 2;
    auto extended_img = extend_boundary(
        src_view,
        half_kernel_size,
        boundary_option::extend_constant
    );
    auto extended_view = subimage_view(
            view(extended_img),
            half_kernel_size,
            half_kernel_size,
            src_view.width(),
            src_view.height()
        );

    for (std::size_t channel = 0; channel < extended_view.num_channels(); channel++)
    {
        detail::filter_median_impl(
            nth_channel_view(extended_view, channel),
            nth_channel_view(dst_view, channel),
            kernel_size
        );
    }
}

}} //namespace boost::gil

#endif // !BOOST_GIL_IMAGE_PROCESSING_FILTER_HPP

/* filter.hpp
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
*/