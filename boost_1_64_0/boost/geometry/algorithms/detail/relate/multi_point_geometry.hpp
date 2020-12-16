// Boost.Geometry

// Copyright (c) 2017-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_MULTI_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_MULTI_POINT_GEOMETRY_HPP


#include <boost/range.hpp>

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/algorithms/detail/relate/topology_check.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/core/is_areal.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate
{

template
<
    typename Geometry,
    typename EqPPStrategy,
    typename Tag = typename tag<Geometry>::type
>
struct multi_point_geometry_eb
{
    template <typename MultiPoint>
    static inline bool apply(MultiPoint const& ,
                             detail::relate::topology_check<Geometry, EqPPStrategy> const& )
    {
        return true;
    }
};

template <typename Geometry, typename EqPPStrategy>
struct multi_point_geometry_eb<Geometry, EqPPStrategy, linestring_tag>
{
    template <typename Points>
    struct boundary_visitor
    {
        boundary_visitor(Points const& points)
            : m_points(points)
            , m_boundary_found(false)
        {}

        template <typename Point>
        struct find_pred
        {
            find_pred(Point const& point)
                : m_point(point)
            {}

            template <typename Pt>
            bool operator()(Pt const& pt) const
            {
                return detail::equals::equals_point_point(pt, m_point, EqPPStrategy());
            }

            Point const& m_point;
        };

        template <typename Point>
        bool apply(Point const& boundary_point)
        {
            if (std::find_if(m_points.begin(), m_points.end(), find_pred<Point>(boundary_point)) == m_points.end())
            {
                m_boundary_found = true;
                return false;
            }
            return true;
        }

        bool result() const { return m_boundary_found; }

    private:
        Points const& m_points;
        bool m_boundary_found;
    };

    template <typename MultiPoint>
    static inline bool apply(MultiPoint const& multi_point,
                             detail::relate::topology_check<Geometry, EqPPStrategy> const& tc)
    {
        boundary_visitor<MultiPoint> visitor(multi_point);
        tc.for_each_boundary_point(visitor);
        return visitor.result();
    }
};

template <typename Geometry, typename EqPPStrategy>
struct multi_point_geometry_eb<Geometry, EqPPStrategy, multi_linestring_tag>
{
    // TODO: CS-specific less compare strategy derived from EqPPStrategy
    typedef geometry::less<void, -1, typename EqPPStrategy::cs_tag> less_type;

    template <typename Points>
    struct boundary_visitor
    {
        boundary_visitor(Points const& points)
            : m_points(points)
            , m_boundary_found(false)
        {}

        template <typename Point>
        bool apply(Point const& boundary_point)
        {
            if (! std::binary_search(m_points.begin(), m_points.end(), boundary_point, less_type()))
            {
                m_boundary_found = true;
                return false;
            }
            return true;
        }

        bool result() const { return m_boundary_found; }

    private:
        Points const& m_points;
        bool m_boundary_found;
    };

    template <typename MultiPoint>
    static inline bool apply(MultiPoint const& multi_point,
                             detail::relate::topology_check<Geometry, EqPPStrategy> const& tc)
    {
        typedef typename boost::range_value<MultiPoint>::type point_type;
        typedef std::vector<point_type> points_type;
        points_type points(boost::begin(multi_point), boost::end(multi_point));
        std::sort(points.begin(), points.end(), less_type());

        boundary_visitor<points_type> visitor(points);
        tc.for_each_boundary_point(visitor);
        return visitor.result();
    }
};

// SingleGeometry - Linear or Areal
template <typename MultiPoint, typename SingleGeometry, bool Transpose = false>
struct multi_point_single_geometry
{
    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(MultiPoint const& multi_point,
                             SingleGeometry const& single_geometry,
                             Result & result,
                             Strategy const& strategy)
    {
        typedef typename point_type<SingleGeometry>::type point2_type;
        typedef model::box<point2_type> box2_type;
        typedef typename Strategy::equals_point_point_strategy_type eq_pp_strategy_type;
        typedef typename Strategy::disjoint_point_box_strategy_type d_pb_strategy_type;
        
        box2_type box2;
        geometry::envelope(single_geometry, box2, strategy.get_envelope_strategy());
        geometry::detail::expand_by_epsilon(box2);

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            if (! (relate::may_update<interior, interior, '0', Transpose>(result)
                || relate::may_update<interior, boundary, '0', Transpose>(result)
                || relate::may_update<interior, exterior, '0', Transpose>(result) ) )
            {
                break;
            }

            // The default strategy is enough for Point/Box
            if (detail::disjoint::disjoint_point_box(*it, box2, d_pb_strategy_type()))
            {
                relate::set<interior, exterior, '0', Transpose>(result);
            }
            else
            {
                int in_val = detail::within::point_in_geometry(*it, single_geometry, strategy);

                if (in_val > 0) // within
                {
                    relate::set<interior, interior, '0', Transpose>(result);
                }
                else if (in_val == 0)
                {
                    relate::set<interior, boundary, '0', Transpose>(result);
                }
                else // in_val < 0 - not within
                {
                    relate::set<interior, exterior, '0', Transpose>(result);
                }
            }

            if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            {
                return;
            }
        }

        typedef detail::relate::topology_check
            <
                SingleGeometry, eq_pp_strategy_type
            > tc_t;
        if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
          || relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result) )
        {
            tc_t tc(single_geometry);

            if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
              && tc.has_interior() )
            {
                // TODO: this is not true if a linestring is degenerated to a point
                // then the interior has topological dimension = 0, not 1
                relate::set<exterior, interior, tc_t::interior, Transpose>(result);
            }

            if ( relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result)
              && tc.has_boundary() )
            {
                if (multi_point_geometry_eb
                        <
                            SingleGeometry, eq_pp_strategy_type
                        >::apply(multi_point, tc))
                {
                    relate::set<exterior, boundary, tc_t::boundary, Transpose>(result);
                }
            }
        }

        relate::set<exterior, exterior, result_dimension<MultiPoint>::value, Transpose>(result);
    }
};


