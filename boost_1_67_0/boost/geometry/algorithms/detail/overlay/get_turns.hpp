// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014, 2016, 2017, 2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

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
#include <boost/mpl/if.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>
#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/views/closeable_view.hpp>
#include <boost/geometry/views/reversible_view.hpp>
#include <boost/geometry/views/detail/range_type.hpp>

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/iterators/ever_circling_iterator.hpp>

#include <boost/geometry/strategies/intersection_strategies.hpp>
#include <boost/geometry/strategies/intersection_result.hpp>

#include <boost/geometry/algorithms/detail/disjoint/box_box.hpp>
#include <boost/geometry/algorithms/detail/disjoint/point_point.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/partition.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/algorithms/detail/sections/section_box_policies.hpp>

#include <boost/geometry/algorithms/detail/overlay/get_turn_info.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_ll.hpp>
#include <boost/geometry/algorithms/detail/overlay/get_turn_info_la.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>

#include <boost/geometry/algorithms/detail/sections/range_by_section.hpp>
#include <boost/geometry/algorithms/detail/sections/sectionalize.hpp>
#include <boost/geometry/algorithms/detail/sections/section_functions.hpp>

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
    typename IntersectionStrategy,
    typename RobustPolicy
>
struct unique_sub_range_from_section
{
    typedef Point point_type;

