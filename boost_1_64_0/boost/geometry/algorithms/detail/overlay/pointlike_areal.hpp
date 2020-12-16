// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html


#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP

#include <vector>

#include <boost/range.hpp>

#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point.hpp>

#include <boost/geometry/algorithms/disjoint.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/algorithms/detail/not.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_geometry.hpp>
#include <boost/geometry/algorithms/detail/equals/point_point.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>

#include <boost/geometry/algorithms/detail/overlay/pointlike_linear.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


// difference/intersection of multipoint-multipolygon
template
<
    typename MultiPoint,
    typename MultiPolygon,
    typename PointOut,
    overlay_type OverlayType,
    typename Policy
>
class multipoint_multipolygon_point
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
    struct expand_box_boxpair
    {
        template <typename Box1, typename Box2, typename SizeT>
        static inline void apply(Box1& total, std::pair<Box2, SizeT> const& box_pair)
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
            return ! geometry::disjoint(point, box, DisjointPointBoxStrategy());
        }
    };

    template <typename DisjointBoxBoxStrategy>
    struct overlaps_box_boxpair
    {
        template <typename Box1, typename Box2, typename SizeT>
        static inline bool apply(Box1 const& box, std::pair<Box2, SizeT> const& box_pair)
        {
            return ! geometry::disjoint(box, box_pair.first, DisjointBoxBoxStrategy());
        }
    };

    template <typename OutputIterator, typename Strategy>
    class item_visitor_type
    {
    public:
        item_visitor_type(MultiPolygon const& multipolygon,
                          OutputIterator& oit,
                          Strategy const& strategy)
            : m_multipolygon(multipolygon)
            , m_oit(oit)
            , m_strategy(strategy)
        {}

        template <typename Point, typename Box, typename SizeT>
        inline bool apply(Point const& item1, std::pair<Box, SizeT> const& item2)
        {
            action_selector_pl
                <
                    PointOut, overlay_intersection
                >::apply(item1,
                         Policy::apply(item1,
                                       range::at(m_multipolygon,
                                                 item2.second),
                         m_strategy),
                         m_oit);

            return true;
        }

    private:
        MultiPolygon const& m_multipolygon;
        OutputIterator& m_oit;        
        Strategy const& m_strategy;
    };

    template <typename Iterator, typename Box, typename SizeT, typename EnvelopeStrategy>
    static inline void fill_box_pairs(Iterator first, Iterator last,
                                      std::vector<std::pair<Box, SizeT> > & box_pairs,
                                      EnvelopeStrategy const& strategy)
    {
        SizeT index = 0;
        for (; first != last; ++first, ++index)
        {
            box_pairs.push_back(
                std::make_pair(geometry::return_envelope<Box>(*first, strategy),
                               index));
        }
    }

    template <typename OutputIterator, typename Strategy>
    static inline OutputIterator get_common_points(MultiPoint const& multipoint,
                                                   MultiPolygon const& multipolygon,
                                                   OutputIterator oit,
                                                   Strategy const& strategy)
    {
        item_visitor_type<OutputIterator, Strategy> item_visitor(multipolygon, oit, strategy);

        typedef geometry::model::point
            <
                typename geometry::coordinate_type<MultiPoint>::type,
                geometry::dimension<MultiPoint>::value,
                typename geometry::coordinate_system<MultiPoint>::type
            > point_type;
        typedef geometry::model::box<point_type> box_type;
        typedef std::pair<box_type, std::size_t> box_pair;
        std::vector<box_pair> box_pairs;
        box_pairs.reserve(boost::size(multipolygon));

        fill_box_pairs(boost::begin(multipolygon),
                       boost::end(multipolygon),
                       box_pairs,
                       strategy.get_envelope_strategy());

        typedef typename Strategy::envelope_strategy_type::box_expand_strategy_type expand_box_strategy_type;
        typedef typename Strategy::disjoint_box_box_strategy_type disjoint_box_box_strategy_type;
        typedef typename Strategy::disjoint_point_box_strategy_type disjoint_point_box_strategy_type;
        typedef typename Strategy::expand_point_strategy_type expand_point_strategy_type;

        geometry::partition
            <
                box_type
            >::apply(multipoint, box_pairs, item_visitor,
                     expand_box_point<expand_point_strategy_type>(),
                     overlaps_box_point<disjoint_point_box_strategy_type>(),
                     expand_box_boxpair<expand_box_strategy_type>(),
                     overlaps_box_boxpair<disjoint_box_box_strategy_type>());

        return oit;
    }

public:
    template <typename RobustPolicy, typename OutputIterator, typename Strategy>
    static inline OutputIterator apply(MultiPoint const& multipoint,
                                       MultiPolygon const& multipolygon,
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
        get_common_points(multipoint, multipolygon,
                          std::back_inserter(common_points),
                          strategy);

        return multipoint_multipoint_point
            <
                MultiPoint, point_vector_type, PointOut, OverlayType
            >::apply(multipoint, common_points, robust_policy, oit, strategy);
    }
};


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DISPATCH


