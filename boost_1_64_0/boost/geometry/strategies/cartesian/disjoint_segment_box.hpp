// Boost.Geometry

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP


#include <cstddef>
#include <utility>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/calculation_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>

#include <boost/geometry/strategies/cartesian/point_in_box.hpp>
#include <boost/geometry/strategies/disjoint.hpp>


namespace boost { namespace geometry { namespace strategy { namespace disjoint
{

namespace detail
{

template <std::size_t I>
struct compute_tmin_tmax_per_dim
{
    template <typename SegmentPoint, typename Box, typename RelativeDistance>
    static inline void apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box,
                             RelativeDistance& ti_min,
                             RelativeDistance& ti_max,
                             RelativeDistance& diff)
    {
        typedef typename coordinate_type<Box>::type box_coordinate_type;
        typedef typename coordinate_type
            <
                SegmentPoint
            >::type point_coordinate_type;

        RelativeDistance c_p0 = boost::numeric_cast
            <
                point_coordinate_type
            >( geometry::get<I>(p0) );

        RelativeDistance c_p1 = boost::numeric_cast
            <
                point_coordinate_type
            >( geometry::get<I>(p1) );

        RelativeDistance c_b_min = boost::numeric_cast
            <
                box_coordinate_type
            >( geometry::get<geometry::min_corner, I>(box) );

        RelativeDistance c_b_max = boost::numeric_cast
            <
                box_coordinate_type
            >( geometry::get<geometry::max_corner, I>(box) );

        if ( geometry::get<I>(p1) >= geometry::get<I>(p0) )
        {
            diff = c_p1 - c_p0;
            ti_min = c_b_min - c_p0;
            ti_max = c_b_max - c_p0;
        }
        else
        {
            diff = c_p0 - c_p1;
            ti_min = c_p0 - c_b_max;
            ti_max = c_p0 - c_b_min;
        }
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t I,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
{
    template <typename RelativeDistancePair>
    static inline bool apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box,
                             RelativeDistancePair& t_min,
                             RelativeDistancePair& t_max)
    {
        RelativeDistance ti_min, ti_max, diff;

        compute_tmin_tmax_per_dim<I>::apply(p0, p1, box, ti_min, ti_max, diff);

        if ( geometry::math::equals(diff, 0) )
        {
            if ( (geometry::math::equals(t_min.second, 0)
                  && t_min.first > ti_max)
                 ||
                 (geometry::math::equals(t_max.second, 0)
                  && t_max.first < ti_min)
                 ||
                 (math::sign(ti_min) * math::sign(ti_max) > 0) )
            {
                return true;
            }
        }

        RelativeDistance t_min_x_diff = t_min.first * diff;
        RelativeDistance t_max_x_diff = t_max.first * diff;

        if ( t_min_x_diff > ti_max * t_min.second
             || t_max_x_diff < ti_min * t_max.second )
        {
            return true;
        }

        if ( ti_min * t_min.second > t_min_x_diff )
        {
            t_min.first = ti_min;
            t_min.second = diff;
        }
        if ( ti_max * t_max.second < t_max_x_diff )
        {
            t_max.first = ti_max;
            t_max.second = diff;
        }

        if ( t_min.first > t_min.second || t_max.first < 0 )
        {
            return true;
        }

        return disjoint_segment_box_impl
            <
                RelativeDistance,
                SegmentPoint,
                Box, 
                I + 1,
                Dimension
            >::apply(p0, p1, box, t_min, t_max);
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
    <
        RelativeDistance, SegmentPoint, Box, 0, Dimension
    >
{
    static inline bool apply(SegmentPoint const& p0,
                             SegmentPoint const& p1,
                             Box const& box)
    {
        std::pair<RelativeDistance, RelativeDistance> t_min, t_max;
        RelativeDistance diff;

        compute_tmin_tmax_per_dim<0>::apply(p0, p1, box,
                                            t_min.first, t_max.first, diff);

        if ( geometry::math::equals(diff, 0) )
        {
            if ( geometry::math::equals(t_min.first, 0) ) { t_min.first = -1; }
            if ( geometry::math::equals(t_max.first, 0) ) { t_max.first = 1; }

            if (math::sign(t_min.first) * math::sign(t_max.first) > 0)
            {
                return true;
            }
        }

        if ( t_min.first > diff || t_max.first < 0 )
        {
            return true;
        }

        t_min.second = t_max.second = diff;

        return disjoint_segment_box_impl
            <
                RelativeDistance, SegmentPoint, Box, 1, Dimension
            >::apply(p0, p1, box, t_min, t_max);
    }
};


template
<
    typename RelativeDistance,
    typename SegmentPoint,
    typename Box,
    std::size_t Dimension
>
struct disjoint_segment_box_impl
    <
        RelativeDistance, SegmentPoint, Box, Dimension, Dimension
    >
{
    template <typename RelativeDistancePair>
    static inline bool apply(SegmentPoint const&, SegmentPoint const&,
                             Box const&,
                             RelativeDistancePair&, RelativeDistancePair&)
    {
        return false;
    }
};

} // namespace detail

// NOTE: This may be temporary place for this or corresponding strategy
// It seems to be more appropriate to implement the opposite of it
// e.g. intersection::segment_box because in disjoint() algorithm
// other strategies that are used are intersection and covered_by strategies.
struct segment_box
{
    typedef covered_by::cartesian_point_box disjoint_point_box_strategy_type;

    static inline disjoint_point_box_strategy_type get_disjoint_point_box_strategy()
    {
        return disjoint_point_box_strategy_type();
    }

    template <typename Segment, typename Box>
    static inline bool apply(Segment const& segment, Box const& box)
    {
        assert_dimension_equal<Segment, Box>();

        typedef typename util::calculation_type::geometric::binary
            <
                Segment, Box, void
            >::type relative_distance_type;

        typedef typename point_type<Segment>::type segment_point_type;
        segment_point_type p0, p1;
        geometry::detail::assign_point_from_index<0>(segment, p0);
        geometry::detail::assign_point_from_index<1>(segment, p1);

        return detail::disjoint_segment_box_impl
            <
                relative_distance_type, segment_point_type, Box,
                0, dimension<Box>::value
            >::apply(p0, p1, box);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Linear, typename Box, typename LinearTag>
struct default_strategy<Linear, Box, LinearTag, box_tag, 1, 2, cartesian_tag, cartesian_tag>
{
    typedef disjoint::segment_box type;
};

template <typename Box, typename Linear, typename LinearTag>
struct default_strategy<Box, Linear, box_tag, LinearTag, 2, 1, cartesian_tag, cartesian_tag>
{
    typedef disjoint::segment_box type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}}}} // namespace boost::geometry::strategy::disjoint


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_DISJOINT_SEGMENT_BOX_HPP

/* disjoint_segment_box.hpp
l2Ee827/vTevGW5juLaUt+T1bCnXXkfk2kvtc089bD8fuPzG3YQG2cpU3xerxF3ead7nEA31vLIv+vrYRej5Zboxu7zjxNw/PeoPsg3NvrmFdM4194nAcZxR2NdIi9ks7eKz9bJkKyUzJy3dW+6DvPnyf9diAWXo8n8OJO0U1jEI88xC9jte9AqZ9c5zRvqZknfrPprDfDJOIY20SXMZ06c/4LtGL/bmKTedtHzvwbQ8n7OOFX1Qlt0dbr/m3Sz7zWi554oz78Uf9e43vgO6DNe8Tvdap1S8wSV9G7z83yR3/qZ3yd8Md/7Wd0nf1i7/N8Cdvz1e8re+nb+tXfI3wJ2/5V7yN8b7hKrpL76d/MWD2U2O/3rb5piDLZ88yXnImL796OTmd6U+VPX6avuC6p954GniMcqn8qkGP+SMybzyYNW2N3tuXVKz5G99O3+DvfzfJP9vfTPc+ZvnJX8j3fkb+CV/+9352/jl/wb+4qpq+saFkdcM7TTyRJvFQd++Mu/1Zrq/UarL/GaKHisXxT8uxSSX/u0LchU3wjexM76FWfg3zMH3cAm+j6vxAN6NB3EzHkIzncR3S07nF50OK6fTCUaVTmVU6YSiSudSVOlURZVOdVTp1ECVjlHHvqfTiZV0LsEYSWcUq1sLR2MEJqDxHjrshmNxEI5Dtcx4l+8b5sUS7yiJ1/oN843kvzZuwmG42fJt9iOy3FhZzvot9dHyLfUE7IljMErNi8NV+hiPSSj5ML+94arpkI9B8i31aKyBgy3598hyDRyW6y3L9cH66u+yHPG41shys2Q5NV9PWS7dpfOfIUOG3VKOM3GGsYyvHMIOmNslsBy2sn4qX/djO/w9dsJt2B8fQpWXhy3l6pH4hhvxXfw3+fcfsG6ni/smf6pLvg2B6xz29z/K/v60HFfP4BTchdPxeczH3XgtvoCr8EW8Fff40uFgKzmdTyWdzySdLySdrySdE5LOt5LOSUnnlKRz2lLeuw+WXN7rpbzvlvLeIOW9Ucp7s5T3vZbyjjhUcnlfI/sVeTLKu9ily/s6JH2uY3R5X2/55v4aie9pic/6zf0i2X7zsbcxrkfnZyEm4GK8UqWLbpUuZuMSvF2lixtxKW5R6eIfcDnuwBss5STfJHANc1ivj6ScPsY2eFTK6xNU8/wTBxtjCS31h8Q3yiG+y2W9ImT7Nsdu2DJIx9Na6qM2lvzJNwFc4xziu0LiGyTxRUt8Q1AtG4OjMRbN+na7xJfpUN/eLOu7GtviLdgRb5Vu1be59H64FtPxDku9I+/kd412qHc8sn/MkXonX+qdQjSek1jqvc0STy2Heq+j1HudsCZ2tqS/W5Zb7pD+Wqmv7pDyWYepeJecD9cHWerdf/iOm8hge/r/rOUqNsaO4hB1nKJaTp3T9styP8py4UY56V+vmvr81Rv7YB+cqPKJV2JfLMR+uBj740ocgLfiQNyktjc+oLY3PqXWG5/DwbgPh+A7OBSPYgyexlg8KXWOvPed98HrfIbx71WSzwjJZ3OMwhZotL/hcFUOOA5b4zRsI/lui4uwHa7B9qjS6oCPY0dUx3knfBs74xfYFUNVPtDc31M/9tUz0ZXs+/sBlz5vf4CN8KDUW4cwFg9LPfOhy1ff7pf4Jsl2sda31wTr/eJabIHF2AmXYC+8Dq/ApcFSj2EiLsdxeAOqdOa75F3p+KSkUx2zJZ0xNfX+n4jGdQuqeMfheByPKq9JWIQTsBgn4nUq73g7JuM9OBkfw6lSbvtd8k50TJftqtZrj6R/XxD1lpy3+8h5ehA+iMPkfD1WztfJ+Aim4KM4Ex/Dq/EPcp24PUin/3iQ3g+fwBfVuuOruAMP4FM=
*/