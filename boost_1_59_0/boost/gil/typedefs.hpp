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
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
*/