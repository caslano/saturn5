// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP
#define BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

#include <boost/geometry/core/closure.hpp>


namespace boost { namespace geometry
{


template<closure_selector Closure>
struct closure_as_bool
{};


template<>
struct closure_as_bool<closed>
{
    static const bool value = true;
};


template<>
struct closure_as_bool<open>
{
    static const bool value = false;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_CLOSURE_AS_BOOL_HPP

/* closure_as_bool.hpp
7sd2+Ca2xyMYgn/GDngOQ5FjLagjtsArMBQ7YQ/sjEOwC0ZjV7wWu+FkvAoT8Wqchz1wMYbjEuyFa7A33od9cDv2xWewH+7Fa/BljMA3sD+ewAF4BgfhNzgY3Q3mUGyDkdgFh2FfjMJrMBqHYgzG4AiMx5E4HUfjQhyDmTgO1+F4vBevxe0Yi49jHL6CE/EgTsZjGI9N3ePfMASn4BU4DQdjEo7EWTgDZ2MypmIGzsUlmIZL8QYsxQX4AP4AH0ML/h6t+BFm4Bm04Tdox+9wEbZvznmGEZiDAzAXx2EeJuESTMEiTEcXFmIxrsSluB6X4cO4HJ/BFfgy3ohv4k34Aa5E9/35KmyOt+AQLMFILMVReBeOwTKcgvfiPNyA83ETrsbNWIoPotIfUe5/5b64vEp/xARph6ZhV5yOPXEGRmIijsWZOBWTcC7OQhsm4xKcgyWYguvwOnwU5+IuvF5rx+S+GO8zacdGSHlG4hAcjSNwDN6AY3EhjsfFOAFXYCyW4kS8Gydp4yTkXhgTJD/9OImfynWnHPviizgef45xuA895W4i96xyD1tOGKCMb/AsN0i//PnYBxfiILRgDFpxHGbgJMzEOWhDC2ZhAWbj7bgY92Ee7sd8fBUL8B0sxL+gA8/jEmwm/VA7YRGGowsjcBmOwRsxHm/C+bgSF+EqXIE34214K67B1bgR1+D9eAc+hqX4BN6Je/EufBnXYQWux7fwHnwXy/Ao3oencQOexa34PW5Drtn0L5frZxO595R7Uurb0196nNT3I1LfP5L6flTq+wmp7104Fp/E6fgUXo+7MQufxZvxeTyIP8W3cC8exp/hCSzHL/BFbE7eP8cOuA9740s4GH+Bw7ECp+ArOAcPYDb+Gl34G7wdX8UyfA3vw0P4CL6Bj+Jb+BxW4gv4Dr6Cv8PX8TC+gX/A4/gunsIP8ByewK/wpH48gtxf9iJwbBi+P3eS7z2d8SrsgrS3nhOoO6F8W3AN/Uv/99+zcnhb8CXbl/RSfdeK2of01LbgQD/SRuhHen5b8CXxzpW2DN7vQ0gm5BHKCOWEI4SzhBC+qEYQYglpBAehlLBje6A/Z2AJLIElsASWwBJYAktgCSyBJbAElsDSWEszQlfp/8/r+jKdKxyuwpmTbUNseXlBLEPot98SK7UY7Uz77SdOS5qhzMEdrMyfK5/ecrwFzxH5kaEwKseSMinVkjgtJVXpK+OXfM/Kp5/6QPLNibJZ0oZHjrYkxc2Mb/x8h0i+DnnWPOZE1Xzj01Ljk1KmzUpKCfLDdvcif/34hB1Hq+TvhzwHSJ7p8ogmTb/NsyalJFvmxKckT5vsj+1V6/uk5O08JnnTmd/TY9PdU5zRI0W8Z87lh/zlOGNOC+nE9r7kb4vKUfY3fVP9mG+l5LvgA2++F+P4Tpb++TEnvPlezOP7gOTf67g3f38d3+o2T5YxAVP1+3hOSlyyM2ep1WWfYV/h3tmNn796flVI/qE+8/df3uNayJwv+ryNG97oeavH+AuSd6R53o2er3qMRbSU37eO6/O9buKM+HmNnqdazzslz9P6PLU2lJPKD+e0mne4jA+Zozun/d1+q3W9UfLefETyvuG6aUmpI2IsOS6/5dlK7Xuv5alm6b/tXCl53q7PMzrKL3mOkDybST//jep3AU87zRtxc7JWWDLtvCKBi2WhU66UjV8Oji/DeIPXfJTDn9fn85L3bkPexQ4Lr5n053Gd10bGiR7R5cve9keeXKcM7xl83LCt8v7FxQyLtBRY8+3+yz9Pxm3EnqiWf86iAqur2Gm3FOTYGj1/9Tg7LfmXH6+afy5XqmL3y9AaPW9127Olj39CtW3PKSri1TCeqvc=
*/