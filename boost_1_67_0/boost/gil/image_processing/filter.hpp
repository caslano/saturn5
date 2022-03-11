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