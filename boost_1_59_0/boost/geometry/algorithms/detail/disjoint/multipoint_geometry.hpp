// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIPOINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_MULTIPOINT_GEOMETRY_HPP

#include <algorithm>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/multirange_geometry.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>

#include <boost/geometry/policies/compare.hpp>


// TEMP
#include <boost/geometry/strategies/envelope/cartesian.hpp>
#include <boost/geometry/strategies/envelope/geographic.hpp>
#include <boost/geometry/strategies/envelope/spherical.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


class multipoint_multipoint
{
private:
    template <typename Iterator, typename CSTag>
    class unary_not_disjoint_predicate
        : geometry::less<void, -1, CSTag>
    {
    private:
        typedef geometry::less<void, -1, CSTag> base_type;

    public:
        unary_not_disjoint_predicate(Iterator first, Iterator last)
            : base_type(), m_first(first), m_last(last)
        {}

        template <typename Point>
        inline bool operator()(Point const& point) const
        {
            return std::binary_search(m_first,
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
        BOOST_GEOMETRY_ASSERT( boost::size(multipoint1) <= boost::size(multipoint2) );

        using cs_tag = typename Strategy::cs_tag;
        using less_type = geometry::less<void, -1, cs_tag>;
        using point1_type = typename boost::range_value<MultiPoint1>::type;

        std::vector<point1_type> points1(boost::begin(multipoint1),
                                         boost::end(multipoint1));

        std::sort(points1.begin(), points1.end(), less_type());

        using predicate_type = unary_not_disjoint_predicate
            <
                typename std::vector<point1_type>::const_iterator,
                cs_tag
            >;

        return none_of(boost::begin(multipoint2),
                       boost::end(multipoint2),
                       predicate_type(points1.begin(), points1.end()));
    }
};


template <typename MultiPoint, typename Linear>
class multipoint_linear
{
private:
    template <typename Strategy>
    struct expand_box_point
    {
        explicit expand_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        void apply(Box& total, Point const& point) const
        {
            geometry::expand(total, point, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct expand_box_segment
    {
        explicit expand_box_segment(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Segment>
        void apply(Box& total, Segment const& segment) const
        {
            geometry::expand(total,
                             geometry::return_envelope<Box>(segment, m_strategy),
                             m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_point
    {
        explicit overlaps_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        bool apply(Box const& box, Point const& point) const
        {
            return ! detail::disjoint::disjoint_point_box(point, box,
                                                          m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_segment
    {
        explicit overlaps_box_segment(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Segment>
        bool apply(Box const& box, Segment const& segment) const
        {
            return ! dispatch::disjoint<Segment, Box>::apply(segment, box, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(Strategy const& strategy)
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
        Strategy const& m_strategy;
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

        // TODO: disjoint Segment/Box may be called in partition multiple times
        // possibly for non-cartesian segments which could be slow. We should consider
        // passing a range of bounding boxes of segments after calculating them once.
        // Alternatively instead of a range of segments a range of Segment/Envelope pairs
        // should be passed, where envelope would be lazily calculated when needed the first time
        geometry::partition
            <
                geometry::model::box<typename point_type<MultiPoint>::type>
            >::apply(multipoint, segment_range(linear), visitor,
                     expand_box_point<Strategy>(strategy),
                     overlaps_box_point<Strategy>(strategy),
                     expand_box_segment<Strategy>(strategy),
                     overlaps_box_segment<Strategy>(strategy));

        return ! visitor.intersection_found();
    }

    template <typename Strategy>
    static inline bool apply(Linear const& linear, MultiPoint const& multipoint,
                             Strategy const& strategy)
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
        typedef typename point_type<MultiPoint>::type point1_type;
        typedef typename point_type<SingleGeometry>::type point2_type;
        typedef model::box<point2_type> box2_type;
        
        box2_type box2;
        geometry::envelope(single_geometry, box2, strategy);
        geometry::detail::expand_by_epsilon(box2);

        typedef typename boost::range_const_iterator<MultiPoint>::type iterator;
        for ( iterator it = boost::begin(multi_point) ; it != boost::end(multi_point) ; ++it )
        {
            // The default strategy is enough for Point/Box
            if (! detail::disjoint::disjoint_point_box(*it, box2, strategy)
                && ! dispatch::disjoint<point1_type, SingleGeometry>::apply(*it, single_geometry, strategy))
            {
                return false;
            }
        }

        return true;
    }

    template <typename Strategy>
    static inline bool apply(SingleGeometry const& single_geometry, MultiPoint const& multi_point,
                             Strategy const& strategy)
    {
        return apply(multi_point, single_geometry, strategy);
    }
};


template <typename MultiPoint, typename MultiGeometry>
class multi_point_multi_geometry
{
private:
    template <typename Strategy>
    struct expand_box_point
    {
        explicit expand_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        void apply(Box& total, Point const& point) const
        {
            geometry::expand(total, point, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct expand_box_box_pair
    {
        explicit expand_box_box_pair(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename BoxPair>
        void apply(Box& total, BoxPair const& box_pair) const
        {
            geometry::expand(total, box_pair.first, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_point
    {
        explicit overlaps_box_point(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename Point>
        bool apply(Box const& box, Point const& point) const
        {
            return ! detail::disjoint::disjoint_point_box(point, box, m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    struct overlaps_box_box_pair
    {
        explicit overlaps_box_box_pair(Strategy const& strategy)
            : m_strategy(strategy)
        {}

        template <typename Box, typename BoxPair>
        bool apply(Box const& box, BoxPair const& box_pair) const
        {
            return ! detail::disjoint::disjoint_box_box(box_pair.first, box,
                                                        m_strategy);
        }

        Strategy const& m_strategy;
    };

    template <typename Strategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(MultiGeometry const& multi_geometry,
                          Strategy const& strategy)
            : m_intersection_found(false)
            , m_multi_geometry(multi_geometry)
            , m_strategy(strategy)
        {}

        template <typename Point, typename BoxPair>
        inline bool apply(Point const& point, BoxPair const& box_pair)
        {
            typedef typename boost::range_value<MultiGeometry>::type single_type;

            // The default strategy is enough for Point/Box
            if (! m_intersection_found
                && ! detail::disjoint::disjoint_point_box(point, box_pair.first, m_strategy)
                && ! dispatch::disjoint
                        <
                            Point, single_type
                        >::apply(point, range::at(m_multi_geometry, box_pair.second), m_strategy))
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
        Strategy const& m_strategy;
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
        
        std::size_t count2 = boost::size(multi_geometry);
        std::vector<box_pair_type> boxes(count2);
        for (std::size_t i = 0 ; i < count2 ; ++i)
        {
            geometry::envelope(range::at(multi_geometry, i), boxes[i].first, strategy);
            geometry::detail::expand_by_epsilon(boxes[i].first);
            boxes[i].second = i;
        }

        item_visitor_type<Strategy> visitor(multi_geometry, strategy);

        geometry::partition
            <
                box1_type
            >::apply(multi_point, boxes, visitor,
                     expand_box_point<Strategy>(strategy),
                     overlaps_box_point<Strategy>(strategy),
                     expand_box_box_pair<Strategy>(strategy),
                     overlaps_box_box_pair<Strategy>(strategy));

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