//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_RGBA_HPP
#define BOOST_GIL_RGBA_HPP

#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {

/// \ingroup ColorNameModel
/// \brief Alpha
struct alpha_t {};

/// \ingroup ColorSpaceModel
using rgba_t =mp11::mp_list<red_t, green_t, blue_t, alpha_t>;

/// \ingroup LayoutModel
using rgba_layout_t = layout<rgba_t>;

/// \ingroup LayoutModel
using bgra_layout_t = layout<rgba_t, mp11::mp_list_c<int, 2, 1, 0, 3>>;

/// \ingroup LayoutModel
using argb_layout_t = layout<rgba_t, mp11::mp_list_c<int, 1, 2, 3, 0>>;

/// \ingroup LayoutModel
using abgr_layout_t = layout<rgba_t, mp11::mp_list_c<int, 3, 2, 1, 0>>;

/// \ingroup ImageViewConstructors
/// \brief from raw RGBA planar data
template <typename ChannelPtr>
inline
auto planar_rgba_view(std::size_t width, std::size_t height,
    ChannelPtr r, ChannelPtr g, ChannelPtr b, ChannelPtr a,
    std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<ChannelPtr, rgba_t> >::view_t
{
    using pixel_iterator_t = planar_pixel_iterator<ChannelPtr, rgba_t>;
    using view_t = typename type_from_x_iterator<pixel_iterator_t>::view_t;
    using locator_t = typename view_t::locator;

    locator_t loc(pixel_iterator_t(r, g, b, a), rowsize_in_bytes);
    return view_t(width, height, loc);
}

}} // namespace boost::gil

#endif

/* rgba.hpp
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
*/