// MultiGeometry - Linear or Areal
// part of the algorithm calculating II and IB when no IE has to be calculated
// using partition()
template <typename MultiPoint, typename MultiGeometry, bool Transpose>
class multi_point_multi_geometry_ii_ib
{
    template <typename ExpandPointStrategy>
    struct expand_box_point
    {
        template <typename Box, typename Point>
        static inline void apply(Box& total, Point const& point)
        {
            geometry::expand(total, point, ExpandPointStrategy());
        }
    };

    template <typename ExpandBoxStrategy>
    struct expand_box_box_pair
    {
        template <typename Box, typename BoxPair>
        static inline void apply(Box& total, BoxPair const& box_pair)
        {
            geometry::expand(total, box_pair.first, ExpandBoxStrategy());
        }
    };

    template <typename DisjointPointBoxStrategy>
    struct overlaps_box_point
    {
        template <typename Box, typename Point>
        static inline bool apply(Box const& box, Point const& point)
        {
            // The default strategy is enough for Point/Box
            return ! detail::disjoint::disjoint_point_box(point, box,
                                                          DisjointPointBoxStrategy());
        }
    };

    template <typename DisjointBoxBoxStrategy>
    struct overlaps_box_box_pair
    {
        template <typename Box, typename BoxPair>
        static inline bool apply(Box const& box, BoxPair const& box_pair)
        {
            // The default strategy is enough for Box/Box
            return ! detail::disjoint::disjoint_box_box(box_pair.first, box,
                                                        DisjointBoxBoxStrategy());
        }
    };

    template <typename Result, typename PtSegStrategy>
    class item_visitor_type
    {
        typedef typename PtSegStrategy::equals_point_point_strategy_type pp_strategy_type;
        typedef typename PtSegStrategy::disjoint_point_box_strategy_type d_pp_strategy_type;
        typedef detail::relate::topology_check<MultiGeometry, pp_strategy_type> topology_check_type;

    public:
        item_visitor_type(MultiGeometry const& multi_geometry,
                          topology_check_type const& tc,
                          Result & result,
                          PtSegStrategy const& strategy)
            : m_multi_geometry(multi_geometry)
            , m_tc(tc)
            , m_result(result)
            , m_strategy(strategy)
        {}

        template <typename Point, typename BoxPair>
        inline bool apply(Point const& point, BoxPair const& box_pair)
        {
            // The default strategy is enough for Point/Box
            if (! detail::disjoint::disjoint_point_box(point, box_pair.first, d_pp_strategy_type()))
            {
                typename boost::range_value<MultiGeometry>::type const&
                    single = range::at(m_multi_geometry, box_pair.second);

                int in_val = detail::within::point_in_geometry(point, single, m_strategy);

                if (in_val > 0) // within
                {
                    relate::set<interior, interior, '0', Transpose>(m_result);
                }
                else if (in_val == 0)
                {
                    if (m_tc.check_boundary_point(point))
                        relate::set<interior, boundary, '0', Transpose>(m_result);
                    else
                        relate::set<interior, interior, '0', Transpose>(m_result);
                }
            }

            if ( BOOST_GEOMETRY_CONDITION(m_result.interrupt) )
            {
                return false;
            }

            if (! (relate::may_update<interior, interior, '0', Transpose>(m_result)
                || relate::may_update<interior, boundary, '0', Transpose>(m_result) ) )
            {
                return false;
            }

            return true;
        }


