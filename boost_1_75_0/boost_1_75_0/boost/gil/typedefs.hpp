//
// Copyright 2005-2007 Adobe Systems Incorporated
// Copyright 2018 Mateusz Loskot <mateusz@loskot.net>
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_GIL_TYPEDEFS_HPP
#define BOOST_GIL_TYPEDEFS_HPP

#include <boost/gil/cmyk.hpp>
#include <boost/gil/device_n.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/rgb.hpp>
#include <boost/gil/rgba.hpp>

#include <cstdint>
#include <memory>

// B - bits size/signedness, CM - channel model, CS - colour space, LAYOUT - pixel layout
// Example: B = '8', CM = 'uint8_t', CS = 'bgr,  LAYOUT='bgr_layout_t'
#define BOOST_GIL_DEFINE_BASE_TYPEDEFS_INTERNAL(B, CM, CS, LAYOUT)                             \
    template <typename, typename> struct pixel;                                          \
    template <typename, typename> struct planar_pixel_reference;                         \
    template <typename, typename> struct planar_pixel_iterator;                          \
    template <typename> class memory_based_step_iterator;                                \
    template <typename> class point;                                                    \
    template <typename> class memory_based_2d_locator;                                   \
    template <typename> class image_view;                                                \
    template <typename, bool, typename> class image;                                     \
    using CS##B##_pixel_t     = pixel<CM, LAYOUT>;                                       \
    using CS##B##c_pixel_t    = pixel<CM, LAYOUT> const;                                 \
    using CS##B##_ref_t       = pixel<CM, LAYOUT>&;                                      \
    using CS##B##c_ref_t      = pixel<CM, LAYOUT> const&;                                \
    using CS##B##_ptr_t       = CS##B##_pixel_t*;                                        \
    using CS##B##c_ptr_t      = CS##B##c_pixel_t*;                                       \
    using CS##B##_step_ptr_t  = memory_based_step_iterator<CS##B##_ptr_t>;               \
    using CS##B##c_step_ptr_t = memory_based_step_iterator<CS##B##c_ptr_t>;              \
    using CS##B##_loc_t                                                                  \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##_ptr_t>>;            \
    using CS##B##c_loc_t                                                                 \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##c_ptr_t>>;           \
    using CS##B##_step_loc_t                                                             \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##_step_ptr_t>>;       \
    using CS##B##c_step_loc_t                                                            \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##c_step_ptr_t>>;      \
    using CS##B##_view_t       = image_view<CS##B##_loc_t>;                              \
    using CS##B##c_view_t      = image_view<CS##B##c_loc_t>;                             \
    using CS##B##_step_view_t  = image_view<CS##B##_step_loc_t>;                         \
    using CS##B##c_step_view_t = image_view<CS##B##c_step_loc_t>;                        \
    using CS##B##_image_t = image<CS##B##_pixel_t, false, std::allocator<unsigned char>>;

// Example: B = '8', CM = 'uint8_t', CS = 'bgr' CS_FULL = 'rgb_t' LAYOUT='bgr_layout_t'
#define BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(B, CM, CS, CS_FULL, LAYOUT)                        \
    BOOST_GIL_DEFINE_BASE_TYPEDEFS_INTERNAL(B, CM, CS, LAYOUT)                                    \
    using CS##B##_planar_ref_t      = planar_pixel_reference<CM&, CS_FULL>;                 \
    using CS##B##c_planar_ref_t     = planar_pixel_reference<CM const&, CS_FULL>;           \
    using CS##B##_planar_ptr_t      = planar_pixel_iterator<CM*, CS_FULL>;                  \
    using CS##B##c_planar_ptr_t     = planar_pixel_iterator<CM const*, CS_FULL>;            \
    using CS##B##_planar_step_ptr_t = memory_based_step_iterator<CS##B##_planar_ptr_t>;     \
    using CS##B##c_planar_step_ptr_t                                                        \
        = memory_based_step_iterator<CS##B##c_planar_ptr_t>;                                \
    using CS##B##_planar_loc_t                                                              \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##_planar_ptr_t>>;        \
    using CS##B##c_planar_loc_t                                                             \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##c_planar_ptr_t>>;       \
    using CS##B##_planar_step_loc_t                                                         \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##_planar_step_ptr_t>>;   \
    using CS##B##c_planar_step_loc_t                                                        \
        = memory_based_2d_locator<memory_based_step_iterator<CS##B##c_planar_step_ptr_t>>;  \
    using CS##B##_planar_view_t       = image_view<CS##B##_planar_loc_t>;                   \
    using CS##B##c_planar_view_t      = image_view<CS##B##c_planar_loc_t>;                  \
    using CS##B##_planar_step_view_t  = image_view<CS##B##_planar_step_loc_t>;              \
    using CS##B##c_planar_step_view_t = image_view<CS##B##c_planar_step_loc_t>;             \
    using CS##B##_planar_image_t                                                            \
        = image<CS##B##_pixel_t, true, std::allocator<unsigned char>>;

