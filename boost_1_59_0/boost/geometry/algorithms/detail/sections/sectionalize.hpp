// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2021.
// Modifications copyright (c) 2013-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTIONALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTIONALIZE_HPP

#include <cstddef>
#include <type_traits>
#include <vector>

#include <boost/concept/requires.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/core/config.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>
#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/normalize_spheroidal_coordinates.hpp>
#include <boost/geometry/util/sequence.hpp>
#include <boost/geometry/views/detail/closed_clockwise_view.hpp>

// TEMP
#include <boost/geometry/strategy/envelope.hpp>
#include <boost/geometry/strategy/expand.hpp>

namespace boost { namespace geometry
{


/*!
    \brief Structure containing section information
    \details Section information consists of a bounding box, direction
        information (if it is increasing or decreasing, per dimension),
        index information (begin-end, ring, multi) and the number of
        segments in this section

    \tparam Box box-type
    \tparam DimensionCount number of dimensions for this section
    \ingroup sectionalize
 */
template
<
    typename Box,
    std::size_t DimensionCount
>
struct section
{
    using box_type = Box;
    static std::size_t const dimension_count = DimensionCount;

    int directions[DimensionCount];
    ring_identifier ring_id;
    Box bounding_box;

    // NOTE: size_type could be passed as template parameter
    // NOTE: these probably also could be of type std::size_t
    signed_size_type begin_index;
    signed_size_type end_index;
    std::size_t count;
    std::size_t range_count;
    bool duplicate;
    signed_size_type non_duplicate_index;

    bool is_non_duplicate_first;
    bool is_non_duplicate_last;

