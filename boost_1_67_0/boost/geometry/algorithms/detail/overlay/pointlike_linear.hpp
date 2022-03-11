// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_LINEAR_HPP

#include <iterator>
#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>

#include <boost/geometry/iterators/segment_iterator.hpp>

#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/not.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/pointlike_pointlike.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


// difference/intersection of point-linear
template
<
    typename Point,
    typename Geometry,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
struct point_single_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(Point const& point,
                                       Geometry const& geometry,
                                       RobustPolicy const&,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        action_selector_pl
            <
                PointOut, OverlayType
            >::apply(point, Policy::apply(point, geometry, strategy), oit);
        return oit;
    }
};

// difference/intersection of multipoint-segment
template
<
    typename MultiPoint,
    typename Geometry,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
struct multipoint_single_point
{
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       Geometry const& geometry,
                                       RobustPolicy const&,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        for (typename boost::range_iterator<MultiPoint const>::type
                 it = boost::begin(multipoint);
             it != boost::end(multipoint);
             ++it)
        {
            action_selector_pl
                <
                    PointOut, OverlayType
                >::apply(*it, Policy::apply(*it, geometry, strategy), oit);
        }

        return oit;
    }
};


// difference/intersection of multipoint-linear
template
<
    typename MultiPoint,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
class multipoint_linear_point
{
private:
    // structs for partition -- start
    template <typename ExpandPointStrategy>
    struct expand_box_point
    {
        template <typename Box, typename Point>
        static inline void apply(Box& total, Point const& point)
        {
            geometry::expand(total, point, ExpandPointStrategy());
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
                             m_strategy.get_box_expand_strategy());
        }

        EnvelopeStrategy const& m_strategy;
    };

    template <typename DisjointPointBoxStrategy>
    struct overlaps_box_point
    {
        template <typename Box, typename Point>
        static inline bool apply(Box const& box, Point const& point)
        {
            return ! geometry::disjoint(point, box, DisjointPointBoxStrategy());
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
            return ! geometry::disjoint(segment, box, m_strategy);
        }

        DisjointStrategy const& m_strategy;
    };

    template <typename OutputIterator, typename Strategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(OutputIterator& oit, Strategy const& strategy)
            : m_oit(oit)
            , m_strategy(strategy)
        {}

        template <typename Item1, typename Item2>
        inline bool apply(Item1 const& item1, Item2 const& item2)
        {
            action_selector_pl
                <
                    PointOut, overlay_intersection
                >::apply(item1, Policy::apply(item1, item2, m_strategy), m_oit);

            return true;
        }

    private:
        OutputIterator& m_oit;
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

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator get_common_points(MultiPoint const& multipoint,
                                                   Linear const& linear,
                                                   OutputIterator oit,
                                                   Strategy const& strategy)
    {
        item_visitor_type<OutputIterator, Strategy> item_visitor(oit, strategy);

        typedef typename Strategy::envelope_strategy_type envelope_strategy_type;
        typedef typename Strategy::disjoint_strategy_type disjoint_strategy_type;
        typedef typename Strategy::disjoint_point_box_strategy_type disjoint_point_box_strategy_type;
        typedef typename Strategy::expand_point_strategy_type expand_point_strategy_type;

        // TODO: disjoint Segment/Box may be called in partition multiple times
        // possibly for non-cartesian segments which could be slow. We should consider
        // passing a range of bounding boxes of segments after calculating them once.
        // Alternatively instead of a range of segments a range of Segment/Envelope pairs
        // should be passed, where envelope would be lazily calculated when needed the first time
        geometry::partition
            <
                geometry::model::box
                    <
                        typename boost::range_value<MultiPoint>::type
                    >
            >::apply(multipoint, segment_range(linear), item_visitor,
                     expand_box_point<expand_point_strategy_type>(),
                     overlaps_box_point<disjoint_point_box_strategy_type>(),
                     expand_box_segment<envelope_strategy_type>(strategy.get_envelope_strategy()),
                     overlaps_box_segment<disjoint_strategy_type>(strategy.get_disjoint_strategy()));

        return oit;
    }

