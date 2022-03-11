//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_COLOR_CONVERT_HPP
#define BOOST_GIL_COLOR_CONVERT_HPP

#include <boost/gil/channel_algorithm.hpp>
#include <boost/gil/cmyk.hpp>
#include <boost/gil/color_base_algorithm.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/metafunctions.hpp>
#include <boost/gil/pixel.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/rgba.hpp>
#include <boost/gil/utilities.hpp>

#include <algorithm>
#include <functional>
#include <type_traits>

namespace boost { namespace gil {

/// Support for fast and simple color conversion.
/// Accurate color conversion using color profiles can be supplied separately in a dedicated module.

// Forward-declare
template <typename P> struct channel_type;

////////////////////////////////////////////////////////////////////////////////////////
///
///                 COLOR SPACE CONVERSION
///
////////////////////////////////////////////////////////////////////////////////////////

/// \ingroup ColorConvert
/// \brief Color Convertion function object. To be specialized for every src/dst color space
template <typename C1, typename C2>
struct default_color_converter_impl
{
    static_assert(
        std::is_same<C1, C2>::value,
        "default_color_converter_impl not specialized for given color spaces");
};

/// \ingroup ColorConvert
/// \brief When the color space is the same, color convertion performs channel depth conversion
template <typename C>
struct default_color_converter_impl<C,C> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        static_for_each(src,dst,default_channel_converter());
    }
};

namespace detail {

/// red * .3 + green * .59 + blue * .11 + .5

// The default implementation of to_luminance uses float0..1 as the intermediate channel type
template <typename RedChannel, typename GreenChannel, typename BlueChannel, typename GrayChannelValue>
struct rgb_to_luminance_fn {
    GrayChannelValue operator()(const RedChannel& red, const GreenChannel& green, const BlueChannel& blue) const {
        return channel_convert<GrayChannelValue>(float32_t(
            channel_convert<float32_t>(red  )*0.30f +
            channel_convert<float32_t>(green)*0.59f +
            channel_convert<float32_t>(blue )*0.11f) );
    }
};

// performance specialization for unsigned char
template <typename GrayChannelValue>
struct rgb_to_luminance_fn<uint8_t,uint8_t,uint8_t, GrayChannelValue> {
    GrayChannelValue operator()(uint8_t red, uint8_t green, uint8_t blue) const {
        return channel_convert<GrayChannelValue>(uint8_t(
            ((uint32_t(red  )*4915 + uint32_t(green)*9667 + uint32_t(blue )*1802) + 8192) >> 14));
    }
};

template <typename GrayChannel, typename RedChannel, typename GreenChannel, typename BlueChannel>
typename channel_traits<GrayChannel>::value_type rgb_to_luminance(const RedChannel& red, const GreenChannel& green, const BlueChannel& blue) {
    return rgb_to_luminance_fn<RedChannel,GreenChannel,BlueChannel,
                               typename channel_traits<GrayChannel>::value_type>()(red,green,blue);
}

}   // namespace detail

/// \ingroup ColorConvert
/// \brief Gray to RGB
template <>
struct default_color_converter_impl<gray_t,rgb_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t  >::type>(get_color(src,gray_color_t()));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2, green_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t >::type>(get_color(src,gray_color_t()));
    }
};

/// \ingroup ColorConvert
/// \brief Gray to CMYK
template <>
struct default_color_converter_impl<gray_t,cmyk_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,cyan_t())=
            channel_traits<typename color_element_type<P2, cyan_t   >::type>::min_value();
        get_color(dst,magenta_t())=
            channel_traits<typename color_element_type<P2, magenta_t>::type>::min_value();
        get_color(dst,yellow_t())=
            channel_traits<typename color_element_type<P2, yellow_t >::type>::min_value();
        get_color(dst,black_t())=
            channel_convert<typename color_element_type<P2, black_t >::type>(get_color(src,gray_color_t()));
    }
};

