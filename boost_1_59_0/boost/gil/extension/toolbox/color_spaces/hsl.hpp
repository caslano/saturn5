//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_HSL_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_HSL_HPP

#include <boost/gil/color_convert.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// \addtogroup ColorNameModel
/// \{
namespace hsl_color_space
{
/// \brief Hue
struct hue_t {};
/// \brief Saturation
struct saturation_t {};
/// \brief Lightness
struct lightness_t {};
}
/// \}

/// \ingroup ColorSpaceModel
using hsl_t = mp11::mp_list
<
    hsl_color_space::hue_t,
    hsl_color_space::saturation_t,
    hsl_color_space::lightness_t
>;

/// \ingroup LayoutModel
using hsl_layout_t = layout<hsl_t>;


BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, hsl)

/// \ingroup ColorConvert
/// \brief RGB to HSL
template <>
struct default_color_converter_impl< rgb_t, hsl_t >
{
   template <typename P1, typename P2>
   void operator()( const P1& src, P2& dst ) const
   {
      using namespace hsl_color_space;

      // only float32_t for hsl is supported
      float32_t temp_red   = channel_convert<float32_t>( get_color( src, red_t()   ));
      float32_t temp_green = channel_convert<float32_t>( get_color( src, green_t() ));
      float32_t temp_blue  = channel_convert<float32_t>( get_color( src, blue_t()  ));

      float32_t hue, saturation, lightness;

      float32_t min_color = (std::min)( temp_red, (std::min)( temp_green, temp_blue ));
      float32_t max_color = (std::max)( temp_red, (std::max)( temp_green, temp_blue ));

      if( std::abs( min_color - max_color ) < 0.001 )
      {
         // rgb color is gray

         hue        = 0.f;
         saturation = 0.f;

         // doesn't matter which rgb channel we use.
         lightness = temp_red;
      }
      else
      {

         float32_t diff = max_color - min_color;

         // lightness calculation

         lightness = ( min_color + max_color ) / 2.f;

         // saturation calculation

         if( lightness < 0.5f )
         {
            saturation = diff
                       / ( min_color + max_color );
         }
         else
         {
            saturation = ( max_color - min_color )
                       / ( 2.f - diff );

         }

         // hue calculation
         if( std::abs( max_color - temp_red ) < 0.0001f )
         {
            // max_color is red
            hue = ( temp_green - temp_blue )
                / diff;

         }
         else if( std::abs( max_color - temp_green) < 0.0001f )
         {
            // max_color is green
            // 2.0 + (b - r) / (maxColor - minColor);
            hue = 2.f
                + ( temp_blue - temp_red )
                / diff;

         }
         else
         {
            // max_color is blue
            hue = 4.f
                + ( temp_red - temp_blue )
                / diff;
         }

         hue /= 6.f;

         if( hue < 0.f )
         {
            hue += 1.f;
         }
      }

      get_color( dst,hue_t() )        = hue;
      get_color( dst,saturation_t() ) = saturation;
      get_color( dst,lightness_t() )  = lightness;
   }
};

/// \ingroup ColorConvert
/// \brief HSL to RGB
template <>
struct default_color_converter_impl<hsl_t,rgb_t>
{
   template <typename P1, typename P2>
   void operator()( const P1& src, P2& dst) const
   {
      using namespace hsl_color_space;

      float32_t red, green, blue;

      if( std::abs( get_color( src, saturation_t() )) < 0.0001  )
      {
         // If saturation is 0, the color is a shade of gray
         red   = get_color( src, lightness_t() );
         green = get_color( src, lightness_t() );
         blue  = get_color( src, lightness_t() );
      }
      else
      {
         float temp1, temp2;
         float tempr, tempg, tempb;

         //Set the temporary values
         if( get_color( src, lightness_t() ) < 0.5 )
         {
            temp2 = get_color( src, lightness_t() )
                  * ( 1.f + get_color( src, saturation_t() ) );
         }
         else
         {
            temp2 = ( get_color( src, lightness_t() ) + get_color( src, saturation_t() ))
                  - ( get_color( src, lightness_t() ) * get_color( src, saturation_t() ));
         }

         temp1 = 2.f
               * get_color( src, lightness_t() )
               - temp2;

         tempr = get_color( src, hue_t() ) + 1.f / 3.f;

         if( tempr > 1.f )
         {
            tempr--;
         }

         tempg = get_color( src, hue_t() );
         tempb = get_color( src, hue_t() ) - 1.f / 3.f;

         if( tempb < 0.f )
         {
            tempb++;
         }

         //Red
         if( tempr < 1.f / 6.f )
         {
            red = temp1 + ( temp2 - temp1 ) * 6.f * tempr;
         }
         else if( tempr < 0.5f )
         {
            red = temp2;
         }
         else if( tempr < 2.f / 3.f )
         {
            red = temp1 + (temp2 - temp1)
                * (( 2.f / 3.f ) - tempr) * 6.f;
         }
         else
         {
            red = temp1;
         }

         //Green
         if( tempg < 1.f / 6.f )
         {
            green = temp1 + ( temp2 - temp1 ) * 6.f * tempg;
         }
         else if( tempg < 0.5f )
         {
            green = temp2;
         }
         else if( tempg < 2.f / 3.f )
         {
            green = temp1 + ( temp2 - temp1 )
                  * (( 2.f / 3.f ) - tempg) * 6.f;
         }
         else
         {
            green = temp1;
         }

         //Blue
         if( tempb < 1.f / 6.f )
         {
            blue = temp1 + (temp2 - temp1) * 6.f * tempb;
         }
         else if( tempb < 0.5f )
         {
            blue = temp2;
         }
         else if( tempb < 2.f / 3.f )
         {
            blue = temp1 + (temp2 - temp1)
                 * (( 2.f / 3.f ) - tempb) * 6.f;
         }
         else
         {
            blue = temp1;
         }
      }

      get_color(dst,red_t())  =
         channel_convert<typename color_element_type< P2, red_t >::type>( red );
      get_color(dst,green_t())=
         channel_convert<typename color_element_type< P2, green_t >::type>( green );
      get_color(dst,blue_t()) =
         channel_convert<typename color_element_type< P2, blue_t >::type>( blue );
   }
};

} // namespace gil
} // namespace boost

#endif

/* hsl.hpp
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
*/