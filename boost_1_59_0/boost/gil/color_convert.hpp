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
/// \todo FIXME: Where does this calculation come from? Shouldn't gray be inverted?
///              Currently, white becomes black and black becomes white.
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
/// where `1` denotes max value of channel type of destination pixel.
///
/// The conversion from RGB to CMYK is based on CMY->CMYK (Version 2)
/// from the Principles of Digital Image Processing - Fundamental Techniques
/// by Burger, Wilhelm, Burge, Mark J.
/// and it is a gross approximation not precise enough for professional work.
///
/// \todo FIXME: The original implementation did not handle properly signed CMYK pixels as destination
///
template <>
struct default_color_converter_impl<rgb_t, cmyk_t>
{
    template <typename SrcPixel, typename DstPixel>
    void operator()(SrcPixel const& src, DstPixel& dst) const
    {
        using src_t = typename channel_type<SrcPixel>::type;
        src_t const r = get_color(src, red_t());  
        src_t const g = get_color(src, green_t());
        src_t const b = get_color(src, blue_t());

        using dst_t   = typename channel_type<DstPixel>::type;
        dst_t const c = channel_invert(channel_convert<dst_t>(r)); // c = 1 - r
        dst_t const m = channel_invert(channel_convert<dst_t>(g)); // m = 1 - g
        dst_t const y = channel_invert(channel_convert<dst_t>(b)); // y = 1 - b
        dst_t const k = (std::min)(c, (std::min)(m, y));           // k = minimum(c, m, y)

        // Apply color correction, strengthening, reducing non-zero components by
        // s = 1 / (1 - k) for k < 1, where 1 denotes dst_t max, otherwise s = 1 (literal).
        dst_t const dst_max = channel_traits<dst_t>::max_value();
        dst_t const s_div   = dst_max - k;
        if (s_div != 0)
        {
            double const s              = dst_max / static_cast<double>(s_div);
            get_color(dst, cyan_t())    = static_cast<dst_t>((c - k) * s);
            get_color(dst, magenta_t()) = static_cast<dst_t>((m - k) * s);
            get_color(dst, yellow_t())  = static_cast<dst_t>((y - k) * s);
        }
        else
        {
            // Black only for k = 1 (max of dst_t)
            get_color(dst, cyan_t())    = channel_traits<dst_t>::min_value();
            get_color(dst, magenta_t()) = channel_traits<dst_t>::min_value();
            get_color(dst, yellow_t())  = channel_traits<dst_t>::min_value();
        }
        get_color(dst, black_t()) = k; 
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