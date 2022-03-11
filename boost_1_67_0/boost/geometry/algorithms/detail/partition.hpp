// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2015-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_PARTITION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_PARTITION_HPP

#include <cstddef>
#include <vector>
#include <boost/range.hpp>
#include <boost/type_traits/is_integral.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/algorithms/assign.hpp>


namespace boost { namespace geometry
{

namespace detail { namespace partition
{

template <typename T, bool IsIntegral = boost::is_integral<T>::value>
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