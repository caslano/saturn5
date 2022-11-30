// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_PARTITION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_PARTITION_HPP


#include <cstddef>
#include <type_traits>
#include <vector>

#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace partition
{

template <typename T, bool IsIntegral = std::is_integral<T>::value>
struct divide_interval
{
    static inline T apply(T const& mi, T const& ma)
    {
        static T const two = 2;
        return (mi + ma) / two;
    }
};

template <typename T>
struct divide_interval<T, true>
{
    static inline T apply(T const& mi, T const& ma)
    {
        // avoid overflow
        return mi / 2 + ma / 2 + (mi % 2 + ma % 2) / 2;
    }
};

template <int Dimension, typename Box>
inline void divide_box(Box const& box, Box& lower_box, Box& upper_box)
{
    typedef typename coordinate_type<Box>::type ctype;

    // Divide input box into two parts, e.g. left/right
    ctype mid = divide_interval<ctype>::apply(
                    geometry::get<min_corner, Dimension>(box),
                    geometry::get<max_corner, Dimension>(box));

    lower_box = box;
    upper_box = box;
    geometry::set<max_corner, Dimension>(lower_box, mid);
    geometry::set<min_corner, Dimension>(upper_box, mid);
}

// Divide forward_range into three subsets: lower, upper and oversized
// (not-fitting)
// (lower == left or bottom, upper == right or top)
template <typename Box, typename IteratorVector, typename OverlapsPolicy>
inline void divide_into_subsets(Box const& lower_box,
                                Box const& upper_box,
                                IteratorVector const& input,
                                IteratorVector& lower,
                                IteratorVector& upper,
                                IteratorVector& exceeding,
                                OverlapsPolicy const& overlaps_policy)
{
    typedef typename boost::range_iterator
        <
            IteratorVector const
        >::type it_type;

    for(it_type it = boost::begin(input); it != boost::end(input); ++it)
    {
        bool const lower_overlapping = overlaps_policy.apply(lower_box, **it);
        bool const upper_overlapping = overlaps_policy.apply(upper_box, **it);

        if (lower_overlapping && upper_overlapping)
        {
            exceeding.push_back(*it);
        }
        else if (lower_overlapping)
        {
            lower.push_back(*it);
        }
        else if (upper_overlapping)
        {
            upper.push_back(*it);
        }
        else
        {
            // Is nowhere. That is (since 1.58) possible, it might be
            // skipped by the OverlapsPolicy to enhance performance
        }
    }
}

template
<
    typename Box,
    typename IteratorVector,
    typename ExpandPolicy
>
inline void expand_with_elements(Box& total, IteratorVector const& input,
                                 ExpandPolicy const& expand_policy)
{
    typedef typename boost::range_iterator<IteratorVector const>::type it_type;
    for(it_type it = boost::begin(input); it != boost::end(input); ++it)
    {
        expand_policy.apply(total, **it);
    }
}


// Match forward_range with itself
template <typename IteratorVector, typename VisitPolicy>
inline bool handle_one(IteratorVector const& input, VisitPolicy& visitor)
{
    if (boost::empty(input))
    {
        return true;
    }

    typedef typename boost::range_iterator<IteratorVector const>::type it_type;

    // Quadratic behaviour at lowest level (lowest quad, or all exceeding)
    for (it_type it1 = boost::begin(input); it1 != boost::end(input); ++it1)
    {
        it_type it2 = it1;
        for (++it2; it2 != boost::end(input); ++it2)
        {
            if (! visitor.apply(**it1, **it2))
            {
                return false; // interrupt
            }
        }
    }

    return true;
}

// Match forward range 1 with forward range 2
template
<
    typename IteratorVector1,
    typename IteratorVector2,
    typename VisitPolicy
>
inline bool handle_two(IteratorVector1 const& input1,
                       IteratorVector2 const& input2,
                       VisitPolicy& visitor)
{
    typedef typename boost::range_iterator
        <
            IteratorVector1 const
        >::type iterator_type1;

    typedef typename boost::range_iterator
        <
            IteratorVector2 const
        >::type iterator_type2;

    if (boost::empty(input1) || boost::empty(input2))
    {
        return true;
    }

    for(iterator_type1 it1 = boost::begin(input1);
        it1 != boost::end(input1);
        ++it1)
    {
        for(iterator_type2 it2 = boost::begin(input2);
            it2 != boost::end(input2);
            ++it2)
        {
            if (! visitor.apply(**it1, **it2))
            {
                return false; // interrupt
            }
        }
    }

    return true;
}

template <typename IteratorVector>
inline bool recurse_ok(IteratorVector const& input,
                       std::size_t min_elements, std::size_t level)
{
    return boost::size(input) >= min_elements
        && level < 100;
}

template <typename IteratorVector1, typename IteratorVector2>
inline bool recurse_ok(IteratorVector1 const& input1,
                       IteratorVector2 const& input2,
                       std::size_t min_elements, std::size_t level)
{
    return boost::size(input1) >= min_elements
        && recurse_ok(input2, min_elements, level);
}

template
<
    typename IteratorVector1,
    typename IteratorVector2,
    typename IteratorVector3
>
inline bool recurse_ok(IteratorVector1 const& input1,
                       IteratorVector2 const& input2,
                       IteratorVector3 const& input3,
                       std::size_t min_elements, std::size_t level)
{
    return boost::size(input1) >= min_elements
        && recurse_ok(input2, input3, min_elements, level);
}


template <int Dimension, typename Box>
class partition_two_ranges;


template <int Dimension, typename Box>
class partition_one_range
{
    template <typename IteratorVector, typename ExpandPolicy>
    static inline Box get_new_box(IteratorVector const& input,
                                  ExpandPolicy const& expand_policy)
    {
        Box box;
        geometry::assign_inverse(box);
        expand_with_elements(box, input, expand_policy);
        return box;
    }

    template
    <
        typename IteratorVector,
        typename VisitPolicy,
        typename ExpandPolicy,
        typename OverlapsPolicy,
        typename VisitBoxPolicy
    >
    static inline bool next_level(Box const& box,
                                  IteratorVector const& input,
                                  std::size_t level, std::size_t min_elements,
                                  VisitPolicy& visitor,
                                  ExpandPolicy const& expand_policy,
                                  OverlapsPolicy const& overlaps_policy,
                                  VisitBoxPolicy& box_policy)
    {
        if (recurse_ok(input, min_elements, level))
        {
            return partition_one_range
                <
                    1 - Dimension,
                    Box
                >::apply(box, input, level + 1, min_elements,
                         visitor, expand_policy, overlaps_policy, box_policy);
        }
        else
        {
            return handle_one(input, visitor);
        }
    }

    // Function to switch to two forward ranges if there are
    // geometries exceeding the separation line
    template
    <
        typename IteratorVector,
        typename VisitPolicy,
        typename ExpandPolicy,
        typename OverlapsPolicy,
        typename VisitBoxPolicy
    >
    static inline bool next_level2(Box const& box,
                                   IteratorVector const& input1,
                                   IteratorVector const& input2,
                                   std::size_t level, std::size_t min_elements,
                                   VisitPolicy& visitor,
                                   ExpandPolicy const& expand_policy,
                                   OverlapsPolicy const& overlaps_policy,
                                   VisitBoxPolicy& box_policy)
    {
        if (recurse_ok(input1, input2, min_elements, level))
        {
            return partition_two_ranges
                <
                    1 - Dimension, Box
                >::apply(box, input1, input2, level + 1, min_elements,
                         visitor, expand_policy, overlaps_policy,
                         expand_policy, overlaps_policy, box_policy);
        }
        else
        {
            return handle_two(input1, input2, visitor);
        }
    }

public :
    template
    <
        typename IteratorVector,
        typename VisitPolicy,
        typename ExpandPolicy,
        typename OverlapsPolicy,
        typename VisitBoxPolicy
    >
    static inline bool apply(Box const& box,
                             IteratorVector const& input,
                             std::size_t level,
                             std::size_t min_elements,
                             VisitPolicy& visitor,
                             ExpandPolicy const& expand_policy,
                             OverlapsPolicy const& overlaps_policy,
                             VisitBoxPolicy& box_policy)
    {
        box_policy.apply(box, level);

        Box lower_box, upper_box;
        divide_box<Dimension>(box, lower_box, upper_box);

        IteratorVector lower, upper, exceeding;
        divide_into_subsets(lower_box, upper_box,
                            input, lower, upper, exceeding,
                            overlaps_policy);

        if (! boost::empty(exceeding))
        {
            // Get the box of exceeding-only
            Box exceeding_box = get_new_box(exceeding, expand_policy);

                   // Recursively do exceeding elements only, in next dimension they
                   // will probably be less exceeding within the new box
            if (! (next_level(exceeding_box, exceeding, level, min_elements,
                              visitor, expand_policy, overlaps_policy, box_policy)
                   // Switch to two forward ranges, combine exceeding with
                   // lower resp upper, but not lower/lower, upper/upper
                && next_level2(exceeding_box, exceeding, lower, level, min_elements,
                               visitor, expand_policy, overlaps_policy, box_policy)
                && next_level2(exceeding_box, exceeding, upper, level, min_elements,
                               visitor, expand_policy, overlaps_policy, box_policy)) )
            {
                return false; // interrupt
            }
        }

        // Recursively call operation both parts
        return next_level(lower_box, lower, level, min_elements,
                          visitor, expand_policy, overlaps_policy, box_policy)
            && next_level(upper_box, upper, level, min_elements,
                          visitor, expand_policy, overlaps_policy, box_policy);
    }
};

template
<
    int Dimension,
    typename Box
>
class partition_two_ranges
{
    template
    <
        typename IteratorVector1,
        typename IteratorVector2,
        typename VisitPolicy,
        typename ExpandPolicy1,
        typename OverlapsPolicy1,
        typename ExpandPolicy2,
        typename OverlapsPolicy2,
        typename VisitBoxPolicy
    >
    static inline bool next_level(Box const& box,
                                  IteratorVector1 const& input1,
                                  IteratorVector2 const& input2,
                                  std::size_t level, std::size_t min_elements,
                                  VisitPolicy& visitor,
                                  ExpandPolicy1 const& expand_policy1,
                                  OverlapsPolicy1 const& overlaps_policy1,
                                  ExpandPolicy2 const& expand_policy2,
                                  OverlapsPolicy2 const& overlaps_policy2,
                                  VisitBoxPolicy& box_policy)
    {
        return partition_two_ranges
            <
                1 - Dimension, Box
            >::apply(box, input1, input2, level + 1, min_elements,
                     visitor, expand_policy1, overlaps_policy1,
                     expand_policy2, overlaps_policy2, box_policy);
    }

    template <typename IteratorVector, typename ExpandPolicy>
    static inline Box get_new_box(IteratorVector const& input,
                                  ExpandPolicy const& expand_policy)
    {
        Box box;
        geometry::assign_inverse(box);
        expand_with_elements(box, input, expand_policy);
        return box;
    }

    template
    <
        typename IteratorVector1, typename IteratorVector2,
        typename ExpandPolicy1, typename ExpandPolicy2
    >
    static inline Box get_new_box(IteratorVector1 const& input1,
                                  IteratorVector2 const& input2,
                                  ExpandPolicy1 const& expand_policy1,
                                  ExpandPolicy2 const& expand_policy2)
    {
        Box box = get_new_box(input1, expand_policy1);
        expand_with_elements(box, input2, expand_policy2);
        return box;
    }

public :
    template
    <
        typename IteratorVector1,
        typename IteratorVector2,
        typename VisitPolicy,
        typename ExpandPolicy1,
        typename OverlapsPolicy1,
        typename ExpandPolicy2,
        typename OverlapsPolicy2,
        typename VisitBoxPolicy
    >
    static inline bool apply(Box const& box,
                             IteratorVector1 const& input1,
                             IteratorVector2 const& input2,
                             std::size_t level,
                             std::size_t min_elements,
                             VisitPolicy& visitor,
                             ExpandPolicy1 const& expand_policy1,
                             OverlapsPolicy1 const& overlaps_policy1,
                             ExpandPolicy2 const& expand_policy2,
                             OverlapsPolicy2 const& overlaps_policy2,
                             VisitBoxPolicy& box_policy)
    {
        box_policy.apply(box, level);

        Box lower_box, upper_box;
        divide_box<Dimension>(box, lower_box, upper_box);

        IteratorVector1 lower1, upper1, exceeding1;
        IteratorVector2 lower2, upper2, exceeding2;
        divide_into_subsets(lower_box, upper_box,
                            input1, lower1, upper1, exceeding1,
                            overlaps_policy1);
        divide_into_subsets(lower_box, upper_box,
                            input2, lower2, upper2, exceeding2,
                            overlaps_policy2);

        if (! boost::empty(exceeding1))
        {
            // All exceeding from 1 with 2:

            if (recurse_ok(exceeding1, exceeding2, min_elements, level))
            {
                Box exceeding_box = get_new_box(exceeding1, exceeding2,
                                                expand_policy1, expand_policy2);
                if (! next_level(exceeding_box, exceeding1, exceeding2, level,
                                 min_elements, visitor, expand_policy1, overlaps_policy1,
                                 expand_policy2, overlaps_policy2, box_policy))
                {
                    return false; // interrupt
                }
            }
            else
            {
                if (! handle_two(exceeding1, exceeding2, visitor))
                {
                    return false; // interrupt
                }
            }

            // All exceeding from 1 with lower and upper of 2:

            // (Check sizes of all three forward ranges to avoid recurse into
            // the same combinations again and again)
            if (recurse_ok(lower2, upper2, exceeding1, min_elements, level))
            {
                Box exceeding_box = get_new_box(exceeding1, expand_policy1);
                if (! (next_level(exceeding_box, exceeding1, lower2, level,
                                  min_elements, visitor, expand_policy1, overlaps_policy1,
                                  expand_policy2, overlaps_policy2, box_policy)
                    && next_level(exceeding_box, exceeding1, upper2, level,
                                  min_elements, visitor, expand_policy1, overlaps_policy1,
                                  expand_policy2, overlaps_policy2, box_policy)) )
                {
                    return false; // interrupt
                }
            }
            else
            {
                if (! (handle_two(exceeding1, lower2, visitor)
                    && handle_two(exceeding1, upper2, visitor)) )
                {
                    return false; // interrupt
                }
            }
        }

        if (! boost::empty(exceeding2))
        {
            // All exceeding from 2 with lower and upper of 1:
            if (recurse_ok(lower1, upper1, exceeding2, min_elements, level))
            {
                Box exceeding_box = get_new_box(exceeding2, expand_policy2);
                if (! (next_level(exceeding_box, lower1, exceeding2, level,
                                  min_elements, visitor, expand_policy1, overlaps_policy1,
                                  expand_policy2, overlaps_policy2, box_policy)
                    && next_level(exceeding_box, upper1, exceeding2, level,
                                  min_elements, visitor, expand_policy1, overlaps_policy1,
                                  expand_policy2, overlaps_policy2, box_policy)) )
                {
                    return false; // interrupt
                }
            }
            else
            {
                if (! (handle_two(lower1, exceeding2, visitor)
                    && handle_two(upper1, exceeding2, visitor)) )
                {
                    return false; // interrupt
                }
            }
        }

        if (recurse_ok(lower1, lower2, min_elements, level))
        {
            if (! next_level(lower_box, lower1, lower2, level,
                             min_elements, visitor, expand_policy1, overlaps_policy1,
                             expand_policy2, overlaps_policy2, box_policy) )
            {
                return false; // interrupt
            }
        }
        else
        {
            if (! handle_two(lower1, lower2, visitor))
            {
                return false; // interrupt
            }
        }

        if (recurse_ok(upper1, upper2, min_elements, level))
        {
            if (! next_level(upper_box, upper1, upper2, level,
                             min_elements, visitor, expand_policy1, overlaps_policy1,
                             expand_policy2, overlaps_policy2, box_policy) )
            {
                return false; // interrupt
            }
        }
        else
        {
            if (! handle_two(upper1, upper2, visitor))
            {
                return false; // interrupt
            }
        }

        return true;
    }
};

struct visit_no_policy
{
    template <typename Box>
    static inline void apply(Box const&, std::size_t )
    {}
};

struct include_all_policy
{
    template <typename Item>
    static inline bool apply(Item const&)
    {
        return true;
    }
};


}} // namespace detail::partition

