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
lShZQdDkn6xm6RN/lVm57rE/J+HzR6XhvwFYXrKH/8ceDgyWInWXSA+IP1H8veBXon/avDzXQ4gdSJFgI8GdmbGvrbTTYkLMqGplLPlhhjZg6J0aarZgWCGAG5NXrHZHSgvud0gLJm4m/eMlOc3XqyagLmfQmLvPosfqAgWSfiJWyyPLFaQvgD+v37zAF4S5PnVZlZwpUXZq/cW/R/wv0G9rR38GH2ZxGykb106omzTJL6kC6EA/SXVcIt6u/gj60yQjj53RXyToH+K/Wvwtxd+MuO9vIzvDjseioI6cgEzJrBSw9UAA2fJJ6L5jwGuf/4VefegHpQuMdhHQg+RXEKX3BFaI/nvBmcvcoevW4wRaodnmzxO9+QoJfMCoO66WqNyRg+vNuqutoTxI+ZOfDMktKKJUxm1eLq3umsJ8nMH/VpQmlQv+k7ErAauq2sKXSXAgSEPNkRzKOZNMEElRUDAwzDHL0hxyyqmLYoLDQ1K6oFZq1nPKoSzLtNQcE0c0x8wUU9Oyct9HKmUq5nDf/6917mWwN/B9m7vPWmuvPZ599rD2vxflZgTDI/63zGxVx0bhbGtFZtPyTMIv8m8RfSyiD4khFtHbInqTaPOkVYn8Vbz+7Q7F+c6NnSLFfYLEjy0ig7juahD+uoXWUiijmNAdS4i/bqEsL/p/k9qZwgA5Da0CeXmLF9r2485hEheoeIXiBEvDOZf4KO+AxLbHjHekzOtKCCWhJQnJSqhKQj2JZ50fg5NgeiszhUx/YeqVArf4rkQqM47Mf5HQSAm9SThlo3RzkT5EZqAyp5C5VZhNhLmGzIIGwoRytH8SzikhiYSZJBxWwhAS0kjYpoTZrOBR5jM+cZJU4NjFOXClwffetwTegaDN12tLD4KjJnZ/XOgZ1gQH7wbsj/cBemE59AGu2IDB7TOnpZ3n8jwsL9JdA+0VsHyWq8dTJn3No0NstWbrYy5roPSFnmyrvvKOy3ngOkr9IU0N6mI28fuxTG+6PKEd3lnw87cb1yNMvV7lvNb8Lk9+X3v52fKXmQv6tJxPc813eNL73zehqv06DsYLmUo0ktjRUn6j4Tdr3EKdIMTUAcyWvZQaEcLWGs/OzpR83S1Zk+piY5zNSR3tpvoLNdRZTRZn58o4p8MOTXodJN3pBcbUm4fK8yOfZeNHfhP8aY2zpz5ayHFBzaDpP8gZhrlTpD8N17C/XiPM1DTnTuH17S3glCbqDWn3eJIpdZ7p/YgHZTQMPJCrmuMPe2i1QWO2UgUl3u9j7XxXXSVmFiKYuuMxjk1uBgRN7wMJHWh0T3UjzjgeljKfIe14doDcVwGxzL55zsZ3WaBHpUBrCy3LWUVoWUIrD795SsOz2J1/3QGhtRI2UsIJQlx6WlUb7s0YnCnZqipD+O4s32BIcoTI/dw+4JIRCYbzc72oorfEsuKOZOtb7d2aHPMGsD4yxPMffwnpWZDMD8iAc57Shyh9KOl7SZ/0p6horiWznypeBAnzzoUDfWHji34Q46gRzp4gYjc4tSmEB2h8xyEMlSFQaV6DLnDilTPsD2iuihAxjuQAokjHmKfD5Cw9zstIecruEYBw57MmJ6Mcgm3JwVAQoAreher8ZYSIyuZEtTtl95llXFYpiItEUJ7wAFITZRcetkZB0BsXmTafrFhl/YMsrpeDxQGnnkjzW3ZXInmemR17VWCdgpmOgaUjbFEywmdUaxMrwu+nF0XYXVn3WxFuBwvGTZUQ2RMaWW1G5neVuFtzvJJrpadN8bITpepkobCbs0JaIpTzEtCYgRQ81WXDWyhAVutUJIoiFSnyNUWSY9Lvhgp/TjH+H6+D/7EAOkvXl+t37I6vXCXEDIY=
*/