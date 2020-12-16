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
CZGr5P941cM9pnSEwxYc5O8iUP38jiAxIVKPGm4yKA2kZ6z0gCG2wDwim+IRc1+ZtVs5LPLhSC+SD6kW+ZC1zSYfzGpEoGE2LdxavgA2V7yJ3fRdFn6z7a15KYHRg95P0PUivVmsSKn5u+WeHJln7odbN9qlS6z9Ijyeu/MMeOgefjV/3syftpzkQCGvv+KzfZgwEWqb367yPQWf8HnqDLeSbySchi+CF4STmdikitiWO95krNYGCDFlkg/YULd9lgAu9NoomL5y6crxlt5aB2YGHpaQml52DvWxmcA5ljQUms7VkgNuLeubaaFHAP1DC6L/SXRjoEPlHHc7ayvCiJ1f7uORS03qd7hb5sii+U61f56OyT9JTg6HA/V53E8I/RJx0uht1F+Plm89v/jIQRITr8hcNT4Wmc+KqmxGzp4SSdK/A9OuG9NjA4X+Kl0Gre22xg7TaVi1Nf6TVWzDcmmIAtZU7anq/pYNAS4sU6WuIUhSN2sSaeaayVXRyNnAP7mwFn7DhGo50WertC6taag1tu7+RW3s83jUyUw73zoSlcTM/Nveh/xTTAG8u+8Pj5atDmOfyym+45WvRQ6qCA15sgvaF+C005DcilXmknb4vMCV6ZxYXvB10fd+05S+IbTVc8XSVmu+Q1u5mqGtjuGMYV5qK1l+9zvPGA9sccQRUgDtNsOmBuB6wCTADMD9gCcBrwE2ALYAPgQcAPwA+Bpw+npgs6KmdtH14DDN+k4WPYLHsB6sPJAAfdSlI77wdifBB8k0MOHM5rXWBDPr3pYRdL3M5rbdOZsTp4VlNme8b8/m5q8JfyCyy6SKy0QqTD24dC4ml1ZZM/QVzKLICsyuyHOYFz2QtZnDSU2OgPla1g4a9kW+tDM3R/a6Wxa5wP9KQ4uF1BC6SAlzce9RZA8r/xQLP42LfEvBHyF+JHZUzq5zY4rdqPG7xSLVD3QONsEZSBmoJObS72x0Vibngh5d3zeTzpURYx+tLezvGew1TuMhze3ro6ugP41+HyM9ZvkPfNWQ+BjyamrOyn7bHXGE8wA/YUU8BWgBdwbABVB9JZsutCya7KK+tpNJasEpeDLDfzNIJ6yvfg++Tnxb45uAse4uDK3PD+2hXoPwwfZkFalGBI7hQuje4gyjP9dBCcST+H/2nfOHvsP/0LcNfM9g71zse9fhU33WSe0Tvy1CNyBAX7fE4L+QeVcYMngfhe0IjRBN8qfOi0qdk/BlndvCkoG/FTkBXJD6L5SObYeV0yw7C0PmGYcqDlIxfaWNMSKbF8TWMLdGGVNCzYyMcrtyTsk612cJeIrvH80/PZBX4A7MmV9aiKA4x1ruqNhY442gGSoUw/u0+RVtitE0GIvWgi3Ompb6EBPpq5DQPCxgkfZsv64IOAEBzxRqP25akGK2pag/9Au47hFehbUhCdO3lWXGUvw+RCFubS0EfKSLMFYes648JtjEDAKVOIjJQzhLq2lxM7UmdzvaFQ0wJ9vfmc3dOhhN9buD0YzAZaTBr2lL8VC6PHT1oqsLXRfS5aOrrdVBTawOOps+l9Inia6ubeUlY0O6v5fJ85m8DhT+HOXsmnN3ow5V072JGo5HfuCMj8yF7XgfbMfHZlKMJ3u6/euJ7fet4aZi5l0ggwvtWeH9nCzXghIvHkOcwOdjb+ggPm4v3p2VTk6CsxkgMQ+PH4q9j4pOfDjmAKYBvxLwBOC4p8T7FWAd3N8ConA/h++bGBZN9yVA0KZceC3eCv1slQu/WQ+baW9E2YfmVqx38obJppDe78w1tblFIU3ea6+pm14SFoI7ss38U53NIuvNKji5vr5Z4ZUiRl42j6vvt5Hl5n442fGPmGJFJkY=
*/