template
<
    typename Box,
    typename IncludePolicy1 = detail::partition::include_all_policy,
    typename IncludePolicy2 = detail::partition::include_all_policy
>
class partition
{
    static const std::size_t default_min_elements = 16;

    template
    <
        typename IncludePolicy,
        typename ForwardRange,
        typename IteratorVector,
        typename ExpandPolicy
    >
    static inline void expand_to_range(ForwardRange const& forward_range,
                                       Box& total,
                                       IteratorVector& iterator_vector,
                                       ExpandPolicy const& expand_policy)
    {
        for(typename boost::range_iterator<ForwardRange const>::type
                it = boost::begin(forward_range);
            it != boost::end(forward_range);
            ++it)
        {
            if (IncludePolicy::apply(*it))
            {
                expand_policy.apply(total, *it);
                iterator_vector.push_back(it);
            }
        }
    }

public:
    template
    <
        typename ForwardRange,
        typename VisitPolicy,
        typename ExpandPolicy,
        typename OverlapsPolicy
    >
    static inline bool apply(ForwardRange const& forward_range,
                             VisitPolicy& visitor,
                             ExpandPolicy const& expand_policy,
                             OverlapsPolicy const& overlaps_policy)
    {
        return apply(forward_range, visitor, expand_policy, overlaps_policy,
                     default_min_elements, detail::partition::visit_no_policy());
    }

