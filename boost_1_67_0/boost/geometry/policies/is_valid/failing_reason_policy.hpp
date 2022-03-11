// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_POLICIES_IS_VALID_FAILING_REASON_POLICY_HPP
#define BOOST_GEOMETRY_POLICIES_IS_VALID_FAILING_REASON_POLICY_HPP

#include <sstream>

#include <boost/geometry/io/dsv/write.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/range.hpp>
#include <boost/geometry/algorithms/validity_failure_type.hpp>
#include <boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>


namespace boost { namespace geometry
{


inline char const* validity_failure_type_message(validity_failure_type failure)
{
    switch (failure)
    {
    case no_failure:
        return "Geometry is valid";
    case failure_few_points:
        return "Geometry has too few points";
    case failure_wrong_topological_dimension:
        return "Geometry has wrong topological dimension";
    case failure_not_closed:
        return "Geometry is defined as closed but is open";
    case failure_spikes:
        return "Geometry has spikes";
    case failure_self_intersections:
        return "Geometry has invalid self-intersections";
    case failure_wrong_orientation:
        return "Geometry has wrong orientation";
    case failure_interior_rings_outside:
        return "Geometry has interior rings defined outside the outer boundary";
    case failure_nested_interior_rings:
        return "Geometry has nested interior rings";
    case failure_disconnected_interior:
        return "Geometry has disconnected interior";
    case failure_intersecting_interiors:
        return "Multi-polygon has intersecting interiors";
    case failure_duplicate_points:
        return "Geometry has duplicate (consecutive) points";
    case failure_wrong_corner_order:
        return "Box has corners in wrong order";
    case failure_invalid_coordinate:
        return "Geometry has point(s) with invalid coordinate(s)";
    default: // to avoid -Wreturn-type warning
        return "";
    }
}


template <bool AllowDuplicates = true, bool AllowSpikes = true>
class failing_reason_policy
{
private:
    static inline
    validity_failure_type transform_failure_type(validity_failure_type failure)
    {
        if (BOOST_GEOMETRY_CONDITION(
                AllowDuplicates && failure == failure_duplicate_points))
        {
            return no_failure;
        }
        return failure;
    }

    static inline
    validity_failure_type transform_failure_type(validity_failure_type failure,
                                                 bool is_linear)
    {
        if (BOOST_GEOMETRY_CONDITION(
                is_linear && AllowSpikes && failure == failure_spikes))
        {
            return no_failure;
        }
        return transform_failure_type(failure);
    }

    inline void set_failure_message(validity_failure_type failure)
    {
        m_oss.str("");
        m_oss.clear();
        m_oss << validity_failure_type_message(failure);
    }

    template
    <
        validity_failure_type Failure,
        typename Data1,
        typename Data2 = Data1,
        typename Dummy = void
    >
    struct process_data
    {
        static inline void apply(std::ostringstream&, Data1 const&)
        {
        }

        static inline void apply(std::ostringstream&,
                                 Data1 const&,
                                 Data2 const&)
        {
        }
    };

    template <typename SpikePoint>
    struct process_data<failure_spikes, bool, SpikePoint>
    {
        static inline void apply(std::ostringstream& oss,
                                 bool is_linear,
                                 SpikePoint const& spike_point)
        {
            if (BOOST_GEOMETRY_CONDITION(is_linear && AllowSpikes))
            {
                return;
            }

            oss << ". A spike point was found with apex at "
                << geometry::dsv(spike_point);
        }
    };

    template <typename Turns>
    struct process_data<failure_self_intersections, Turns>
    {
        static inline
        void apply_to_segment_identifier(std::ostringstream& oss,
                                         segment_identifier seg_id)
        {
            oss << "{" << seg_id.source_index
                << ", " << seg_id.multi_index
                << ", " << seg_id.ring_index
                << ", " << seg_id.segment_index
                << "}";
        }

        static inline void apply(std::ostringstream& oss,
                                 Turns const& turns)
        {
            typedef typename boost::range_value<Turns>::type turn_type;
            turn_type const& turn = range::front(turns);
            oss << ". A self-intersection point was found at "
                << geometry::dsv(turn.point);

            oss << "; method: " << method_char(turn.method)
                << "; operations: "
                << operation_char(turn.operations[0].operation)
                << "/"
                << operation_char(turn.operations[1].operation)
                << "; segment IDs {source, multi, ring, segment}: ";
            apply_to_segment_identifier(oss, turn.operations[0].seg_id);
            oss << "/";
            apply_to_segment_identifier(oss, turn.operations[1].seg_id);
        }
    };

    template <typename Point>
    struct process_data<failure_duplicate_points, Point>
    {
        static inline void apply(std::ostringstream& oss,
                                 Point const& point)
        {
            if (BOOST_GEOMETRY_CONDITION(AllowDuplicates))
            {
                return;
            }
            oss << ". Duplicate points were found near point "
                << geometry::dsv(point);
        }
    };

public:
    failing_reason_policy(std::ostringstream& oss)
        : m_oss(oss)
    {}

    template <validity_failure_type Failure>
    inline bool apply()
    {
        validity_failure_type const failure = transform_failure_type(Failure);
        set_failure_message(failure);
        return failure == no_failure;
    }

    template <validity_failure_type Failure, typename Data>
    inline bool apply(Data const& data)
    {
        validity_failure_type const failure = transform_failure_type(Failure);
        set_failure_message(failure);
        process_data<Failure, Data>::apply(m_oss, data);
        return failure == no_failure;
    }

    template <validity_failure_type Failure, typename Data1, typename Data2>
    inline bool apply(Data1 const& data1, Data2 const& data2)
    {
        validity_failure_type const failure
            = transform_failure_type(Failure, data1);
        set_failure_message(failure);
        process_data<Failure, Data1, Data2>::apply(m_oss, data1, data2);
        return failure == no_failure;
    }

private:
    std::ostringstream& m_oss;
};


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_POLICIES_IS_VALID_FAILING_REASON_POLICY_HPP

/* failing_reason_policy.hpp
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
*/