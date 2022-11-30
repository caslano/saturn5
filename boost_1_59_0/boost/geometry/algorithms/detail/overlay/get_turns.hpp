// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURNS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURNS_HPP


#include <cstddef>
#include <map>

#include <boost/array.hpp>
#include <boost/concept_check.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>
#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_ll.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_la.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/algorithms/detail/sections/range_by_section.hpp>
#include <boost/geometry/algorithms/detail/sections/section_box_policies.hpp>
#include <boost/geometry/algorithms/detail/sections/section_functions.hpp>
#include <boost/geometry/algorithms/detail/sections/sectionalize.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/concepts/check.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/iterators/ever_circling_iterator.hpp>

#include <boost/geometry/strategies/intersection_strategies.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/type_traits.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>


#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
#  include <sstream>
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{

// Silence warning C4127: conditional expression is constant
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4127)
#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace get_turns
{


struct no_interrupt_policy
{
    static bool const enabled = false;

    // variable required by self_get_turn_points::get_turns
    static bool const has_intersections = false;

    template <typename Range>
    static inline bool apply(Range const&)
    {
        return false;
    }
};

template
<
    bool IsAreal,
    typename Section,
    typename Point,
    typename CircularIterator,
    typename Strategy,
    typename RobustPolicy
>
struct unique_sub_range_from_section
{
    typedef Point point_type;

    unique_sub_range_from_section(Section const& section, signed_size_type index,
                          CircularIterator circular_iterator,
                          Point const& previous, Point const& current,
                          Strategy const& strategy,
                          RobustPolicy const& robust_policy)
        : m_section(section)
        , m_index(index)
        , m_previous_point(previous)
        , m_current_point(current)
        , m_circular_iterator(circular_iterator)
        , m_point_retrieved(false)
        , m_strategy(strategy)
        , m_robust_policy(robust_policy)
    {}

    inline bool is_first_segment() const
    {
        return !IsAreal && m_section.is_non_duplicate_first && m_index == m_section.begin_index;
    }
    inline bool is_last_segment() const
    {
        return size() == 2u;
    }

    inline std::size_t size() const
    {
        return IsAreal ? 3
            : m_section.is_non_duplicate_last && m_index + 1 >= m_section.end_index ? 2 : 3;
    }

    inline Point const& at(std::size_t index) const
    {
        BOOST_GEOMETRY_ASSERT(index < size());
        switch (index)
        {
            case 0 : return m_previous_point;
            case 1 : return m_current_point;
            case 2 : return get_next_point();
            default : return m_previous_point;
        }
    }

private :
    inline Point const& get_next_point() const
    {
        if (! m_point_retrieved)
        {
            advance_to_non_duplicate_next(m_current_point, m_circular_iterator);
            m_point = *m_circular_iterator;
            m_point_retrieved = true;
        }
        return m_point;
    }

    inline void advance_to_non_duplicate_next(Point const& current, CircularIterator& circular_iterator) const
    {
        typedef typename robust_point_type<Point, RobustPolicy>::type robust_point_type;
        robust_point_type current_robust_point;
        robust_point_type next_robust_point;
        geometry::recalculate(current_robust_point, current, m_robust_policy);
        geometry::recalculate(next_robust_point, *circular_iterator, m_robust_policy);

        // To see where the next segments bend to, in case of touch/intersections
        // on end points, we need (in case of degenerate/duplicate points) an extra
        // iterator which moves to the REAL next point, so non duplicate.
        // This needs an extra comparison (disjoint).
        // (Note that within sections, non duplicate points are already asserted,
        //   by the sectionalize process).

        // So advance to the "non duplicate next"
        // (the check is defensive, to avoid endless loops)
        std::size_t check = 0;
        while (! detail::disjoint::disjoint_point_point(
                    current_robust_point, next_robust_point, m_strategy)
               && check++ < m_section.range_count)
        {
            circular_iterator++;
            geometry::recalculate(next_robust_point, *circular_iterator, m_robust_policy);
        }
    }

    Section const& m_section;
    signed_size_type m_index;
    Point const& m_previous_point;
    Point const& m_current_point;
    mutable CircularIterator m_circular_iterator;
    mutable Point m_point;
    mutable bool m_point_retrieved;
    Strategy m_strategy;
    RobustPolicy m_robust_policy;
};

template
<
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2,
    typename Section1, typename Section2,
    typename TurnPolicy
>
class get_turns_in_sections
{
    using range1_view = detail::closed_clockwise_view
        <
            typename ring_type<Geometry1>::type const,
            geometry::closure<Geometry1>::value,
            Reverse1 ? counterclockwise : clockwise
        >;
    using range2_view = detail::closed_clockwise_view
        <
            typename ring_type<Geometry2>::type const,
            geometry::closure<Geometry2>::value,
            Reverse2 ? counterclockwise : clockwise
        >;

    using range1_iterator = typename boost::range_iterator<range1_view const>::type;
    using range2_iterator = typename boost::range_iterator<range2_view const>::type;

    using circular1_iterator = ever_circling_iterator<range1_iterator>;
    using circular2_iterator = ever_circling_iterator<range2_iterator>;

    template <typename Geometry, typename Section>
    static inline bool adjacent(Section const& section,
            signed_size_type index1, signed_size_type index2)
    {
        // About n-2:
        //   (square: range_count=5, indices 0,1,2,3
        //    -> 0-3 are adjacent, don't check on intersections)
        // Also tested for open polygons, and/or duplicates
        // About first condition: will be optimized by compiler (static)
        // It checks if it is areal (box, ring, (multi)polygon)
        signed_size_type const n = static_cast<signed_size_type>(section.range_count);

        boost::ignore_unused(n, index1, index2);

        return util::is_areal<Geometry>::value
               && index1 == 0
               && index2 >= n - 2
                ;
    }


public :
    // Returns true if terminated, false if interrupted
    template <typename Strategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline bool apply(
            int source_id1, Geometry1 const& geometry1, Section1 const& sec1,
            int source_id2, Geometry2 const& geometry2, Section2 const& sec2,
            bool skip_larger, bool skip_adjacent,
            Strategy const& strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        boost::ignore_unused(interrupt_policy);

        static bool const areal1 = util::is_areal<Geometry1>::value;
        static bool const areal2 = util::is_areal<Geometry2>::value;

        if ((sec1.duplicate && (sec1.count + 1) < sec1.range_count)
           || (sec2.duplicate && (sec2.count + 1) < sec2.range_count))
        {
            // Skip sections containig only duplicates.
            // They are still important (can indicate non-disjointness)
            // but they will be found processing adjacent sections.
            // Do NOT skip if they are the ONLY section
            return true;
        }

        range1_view const view1(range_by_section(geometry1, sec1));
        range2_view const view2(range_by_section(geometry2, sec2));

        range1_iterator begin_range_1 = boost::begin(view1);
        range1_iterator end_range_1 = boost::end(view1);

        range2_iterator begin_range_2 = boost::begin(view2);
        range2_iterator end_range_2 = boost::end(view2);

        int const dir1 = sec1.directions[0];
        int const dir2 = sec2.directions[0];
        signed_size_type index1 = sec1.begin_index;
        signed_size_type ndi1 = sec1.non_duplicate_index;

        range1_iterator prev1, it1, end1;

        get_start_point_iterator(sec1, view1, prev1, it1, end1,
                    index1, ndi1, dir1, sec2.bounding_box, robust_policy);

        // We need a circular iterator because it might run through the closing point.
        // One circle is actually enough but this one is just convenient.
        circular1_iterator next1(begin_range_1, end_range_1, it1, true);
        next1++;

        // Walk through section and stop if we exceed the other box
        // section 2:    [--------------]
        // section 1: |----|---|---|---|---|
        for (prev1 = it1++, next1++;
            it1 != end1 && ! detail::section::exceeding<0>(dir1, *prev1, sec1.bounding_box, sec2.bounding_box, robust_policy);
            ++prev1, ++it1, ++index1, ++next1, ++ndi1)
        {
            unique_sub_range_from_section
                <
                    areal1, Section1, point1_type, circular1_iterator,
                    Strategy, RobustPolicy
                > unique_sub_range1(sec1, index1,
                                    circular1_iterator(begin_range_1, end_range_1, next1, true),
                                    *prev1, *it1,
                                    strategy, robust_policy);

            signed_size_type index2 = sec2.begin_index;
            signed_size_type ndi2 = sec2.non_duplicate_index;

            range2_iterator prev2, it2, end2;

            get_start_point_iterator(sec2, view2, prev2, it2, end2,
                        index2, ndi2, dir2, sec1.bounding_box, robust_policy);
            circular2_iterator next2(begin_range_2, end_range_2, it2, true);
            next2++;

            for (prev2 = it2++, next2++;
                it2 != end2 && ! detail::section::exceeding<0>(dir2, *prev2, sec2.bounding_box, sec1.bounding_box, robust_policy);
                ++prev2, ++it2, ++index2, ++next2, ++ndi2)
            {
                bool skip = false;

                if (source_id1 == source_id2
                        && sec1.ring_id.multi_index == sec2.ring_id.multi_index
                        && sec1.ring_id.ring_index == sec2.ring_id.ring_index)
                {
                    // Sources and rings are the same

                    if (skip_larger && index1 >= index2)
                    {
                        // Skip to avoid getting all intersections twice
                        skip = true;
                    }
                    else if (skip_adjacent)
                    {
                        // In some cases (dissolve, has_self_intersections)
                        // neighbouring segments should be checked
                        // (for example to detect spikes properly)

                        // skip if it is a neighbouring segment.
                        // (including, for areas, first-last segment
                        //  and two segments with one or more degenerate/duplicate
                        //  (zero-length) segments in between)
                        skip = ndi2 == ndi1 + 1
                            || adjacent<Geometry1>(sec1, index1, index2);
                    }
                }

                if (! skip)
                {
                    unique_sub_range_from_section
                        <
                            areal2, Section2, point2_type, circular2_iterator,
                            Strategy, RobustPolicy
                        > unique_sub_range2(sec2, index2,
                                            circular2_iterator(begin_range_2, end_range_2, next2),
                                            *prev2, *it2,
                                            strategy, robust_policy);

                    typedef typename boost::range_value<Turns>::type turn_info;

                    turn_info ti;
                    ti.operations[0].seg_id
                        = segment_identifier(source_id1, sec1.ring_id.multi_index,
                                             sec1.ring_id.ring_index, index1);
                    ti.operations[1].seg_id
                        = segment_identifier(source_id2, sec2.ring_id.multi_index,
                                             sec2.ring_id.ring_index, index2);

                    std::size_t const size_before = boost::size(turns);

                    TurnPolicy::apply(unique_sub_range1, unique_sub_range2,
                                      ti, strategy, robust_policy,
                                      std::back_inserter(turns));

                    if (InterruptPolicy::enabled)
                    {
                        if (interrupt_policy.apply(
                                std::make_pair(range::pos(turns, size_before),
                                               boost::end(turns))))
                        {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }


private :
    typedef typename geometry::point_type<Geometry1>::type point1_type;
    typedef typename geometry::point_type<Geometry2>::type point2_type;

    // It is NOT possible to have section-iterators here
    // because of the logistics of "index" (the section-iterator automatically
    // skips to the begin-point, we loose the index or have to recalculate it)
    // So we mimic it here
    template <typename Range, typename Section, typename Box, typename RobustPolicy>
    static inline void get_start_point_iterator(Section const& section,
            Range const& range,
            typename boost::range_iterator<Range const>::type& it,
            typename boost::range_iterator<Range const>::type& prev,
            typename boost::range_iterator<Range const>::type& end,
            signed_size_type& index, signed_size_type& ndi,
            int dir, Box const& other_bounding_box, RobustPolicy const& robust_policy)
    {
        it = boost::begin(range) + section.begin_index;
        end = boost::begin(range) + section.end_index + 1;

        // Mimic section-iterator:
        // Skip to point such that section interects other box
        prev = it++;
        for(; it != end && detail::section::preceding<0>(dir, *it, section.bounding_box, other_bounding_box, robust_policy);
            prev = it++, index++, ndi++)
        {}
        // Go back one step because we want to start completely preceding
        it = prev;
    }
};

template
<
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2,
    typename TurnPolicy,
    typename Strategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
struct section_visitor
{
    int m_source_id1;
    Geometry1 const& m_geometry1;
    int m_source_id2;
    Geometry2 const& m_geometry2;
    Strategy const& m_strategy;
    RobustPolicy const& m_rescale_policy;
    Turns& m_turns;
    InterruptPolicy& m_interrupt_policy;

    section_visitor(int id1, Geometry1 const& g1,
                    int id2, Geometry2 const& g2,
                    Strategy const& strategy,
                    RobustPolicy const& robust_policy,
                    Turns& turns,
                    InterruptPolicy& ip)
        : m_source_id1(id1), m_geometry1(g1)
        , m_source_id2(id2), m_geometry2(g2)
        , m_strategy(strategy)
        , m_rescale_policy(robust_policy)
        , m_turns(turns)
        , m_interrupt_policy(ip)
    {}

    template <typename Section>
    inline bool apply(Section const& sec1, Section const& sec2)
    {
        if (! detail::disjoint::disjoint_box_box(sec1.bounding_box,
                                                 sec2.bounding_box,
                                                 m_strategy) )
        {
            // false if interrupted
            return get_turns_in_sections
                    <
                        Geometry1,
                        Geometry2,
                        Reverse1, Reverse2,
                        Section, Section,
                        TurnPolicy
                    >::apply(m_source_id1, m_geometry1, sec1,
                             m_source_id2, m_geometry2, sec2,
                             false, false,
                             m_strategy,
                             m_rescale_policy,
                             m_turns, m_interrupt_policy);
        }
        return true;
    }

};

template
<
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2,
    typename TurnPolicy
>
class get_turns_generic
{

public:
    template <typename Strategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(
            int source_id1, Geometry1 const& geometry1,
            int source_id2, Geometry2 const& geometry2,
            Strategy const& strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        // First create monotonic sections...
        typedef typename boost::range_value<Turns>::type ip_type;
        typedef typename ip_type::point_type point_type;

        typedef model::box
            <
                typename geometry::robust_point_type
                <
                    point_type, RobustPolicy
                >::type
            > box_type;
        typedef geometry::sections<box_type, 2> sections_type;

        sections_type sec1, sec2;
        typedef std::integer_sequence<std::size_t, 0, 1> dimensions;

        geometry::sectionalize<Reverse1, dimensions>(geometry1, robust_policy,
                                                     sec1, strategy, 0);
        geometry::sectionalize<Reverse2, dimensions>(geometry2, robust_policy,
                                                     sec2, strategy, 1);

        // ... and then partition them, intersecting overlapping sections in visitor method
        section_visitor
            <
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                TurnPolicy,
                Strategy, RobustPolicy,
                Turns, InterruptPolicy
            > visitor(source_id1, geometry1, source_id2, geometry2,
                      strategy, robust_policy, turns, interrupt_policy);

        geometry::partition
            <
                box_type
            >::apply(sec1, sec2, visitor,
                     detail::section::get_section_box<Strategy>(strategy),
                     detail::section::overlaps_section_box<Strategy>(strategy));
    }
};


// Get turns for a range with a box, following Cohen-Sutherland (cs) approach
template
<
    typename Range, typename Box,
    bool ReverseRange, bool ReverseBox,
    typename TurnPolicy
>
struct get_turns_cs
{
    typedef typename geometry::point_type<Range>::type range_point_type;
    typedef typename geometry::point_type<Box>::type box_point_type;
    typedef boost::array<box_point_type, 4> box_array;

    using view_type = detail::closed_clockwise_view
        <
            Range const,
            geometry::closure<Range>::value,
            ReverseRange ? counterclockwise : clockwise
        >;

    using iterator_type = typename boost::range_iterator<view_type const>::type;

    struct unique_sub_range_from_box_policy
    {
        typedef box_point_type point_type;

        unique_sub_range_from_box_policy(box_array const& box)
          : m_box(box)
          , m_index(0)
        {}

        static inline bool is_first_segment() { return false; }
        static inline bool is_last_segment() { return false; }
        static inline std::size_t size() { return 4; }

        inline box_point_type const& at(std::size_t index) const
        {
            BOOST_GEOMETRY_ASSERT(index < size());
            return m_box[(m_index + index) % 4];
        }

        inline void next()
        {
            m_index++;
        }

    private :
        box_array const& m_box;
        std::size_t m_index;
    };

    struct unique_sub_range_from_view_policy
    {
        typedef range_point_type point_type;

        unique_sub_range_from_view_policy(view_type const& view, point_type const& pi, point_type const& pj, iterator_type it)
          : m_view(view)
          , m_pi(pi)
          , m_pj(pj)
          , m_circular_iterator(boost::begin(view), boost::end(view), it, true)
        {
            ++m_circular_iterator;
        }

        static inline bool is_first_segment() { return false; }
        static inline bool is_last_segment() { return false; }
        static inline std::size_t size() { return 3; }

        inline point_type const& at(std::size_t index) const
        {
            BOOST_GEOMETRY_ASSERT(index < size());
            switch (index)
            {
                case 0 : return m_pi;
                case 1 : return m_pj;
                case 2 : return *m_circular_iterator;
                default : return m_pi;
            }
        }

    private :
        view_type const& m_view;
        point_type const& m_pi;
        point_type const& m_pj;
        ever_circling_iterator<iterator_type> m_circular_iterator;
    };

    template <typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(
                int source_id1, Range const& range,
                int source_id2, Box const& box,
                IntersectionStrategy const& intersection_strategy,
                RobustPolicy const& robust_policy,
                Turns& turns,
                InterruptPolicy& interrupt_policy,
                signed_size_type multi_index = -1,
                signed_size_type ring_index = -1)
    {
        if ( boost::size(range) <= 1)
        {
            return;
        }

        box_array box_points;
        assign_box_corners_oriented<ReverseBox>(box, box_points);

        view_type const view(range);

        // TODO: in this code, possible duplicate points are not yet taken
        // into account (not in the iterator, nor in the retrieve policy)
        iterator_type it = boost::begin(view);

        //bool first = true;

        //char previous_side[2] = {0, 0};

        signed_size_type index = 0;

        for (iterator_type prev = it++;
            it != boost::end(view);
            prev = it++, index++)
        {
            segment_identifier seg_id(source_id1,
                        multi_index, ring_index, index);

            unique_sub_range_from_view_policy view_unique_sub_range(view, *prev, *it, it);

            /*if (first)
            {
                previous_side[0] = get_side<0>(box, *prev);
                previous_side[1] = get_side<1>(box, *prev);
            }

            char current_side[2];
            current_side[0] = get_side<0>(box, *it);
            current_side[1] = get_side<1>(box, *it);

            // There can NOT be intersections if
            // 1) EITHER the two points are lying on one side of the box (! 0 && the same)
            // 2) OR same in Y-direction
            // 3) OR all points are inside the box (0)
            if (! (
                (current_side[0] != 0 && current_side[0] == previous_side[0])
                || (current_side[1] != 0 && current_side[1] == previous_side[1])
                || (current_side[0] == 0
                        && current_side[1] == 0
                        && previous_side[0] == 0
                        && previous_side[1] == 0)
                  )
                )*/
            if (true)
            {
                get_turns_with_box(seg_id, source_id2,
                        view_unique_sub_range,
                        box_points,
                        intersection_strategy,
                        robust_policy,
                        turns,
                        interrupt_policy);
                // Future performance enhancement:
                // return if told by the interrupt policy
            }
        }
    }

private:
    template<std::size_t Index, typename Point>
    static inline int get_side(Box const& box, Point const& point)
    {
        // Inside -> 0
        // Outside -> -1 (left/below) or 1 (right/above)
        // On border -> -2 (left/lower) or 2 (right/upper)
        // The only purpose of the value is to not be the same,
        // and to denote if it is inside (0)

        typename coordinate_type<Point>::type const& c = get<Index>(point);
        typename coordinate_type<Box>::type const& left = get<min_corner, Index>(box);
        typename coordinate_type<Box>::type const& right = get<max_corner, Index>(box);

        if (geometry::math::equals(c, left)) return -2;
        else if (geometry::math::equals(c, right)) return 2;
        else if (c < left) return -1;
        else if (c > right) return 1;
        else return 0;
    }

    template
    <
        typename IntersectionStrategy,
        typename Turns,
        typename InterruptPolicy,
        typename RobustPolicy
    >
    static inline void get_turns_with_box(segment_identifier const& seg_id, int source_id2,
            unique_sub_range_from_view_policy const& range_unique_sub_range,
            box_array const& box,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy,
            // Output
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        boost::ignore_unused(interrupt_policy);

        // Depending on code some relations can be left out

        typedef typename boost::range_value<Turns>::type turn_info;

        turn_info ti;
        ti.operations[0].seg_id = seg_id;

        unique_sub_range_from_box_policy box_unique_sub_range(box);
        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 0);
        TurnPolicy::apply(range_unique_sub_range, box_unique_sub_range,
                          ti, intersection_strategy, robust_policy,
                          std::back_inserter(turns));

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 1);
        box_unique_sub_range.next();
        TurnPolicy::apply(range_unique_sub_range, box_unique_sub_range,
                          ti, intersection_strategy, robust_policy,
                          std::back_inserter(turns));

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 2);
        box_unique_sub_range.next();
        TurnPolicy::apply(range_unique_sub_range, box_unique_sub_range,
                          ti, intersection_strategy, robust_policy,
                          std::back_inserter(turns));

        ti.operations[1].seg_id = segment_identifier(source_id2, -1, -1, 3);
        box_unique_sub_range.next();
        TurnPolicy::apply(range_unique_sub_range, box_unique_sub_range,
                          ti, intersection_strategy, robust_policy,
                          std::back_inserter(turns));

        if (InterruptPolicy::enabled)
        {
            interrupt_policy.apply(turns);
        }

    }

};


template
<
    typename Polygon, typename Box,
    bool Reverse, bool ReverseBox,
    typename TurnPolicy
>
struct get_turns_polygon_cs
{
    template <typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(
            int source_id1, Polygon const& polygon,
            int source_id2, Box const& box,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy,
            signed_size_type multi_index = -1)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        typedef detail::get_turns::get_turns_cs
            <
                ring_type, Box,
                Reverse, ReverseBox,
                TurnPolicy
            > intersector_type;

        intersector_type::apply(
                source_id1, geometry::exterior_ring(polygon),
                source_id2, box,
                intersection_strategy,
                robust_policy,
                turns,
                interrupt_policy,
                multi_index, -1);

        signed_size_type i = 0;

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(polygon);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it, ++i)
        {
            intersector_type::apply(
                    source_id1, *it,
                    source_id2, box,
                    intersection_strategy,
                    robust_policy,
                    turns, interrupt_policy,
                    multi_index, i);
        }

    }
};


template
<
    typename Multi, typename Box,
    bool Reverse, bool ReverseBox,
    typename TurnPolicy
>
struct get_turns_multi_polygon_cs
{
    template <typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(
            int source_id1, Multi const& multi,
            int source_id2, Box const& box,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        typedef typename boost::range_iterator
            <
                Multi const
            >::type iterator_type;

        signed_size_type i = 0;
        for (iterator_type it = boost::begin(multi);
             it != boost::end(multi);
             ++it, ++i)
        {
            // Call its single version
            get_turns_polygon_cs
                <
                    typename boost::range_value<Multi>::type, Box,
                    Reverse, ReverseBox,
                    TurnPolicy
                >::apply(source_id1, *it, source_id2, box,
                         intersection_strategy, robust_policy,
                         turns, interrupt_policy, i);
        }
    }
};


// GET_TURN_INFO_TYPE

template <typename Geometry>
struct topological_tag_base
{
    typedef typename tag_cast<typename tag<Geometry>::type, pointlike_tag, linear_tag, areal_tag>::type type;
};

template <typename Geometry1, typename Geometry2, typename AssignPolicy,
          typename Tag1 = typename tag<Geometry1>::type, typename Tag2 = typename tag<Geometry2>::type,
          typename TagBase1 = typename topological_tag_base<Geometry1>::type, typename TagBase2 = typename topological_tag_base<Geometry2>::type>
struct get_turn_info_type
    : overlay::get_turn_info<AssignPolicy>
{};

template <typename Geometry1, typename Geometry2, typename AssignPolicy, typename Tag1, typename Tag2>
struct get_turn_info_type<Geometry1, Geometry2, AssignPolicy, Tag1, Tag2, linear_tag, linear_tag>
    : overlay::get_turn_info_linear_linear<AssignPolicy>
{};

template <typename Geometry1, typename Geometry2, typename AssignPolicy, typename Tag1, typename Tag2>
struct get_turn_info_type<Geometry1, Geometry2, AssignPolicy, Tag1, Tag2, linear_tag, areal_tag>
    : overlay::get_turn_info_linear_areal<AssignPolicy>
{};

template <typename Geometry1, typename Geometry2, typename SegmentRatio,
          typename Tag1 = typename tag<Geometry1>::type, typename Tag2 = typename tag<Geometry2>::type,
          typename TagBase1 = typename topological_tag_base<Geometry1>::type, typename TagBase2 = typename topological_tag_base<Geometry2>::type>
struct turn_operation_type
{
    typedef overlay::turn_operation<typename point_type<Geometry1>::type, SegmentRatio> type;
};

template <typename Geometry1, typename Geometry2, typename SegmentRatio, typename Tag1, typename Tag2>
struct turn_operation_type<Geometry1, Geometry2, SegmentRatio, Tag1, Tag2, linear_tag, linear_tag>
{
    typedef overlay::turn_operation_linear<typename point_type<Geometry1>::type, SegmentRatio> type;
};

template <typename Geometry1, typename Geometry2, typename SegmentRatio, typename Tag1, typename Tag2>
struct turn_operation_type<Geometry1, Geometry2, SegmentRatio, Tag1, Tag2, linear_tag, areal_tag>
{
    typedef overlay::turn_operation_linear<typename point_type<Geometry1>::type, SegmentRatio> type;
};

}} // namespace detail::get_turns
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

