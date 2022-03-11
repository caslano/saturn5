// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2019, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIPOINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIPOINT_GEOMETRY_HPP

#include <algorithm>
#include <vector>

#include <boost/range.hpp>
#include <boost/mpl/assert.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/algorithms/detail/check_iterator_range.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/multirange_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

#include <boost/geometry/policies/compare.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


class multipoint_multipoint
{
private:
    template <typename Iterator, typename CSTag>
    class unary_disjoint_predicate
        : geometry::less<void, -1, CSTag>
    {
    private:
        typedef geometry::less<void, -1, CSTag> base_type;

    public:
        unary_disjoint_predicate(Iterator first, Iterator last)
            : base_type(), m_first(first), m_last(last)
        {}

        template <typename Point>
        inline bool apply(Point const& point) const
        {
            return !std::binary_search(m_first,
                                       m_last,
                                       point,
                                       static_cast<base_type const&>(*this));
        }

    private:
        Iterator m_first, m_last;
    };

public:
    template <typename MultiPoint1, typename MultiPoint2, typename Strategy>
    static inline bool apply(MultiPoint1 const& multipoint1,
                             MultiPoint2 const& multipoint2,
                             Strategy const&)
    {
        typedef typename Strategy::cs_tag cs_tag;
        typedef geometry::less<void, -1, cs_tag> less_type;

        BOOST_GEOMETRY_ASSERT( boost::size(multipoint1) <= boost::size(multipoint2) );

        typedef typename boost::range_value<MultiPoint1>::type point1_type;

        std::vector<point1_type> points1(boost::begin(multipoint1),
                                         boost::end(multipoint1));

        std::sort(points1.begin(), points1.end(), less_type());

        typedef unary_disjoint_predicate
            <
                typename std::vector<point1_type>::const_iterator,
                cs_tag
            > predicate_type;

        return check_iterator_range
            <
                predicate_type
            >::apply(boost::begin(multipoint2),
                     boost::end(multipoint2),
                     predicate_type(points1.begin(), points1.end()));
    }
};


template <typename MultiPoint, typename Linear>
class multipoint_linear
{
private:
    template <typename ExpandPointBoxStrategy>
    struct expand_box_point
    {
        template <typename Box, typename Point>
        static inline void apply(Box& total, Point const& point)
        {
            geometry::expand(total, point, ExpandPointBoxStrategy());
        }
    };

    template <typename EnvelopeStrategy>
    struct expand_box_segment
    {
        explicit expand_box_segment(EnvelopeStrategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Segment>
        inline void apply(Box& total, Segment const& segment) const
        {
            geometry::expand(total,
                             geometry::return_envelope<Box>(segment, m_strategy),
                             typename EnvelopeStrategy::box_expand_strategy_type());
        }

        EnvelopeStrategy const& m_strategy;
    };

    template <typename DisjointPointBoxStrategy>
    struct overlaps_box_point
    {
        template <typename Box, typename Point>
        static inline bool apply(Box const& box, Point const& point)
        {
            // The default strategy is enough in this case
            return ! detail::disjoint::disjoint_point_box(point, box,
                DisjointPointBoxStrategy());
        }
    };

    template <typename DisjointStrategy>
    struct overlaps_box_segment
    {
        explicit overlaps_box_segment(DisjointStrategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Segment>
        inline bool apply(Box const& box, Segment const& segment) const
        {
            return ! dispatch::disjoint<Segment, Box>::apply(segment, box, m_strategy);
        }

        DisjointStrategy const& m_strategy;
    };

    template <typename PtSegStrategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(PtSegStrategy const& strategy)
            : m_intersection_found(false)
            , m_strategy(strategy)
        {}

        template <typename Item1, typename Item2>
        inline bool apply(Item1 const& item1, Item2 const& item2)
        {
            if (! m_intersection_found
                && ! dispatch::disjoint<Item1, Item2>::apply(item1, item2, m_strategy))
            {
                m_intersection_found = true;
                return false;
            }
            return true;
        }

        inline bool intersection_found() const { return m_intersection_found; }

    private:
        bool m_intersection_found;
        PtSegStrategy const& m_strategy;
    };
    // structs for partition -- end

    class segment_range
    {
    public:
        typedef geometry::segment_iterator<Linear const> const_iterator;
        typedef const_iterator iterator;