#ifndef DOXYGEN_NO_DISPATCH
namespace detail_dispatch { namespace overlay
{

// dispatch struct for pointlike-areal difference/intersection computation
template
<
    typename PointLike,
    typename Areal,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag1,
    typename Tag2
>
struct pointlike_areal_point
    : not_implemented<PointLike, Areal, PointOut>
{};


template
<
    typename Point,
    typename Areal,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag2
>
struct pointlike_areal_point
    <
        Point, Areal, PointOut, OverlayType, point_tag, Tag2
    > : detail::overlay::point_single_point
        <
            Point, Areal, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


// TODO: Consider implementing Areal-specific version
//   calculating envelope first in order to reject Points without
//   calling disjoint for Rings and Polygons
template
<
    typename MultiPoint,
    typename Areal,
    typename PointOut,
    overlay_type OverlayType,
    typename Tag2
>
struct pointlike_areal_point
    <
        MultiPoint, Areal, PointOut, OverlayType, multi_point_tag, Tag2
    > : detail::overlay::multipoint_single_point
        <
            MultiPoint, Areal, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


template
<
    typename MultiPoint,
    typename MultiPolygon,
    typename PointOut,
    overlay_type OverlayType
>
struct pointlike_areal_point
    <
        MultiPoint, MultiPolygon, PointOut, OverlayType, multi_point_tag, multi_polygon_tag
    > : detail::overlay::multipoint_multipolygon_point
        <
            MultiPoint, MultiPolygon, PointOut, OverlayType,
            detail::not_<detail::disjoint::reverse_covered_by>
        >
{};


}} // namespace detail_dispatch::overlay
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_POINTLIKE_AREAL_HPP

/* pointlike_areal.hpp
KBb4LESxOWaItiCOtiflub8MdX2oEDIh+IXKmRIgt0bSfeoD0Cp0aKPi0HpL+3tfCk8LFe4CvF2AV6Hg7SM8fhBenvE44aG8zYDXTFvLCp4N8NQHRJTUVtrusFACWjfEzE6pVV1jltpl0oSBunGePfw/xHrBsR9d/3GjPt6tne36eK+92mw4Bj/q+Y0J1vnBIhA/3dwharAak3hS3rkwUlx9a0tGFS/Q4SL3dIhjXQaElCLfMckiX2iMzR3qWDvGYZAjpWuryNwMDs+tKoIwTp7B332Z6g+dvOwPLpJCe9ghCCVkSgLiqTXSWXNsenPVBn1qOyhtt3TA6rHLzoXoTYY+Ot8s7wTP5bTVHRfgtjHhOLc3avkZ1jJvdl+xnam8V8nzO09I1YXT/tM1Ys1XIxNVe568IXm/uc+SZmgZfvhVFa5v39je5g6GlO0tShmlJmX7v9qiKkLNajEtXGCGLZQrzZQno1dqfmdL/d94fuqNen4W2wxf1v90UrVyioX0fywT1puWx+1xOBECMjU3qk6NeUxFU5sHkCn0Oym8yZ0tdAMEbpCqcuU5/Pr9YqUHE/pMq5x5eYE9pDyf47XrVSb7yk/6mleNMlh4Cy8XIR+NvxGHE4364y6kkdevZLD2wBWK6U6jfSpBeK1u48VJbnnp6iNRZuNP9BSvyXxqMxP5K58bxdPTakoz5OepS4OjPc8x4Krajonr/CimizW6LoMkarP24jwz6aKuMh81aAk7XCvMrODuyE58y7ndpOwzIdnKt5RK2h7tNiSOnIpvFWetivPdjISBq3O0SxjH+rIaqKhTg7+jyviv5yuTTneh5pUNjDPRA3lPLdqI99Rme8XiHNxTe1x9+Z/xJM6PE/qQe9fqXWg7WRfFBtWNtwySdiPCCzZr266Q7GPtc7zJKXtjDt6KnXwBKsnTWW2cBeps5VbuZopwfXChUxsy1wwzLmzu3zIFTeJoQwFDP5i5HU65mxGrJbs1rpu28loAQVdCStT7vdovkRrz2p94Hs4rgXSbSHnz1bH/XAU5eoX6DDOLH/BDt95O1TP9BGe3hFQiDY0/yNa0o/MxYLtCcUorFG8omIEHtZ8iQsN3AIlJ5yBpwynfhnlyuTXV22l8nd5O+7UTZH1qMRnuNR1VC+wwkmOZZJfkt5frJtnUiboyx8YByDnBk7tDewURwMYcHbPPr86y/gRf1uLD8+J727NkDW7Qfo8gfA5CtGiNVo6vgq1L1nrYhBIywCbQcRCejU7AhKuQZdb0oLnMUqT+1a/0kDkVGCiMAw2o/VFSkKVHjDlFI93gQkndCWV3QM6mSha0lLw3hKrZ/Fj0/xpZ08j96f05GDIC90AKaN8c2j5DjyrMuArfPAcjO4Oca2Ft+q7V0A4mdip95OsVNh/a9e45quIXz5a8gC7EjoadgWjMRh9+Cw3Ho1HtOn0QsofvMuh3pXL6gupgeBo4tGPNrPYrAIlRdiJE79wzdAtdzYTAsL8iTJfnlvoC2srZ8Xa/Vd5QoT0yJzGeIBKjLDYn+TExegg7z4foE0zZWWqEswPuiJyoH5Kuxqc+4hYAB7nYrTI1V89U+SI0cKSQvXoqVUttdLlNSZa4NqdbKKNSAsbra1rVLCWrVlcsK66aL57Y4p0bJdzBiKCK8iT8mJdcmc+o36qtYJhiq9Qma8l+28b4WtEX019pSV+gN7Nsf0fFaX78A30Br2T64uvbo07G/1ZNEn7uNsZ4gkicod1/GZGb2chnspbLi1WvvQFv1W0oCtEJ/UG7HVF56shopyPPLehgSfIe13GwPj5H6TkjoXQtoLah/5LCz08RfnhVInxQivC3k8IzGZ6a/l/VhhT2oic=
*/