    inline section()
        : begin_index(-1)
        , end_index(-1)
        , count(0)
        , range_count(0)
        , duplicate(false)
        , non_duplicate_index(-1)
        , is_non_duplicate_first(false)
        , is_non_duplicate_last(false)
    {
        assign_inverse(bounding_box);
        for (std::size_t i = 0; i < DimensionCount; i++)
        {
            directions[i] = 0;
        }
    }
};


/*!
    \brief Structure containing a collection of sections
    \note Derived from a vector, proves to be faster than of deque
    \note vector might be templated in the future
    \ingroup sectionalize
 */
template <typename Box, std::size_t DimensionCount>
struct sections : std::vector<section<Box, DimensionCount> >
{
    using box_type = Box;
    static std::size_t const value = DimensionCount;
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace sectionalize
{

// NOTE: This utility will NOT work for latitudes, dimension 1 in spherical
// and geographic coordinate system because in these coordinate systems
// e.g. a segment on northern hemisphere may go towards greater latitude
// and then towards lesser latitude.
template
<
    typename Point,
    typename DimensionVector,
    std::size_t Index,
    std::size_t Count,
    typename CastedCSTag = typename tag_cast
                            <
                                typename cs_tag<Point>::type,
                                spherical_tag
                            >::type
>
struct get_direction_loop
{
    using dimension = typename util::sequence_element<Index, DimensionVector>::type;

    template <typename Segment>
    static inline void apply(Segment const& seg,
                int directions[Count])
    {
        auto const& c0 = geometry::get<0, dimension::value>(seg);
        auto const& c1 = geometry::get<1, dimension::value>(seg);

        directions[Index] = c1 > c0 ? 1 : c1 < c0 ? -1 : 0;

        get_direction_loop
        <
            Point,
            DimensionVector,
            Index + 1,
            Count,
            CastedCSTag
        >::apply(seg, directions);
    }
};

template
<
    typename Point,
    typename DimensionVector,
    std::size_t Count
>
struct get_direction_loop<Point, DimensionVector, 0, Count, spherical_tag>
{
    using dimension = typename util::sequence_element<0, DimensionVector>::type;

    template <typename Segment>
    static inline void apply(Segment const& seg,
                int directions[Count])
    {
        using coordinate_type = typename coordinate_type<Segment>::type;
        using units_t = typename coordinate_system<Point>::type::units;

        coordinate_type const diff = math::longitude_distance_signed
                                        <
                                            units_t, coordinate_type
                                        >(geometry::get<0, 0>(seg),
                                          geometry::get<1, 0>(seg));

        coordinate_type zero = coordinate_type();
        directions[0] = diff > zero ? 1 : diff < zero ? -1 : 0;

        get_direction_loop
        <
            Point,
            DimensionVector,
            1,
            Count,
            spherical_tag
        >::apply(seg, directions);
    }
};

template
<
    typename Point,
    typename DimensionVector,
    std::size_t Count,
    typename CastedCSTag
>
struct get_direction_loop<Point, DimensionVector, Count, Count, CastedCSTag>
{
    template <typename Segment>
    static inline void apply(Segment const&, int [Count])
    {}
};


//! Copy one static array to another
template <typename T, std::size_t Index, std::size_t Count>
struct copy_loop
{
    static inline void apply(T const source[Count], T target[Count])
    {
        target[Index] = source[Index];
        copy_loop<T, Index + 1, Count>::apply(source, target);
    }
};

template <typename T, std::size_t Count>
struct copy_loop<T, Count, Count>
{
    static inline void apply(T const [Count], T [Count])
    {}
};

//! Compare two static arrays
template <typename T, std::size_t Index, std::size_t Count>
struct compare_loop
{
    static inline bool apply(T const array1[Count], T const array2[Count])
    {
        return array1[Index] != array2[Index]
            ? false
            : compare_loop
                <
                    T, Index + 1, Count
                >::apply(array1, array2);
    }
};

template <typename T, std::size_t Count>
struct compare_loop<T, Count, Count>
{
    static inline bool apply(T const [Count], T const [Count])
    {

        return true;
    }
};


template <std::size_t Dimension, std::size_t DimensionCount>
struct check_duplicate_loop
{
    template <typename Segment>
    static inline bool apply(Segment const& seg)
    {
        if (! geometry::math::equals
                (
                    geometry::get<0, Dimension>(seg),
                    geometry::get<1, Dimension>(seg)
                )
            )
        {
            return false;
        }

        return check_duplicate_loop
        <
                Dimension + 1, DimensionCount
        >::apply(seg);
    }
};

template <std::size_t DimensionCount>
struct check_duplicate_loop<DimensionCount, DimensionCount>
{
    template <typename Segment>
    static inline bool apply(Segment const&)
    {
        return true;
    }
};

//! Assign a value to a static array
template <typename T, std::size_t Index, std::size_t Count>
struct assign_loop
{
    static inline void apply(T dims[Count], T const value)
    {
        dims[Index] = value;
        assign_loop<T, Index + 1, Count>::apply(dims, value);
    }
};

template <typename T, std::size_t Count>
struct assign_loop<T, Count, Count>
{
    static inline void apply(T [Count], T const)
    {
    }
};

template <typename CSTag>
struct box_first_in_section
{
    template <typename Box, typename Point, typename Strategy>
    static inline void apply(Box & box, Point const& prev, Point const& curr,
                             Strategy const& strategy)
    {
        geometry::model::referring_segment<Point const> seg(prev, curr);
        geometry::envelope(seg, box, strategy);
    }
};

template <>
struct box_first_in_section<cartesian_tag>
{
    template <typename Box, typename Point, typename Strategy>
    static inline void apply(Box & box, Point const& prev, Point const& curr,
                             Strategy const& strategy)
    {
        geometry::envelope(prev, box, strategy);
        geometry::expand(box, curr, strategy);
    }
};

template <typename CSTag>
struct box_next_in_section
{
    template <typename Box, typename Point, typename Strategy>
    static inline void apply(Box & box, Point const& prev, Point const& curr,
                             Strategy const& strategy)
    {
        geometry::model::referring_segment<Point const> seg(prev, curr);
        geometry::expand(box, seg, strategy);
    }
};

template <>
struct box_next_in_section<cartesian_tag>
{
    template <typename Box, typename Point, typename Strategy>
    static inline void apply(Box & box, Point const& , Point const& curr,
                             Strategy const& strategy)
    {
        geometry::expand(box, curr, strategy);
    }
};

/// @brief Helper class to create sections of a part of a range, on the fly
template<typename DimensionVector>
struct sectionalize_part
{
    static const std::size_t dimension_count
        = util::sequence_size<DimensionVector>::value;

    template
    <
        typename Iterator,
        typename RobustPolicy,
        typename Sections,
        typename Strategy
    >
    static inline void apply(Sections& sections,
                             Iterator begin, Iterator end,
                             RobustPolicy const& robust_policy,
                             Strategy const& strategy,
                             ring_identifier ring_id,
                             std::size_t max_count)
    {
        boost::ignore_unused(robust_policy);

        using section_type = typename boost::range_value<Sections>::type;
        using box_type = typename section_type::box_type;
        using point_type = typename geometry::point_type<box_type>::type;

        BOOST_STATIC_ASSERT
            (
                section_type::dimension_count
                 == util::sequence_size<DimensionVector>::value
            );

        using robust_point_type = typename geometry::robust_point_type
            <
                point_type,
                RobustPolicy
            >::type;

        std::size_t const count = std::distance(begin, end);
        if (count == 0)
        {
            return;
        }

        signed_size_type index = 0;
        signed_size_type ndi = 0; // non duplicate index
        section_type section;

        bool mark_first_non_duplicated = true;
        std::size_t last_non_duplicate_index = sections.size();

        Iterator it = begin;
        robust_point_type previous_robust_point;
        geometry::recalculate(previous_robust_point, *it, robust_policy);

        for(Iterator previous = it++;
            it != end;
            ++previous, ++it, index++)
        {
            robust_point_type current_robust_point;
            geometry::recalculate(current_robust_point, *it, robust_policy);
            model::referring_segment<robust_point_type> robust_segment(
                    previous_robust_point, current_robust_point);

            int direction_classes[dimension_count] = {0};
            get_direction_loop
            <
                point_type, DimensionVector, 0, dimension_count
            >::apply(robust_segment, direction_classes);

            // if "dir" == 0 for all point-dimensions, it is duplicate.
            // Those sections might be omitted, if wished, lateron
            bool duplicate = false;

            if (direction_classes[0] == 0)
            {
                // Recheck because ALL dimensions should be checked,
                // not only first one.
                // (dimension_count might be < dimension<P>::value)
                if (check_duplicate_loop
                    <
                        0, geometry::dimension<point_type>::type::value
                    >::apply(robust_segment)
                    )
                {
                    duplicate = true;

                    // Change direction-info to force new section
                    // Note that wo consecutive duplicate segments will generate
                    // only one duplicate-section.
                    // Actual value is not important as long as it is not -1,0,1
                    assign_loop
                    <
                        int, 0, dimension_count
                    >::apply(direction_classes, -99);
                }
            }

            if (section.count > 0
                && (! compare_loop
                        <
                            int, 0, dimension_count
                        >::apply(direction_classes, section.directions)
                    || section.count > max_count)
                )
            {
                if (! section.duplicate)
                {
                    last_non_duplicate_index = sections.size();
                }

                sections.push_back(section);
                section = section_type();
            }

            if (section.count == 0)
            {
                section.begin_index = index;
                section.ring_id = ring_id;
                section.duplicate = duplicate;
                section.non_duplicate_index = ndi;
                section.range_count = count;

                if (mark_first_non_duplicated && ! duplicate)
                {
                    section.is_non_duplicate_first = true;
                    mark_first_non_duplicated = false;
                }

                copy_loop
                    <
                        int, 0, dimension_count
                    >::apply(direction_classes, section.directions);

                // In cartesian this is envelope of previous point expanded with current point
                // in non-cartesian this is envelope of a segment
                box_first_in_section<typename cs_tag<robust_point_type>::type>
                    ::apply(section.bounding_box, previous_robust_point, current_robust_point, strategy);
            }
            else
            {
                // In cartesian this is expand with current point
                // in non-cartesian this is expand with a segment
                box_next_in_section<typename cs_tag<robust_point_type>::type>
                    ::apply(section.bounding_box, previous_robust_point, current_robust_point, strategy);
            }

            section.end_index = index + 1;
            section.count++;
            if (! duplicate)
            {
                ndi++;
            }
            previous_robust_point = current_robust_point;
        }

        // Add last section if applicable
        if (section.count > 0)
        {
            if (! section.duplicate)
            {
                last_non_duplicate_index = sections.size();
            }

            sections.push_back(section);
        }

        if (last_non_duplicate_index < sections.size()
            && ! sections[last_non_duplicate_index].duplicate)
        {
            sections[last_non_duplicate_index].is_non_duplicate_last = true;
        }
    }
};


template
<
    closure_selector Closure,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize_range
{
    template
    <
        typename Range,
        typename RobustPolicy,
        typename Sections,
        typename Strategy
    >
    static inline void apply(Range const& range,
                             RobustPolicy const& robust_policy,
                             Sections& sections,
                             Strategy const& strategy,
                             ring_identifier ring_id,
                             std::size_t max_count)
    {
        detail::closed_clockwise_view
            <
                Range const,
                Closure,
                Reverse ? counterclockwise : clockwise
            > const view(range);

        std::size_t const n = boost::size(view);
        if (n == 0)
        {
            // Zero points, no section
            return;
        }

        if (n == 1)
        {
            // Line with one point ==> no sections
            return;
        }

        sectionalize_part<DimensionVector>::apply(sections,
            boost::begin(view), boost::end(view),
            robust_policy, strategy,
            ring_id, max_count);
    }
};

template
<
    bool Reverse,
    typename DimensionVector
>
struct sectionalize_polygon
{
    template
    <
        typename Polygon,
        typename RobustPolicy,
        typename Sections,
        typename Strategy
    >
    static inline void apply(Polygon const& poly,
                RobustPolicy const& robust_policy,
                Sections& sections,
                Strategy const& strategy,
                ring_identifier ring_id,
                std::size_t max_count)
    {
        using sectionalizer = sectionalize_range
            <
                closure<Polygon>::value, Reverse, DimensionVector
            >;

        ring_id.ring_index = -1;
        sectionalizer::apply(exterior_ring(poly), robust_policy, sections,
                         strategy, ring_id, max_count);

        ring_id.ring_index++;
        auto const& rings = interior_rings(poly);
        for (auto it = boost::begin(rings); it != boost::end(rings);
             ++it, ++ring_id.ring_index)
        {
            sectionalizer::apply(*it, robust_policy, sections,
                             strategy, ring_id, max_count);
        }
    }
};

template <typename DimensionVector>
struct sectionalize_box
{
    template
    <
        typename Box,
        typename RobustPolicy,
        typename Sections,
        typename Strategy
    >
    static inline void apply(Box const& box,
                RobustPolicy const& robust_policy,
                Sections& sections,
                Strategy const& strategy,
                ring_identifier const& ring_id, std::size_t max_count)
    {
        using point_type = typename point_type<Box>::type;

        assert_dimension<Box, 2>();

        // Add all four sides of the 2D-box as separate section.
        // Easiest is to convert it to a polygon.
        // However, we don't have the polygon type
        // (or polygon would be a helper-type).
        // Therefore we mimic a linestring/std::vector of 5 points

        // TODO: might be replaced by assign_box_corners_oriented
        // or just "convert"
        point_type ll, lr, ul, ur;
        geometry::detail::assign_box_corners(box, ll, lr, ul, ur);

        std::vector<point_type> points;
        points.push_back(ll);
        points.push_back(ul);
        points.push_back(ur);
        points.push_back(lr);
        points.push_back(ll);

        // NOTE: Use cartesian envelope strategy in all coordinate systems
        //       because edges of a box are not geodesic segments
        sectionalize_range
            <
                closed, false, DimensionVector
            >::apply(points, robust_policy, sections,
                     strategy, ring_id, max_count);
    }
};

template <typename DimensionVector, typename Policy>
struct sectionalize_multi
{
    template
    <
        typename MultiGeometry,
        typename RobustPolicy,
        typename Sections,
        typename Strategy
    >
    static inline void apply(MultiGeometry const& multi,
                RobustPolicy const& robust_policy,
                Sections& sections,
                Strategy const& strategy,
                ring_identifier ring_id,
                std::size_t max_count)
    {
        ring_id.multi_index = 0;
        for (typename boost::range_iterator<MultiGeometry const>::type
                    it = boost::begin(multi);
            it != boost::end(multi);
            ++it, ++ring_id.multi_index)
        {
            Policy::apply(*it, robust_policy, sections,
                          strategy,
                          ring_id, max_count);
        }
    }
};

template <typename Sections, typename Strategy>
inline void enlarge_sections(Sections& sections, Strategy const&)
{
    // Expand the box to avoid missing any intersection. The amount is
    // should be larger than epsilon. About the value itself: the smaller
    // it is, the higher the risk to miss intersections. The larger it is,
    // the more comparisons are made, which is not harmful for the result
    // (but it might be for the performance).
    // So it should be on the high side.

    // Use a compilable and workable epsilon for all types, for example:
    // - for double :~ 2.22e-13
    // - for float  :~ 1e-4
    // - for Boost.Multiprecision (50) :~ 5.35e-48
    // - for Boost.Rational : 0/1

    for (auto& section : sections)
    {
        using gt = decltype(section.bounding_box);
        using ct = typename geometry::coordinate_type<gt>::type;
        static ct const eps = math::scaled_epsilon<ct>(1000);
        expand_by_epsilon(section.bounding_box, eps);
    }
}


}} // namespace detail::sectionalize
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Tag,
    typename Geometry,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not or not yet implemented for this Geometry type.",
        Tag, Geometry);
};

