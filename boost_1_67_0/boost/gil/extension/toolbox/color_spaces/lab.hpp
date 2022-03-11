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