    private:
        MultiGeometry const& m_multi_geometry;
        topology_check_type const& m_tc;
        Result & m_result;
        PtSegStrategy const& m_strategy;
    };

public:
    typedef typename point_type<MultiPoint>::type point1_type;
    typedef typename point_type<MultiGeometry>::type point2_type;
    typedef model::box<point1_type> box1_type;
    typedef model::box<point2_type> box2_type;
    typedef std::pair<box2_type, std::size_t> box_pair_type;

    template <typename Result, typename Strategy>
    static inline void apply(MultiPoint const& multi_point,
                             MultiGeometry const& multi_geometry,
                             std::vector<box_pair_type> const& boxes,
                             detail::relate::topology_check
                                <
                                    MultiGeometry,
                                    typename Strategy::equals_point_point_strategy_type
                                > const& tc,
                             Result & result,
                             Strategy const& strategy)
    {
        item_visitor_type<Result, Strategy> visitor(multi_geometry, tc, result, strategy);

        typedef expand_box_point
            <
                typename Strategy::expand_point_strategy_type
            > expand_box_point_type;
        typedef overlaps_box_point
            <
                typename Strategy::disjoint_point_box_strategy_type
            > overlaps_box_point_type;
        typedef expand_box_box_pair
            <
                typename Strategy::envelope_strategy_type::box_expand_strategy_type
            > expand_box_box_pair_type;
        typedef overlaps_box_box_pair
            <
                typename Strategy::disjoint_box_box_strategy_type
            > overlaps_box_box_pair_type;

        geometry::partition
            <
                box1_type
            >::apply(multi_point, boxes, visitor,
                     expand_box_point_type(),
                     overlaps_box_point_type(),
                     expand_box_box_pair_type(),
                     overlaps_box_box_pair_type());
    }

};

// MultiGeometry - Linear or Areal
// part of the algorithm calculating II, IB and IE
// using rtree
template <typename MultiPoint, typename MultiGeometry, bool Transpose>
struct multi_point_multi_geometry_ii_ib_ie
{
    typedef typename point_type<MultiPoint>::type point1_type;
    typedef typename point_type<MultiGeometry>::type point2_type;
    typedef model::box<point1_type> box1_type;
    typedef model::box<point2_type> box2_type;
    typedef std::pair<box2_type, std::size_t> box_pair_type;
    typedef std::vector<box_pair_type> boxes_type;
    typedef typename boxes_type::const_iterator boxes_iterator;

    template <typename Result, typename Strategy>
    static inline void apply(MultiPoint const& multi_point,
                             MultiGeometry const& multi_geometry,
                             std::vector<box_pair_type> const& boxes,
                             detail::relate::topology_check
                                <
                                    MultiGeometry,
                                    typename Strategy::equals_point_point_strategy_type
                                > const& tc,
                             Result & result,
                             Strategy const& strategy)
    {
        typedef strategy::index::services::from_strategy
            <
                Strategy
            > index_strategy_from;
        typedef index::parameters
            <
                index::rstar<4>, typename index_strategy_from::type
            > index_parameters_type;
        index::rtree<box_pair_type, index_parameters_type>
            rtree(boxes.begin(), boxes.end(),
                  index_parameters_type(index::rstar<4>(), index_strategy_from::get(strategy)));

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            if (! (relate::may_update<interior, interior, '0', Transpose>(result)
                || relate::may_update<interior, boundary, '0', Transpose>(result)
                || relate::may_update<interior, exterior, '0', Transpose>(result) ) )
            {
                return;
            }

            typename boost::range_value<MultiPoint>::type const& point = *it;

            boxes_type boxes_found;
            rtree.query(index::intersects(point), std::back_inserter(boxes_found));

            bool found_ii_or_ib = false;
            for (boxes_iterator bi = boxes_found.begin() ; bi != boxes_found.end() ; ++bi)
            {
                typename boost::range_value<MultiGeometry>::type const&
                    single = range::at(multi_geometry, bi->second);

                int in_val = detail::within::point_in_geometry(point, single, strategy);

                if (in_val > 0) // within
                {
                    relate::set<interior, interior, '0', Transpose>(result);
                    found_ii_or_ib = true;
                }
                else if (in_val == 0) // on boundary of single
                {
                    if (tc.check_boundary_point(point))
                        relate::set<interior, boundary, '0', Transpose>(result);
                    else
                        relate::set<interior, interior, '0', Transpose>(result);
                    found_ii_or_ib = true;
                }
            }

            // neither interior nor boundary found -> exterior
            if (found_ii_or_ib == false)
            {
                relate::set<interior, exterior, '0', Transpose>(result);
            }

            if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
            {
                return;
            }
        }
    }
};

