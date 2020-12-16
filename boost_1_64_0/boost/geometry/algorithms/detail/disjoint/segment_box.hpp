// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP

#include <cstddef>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/algorithms/detail/assign_indexed_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/formulas/vertex_longitude.hpp>

#include <boost/geometry/geometries/box.hpp>

// Temporary, for envelope_segment_impl
#include <boost/geometry/strategies/spherical/envelope_segment.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{

template <typename CS_Tag>
struct disjoint_segment_box_sphere_or_spheroid
{
    struct disjoint_info
    {
        enum type
        {
            intersect,
            disjoint_no_vertex,
            disjoint_vertex
        };
        disjoint_info(type t) : m_(t){}
        operator type () const {return m_;}
        type m_;
    private :
        //prevent automatic conversion for any other built-in types
        template <typename T>
        operator T () const;
    };

    template
    <
        typename Segment, typename Box,
        typename AzimuthStrategy,
        typename NormalizeStrategy,
        typename DisjointPointBoxStrategy,
        typename DisjointBoxBoxStrategy
    >
    static inline bool apply(Segment const& segment,
                             Box const& box,
                             AzimuthStrategy const& azimuth_strategy,
                             NormalizeStrategy const& normalize_strategy,
                             DisjointPointBoxStrategy const& disjoint_point_box_strategy,
                             DisjointBoxBoxStrategy const& disjoint_box_box_strategy)
    {
        typedef typename point_type<Segment>::type segment_point;
        segment_point vertex;
        return apply(segment, box, vertex,
                     azimuth_strategy,
                     normalize_strategy,
                     disjoint_point_box_strategy,
                     disjoint_box_box_strategy) != disjoint_info::intersect;
    }

