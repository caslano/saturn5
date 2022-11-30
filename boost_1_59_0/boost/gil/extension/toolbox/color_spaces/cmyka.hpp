//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_CMYKA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_CMYKA_HPP

#include <boost/gil/cmyk.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// \ingroup ColorSpaceModel
using cmyka_t = mp11::mp_list<cyan_t, magenta_t, yellow_t, black_t, alpha_t>;

/// \ingroup LayoutModel
using cmyka_layout_t = layout<cmyka_t>;

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, cmyka)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, cmyka)

///// \ingroup ColorConvert
///// \brief Converting CMYKA to any pixel type. Note: Supports homogeneous pixels only.
//template <typename C2>
//struct default_color_converter_impl<cmyka_t,C2> {
//    template <typename P1, typename P2>
//    void operator()(const P1& src, P2& dst) const {
//        using T1 = typename channel_type<P1>::type;
//        default_color_converter_impl<cmyk_t,C2>()(
//            pixel<T1,cmyk_layout_t>(channel_multiply(get_color(src,cyan_t()),  get_color(src,alpha_t())),
//                                    channel_multiply(get_color(src,magenta_t()),get_color(src,alpha_t())),
//                                    channel_multiply(get_color(src,yellow_t()), get_color(src,alpha_t())),
//                                    channel_multiply(get_color(src,black_t()), get_color(src,alpha_t())))
//            ,dst);
//    }
//};
template <>
struct default_color_converter_impl<cmyka_t,rgba_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        using T1 = typename channel_type<P1>::type;
        default_color_converter_impl<cmyk_t,rgba_t>()(
            pixel<T1,cmyk_layout_t>(get_color(src,cyan_t()),
                                    get_color(src,magenta_t()),
                                    get_color(src,yellow_t()),
                                    get_color(src,black_t()))
            ,dst);
    }
};

/// \ingroup ColorConvert
/// \brief Unfortunately CMYKA to CMYKA must be explicitly provided - otherwise we get ambiguous specialization error.
template <>
struct default_color_converter_impl<cmyka_t,cmyka_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        static_for_each(src,dst,default_channel_converter());
    }
};

} // namespace gil
} // namespace boost

#endif

/* cmyka.hpp
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
*/