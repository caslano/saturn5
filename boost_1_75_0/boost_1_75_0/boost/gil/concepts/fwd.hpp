//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_FWD_HPP
#define BOOST_GIL_CONCEPTS_FWD_HPP

namespace boost { namespace gil {

// Forward declarations used by concepts

template <typename ColorBase, int K> struct kth_element_type;
template <typename ColorBase, int K> struct kth_element_reference_type;
template <typename ColorBase, int K> struct kth_element_const_reference_type;
template <typename ColorBase, int K> struct kth_semantic_element_reference_type;
template <typename ColorBase, int K> struct kth_semantic_element_const_reference_type;
template <typename ColorBase> struct size;
template <typename ColorBase> struct element_type;

template <typename T> struct is_pixel;
template <typename T> struct is_planar;
template <typename T> struct channel_type;
template <typename T> struct color_space_type;
template <typename T> struct channel_mapping_type;
template <typename T> struct num_channels;

template <typename T> struct dynamic_x_step_type;
template <typename T> struct dynamic_y_step_type;
template <typename T> struct transposed_type;

}} // namespace boost::gil

#endif

/* fwd.hpp
xXQWMUQvwwBOkEZ5BFOkYqVQrWTWZKhV2PqmaO8A0Eijck0Z91nlFKt1JzGkqss56pvb1WrTcNQ1KZhWjOvEcwFldBryv3CPKReVRrq6UkxlWS//mFqo+QgtHtlai97JJWjWpcuophmcGlYucarmA7Yk62hj1Y7lVdPlVME4TScpJE0tSjDKM+ja2CAZe+O0c5gru1ixajVp3dMZMvTrMkShvGrLhWj0GJfkzipKAbYoSi/QktYcapKFPQKyNZjAsL8Hw211DKszbQghqg9/yVXjefV2VUUMzfxROAap1tUkGW4fPefOopCXb7Nt7lHFVyR7rADor4eS6+Zq6WpH23Et4XFOJdv0SyVC7rT8sk1QKP9sYTHUKVajH0ChK9f+htT6DVCDG6VRzqjBZJtZo5SQ50Rrq5P4oI6IN5uyMJ0BQpXhK6ZNjli4Kz1YXAE4O/skPixE02t+6TPSM9iqYmRkJ46IictdWT07SamP2DaHPlc0TkAQq7XTzPOiKq5N3pu7ski4VUMpQ22Q0MqFDCqgZU1glMPhWZ0QFigyQztpwZRZHIiVy5VlyHIMIbRpgyXuaqerQsxmJMHuFycMz+bLsUhmTVnVVQ2jaUTIkKofQKGXT4o5oE5abC6b8OWFKbkrewBGKq19YxRyYJaIjg8m5tZpVflE6JyW43N68Uz69JXmkmE8TKrBso0TZc8GZy14UjV0BapvL5c1
*/