    template
    <
        typename ForwardRange,
        typename VisitPolicy,
        typename ExpandPolicy,
        typename OverlapsPolicy
    >
    static inline bool apply(ForwardRange const& forward_range,
                             VisitPolicy& visitor,
                             ExpandPolicy const& expand_policy,
                             OverlapsPolicy const& overlaps_policy,
                             std::size_t min_elements)
    {
        return apply(forward_range, visitor, expand_policy, overlaps_policy,
                     min_elements, detail::partition::visit_no_policy());
    }

    template
    <
        typename ForwardRange,
        typename VisitPolicy,
        typename ExpandPolicy,
        typename OverlapsPolicy,
        typename VisitBoxPolicy
    >
    static inline bool apply(ForwardRange const& forward_range,
                             VisitPolicy& visitor,
                             ExpandPolicy const& expand_policy,
                             OverlapsPolicy const& overlaps_policy,
                             std::size_t min_elements,
                             VisitBoxPolicy box_visitor)
    {
        typedef typename boost::range_iterator
            <
                ForwardRange const
            >::type iterator_type;

        if (std::size_t(boost::size(forward_range)) > min_elements)
        {
            std::vector<iterator_type> iterator_vector;
            Box total;
            assign_inverse(total);
            expand_to_range<IncludePolicy1>(forward_range, total,
                                            iterator_vector, expand_policy);

            return detail::partition::partition_one_range
                <
                    0, Box
                >::apply(total, iterator_vector, 0, min_elements,
                         visitor, expand_policy, overlaps_policy, box_visitor);
        }
        else
        {
            for(iterator_type it1 = boost::begin(forward_range);
                it1 != boost::end(forward_range);
                ++it1)
            {
                iterator_type it2 = it1;
                for(++it2; it2 != boost::end(forward_range); ++it2)
                {
                    if (! visitor.apply(*it1, *it2))
                    {
                        return false; // interrupt
                    }
                }
            }
        }

        return true;
    }

