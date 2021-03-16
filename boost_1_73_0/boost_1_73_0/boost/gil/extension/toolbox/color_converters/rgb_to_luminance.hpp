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
szS44TfH+et9c9K23N/qfjrz47+8uGli34P33L6JsTepPX1TsLhk1YnZo0+Ozh35TPN/M3ZZOrZ/Wu0c21m6cf1LhXM2Djl8BhYNUPuJE0Mf2PqjjWvnvHFLdFTl+5Cw30Ptb614e0/fV3d8uSw+/pKn1t8AYnuf2kf/ceX6U1c0vnjb0nm/u/WFf9/L2NQMbJ/QW7Z06/ruO588M/7xcW/mrOEvqM1Je/aOxXdfuf651iOXnN7+VenlMxm7g9o=
*/