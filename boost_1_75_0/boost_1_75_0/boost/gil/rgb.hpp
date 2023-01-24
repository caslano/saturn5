//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_RGB_HPP
#define BOOST_GIL_RGB_HPP

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {

/// \addtogroup ColorNameModel
/// \{

/// \brief Red
struct red_t {};

/// \brief Green
struct green_t {};

/// \brief Blue
struct blue_t {};
/// \}

/// \ingroup ColorSpaceModel
using rgb_t = mp11::mp_list<red_t, green_t, blue_t>;

/// \ingroup LayoutModel
using rgb_layout_t = layout<rgb_t>;

/// \ingroup LayoutModel
using bgr_layout_t = layout<rgb_t, mp11::mp_list_c<int, 2, 1, 0>>;

/// \ingroup ImageViewConstructors
/// \brief from raw RGB planar data
template <typename IC>
inline
auto planar_rgb_view(
    std::size_t width, std::size_t height,
    IC r, IC g, IC b,
    std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<IC, rgb_t> >::view_t
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC, rgb_t>>::view_t;

    return view_t(
        width, height,
        typename view_t::locator(
            planar_pixel_iterator<IC, rgb_t>(r, g, b),
            rowsize_in_bytes));
}

}}  // namespace boost::gil

#endif

/* rgb.hpp
yZSOedrnmhx5eSX2Htvcw8tlC33McO/pa1l+OqqnWyYzQx253AbEGGbTb3CE1tk8Di2K4Qh9aX5PZDOcE+jr3Ye4XjLhL30U4GdaoBe6Rb7G7OZSQ5ngEvMm0GX43juAebSwt/Stq6V3enZbdzan/V0/0B766feMEHFY4ucpjL7JBk+4LBrYZzkd/m37TcNcshfI2ePo+WjFIKxMXPN4Koylu9dL+Spzezbfvj85e+PukI2KHUcqbET8luvd+/iCgvmskfQd2+AnpjVsNcRe9i8L4a077vThK68bbG/qradn9+kHCo0UZAaaiaQr6PapSPliZAA/RD5YPmQqeEr2/VNuny71IzzxBc8Y3JnRmfCWypjcWfCuS7EV1ZvdGd2ZvQl2HWEbzB70PQSU05B+dyt4K4Q/2GFAL7gDLcnKPG+CJfp3Q+m7ON2cYjO2N/8t0r7QfuA+6L7oyomBNzHUc3r8j5IsdDzoX2s8uNwv1GZnnbgt8d4t/V7e85dyo0vgMck5sZurxWaU6AWq35dyVKZYcwQtaWEVVwh7T9f89dlufKa6X5UFSmPN9Wk2YwpPuVb5jkvOi+0bXvOJOe0Zp8i6sMNEQrZ/lnACjFlyWNCVjCp3iohEpDjoMG4SMFtIp7jKlBaJrruHCYTMeSoHQ82oD1NXhJ5WvEAgyC39VQKwXx/PV/j9mSMxkDeEFyPq9q+tSdfseF2WLtYc
*/