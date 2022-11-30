//
// Copyright 2012 Chung-Lin Wen, Davide Anastasia
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_XYZ_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_XYZ_HPP

#include <boost/gil/color_convert.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// \addtogroup ColorNameModel
/// \{
namespace xyz_color_space
{
/// \brief x Color Component
struct x_t {};
/// \brief y Color Component
struct y_t {};
/// \brief z Color Component
struct z_t {};
}
/// \}

/// \ingroup ColorSpaceModel
using xyz_t = mp11::mp_list
<
    xyz_color_space::x_t,
    xyz_color_space::y_t,
    xyz_color_space::z_t
>;

/// \ingroup LayoutModel
using xyz_layout_t = layout<xyz_t>;

BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, xyz)

/// \ingroup ColorConvert
/// \brief RGB to XYZ
/// <a href="http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html">Link</a>
/// \note rgb_t is assumed to be sRGB D65
template <>
struct default_color_converter_impl< rgb_t, xyz_t >
{
private:
    BOOST_FORCEINLINE
    float32_t inverse_companding(float32_t sample) const
    {
        if ( sample > 0.04045f )
        {
            return powf((( sample + 0.055f ) / 1.055f ), 2.4f);
        }
        else
        {
            return ( sample / 12.92f );
        }
    }

public:
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst ) const
    {
        using namespace xyz_color_space;

        float32_t red(
            inverse_companding(
                channel_convert<float32_t>(get_color(src, red_t()))));
        float32_t green(
            inverse_companding(
                channel_convert<float32_t>(get_color(src, green_t()))));
        float32_t blue(
            inverse_companding(
                channel_convert<float32_t>(get_color(src, blue_t()))));

        get_color( dst, x_t() ) =
                red * 0.4124564f +
                green * 0.3575761f +
                blue * 0.1804375f;
        get_color( dst, y_t() ) =
                red * 0.2126729f +
                green * 0.7151522f +
                blue * 0.0721750f;
        get_color( dst, z_t() ) =
                red * 0.0193339f +
                green * 0.1191920f +
                blue * 0.9503041f;
    }
};

/// \ingroup ColorConvert
/// \brief XYZ to RGB
template <>
struct default_color_converter_impl<xyz_t,rgb_t>
{
private:
    BOOST_FORCEINLINE
    float32_t companding(float32_t sample) const
    {
        if ( sample > 0.0031308f )
        {
            return ( 1.055f * powf( sample, 1.f/2.4f ) - 0.055f );
        }
        else
        {
            return ( 12.92f * sample );
        }
    }

public:
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst) const
    {
        using namespace xyz_color_space;

        // Note: ideally channel_convert should be compiled out, because xyz_t
        // is float32_t natively only
        float32_t x( channel_convert<float32_t>( get_color( src, x_t() ) ) );
        float32_t y( channel_convert<float32_t>( get_color( src, y_t() ) ) );
        float32_t z( channel_convert<float32_t>( get_color( src, z_t() ) ) );

        get_color(dst,red_t())  =
                channel_convert<typename color_element_type<P2, red_t>::type>(
                    companding( x *  3.2404542f +
                                y * -1.5371385f +
                                z * -0.4985314f )
                    );
        get_color(dst,green_t()) =
                channel_convert<typename color_element_type<P2, green_t>::type>(
                    companding( x * -0.9692660f +
                                y *  1.8760108f +
                                z *  0.0415560f )
                    );
        get_color(dst,blue_t()) =
                channel_convert<typename color_element_type<P2, blue_t>::type>(
                    companding( x *  0.0556434f +
                                y * -0.2040259f +
                                z *  1.0572252f )
                    );
    }
};

} // namespace gil
} // namespace boost

#endif // BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_XYZ_HPP

/* xyz.hpp
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
*/