    template
    <
        typename ForwardRange1,
        typename ForwardRange2,
        typename VisitPolicy,
        typename ExpandPolicy1,
        typename OverlapsPolicy1
    >
    static inline bool apply(ForwardRange1 const& forward_range1,
                             ForwardRange2 const& forward_range2,
                             VisitPolicy& visitor,
                             ExpandPolicy1 const& expand_policy1,
                             OverlapsPolicy1 const& overlaps_policy1)
    {
        return apply(forward_range1, forward_range2, visitor,
                     expand_policy1, overlaps_policy1, expand_policy1, overlaps_policy1,
                     default_min_elements, detail::partition::visit_no_policy());
    }

    template
    <
        typename ForwardRange1,
        typename ForwardRange2,
        typename VisitPolicy,
        typename ExpandPolicy1,
        typename OverlapsPolicy1,
        typename ExpandPolicy2,
        typename OverlapsPolicy2
    >
    static inline bool apply(ForwardRange1 const& forward_range1,
                             ForwardRange2 const& forward_range2,
                             VisitPolicy& visitor,
                             ExpandPolicy1 const& expand_policy1,
                             OverlapsPolicy1 const& overlaps_policy1,
                             ExpandPolicy2 const& expand_policy2,
                             OverlapsPolicy2 const& overlaps_policy2)
    {
        return apply(forward_range1, forward_range2, visitor,
                     expand_policy1, overlaps_policy1, expand_policy2, overlaps_policy2,
                     default_min_elements, detail::partition::visit_no_policy());
    }

