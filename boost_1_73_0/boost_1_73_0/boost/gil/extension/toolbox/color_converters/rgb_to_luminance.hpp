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
r0nsyfm5O7p0L/ghNPdaR4Nuu//Z6fWb/UGPCenKRBxuQBPswi8Jj+dklUIPBSdGY9kELMayDUwxPZS9ZMKJYKaTYOcVjS/MipzUav2jd80u2wZhr/Xpt/7Zr/XOnU7zNNXremNNKlsFlupmvV3uc9BlWrFZ6DCZTMBRgP8GVwebE4QSvPpviRejVw/moHJcCcCb1IwMXqJgnZZz9r7OfifuUqGcxJwfhYHkN/IN0a6V2WHsO7IUk56wCrLstVKeF+yk+aHXgiHfy+o9ijkorNEOUOQYTAT+uOALtfyCBzx2KQxADILx4znjwSgcQ3Ol1iNVGHjJAySnyTM1cEJxJBh7wQXSRqlCPPQgoASywkL0E3QyZqd+9YKv9GWHPIIA8hAvIbQGYxUdaP6oujexFgB1G7PDeAaRdIDPgbXjEDBA8AX/JFKRK8T1OFpE6rFQPcKYzBuYia8AIVTzqZrkPII/ktEU1QcDeIOJGf6MwkiFHDciWtNQyAVrpiZcBXWcJTJx1fZmO5747gUTEQh3MkdpX085hTeYA/VVjWI4CkTvjVxEHUtgFygEDxB4qJWOpv7FT88quQOIAaSAtooBVlcgJvo+D0AVtEoQoct4+DyzzL0wkV81IatUz5UCQHxPAKoOOS6HtBMRB+EX
*/