    unique_sub_range_from_section(Section const& section, signed_size_type index,
                          CircularIterator circular_iterator,
                          Point const& previous, Point const& current,
                          RobustPolicy const& robust_policy)
      : m_section(section)
      , m_index(index)
      , m_previous_point(previous)
      , m_current_point(current)
      , m_circular_iterator(circular_iterator)
      , m_point_retrieved(false)
      , m_robust_policy(robust_policy)
    {
    }

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
        typedef typename IntersectionStrategy::point_in_point_strategy_type disjoint_strategy_type;
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
        while(! detail::disjoint::disjoint_point_point
                (
                    current_robust_point, next_robust_point,
                    disjoint_strategy_type()
                )
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
    typedef typename closeable_view
        <
            typename range_type<Geometry1>::type const,
            closure<Geometry1>::value
        >::type cview_type1;
    typedef typename closeable_view
        <
            typename range_type<Geometry2>::type const,
            closure<Geometry2>::value
        >::type cview_type2;

    typedef typename reversible_view
        <
            cview_type1 const,
            Reverse1 ? iterate_reverse : iterate_forward
        >::type view_type1;
    typedef typename reversible_view
        <
            cview_type2 const,
            Reverse2 ? iterate_reverse : iterate_forward
        >::type view_type2;

    typedef typename boost::range_iterator
        <
            view_type1 const
        >::type range1_iterator;

    typedef typename boost::range_iterator
        <
            view_type2 const
        >::type range2_iterator;

    typedef ever_circling_iterator<range1_iterator> circular1_iterator;
    typedef ever_circling_iterator<range2_iterator> circular2_iterator;

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

        return boost::is_same
                    <
                        typename tag_cast
                            <
                                typename geometry::tag<Geometry>::type,
                                areal_tag
                            >::type,
                        areal_tag
                    >::value
               && index1 == 0
               && index2 >= n - 2
                ;
    }


public :
    // Returns true if terminated, false if interrupted
    template <typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline bool apply(
            int source_id1, Geometry1 const& geometry1, Section1 const& sec1,
            int source_id2, Geometry2 const& geometry2, Section2 const& sec2,
            bool skip_larger, bool skip_adjacent,
            IntersectionStrategy const& intersection_strategy,
            RobustPolicy const& robust_policy,
            Turns& turns,
            InterruptPolicy& interrupt_policy)
    {
        boost::ignore_unused(interrupt_policy);

        static bool const areal1 = boost::is_same
            <
                typename tag_cast<typename tag<Geometry1>::type, areal_tag>::type,
                areal_tag
            >::type::value;
        static bool const areal2 = boost::is_same
            <
                typename tag_cast<typename tag<Geometry2>::type, areal_tag>::type,
                areal_tag
            >::type::value;


        if ((sec1.duplicate && (sec1.count + 1) < sec1.range_count)
           || (sec2.duplicate && (sec2.count + 1) < sec2.range_count))
        {
            // Skip sections containig only duplicates.
            // They are still important (can indicate non-disjointness)
            // but they will be found processing adjacent sections.
            // Do NOT skip if they are the ONLY section
            return true;
        }

        cview_type1 cview1(range_by_section(geometry1, sec1));
        cview_type2 cview2(range_by_section(geometry2, sec2));
        view_type1 view1(cview1);
        view_type2 view2(cview2);

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
        ever_circling_iterator<range1_iterator> next1(begin_range_1, end_range_1, it1, true);
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
                    IntersectionStrategy, RobustPolicy
                > unique_sub_range1(sec1, index1,
                                    circular1_iterator(begin_range_1, end_range_1, next1, true),
                                    *prev1, *it1,
                                    robust_policy);

            signed_size_type index2 = sec2.begin_index;
            signed_size_type ndi2 = sec2.non_duplicate_index;

            range2_iterator prev2, it2, end2;

            get_start_point_iterator(sec2, view2, prev2, it2, end2,
                        index2, ndi2, dir2, sec1.bounding_box, robust_policy);
            ever_circling_iterator<range2_iterator> next2(begin_range_2, end_range_2, it2, true);
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
                            IntersectionStrategy, RobustPolicy
                        > unique_sub_range2(sec2, index2,
                                            circular2_iterator(begin_range_2, end_range_2, next2),
                                            *prev2, *it2,
                                            robust_policy);

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
                                      ti, intersection_strategy, robust_policy,
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
    typedef typename model::referring_segment<point1_type const> segment1_type;
    typedef typename model::referring_segment<point2_type const> segment2_type;

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
    typename IntersectionStrategy,
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
    IntersectionStrategy const& m_intersection_strategy;
    RobustPolicy const& m_rescale_policy;
    Turns& m_turns;
    InterruptPolicy& m_interrupt_policy;

    section_visitor(int id1, Geometry1 const& g1,
                    int id2, Geometry2 const& g2,
                    IntersectionStrategy const& intersection_strategy,
                    RobustPolicy const& robust_policy,
                    Turns& turns,
                    InterruptPolicy& ip)
        : m_source_id1(id1), m_geometry1(g1)
        , m_source_id2(id2), m_geometry2(g2)
        , m_intersection_strategy(intersection_strategy)
        , m_rescale_policy(robust_policy)
        , m_turns(turns)
        , m_interrupt_policy(ip)
    {}

    template <typename Section>
    inline bool apply(Section const& sec1, Section const& sec2)
    {
        if (! detail::disjoint::disjoint_box_box(sec1.bounding_box,
                                                 sec2.bounding_box,
                                                 m_intersection_strategy.get_disjoint_box_box_strategy()))
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
                             m_intersection_strategy,
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
    template <typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(
            int source_id1, Geometry1 const& geometry1,
            int source_id2, Geometry2 const& geometry2,
            IntersectionStrategy const& intersection_strategy,
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
        typedef boost::mpl::vector_c<std::size_t, 0, 1> dimensions;

        typename IntersectionStrategy::envelope_strategy_type const
            envelope_strategy = intersection_strategy.get_envelope_strategy();
        typename IntersectionStrategy::expand_strategy_type const
            expand_strategy = intersection_strategy.get_expand_strategy();

        geometry::sectionalize<Reverse1, dimensions>(geometry1, robust_policy,
                sec1, envelope_strategy, expand_strategy, 0);
        geometry::sectionalize<Reverse2, dimensions>(geometry2, robust_policy,
                sec2, envelope_strategy, expand_strategy, 1);

        // ... and then partition them, intersecting overlapping sections in visitor method
        section_visitor
            <
                Geometry1, Geometry2,
                Reverse1, Reverse2,
                TurnPolicy,
                IntersectionStrategy, RobustPolicy,
                Turns, InterruptPolicy
            > visitor(source_id1, geometry1, source_id2, geometry2,
                      intersection_strategy, robust_policy,
                      turns, interrupt_policy);

        typedef detail::section::get_section_box
            <
                typename IntersectionStrategy::expand_box_strategy_type
            > get_section_box_type;
        typedef detail::section::overlaps_section_box
            <
                typename IntersectionStrategy::disjoint_box_box_strategy_type
            > overlaps_section_box_type;

        geometry::partition
            <
                box_type
            >::apply(sec1, sec2, visitor,
                     get_section_box_type(),
                     overlaps_section_box_type());
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

    typedef typename closeable_view
        <
            Range const,
            closure<Range>::value
        >::type cview_type;

    typedef typename reversible_view
        <
            cview_type const,
            ReverseRange ? iterate_reverse : iterate_forward
        >::type view_type;

    typedef typename boost::range_iterator
        <
            view_type const
        >::type iterator_type;

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

        cview_type cview(range);
        view_type view(cview);

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
    template <typename IntersectionStrategy, typename RobustPolicy, typename Turns, typename InterruptPolicy>
    static inline void apply(int source_id1, Geometry1 const& g1,
                             int source_id2, Geometry2 const& g2,
                             IntersectionStrategy const& intersection_strategy,
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
                     intersection_strategy, robust_policy,
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
    typename IntersectionStrategy,
    typename RobustPolicy,
    typename Turns,
    typename InterruptPolicy
>
inline void get_turns(Geometry1 const& geometry1,
                      Geometry2 const& geometry2,
                      IntersectionStrategy const& intersection_strategy,
                      RobustPolicy const& robust_policy,
                      Turns& turns,
                      InterruptPolicy& interrupt_policy)
{
    concepts::check_concepts_and_equal_dimensions<Geometry1 const, Geometry2 const>();

    typedef detail::overlay::get_turn_info<AssignPolicy> TurnPolicy;
    //typedef detail::get_turns::get_turn_info_type<Geometry1, Geometry2, AssignPolicy> TurnPolicy;

    boost::mpl::if_c
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
        >::type::apply(0, geometry1,
                       1, geometry2,
                       intersection_strategy,
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