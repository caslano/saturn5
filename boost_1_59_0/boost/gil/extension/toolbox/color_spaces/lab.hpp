//
// Copyright 2012 Chung-Lin Wen
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_LAB_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_LAB_HPP

#include <boost/gil/extension/toolbox/color_spaces/xyz.hpp>

#include <boost/gil/color_convert.hpp>
#include <boost/gil.hpp> // FIXME: Include what you use, not everything, even in extensions!
#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

/// \addtogroup ColorNameModel
/// \{
namespace lab_color_space
{
/// \brief Luminance
struct luminance_t {};
/// \brief a Color Component
struct a_color_opponent_t {};
/// \brief b Color Component
struct b_color_opponent_t {};
}
/// \}

/// \ingroup ColorSpaceModel
using lab_t = mp11::mp_list
<
    lab_color_space::luminance_t,
    lab_color_space::a_color_opponent_t,
    lab_color_space::b_color_opponent_t
>;

/// \ingroup LayoutModel
using lab_layout_t = layout<lab_t>;

BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, lab)

/// \ingroup ColorConvert
/// \brief LAB to XYZ
template <>
struct default_color_converter_impl< lab_t, xyz_t >
{
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst ) const
    {
        using namespace lab_color_space;
        using namespace xyz_color_space;

        float32_t p = ((get_color(src, luminance_t()) + 16.f)/116.f);

        get_color(dst, y_t()) =
                1.f * powf(p, 3.f);

        get_color(dst, x_t()) =
                0.95047f * powf((p +
                                 (get_color(src, a_color_opponent_t())/500.f)
                                 ), 3.f);
        get_color(dst, z_t()) =
                1.08883f * powf((p -
                                 (get_color(src, b_color_opponent_t())/200.f)
                                 ), 3.f);
    }
};

/// \ingroup ColorConvert
/// \brief XYZ to LAB
/// \note I assume \c xyz_t
template <>
struct default_color_converter_impl< xyz_t, lab_t >
{
private:
    /// \ref http://www.brucelindbloom.com/index.html?Eqn_XYZ_to_Lab.html
    BOOST_FORCEINLINE
    float32_t forward_companding(float32_t value) const
    {
        if (value > 216.f/24389.f)
        {
            return powf(value, 1.f/3.f);
        }
        else
        {
            return ((24389.f/27.f * value + 16.f)/116.f);
        }
    }

public:
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst ) const
    {
        using namespace lab_color_space;

        float32_t f_y =
                forward_companding(
                    channel_convert<float32_t>(
                        get_color(src, xyz_color_space::y_t())
                        )
                    // / 1.f
                    );

        float32_t f_x =
                forward_companding(
                    channel_convert<float32_t>(
                        get_color(src, xyz_color_space::x_t())
                        )
                    * (1.f / 0.95047f)  // if the compiler is smart, it should
                                        // precalculate this, no?
                    );

        float32_t f_z =
                forward_companding(
                    channel_convert<float32_t>(
                        get_color(src, xyz_color_space::z_t())
                        )
                    * (1.f / 1.08883f)  // if the compiler is smart, it should
                                        // precalculate this, no?
                    );

        get_color(dst, luminance_t()) =
                116.f * f_y - 16.f;

        get_color(dst, a_color_opponent_t()) =
                500.f * (f_x - f_y);

        get_color(dst, b_color_opponent_t()) =
                200.f * (f_y - f_z);
    }
};


/// \ingroup ColorConvert
/// \brief RGB to LAB
template <>
struct default_color_converter_impl< rgb_t, lab_t >
{
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst ) const
    {
        using namespace lab_color_space;

        xyz32f_pixel_t xyz32f_temp_pixel;
        default_color_converter_impl<rgb_t, xyz_t>()(src, xyz32f_temp_pixel);
        default_color_converter_impl<xyz_t, lab_t>()(xyz32f_temp_pixel, dst);
    }
};

/// \ingroup ColorConvert
/// \brief LAB to RGB
template <>
struct default_color_converter_impl<lab_t,rgb_t>
{
    template <typename P1, typename P2>
    void operator()( const P1& src, P2& dst) const
    {
        using namespace lab_color_space;

        xyz32f_pixel_t xyz32f_temp_pixel;
        default_color_converter_impl<lab_t, xyz_t>()(src, xyz32f_temp_pixel);
        default_color_converter_impl<xyz_t, rgb_t>()(xyz32f_temp_pixel, dst);
    }
};

} // namespace gil
} // namespace boost

#endif

/* lab.hpp
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
*/