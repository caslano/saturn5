// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP

#include <boost/array.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/strategies/within.hpp>


namespace boost { namespace geometry { namespace strategy
{

namespace within
{

struct decide_within
{
    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = false;
            return false;
        }
        return true; // continue
    }
};

struct decide_covered_by
{
    static inline bool apply(int side, bool& result)
    {
        if (side != 1)
        {
            result = side >= 0;
            return false;
        }
        return true; // continue
    }
};


// WARNING
// This strategy is not suitable for boxes in non-cartesian CSes having edges
// longer than 180deg because e.g. the SSF formula picks the side of the closer
// longitude, so for long edges the side is the opposite.
template <typename Decide = decide_within>
struct point_in_box_by_side
{
    template <typename Point, typename Box>
    static inline bool apply(Point const& point, Box const& box)
    {
        typedef typename strategy::side::services::default_strategy
            <
                typename cs_tag<Box>::type
            >::type side_strategy_type;

        // Create (counterclockwise) array of points, the fifth one closes it
        // Every point should be on the LEFT side (=1), or ON the border (=0),
        // So >= 1 or >= 0
        boost::array<typename point_type<Box>::type, 5> bp;
        geometry::detail::assign_box_corners_oriented<true>(box, bp);
        bp[4] = bp[0];

        bool result = true;
        side_strategy_type strategy;
        boost::ignore_unused(strategy);

        for (int i = 1; i < 5; i++)
        {
            int const side = strategy.apply(point, bp[i - 1], bp[i]);
            if (! Decide::apply(side, result))
            {
                return result;
            }
        }

        return result;
    }
};


} // namespace within


}}} // namespace boost::geometry::strategy


#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_POINT_IN_BOX_BY_SIDE_HPP

/* point_in_box_by_side.hpp
SA391WMN7jOFmLUMfMDpjM9A5hc+9izGHDt2Nv0Aw/UYPCcoI0HbQYwtvEMtMWMXwa9OZzz1eDyXve48jl+NBw7MoC+UicJ/Ox9fpEcvYK2BrqSHLwzKtaAbdiP8GVipbc0MyjUXMXdqX8y+egl905hnBeXjOtbPQOpeGZQzwDTserjPVRz7Wgb+bjbzovbVHLPXMHfaL3jXa5k/7Rf84RzGX+3rWLPXM54aG7wYzB7I+MPt5jKvOm7wn+cxj2rfwHEEytUnvNdNjNsgYoDzb2GsBjH+8PG3MobaL/jN25gX7Pjt9HUB86Ll4WsWMneDiHMRxyLoOpgxvJsxAbPUD7zFPfQLOwKfD+ZpXTjvXuLUdPi+BsZN7T+w/4BF6vOPQbkCfDOIOO/jOLqfccCWPwWlH5ivZeBLHyA+naMHmV/QVmN4KCing/u1LnzWw+ybpMcfZe39hXHQtv7KHgKeHMTahk9qZDx1bSiD0GC99g7KR2CZzvXjjBtYo/2CS59gfgex9uD+T7GWKC9/Y/2Dmdj18HOgB3Yz3OlpriWwo/Cx4JDBxA9fArppefg50FvLw1suYV6wI/B+z3Cux66FbwbTNAb4RVAziPLw1s8yp9ov+DowlPKN8D5NzOlg/ZyFY205xwt2+HX27bc5n2pb77DOm0nXPsKPgDrSW+D4e+ylWv79oNz2IXuvjslHzC9YPJgY4FWgQcusoPwnnDfV/hT7M66p1P6cNf8N60P7+B3H6Sr2c+07fNdqjiXt1/f4Bi3aLhz9gT1F/cP9f+RcczhzB98Euh9OOvwOKDyc8nDnNRwD2BH4CRDGLuIPa0eBfC3PH7kGQyGJYpfmheSgrUMS0fS2IRnQLiQx9Q8/BQqwm+HANiFZofHDr/JHz0XaFn/c3I8/sO5eTMzwU6CwmPLw7vxhc34x7cJXgIJi/MPFHamLHYfzO9EWdhSeApbjsw5+DaxQ//CB/AH2auwYfDNYgt0It+EPrYW6EXgcCGsM8EsgUkxdeAR/vNtE+Vp4S/7wuBk7Cr8OWrDD/PHxKaBR24U778iYaMzwFWCEjgn8Ligcwlh1DcldO9HfIXotGpJBIKrp8KxfhaRW+w4/GQnJTGzZhf6BOdpf+PDdQjK1mPjhO/hD5riWhyO/CUmdloFb9gxJaTGx9cAHf5xcqf3ij5oXggXad/hdMEfHB+4SDUm99gs+FjTonMIXgcXY9fBjUXxiN8E/grj2vWdIDgaVOrbwGFCr8w7PBXXad/gNMFPbgrv0In5tC/5Lb+Z0COX3D8mkA2h3CLHBpxQyv0NoC77vIOZR5wJ+4mDmUcf2kJDsyR9tzxiCf/iWIsYOO9IvJBMHh2S21j08JJ2GEtsQvcfIeMZCMk3LHxuS4ccxDtoWfOpw5hSf9fBlJzEOxXoNEJLqUsZR2ypjjVWwBnQuRofkzDGMNXWb4Umnst50/YzDfxVrQNfheMom6IuO+aSQHDCNNTaE+M8Kyf7TGU+dl3NZCxey3kivmxmSTy5mTWr5S0LS62pi03iuDUnFPNbPEOwbQnL9zYy/2rdw7NzKMaD9mo+PO1gf2l/447toW/u4MCRP309bQ2jrgZCcDCJHMM7wmsXEg137IOPzEH3DLoKnPBySoUfgB97mEcYIOwJ/8Cj1sUv/EpKtH2d+seWJkFwDlugYwt2eDUkV6Y3PhWTyUuZIY4D3bQrJ+xrDiyH54aWQlGu7L4dkv2WMla55+BUQVZ+vMA+vclxoW6/R1j9YG1oe3uct+qnxvB2Sle8xdtj1H4Sk7Uchma/9gj9YEZJF2LGPQ9L/k5D0OJK68PPgftKb4Rs/ZW1oH+EVK0OyFDv6GWv4c+LUtuA=
*/