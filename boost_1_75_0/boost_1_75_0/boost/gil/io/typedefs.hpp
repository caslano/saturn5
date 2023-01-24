//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_TYPEDEFS_HPP
#define BOOST_GIL_IO_TYPEDEFS_HPP

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
#include <boost/gil/extension/toolbox/color_spaces/gray_alpha.hpp>
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

#include <boost/gil/image.hpp>
#include <boost/gil/point.hpp>
#include <boost/gil/utilities.hpp>

#include <type_traits>
#include <vector>

namespace boost { namespace gil {

struct double_zero { static double apply() { return 0.0; } };
struct double_one  { static double apply() { return 1.0; } };

using byte_t = unsigned char;
using byte_vector_t = std::vector<byte_t>;

}} // namespace boost::gil

namespace boost {

template<> struct is_floating_point<gil::float32_t> : std::true_type {};
template<> struct is_floating_point<gil::float64_t> : std::true_type {};

} // namespace boost

namespace boost { namespace gil {

///@todo We should use boost::preprocessor here.
/// TODO: NO! Please do not use preprocessor here! --mloskot

using gray1_image_t = bit_aligned_image1_type<1, gray_layout_t>::type;
using gray2_image_t = bit_aligned_image1_type<2, gray_layout_t>::type;
using gray4_image_t = bit_aligned_image1_type<4, gray_layout_t>::type;
using gray6_image_t = bit_aligned_image1_type<6, gray_layout_t>::type;
using gray10_image_t = bit_aligned_image1_type<10, gray_layout_t>::type;
using gray12_image_t = bit_aligned_image1_type<12, gray_layout_t>::type;
using gray14_image_t = bit_aligned_image1_type<14, gray_layout_t>::type;
using gray24_image_t = bit_aligned_image1_type<24, gray_layout_t>::type;

using gray64f_pixel_t = pixel<double, gray_layout_t>;

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
using gray_alpha8_pixel_t = pixel<uint8_t, gray_alpha_layout_t>;
using gray_alpha16_pixel_t = pixel<uint16_t, gray_alpha_layout_t>;
using gray_alpha64f_pixel_t = pixel<double, gray_alpha_layout_t>;
#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

using rgb64f_pixel_t = pixel<double, rgb_layout_t>;
using rgba64f_pixel_t = pixel<double, rgba_layout_t>;
using gray64f_image_t = image<gray64f_pixel_t, false>;

#ifdef BOOST_GIL_IO_ENABLE_GRAY_ALPHA
using gray_alpha8_image_t = image<gray_alpha8_pixel_t, false>;
using gray_alpha16_image_t = image<gray_alpha16_pixel_t, false>;
using gray_alpha32f_image_t = image<gray_alpha32f_pixel_t, false>;
using gray_alpha32f_planar_image_t = image<gray_alpha32f_pixel_t, true>;
using gray_alpha64f_image_t = image<gray_alpha64f_pixel_t, false>;
using gray_alpha64f_planar_image_t = image<gray_alpha64f_pixel_t, true>;

#endif // BOOST_GIL_IO_ENABLE_GRAY_ALPHA

using rgb64f_image_t = image<rgb64f_pixel_t, false>;
using rgb64f_planar_image_t = image<rgb64f_pixel_t, true>;
using rgba64f_image_t = image<rgba64f_pixel_t, false>;
using rgba64f_planar_image_t = image<rgba64f_pixel_t, true>;

}} // namespace boost::gil

#endif

/* typedefs.hpp
lXvXpEXnbzTtb/vCpFo8mV62eCpEaTcX/X6udrVjr3vP54ndsu1HRFS8gJpECNnOlYq16G53YYfw69K7h+LR/W4/azobEnIXtHKJT9cobfuF6LbNu1luKPXFSjfyYSMSTvWWvhEutXgPNFtZjo7HLV5PCLlmXAeo+w/iUVPFd8qGy0w1Mz5cxBcENporPnQhXtGHzxDcS18Qtp+7c26ugTo/ur3XfMmeZTsqQRC5+yXGN1pOvbt9xwD9vP1LgEGBXGV6n2NqKGHyxFpkTJl79HmL0IPdSajZ6xCKlmzWO2duWwOo4kNn3Iisgubn1P2nEYdR/qsHodfLAWQb2XQPTA3odPPGl6+qWnknCbBOKPSepDJ7ntq3dsqYMqohPrxmfVGze9hAzrHDRtXMSyQ1l7SKBM4Pic0WljuXYVjPlgdkJ2zZru/hq5G21itbpNC4KAivrtyO6uVdJg4VxC3V/hcq2o7S9mOabgvlPev+Xaih2bGCWkGk37yAF50qC5UuzLyvgmQPW9fuZvHoXfnEQKCHX2mC8dvwQQmGMZfGYadrDOBxSvDX/Q85xeyQDPvXQJ3qtEv8U7wCTekYCdvm7dmzMHRUxVdcM8Trn0PtoY0JyFbD6bCYly9y7ahA+ZmRZz1XEv6222D0LgluKFOzomQjx4r9jdcP2CeXh3BNjmD7jM34BCYK1GKrgt5/AUmb4kl5xACrfjuqlg1+
*/