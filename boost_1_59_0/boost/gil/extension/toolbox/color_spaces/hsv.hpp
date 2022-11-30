//
// Copyright 2012 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_HSV_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_HSV_HPP

#include <boost/numeric/conversion/cast.hpp>

#include <boost/gil/color_convert.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <algorithm>
#include <cmath>

namespace boost{ namespace gil {

/// \addtogroup ColorNameModel
/// \{
namespace hsv_color_space
{
/// \brief Hue
struct hue_t {};
/// \brief Saturation
struct saturation_t{};
/// \brief Value
struct value_t {};
}
/// \}

/// \ingroup ColorSpaceModel
using hsv_t = mp11::mp_list
<
    hsv_color_space::hue_t,
    hsv_color_space::saturation_t,
    hsv_color_space::value_t
>;

/// \ingroup LayoutModel
using hsv_layout_t = layout<hsv_t>;

BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, hsv)

/// \ingroup ColorConvert
/// \brief RGB to HSV
template <>
struct default_color_converter_impl< rgb_t, hsv_t >
{
   template <typename P1, typename P2>
   void operator()( const P1& src, P2& dst ) const
   {
      using namespace hsv_color_space;

      // only float32_t for hsv is supported
      float32_t temp_red   = channel_convert<float32_t>( get_color( src, red_t()   ));
      float32_t temp_green = channel_convert<float32_t>( get_color( src, green_t() ));
      float32_t temp_blue  = channel_convert<float32_t>( get_color( src, blue_t()  ));

      float32_t hue, saturation, value;

      float32_t min_color = (std::min)( temp_red, (std::min)( temp_green, temp_blue ));
      float32_t max_color = (std::max)( temp_red, (std::max)( temp_green, temp_blue ));

      value = max_color;

      float32_t diff = max_color - min_color;

      if( max_color < 0.0001f )
      {
         saturation = 0.f;
      }
      else
      {
         saturation = diff / max_color;
      }


      if( saturation < 0.0001f )
      {
         //it doesn't matter what value it has
         hue = 0.f;
      }
      else
      {
         if( (std::abs)( boost::numeric_cast<float32_t>(temp_red - max_color) ) < 0.0001f )
         {
            hue = ( temp_green - temp_blue )
                / diff;
         }
         else if( temp_green >= max_color ) // means == but >= avoids compiler warning; color is never greater than max
         {
            hue = 2.f + ( temp_blue - temp_red )
                / diff;
         }
         else
         {
            hue = 4.f + ( temp_red - temp_green )
                / diff;
         }

         //to bring it to a number between 0 and 1
         hue /= 6.f;

         if( hue < 0.f )
         {
            hue++;
         }
      }

      get_color( dst, hue_t() )        = hue;
      get_color( dst, saturation_t() ) = saturation;
      get_color( dst, value_t() )      = value;
   }
};

/// \ingroup ColorConvert
/// \brief HSV to RGB
template <>
struct default_color_converter_impl<hsv_t,rgb_t>
{
   template <typename P1, typename P2>
   void operator()( const P1& src, P2& dst) const
   {
      using namespace hsv_color_space;

      float32_t red, green, blue;

      //If saturation is 0, the color is a shade of gray
      if (std::abs(get_color(src, saturation_t())) < 0.0001f)
      {
         // If saturation is 0, the color is a shade of gray
         red   = get_color( src, value_t() );
         green = get_color( src, value_t() );
         blue  = get_color( src, value_t() );
      }
      else
      {
         float32_t frac, p, q, t, h;
         uint32_t i;

         //to bring hue to a number between 0 and 6, better for the calculations
         h = get_color( src, hue_t() );
         h *= 6.f;

         i = static_cast<uint32_t>(floor(h));

         frac = h - i;

         p = get_color( src, value_t() )
           * ( 1.f - get_color( src, saturation_t() ));

         q = get_color( src, value_t() )
           * ( 1.f - ( get_color( src, saturation_t() ) * frac ));

         t = get_color( src, value_t() )
           * ( 1.f - ( get_color( src, saturation_t() ) * ( 1.f - frac )));

         switch( i )
         {
            case 0:
            {
               red   = get_color( src, value_t() );
               green = t;
               blue  = p;

               break;
            }

            case 1:
            {
               red   = q;
               green = get_color( src, value_t() );
               blue  = p;

               break;
            }

            case 2:
            {
               red   = p;
               green = get_color( src, value_t() );
               blue  = t;

               break;
            }

            case 3:
            {
               red   = p;
               green = q;
               blue  = get_color( src, value_t() );

               break;
            }

            case 4:
            {
               red   = t;
               green = p;
               blue  = get_color( src, value_t() );

               break;
            }

            case 5:
            {
               red   = get_color( src, value_t() );
               green = p;
               blue  = q;

               break;
            }

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

/* hsv.hpp
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
*/