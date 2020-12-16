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
o72Qd9cVjMUSruM5pt/0BinmCRUThoZpbHvZHcV6bEts/SDUAg0t03nzgaZu27na5C+0t1V2tmgv1ihXimbsIkxBbEGw6JXQXtewS4DhRaduTUfxJEgzo22C5qAbrDw+YqIdNY+AlYe3vU1rvtlOaM1/ho9gk+GFu8HXUkOaIE21FX3zVScp+dFOurm+hzB827gVrX8jSjFuyR5wUQizAU5AB0BPQD/AYMDlgOGA0YAbAf+Nn5b7G6Z/GTWPfNbb5qeNesDmp63C4iY6FEeRkgnuIJ1VjMk7/xudvGMwM4Fa5oHmQnyfl7nsXRo6Qn4DjKHhM1eIOcB4JOPj3Ma3gF9KMgAmA4oAwwAjzN5NwqEwOyt1jjZ0WjP8on6c4WnWDG9aac/w89dx9iLp2PR+EBh5XkZzGqtNPfxkGSP/MKfe1bAFkd3mR7hZ5MhfyZ2aGCnlZ1TkLmHkyQxXrtXtcJkNDKzWnseYjfgR+bt5WXHm+7YgtU+wtwYy6MOCTslFG/K9UluumJVcNJeei070Orj+WDFfRUzSxxbZF9qJvQz7yhcg4aT8XLPAdRjjXngYfW/KgZdGF9Uipkt1mUaZbmi2cCLzb6b1Whp+i4Hq668l4X/w16l37KXKsbRK+jL8APAV6AAKWeM7LMnic46ILDDbGFxzKDJu5GAbq0ShiiK9zIpq/2Hmx42yQv0FfsNgH3tJtd8Is0f9BlPecrY33IZluVUCpKTf75I5eW6snSZnYApkYPVsdYj8n/XRqLByq8Kvc5T6tkpSran/7j7Vf3e3pf8O8RisFMFAES8pUJs00P5f6p1rVo0QvhNFRZ7ReJd+jGN3vBVpBCJBeygoTTZ4oIG58iKrscHDWvbq7Z6QR3UJ+65hw9mGylsniI6dAtw8IqfnzZaRscPGTUhoonsBLpFJxM8Fs2JSqZOBfQzMXUVWEG+xHrfmTmFMw5gXcWykXxS7lb2A7ZMh6/J3S7AWX95G1uXP6E6T8uPJXfiheHRc9g3tx/tHo6wFfTnDQOUqxfVlFysYmjI8ESGpCcH2LKnpiTfQTHzeEmmj+39GG33e2s7jT/EWC4Wni2EFY2k7DwXuyvcRw0BznO8DagS7R7ZBjm1qcyLrXa1SmJwuJI9CGLLwxIaaCaSqB25Bn8aWD7AomFMKttdWany4DU7Lx0n8kzFCDsufcKeL1egoPPR1Qilsq5TOWmUmXiDnlybssVWd7eJPQV+IMcKvBlWJ0Y6KrGZ48H+y+sH/Bk9WBh/8/9wGl/s8QaAUa4S4PCjXX0xvjFKhT7A0N6E0SK9dQVW0RqOTb4KI1zOg3a7HHdrotmdSTc9PHNLoyfdKo7f6CY1+cyvLX9jmHH3kP/p7axbNraibUUA9Gp68kOeXOM3kNfFWevcZenwED43Z7LSYryNAJB3R3Aunk2ypjnrthVJzmzbY2FrG4Lh7MO62tpQxeA3d96Go4WZqT2guT85ZenJ+qXWtbhm9ynx4fsyCbsY9Utf7muFQMbulFlEfypTnZnX3p3O/raO8ITerq6W8AVwccpbSL6yWXCCti/yU8uIu3VHoGtvvkVbw49VfdTfliCo2+3oPWQvFgr6RyckBm43Nyd/A/KOT3CZFLjb7z1dXZzZyqoY2ay0kazWoVGo18kf04PMtePYGZcKidkMaLNZVHdW+4pMybwuLzfMLq6LCF2eD4vtbC/GYi1QebEWu7WjuGKsEi/UM6NmCvpboR4DO4ygt5UZNZm5JdyUjU13CzOXGXpOOHLfk0w2OOMLbgENlsJu9HgC3C9+WgPMBXQA9AZnA9wNcB7gTkA/caMDDgAOAowAnw+B7Rvp/idD/f6qm/w9W0//9Dio=
*/