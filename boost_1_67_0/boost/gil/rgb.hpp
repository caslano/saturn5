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
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
*/