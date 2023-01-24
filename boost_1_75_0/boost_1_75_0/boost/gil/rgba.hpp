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
NmjHPmByKuPde243LChKLfVjdIx5PJZb1Yt75mQeKxMC3YoyXEMn2NUGD+uPXnaTfV+oUz2bKX3rvsNxuM3LoQ5Hm1gwzC9dIg8tO1A5fUSTPIi5AYtY5aJTsh64z8VnOL7Ty/USk6wHUsvvokNlBTwWT5UOYReSqrJFCryZaSeUUWniO7J+AygHIWrjzgiUTU0bCwCFc4YVApgI8ZBVEbu99tUBxoD6ra+tD76vgpK+1flnka1VQoOQWZXK/q6IsGVVliueCYiOlGnCsI8/i6pR8C497FzGlL/TXHhArIzr9/YOjC6cbO7CfOdlKBTwUxFxws51AK72WndaZyJXNa7Gt71WN0Kbf3U4BSkbJaXIPD0NTFd+6uXpvYMAnyvrZBbbr8OWpfyLMlgEH5XXalVt3lfFz5ZtaDEYngobzOViTm+uBPz1OrlbX5yTzh7xPPvPnG+e8J4Q8MRhq5UnXHC++RgHb3HNgueKT04sN8yKXBbjldcsKnfXz9a11ET5edPZMk78pnlO0ghEZ0idmIj7268dMMYoD+L9nBraB0i3etbkKtRT91vZBqeWsIq83h2PaQonqC7aCXc+Tz2PfmFiBs7sbHOZUXreHCIYG8hebe/MO9vXTB5CT5PSHgIYPTk5BnT95SLRP3kLKP5eJuGRO7cUc4rXqbZG0+TL9kQqPHiOrC87YQqiJRQixCDsfRCRKVoPBDr+mKDD
*/