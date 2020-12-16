// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_HPP
#define BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_HPP

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{




/*!
    \brief Traits class binding a convex hull calculation strategy to a coordinate system
    \ingroup convex_hull
    \tparam Tag tag of coordinate system
    \tparam Geometry the geometry type (hull operates internally per hull over geometry)
    \tparam Point point-type of output points
*/
template
<
    typename Geometry1,
    typename Point,
    typename CsTag = typename cs_tag<Point>::type
>
struct strategy_convex_hull
{
    typedef strategy::not_implemented type;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CONVEX_HULL_HPP

/* convex_hull.hpp
2lIlVIil5sB+w0Q1TBb/+h/EqGu4P+nkWf5hcy7nm5TLLYxrvT5p1htmcrK6SUJcuynDgWsnJ3Ft2MQ+BT7X28rcwO7kSqy2eq7EUiuxEmOduyNPOu0o+YBZoUPJfD5MT6kz5joj2dGEACEUGtu5rZNSptTmRqYUYfcfMGh6aRtdpLaQnrotl5nSearQrkBGPSz863WBMNvSJvP2nF14W8GQ+YW07dpYF11/oJ1ZOft3eWmQw87s4tdpZ3ZwWooyv5Ap8/vQm1L7D0yS+YV6k/ml1LMrERuqtrmCmBjvVjWv4pq/lutQ8/rXqOaHeYWygXMjGdfm2HLMGheblSy1NJ3+EktYnNfa4JEcZSBjs6fXxu33cDLPkxLdh+zF4aSYh5N+IvqSOyVE8/YGoimidERqKA3dGygFlAtKckXhX1xuGYxAdykpPyOJJ57NcLofR1p/T9xYKnW54WuZZQHe+DoWEknPmt75OaThEPViiPTQnGJnLjU780grJcIMTurMpb115tJUOrO0mQm9h8bQ0z4XdjSdeuVqKSZQ0g43RJ0F5DgLLv7IFLHTOiDQaYVC0YzcWSZydqQCwyjyO+Pc/HzBf6R1iH2/fb99v32/fb99v37oX5DXyUN2dwuttbq33NLeVac0LKQ5e6ZDbP2jRFpwdHJ8VtdTZAFEhlGm1rLdi7dx4TUsLOYrL6I+fBMGYWpRfs4a0KMYpi4Z9ylPD3MsmXOOi3POwZzJC7MdLl2bYsVAaYlS2yOvT1KqKNWEbss/6VaqBRt5m3GxV20zhqhtRnYnbTOmcglcrrkmg7Ce12S7c/ZQqeKLr8kqERuqNsWrmv/gY7vmr3DN6z0ONc/bTDUvz+l5KUcAm0uFQsUd2bIVNE+rL7j0wACLVjEumQ12utQOxST1MJPU5nbgluyUVr2uL7odQO4F7GaIjeLM0DJW2VR0vbURPmC5P9M+3f4bkzff7UDen7xA5P3tgMTajnCoLSna6kfbdw9IqdZJR9uIeJ9qBDP7eagNuDmoEcwkpVZ1nD3tI3jjYGc+aomEeYt6n07V2h/xseGN/eOKJalJmUd9Ua6I5Un0NzcR+ga7V7v3hKO3ZqaEe9oXxZ3x7EVaxQmob253Jw6m5dpg+la3LbMZn048H4hbyTz/zLPE812+FAfTcnMwfcSXEmGSpVXlvQ2m5alweiViQ9U2B9PtO+2aT+Oaj9ntUPMXNlLNP8zgwbTc7AQ9z8K5o9HcyTTsRuFD+kjUTAPutZbWe2b9rTs+Gl6asEnxaHETq0R8Ds/bMQE874AnhqPNk8AmdjpVAs+74HkQPO8W33gK4dvEO+l0eN4rnthdD4UnqoG3whMNQnrg+SA83fB8SDxRGp8JzzUC3iMC3qMCzk/E8zEB73EB7wkB70kBJyKea+E5BJ7rBLynBLz1As5PxfNpAe8ZAW+DgLdRwHlWPJ+D59CUumkRceOodFQiKRK6TivVQHfK+/YBTJFT40JXY5ONjQkRmynCJW6UQHerU51QP92IcF88OTkSMeXPdvpsXyouGLRtEB41g7rp0u2axfP4cgCLSM2HsucDH33sSmViwks50EntE4WctD05KMHDph4F/RiZSh/FdCTU5xpya2x6z+XCCOcOZ5JeyfB3KnMvXFkWDa+z9Inp+k+7pXR4mFcf9L287pymmsdZw2Cuc28GQzTB8Bk9xRV6w0c6xzU3Frq8aJ+t52iIbxhqT1eEJ57b9XN6Gvslyq71XgMWMulOer/n0yu/RIGxQpjPIZkV2iFjcrNgJGuCOcVu8wh/YX33Qb7e27IxQ/bB9tQEwUmnelBaCvrBoX7pB4f6Xm6G+r3cDDksN0NkR171+5c=
*/