// Because this is "detail" method, and most implementations will use "generic",
// we take the freedom to derive it from "generic".
template
<
    typename GeometryTag1, typename GeometryTag2,
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2,
    typename TurnPolicy
>
struct get_turns
    : detail::get_turns::get_turns_generic
        <
            Geometry1, Geometry2,
            Reverse1, Reverse2,
            TurnPolicy
        >
{};


template
<
    typename Polygon, typename Box,
    bool ReversePolygon, bool ReverseBox,
    typename TurnPolicy
>
struct get_turns
    <
        polygon_tag, box_tag,
        Polygon, Box,
        ReversePolygon, ReverseBox,
        TurnPolicy
    > : detail::get_turns::get_turns_polygon_cs
            <
                Polygon, Box,
                ReversePolygon, ReverseBox,
                TurnPolicy
            >
{};


template
<
    typename Ring, typename Box,
    bool ReverseRing, bool ReverseBox,
    typename TurnPolicy
>
struct get_turns
    <
        ring_tag, box_tag,
        Ring, Box,
        ReverseRing, ReverseBox,
        TurnPolicy
    > : detail::get_turns::get_turns_cs
            <
                Ring, Box, ReverseRing, ReverseBox,
                TurnPolicy
            >

{};


template
<
    typename MultiPolygon,
    typename Box,
    bool ReverseMultiPolygon, bool ReverseBox,
    typename TurnPolicy
