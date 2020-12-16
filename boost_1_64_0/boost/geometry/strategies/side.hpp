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

#ifndef BOOST_GEOMETRY_STRATEGIES_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_SIDE_HPP


#include <boost/mpl/assert.hpp>

#include <boost/geometry/strategies/tags.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace side
{

namespace services
{

/*!
\brief Traits class binding a side determination strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system of point-type
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<CSTag>)
        );
};


} // namespace services


}} // namespace strategy::side


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SIDE_HPP

/* side.hpp
Z93zr8ed1iLst7NjHhttx3b3nyG/i12lfUFqb71Tpe257u4L/DLQ65xS5bLy1+Iv7dX/6qO/sAqftimzSteq2O0v294zfRkYz51638l7aGdO6vEAfpZOM/MHhW7ZFTDHWm7scnpOpn05rq7S+yaOeQ79TPmWRtgvibmg/Thav9v+wlvYD2WWNXX6XYQf606sc4z+GtyHdgN3ApgdfFPXMtYoJe9K92mfjdJ1yndxN9C8bvoq077ra2m/ot0uznsQ+0FNf6Se67Jtik5alnRat4n9iNqO0uW0DGTLEPJt/XojJavaP6Xx/DqjF7ul1z1ZFx+HrbfXQSd00wGo5yZ0AfDWQycALufuAT13WU7Sezl3zsMHLn3AA3pvRHnadtG2jO330vk7teyAln02wnLr+rmz/d337g/uTTrnLo2daIfdbjVHhthPqObNcH9wTzor2NHYDpvoPchVMuvaPkxjF2ioO5nwhdvzUetb6CC7XTJvH/K2a70En7maq1qHaR8z+k3vkXSsy6OtMl/ZuGrdztr/qvILq1gn77gKW1bRT/unFtZxzq12jol6VzPXBns4a8723+jxAR9qvVH+XS1Pg4Epe8DVvsx7s7zINeKzKOHqcMSube3OCfSHu5ez5fuxqKuRt8+K9Fps6wOGax9U6sxYn22qNVCt165/AO30nYVpe0TLfbKnuT/ODIFzDhgZvve0DSL4uHN/cGfqmy2Nzdw39+wL7nmNNAFSet3lMb+hxlzNyfu550D2uY1rU6NfJFzvR7Wu0DKLNlFbsZbbbXL9q6DRw7ywz/HttF57NS+OPA/el+jaPPE9B7vv/fZ5L/M4LUOQLc+5eH8u6L8jxXfKBXcS8N25YLfAE3XTIjSgZFqVFenb5ILbUBrxz1IxwXfcPhfcnurM32kL6Iz8cXPwSfoEj9mS3K/ZnA82H87P7BB1LCRlP/KnzcEv6BN6ymbdJ7mNiI36nv7nzUH5L5uDGaIhYk1jFjSAi7YQjpVOxwuptj47Sd9GxNeSOn+yaUtwcvOW4D2PQWzzjbp0fybxtlywTcRb+4KtNzY3NpnzRPf3TcRyHHJiHBZU2oz7gtvk7hzk8UCVxDPr29YXbMt9NNgEuNEH9JDU1gdvCbYe5vm9Z1M+2NTaHLxi25bg3fR5zVn57AV97Lxs3N9Qmdvdbkvw1QQ3naf5HtxJ/fmq/DDuCAQG73tVvPEYxUbYCBvhn+ydC5yVYx7H/+85ZzIoTrqYiD1oVwinhBEyXU2EIy1Z7MzUTE2a6pgzXRAmQgiDEIVBiMLssiu33XFbIXYQWtexbiGMayHa7/99nud0TudMttN+PvvZz3Y+/fr9f8/l//yfy/u873nPmfNufv03Xu5v7s4dl+/vw1d4BstPyudaK19KK/OlcweRdzuJLNpJ5NHO/G1xV5HB6AHoPxSI3Lkj7wPR15N3JnkfYn8a5s9xIyL3Yr9D2vKdRf4EHu9M/q9EzuYP/Ka1F+lE2lX46IH9Ge2MIj+OPm17kYfhn7jOaU87Cyl/OfYtBdjUORf/x1Dnr9h/oY3dQE/a25Oyo4jnbbgXadXYe3PuGUPdnakzGJSALUnfNcJ5izJdyH+NtCPBO7Tbl7oPkv4xcZcR00e03bQdeeAI6i3ZAV9gV+wXieHPO1EXfWpH6sGn4CNE3o3Un6HxUGYcvIrYR5BXBh9K2d3CxA9/2UWkdwExUPdCcABj8BTtXoEdpfzu1G8mbQ0+xlHu1+BNxrAYfQ/pN1JmLPHu2wGQtxa/gu4HJlFmD9o4BHsevDN8G/genx3o/0Bi3II69bQ1CF9/6sIcbk91yp6gMdBOgPy/g+nk/5Hyb9C3p0F3fb9GuUc=
*/