/// \ingroup ColorConvert
/// \brief RGB to Gray
template <>
struct default_color_converter_impl<rgb_t,gray_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,gray_color_t()) =
            detail::rgb_to_luminance<typename color_element_type<P2,gray_color_t>::type>(
                get_color(src,red_t()), get_color(src,green_t()), get_color(src,blue_t())
            );
    }
};


/// \ingroup ColorConvert
/// \brief RGB to CMYK (not the fastest code in the world)
///
/// k = min(1 - r, 1 - g, 1 - b)
/// c = (1 - r - k) / (1 - k)
/// m = (1 - g - k) / (1 - k)
/// y = (1 - b - k) / (1 - k)
template <>
struct default_color_converter_impl<rgb_t,cmyk_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        using T2 = typename channel_type<P2>::type;
        get_color(dst,cyan_t())    = channel_invert(channel_convert<T2>(get_color(src,red_t())));          // c = 1 - r
        get_color(dst,magenta_t()) = channel_invert(channel_convert<T2>(get_color(src,green_t())));        // m = 1 - g
        get_color(dst,yellow_t())  = channel_invert(channel_convert<T2>(get_color(src,blue_t())));         // y = 1 - b
        get_color(dst,black_t())   = (std::min)(get_color(dst,cyan_t()),
                                                (std::min)(get_color(dst,magenta_t()),
                                                           get_color(dst,yellow_t())));   // k = minimum(c, m, y)
        T2 x = channel_traits<T2>::max_value()-get_color(dst,black_t());                  // x = 1 - k
        if (x>0.0001f) {
            float x1 = channel_traits<T2>::max_value()/float(x);
            get_color(dst,cyan_t())    = (T2)((get_color(dst,cyan_t())    - get_color(dst,black_t()))*x1);                // c = (c - k) / x
            get_color(dst,magenta_t()) = (T2)((get_color(dst,magenta_t()) - get_color(dst,black_t()))*x1);                // m = (m - k) / x
            get_color(dst,yellow_t())  = (T2)((get_color(dst,yellow_t())  - get_color(dst,black_t()))*x1);                // y = (y - k) / x
        } else {
            get_color(dst,cyan_t())=get_color(dst,magenta_t())=get_color(dst,yellow_t())=0;
        }
    }
};

/// \ingroup ColorConvert
/// \brief CMYK to RGB (not the fastest code in the world)
///
/// r = 1 - min(1, c*(1-k)+k)
/// g = 1 - min(1, m*(1-k)+k)
/// b = 1 - min(1, y*(1-k)+k)
template <>
struct default_color_converter_impl<cmyk_t,rgb_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        using T1 = typename channel_type<P1>::type;
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2,red_t>::type>(
                channel_invert<T1>(
                    (std::min)(channel_traits<T1>::max_value(),
                             T1(channel_multiply(get_color(src,cyan_t()),channel_invert(get_color(src,black_t())))+get_color(src,black_t())))));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2,green_t>::type>(
                channel_invert<T1>(
                    (std::min)(channel_traits<T1>::max_value(),
                             T1(channel_multiply(get_color(src,magenta_t()),channel_invert(get_color(src,black_t())))+get_color(src,black_t())))));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2,blue_t>::type>(
                channel_invert<T1>(
                    (std::min)(channel_traits<T1>::max_value(),
                             T1(channel_multiply(get_color(src,yellow_t()),channel_invert(get_color(src,black_t())))+get_color(src,black_t())))));
    }
};


/// \ingroup ColorConvert
/// \brief CMYK to Gray
///
/// gray = (1 - 0.212c - 0.715m - 0.0722y) * (1 - k)
template <>
struct default_color_converter_impl<cmyk_t,gray_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const  {
        get_color(dst,gray_color_t())=
            channel_convert<typename color_element_type<P2,gray_color_t>::type>(
                channel_multiply(
                    channel_invert(
                       detail::rgb_to_luminance<typename color_element_type<P1,black_t>::type>(
                            get_color(src,cyan_t()),
                            get_color(src,magenta_t()),
                            get_color(src,yellow_t())
                       )
                    ),
                    channel_invert(get_color(src,black_t()))));
    }
};