public:
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       Linear const& linear,
                                       RobustPolicy const& robust_policy,
                                       OutputIterator oit,
                                       Strategy const& strategy)
    {
        typedef std::vector
            <
                typename boost::range_value<MultiPoint>::type
            > point_vector_type;

        point_vector_type common_points;

        // compute the common points
        get_common_points(multipoint, linear,
                          std::back_inserter(common_points),
                          strategy);

        return multipoint_multipoint_point
            <
                MultiPoint, point_vector_type, PointOut, OverlayType
            >::apply(multipoint, common_points, robust_policy, oit, strategy);
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch { namespace overlay
{

// dispatch struct for pointlike-linear difference/intersection computation
template
<
    typename PointLike,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag1,
    typename Tag2
>
struct pointlike_linear_point
    : not_implemented<PointLike, Linear, PointOut>
{};


template
<
    typename Point,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        Point, Linear, PointOut, OverlayType, point_tag, linear_tag
    > : detail::overlay::point_single_point
        <
            Point, Linear, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename Point,
    typename Segment,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        Point, Segment, PointOut, OverlayType, point_tag, segment_tag
    > : detail::overlay::point_single_point
        <
            Point, Segment, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename MultiPoint,
    typename Linear,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        MultiPoint, Linear, PointOut, OverlayType, multi_point_tag, linear_tag
    > : detail::overlay::multipoint_linear_point
        <
            MultiPoint, Linear, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename MultiPoint,
    typename Segment,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_linear_point
    <
        MultiPoint, Segment, PointOut, OverlayType, multi_point_tag, segment_tag
    > : detail::overlay::multipoint_single_point
        <
            MultiPoint, Segment, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


}} // namespace detail_dispatch::overlay
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_LINEAR_HPP

/* pointlike_linear.hpp
R+/XhLzl9L+zI/pQixKXB3rDjI6GCJ+99RT4PMdPUwGDT7shSMzD/BsEvz0y3WtJdQ4ijhcf1qK8E1qLI3CIlUOzmwRVsFhmSSuhMWiWQ4qkPuiHLyOxpJuejg6D7DL9Ke+0R5yqOitD4Qr0L9oooW3iK7JnYHzRIGuM2ETwY/Sv32s6tnllOX1DgFqLf9tEHTnRx66DiniKOBEoQRO9Z1d/1ahd0O65bhIA710ZkP1I8O6+c/4YtTMco6Zy7gNXrygtT0k4sqHtZqH2yT8Nx1NvtU87oMrB3UvvagiMoQRFKPh5k73VQIpfkdGTd3ewMB4/wCzKv+kdAsHM9MYxQMehHd2Q40EVjKNjFPyvbc/pD1rWr+HfiICLvRmpBry5KJgs1fUqIJcFYcKCN8x00dUq/D7mLZkSkT4qrBJHKPg4laQVpnFk+AtJGQUEfTXWVxDF7Ym3CXXFZYwoqoithvgMWV7difzlYS2FghswzXwuhUAdQoYr58uMxGmS/GPxSBgFBGk8WnVAji9SjR6UKv7YXToz3DRRWhSCqEzGhUDHfXs3CMXsckd/v+3sckI2xbPV9HKdMVHbx19cfmoNKbfdLjIA7xIk+9b/dEsg3f/+Ydy7k+iTAWGVVQDOSiUC4mUVAGjH9r9cWPrTJJn0V6X4Y8G/V/xn2bFO+ItRAl5xAMSyVAL+MquAeht3AtWDBPDJXCDUlw+cxUpxzbCHVqfjagat/f23k+ZQV0ZftwilWIgkmZvoRvtrZoiKXj08TvS/+HysnW/eXPKyRgB43GHOuPCUBnys9fI0hhV+3cgyVmL5piXRCw+poOyUiYEVRjd2/LHMBLo/NYy/qi5bYdegcNwPS/GPQmifKRud8FSn3QFcEpR6y+laEX8Lg85wplpEMffBKeE6V2VZlJHSpQMy2xhfjO8HfiCKv3+K2uYZ6mZUI10HlBw2tQMc6O2ViNHPi+/CBlsUhHJ93bKU3iAjK4nBDyGQQsE3e7UmgucJ8tkimcvP6dT6QZbPeit/gO711B39GqgoINjzqhnrBi4IkiTpu1eSLNcBfNmRsfweDJsVR4wxEq8GOt6S4Ukl5/c0G0ddRvsvH0+hRUckNoGmXEwJxflZSlt+48jTWoO/fGJOQrCmRBAnn/+2iK4K4TKOyQSxPB0R87EqN48FYDGdUKlcDBnfSnGFunTgbbwcuxrAo4+SUk1VcpM5mWCldD5eCraKYfmsznO4Iq4BoUzC4BKND0LJr6NHZuR1+e8uUXgHGqOQ/+qabUX8+dRvnPTiPqeAwO46o4xG8NZbDPRC0X9a9QU83zUM2rEY6DhdxxJfy3UK/88EGuZirwr0sYOHcdwQRPxIzBKfzo88qFsEkPHIiCUe7jZFAFcOAubDn3J8Am8CvwcyvswLFqJrO33hakTnFqNzKkaNX4enVAikYO8uCcHzMXY+fmxy5V63WQ/0I/m/eYAt8dPw7kFnzycg4/WqArv/ZDBSysiorh0rXWPfTqL5agA+9n1Z4lu3jFN3igE6/lRZUnvMK/5ljMAzShwcGBRgvlVZhhZnYpVb/soAtviUYq5I99ZT2utLK/l7d1SIgBQfiUS8uYcyk4aFPnPvGS25Qhn9mWxoDjRvQNykNpNoDHTe9CvNkHnUUMpCmlhYAen6VCLa/5LSZ10oLWML1E4FYCUi+++Af1dJwNwLXTDqy0K8o/zz7TTrP5xu+D7sn5aRhuRx4tOrUiqAnk1bjYyfgK7IKq/Psu0oPR3Qa5YKljYbJwUZRzix7G7AKquGordV9nfeW6g17OjdaRTVrsX8xH452xIquu2974IUvOMkK+QkpT/GABnfw1rm73267/Qny6wEqNDbNNoFfGwJQjTmFZqVAYfR2Cw1XaRjqYPJNstT8992qh2LpxfKe0apKM5pQGeUAWQRWCPaHam5/OuNb6UUbkH4s4G8elrXVc8L82qrYg8ywU6R5tdmV/zuawspbT/Kws0C4K+BfpN0zA8dKffPtJeJMfB4KjF0GERlPJ6uKSBw+7mphBQf4oBQnIs3Q8Hv46gBdWww9ek/k1Dz/z5TYZn8s657CRgyXHqfj9/a/ENWrPYbP7HsgMYx4rxmdAKWIcO7O8tq3FV+E07uUes0pcHoaI0ddSF7yPg130vmLeneaoZ1shdFJuFonqbmfaWHkR8dH0+oFhsTdcTQrK2T64pNvXuHqjpiahY8UMDmqRj008CViosAQ2VwdYw2hWX9eUW9LB5kMYtz60VgW4+onZYplUUWnLpkUE2L3l4cfuoK5l2y9Xa4s6RXWciP+oe6NFd8K9hwAkzfVlywue2LA2/RJTG7zU8KqGmiGLKwDd/TETjqLvrQUDePz+LHnjpW56YPZgUd1SP4ZM42In6jN3lk5moxF/GQZLfjjAPMtgFt5nIM/d65JekUnGBD6xmzxqN6dKmTw+tKrQ12CAG5eWQr9+m7Wq2RPt+ByrW7wZI5pE5puUq929reVN3eHUKYdjUsynVrX3C/7e1bkOOr4TlMAYIzmUXCTY85Pu6SGAyo9v6hWB7V72URQmbJLMq1l7/wrGtF8JDL6TEMQ7Nlxy7cfLHwRUkdK16wtgdQgKUrQDI6MERynEFHv12abwWsJGv0hBgEMvrnqU91V0Nfn7DTRoQpMEz8sC2ilCO1PKgmeeluFDFLMX2qWzlbox1MFH3QewDDfLdP0v4PHqM2NIZ4iq7lHt14+D7pYx2pGbMHMAn61KWqbdagL4P1FlZPtemte0A5aCbkOfMQQZtviX8N3wo3AkyyA4mfdCOGSBlzHeHp2+9ArVnfz5IWtbcalpaGsv+QBI1mmNTZARw2onTj6lN+j0Sl/x/GDOdmjLBxqmRLqLBF5wvj5NGgeaD8YsWwaahTm/5UApCPRHJOwARRVJSALQin2ZmguUgzx3aEY/VKsrpFJS3v7EnzVzMRdTrX61wUTfeFZQJr4QYeYLqqlnDLCiE4fC0QhuG69d+e5jvIQAuRhZpYLVtb4Qgb37RkN0Azg5haaZ4/RswLmpa7ww8YBISxMcEE9xwYg8nJr9FRYru2/sTSIGozFk/NLHJdmY4SN0JKxgEM9Gv5fu8DXNPHLRP96qzGqwkzEo59TMgzKINxBP1zQi3KrlSf29vJoHRqKksPmyUMeyt+rUQVlwpP9JQlKtQKLbM4j8eJ05unExTdtCR6NAPf8Grkzbtsh9iAo3Nb+qUkaJKJnIu/8rPJJzt1ya+LU9SykBK6z55eFzVzJ5+hkM7RJefmAtBqfW5tRi5VdJ+fFb0FyPc5dXvhFNgI8Alevzq/H7bo/UfzEMZ8NHvjmSDUXElhNANOKguWNeov2Kx1/WNtejgl1W9ABPNDN1Wsdjc+/aqOadwgQ11W71AM+qt013ICdnthPhN974lM9J8s0lFfCBViVvm2RUs45iK4n025vQjENasBQSxlIzsPfDJ5AXWqvHyIn02ykfVV4EOtP0LeLglijuHwFMPuZWBDO9QoZrIqSoXMVawCVwsUG4iO/CiUkZ3MlezfakVjg92t49oKrOfaI3wRzR3nJgjfvEphmYJxNxluyz0fv/vzADZOktnF9VZAXhyXnAY6MVgMXV83ID8bQbmUHMFGNlJ1Vao1oD70hw2bTqTvJ9l6CaSDh9yg/SQx74W4KYEVr+r4KTYdswrnlxEbqjQHp2kDJ+H7ES/bHOqyUX4+HdO0c2V5WluKHoYJHjqslKEVgnVHjQLVC6rlnd7u9sAXkc+6X/uuZciUwMwAEvspOFI+uxpNmhOh55kKFgRwb73mAD9tGe+nPt6uCpXRPF8m13SGlUxKbkF1B2vFoPPMUlqWTh8DaXf1XrPzOrLfkZOlTh9Qakw0ED76gnmt26U/eGN+ESD0OwQiGwt7kCBliX+CQ545p7uHfA8zAZ9sgQjQgWLjOfY4tHaGa5HU3QRzpzOtw9JuB+KqF+XkLOhfBMJpPy51g+ltcEp0wEbbRnVq7Z76BOV7NhNbEklFY+O/xpU3OmoulO5P1kyXVkYm+1LgJm2T2yKCLUGd0CeIpPIihiwFdxYPiNCr1Z/GoWBIsdTbuiIMh3WXR/0u9a2R7WjShlHB0raH7vWZRn2SG/YOM0l59IbmidaQfBAoEKnYgDWQtzCICEPbTCuk5g59nytue+vf/S4Ygt4hy5nmpo3K3V0SzgZH/FLiWqC++KuxGRsOfppzuFK7qCZvBorSIlwaN5oGlNSVGtZbRUOnwxXoRk8dMDzAx5cLpUfr1D+6G6/+//+tnSxjYlqCkb6IdLu8QBgmlVO9ASKTvSF0kt8aQhZ8mlgQsRp9CXmvhN1ICG9gP34LeqziWee7Wa+Dxnf+bqmszVFP4TDJUpBcglLy/QkfgRkwKNch0M2fAEN/0uOqbe46iSnJ/KbHG89JdVbXq+bHrKZnTfcsu6W419nbNtxmmVWdokduSc5vZVFWCbPCaKuC8KmLO2jCjh3K1iHfJVk9LtJzsDWMrTjygF8pUqsTQhl2g7d6PkwHJQCEQrYiod3aNT0CakPURvSCQd9ZDjxWXeGC0BLY1rpWt0DjruwB1GZTDH5KAL8guMXkdFU1XTKLsKYI6/rTSljdk0PcOA1i3+brqpu/tqVQ0S9fsG+OAiSEAEPxqjIZlPGQZ9ZJiizowZXYr8WcFMG4Y5Hw9/TcB7bpDOHyccfQ5thfaHUDjI1bOFS4394uYX/GyiI1gaCbW1HChGLROR56KZaSqzB4AZTA3Qez2m2rxfJr5QXM/04CrLc50N4q7Yjqyvj3I7Lh4k2ynp7myIu8t3tFKQse+d8FzjV4wrI1aKSGSAQgCenukR1sUkVhnyle0zs1tf34c6tFeB1tqpiJGLs8OTleYL2dshC7Rfsh8/2vbb+RdENcDc+JFewVdd8nvGkBm+mTqEiYsccQFqoL8+sng98TeI73MPBrg5liAr+2oySbRDNnRlR8Ys93ck+SSKIYXDfCh/l3lVJb+NxihPI0qylX3VvsOVwH5fMOcTxceqgxamkQKedpqnW8nBg0gkXXQw0v/6Fnv/7yBvYC8hi4+OfrnGVKT13UcqxpsfkwmvPRTrqdZAORmPfw4/WS+0KHtqOEGW/cOPP9QScEBF6NcVekCkJaV2Kq8MXBHEOWsUP4Wrg/z7dyg1TGrGWDWdOCnmwjgXvpFu+wJuI4JawMDW0cD4tJk4NAlkXBdfhGnXsfco9CF1tjamjo89yrxAlgkqxn9DjjEh+HcTciXW40tkPm+sUoW5PY6ojaPpcfaNSUtOlEYaphjhkBll+ig08y7OgtZCNrm1LX888KMYBqJ0teaLztrSlUBLuKnq2Lqv6LVmYiEJdzJjORTBkUSqSIq1vxB2mDmGZ7Voaz7EL5naukijuNL2ZMmx3loc8uAl2yZFhDPhTSIUP7+lt1TY8Mk3BRD/VitpGHVUa98J7EYV8KC6CYXRZD8dsLMZj4wCYEn2KvoD4n0T20olvTpY1fWWcjdZSooA6SmIqhXclmYo3ioaEHlMd6/V3vs8v45cIAyc85dcTTIbKyR4hKQmkfCzmR31dr0+TjAkvDYvODJG5J4nOp4kXEsaQ5l6yE7QVzDI2KuQDIOheJGQrDQTkxBrDhgClRDUwWJzec+u4N/vWZfwydsQRI9CHLO/gho+RUfEMmdD9SMeLa1vXhl+0FxqF/yuM0/bRBg5UHocVU13Lil0BC9Fm8SonQW474aZiJ4PLWUC7HOsteW0jJnSA240gY4aHJVos/l4kEvtVsogeK7MWZ52sGdLoHUoYEyPxg7j4dkmNLPYhg/Om5Omu7E3VXo+vl4UkcxYmTYuJUSsMeNXK07eUL8rYabb1dQIxhOqgxcy+omh0q64snX0nIredWzyFBWvPpEnhWUlGeKCkf41JGXOjqimLxk3L7aNivwJQWNUq+aGuf53tcLFzfrZLJO94XMy+hBFnzDAvQlWj4HebK24k7YeHI7gWF8wRf1DrniJBh3/MrhmUtSJDvrivD/mD+Wb2AnIxJUCxtgAqN4iZpg76GNGi5BJ+tB/9ZRYFsiK2o3XZmr/qKSGwnPw+6dPbT16z3SPaX4jLHnjh7i0sEz3L52LpFKW7vVH3lxmOr+0u+9kGxrVaKXN1S8TKdCSvHW/aAvkyh0Z8ZUIKz7PB0xPdHtuDxtwUNwoiYQGrIzAAsrkOTyoMPe3AxMrJkqg67v6ZcYo+TonUrJeta+9ChlzE2dfi/xutX3saOwtaq11+Y4HnPRa8qnssfVX2BdYqfZfiUKmATVXUHQfNQQ/UOP05yKbxvBQ3tnc8oWoovRetFEFdDptvSmR3edt4ohbxE/p+8YheHzNaoFE9Oz240jDLOAifaGAyPNh8hYtnHv8sWYrt427MZ4pGDY9KC0mNNnjk52F3RShNjiPkNWJWZH4CrBmj2YDv+Qy9MxK4W4si+wH825MbkT5dofkBe2artLAhsbxw3maNE+tVMDFU8y3B5Src9KYuPAtjGM1ANf9j2SFM0S+1VFYqeLvaIYkhb/eK0HENmEQZARfQMmCfRofhxRXn0pMS99W9H0oeVV/rcyzK1C9u+Y1rO0R1ntNhLxNgWQ+PwnGixCpx6u3Bg9iSFyDn6BJSDKe/W81TM54v7QbuePPXwrtKTxjeG7gaMQcUkepQHOylygG87Kc7uxhXhBs+LufsTgvH2ZU2LJ8Mbsxvh5XKOrnES1oRJyeVmCR2iJTGcrs9ESakmgb8yQoMdB1YQhGVA5rNsBNHFZGgFRtiB3GbZ5fiXhx1ixYsRwWe2BbmdGvjYiLGAH+xc+yIjbxYmrBJv8/5hpV0lp3EWEKZWbw+iGaiVZZ2jxrneWwhZ8ZvB4ESG6h7UvYL/4jtptO0RC6hoGet8M0zgWGWwYw6E7UFRy1TnB/bkyAA4gcayjWMkgBhGstVzgqNHQHMDkNiz0saI0VAo4YgQUXwZ856qyZp5z4I0ts+yOW+den8gYuY+tl6CHPvv/ZNwRPtWb6w9omBD7gP9ftf3h49uimfluJx8Z1GU4lF3Md98TkGm4ZT7/zQSjv+8BV/8fuvGwFp+55AbqFc3u2wnuf00oOPw1rWJ389rPmHJ1soYTyZkZ9QIq/NYAQNwZi1qLTstjzO6VMSMzArl7tppBuhOcOc/m16fmdaW7kzlngN/ZksfAncS5a2KFKsMXoXp1IEtYeIpqbYD+58pdesXYJy0iTM8qsyHC5/XZF5S3XACTeTy2uueolmc8t4PDvZH1mzPa/reMe9x/+mmFecFR+yWerpuhgPimGcZOWtu3+Mrmo6hVf2FXToVxN6+X56b2lKN1D1pJYLerhy8UZXwjocTUfPYST1eLv/zcyEklDstdHDAg4lYr4mDlb18jvjyTh8zG4gIz8aGf73KhkXz5R7Phv3cjeQ/wHzHUcxZDDnPl5YJ58K9lCAoLThJ8sTVRx/4Agg7aDG1DokWSmYXHsOBi5wceJAHGQsKEtb8kyg5Bnx7s8HbhAVBLSlT/deYmar8b3oPDn0y+9ckcFn8Zj6OEewfKsJaykA7VKGi5c9DviEkadlppdq0nLB2xOoWjqlcSPkYQ0GNdqve7n0+lXy6rlyXg0/DxnnObDa86SXRk4D3K3nnjDb8i29TgmrxUNpN2KofQLVmHMCXNeX6ImONSRVHxLU3cm/jdc43MeP7uf6ghHHggO9BFfRrHvmJCBKM60O31nev+2AjWVF+UW5si9PVzbTlHT6XJ96Xv7seJYpiwhu1oS2hdiq6iFX0MqY2XmSbZeFGrIlT/+5NRTkd7SN1YUrU6o7nZxYPnvFUMIdX4cEtVzwkt6UAH8a4Rv0G3JTtxUhK0LTlX3jtBCtN0oPJtGVbeI4z9414TZsWjwAELPvTQuO6FKVNDv1mxQr9JlX5a/tC73OuMmNWVSq9g4MkXAys49AOMO0UGS+6Gsybygv4rSLUFA/UjoMVZxLHboiBafOekGgXjfRPO+nLCozl9GsJXD6glTuwJy2M49KP4U7xTvY0/dfMpMMQdWYJwzR0UdBeP72X8YnwkPT4r+TQtCLbOEyTvwEMNZPQa7uJqiJbun6GQxOEBv8vlOnSffuGczXtgrWn9Uj+qDWinRxj1jDya3qKqzYam6m5li9ukV12fU3ixuPiWgbNzjCU6RRMSxCE6dRKX/YPZ1OIBo2wNIPmZ5h+875PuELcjM3Gk4+0kxkMS3lYcIjw6EltPKOrIFB9qPiZFajJr+c/P2i/uEWdvRvuWlnVrlsPzN2bj8ydu1YihFPVsSAEDi+klx4F/Z9BGG6ZhKatDf9qJs4SlBZ0UQiPirgDB9DK61LFTfq7nAz4gRCGTjY+Ay9bvm+4esEwZNWrRA2c6bXr89VXuK7wFYFgBY64+UJIE9TdCKWxGYdJOsZJImEP0CJublmPG+LkNV+nybeqZCi+NCSKs2MydYJrArFZG2q5+mYHrppt9+EHwzxGfmOV9mKpG0lVZTQqz5hIcfIj1hMGRAaERBmZek6dRbf4uwRqVjQW/s+3LUQbBhAIpxxJc5YkNB4fgVVuepMZLbeqxW6mvjg2Ok/xJW41wadpiJmsrOVuLDrymS2ht5IKyyfMkNeBneFxTLPmWCZP3anzbVyaIpyw5mhYWrNobyxCzroIGvmC+MEUVAhUIbnPDRBuVsyFgL+e/b8qLSQjKyOf46qtz5Pr9unLMaBYdKzMrnBBu0LQld3ChfwlvF9gQ58lR9pVn9sB4YZe5ylhmM7ktHwBuT+i6l334CZP7oyVUy3SyY/TbjvqsyncA8fcCXKrY+9Z4uQzb6dJtSqOE602MgXe3LRnazmiHpQ0MvE7Libkgsm/tnb5nbcA0XJdTyUq5TRftnKEyjw1Mkk74krxO5NOOo6nxBI3iewFrq3DaFi8ZfpOqoAFJ4joUtU/nYsfQk7anqv+PrtRNam7LpUk8TsqBRVPDRjGmUVioSkT7tti4PyzwnUlJGF1yJuNqeogJ358L+XLVA2wxXHiuotBj+i75ZqU5Y/+Nvjeiv3wn7pUNM7rr/Dnqjnt1Ciq6etsmwc6rAe6qAkU09QzI+FO3Jox3+15bw3bvq9b1d9LrJaSfDejJP+3EWo650cnXW7nw6Y/IlzEO7/VJnnHgBGPxT1X0n9XUqzkXBuwuVIxBmQT0/MiDcg7LFM+4XqegA/bE7oiNa4=
*/