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