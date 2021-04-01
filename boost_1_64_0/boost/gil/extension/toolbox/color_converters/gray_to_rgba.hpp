//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_GRAY_TO_RGBA_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_GRAY_TO_RGBA_HPP

#include <boost/gil/color_convert.hpp>

namespace boost{ namespace gil {

/// This one is missing in gil ( color_convert.hpp ).
template <>
struct default_color_converter_impl<gray_t,rgba_t>
{
    template <typename P1, typename P2>
    void operator()(const P1& src, P2& dst) const
    {
        get_color(dst,red_t())  =
            channel_convert<typename color_element_type<P2, red_t  >::type>(get_color(src,gray_color_t()));
        get_color(dst,green_t())=
            channel_convert<typename color_element_type<P2, green_t>::type>(get_color(src,gray_color_t()));
        get_color(dst,blue_t()) =
            channel_convert<typename color_element_type<P2, blue_t >::type>(get_color(src,gray_color_t()));

        using channel_t = typename channel_type<P2>::type;
        get_color(dst,alpha_t()) = channel_traits< channel_t >::max_value();
    }
};

}} // namespace boost::gil

#endif

/* gray_to_rgba.hpp
IDlQKiT4HCliYSjfiCK3voUdS7BCmH7Rtmne1wc6QawrNaJkUJ1eXcDXCz4Naj0YKKCZ/vZ+gn0D/sflT2sPx3bEmQSH5TV0t++OXxk/r0q+OvlJm7XE9o6F0ERaWLTAoQxHLcidvV7VoJWWJyUGG5tgJfDvrmnVY+qH2AHujcs6UoW9p8JXtg2X1avT7mSG6gYU9xqjIdakr3P1If/uQglScIqGmIJpYymgAdForidMeO5MMfsUhETYdjUN3JMdTB0HLqtsrDX9Am7BJCT9rQVbt3veFKRbvaByvfT/HrWidURa06YyBCB/8t+3ePFPIsgijiAndDOa80yFRyK5PAQ8l3uImOXt3Zsw+3Es9fCy1a/OEhiXC+xfCHD6tJsaucKdeqlozF/HtWP4038/Y9Cj0VDXlwQIKbkQY0iuTgS31XMLMeiBQ3Vj1sNBhFtz4R2Oe660ZcFSeWw6sYY30yzKUHy5u0Q6Z5YQwjrAb9zUSVqfs0qFL24S1dc0K3AOMobyW1dl+fkhh8GZvRWmCTRI44x+LCuUBuGWcN7HnNFi3kfCchDD4VmNQg==
*/