#define BOOST_GIL_DEFINE_BASE_TYPEDEFS(B, CM, CS)                                                  \
    BOOST_GIL_DEFINE_BASE_TYPEDEFS_INTERNAL(B, CM, CS, CS##_layout_t)

#define BOOST_GIL_DEFINE_ALL_TYPEDEFS(B, CM, CS)                                                   \
    BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(B, CM, CS, CS##_t, CS##_layout_t)


namespace boost { namespace gil {

// forward declarations
template <typename B, typename Mn, typename Mx> struct scoped_channel_value;
template <typename T> struct float_point_zero;
template <typename T> struct float_point_one;

//////////////////////////////////////////////////////////////////////////////////////////
///  Built-in channel models
//////////////////////////////////////////////////////////////////////////////////////////

/// \ingroup ChannelModel
/// \brief 8-bit unsigned integral channel type (alias from uint8_t). Models ChannelValueConcept
using std::uint8_t;

/// \ingroup ChannelModel
/// \brief 16-bit unsigned integral channel type (alias from uint16_t). Models ChannelValueConcept
using std::uint16_t;

/// \ingroup ChannelModel
/// \brief 32-bit unsigned integral channel type  (alias from uint32_t). Models ChannelValueConcept
using std::uint32_t;

/// \ingroup ChannelModel
/// \brief 8-bit signed integral channel type (alias from int8_t). Models ChannelValueConcept
using std::int8_t;

/// \ingroup ChannelModel
/// \brief 16-bit signed integral channel type (alias from int16_t). Models ChannelValueConcept
using std::int16_t;

/// \ingroup ChannelModel
/// \brief 32-bit signed integral channel type (alias from int32_t). Models ChannelValueConcept
using std::int32_t;

/// \ingroup ChannelModel
/// \brief 32-bit floating point channel type with range [0.0f ... 1.0f]. Models ChannelValueConcept
using float32_t = scoped_channel_value<float, float_point_zero<float>, float_point_one<float>>;

/// \ingroup ChannelModel
/// \brief 64-bit floating point channel type with range [0.0f ... 1.0f]. Models ChannelValueConcept
using float64_t = scoped_channel_value<double, float_point_zero<double>, float_point_one<double>>;

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, gray)

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, bgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, bgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, bgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, bgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, bgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, bgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, bgr)

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, argb)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, argb)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, argb)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, argb)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, argb)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, argb)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, argb)

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, abgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, abgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, abgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, abgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, abgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, abgr)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, abgr)

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, bgra)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, bgra)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, bgra)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, bgra)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, bgra)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, bgra)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, bgra)

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, rgb)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, rgb)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, rgb)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, rgb)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, rgb)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, rgb)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, rgb)

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, rgba)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, rgba)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, rgba)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, rgba)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, rgba)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, rgba)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, rgba)

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, cmyk)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, cmyk)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, cmyk)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, cmyk)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, cmyk)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, cmyk)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, cmyk)

template <int N> struct devicen_t;
template <int N> struct devicen_layout_t;

BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8, uint8_t, dev2n, devicen_t<2>, devicen_layout_t<2>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8s, int8_t, dev2n, devicen_t<2>, devicen_layout_t<2>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16, uint16_t, dev2n, devicen_t<2>, devicen_layout_t<2>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16s, int16_t, dev2n, devicen_t<2>, devicen_layout_t<2>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32, uint32_t, dev2n, devicen_t<2>, devicen_layout_t<2>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32s, int32_t, dev2n, devicen_t<2>, devicen_layout_t<2>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32f, float32_t, dev2n, devicen_t<2>, devicen_layout_t<2>)

BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8, uint8_t, dev3n, devicen_t<3>, devicen_layout_t<3>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8s, int8_t, dev3n, devicen_t<3>, devicen_layout_t<3>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16, uint16_t, dev3n, devicen_t<3>, devicen_layout_t<3>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16s, int16_t, dev3n, devicen_t<3>, devicen_layout_t<3>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32, uint32_t, dev3n, devicen_t<3>, devicen_layout_t<3>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32s, int32_t, dev3n, devicen_t<3>, devicen_layout_t<3>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32f, float32_t, dev3n, devicen_t<3>, devicen_layout_t<3>)

BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8, uint8_t, dev4n, devicen_t<4>, devicen_layout_t<4>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8s, int8_t, dev4n, devicen_t<4>, devicen_layout_t<4>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16, uint16_t, dev4n, devicen_t<4>, devicen_layout_t<4>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16s, int16_t, dev4n, devicen_t<4>, devicen_layout_t<4>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32, uint32_t, dev4n, devicen_t<4>, devicen_layout_t<4>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32s, int32_t, dev4n, devicen_t<4>, devicen_layout_t<4>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32f, float32_t, dev4n, devicen_t<4>, devicen_layout_t<4>)

BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8, uint8_t, dev5n, devicen_t<5>, devicen_layout_t<5>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(8s, int8_t, dev5n, devicen_t<5>, devicen_layout_t<5>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16, uint16_t, dev5n, devicen_t<5>, devicen_layout_t<5>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(16s, int16_t, dev5n, devicen_t<5>, devicen_layout_t<5>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32, uint32_t, dev5n, devicen_t<5>, devicen_layout_t<5>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32s, int32_t, dev5n, devicen_t<5>, devicen_layout_t<5>)
BOOST_GIL_DEFINE_ALL_TYPEDEFS_INTERNAL(32f, float32_t, dev5n, devicen_t<5>, devicen_layout_t<5>)

}} // namespace boost::gil

#endif

/* typedefs.hpp
vPXMrnKA3Afm5tKacZJjvoPTsB+ppHNsL6GuPnQc95ArvszYmy/xbKvXvoBeFNbnF9Nm2Lal9YHSb/k2P+4vDMKybhc4J/EiJVvJfsd3GMRBtE8fZvd7Qd+I74I+5LxPHI7dUoH3AEShkoW8Jmd6yVGyss23cW0zrtSFWeBfKfbmDCyaST0QexEima4h9iRjU+Bmb6w3BUFK3Ti4+E7AEzDc1qlzaxf+lZYEjqjy8TD24A8QK/n9AEkWsv2vYLzRbaoaSw2Eh+l6c8xLAZfXHDABAEQSTKd2MPKSY3vUFRhguMJZNaZJBMnQrQtkMSgwAMxfDeTo93bKWfC0AHWRLxVbhVXnL7VrmEcx3r0ImMIUVjH8SUFlAiHoPeDuC6/vHd6rGOqnC2ifdrAwpsosmOOAYlIdkQ7ybEAdQnGzMDlsEOzrBdnrOafKLBW4Yjy5CakxpTGj3hAWuJMlaLv4UWaTxuvvGEZT7hbNE6stSUfOQnyTeN/2CAcLRnv8Wq2mENmdzMH+ALIxfUO2jXza7gbq95CttuCZuhgHsIhFXG2BFwqsuXFXL9e3cqhzkje1doIW7mAx8u6Itr8gg/GD7fbbBKTrTkhHkaLbxrHoZ9FNy//WrIf6uk+5T9F8YX0JXIPqi3ESOyPihsHBO/PYm0zT3pNH3+M0FCryu5KGVl4LuBfDdND9OWt8+GjhU9zduvvoKaL0qXyhmeDv
*/