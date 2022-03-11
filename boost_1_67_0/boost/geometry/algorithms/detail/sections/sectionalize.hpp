// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

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
#include <vector>

#include <boost/concept/requires.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/range.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_fundamental.hpp>

#include <boost/geometry/core/config.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/algorithms/expand.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/algorithms/detail/ring_identifier.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/util/math.hpp>
#include <boost/geometry/policies/robustness/no_rescale_policy.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/algorithms/detail/expand_by_epsilon.hpp>
#include <boost/geometry/algorithms/detail/buffer/buffer_box.hpp>

#include <boost/geometry/strategies/envelope.hpp>
#include <boost/geometry/strategies/expand.hpp>

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
    typedef Box box_type;
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
    typedef Box box_type;
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
    typedef typename boost::mpl::at_c<DimensionVector, Index>::type dimension;

    template <typename Segment>
    static inline void apply(Segment const& seg,
                int directions[Count])
    {
        typedef typename coordinate_type<Segment>::type coordinate_type;

        coordinate_type const c0 = geometry::get<0, dimension::value>(seg);
        coordinate_type const c1 = geometry::get<1, dimension::value>(seg);

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
    typedef typename boost::mpl::at_c<DimensionVector, 0>::type dimension;

    template <typename Segment>
    static inline void apply(Segment const& seg,
                int directions[Count])
    {
        typedef typename coordinate_type<Segment>::type coordinate_type;
        typedef typename coordinate_system<Point>::type::units units_t;

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
    template <typename Box, typename Point, typename EnvelopeStrategy>
    static inline void apply(Box & box, Point const& prev, Point const& curr,
                             EnvelopeStrategy const& strategy)
    {
        geometry::model::referring_segment<Point const> seg(prev, curr);
        geometry::envelope(seg, box, strategy);
    }
};

template <>
struct box_first_in_section<cartesian_tag>
{
    template <typename Box, typename Point, typename ExpandStrategy>
    static inline void apply(Box & box, Point const& prev, Point const& curr,
                             ExpandStrategy const& )
    {
        geometry::envelope(prev, box);
        geometry::expand(box, curr);
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
                             Strategy const& )
    {
        geometry::expand(box, curr);
    }
};

/// @brief Helper class to create sections of a part of a range, on the fly
template
<
    typename Point,
    typename DimensionVector
>
struct sectionalize_part
{
    static const std::size_t dimension_count
        = boost::mpl::size<DimensionVector>::value;

    template
    <
        typename Iterator,
        typename RobustPolicy,
        typename Sections
    >
    static inline void apply(Sections& sections,
                             Iterator begin, Iterator end,
                             RobustPolicy const& robust_policy,
                             ring_identifier ring_id,
                             std::size_t max_count)
    {
        typedef typename strategy::envelope::services::default_strategy
            <
                segment_tag,
                typename cs_tag<typename Sections::box_type>::type
            >::type envelope_strategy_type;

        typedef typename strategy::expand::services::default_strategy
            <
                segment_tag,
                typename cs_tag<typename Sections::box_type>::type
            >::type expand_strategy_type;

        apply(sections, begin, end,
              robust_policy,
              envelope_strategy_type(),
              expand_strategy_type(),
              ring_id, max_count);
    }

    template
    <
        typename Iterator,
        typename RobustPolicy,
        typename Sections,
        typename EnvelopeStrategy,
        typename ExpandStrategy
    >
    static inline void apply(Sections& sections,
                             Iterator begin, Iterator end,
                             RobustPolicy const& robust_policy,
                             EnvelopeStrategy const& envelope_strategy,
                             ExpandStrategy const& expand_strategy,
                             ring_identifier ring_id,
                             std::size_t max_count)
    {
        boost::ignore_unused(robust_policy);

        typedef typename boost::range_value<Sections>::type section_type;
        BOOST_STATIC_ASSERT
            (
                (static_cast<std::size_t>(section_type::dimension_count)
                 == static_cast<std::size_t>(boost::mpl::size<DimensionVector>::value))
            );

        typedef typename geometry::robust_point_type
        <
            Point,
            RobustPolicy
        >::type robust_point_type;

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
                Point, DimensionVector, 0, dimension_count
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
                        0, geometry::dimension<Point>::type::value
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
                    ::apply(section.bounding_box, previous_robust_point, current_robust_point, envelope_strategy);
            }
            else
            {
                // In cartesian this is expand with current point
                // in non-cartesian this is expand with a segment
                box_next_in_section<typename cs_tag<robust_point_type>::type>
                    ::apply(section.bounding_box, previous_robust_point, current_robust_point, expand_strategy);
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
    typename Point,
    typename DimensionVector
>
struct sectionalize_range
{
    template
    <
        typename Range,
        typename RobustPolicy,
        typename Sections,
        typename EnvelopeStrategy,
        typename ExpandStrategy
    >
    static inline void apply(Range const& range,
                             RobustPolicy const& robust_policy,
                             Sections& sections,
                             EnvelopeStrategy const& envelope_strategy,
                             ExpandStrategy const& expand_strategy,
                             ring_identifier ring_id,
                             std::size_t max_count)
    {
        typedef typename closeable_view<Range const, Closure>::type cview_type;
        typedef typename reversible_view
        <
            cview_type const,
            Reverse ? iterate_reverse : iterate_forward
        >::type view_type;

        cview_type cview(range);
        view_type view(cview);

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

        sectionalize_part<Point, DimensionVector>::apply(sections,
            boost::begin(view), boost::end(view),
            robust_policy, envelope_strategy, expand_strategy,
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
        typename EnvelopeStrategy,
        typename ExpandStrategy
    >
    static inline void apply(Polygon const& poly,
                RobustPolicy const& robust_policy,
                Sections& sections,
                EnvelopeStrategy const& envelope_strategy,
                ExpandStrategy const& expand_strategy,
                ring_identifier ring_id,
                std::size_t max_count)
    {
        typedef typename point_type<Polygon>::type point_type;
        typedef sectionalize_range
        <
                closure<Polygon>::value, Reverse,
                point_type, DimensionVector
        > per_range;

        ring_id.ring_index = -1;
        per_range::apply(exterior_ring(poly), robust_policy, sections,
                         envelope_strategy, expand_strategy, ring_id, max_count);

        ring_id.ring_index++;
        typename interior_return_type<Polygon const>::type
            rings = interior_rings(poly);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it, ++ring_id.ring_index)
        {
            per_range::apply(*it, robust_policy, sections,
                             envelope_strategy, expand_strategy, ring_id, max_count);
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
        typename EnvelopeStrategy,
        typename ExpandStrategy
    >
    static inline void apply(Box const& box,
                RobustPolicy const& robust_policy,
                Sections& sections,
                EnvelopeStrategy const& envelope_strategy,
                ExpandStrategy const& expand_strategy,
                ring_identifier const& ring_id, std::size_t max_count)
    {
        typedef typename point_type<Box>::type point_type;

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
                closed, false,
            point_type,
            DimensionVector
        >::apply(points, robust_policy, sections,
                 envelope_strategy, expand_strategy,
                 ring_id, max_count);
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
        typename EnvelopeStrategy,
        typename ExpandStrategy
    >
    static inline void apply(MultiGeometry const& multi,
                RobustPolicy const& robust_policy,
                Sections& sections,
                EnvelopeStrategy const& envelope_strategy,
                ExpandStrategy const& expand_strategy,
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
                          envelope_strategy, expand_strategy,
                          ring_id, max_count);
        }
    }
};

// TODO: If it depends on CS it should probably be made into strategy.
// For now implemented here because of ongoing work on robustness
//   the fact that it interferes with detail::buffer::buffer_box
//   and that we probably need a general strategy for defining epsilon in
//   various coordinate systems, e.g. for point comparison, enlargement of
//   bounding boxes, etc.
template <typename CSTag>
struct expand_by_epsilon
    : not_implemented<CSTag>
{};

template <>
struct expand_by_epsilon<cartesian_tag>
{
    template <typename Box>
    static inline void apply(Box & box)
    {
        detail::expand_by_epsilon(box);
    }
};

template <>
struct expand_by_epsilon<spherical_tag>
{
    template <typename Box>
    static inline void apply(Box & box)
    {
        typedef typename coordinate_type<Box>::type coord_t;
        static const coord_t eps = boost::is_same<coord_t, float>::value
            ? coord_t(1e-6)
            : coord_t(1e-12);
        detail::expand_by_epsilon(box, eps);
    }
};

// TODO: In geographic CS it should probably also depend on FormulaPolicy.
template <>
struct expand_by_epsilon<geographic_tag>
    : expand_by_epsilon<spherical_tag>
{};

template <typename Sections, typename Strategy>
inline void enlarge_sections(Sections& sections, Strategy const&)
{
    // Enlarge sections slightly, this should be consistent with math::equals()
    // and with the tolerances used in general_form intersections.
    // This avoids missing turns.
    
    // Points and Segments are equal-compared WRT machine epsilon, but Boxes aren't
    // Enlarging Boxes ensures that they correspond to the bound objects,
    // Segments in this case, since Sections are collections of Segments.

    // It makes section a tiny bit too large, which might cause (a small number)
    // of more comparisons
    for (typename boost::range_iterator<Sections>::type it = boost::begin(sections);
        it != boost::end(sections);
        ++it)
    {
#if defined(BOOST_GEOMETRY_USE_RESCALING)
        detail::sectionalize::expand_by_epsilon
            <
                typename Strategy::cs_tag
            >::apply(it->bounding_box);

#else
        // Expand the box to avoid missing any intersection. The amount is
        // should be larger than epsilon. About the value itself: the smaller
        // it is, the higher the risk to miss intersections. The larger it is,
        // the more comparisons are made. So it should be on the high side.
        detail::buffer::buffer_box(it->bounding_box, 0.001, it->bounding_box);
#endif
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
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_OR_NOT_YET_IMPLEMENTED_FOR_THIS_GEOMETRY_TYPE
            , (types<Geometry>)
        );
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
    : detail::sectionalize::sectionalize_range
        <
            closed, false,
            typename point_type<LineString>::type,
            DimensionVector
        >
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
            typename point_type<Ring>::type,
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
            detail::sectionalize::sectionalize_range
                <
                    closed, false,
                    typename point_type<MultiLinestring>::type,
                    DimensionVector
                >
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
    \param envelope_strategy strategy for envelope calculation
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
    typename EnvelopeStrategy,
    typename ExpandStrategy
>
inline void sectionalize(Geometry const& geometry,
                RobustPolicy const& robust_policy,
                Sections& sections,
                EnvelopeStrategy const& envelope_strategy,
                ExpandStrategy const& expand_strategy,
                int source_index = 0,
                std::size_t max_count = 10)
{
    BOOST_STATIC_ASSERT((! boost::is_fundamental<EnvelopeStrategy>::value));

    concepts::check<Geometry const>();

    typedef typename boost::range_value<Sections>::type section_type;

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

    BOOST_MPL_ASSERT((boost::is_same<ctype1, ctype2>));


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
                 envelope_strategy, expand_strategy,
                 ring_id, max_count);

    detail::sectionalize::enlarge_sections(sections, envelope_strategy);
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
    typedef typename strategy::envelope::services::default_strategy
        <
            typename tag<Geometry>::type,
            typename cs_tag<Geometry>::type
        >::type envelope_strategy_type;

    typedef typename strategy::expand::services::default_strategy
        <
            typename boost::mpl::if_c
                <
                    boost::is_same<typename tag<Geometry>::type, box_tag>::value,
                    box_tag,
                    segment_tag
                >::type,
            typename cs_tag<Geometry>::type
        >::type expand_strategy_type;

    boost::geometry::sectionalize
        <
            Reverse, DimensionVector
        >(geometry, robust_policy, sections,
          envelope_strategy_type(),
          expand_strategy_type(),
          source_index, max_count);
}

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_SECTIONS_SECTIONALIZE_HPP

/* sectionalize.hpp
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
*/