>
struct get_turns
    <
        multi_polygon_tag, box_tag,
        MultiPolygon, Box,
        ReverseMultiPolygon, ReverseBox,
        TurnPolicy
    >
    : detail::get_turns::get_turns_multi_polygon_cs
        <
            MultiPolygon, Box,
            ReverseMultiPolygon, ReverseBox,
            TurnPolicy
        >
{};


template
<
    typename GeometryTag1, typename GeometryTag2,
    typename Geometry1, typename Geometry2,
    bool Reverse1, bool Reverse2,
    typename TurnPolicy
>
struct get_turns_reversed
{
    template <typename Strategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(int source_id1, Geometry1 const& g1,
                             int source_id2, Geometry2 const& g2,
                             Strategy const& strategy,
                             RobustPolicy const& robust_policy,
                             Turns& turns,
                             InterruptPolicy& interrupt_policy)
    {
        get_turns
            <
                GeometryTag2, GeometryTag1,
                Geometry2, Geometry1,
                Reverse2, Reverse1,
                TurnPolicy
            >::apply(source_id2, g2, source_id1, g1,
                     strategy, robust_policy,
                     turns, interrupt_policy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH



/*!
\brief \brief_calc2{turn points}
\ingroup overlay
\tparam Geometry1 \tparam_geometry
\tparam Geometry2 \tparam_geometry
\tparam Turns type of turn-container (e.g. vector of "intersection/turn point"'s)
\param geometry1 \param_geometry
\param geometry2 \param_geometry
\param intersection_strategy segments intersection strategy
\param robust_policy policy to handle robustness issues
\param turns container which will contain turn points
\param interrupt_policy policy determining if process is stopped
    when intersection is found
 */
template
<
    bool Reverse1, bool Reverse2,
    typename AssignPolicy,
    typename Geometry1,
    typename Geometry2,
    typename Strategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
inline void get_turns(Geometry1 const& geometry1,
                      Geometry2 const& geometry2,
                      Strategy const& strategy,
                      RobustPolicy const& robust_policy,
                      Turns& turns,
                      InterruptPolicy& interrupt_policy)
{
    concepts::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2 const>();

    typedef detail::overlay::get_turn_info<AssignPolicy> TurnPolicy;
    //typedef detail::get_turns::get_turn_info_type<Geometry1, Geometry2, AssignPolicy> TurnPolicy;

    std::conditional_t
        <
            reverse_dispatch<Geometry1, Geometry2>::type::value,
            dispatch::get_turns_reversed
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                TurnPolicy
            >,
            dispatch::get_turns
            <
                typename tag<Geometry1>::type,
                typename tag<Geometry2>::type,
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                TurnPolicy
            >
        >::apply(0, geometry1,
                 1, geometry2,
                 strategy,
                 robust_policy,
                 turns, interrupt_policy);
}

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_GET_TURNS_HPP

/* get_turns.hpp
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
*/