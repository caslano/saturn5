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