template
<
    typename Box,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize<box_tag, Box, Reverse, DimensionVector>
    : detail::sectionalize::sectionalize_box<DimensionVector>
{};

template
<
    typename LineString,
    typename DimensionVector
>
struct sectionalize
    <
        linestring_tag,
        LineString,
        false,
        DimensionVector
    >
    : detail::sectionalize::sectionalize_range<closed, false, DimensionVector>
{};

template
<
    typename Ring,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize<ring_tag, Ring, Reverse, DimensionVector>
    : detail::sectionalize::sectionalize_range
        <
            geometry::closure<Ring>::value, Reverse,
            DimensionVector
        >
{};

template
<
    typename Polygon,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize<polygon_tag, Polygon, Reverse, DimensionVector>
    : detail::sectionalize::sectionalize_polygon
        <
            Reverse, DimensionVector
        >
{};

template
<
    typename MultiPolygon,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize<multi_polygon_tag, MultiPolygon, Reverse, DimensionVector>
    : detail::sectionalize::sectionalize_multi
        <
            DimensionVector,
            detail::sectionalize::sectionalize_polygon
                <
                    Reverse,
                    DimensionVector
                >
        >

{};

template
<
    typename MultiLinestring,
    bool Reverse,
    typename DimensionVector
>
struct sectionalize<multi_linestring_tag, MultiLinestring, Reverse, DimensionVector>
    : detail::sectionalize::sectionalize_multi
        <
            DimensionVector,
            detail::sectionalize::sectionalize_range<closed, false, DimensionVector>
        >

