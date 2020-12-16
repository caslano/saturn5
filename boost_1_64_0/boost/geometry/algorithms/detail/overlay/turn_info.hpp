// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TURN_INFO_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TURN_INFO_HPP


#include <boost/array.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/segment_identifier.hpp>
#include <boost/geometry/algorithms/detail/overlay/overlay_type.hpp>
#include <boost/geometry/policies/robustness/segment_ratio.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

enum method_type
{
    method_none,
    method_disjoint,
    method_crosses,
    method_touch,
    method_touch_interior,
    method_collinear,
    method_equal,
    method_error
};


/*!
    \brief Turn operation: operation
    \details Information necessary for traversal phase (a phase
        of the overlay process). The information is gathered during the
        get_turns (segment intersection) phase.
        The class is to be included in the turn_info class, either direct
        or a derived or similar class with more (e.g. enrichment) information.
 */
template <typename Point, typename SegmentRatio>
struct turn_operation
{
    typedef SegmentRatio segment_ratio_type;

    operation_type operation;
    segment_identifier seg_id;
    SegmentRatio fraction;

    typedef typename coordinate_type<Point>::type comparable_distance_type;
    comparable_distance_type remaining_distance;

    inline turn_operation()
        : operation(operation_none)
        , remaining_distance(0)
    {}
};


/*!
    \brief Turn information: intersection point, method, and turn information
    \details Information necessary for traversal phase (a phase
        of the overlay process). The information is gathered during the
        get_turns (segment intersection) phase.
    \tparam Point point type of intersection point
    \tparam Operation gives classes opportunity to add additional info
    \tparam Container gives classes opportunity to define how operations are stored
 */
template
<
    typename Point,
    typename SegmentRatio = geometry::segment_ratio<typename coordinate_type<Point>::type>,
    typename Operation = turn_operation<Point, SegmentRatio>,
    typename Container = boost::array<Operation, 2>
>
struct turn_info
{
    typedef Point point_type;
    typedef SegmentRatio segment_ratio_type;
    typedef Operation turn_operation_type;
    typedef Container container_type;

    Point point;
    method_type method;
    bool touch_only; // True in case of method touch(interior) and lines do not cross
    signed_size_type cluster_id; // For multiple turns on same location, > 0. Else -1. 0 is unused.
    bool discarded;
    bool has_colocated_both; // Colocated with a uu turn (for union) or ii (other)

    Container operations;

    inline turn_info()
        : method(method_none)
        , touch_only(false)
        , cluster_id(-1)
        , discarded(false)
        , has_colocated_both(false)
    {}

    inline bool both(operation_type type) const
    {
        return has12(type, type);
    }

    inline bool has(operation_type type) const
    {
        return this->operations[0].operation == type
            || this->operations[1].operation == type;
    }

    inline bool combination(operation_type type1, operation_type type2) const
    {
        return has12(type1, type2) || has12(type2, type1);
    }

    inline bool blocked() const
    {
        return both(operation_blocked);
    }
    inline bool opposite() const
    {
        return both(operation_opposite);
    }
    inline bool any_blocked() const
    {
        return has(operation_blocked);
    }
    inline bool is_clustered() const
    {
        return cluster_id > 0;
    }

private :
    inline bool has12(operation_type type1, operation_type type2) const
    {
        return this->operations[0].operation == type1
            && this->operations[1].operation == type2
            ;
    }

};


}} // namespace detail::overlay
#endif //DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_TURN_INFO_HPP

