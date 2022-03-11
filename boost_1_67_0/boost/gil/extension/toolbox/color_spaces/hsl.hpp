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