//
// Copyright 2009 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/raw/tags.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< raw_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    using pixel_t = typename get_pixel_type<View>::type;
    using num_channel_t = typename num_channels<pixel_t>::value_type;
    using channel_t = typename channel_traits<typename element_type<typename View::value_type>::type>::value_type;

    constexpr num_channel_t dst_samples_per_pixel = num_channels<pixel_t>::value;
    constexpr unsigned int dst_bits_per_pixel = detail::unsigned_integral_num_bits<channel_t>::value;
    constexpr bool is_type_signed = std::is_signed<channel_t>::value;

    return (dst_samples_per_pixel == info._samples_per_pixel &&
            dst_bits_per_pixel == static_cast<unsigned int>(info._bits_per_pixel) &&
            !is_type_signed);
}

template< typename View >
bool is_allowed( const image_read_info< raw_tag >& /* info */
               , std::false_type  // is read_and_convert
               )
{
    return true;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* is_allowed.hpp
U9YZ99V1/8WJsym1ZO6cZ1HMSbgIfK/MTlpXzlBKLgy/1EymN2gjUmnhJj/k56eexkXg/dtklAnlrHNwhxDa5jfT6/yV+3TEAdl1THyYlQzeT3J3ouzj9wRvllWOM+Tpcv3Kvr8f9iH22HE0bzkO37Y5QrRD0DHRkJZ0TU3gCIu3nbYoa9V/qLt7yQc9ORtwdJa4nUd+oElcJlrenYsSRpCJF7esJ/mJfKLf3BxugUQ+lG49iKfLr0U+ktuTBLtgP3MQB1U0Bo3RnNcwJS2+2z1KMBU+3SkNJFMhFTakUZMLoW6MmO2ydxSiaaIN+nCVUsZFijDVfyByMRbJb6jrH9KEvmi6rqcTfN03yIzYN/itNYGJn4Ehyjmw8BHBjbmBmtFrPUtRcFD7RKmh8oYZoXiyI2R5C+EGyPwsiq2Lsu6gj+nUCfCAG5wGPYXiPJZ4EA3u0vkxDpaqvMlExRd4oA760m0oXD/BAO/b9voV/ImZo//FAZ3W+Tlv2yjb5I8nDIiD9VlLQWkd5SRx+DlYLYBwxauB+AQ5RexJrsJpxksR02H4F37ddQB6BmY3W2xA/R7ZO4ue61jbFtl7Ima++bt2Y70/1cdW9viUojZg1Ay/h2fUjCtDJCcWtWeBnubSArVmWfBHHvItsttjv8ObS5YSxfACnJBhT+gx6w8A7+1vIk4w+oFar0cNo9ibJszOCsaAYH+FkZjt1bfD
*/