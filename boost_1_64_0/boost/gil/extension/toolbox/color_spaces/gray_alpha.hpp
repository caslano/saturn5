//
// Copyright 2012 Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_GRAY_ALPHA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_SPACES_GRAY_ALPHA_HPP

#include <boost/gil/color_convert.hpp>
#include <boost/gil/gray.hpp>
#include <boost/gil/typedefs.hpp>

#include <boost/gil/detail/mp11.hpp>

namespace boost{ namespace gil {

using gray_alpha_t = mp11::mp_list<gray_color_t,alpha_t>;

using gray_alpha_layout_t = layout<gray_alpha_t>;
using alpha_gray_layout_t = layout<gray_alpha_layout_t, mp11::mp_list_c<int,1,0>>;

BOOST_GIL_DEFINE_BASE_TYPEDEFS(8, uint8_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(8s, int8_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16, uint16_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(16s, int16_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32, uint32_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32s, int32_t, alpha_gray)
BOOST_GIL_DEFINE_BASE_TYPEDEFS(32f, float32_t, alpha_gray)

BOOST_GIL_DEFINE_ALL_TYPEDEFS(8, uint8_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(8s, int8_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16, uint16_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(16s, int16_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32, uint32_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32s, int32_t, gray_alpha)
BOOST_GIL_DEFINE_ALL_TYPEDEFS(32f, float32_t, gray_alpha)

/// \ingroup ColorConvert
/// \brief Gray Alpha to RGBA
template <>
struct default_color_converter_impl<gray_alpha_t,rgba_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2, green_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,alpha_t()) =
            channel_convert<typename color_element_type<P2, alpha_t>::type>(get_color(src,alpha_t()));
    }
};

/// \brief Gray Alpha to RGB
template <>
struct default_color_converter_impl<gray_alpha_t,rgb_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
        get_color(dst,green_t())  =
            channel_convert<typename color_element_type<P2, green_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
        get_color(dst,blue_t())  =
            channel_convert<typename color_element_type<P2, blue_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
    }
};

/// \brief Gray Alpha to Gray
template <>
struct default_color_converter_impl<gray_alpha_t,gray_t> {
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const {
        get_color(dst,gray_color_t())  =
            channel_convert<typename color_element_type<P2, gray_color_t>::type>(
                channel_multiply(get_color(src,gray_color_t()),get_color(src,alpha_t()) )
                );
    }
};

} // namespace gil
} // namespace boost

#endif

/* gray_alpha.hpp
g107ZnFi5ha0bybbtx0VXLaGDCzl5LljrH3SITcxmCrstZsQMzjr6Th/BgO2QBPZAalxc0S8hhqAUKqtEsTBdqwUBRfEVorCIrMzS+StPNTBlRkPTdR8O5JzwN8WNOveHNno4p+QqXQ0U6Xcru2M2bQBweBl/o6R1KYLEK8AIZeIgbNtwy7Di+y1aBKihLzFli6myWrls6tou/Q+b1tAEMaYd7GqzFuhk85+S20u7hMbFY2R72Tm+xwL0lcHpBhuaIo8l7Bb1u9WsmMwJJ6Q4URq1OIUXoI2Qs57pe2ZEU9zaPyYhdFXpcaFR7gM1CNi0XjVrjhdzaU6RdsPs1iBkFSm/s5vokQXgx7hwac1b4yT7clIhIdEuZ+mJ5Pi4vH26uFvAw+D/exIl1jVzub593FUbduF1qwLj0IKZNJmKzP2ufNrdt5ZIJ/1fJRyLaLxvhzGCs3bnezYrRGbBjKRwBm65SOEyzv2Hl4MzbOM8I/oLQkGsE3uJKGndjyG89HnAHhhkWTGe2WhMeuyZXgcekxyPg8lM4eQIhsY6O1Am7iuauSWz/YTzVREiMTLep/yssY63kH5TPU7qRIwMBLeQ1lo8+jcmN2vt9HRlHXvXrZwvw/3XuAPiTox6UadY48gCPf9RXLxgDGGyMEtcrQ6lF193HqeZAGe5bMH92bLVS66lBqLyUdFWSwT0u93dNZMPaez1PTko644DkCEncZ2HoZQ4XwkCcQ9RAwAQm/ScSFANf7QaKUDDffm+E2dorKdYGJ6RA3Zt99zpMqO9RhSR0KTmNDJC5Dyj79XExvhYSesHxg94YH4sWQDzHwQ3sbT6hfwvQDQDdAXkA8YChgJuAEwCTAVMAdQAngA8ATAAH4CVAGSoDj0cUA7QBrgQsClgBsBUwDzAPcCngW8DvgG8BPgN0A9lKExoAWgA6Ab4GJAX0BNe17W+cyRZz05OSFma/bxdcE5qPsrrHtVJtoeNlDUwhoMJXEVS7yAo4+cDEvy+e8MuifT5g/ZYeGTafQE6jOvwxuRobCwMlOZg9kIrJbTeHhS8zWvZsZO5g0vtpzGzESXI7GHt8i5GpIGZhzC8Z6lJU/2lGrUEJ111JiB8I40z6MFPnio+oZ3GqpfJ2aBrJ7ppTQZR6luJE8A4wmBBtoZ/C7efyXuDP1Dgieb+znG9p+nsQ+fj5THkbcYaizcxfSL7Qz6fOu0h2zF+RzOvMEHflU7NfhYj4XqRL1oUgkn1ZiY8iMyYscscKoasJCVz8LzpbmgNPCR81Vp4H6yM4SMJkvRB5evdnOfJl9k63/oV+O9CjUPXyfagAvfd8bVkMdOaGira2kpwsSHKxK5EdR90iJSlKhISSL6/kvMlNuXKj3cXg3mbu+gTKBYhP9gL1b4HHddIiWDKjblInJVph2EcIKqV4a8hU92or0IsNQKgGtQVZBsuBlBL2/oCEfE2i16s/nqNt1uDtk3m40H8GazoXWz+cE62/JI/XKyhyRjjjOVmPIDKXp78SPymvl6g4ZZyp+fmI/wE+Mx8jezjS6WInIP7kLvpvhWZIEHN5gz0WaeUFRuNs2zG+xz0gq+UGeVwiP1inOwSYB+mgrSWeTEpHexDTW/em+VPtc3yR2UlZcp38f0wq6iJhtGWGxDcIazbM9985D0xcB79aYz7zwMqic9es3Ja0tktJwHCbYpd72FHPeVQeWmJQQSzU09aGlN1RWY8fhRoMYJ25NexTDm+Qd5mG/byxo8le6XkEs4S6rNhlIt0djKTRaystf6dL3o9Te2NSR+yFU/DjnIISJRtP8VpuMghwWi9AJeBZztdwVPpAca54fEFI0f96WTUcnxqQVjq6i7cpKqP70=
*/