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