//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_METAFUNCTIONS_IS_BIT_ALIGNED_TYPE_HPP

#include <boost/gil/bit_aligned_pixel_reference.hpp>

#include <type_traits>

namespace boost{ namespace gil {

/// is_bit_aligned metafunctions
/// \brief Determines whether the given type is bit_aligned.

template< typename PixelRef >
struct is_bit_aligned : std::false_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M>> : std::true_type {};

template <typename B, typename C, typename L, bool M>
struct is_bit_aligned<bit_aligned_pixel_reference<B, C, L, M> const> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L>> : std::true_type {};

template <typename B, typename C, typename L>
struct is_bit_aligned<packed_pixel<B, C, L> const> : std::true_type {};

}} // namespace boost::gil

#endif

/* is_bit_aligned.hpp
p7q0NJ9V+rn1JSERuaLxwtcJIaf6cS0gJ94fIeACm9KS1qTg+WdxARUb0BieNDXZBKQNWwXJ6k3j8dfG0faR88gqdX1p5Ki5Pg1FMA+aG/ImFXmID63hm0qeOhafFWZVuP5aatmP5g+Dc0sEVTz1D2LSv4bAFcxUyIAwvgkdSi3aWk7alMJQ86RIAKmdTsXsI44Jr9iVMeYd246D+eAfPPBE0xe/58ETsudRt6GOgJvwC63qSWX5mWujNqLyZzZERE1X5sPA0ivzkDXLwFNcsnGSsG1VbXJjzAa/JcDg581NpbZI90sTMyWMSNOj1mCIL/bX4wwgeKxdBF6/aawL8y5I9Cj90WL33aWJ3i13eWBGS1K93dipCQiYIZW5cc/EnF2sTMAt27exZDAL45KAlqVZ3tTHVrzInsYBQeuyszzXWp5qwXQCPw+Jlxl2KcYNxBTQsWu8DuniqTc1bfcGfyUyvhmGDyO/iMx6KO56wUiU+Hlwb4NW5ngTl1FsmGpNKMWPIh+0Zopffc8Xfa+mT3Swj7JgjnSZ+iv1fPAZ6SADPD8KcjTM0Yh6cR/AVDBEoDoTtgh7zOUPzpNW1BFtfnNaxyeeM1KLLn39A1rmEHMnyNnBzHxYM9QBh1PLq2QKN3f2hTiKZ5+uRyHn
*/