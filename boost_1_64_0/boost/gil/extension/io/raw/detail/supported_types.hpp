//
// Copyright 2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_RAW_DETAIL_SUPPORTED_TYPES_HPP
#define BOOST_GIL_EXTENSION_IO_RAW_DETAIL_SUPPORTED_TYPES_HPP

#include <boost/gil/extension/io/raw/tags.hpp>

#include <boost/gil/channel.hpp>
#include <boost/gil/color_base.hpp>
#include <boost/gil/io/base.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

// Read support

template< typename Channel
        , typename ColorSpace
        >
struct raw_read_support : read_support_false {};

template<>
struct raw_read_support<uint8_t
                       , gray_t
                       > : read_support_true {};

template<>
struct raw_read_support<uint16_t
                       , gray_t
                       > : read_support_true {};

template<>
struct raw_read_support<uint8_t
                       , rgb_t
                       > : read_support_true {};

template<>
struct raw_read_support<uint16_t
                       , rgb_t
                       > : read_support_true {};

// Write support

struct raw_write_support : write_support_false {};

} // namespace detail

template<typename Pixel>
struct is_read_supported<Pixel,raw_tag>
    : std::integral_constant
        <
            bool,
            detail::raw_read_support
            <
                typename channel_type<Pixel>::type,
                typename color_space_type<Pixel>::type
            >::is_supported
        >
{};

template<typename Pixel>
struct is_write_supported<Pixel, raw_tag>
    : std::integral_constant<bool, detail::raw_write_support::is_supported>
{};

}} // namespace boost::gil

#endif

/* supported_types.hpp
YOKNCo1lhQzNtv9nqpBvr/VVm6a199VYvHGa7R0Y1RIlFkgqb9Jsr/FbK3prqtle4LcI0o8dmltldoP7LhU8c6kQhiv3oCcus8cRTyNuKhrwajHUL9U+auSjukBD4yE0FKpOsUDd+Za/3RmppO2CERADvzWY7m0hvqgwK/n3m0jD06Uyu9Td6JxIYahqgrqFxn8G69ZoYHGrAfHpDlKverUqaAimph0Un+8gLsy+z+CvxLcKuS6IXu0f41Jd8W51k1hWwey7hXgZELMA0GP/zG91LQeuOujd6h/j0byJm38AGGKL/xCtiE6ow6D1aClvMB5TiBOnTjInAJHi0jqshXwa8Cs1ElD+k8ao7d07NGqTUKJesxdYeHjalE6RaPSAZnurlsXd2pXfz2IvGG7i0na3Y/Qd225WgguRYS+IlJV2I5sFN1ZW6oZKkZotHnQQi+Pd+fdHAqwAYMG+XHGMxLfjNqpYKhYSyh7Iy9VI4Sw/9YqmmtbcxWggRNtSoxlNquIdyFuEPCJReLejsTzL57KmdyTatKDcQ23uRv20Mrz9BW/WdZFNMBi6Oxpr1txPCLOvJsob/NKUDRZ91EwhLBN1LAmQRfferBz9qOtLykHny0yTEkk0DUxOIvpboXF1v08zeW5AjVTUFq2JnhJLEtL0l3twjg1F53oxst6ErB+QVfYtbGzYRc0255o0jOZiauEtyaP3UyJ1uzmOKiRAQ5F7iDkX+zY1FVFumMOkSGkOHzghJxRXJE8oJP1RgbA+kDInDClYFIEef3DcUIrbeoaUIhslaQdd6gW0pX4LqxgvjV4jl7ZJ86ff5K0im5c/w+Saq5Fpm2bxlWqVz7ryHcnDYZRSHGoFmzi3Wizt0+Fq3T7lavXtG8xTu7F5juHDXVrA1ePIlPPE01Tq73DN1he1XL5qzbMCTNZsqXhVHcmpRSLSd9SE/oJO2d/B6IQ7f2ky9ShTfTQhU52alKkeHxWQ86c+Afh/NKZOzEieGdZ1pu6WoZ0jFW9T6zo70llIex4Dc3vQvJ28zbAR1tz3UR12ugbtx2i2nTU8ybfvGY1GYy+mstXg/qLugM6oO3krQ2g9IJ2u2wxrkkEWbVSA+PHRNQIoLYxnuraGrJFDsw3TW3lGtvJVD2rF4u9IrZSige9T0YBVNvB3amDv1noNhIxce+DGE9ZQPMPggTow5eUN/QudSW8dM5hU4kjur+EPI0e9KI5vIxYji7GXgl5xaBvbwhYutYQxk7FySfS+mcn9lTlJ4vAzJqLzSndW+0ncCb9b3SH+WAZd7iC+RrlDdSf3R+lzHVmltwIWQERTkugIMOrLeDTFbaCj4VYM+vX54OjRuvLtwPKdcXdYvs8i7YlDS4/eChY6iAIbCSOppo4w0pBNnXuuTHp4sZK1qfXmj+JaTdNZa2X4QBimof8haXNI2tIOkjNERmJbN4iut0Z49qNxGvZOZ5o/bZd4fSuxdc7dANrYjfn2EtHbppRF/gHV+5HT28RAFj01+2iA3h145ylGZqH9evp/RPJnzAGXeg3gwJyVHAlL84oZpZGl0lr3EClPs9DssvFPU1ho7Gw40MbiEqbjFqJjGOp8Se1hvriCSefXChbWL0KQYB8s2XGvJCVTrcmiafOim2S2y3MnCS7FrWIqL3J3+taaCGsd38e6rml8p2+90XBvwbxzubu8lvxhpsqItINZ8BtaqrszQVaLGk3LzIuiHsRV3kdOUHRmiVxCIG3Lb9naBbU7Vw2G50VLqGZkjaJdJdGK4ZSzFNkDhm/CPUmyjwwLNMzP/tSJyT8YpvOnrrrpdCS78Jp4XzTWJGoNNZOi2QouQUq7vqQZw6H6NdvaS2TWyjQ=
*/