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