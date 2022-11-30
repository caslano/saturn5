//
// Copyright 2013 Juan V. Puertos G-Cluster, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_YCBCR_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_YCBCR_HPP

#include <boost/gil/extension/toolbox/metafunctions/get_num_bits.hpp>

#include <boost/gil/color_convert.hpp>
#include <boost/gil.hpp> // FIXME: Include what you use!
#include <boost/gil/detail/mp11.hpp>

#include <boost/config.hpp>

#include <cstdint>
#include <type_traits>

namespace boost { namespace gil {

/// \addtogroup ColorNameModel
/// \{
namespace ycbcr_601_color_space
{
/// \brief Luminance
struct y_t {};
/// \brief Blue chrominance component
struct cb_t {};
/// \brief Red chrominance component
struct cr_t {};
}

namespace ycbcr_709_color_space
{
/// \brief Luminance
struct y_t {};
/// \brief Blue chrominance component
struct cb_t {};
/// \brief Red chrominance component
struct cr_t {};
}
/// \}

/// \ingroup ColorSpaceModel
using ycbcr_601__t = mp11::mp_list
<
    ycbcr_601_color_space::y_t,
    ycbcr_601_color_space::cb_t,
    ycbcr_601_color_space::cr_t
>;

/// \ingroup ColorSpaceModel
using ycbcr_709__t = mp11::mp_list
<
    ycbcr_709_color_space::y_t,
    ycbcr_709_color_space::cb_t,
    ycbcr_709_color_space::cr_t
>;

/// \ingroup LayoutModel
using ycbcr_601__layout_t = boost::gil::layout<ycbcr_601__t>;
using ycbcr_709__layout_t = boost::gil::layout<ycbcr_709__t>;

//The channel depth is ALWAYS 8bits ofr YCbCr!
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, ycbcr_601_)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, ycbcr_709_)

namespace detail {

// Source:boost/algorithm/clamp.hpp
template<typename T>
BOOST_CXX14_CONSTEXPR
T const& clamp(
    T const& val,
    typename boost::mp11::mp_identity<T>::type const & lo,
    typename boost::mp11::mp_identity<T>::type const & hi)
{
    // assert ( !p ( hi, lo )); // Can't assert p ( lo, hi ) b/c they might be equal
    auto const p = std::less<T>();
    return p(val, lo) ? lo : p(hi, val) ? hi : val;
}

} // namespace detail

/*
 * 601 Source: http://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.601_conversion
 * 709 Source: http://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.709_conversion
 * (using values coming directly from ITU-R BT.601 recommendation)
 * (using values coming directly from ITU-R BT.709 recommendation)
 */

/**
* @brief Convert YCbCr ITU.BT-601 to RGB.
*/
template<>
struct default_color_converter_impl<ycbcr_601__t, rgb_t>
{
	// Note: the RGB_t channels range can be set later on by the users. We dont want to cast to uint8_t or anything here.
	template < typename SRCP, typename DSTP >
	void operator()( const SRCP& src, DSTP& dst ) const
	{
        using dst_channel_t = typename channel_type<DSTP>::type;
        convert(src, dst, typename std::is_same
            <
                std::integral_constant<int, sizeof(dst_channel_t)>,
                std::integral_constant<int, 1>
            >::type());
	}

private:

    // optimization for bit8 channels
    template< typename Src_Pixel
            , typename Dst_Pixel
            >
    void convert( const Src_Pixel& src
                ,       Dst_Pixel& dst
                , std::true_type // is 8 bit channel
                ) const
    {
        using namespace ycbcr_601_color_space;

        using src_channel_t = typename channel_type<Src_Pixel>::type;
        using dst_channel_t = typename channel_type<Dst_Pixel>::type;

		src_channel_t y  = channel_convert<src_channel_t>( get_color(src,  y_t()));
		src_channel_t cb = channel_convert<src_channel_t>( get_color(src, cb_t()));
		src_channel_t cr = channel_convert<src_channel_t>( get_color(src, cr_t()));

		// The intermediate results of the formulas require at least 16bits of precission.
		std::int_fast16_t c = y  - 16;
		std::int_fast16_t d = cb - 128;
		std::int_fast16_t e = cr - 128;
		std::int_fast16_t red   = detail::clamp((( 298 * c + 409 * e + 128) >> 8), 0, 255);
		std::int_fast16_t green = detail::clamp((( 298 * c - 100 * d - 208 * e + 128) >> 8), 0, 255);
		std::int_fast16_t blue  = detail::clamp((( 298 * c + 516 * d + 128) >> 8), 0, 255);

		get_color( dst,  red_t() )  = (dst_channel_t) red;
		get_color( dst, green_t() ) = (dst_channel_t) green;
		get_color( dst,  blue_t() ) = (dst_channel_t) blue;
    }


