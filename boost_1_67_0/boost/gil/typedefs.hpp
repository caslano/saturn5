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