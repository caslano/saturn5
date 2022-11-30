// Boost.Geometry

// Copyright (c) 2017-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_MULTI_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RELATE_MULTI_POINT_GEOMETRY_HPP


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/relate/result.hpp>
#include <boost/geometry/algorithms/detail/relate/topology_check.hpp>
#include <boost/geometry/algorithms/detail/within/point_in_geometry.hpp>
#include <boost/geometry/algorithms/envelope.hpp>

#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/index/rtree.hpp>

// TEMP
#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/envelope/spherical.hpp>

#include <boost/geometry/util/type_traits.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace relate
{

template
<
    typename Geometry,
    typename Tag = typename tag<Geometry>::type
>
struct multi_point_geometry_eb
{
    template <typename MultiPoint, typename Strategy>
    static inline bool apply(MultiPoint const& ,
                             detail::relate::topology_check<Geometry, Strategy> const& )
    {
        return true;
    }
};

template <typename Geometry>
struct multi_point_geometry_eb<Geometry, linestring_tag>
{
    template <typename Points>
    struct boundary_visitor
    {
        boundary_visitor(Points const& points)
            : m_points(points)
            , m_boundary_found(false)
        {}

        template <typename Point, typename Strategy>
        struct find_pred
        {
            find_pred(Point const& point, Strategy const& strategy)
                : m_point(point)
                , m_strategy(strategy)
            {}

            template <typename Pt>
            bool operator()(Pt const& pt) const
            {
                return detail::equals::equals_point_point(pt, m_point, m_strategy);
            }

            Point const& m_point;
            Strategy const& m_strategy;
        };

        template <typename Point, typename Strategy>
        bool apply(Point const& boundary_point, Strategy const& strategy)
        {
            if ( std::none_of(m_points.begin(), m_points.end(),
                              find_pred<Point, Strategy>(boundary_point, strategy)))
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

    template <typename MultiPoint, typename Strategy>
    static inline bool apply(MultiPoint const& multi_point,
                             detail::relate::topology_check<Geometry, Strategy> const& tc)
    {
        boundary_visitor<MultiPoint> visitor(multi_point);
        tc.for_each_boundary_point(visitor);
        return visitor.result();
    }
};

template <typename Geometry>
struct multi_point_geometry_eb<Geometry, multi_linestring_tag>
{
    template <typename Points>
    struct boundary_visitor
    {
        boundary_visitor(Points const& points)
            : m_points(points)
            , m_boundary_found(false)
        {}

        template <typename Point, typename Strategy>
        bool apply(Point const& boundary_point, Strategy const&)
        {
            typedef geometry::less<void, -1, typename Strategy::cs_tag> less_type;

            if (! std::binary_search(m_points.begin(), m_points.end(),
                                     boundary_point, less_type()) )
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

    template <typename MultiPoint, typename Strategy>
    static inline bool apply(MultiPoint const& multi_point,
                             detail::relate::topology_check<Geometry, Strategy> const& tc)
    {
        typedef typename boost::range_value<MultiPoint>::type point_type;
        typedef std::vector<point_type> points_type;
        typedef geometry::less<void, -1, typename Strategy::cs_tag> less_type;

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
        
        box2_type box2;
        geometry::envelope(single_geometry, box2, strategy);
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
            if (detail::disjoint::disjoint_point_box(*it, box2, strategy))
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

        typedef detail::relate::topology_check<SingleGeometry, Strategy> tc_t;

        if ( relate::may_update<exterior, interior, tc_t::interior, Transpose>(result)
          || relate::may_update<exterior, boundary, tc_t::boundary, Transpose>(result) )
        {
            tc_t tc(single_geometry, strategy);

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
                if (multi_point_geometry_eb<SingleGeometry>::apply(multi_point, tc))
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
    template <typename Strategy>
    struct expand_box_point
    {
        expand_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        inline void apply(Box& total, Point const& point) const
        {
            geometry::expand(total, point, m_strategy);
        }

    private:
        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct expand_box_box_pair
    {
        expand_box_box_pair(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename BoxPair>
        inline void apply(Box& total, BoxPair const& box_pair) const
        {
            geometry::expand(total, box_pair.first, m_strategy);
        }

    private:
        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_point
    {
        overlaps_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        inline bool apply(Box const& box, Point const& point) const
        {
            // The default strategy is enough for Point/Box
            return ! detail::disjoint::disjoint_point_box(point, box,
                                                          m_strategy);
        }

    private:
        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_box_pair
    {
        overlaps_box_box_pair(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename BoxPair>
        inline bool apply(Box const& box, BoxPair const& box_pair) const
        {
            // The default strategy is enough for Box/Box
            return ! detail::disjoint::disjoint_box_box(box_pair.first, box,
                                                        m_strategy);
        }

    private:
        Strategy const& m_strategy;
    };

    template <typename Result, typename Strategy>
    class item_visitor_type
    {
        typedef detail::relate::topology_check<MultiGeometry, Strategy> topology_check_type;

    public:
        item_visitor_type(MultiGeometry const& multi_geometry,
                          topology_check_type const& tc,
                          Result & result,
                          Strategy const& strategy)
            : m_multi_geometry(multi_geometry)
            , m_tc(tc)
            , m_result(result)
            , m_strategy(strategy)
        {}

        template <typename Point, typename BoxPair>
        inline bool apply(Point const& point, BoxPair const& box_pair)
        {
            // The default strategy is enough for Point/Box
            if (! detail::disjoint::disjoint_point_box(point, box_pair.first, m_strategy) )
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
        Strategy const& m_strategy;
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
                                    MultiGeometry, Strategy
                                > const& tc,
                             Result & result,
                             Strategy const& strategy)
    {
        item_visitor_type<Result, Strategy> visitor(multi_geometry, tc, result, strategy);

        geometry::partition
            <
                box1_type
            >::apply(multi_point, boxes, visitor,
                     expand_box_point<Strategy>(strategy),
                     overlaps_box_point<Strategy>(strategy),
                     expand_box_box_pair<Strategy>(strategy),
                     overlaps_box_box_pair<Strategy>(strategy));
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
                                    MultiGeometry, Strategy
                                > const& tc,
                             Result & result,
                             Strategy const& strategy)
    {
        typedef index::parameters
            <
                index::rstar<4>, Strategy
            > index_parameters_type;
        index::rtree<box_pair_type, index_parameters_type>
            rtree(boxes.begin(), boxes.end(),
                  index_parameters_type(index::rstar<4>(), strategy));

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

        std::size_t count2 = boost::size(multi_geometry);
        std::vector<box_pair_type> boxes(count2);
        for (std::size_t i = 0 ; i < count2 ; ++i)
        {
            geometry::envelope(range::at(multi_geometry, i), boxes[i].first, strategy);
            geometry::detail::expand_by_epsilon(boxes[i].first);
            boxes[i].second = i;
        }

        typedef detail::relate::topology_check<MultiGeometry, Strategy> tc_t;
        tc_t tc(multi_geometry, strategy);

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
                if (multi_point_geometry_eb<MultiGeometry>::apply(multi_point, tc))
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
    bool isMulti = util::is_multi<Geometry>::value
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