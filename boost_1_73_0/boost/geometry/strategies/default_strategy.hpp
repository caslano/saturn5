// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_STRATEGY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_STRATEGY_HPP


namespace boost { namespace geometry
{

// This is a strategy placeholder type, which is passed by the algorithm free
// functions to the multi-stage resolving process. It's resolved into an actual
// strategy type during the resolve_strategy stage, possibly depending on the
// input geometry type(s). This typically happens after the resolve_variant
// stage, as it needs to be based on concrete geometry types - as opposed to
// variant geometry types.

struct default_strategy {};

}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_STRATEGY_HPP

/* default_strategy.hpp
4xqozuFBcLjVH4TARwfuMTC4d0C8jQXcUsF19fQUehAAbgh6vdpWo+CG3Ck5jBhn8DTR5wceyp4i+L1d9yiMFn3ktVH18buM+mKHK15Uo979ifiKkDzqK8Kty9NUvgqaeyy5IZNk0AeuD/NxzoAHY0gyZG1M2mi5bYSHY990rxiu2Fcs9PcNpHrL56X1eocWWq3qmrWjXsa7asnHsOLgQ0RccwwrvRkHxzrw+S45UPtwInSn
*/