// Boost.Geometry

// Copyright (c) 2016-2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP
#define BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP


#include <boost/geometry/strategies/tags.hpp>


#include <boost/mpl/assert.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace intersection
{

namespace services
{

/*!
\brief Traits class binding a segments intersection strategy to a coordinate system
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

}} // namespace strategy::intersection

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SEGMENT_INTERSECTION_HPP

/* intersection.hpp
6xycXNF8DimkmBqJ1u0QukUXbj50fol+mGiGFf2C5skFE+gQLKk42jY5KGcz6QFnMycHkdn0QcC0SZu0SZu0SZu0SZu0SZu0SZu0SZv/U+NJm7RJm7RJm7RJm7T5nE2WV35bK7PqLfpdUeTBb94o+d1xEn6NKRoj9qovym9RSIUv4d9kU129EL8jRsyi/5dXzVtELsNPHHHiiKL5s+hx1sULLp9NvyPmpM7fUd2Fbrfe8ju7p/yu6CW/x6nfr3aT32wVr/JSKU+ustcn2K0+Ev6Xin4nFTcyRex7+PdzTH9gO+n/nhWrejmC51OZOQsXkE7g4PwFixZUV86ba7+feYuvmLfY5X7w9zX3xNkLF1w8Yk4Hwn2l+hIT7uzpMyKzSyaffeLI4tlfmjr77HDJibOLi8jjIP6jRib5l5RyoNkc6tQvTfW05z/ypDHi36HyVC+uqWqn/SVV/BDVDvJ6yO+4fvL7ZJ78dj1Kfs9W7aFI/UaU/7kD5PflPuq9q99z+srvamW/QqUzTcW/eaD8Nv2LvSuNjesn4m83aRtKgRYobThfC4UWSElb/lD+0NI0SUkgTUOSQrm0bHZfmqWb3WXfbpsiJCrEfV8fAHGUAhISICGEEJeglPu+71OID3zhkkDcx/g3tp/97Le7acKpuN147fGMx/Z4PB77vb0Hx3+X9dxdwj8o6U9J+u3dcp7ecwDx7yX+HyW/v5Zy29enmzbw/9i+fB9PH9Gk/8X2/eYenduXS9rX/7/Yvkan9t3E/Dv039a+dZ5//2vtW+38+29r33rPv/+29q3X/Du0479Uv6zT/PtfbV+v8++/tX3rNf/+W9vXbf794+92+07I/A9JOl9Y5fr+hkF/+14i9zUtSXeb5C+8x8217x27JH5lS8f2/e3vyfz7X2zf1S7t+8c/xF8O/5ftW6V8Hvova996y+d/W/u6jt8q5fN/rn09ymev68O/u33d5DPI/X+3r9f599/avq7y2eP8+19t30bYCBvh/zdk+tUbT29H7aj7OUEzKtWbZREVqsXLUbNQPmT64veVpX9/biosVqNmK6y1lxfoxELCi3FMmZV6LVwsVqpR+dawGtXCRxwLCeFIYXa+cHrkXGFmamRyujA1Pv2o+QlFOBN/GPnNqFgOl+hP1EzSC/XyZaRkulyvRTLdrl2o1S/V8H12gj4n6TO2mnbHRw6WeuhXxhNfjxQW2ouLURNoKjxkleHJqwyrlgOTX/5u8fuo8XkM5cyZOXyZoCOcUKTPcv7omenpcbMe+vdk+bceNIIoqAUx/asGQ8EhyhWf4WCRoMiluEllSkGd4rLOPRIUrPyD9M0fKsFyUCRoIYjp+zMIJwyOB8fo7zB97kv/Qm+ZR6DMePC4YIbyTwcjwTnEY/R3LpgMnkgwhK7yuFwsFeLKMyIh1OOPm4FAnx4rzE0+cbwjXi08fiwczoa3usBpsIaO15uV84VqBFrLZfDRld9yD+xmy0t8pFBaKEFG/PTLxVax0Ki244LoGXxpFMvlSu28rDc8NHz4weH9EfXSv2XRwPOtJc22YHliZG6icHJyvjB65uz0fOHkE+bH53ocr3JhoVovXfCQmzoz+hj0RE90xLhHpWbUkvwJWoJmfXH/EgFFqw9YNEboc/IkzZnR0Y79G9U69e8y8kenpuf5XPVxs2YdP70b23VVaec9DPYilZf25Dulvbkky91H4r32BVuQ7pfpq6l08R6mnYsA2Guk/XnL3XuzJ6fPTk0NnR67xUrTabJK8xFzkjM2MT40Njc35MufnRtx8kfGJuy8hC4dOvvoIt+li3yHrs5L808Ak3+do3GQdtuTYNr1u3Av39n4fjja4dJGvhc=
*/