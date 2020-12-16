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
QElm/kA69aMdwDJnakYpwXu1/xyutWYAMNtSkdzIKGYnTx/mNoQIP0lWDOjCuBTGTvrZ127CmW6j4r0L5UCd5Yjyuj8ofqoWAr3OdDFZuCMYC09qYgKOQSWpE7q1gRGI0FJa+ozwL8v0p8eDdSNPzMv+Ys/Cii01pJacwzqQqazIFJ53itT4YI1l5kWqNWzaf31Cz4w8fk5ENMhZ3kbdI2nc+18EANtc10emqZTwJHwjXzsXGdHeeHKYmkNxkiGVUEFgog8zLB3z838l2nmB/Zd60tqpVGvwC1hIQWyhkoAlJvo+m8HP19CSO5uKZVX5guuYt8uclVlBzRRA5FvKocD/rA+vf71ym3OnvVxTjpgXYyO4gggX8kaLSxjbhSoIieN6geYpqhkBAPv8YURHjW37nym5antCtKO5ZxZYCtL+S/18JXUvLE9Z9QvLU+qoUp4O4fL8Wv3/WJ6Ui5Rn2EXK461anrdq2OVJ+1/Kk2DtBQV1LBt90FdIeApNAcfZ9iv1MpzXW27VakRAdyXfNgwY5Q1fcFbGdVsV+vkCXyLrLWPqsJkASTyEXq6yP1POylDeYA1lJK+Yjz/ut8H6vvKOviEnIzqgqwA1keecmqJS2bQ+fPURVQtCAIC2FK3bntrWseusN18W+s3mso6hkM2ax/ZFoakzvQXYN4hQ9WzIK6wg7dXHWrmyRP+v4sOLEcp42y6W8QxuMAdryFq8bzDt7aZ0PGj2oKj5vZwZaAHMpWhzI6oR7AKrGLDP/DZ2vjbF2c2wOt3ixHe+ftfidwS+x8l37s8p7gUH3Z4DvMcNVj28yAXZlsLclclBBhkWExnPf49LjKEaYxx+TOQZ7AnLwjqu+skVNK4HUEFwgoxZKSaRSJTk24Tr/+P6ToXU3NqXQpttoLrFv6QleBhBYkJOL8G3oiRiy9EcZzdpcbqbPmf4cY7yJmtN4+r6dMQDFb5Jp0z3WM9lYLPh7sSjl7nlHKicI6inl6XAFeYtolQCznyAVzwmhVsWGynjohUKF3zISgzGq5RJB30NPJbiCXSrEONGngHOS1VkZK0K/bNm5Y/7aQDQurJ9vWaBX5JFWoanO61UppCus8SLVqvcpvZ5H+SePnwUKlnYHinNELd93D/wqHXcT8NOlwYVJQF5wuQ8J/MLx9ggkv5Gm1hknJP8Keop1Cwo3c/VG//aQapfvzp6td0pp9x/FNQlFqDGCvpUQTcSFK2gNxQ0nqDjJwWUo6A5BO1S0HAF/UzQGgX1U9At0QB9K6A1Zh1+2ZG3VlObhq2dqjimuVPNCCaopHgoA+MjnjCExfA3v8tSoAaK1NBPxg8sqUk/gTwa6bA0YZmxgGFwjWHXkqeqhCxso2Nscz1iU47G4/5wL7iUCj7lkXzSVl/ti1qXSyoe9Rd/iX8JDNJ4Izd1+tmyJxcVq9rWY6hOnQISv2NrdokVY9aqn5IiHCgDpSMLLrQV9F/l3L1izmF7OP9F/tuEj8c1tTry/+WRaZU4F63sj0r2a5F9nWkXPVgmlYxqBq0sS3lPAR5vm2LYszbzG+sEfFaY3wvZICmOf1c94v/f61dL6xddpX7nQUx3L4gmfnCVTuvebVQ96HgtrnJii6PRE2Q6Cfr+g8wdeUNI7eyEG3Bey1kTgtp68g9xl8k6wQPiYeLm60wm1Dmh/wbGgDFxoKxOmRNMwXEniBQD3fm+SEv8ngzDtF/+iJpaSpaxrWyo5l3EBp1p/R0RNrbrK2F7CuFI60RaomH68yfCa5TL3I9wK2HtSgm7SkJwS/Pq1xsofnhYUZhvMU+RNs60QBTyaPMYaOH4NboijhPHKuDIAo5nbByjFEctsx1RcKAla10wyo8=
*/