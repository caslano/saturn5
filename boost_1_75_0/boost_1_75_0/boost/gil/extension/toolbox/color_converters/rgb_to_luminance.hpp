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
qNAxKnGMih2jUsco6xiVO0Zljp2U2SU7oWRrQ+TQRZldmLURTsTISSaGpMjtckkdcjEO5H1TXpMz5iCITQAOgYstBiNSIQ4cSKDgpSkfd3XIjkGoOuQCAB0DeR8oOcPb+jxEQbFWCMkgtUZVxVKExtWxSjhLba2QEphdq0BFZQXlfXByiDlDDLiNmER5jQxxbHsEVxy7heIqii/CCAQEUo5T6FCD2CHGOsRkEHOyIYZy5RGxfYS1j8js6xI54JM4xKQOMblDXSJ7jBL7iNQ+IkcDKLJ2vBn0u1ioZOxp8caRVG9wnRKGwZ4XBAAWIASjmRaL4SRC+oBEgm5dIN4glwO3ERPTAasBJCCzBiTWgNQakJOtBJRVcInLg2x5UFYelJQHpeVBOWJiZKODLcTaQjJbSGILSW0hVJaxlWVsZRlbWcZWlrGVJSHkgJMix5Mce5+cQSrwfhNg6fyEwgQFe9EaU0olXrzt5AW2k8ALeZN5GwkiDOvFK24iL3wHgOUVQwznd0vwWqCXdT8FSsP3UwCBGqfjPQleeNOHkEVmKIsVHBYpOCylQHmwxIQCMowZVQENUqmlXlbJhkK8YPMCweYFiqEX31DUdBpipH5oqRLDcE53KGf1HtH4Y50U6OoUTSUx1bobdXkd7R5VxDuLTTTkY3A+GU2JDDnNuyaCJkZTzo5bQamaNFXV9ticJjLXmJdLHtJBX8SiatqS
*/