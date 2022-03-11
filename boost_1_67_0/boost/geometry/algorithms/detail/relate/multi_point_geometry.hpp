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
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
*/