namespace detail {

template <typename Pixel>
auto alpha_or_max_impl(Pixel const& p, std::true_type) -> typename channel_type<Pixel>::type
{
    return get_color(p,alpha_t());
}
template <typename Pixel>
auto alpha_or_max_impl(Pixel const&, std::false_type) -> typename channel_type<Pixel>::type
{
    return channel_traits<typename channel_type<Pixel>::type>::max_value();
}

} // namespace detail

// Returns max_value if the pixel has no alpha channel. Otherwise returns the alpha.
template <typename Pixel>
auto alpha_or_max(Pixel const& p) -> typename channel_type<Pixel>::type
{
    return detail::alpha_or_max_impl(
        p,
        mp11::mp_contains<typename color_space_type<Pixel>::type, alpha_t>());
}


/// \ingroup ColorConvert
/// \brief Converting any pixel type to RGBA. Note: Supports homogeneous pixels only.
template <typename C1>
struct default_color_converter_impl<C1,rgba_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        using T2 = typename channel_type<P2>::type;
        pixel<T2,rgb_layout_t> tmp;
        default_color_converter_impl<C1,rgb_t>()(src,tmp);
        get_color(dst,red_t())  =get_color(tmp,red_t());
        get_color(dst,green_t())=get_color(tmp,green_t());
        get_color(dst,blue_t()) =get_color(tmp,blue_t());
        get_color(dst,alpha_t())=channel_convert<T2>(alpha_or_max(src));
    }
};

/// \ingroup ColorConvert
///  \brief Converting RGBA to any pixel type. Note: Supports homogeneous pixels only.
///
/// Done by multiplying the alpha to get to RGB, then converting the RGB to the target pixel type
/// Note: This may be slower if the compiler doesn't optimize out constructing/destructing a temporary RGB pixel.
///       Consider rewriting if performance is an issue
template <typename C2>
struct default_color_converter_impl<rgba_t,C2> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        using T1 = typename channel_type<P1>::type;
        default_color_converter_impl<rgb_t,C2>()(
            pixel<T1,rgb_layout_t>(channel_multiply(get_color(src,red_t()),  get_color(src,alpha_t())),
                                   channel_multiply(get_color(src,green_t()),get_color(src,alpha_t())),
                                   channel_multiply(get_color(src,blue_t()), get_color(src,alpha_t())))
            ,dst);
    }
};

/// \ingroup ColorConvert
/// \brief Unfortunately RGBA to RGBA must be explicitly provided - otherwise we get ambiguous specialization error.
template <>
struct default_color_converter_impl<rgba_t,rgba_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        static_for_each(src,dst,default_channel_converter());
    }
};

/// @defgroup ColorConvert Color Space Converion
/// \ingroup ColorSpaces
/// \brief Support for conversion between pixels of different color spaces and channel depths

/// \ingroup PixelAlgorithm ColorConvert
/// \brief class for color-converting one pixel to another
struct default_color_converter {
    template <typename SrcP, typename DstP>
    void operator()(const SrcP& src,DstP& dst) const {
        using SrcColorSpace = typename color_space_type<SrcP>::type;
        using DstColorSpace = typename color_space_type<DstP>::type;
        default_color_converter_impl<SrcColorSpace,DstColorSpace>()(src,dst);
    }
};

/// \ingroup PixelAlgorithm
/// \brief helper function for converting one pixel to another using GIL default color-converters
///     where ScrP models HomogeneousPixelConcept
///           DstP models HomogeneousPixelValueConcept
template <typename SrcP, typename DstP>
inline void color_convert(const SrcP& src, DstP& dst) {
    default_color_converter()(src,dst);
}

} }  // namespace boost::gil

#endif

/* color_convert.hpp
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
*/