    template
    <
        typename Segment, typename Box,
        typename P,
        typename AzimuthStrategy,
        typename NormalizeStrategy,
        typename DisjointPointBoxStrategy,
        typename DisjointBoxBoxStrategy
    >
    static inline disjoint_info apply(Segment const& segment,
                                      Box const& box,
                                      P& vertex,
                                      AzimuthStrategy const& azimuth_strategy,
                                      NormalizeStrategy const& ,
                                      DisjointPointBoxStrategy const& disjoint_point_box_strategy,
                                      DisjointBoxBoxStrategy const& disjoint_box_box_strategy)
    {
        assert_dimension_equal<Segment, Box>();

        typedef typename point_type<Segment>::type segment_point_type;

        segment_point_type p0, p1;
        geometry::detail::assign_point_from_index<0>(segment, p0);
        geometry::detail::assign_point_from_index<1>(segment, p1);

        //vertex not computed here
        disjoint_info disjoint_return_value = disjoint_info::disjoint_no_vertex;

        // Simplest cases first

        // Case 1: if box contains one of segment's endpoints then they are not disjoint
        if ( ! disjoint_point_box(p0, box, disjoint_point_box_strategy)
          || ! disjoint_point_box(p1, box, disjoint_point_box_strategy) )
        {
            return disjoint_info::intersect;
        }

        // Case 2: disjoint if bounding boxes are disjoint

        typedef typename coordinate_type<segment_point_type>::type CT;

        segment_point_type p0_normalized;
        NormalizeStrategy::apply(p0, p0_normalized);
        segment_point_type p1_normalized;
        NormalizeStrategy::apply(p1, p1_normalized);

        CT lon1 = geometry::get_as_radian<0>(p0_normalized);
        CT lat1 = geometry::get_as_radian<1>(p0_normalized);
        CT lon2 = geometry::get_as_radian<0>(p1_normalized);
        CT lat2 = geometry::get_as_radian<1>(p1_normalized);

        if (lon1 > lon2)
        {
            std::swap(lon1, lon2);
            std::swap(lat1, lat2);
        }

        geometry::model::box<segment_point_type> box_seg;

        strategy::envelope::detail::envelope_segment_impl
            <
                CS_Tag
            >::template apply<geometry::radian>(lon1, lat1,
                                                lon2, lat2,
                                                box_seg,
                                                azimuth_strategy);

        if (disjoint_box_box(box, box_seg, disjoint_box_box_strategy))
        {
            return disjoint_return_value;
        }

        // Case 3: test intersection by comparing angles

        CT alp1, a_b0, a_b1, a_b2, a_b3;

        CT b_lon_min = geometry::get_as_radian<geometry::min_corner, 0>(box);
        CT b_lat_min = geometry::get_as_radian<geometry::min_corner, 1>(box);
        CT b_lon_max = geometry::get_as_radian<geometry::max_corner, 0>(box);
        CT b_lat_max = geometry::get_as_radian<geometry::max_corner, 1>(box);

        azimuth_strategy.apply(lon1, lat1, lon2, lat2, alp1);
        azimuth_strategy.apply(lon1, lat1, b_lon_min, b_lat_min, a_b0);
        azimuth_strategy.apply(lon1, lat1, b_lon_max, b_lat_min, a_b1);
        azimuth_strategy.apply(lon1, lat1, b_lon_min, b_lat_max, a_b2);
        azimuth_strategy.apply(lon1, lat1, b_lon_max, b_lat_max, a_b3);

        bool b0 = formula::azimuth_side_value(alp1, a_b0) > 0;
        bool b1 = formula::azimuth_side_value(alp1, a_b1) > 0;
        bool b2 = formula::azimuth_side_value(alp1, a_b2) > 0;
        bool b3 = formula::azimuth_side_value(alp1, a_b3) > 0;

        if (!(b0 && b1 && b2 && b3) && (b0 || b1 || b2 || b3))
        {
            return disjoint_info::intersect;
        }

        // Case 4: The only intersection case not covered above is when all four
        // points of the box are above (below) the segment in northern (southern)
        // hemisphere. Then we have to compute the vertex of the segment

        CT vertex_lat;
        CT lat_sum = lat1 + lat2;

        if ((lat1 < b_lat_min && lat_sum > CT(0))
                || (lat1 > b_lat_max && lat_sum < CT(0)))
        {
            CT b_lat_below; //latitude of box closest to equator

            if (lat_sum > CT(0))
            {
                vertex_lat = geometry::get_as_radian<geometry::max_corner, 1>(box_seg);
                b_lat_below = b_lat_min;
            } else {
                vertex_lat = geometry::get_as_radian<geometry::min_corner, 1>(box_seg);
                b_lat_below = b_lat_max;
            }

            //optimization TODO: computing the spherical longitude should suffice for
            // the majority of cases
            CT vertex_lon = geometry::formula::vertex_longitude<CT, CS_Tag>
                                    ::apply(lon1, lat1,
                                            lon2, lat2,
                                            vertex_lat,
                                            alp1,
                                            azimuth_strategy);

            geometry::set_from_radian<0>(vertex, vertex_lon);
            geometry::set_from_radian<1>(vertex, vertex_lat);
            disjoint_return_value = disjoint_info::disjoint_vertex; //vertex_computed

            // Check if the vertex point is within the band defined by the
            // minimum and maximum longitude of the box; if yes, then return
            // false if the point is above the min latitude of the box; return
            // true in all other cases
            if (vertex_lon >= b_lon_min && vertex_lon <= b_lon_max
                    && std::abs(vertex_lat) > std::abs(b_lat_below))
            {
                return disjoint_info::intersect;
            }
        }

        return disjoint_return_value;
    }
};

struct disjoint_segment_box
{
    template <typename Segment, typename Box, typename Strategy>
    static inline bool apply(Segment const& segment,
                             Box const& box,
                             Strategy const& strategy)
    {
        return strategy.apply(segment, box);
    }
};

}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Segment, typename Box, std::size_t DimensionCount>
struct disjoint<Segment, Box, DimensionCount, segment_tag, box_tag, false>
        : detail::disjoint::disjoint_segment_box
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_SEGMENT_BOX_HPP

