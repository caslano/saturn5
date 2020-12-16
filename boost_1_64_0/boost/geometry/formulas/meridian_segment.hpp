// Boost.Geometry

// Copyright (c) 2017-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_FORMULAS_MERIDIAN_SEGMENT_HPP
#define BOOST_GEOMETRY_FORMULAS_MERIDIAN_SEGMENT_HPP

#include <boost/math/constants/constants.hpp>

#include <boost/geometry/core/radius.hpp>

#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>

namespace boost { namespace geometry { namespace formula
{

/*!
\brief Test if a segment is meridian or not.
*/

class meridian_segment
{

public :

    enum SegmentType {NonMeridian, MeridianCrossingPole, MeridianNotCrossingPole};

    template <typename T>
    static inline SegmentType is_meridian(T lon1, T lat1, T lon2, T lat2)
    {
        SegmentType res = NonMeridian;
        T diff = geometry::math::longitude_distance_signed<geometry::radian>(lon1, lon2);

        if ( meridian_not_crossing_pole(lat1, lat2, diff) )
        {
            res = MeridianNotCrossingPole;
        }
        else if ( meridian_crossing_pole(diff) )
        {
            res = MeridianCrossingPole;
        }
        return res;
    }

    template <typename T>
    static bool meridian_not_crossing_pole(T lat1, T lat2, T diff)
    {
        T half_pi = math::half_pi<T>();
        return math::equals(diff, T(0)) ||
               (math::equals(lat2, half_pi) && math::equals(lat1, -half_pi));
    }

    template <typename T>
    static bool meridian_crossing_pole(T diff)
    {
        return math::equals(math::abs(diff), math::pi<T>());
    }

};

}}} // namespace boost::geometry::formula

#endif //BOOST_GEOMETRY_FORMULAS_MERIDIAN_SEGMENT_HPP

/* meridian_segment.hpp
jvF3kDDtOn7N+qcFIi+24pjwB7GJHGP9gWHDJAMzZi6Yb/V2PBDs6krqC9lPfk8+2S4j0sOynyJ4VqHkfQLG3drE2e8zpnKe+hFlhkX1ahvOi6IEG/pTYs61rcGla6hTRJ+2E3jGuROPu70ig5WLcJfE+T0e4Q0Kzud3HG80cPMcqSkny9+iIr/cBm/a/4rlN03hwDJMZ7qBGRtHUc8MAzfNldAGj8FlnhPNzMn2N7V4Pz/L4LPuC0XbmhW5sN7VL+4RWww8+1zGa8gMNpfh9rQaslnf6aA9bVJOlDrm6w4K3k3PjHwcy/aOBfO4XcpgleC3WDwP/QZnmbMQP5vztvcu4hlTB+f/1HsR5tscQ9783YC5HM/2PgRl5nGZbO9CUP98ISPfg6AfOwrcPj/BPOo0ePs8ZCeDk/OQnQU2yDwkIGTs8xC0dRcTL+fZQY5ne3+CMl12GZZGUseWxWVCdhnx/A/08DoZHkwGdfH80aWczDlKp1vlkgkqF97LCJmeQWTgjQ6m0StkTOM+z8uI4OzvNpDfVfD29xqY1wsEL99pIB4VuDG28/T6BJ7lmw8xwdvmBLzOxAXPx3hMK8ExmX/Uh+zGcXu+LIqke43ZEy+HJMmqw5GwKUWcbagim9KcNz1f7OeY5Z0J17dQcPZ3Lsgvysjj+I/8AOft70eoTiw285YkuMzudhmZDOXJHlLGdr++Z2aOUqB341xmsPcqqGvvzHIkwWX2kTL2eyUqhyUkAwVtzPv3JWxRMJJmxQbTOP5cgeLsZ/CghrD9Oca/q0bt9ADAbJ/HI/kDOWf6PspBDLN/Hg9tOhg4/tk5y4fsqO0cInlTWz1U4hn1Hmbw4zPqPVzyJr1HSNysl3w/UvBmrajzKMEJkOIcLXBDo4xzDHDh8RH1a3WIHwt4ZHxYxY2/e/Ay/t2Dg07o6Lhsz80Kfz1tZvOv36/3ruYEJzjBCU5wghOc4AQnOMEJTviXh3w4uvj3/1flZ/s7ge2E51jsmU91vGtXbQr8LQFtF/Z3AMvobwiUZfxbAq0JePsd2R0eEVQ2wut5ePKQhG8RNpfcCh9Zn6gVo50n5HDbr4VjQziWwfE9uy89Nh9epy+xfmYd0tm2ZHSxBhx7fu/C5+61KHusthn8uxZgM3NE/I3getuSw4pZCslYGL+F2FRSiffu8/G7/9eDFcvho/Cvwvm2cmZDafEumbO3EUQg/Sn4rdvWHJZWCX6zcnQxu2b2lKDuw/Cap5cLKU4hX3tzuSL2XnhtOA+F80/wQfgvydd2fKVhWj6H9g8vYf7iR7QNn3OPY3F+14YaPgs9pfCcbj7+LYGTwI73hw12cH8rM/vbAMmiTzVwHl7CfAIbLD79Qj7tRZH21LhPbcdbfJLL/qw+kf0izl5ok7YSm4oy2LQt2fRcHhceCcearKzhOH0DyB9hU+al/FnsEvFGIp9XyHiQJ36WwZdD3ZiPf5diRCnP1zF/MV8ZVg9nSAMwSIP8mkl+3UQf7xxBfpXBcSb4VXkC+bXyLQhZfBQ6RiB/SynyXZrw0eDLDB/X/4c+QhqAQRqWsjulwF52y8DHNuFj5q0T2evUCbzsSoFPYNmJKOQbyqya8isn3xJYfiIds38DhXb/cirgb5AK/zJv+8jq3xLFv7TGeBGFy7A6smQV+5fG/k+kY/avbbXM5XdVRv+MFwZZ/GPxqO0Z5cfEZdldtYp8KzWVHUvD3Pbqiuxt7xzwa7nwa+XbbLL6uFxteyX2trd8Vbe9EnPb85KPI1a3+3ge+Fh8Ivn457YHZfGT6ZF+7lVs8RP5VesnpKH6acw53l3dOg7zOcf2hp+mMTjjnMN3onX8ZfFX/fi7FvNPzjE=
*/