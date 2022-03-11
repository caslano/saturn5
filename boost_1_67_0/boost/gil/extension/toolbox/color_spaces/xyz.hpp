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