/* turn_info.hpp
cJnqK5oNOBpLtDIbcN/DEjftFOG7vZHZgJtvTWQ2gG3jWwF8NXOkL6/MZzdk1kMbeCZzNDIpkO74hTLjy+LJXupjW+9P6U9wf9pva0Pj+7JFt7XMHsf270RS9t02/Xkk4pz6vtR8PWgAOu6ih2THRZLQcRUmE6m1PiySqNOw3/u19aLPCifoAeQZ5Nn0Le6nw75ssEjWH/hyZ52PA1F1q76+10PUKxPsSbipry+4M/PKWq6vr/Q/v21Cj0TL9mWvIXZfl8B+g8yvzMjP52qksF/b6JzTtlntO5l/o/LmN+Wf92ha/6MT1z8y0nqfRf1v8/4q8XxZ9o3R6dp2YxdJ0bvNEROG6/RFqeACS7Wlp29x2AYnJ/NVPvmQm8SjK/VaROSsKEoh0BK468/VM+fKqTftlrip99n9cuot5NRbZpl662/Z59RbZ0y9tVxgKCVeSweh5AyIXOT5RUiakP7e9/3b/u0bXItFyrRv0Fjn8JP7DPsGA/VNs632DQLSvkFQ2Te48On92zeIjPRXNUsvfFqvxvd6F1/tNYiG7aGA5lA785UZ2a2KWuGdLFe9J/q7NKlU64qe4yEdm3NdBsd1BPaC4Rn1HeBPJx0xNB10AGX0FB0Na/cHtRUr+wf1cfjUKiE+Wc+/9U3wodut+7B/QAZyAWUxghF5NZWg/Ne+apLf2sg+8quwN4tPk4yspnkE64LE12DSXVeFDeTpL5EHgQJ57goL5Ekl0HS4A1KGavgXDdG625mlXipRqb+I3GWg0v1/lKj0EFFpuQWVZoWbQ6X1ApVmMk8r/Vdqpf9KExwZd82UEIbe6yEgbhPeB0k2UN+6hjj9Y4/QBGvF7b0Lyq6/Xr/yI3GqO8+itnS6fhNrjtBTuNGDvv8wzaq6hDz8kkMQKDRZOKcdK0a8kNdLkvChB4yPQhZ5qSjyXqmzftw90F/bbNrcO3Km4DsRvgU35c3Of11ySeSeZ5Xkpz2NQbMOjT2N97BXW+xp8EUEvlHCqbIqC0JElMdM8FJWzK5GR0WR9pJ2NVLvjvGeS/QOJY20BLlrS4H27+4iQ7+Pxa7G8GLTrka6tKuxGjAcjuvRqUwZZ1fD26xdDe+/wK6G8YF5y6b62hkekyGm+TAizfE3z/oiMX+zVm0SGZJ//Lc7Df6mX3/p5n3xN+2hQTIhmZwi3SykYza/QTbG2ET1STKHZligI/Xc2RJ1hirU+VOPGOpY2J/EIdnBgYCJQzuPPmA2aGDNIfkc6Ptu8r6ZDzUYvDm99weNzjeH3SzM9yIAn0ZnnJ9miDgE8LN/RQnx/g07L83yCM6ZRuElExzkieIRHG0vHrXRvhWXXI9y2CBQg7g8+rkJcBC8PD56ccl03CyS4NwIQpO5MewwN4bQ5RyyAAK1j/RPw/LRXamC+D58hDhZ7j7l5U55mVmD8Pyy27IEdwRhUgQbYkCkWLdCbr0DUker9Lu5TW288UX1rO5aPQcBzLiMGeBXo59v4sg31cccwld3E8i/bTFP2A4hf8+mFeB1sZKAlG7gC3VCZpSdlqE/xWWlTJOttBut3KX/QyqGahv1awihIYGSfWqZBJRRn+mfGvWZaJf1kbeApcbjvP48WZ8M9v0rTgqZlFiq5IhVKd+s0iZCaEhzAAJ8LdP/EPtB9Sfq/O/TdPWGWnZ20QB97nQMKPVTKoT1m5Nvk0vKaDfojHO5J40AnTHUpx85Xawq9bk8CN58kymgn6G9w0XhaNQeF99Fp+drHShrMHS6mI4nSXn9ESZ8Ua1WbRHUN0ScOH8yoPHBbaKtOm0mqRJr1xzsR75v08z5+cXNslM+QI9we2xHwyXX/cEBfed6h7ZndnRGD1mXcQgj/ng=
*/