{};

} // namespace dispatch
#endif


/*!
    \brief Split a geometry into monotonic sections
    \ingroup sectionalize
    \tparam Geometry type of geometry to check
    \tparam Sections type of sections to create
    \param geometry geometry to create sections from
    \param robust_policy policy to handle robustness issues
    \param sections structure with sections
    \param strategy strategy for envelope calculation
    \param expand_strategy strategy for partitions
    \param source_index index to assign to the ring_identifiers
    \param max_count maximal number of points per section
        (defaults to 10, this seems to give the fastest results)

 */
template
<
    bool Reverse,
    typename DimensionVector,
    typename Geometry,
    typename Sections,
    typename RobustPolicy,
    typename Strategy
>
inline void sectionalize(Geometry const& geometry,
                RobustPolicy const& robust_policy,
                Sections& sections,
                Strategy const& strategy,
                int source_index = 0,
                std::size_t max_count = 10)
{
    concepts::check<Geometry const>();

    using section_type = typename boost::range_value<Sections>::type;

    // Compiletime check for point type of section boxes
    // and point type related to robust policy
    typedef typename geometry::coordinate_type
    <
        typename section_type::box_type
    >::type ctype1;
    typedef typename geometry::coordinate_type
    <
        typename geometry::robust_point_type
        <
            typename geometry::point_type<Geometry>::type,
            RobustPolicy
        >::type
    >::type ctype2;

    BOOST_STATIC_ASSERT((std::is_same<ctype1, ctype2>::value));


    sections.clear();

    ring_identifier ring_id;
    ring_id.source_index = source_index;

    dispatch::sectionalize
        <
            typename tag<Geometry>::type,
            Geometry,
            Reverse,
            DimensionVector
        >::apply(geometry, robust_policy, sections,
                 strategy,
                 ring_id, max_count);

    detail::sectionalize::enlarge_sections(sections, strategy);
}


template
<
    bool Reverse,
    typename DimensionVector,
    typename Geometry,
    typename Sections,
    typename RobustPolicy
>
inline void sectionalize(Geometry const& geometry,
                         RobustPolicy const& robust_policy,
                         Sections& sections,
                         int source_index = 0,
                         std::size_t max_count = 10)
{
    using box_type = typename Sections::box_type;
    using strategy_type = typename strategies::envelope::services::default_strategy
        <
            Geometry,
            box_type
        >::type;

    boost::geometry::sectionalize
        <
            Reverse, DimensionVector
        >(geometry, robust_policy, sections,
          strategy_type(),
          source_index, max_count);
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTIONALIZE_HPP

/* sectionalize.hpp
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
*/