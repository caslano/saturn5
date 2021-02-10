// Boost.Geometry

// Copyright (c) 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP
#define BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace io
{

namespace services
{

template <typename CSTag>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_CS
            , (types<CSTag>)
        );
};

} // namespace services

}} // namespace strategy::io

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_EXTENSIONS_STRATEGIES_IO_HPP

/* io.hpp
RswbWABM8FmT98GbCBsnyZxgvhEFBI7n3WBGeUORlxfk5St48T/xm7xIXy/FyM8/9oaQfV+Mr6/gDTwlpuLwGl++h8/89bkM58orxkmamNzjX3xr4d/Ix9ys9ffm7yEdb5bjLOGzIacO6ZSPSVqsJm5DXIk8KAXmIojFVSNfNb6qxoEhZ3QiGVAki2MAxTN1XFV6TOmv0UtBpJuM9csz/aJ3cTm8jj06dRgtJrQ0HMcztZxqX67xxVLpqbNkkGl495BPeCysc77IS9I6iGdClswV+YumQtfyNphndEvmILo+Zw2MpHn4WDfrMAipcu8ee7669I7oh5un2Ud++ug452pzIyPnRxlTeRrxZnJ21hvqsAJG/csBX105+LpAPX7waQaEr47TgvHmVAYBGS7yz/3b5LnwezBGcfAr01SfrcwzjTH5oVtONEWw3USV8YUTVZ4XTTQJXuo0vz7NPFEmqUbJ7KDN01OiXd26O/fuUk6zjya+Hz86SrJMoK37EOHOwETb5qfIDqgS6URo1HBa2+ZU8Usbd961h+RFlYx7fx1rlfc0mNLAY5Xqrphg2lfv3+qdYa+Ly/vN5QS2nTvi2GcGXzLMsaLanWFFliJiLDjV3IZLbBnidL9SZhSVJN5kdhpnfGuBAdAQgNwI
*/