        segment_range(Linear const& linear)
            : m_linear(linear)
        {}

        const_iterator begin() const
        {
            return geometry::segments_begin(m_linear);
        }

        const_iterator end() const
        {
            return geometry::segments_end(m_linear);
        }

    private:
        Linear const& m_linear;
    };

public:
    template <typename Strategy>
    static inline bool apply(MultiPoint const& multipoint, Linear const& linear, Strategy const& strategy)
    {
        item_visitor_type<Strategy> visitor(strategy);

        typedef typename Strategy::expand_point_strategy_type expand_point_strategy_type;
        typedef typename Strategy::envelope_strategy_type envelope_strategy_type;
        typedef typename Strategy::disjoint_strategy_type disjoint_strategy_type;
        typedef typename Strategy::disjoint_point_box_strategy_type disjoint_pb_strategy_type;

        // TODO: disjoint Segment/Box may be called in partition multiple times
        // possibly for non-cartesian segments which could be slow. We should consider
        // passing a range of bounding boxes of segments after calculating them once.
        // Alternatively instead of a range of segments a range of Segment/Envelope pairs
        // should be passed, where envelope would be lazily calculated when needed the first time
        geometry::partition
            <
                geometry::model::box<typename point_type<MultiPoint>::type>
            >::apply(multipoint, segment_range(linear), visitor,
                     expand_box_point<expand_point_strategy_type>(),
                     overlaps_box_point<disjoint_pb_strategy_type>(),
                     expand_box_segment<envelope_strategy_type>(strategy.get_envelope_strategy()),
                     overlaps_box_segment<disjoint_strategy_type>(strategy.get_disjoint_strategy()));

        return ! visitor.intersection_found();
    }

    template <typename Strategy>
    static inline bool apply(Linear const& linear, MultiPoint const& multipoint, Strategy const& strategy)
    {
        return apply(multipoint, linear, strategy);
    }
};


template <typename MultiPoint, typename SingleGeometry>
class multi_point_single_geometry
{
public:
    template <typename Strategy>
    static inline bool apply(MultiPoint const& multi_point,
                             SingleGeometry const& single_geometry,
                             Strategy const& strategy)
    {
        typedef typename Strategy::disjoint_point_box_strategy_type d_pb_strategy_type;

        typedef typename point_type<MultiPoint>::type point1_type;
        typedef typename point_type<SingleGeometry>::type point2_type;
        typedef model::box<point2_type> box2_type;
        
        box2_type box2;
        geometry::envelope(single_geometry, box2, strategy.get_envelope_strategy());
        geometry::detail::expand_by_epsilon(box2);

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            // The default strategy is enough for Point/Box
            if (! detail::disjoint::disjoint_point_box(*it, box2, d_pb_strategy_type())
                && ! dispatch::disjoint<point1_type, SingleGeometry>::apply(*it, single_geometry, strategy))
            {
                return false;
            }
        }

        return true;
    }

    template <typename Strategy>
    static inline bool apply(SingleGeometry const& single_geometry, MultiPoint const& multi_point, Strategy const& strategy)
    {
        return apply(multi_point, single_geometry, strategy);
    }
};


template <typename MultiPoint, typename MultiGeometry>
class multi_point_multi_geometry
{
private:
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
        inline void apply(Box& total, BoxPair const& box_pair) const
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
        inline bool apply(Box const& box, BoxPair const& box_pair) const
        {
            // The default strategy is enough for Box/Box
            return ! detail::disjoint::disjoint_box_box(box_pair.first, box,
                                                        DisjointBoxBoxStrategy());
        }
    };

    template <typename PtSegStrategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(MultiGeometry const& multi_geometry,
                          PtSegStrategy const& strategy)
            : m_intersection_found(false)
            , m_multi_geometry(multi_geometry)
            , m_strategy(strategy)
        {}

        template <typename Point, typename BoxPair>
        inline bool apply(Point const& point, BoxPair const& box_pair)
        {
            typedef typename PtSegStrategy::disjoint_point_box_strategy_type d_pb_strategy_type;

            typedef typename boost::range_value<MultiGeometry>::type single_type;

            // The default strategy is enough for Point/Box
            if (! m_intersection_found
                && ! detail::disjoint::disjoint_point_box(point, box_pair.first, d_pb_strategy_type())
                && ! dispatch::disjoint<Point, single_type>::apply(point, range::at(m_multi_geometry, box_pair.second), m_strategy))
            {
                m_intersection_found = true;
                return false;
            }
            return true;
        }

        inline bool intersection_found() const { return m_intersection_found; }

    private:
        bool m_intersection_found;
        MultiGeometry const& m_multi_geometry;
        PtSegStrategy const& m_strategy;
    };
    // structs for partition -- end