// MultiGeometry - Linear or Areal
template <typename MultiPoint, typename MultiGeometry, bool Transpose = false>
struct multi_point_multi_geometry
{
    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(MultiPoint const& multi_point,
                             MultiGeometry const& multi_geometry,
                             Result & result,
                             Strategy const& strategy)
    {
        typedef typename point_type<MultiGeometry>::type point2_type;
        typedef model::box<point2_type> box2_type;
        typedef std::pair<box2_type, std::size_t> box_pair_type;

        typedef typename Strategy::equals_point_point_strategy_type eq_pp_strategy_type;

        typename Strategy::envelope_strategy_type const
            envelope_strategy = strategy.get_envelope_strategy();
        
        std::size_t count2 = boost::size(multi_geometry);
        std::vector<box_pair_type> boxes(count2);
        for (std::size_t i = 0 ; i < count2 ; ++i)
        {
            geometry::envelope(range::at(multi_geometry, i), boxes[i].first, envelope_strategy);
            geometry::detail::expand_by_epsilon(boxes[i].first);
            boxes[i].second = i;
        }

        typedef detail::relate::topology_check<MultiGeometry, eq_pp_strategy_type> tc_t;
        tc_t tc(multi_geometry);

        if ( relate::may_update<interior, interior, '0', Transpose>(result)
          || relate::may_update<interior, boundary, '0', Transpose>(result)
          || relate::may_update<interior, exterior, '0', Transpose>(result) )
        {
            // If there is no need to calculate IE, use partition
            if (! relate::may_update<interior, exterior, '0', Transpose>(result) )
            {
                multi_point_multi_geometry_ii_ib<MultiPoint, MultiGeometry, Transpose>
                    ::apply(multi_point, multi_geometry, boxes, tc, result, strategy);
            }
            else // otherwise use rtree
            {
                multi_point_multi_geometry_ii_ib_ie<MultiPoint, MultiGeometry, Transpose>
                    ::apply(multi_point, multi_geometry, boxes, tc, result, strategy);
            }
        }

        if ( BOOST_GEOMETRY_CONDITION(result.interrupt) )
        {
            return;
        }

        if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
          || relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result) )
        {
            if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
              && tc.has_interior() )
            {
                // TODO: this is not true if a linestring is degenerated to a point
                // then the interior has topological dimension = 0, not 1
                relate::set<exterior, interior, tc_t::interior, Transpose>(result);
            }

            if ( relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result)
              && tc.has_boundary() )
            {
                if (multi_point_geometry_eb
                        <
                            MultiGeometry, eq_pp_strategy_type
                        >::apply(multi_point, tc))
                {
                    relate::set<exterior, boundary, tc_t::boundary, Transpose>(result);
                }
            }
        }

        relate::set<exterior, exterior, result_dimension<MultiPoint>::value, Transpose>(result);
    }

};


template
<
    typename MultiPoint, typename Geometry,
    bool Transpose = false,
    bool isMulti = boost::is_same
                    <
                        typename tag_cast
                            <
                                typename tag<Geometry>::type, multi_tag
                            >::type,
                            multi_tag
                    >::value
>
struct multi_point_geometry
    : multi_point_single_geometry<MultiPoint, Geometry, Transpose>
{};

template <typename MultiPoint, typename Geometry, bool Transpose>
struct multi_point_geometry<MultiPoint, Geometry, Transpose, true>
    : multi_point_multi_geometry<MultiPoint, Geometry, Transpose>
{};


// transposed result of multi_point_geometry
template <typename Geometry, typename MultiPoint>
struct geometry_multi_point
{
    static const bool interruption_enabled = true;

    template <typename Result, typename Strategy>
    static inline void apply(Geometry const& geometry, MultiPoint const& multi_point,
                             Result & result, Strategy const& strategy)
    {
        multi_point_geometry<MultiPoint, Geometry, true>::apply(multi_point, geometry, result, strategy);
    }
};

}} // namespace detail::relate
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_MULTI_POINT_GEOMETRY_HPP