    template< typename Src_Pixel
            , typename Dst_Pixel
            >
    void convert( const Src_Pixel& src
                ,       Dst_Pixel& dst
                , std::false_type // is 8 bit channel
                ) const
    {
        using namespace ycbcr_601_color_space;

        using dst_channel_t = typename channel_type<Dst_Pixel>::type;

        double  y = get_color( src,  y_t() );
        double cb = get_color( src, cb_t() );
        double cr = get_color( src, cr_t() );

        get_color(dst, red_t()) = static_cast<dst_channel_t>(
            detail::clamp(1.6438 * (y - 16.0) + 1.5960 * (cr -128.0), 0.0, 255.0));

        get_color(dst, green_t()) = static_cast<dst_channel_t>(
            detail::clamp(1.6438 * (y - 16.0) - 0.3917 * (cb - 128.0) + 0.8129 * (cr -128.0), 0.0, 255.0));

        get_color(dst, blue_t()) = static_cast<dst_channel_t>(
            detail::clamp(1.6438 * ( y - 16.0 ) - 2.0172 * ( cb -128.0 ), 0.0, 255.0));
    }
};

/*
 * Source: http://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.601_conversion
 * digital Y'CbCr derived from digital R'dG'dB'd 8 bits per sample, each using the full range.
 * with NO footroom wither headroom.
 */
/**
* @brief Convert RGB to YCbCr ITU.BT-601.
*/
template<>
struct default_color_converter_impl<rgb_t, ycbcr_601__t>
{
	template < typename SRCP, typename DSTP >
	void operator()( const SRCP& src, DSTP& dst ) const
	{
        using namespace ycbcr_601_color_space;

        using src_channel_t = typename channel_type<SRCP>::type;
        using dst_channel_t = typename channel_type<DSTP>::type;

		src_channel_t red   = channel_convert<src_channel_t>( get_color(src,   red_t()));
		src_channel_t green = channel_convert<src_channel_t>( get_color(src, green_t()));
		src_channel_t blue  = channel_convert<src_channel_t>( get_color(src,  blue_t()));

		double  y =  16.0 + 0.2567 * red  + 0.5041 * green + 0.0979 * blue;
		double cb = 128.0 - 0.1482 * red  - 0.2909 * green + 0.4392 * blue;
		double cr = 128.0 + 0.4392 * red  - 0.3677 * green - 0.0714 * blue;

		get_color( dst,  y_t() ) = (dst_channel_t)  y;
		get_color( dst, cb_t() ) = (dst_channel_t) cb;
		get_color( dst, cr_t() ) = (dst_channel_t) cr;
	}
};

/**
* @brief Convert RGB to YCbCr ITU.BT-709.
*/
template<>
struct default_color_converter_impl<rgb_t, ycbcr_709__t>
{
	template < typename SRCP, typename DSTP >
	void operator()( const SRCP& src, DSTP& dst ) const
	{
        using namespace ycbcr_709_color_space;

        using src_channel_t = typename channel_type<SRCP>::type;
        using dst_channel_t = typename channel_type<DSTP>::type;

		src_channel_t red   = channel_convert<src_channel_t>( get_color(src,   red_t()));
		src_channel_t green = channel_convert<src_channel_t>( get_color(src, green_t()));
		src_channel_t blue  = channel_convert<src_channel_t>( get_color(src,  blue_t()));

		double  y =            0.299 * red  +    0.587 * green +    0.114 * blue;
		double cb = 128.0 - 0.168736 * red  - 0.331264 * green +      0.5 * blue;
		double cr = 128.0 +      0.5 * red  - 0.418688 * green - 0.081312 * blue;

		get_color( dst,  y_t() ) = (dst_channel_t)  y;
		get_color( dst, cb_t() ) = (dst_channel_t) cb;
		get_color( dst, cr_t() ) = (dst_channel_t) cr;
	}
};

/**
* @brief Convert RGB to YCbCr ITU.BT-709.
*/
template<>
struct default_color_converter_impl<ycbcr_709__t, rgb_t>
{
	template < typename SRCP, typename DSTP >
	void operator()( const SRCP& src, DSTP& dst ) const
	{
        using namespace ycbcr_709_color_space;

        using src_channel_t = typename channel_type<SRCP>::type;
        using dst_channel_t = typename channel_type<DSTP>::type;

		src_channel_t y           = channel_convert<src_channel_t>( get_color(src,  y_t())       );
		src_channel_t cb_clipped  = channel_convert<src_channel_t>( get_color(src, cb_t()) - 128 );
		src_channel_t cr_clipped  = channel_convert<src_channel_t>( get_color(src, cr_t()) - 128 );

		double   red =   y                        +   1.042 * cr_clipped;
		double green =   y - 0.34414 * cb_clipped - 0.71414 * cr_clipped;
		double  blue =   y +   1.772 * cb_clipped;

		get_color( dst,   red_t() ) = (dst_channel_t)   red;
		get_color( dst, green_t() ) = (dst_channel_t) green;
		get_color( dst,  blue_t() ) = (dst_channel_t)  blue;
	}
};

} // namespace gil
} // namespace boost

#endif

/* ycbcr.hpp
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
*/