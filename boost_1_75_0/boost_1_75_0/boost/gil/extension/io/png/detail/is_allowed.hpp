//
// Copyright 2008 Christian Henning, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_PNG_DETAIL_IS_ALLOWED_HPP
#define BOOST_GIL_EXTENSION_IO_PNG_DETAIL_IS_ALLOWED_HPP

#include <boost/gil/extension/io/png/tags.hpp>

#include <type_traits>

namespace boost { namespace gil { namespace detail {

template< typename View >
bool is_allowed( const image_read_info< png_tag >& info
               , std::true_type   // is read_and_no_convert
               )
{
    using pixel_t = typename get_pixel_type<View>::type;

    using channel_t = typename channel_traits<typename element_type<pixel_t>::type>::value_type;

    const png_num_channels::type dst_num_channels = num_channels< pixel_t >::value;
    const png_bitdepth::type     dst_bit_depth    = detail::unsigned_integral_num_bits< channel_t >::value;

    return   dst_num_channels == info._num_channels
          && dst_bit_depth    == info._bit_depth;
}

template< typename View >
bool is_allowed( const image_read_info< png_tag >& /* info */
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
4yoEUJHCRXzF2S39xSK+H/4YGsDVz34RHYIteOYDzaJ15WPXk+QveMmPkyNEpw6h5/5ODKPfht/PO0r0C50iXQY3ljhCFV7QZXY2c5jNX0zdSac58j0X3RqdRrddZsI0/pfMfl+LS0+Ir/hjnFEXDvBWel+9+FpwyWBeOl+85x5MPSTXix//OMfVpbl4OoYvUyBO5ew0RGhw+JBrA0Qyz1yga8hYF34nd6U12uTrcd7Sm3t6ONzhI6UwPts4O02+hpsb+VY6ZjJqAZogRHw4z1wk7fEwxp3LCUzCw6iQgqqHMV/LQmKusTpOMZangR1k6gKJcSU38um2yrAu3HO9J0y7ZY1S0lsoDxD+Zz6uAN2H2RkgTNTd8vhuDELKDEM4M98tMxfOdHkfqrMcWWf3klguybG7XoQ9usjLwmxjl+z2Z5Lh9PNmvHdyV8DzXtI3fDkH6DO8/TMQx7ha0RS8y6WuOz8U+BlvPnGG8Ten88XTb/9FrrlulF/BXflgzz/Octy6Xj+852hctlJQPMsAMWEI4gJ/NK5Y+rptinVorUxq2KQUf4D3QIPjAbGqUuy5lMT6IVZUir/yqhjGChDLKMUrt6QxNoCfIpEH6+y7K+6cH+lC+HVJ+gT+ISi0bJ3DexUW+WCFGT5YoYgVee3d4uPtW5jU5WHEVTzUw/F4EJBrQlIBk3poEodJGmLlhzHFSjcnidC6uv06pv9p
*/