/* multi_point_geometry.hpp
wcfpGzAG8MsU/M0K/hjAxzYUXJ43903EhlTsJSq2i8I2c95oxU9ix1dO2ScqxUSV4nWnxDdT4CtWsf1V7ONOiS+pQ3z8zA/7yRR7NZni5wpfksDXVeHbrGIvFjfIvCbhk1HPpwW5KuBagQVP9gANeIprjXsV+FiA2/JYpoKHSiyK9rEOscBiS36Rgjsk58tGldyvgj/URHJFCLlEJgeAH5pAgMUYruBIqezTw7x74PtuH+q1V6hSFMiviSMsdPQ5ggXsXwrgTYcEWCBxZIlLEqlq7BeEJsyTCmY6/OF1Uh/ZlX68gc1owI07vYJJQtHM8x6FYbnb6CS7hXyrOle+dvUQSBHBD6FCYeRaKyuoEGUypjvYN6lcGSFTEOLTHcZ4VYKX2aK8Aoh/6WT1IQMVyEMSpNoG4lcgB2OaAFkusztZBb8mghdejaAJKmiDDPqJrq8WRLwHNOKkG0Be0QcaBf+lhPOqy23uZxkJ3UWwVCuT3pYftlDC9oor4bPxoCoijm/Llfq/82sn7238WTYhKcasfZpg4Svao9mlngztJcl0mKLmSRsL362AY7UnCkVDNyZ7seBru9DIBYykXzDmlpuiD4wvEMgU31D+wdejl7lkZvyjmsSigUIr5SqPCFcSXPfK/vgJ1n8jo1X27V/KsPe5JyC33EEZvEjKtd6bvyBv3iB9AyBezRAQnB/7jjF2CriFP5Qz9tuIf1hhWCdjvPkLkuYNOn8F4Qe6uZbI9MbdMv7IWEPBgqS5OxCzr5eMqZAxSp2d007C8x2ZIL6sPqtj8rcoAK46SbnUXVEted3tcwNpdkJg+MqZjlCX8JV+R0jpUgWKBPjyNvDlgEcqrWN4Kr9T18zdTFWU+uLdBPzK/i26wjlnWkSJJP0ome+ftQ0kiWJNyT7DbSzfoxF7hzoWCz6b2wQ6nPkyjMu9q14CRZYRgSjwN2uGBu+pDhY+7g9IfyL90xmi0CDOFCQ1E+PCTPZ6/a1oneBYpRUwXO0Wa9IIzNjCMTh8ZR7UcaFdKGQ93JIR6iHrFXXcpeM6TqQvb/CWEybi9UdAdu+9uL4j+i9ZPiXccxXWu3j7zq5PxIe+oHluRIbqe/12GlX6+f3MVFgzMxKbFuT2STHgjJVIvJGTE/oP0zvj6es7ov/xnlZdzkLPmKF6woPsUWBs9kWkOg4hrnyPrX+t3s1QxLKGLd1p/gAFQvnyf5IH7arREdfOpBKOIUVTaB3/doDW2PdxBdJ8BGK3nyxii08WsU+dImKvhQ/pzw12a6jYzQVP0JH85Fy+Cs6Q+kj0yafimj4Pdzaepe8jGvc2WP09lZSNp0+b4Y29qjdGimaI+GmaiPdU/lYjnotOba7zC6nzNyp591XcGOzxznYDRdATiC7F55IP5DQUspNx5Qy5o5glaXyCh3vV0vpcjZbJN/+L8kKdarR07PNe0U2Uz8VeZposubVaIcP0alIheWOvFLR4llEOJothyz7UB9SaPaPTk4T4m4MxkS1vXBuKTsV/O/C+/AQWlfAfqWJy02JtBvlCTnIFZi6/it48X+Q+1CtK8hJcLLDeyKQVcIkae0nWaDCFtdW0Ak/fKIHoP0UzXLCarkGQ0JCgXy9KM362O+hmKS6ZqijQmvNrnCZZ0MzJrTHr7WuhfH9/Lh1vX+Wm9tgrP9aAW3R5rImWXmHqrVNPX7rsZRhI5d6zQL1D7PxukcGBSbYM8mQGF9oy+Mzoiwya72xTgU1+TBE2RCOMh4AIaUciLVGBz5A4LO1PggVq8181R9PpsX9rdSvf+Rend7aJQvrBqeblTHEuaDW8OgQMfRrr5b42yRF+PkZZg+EFfnSf2egjnunbuN2YET29E2k=
*/