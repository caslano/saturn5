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
Jo4He1Pg82JfSKqyWx8Q4YX2ZwWlPX9DMuCHIkWJy51QpGzNaw2lmPNBM0vPh/5q+ae8NR2D730QEHZ+FlP9Q3N9MxY0EYrGXkCyfPc3XSrwHH4tLMMj9/fND/UYbyD0jVUkse6LhHOKSAhWpJGuZ/qbEC7cAV4Ya6FPHALPAtIAzQGtAd0AvQBnfC+dm0qJ1Nb2veOhqbH30l3hg8FtL13UL7UrAcO+O4aI99+sXQd0lFUWnkkyJATChB5AEBEUBZS6BkI0kYlOJNEooFhQFFSUIsoEUKmGKGGIYl2wgXVVULDAArYAkkRqEIQAS5P2hhHpXTL7fff+/6TAlrNnc87LvP++9+7r7b5b8sdGpOU/7DRzPtOj7Ic4T/GOjZFf/fKyUMVh791hDXsTel8og8G25gR8eoA8N6ZMDrEJZhdhmAK1Un+MRMMHq8GIPn5N+hwd9qZknoz4Rl+TWe8fYHuSQR0jFn/M15/pWZpXtq64K7mnDoKPfMYh5TN+qiPWGfIW8q7+cCfhMW42SulgHyqP8dMubKT+Iryr02rvDeWEKp7zUieGWKzslmZKdeWDXIPoEixctvrSfoWEGUroc2/5mCehAacWQV2R6stOWuK+bQnZ2LE9HYat5cfj9X17HUfaxDJW2HeNh6cQqrvirRCZJBW6xV51sAcmamwJJmofGEICeYZCOjin5Z4cd5XK91Pew3MJL0+hr5T28FEU3/gjskeI1Mf2MdtZNClPm8I8KaXaZ0D1mHm2m3PyQU1bw1VuOW61WFUIRQkTwBVoz6/QniQnohjBFmjLX7KlLTsN06tDO8QE9DtAzbEoPevcMEwJnD/iW0T1pmKQKdG89yV6VJsWL8TLlPgqMrn7ob+T7ja4mtucjgZwV8N1husOV1m//RtNbPs+3bVUH9Wi/ePIiAqqwS+in4U3i3vtpK7NI8JTIQUhVD2MH9j7pDJi8ZX6XR8CP9i5YLoSuwP1cReQ9Be33CfZjkvgLrYSLKCmaaS0xxxfJSsVcwnFifDG1IX6SiOn/19NB8BtUP05D0RoiLkkWpA8qtg7L+UystwsjcAS1NHTtUtDFMYzGcTU7MdozyMGDxGLw2jFqEd9gGTIZjvJiwSZtUlQ8MqZMuFsrK/bhLPXZA+bMKZlamz2o7YJFVReu+jLxmJCha1UQRnDI+RkjZUbxmoPXo2KK9VkvXk0okJNfrvfrskd1SI0f/nEA8qkX6igsZL+GE9iB9UfA3sRUNc3YUxUSqw7l2QYfHmT5fqUAzkO1jkqBZMgPmnN2JoeOcJ78KgVrJMbGt0xae04TKgiwIYDRvvX6FfzohNLv2sfvOixwV7udqlYtgI1MBVANC4BbjHCS16bYunsVVjZ58FHQhQ3Oa6J4WPdvZGcF3Lw9LjTjqA+gSV6m/z2KemrSbiemEZOsftJPf/mJbTmqv9sb3ZVgk0Rw+Sk9ZckFJkKGTgOXVfgA8MQahtBF+P6Yo+/NM21rL6MP87HdxwydNo+VWn8XevU8Xe9dhGGHu9mXzsq9Nk1/ZSHfJZO6OCTSrv+UcfeTQ6OvZzkt4DXUeh6mz/Zgzj6prTX0cfEMvZmACBjb4SMvfpPIi5H30Br9CVx9A2dkHw34LHZA8uNr6nlWdqgrWp+FoqQrkJsHX5rqFP9Zy239Tp5IOQsr8jD92lFNkVGMPujqIiYkMXIu7i6cx12N07o3hzDbnblYbeAtgoKo5o7Kg+71fUuHHZnAEPDfTUcw64hCuR3PfGkDLthMuxu4bCrZ7F1TZab8yq+teAKER5ek6xbg0Fczv/h0gde3tOWlzmJvTex+4Ed46tIY6VqrFjGmlkmIZ9z5NVPkJH338hH3to=
*/