/* segment_box.hpp
TazpFZR3NeRNgguqhXnUxSbD4HsyN4xyf8xnxq6fzPUHWPGx2iWX8+rF9iXDCza/pah7h+RX+8fEgx4ieSabduaHLexvzgetjVVK3M9y2Jz1hxNeNwdcsGch66BwsdP9CU4jrj5Q6/vJTZrrO4Xpck3pOHDlAtpS6+E4uL0NPy5k05X6L9p0pg56pNZ0AZiT/VoYshXWJvYSfyqObxNzeORxdeZJ31llXNkryTVawADXPoFT1xtmH1kx2MWfQx4yN58V/UmNKyLfXoBBvX2e2EdIvzjaDHbrPSrRuB8+M6FrG/emRH8u32HIwFL0bfg27ggNa4w+uCUet02cj1O3n/eX5p1vgbHLszuMefel/K6WPaVnLnWXOrnbOsF3sJkOfmwE3vAMLfxyMduUXVP5TlxcLw4XwvUX2+iLaW8rxMKyBeJMfC9We95dBkfash/se+Y8dWMQTWCYnoLumgXX7cd/X9P+nsqlntjzWJuGmtRMDdqJt5ln3TMTezDUZdgwgM6XrDfbxJZtgvx5hU7cFxeWM1/IhQbyOWkCPamfXk69vP04DgeLb/2D/ruP79S1VkHP6gpLu8Ci6V1PPl/y6xnGPw6/rqgmD6GpwccRq+FQYzFWU63n01zdaNz0kfijajJsimXFL4rKuWZieRG+Uc98aAlV5PPD+O8Rvf2urvoEvUAvuHCf3L2JLw6mWVO6VZwl44xvq8+NaWdwtSw/f1GXRpVH7dfvNJuHS8CsBvDoBJvvvDek6+bXtoF3cD+PPE4xr/o/8u1DrveAOt1fXVP/Gm1wzcSaXVH5e5RO08p66mD2S3V/ZhFccKRz3KNuBTxvCS7yru/Tpi7uiUeXprvs1Rd+iEPnx0fYsdVx2hrbZBvPtmeLS/7a25LP4Myug/bbRXoq+F54OQ5mX8qZPwaxyo4wJktCr9iNZ+u5FsDjV/TyvXfAuctDGLIfRtYJ9q67F4Bm8/1uuNuG9ppHjS6EW4ulqny04Unr9bngzdn6vC/VevWtHSxZkxP3OoQ/deD7xcacTYzP1z8dFW9j5Dlc65yCj/9Kgx9EG7UXrDU8z1sWPzlPbsHKR9g6Z317THLBNDn16iTx+wjM3EtPXpnYm2wfawN4pEaVlTPF8KXx6mEJ3x/YCK8fqJ+fql/kw7q/Gr/13kylxZs9FSVy001hRlHH1qP196hO551Pm8xHD3Cuu1+FsWc4xr6bSy9n20ZqViv5Wltu9dJbs8OkGjhmT3sxmpt7inlUFrOvyKV34nQaObyVP8R0Gh1h+TBY4PPDYj1/dPI9PtkuhVul/VzWtVP1UWrZ+Y57bLbrlQr2arDnO4Gua1wt9JJiaoLaeaSxuqhPa/ugvmw4Lroonn4/zE+j7Ql7BeZVo5nA9ctb+b5eJBX3Gsv+1Saor3hv/l+CdSiYKyce9dmZ1pxHZPHZaNeph9Mk+39u8XArvQn297gwcR+dOOWjg0k0Ddj1zFIabE1YltCP9Qkd5ekldOZ8asn6qvgVfM6jXrS3plu5N52V3fsQnWpUoSXu0YumioWVeg764PCp7Coe75GPdWDmiebOM935Ax7MJtvKJPbo2Q9pbkflWWDz0fBmptgYqFcegh+UOwsuXAsXbsbHp9EMt0fp9/kNLmsMlQJ/q0fivmBbOPmkWHsE9uuLHhM77yd0PD3Ks031t/jAELVxrrEswQf30y22wooWDWFAY7g2Xk7TQjO3tf9CDc5UgJ5BOzzf3FvSSl/ik3MK4wXyqclGHGouPDHHjiNO3od92294ydtisj9M5vs0PhhOc1gqRqe310fQtNrO5MM/wJoL9Zk/sYPzvq82Ta2lz9mjxiTDS73bMH3UIOvjZ5hb4j4=
*/