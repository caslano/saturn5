//
// Copyright 2012 Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_GRAY_ALPHA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_GRAY_ALPHA_HPP

#include <boost/gil/color_convert.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/typedefs.hpp>

#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

using gray_alpha_t = mp11::mp_list<gray_color_t,alpha_t>;

using gray_alpha_layout_t = layout<gray_alpha_t>;
using alpha_gray_layout_t = layout<gray_alpha_layout_t, mp11::mp_list_c<int,1,0>>;

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, alpha_gray)

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, gray_alpha)

/// \ingroup ColorConvert
/// \brief Gray Alpha to RGBA
template <>
struct default_color_converter_impl<gray_alpha_t,rgba_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2, green_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,alpha_t()) =
            channel_convert<typename color_element_type<P2, alpha_t>::type>(get_color(src,alpha_t()));
    }
};

/// \brief Gray Alpha to RGB
template <>
struct default_color_converter_impl<gray_alpha_t,rgb_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
        get_color(dst,green_t())  =
            channel_convert<typename color_element_type<P2, green_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
        get_color(dst,blue_t())  =
            channel_convert<typename color_element_type<P2, blue_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
    }
};

/// \brief Gray Alpha to Gray
template <>
struct default_color_converter_impl<gray_alpha_t,gray_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,gray_color_t())  =
            channel_convert<typename color_element_type<P2, gray_color_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
    }
};

} // namespace gil
} // namespace boost

#endif

/* gray_alpha.hpp
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
*/