    template
    <
        typename ForwardRange1,
        typename ForwardRange2,
        typename VisitPolicy,
        typename ExpandPolicy1,
        typename OverlapsPolicy1,
        typename ExpandPolicy2,
        typename OverlapsPolicy2
    >
    static inline bool apply(ForwardRange1 const& forward_range1,
                             ForwardRange2 const& forward_range2,
                             VisitPolicy& visitor,
                             ExpandPolicy1 const& expand_policy1,
                             OverlapsPolicy1 const& overlaps_policy1,
                             ExpandPolicy2 const& expand_policy2,
                             OverlapsPolicy2 const& overlaps_policy2,
                             std::size_t min_elements)
    {
        return apply(forward_range1, forward_range2, visitor,
                     expand_policy1, overlaps_policy1, expand_policy2, overlaps_policy2,
                     min_elements, detail::partition::visit_no_policy());
    }

    template
    <
        typename ForwardRange1,
        typename ForwardRange2,
        typename VisitPolicy,
        typename ExpandPolicy1,
        typename OverlapsPolicy1,
        typename ExpandPolicy2,
        typename OverlapsPolicy2,
        typename VisitBoxPolicy
    >
    static inline bool apply(ForwardRange1 const& forward_range1,
                             ForwardRange2 const& forward_range2,
                             VisitPolicy& visitor,
                             ExpandPolicy1 const& expand_policy1,
                             OverlapsPolicy1 const& overlaps_policy1,
                             ExpandPolicy2 const& expand_policy2,
                             OverlapsPolicy2 const& overlaps_policy2,
                             std::size_t min_elements,
                             VisitBoxPolicy box_visitor)
    {
        typedef typename boost::range_iterator
            <
                ForwardRange1 const
            >::type iterator_type1;

        typedef typename boost::range_iterator
            <
                ForwardRange2 const
            >::type iterator_type2;

        if (std::size_t(boost::size(forward_range1)) > min_elements
            && std::size_t(boost::size(forward_range2)) > min_elements)
        {
            std::vector<iterator_type1> iterator_vector1;
            std::vector<iterator_type2> iterator_vector2;
            Box total;
            assign_inverse(total);
            expand_to_range<IncludePolicy1>(forward_range1, total,
                                            iterator_vector1, expand_policy1);
            expand_to_range<IncludePolicy2>(forward_range2, total,
                                            iterator_vector2, expand_policy2);

            return detail::partition::partition_two_ranges
                <
                    0, Box
                >::apply(total, iterator_vector1, iterator_vector2,
                         0, min_elements, visitor, expand_policy1,
                         overlaps_policy1, expand_policy2, overlaps_policy2,
                         box_visitor);
        }
        else
        {
            for(iterator_type1 it1 = boost::begin(forward_range1);
                it1 != boost::end(forward_range1);
                ++it1)
            {
                for(iterator_type2 it2 = boost::begin(forward_range2);
                    it2 != boost::end(forward_range2);
                    ++it2)
                {
                    if (! visitor.apply(*it1, *it2))
                    {
                        return false; // interrupt
                    }
                }
            }
        }

        return true;
    }
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_PARTITION_HPP

/* partition.hpp
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
*/