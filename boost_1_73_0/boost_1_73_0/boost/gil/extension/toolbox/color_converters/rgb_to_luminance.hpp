//
// Copyright 2012 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_RGB_TO_LUMINANCE_HPP
#define BOOST_GIL_EXTENSION_TOOLBOX_COLOR_CONVERTERS_RGB_TO_LUMINANCE_HPP

#include <boost/gil/color_convert.hpp>

namespace boost{ namespace gil { namespace detail {

/// - performance specialization double
/// - to eliminate compiler warning 4244
template <typename GrayChannelValue>
struct rgb_to_luminance_fn< double, double, double, GrayChannelValue >
{
    GrayChannelValue operator()( const double& red
                               , const double& green
                               , const double& blue    ) const
   {
      return channel_convert<GrayChannelValue>( red * 0.30 + green * 0.59 + blue * 0.11 );
   }
};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* rgb_to_luminance.hpp
t3v57zkM+e/po/z3ZJG/9M+u8vnQ5B2QXofP/Ixk4bWnyPX9P5fdRK7v
*/