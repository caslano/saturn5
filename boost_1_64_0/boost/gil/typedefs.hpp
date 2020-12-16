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
q3DrJqhTFJ3rceH2qHF5/nSOa7zSBPC6AyqC0CSWu0fJX1Z+Y5gjy3TZVi6ISXyjT3mZFZ+taVL4totP1NiUm1PhIlIRsSuxoW/UyLwG7mPFNzYoxx3kQMU3EtbUNx7meDXYhaslnDhp4nkszoCzwnFa4KRI+UdxYBxpxPEkToWMY7C1RjSWhMTzxj1W5diuMmMqPpZTJEd5/8pDaQ9hi4xxMXPVL2J54XLeRDTO0x0TX1cUfhXEVVIkxcQkT+J/T+EbRAeipFMx0p/Gp5qJAj+EzzwOEtje+YLWc0e1ehQuJq5BjEIsF8o07uxxSoZFJSsI/ZknPJuncW/SuCZs2hxxGgd5afN6mwK3RK5zk0cmquV4TXMw9GF0H4GBw2IeiD6mOaG7bn4vu552uquu96Kb1UP/c9W/zW9sUFuF1sT/weMV3YcP5Stv1bqa5pHWlugjRf7JtkiQ5Jzmd5oF0h2ua/ywRZhPkRD+NHk6T/7+OKVvVoh2zmNaIhR9ibuKfKMfL3Aa1KdFfHRBS4PjDOvp0OOV3te0CRajz+dTk6R8DAo3trVAoqjhuJo0nWOPl77LOGhREW3cAhQxyuIujMRBNeQYSntK38dxqG6c4BECRQ0mizKf/D5CH+fxosKPTVVFWThxxkh8qgvL8Q2WM8IcIRXYIGtBWevHX5d4adMi2N3kDo8oEh7p8WpOSuzvGDJLz+80VbpzFW4Dj/wgzkuHO0l54PfvAtf3bMZdJIFY/tDj6r59gsQr4yLGNouXPvS43J+HnyDnBfU9qzxNfOL1f8zrcYUflFgZeRNMfOskvnmCysPehKhBkE7GvPCxprtT4WOsTINQfYnPeVBnnMDPIcchgzlitgT+9BhQH99TfeA51dbxm+ZB9UHnnOgjsYY0ZC6MatWHln9Jhvi7Goe2wShUQTH9HdQD0T/0RIlf4L4IIz+e/IYJeXhF4EeI7Y1rvESXA/5JzT2PmXui/PYqySMw3xLuFOds7M4p/BoxJgHClgl/inOeu5DjG8R/WBmkKVyyh5FrLUNcE3QDG6PZQlsMHeIUy4T7I4XbpjGWXmMId0Kmp1gHgVtaBQI5vGu13qYFL6pVrPoo2ioskP9+er7d3ar6OPQkue5N0iCspBHjPs3F2MeK6qOOswKj2LA+prlgPjDmgyRXq+K0sygZ5krQqb2qiJErIbDf+39IbWPNoF/qfpK4TOMyQT//h+TGYraeJG2OZW4rSETdca1XHMm7K3LNYMUEEBn5naTXakbyrsKtS8gJKQwcYPgg3MH/5nuvofGdKII9ykArgkYEZ5eytblU1d0VhBPflilciBc2j33E7y+FS2volMDNuiS2bRE5PX6S+HLtU9VHnfVxdBP32IF9XFN9JD4sCnnVjfH/y8dPVR8BdLHQZKqPaT4o5/uK0gcbZPvE3qSxnF7kdJfMjmp9ssiNSUvCn17cFIt1+Kg6W+KqSdI8pLH8P3QPT/eRV4UP5ynqY5IRtS5UH2FRp5DhWjuW/y8fl3QfSR0GuBmpj/9DB7qmxjNEsHuammJiX0zqQD/V+GkcQBqNp/cGkSfZ+c9HVZ64xBQtyr3xw4YTHvD+pfASm/+8TMMRb3rcD63KMYuQlQjxeNPb8YD7aUX1YVK/NoESK6e/e7TXrKpaI7ZAK4onUCfq4/U+Ovcf9q4Euq2jin45m5sNFwoEKMGUEEKB4jhL07JJlmRLtiwJ20kTNkW2lVjUsYVlp0nZDBQIe9gLFAjrCXuAAgEKhLIVKBAKlLCHvUCBsIedO//P3P9m9GUbzinncA6GpPG/d97sM2/ezLxxwhd6u1K9WHe64Rm7O6Y4ecgVsPIo5hLR40F0+zviykg=
*/