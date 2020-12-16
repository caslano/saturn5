// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018, 2019.
// Modifications copyright (c) 2018, 2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_FRANKLIN_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_FRANKLIN_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace within
{

/*!
\brief Within detection using cross counting
\ingroup strategies
\tparam Point \tparam_point
\tparam PointOfSegment \tparam_segment_point
\tparam CalculationType \tparam_calculation
\author adapted from Randolph Franklin algorithm
\author Barend and Maarten, 1995
\author Revised for templatized library, Barend Gehrels, 2007
\return true if point is in ring, works for closed rings in both directions
\note Does NOT work correctly for point ON border

\qbk{
[heading See also]
[link geometry.reference.algorithms.within.within_3_with_strategy within (with strategy)]
}
 */

template
<
    typename Point_,                   // for backward compatibility
    typename PointOfSegment_ = Point_, // for backward compatibility
    typename CalculationType = void
>
class franklin
{
    template <typename Point, typename PointOfSegment>
    struct calculation_type
        : select_calculation_type
            <
                Point,
                PointOfSegment,
                CalculationType
            >
    {};

    /*! subclass to keep state */
    class crossings
    {
        bool crosses;

    public :

        friend class franklin;
        inline crossings()
            : crosses(false)
        {}
    };

public :

    typedef crossings state_type;

    template <typename Point, typename PointOfSegment>
    static inline bool apply(Point const& point,
            PointOfSegment const& seg1, PointOfSegment const& seg2,
            crossings& state)
    {
        typedef typename calculation_type<Point, PointOfSegment>::type calc_t;

        calc_t const& px = get<0>(point);
        calc_t const& py = get<1>(point);
        calc_t const& x1 = get<0>(seg1);
        calc_t const& y1 = get<1>(seg1);
        calc_t const& x2 = get<0>(seg2);
        calc_t const& y2 = get<1>(seg2);

        if (
            ( (y2 <= py && py < y1) || (y1 <= py && py < y2) )
            && (px < (x1 - x2) * (py - y2) / (y1 - y2) + x2)
            )
        {
            state.crosses = ! state.crosses;
        }
        return true;
    }

    static inline int result(crossings const& state)
    {
        return state.crosses ? 1 : -1;
    }
};



}} // namespace strategy::within





}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_POINT_IN_POLY_FRANKLIN_HPP

/* point_in_poly_franklin.hpp
5LX4tKPTt88+fairu16MrasJL8XW1ZYZ93IUDt+1h/eZl9Ef/uWYepKa3G1ASv8+qeH0OTEho7FI+TvawmO3Zzh+xG63zP2+pAXzdzH9/TOnS85+H0vPY+7/iA+dz24L7WEvTlMf5y7JcR1j2sFJv/DZYET4bJDzeXXseUfktblU5zOWM4dz7bCOOdT3ocdZ38tGyzfsR9ETt8ie1Cu1d2Y/6ibR9+l2o02Z/vEu2/E6NXS8+zIcG3dweuTcdnm2MuuTeGNiZq3IbEZ+8Xwk5z7NWduDUCdyqCe1c6gnFbP2Ew77cSvbPcl6bPdz4RVH9+MqOZ0zm76kaftJU79rE6bPfj+xMgo5Wr8ahzPQF6SiPC8zIueKr2Upq5RjzqX/7jbfPDL7zRePOa87eo7Q8a98Xuh6zLrHHjcaFwv3Hoa6myQzI+cOK//munTpMyD1uM/RYu67zWF9auewPvWz7ktdBgzun3kulPN6xv/Kz0UZ67/V/9MN9X4LZ5k+btXR9Y9+2M6+NY//HDXrvUFVs9StnJcvtr1OKh7O7XIpK04P99V2XRNdvl+8gek4Pitk2zdD3/jM5Yy5PjEt9MF/Xptans/yuUjdXxeWJ/ZGkl+8TyZy78Cq6N9W6dYrehNDjvfOxN4/Eu5lir2fJrZ+hHPoLOuX8/0i4Vwk5tid2j8p+qdh38q+jaLH2DvWx957M++NjJ9j69idp0RX+A2fMc/hAs7xfhXfjCmzLKdnCTHlt/kXjknLwjEpUpa/fzf2PozIa5e9GX1Ngz0w496brdnKd1dk2mxl2fyYfeqYc6vMY9xH6cfsIX2SE+NyKN/oa62yt9k5t1vhPCdzO5rv0etLnYvGbIdwfMvhPp9wTJihvrZV/hP8/OQ7R9v4rlnrdziHevfN2HOoyu/Ebt+4dzN+//97P/5/78d//70fM0tFXt/e8Ppce1+8/YIjqwf0+6rMm5//ffd+FM0VrruH6/Fp2Z6X8EmWPs7X80sO5le8hbt5J/fyee7nizzAyt7jW1bhdxzEHzmGh/kH/sTlPMIN/Jk7GZc3Oh50HhbI7Ueexnysy/xswRPYlQWZzJM4iUX4MkvyLZ7C91iK21iaO1iWua13OZ7A8kwvlzyZ1+5d04+WS5fIYoXr/EnhHpUUVuCNrMUhbMBh7M+bOYS38EHeyh0cye94B2uayV2sz1HsyNHsxHvYnWP4GMfxJd7PpXyAq/kg/8iH+CUfDn1zHmVRPs5KnMbfcBZbcjb78DnewAW8k2mcy8V8nS9zN1/hQb7Kn/kaT1cmK3kWV/F8ruZFXMs2XMd+XM8xfJ3juIGPcBNn8Y98ke9xDd/nFn7APfyE33Erj3AHC0Se98Iz+AU7cC8f4T5O5bfcwEP8jN/zIH/gER5m/nzqIwvwCIvzZ5ZkXKTvJ3PzDBbg9SzI0SzCOSzGdSzJXSzDvPnVMyazHJezPPNFnjvKFFbgSJ7Oe1iRY1iJj7Iyp/FMvsqzuI7ncBur8Rv+hv0izxvlrazN8azLR3geF/J8vs963M4LeJAXs4D63oSF2ZRF2IzRe4TC9yZslcM9QvdGxlvmGNbhOF7I+9iC9zOjr1dSeJ+xuY7t6zXFdKX5FM/hVF7Cp/l7PsMtnM46/v4PHMUZzLyn7dnQxzwsZ9Z70xbnsX9wFUtyNTOffxr+7qHwd1mff3p96AvehWXZleXZjWezO89nApuxJ69nLw5jb45nH4bnFGR8Z2AbmF+25xQ0NN0p/C0r8MIwn0aszYvZio3Znk14LZuxO5vzNl7CUbyUk9mCz7AVX+AVXMy2oX1qxz28kpFjwVUsx/Y8nR1Zg51Yl9eG9YmPC98V8KJQfvmjyx0=
*/