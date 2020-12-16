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
ueLz+7voecvhb0fgsDh5Qy2uHsQJn2Q5FA+XnaVHgvF7aZFZnmRDfrravL/bhd/lVM8KmhsOdv4xPSj+kpf+U+8lfOZ155GL166OhW87wY2hcEvunLkSJxJr03yncic4u0EvxO7TpiYeeJHIOfW7aDz0eEYvOAhPmun9i+ZZEk/s2cvzEtSnHzrwP/3qwd5wbDgb3sCXF7pnx7yHHXCNQmygHpV9T61/KQoV6/gdLt+CrjKil3wQNxPF8MDBav3n8FX/cRAmbYKFL6vTL+RkG3H0jhit+bBnFKg3G/UlheDHAsdP0ldMXoJf0nfyN9Nv3MV9asdXw9XddfonWNNqmpxNVc+uxCPoApv1P/3Li6tBMGG6a1xIN+ylR9tL9zKXN+Xbrl7018/EzSJ4don+6HacXo9TSJwWuoNvO6p7NdgDfyqVR08CKz/a7TuL6S4t5Hx+OmmrkK5VXrsfV5vCpPC/H9KR3RgLXSYW5Wp9Ws19akKynjkGf55tTpPFhTL1j4Vek0AGTb+SfqxhV/7ewc4TxYPrPNmHtiHf8h2L04viOG4sfFFAXuJgKTujsCmPmtZWD8KnW8TL7VfIwfvUbz354TK0EuMt8wUtNLPzqOODh4qjCo4p6Rz8fi7Nq29TmIrbn10LXxP79S6iu1XRRvn+rMO0gJf1hmprW7g6xXx+OpMvUnB4+DNE7Wshbic/hKPq/eduhue06ybsUUgsXvxoFC4L6vgWmJUTTsnj6Wv0e608P/Mp/BvW5F0jH+lrfS6Rn2L0ZjFS6WM8Tnw+WpRP9fWfGv+JQepXH73EXXAb7+980Jxg90NLYdetPt+uNvPlcHYpV8YYzWlQXfg9TZ93BdviHTX206Lg0E0jjON5/c18fHcI+7JhoVp09vyu1cRYhukVXbOHen4If3hMHre5XU7UYn9rHw8OVsuX0lm/xhN/kMu0gB1T9PV00Utwod92x8Mtx2HFRez8Kz1/GC2KfldfjznyVs/eqKynKECbog816q7Pq4m/0fQfUQfHNPZdYy7YiTaHC3ekK2VN8KYFzvO4fL9f3cM92+FF3fWY09WqCn1xDE3Gk2PVprfV3EtxA/mYug42N1fHtuIEcKQW+65NUVv1n51WGS/uNeoVfBHenN1OPM0R07h+I7WtbA7crhwsh4lFDhmH2Cj2sHFcyA/yvFdWON4MJ10r937Wj7RSW6eyz1xa7XqYJXaHloLXjWlZN9JFy8v9bfo2c+un5lyE/y/sQ2+Dw7+wy3ixlTJSnA2RK3PYYJa8wW1Kyt+6ercJ5tn/QzjRVL6+LLbF+FLHBxgySe8y1vhfbybn+aRhmrzbhcfo885bLi++iMIdS9mhkfnpIW9saY2hKFzZFoVia2HyGWoZ/Stlhf16eqlRdfUSerebursOzXGJ77yCc/1YQv6Kr0b4c4MsevUmOMoAOUBb3ih2BltTGC8W4jTk0XX00nLjjfv1OdXY5ibzoMkXrqgnwreG19CLHGEnuNdoglzP5TxN4d1EdqJ1DKoM6+nn1frKv+vUgxNquhgsVj8enpK37V0nM9/kf8SxAd6p1Ye3yCt5lOVV/L4sDaQfHlvLPGBVl2Sx3o5etUtudRZ7edRUcfdwdfj4CP/TF8rA0PLZ6b7GE4p6VoF+96U5cN41b1MHz36Gf0om9OMozJ8F73HX0rP1MXrezb/gHgldDF88QF8YWsWcksRJYfwJZ0p6IYQ7X9Orq+fJfHf0F/GsNs2Fw9erl+8acxU1diqucvl5vkuDKACDG4i9/fTvWrTul9Ksk81nP/XqRdgz8w/8/r5+4i7+wR+ug2n3nqvv08fUeFzczdf/doIH/FRSL3BGMzn5jl6krXE=
*/