public:
    template <typename Strategy>
    static inline bool apply(MultiPoint const& multi_point, MultiGeometry const& multi_geometry, Strategy const& strategy)
    {
        typedef typename point_type<MultiPoint>::type point1_type;
        typedef typename point_type<MultiGeometry>::type point2_type;
        typedef model::box<point1_type> box1_type;
        typedef model::box<point2_type> box2_type;
        typedef std::pair<box2_type, std::size_t> box_pair_type;

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

        item_visitor_type<Strategy> visitor(multi_geometry, strategy);

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

        return ! visitor.intersection_found();
    }

    template <typename Strategy>
    static inline bool apply(MultiGeometry const& multi_geometry, MultiPoint const& multi_point, Strategy const& strategy)
    {
        return apply(multi_point, multi_geometry, strategy);
    }
};


template <typename MultiPoint, typename Areal, typename Tag = typename tag<Areal>::type>
struct multipoint_areal
    : multi_point_single_geometry<MultiPoint, Areal>
{};

template <typename MultiPoint, typename Areal>
struct multipoint_areal<MultiPoint, Areal, multi_polygon_tag>
    : multi_point_multi_geometry<MultiPoint, Areal>
{};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Point, typename MultiPoint, std::size_t DimensionCount>
struct disjoint
    <
        Point, MultiPoint, DimensionCount, point_tag, multi_point_tag, false
    > : detail::disjoint::multirange_constant_size_geometry<MultiPoint, Point>
{};


template <typename MultiPoint, typename Segment, std::size_t DimensionCount>
struct disjoint
    <
        MultiPoint, Segment, DimensionCount, multi_point_tag, segment_tag, false
    > : detail::disjoint::multirange_constant_size_geometry<MultiPoint, Segment>
{};


template <typename MultiPoint, typename Box, std::size_t DimensionCount>
struct disjoint
    <
        MultiPoint, Box, DimensionCount, multi_point_tag, box_tag, false
    > : detail::disjoint::multirange_constant_size_geometry<MultiPoint, Box>
{};


template
<
    typename MultiPoint1,
    typename MultiPoint2,
    std::size_t DimensionCount
>
struct disjoint
    <
        MultiPoint1, MultiPoint2, DimensionCount,
        multi_point_tag, multi_point_tag, false
    >
{
    template <typename Strategy>
    static inline bool apply(MultiPoint1 const& multipoint1,
                             MultiPoint2 const& multipoint2,
                             Strategy const& strategy)
    {
        if ( boost::size(multipoint2) < boost::size(multipoint1) )
        {
            return detail::disjoint::multipoint_multipoint
                ::apply(multipoint2, multipoint1, strategy);
        } 

        return detail::disjoint::multipoint_multipoint
            ::apply(multipoint1, multipoint2, strategy);
   }
};


template <typename Linear, typename MultiPoint, std::size_t DimensionCount>
struct disjoint
    <
        Linear, MultiPoint, DimensionCount, linear_tag, multi_point_tag, false
    > : detail::disjoint::multipoint_linear<MultiPoint, Linear>
{};


template <typename MultiPoint, typename Linear, std::size_t DimensionCount>
struct disjoint
    <
        MultiPoint, Linear, DimensionCount, multi_point_tag, linear_tag, false
    > : detail::disjoint::multipoint_linear<MultiPoint, Linear>
{};


template <typename Areal, typename MultiPoint, std::size_t DimensionCount>
struct disjoint
    <
        Areal, MultiPoint, DimensionCount, areal_tag, multi_point_tag, false
    > : detail::disjoint::multipoint_areal<MultiPoint, Areal>
{};


template <typename MultiPoint, typename Areal, std::size_t DimensionCount>
struct disjoint
    <
        MultiPoint, Areal, DimensionCount, multi_point_tag, areal_tag, false
    > : detail::disjoint::multipoint_areal<MultiPoint, Areal>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIPOINT_GEOMETRY_HPP

/* multipoint_geometry.hpp
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
*/