// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_DIRECTION_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_DIRECTION_HPP


#include <cstddef>
#include <string>

#include <boost/concept_check.hpp>

#include <boost/geometry/arithmetic/determinant.hpp>
#include <boost/geometry/strategies/side_info.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{


namespace policies { namespace relate
{

struct direction_type
{
    // NOTE: "char" will be replaced by enum in future version

    inline direction_type(side_info const& s, char h,
                int ha, int hb,
                int da = 0, int db = 0,
                bool op = false)
        : how(h)
        , opposite(op)
        , how_a(ha)
        , how_b(hb)
        , dir_a(da)
        , dir_b(db)
        , sides(s)
    {
        arrival[0] = ha;
        arrival[1] = hb;
    }

    inline direction_type(char h, bool op, int ha = 0, int hb = 0)
        : how(h)
        , opposite(op)
        , how_a(ha)
        , how_b(hb)
        , dir_a(0)
        , dir_b(0)
    {
        arrival[0] = ha;
        arrival[1] = hb;
    }


    // TODO: replace this
    // NOTE: "char" will be replaced by enum in future version
    // "How" is the intersection formed?
    char how;

    // Is it opposite (for collinear/equal cases)
    bool opposite;

    // Information on how A arrives at intersection, how B arrives at intersection
    // 1: arrives at intersection
    // -1: starts from intersection
    int how_a;
    int how_b;

    // Direction: how is A positioned from B
    // 1: points left, seen from IP
    // -1: points right, seen from IP
    // In case of intersection: B's TO direction
    // In case that B's TO direction is at A: B's from direction
    // In collinear cases: it is 0
    int dir_a; // Direction of A-s TO from IP
    int dir_b; // Direction of B-s TO from IP

    // New information
    side_info sides;
    // THIS IS EQUAL TO arrival_a, arrival_b - they probably can go now we have robust fractions
    int arrival[2]; // 1=arrival, -1=departure, 0=neutral; == how_a//how_b


    // About arrival[0] (== arrival of a2 w.r.t. b) for COLLINEAR cases
    // Arrival  1: a1--------->a2         (a arrives within b)
    //                      b1----->b2

    // Arrival  1: (a in b)
    //


    // Arrival -1:      a1--------->a2     (a does not arrive within b)
    //             b1----->b2

    // Arrival -1: (b in a)               a_1-------------a_2
    //                                         b_1---b_2

    // Arrival  0:                        a1------->a2  (a arrives at TO-border of b)
    //                                        b1--->b2

};

struct segments_direction
{
    typedef direction_type return_type;

    template
    <
        typename Segment1,
        typename Segment2,
        typename SegmentIntersectionInfo
    >
    static inline return_type segments_crosses(side_info const& sides,
                    SegmentIntersectionInfo const& ,
                    Segment1 const& , Segment2 const& )
    {
        bool const ra0 = sides.get<0,0>() == 0;
        bool const ra1 = sides.get<0,1>() == 0;
        bool const rb0 = sides.get<1,0>() == 0;
        bool const rb1 = sides.get<1,1>() == 0;

        return
            // opposite and same starting point (FROM)
            ra0 && rb0 ? calculate_side<1>(sides, 'f', -1, -1)

            // opposite and point to each other (TO)
            : ra1 && rb1 ? calculate_side<0>(sides, 't', 1, 1)

            // not opposite, forming an angle, first a then b,
            // directed either both left, or both right
            // Check side of B2 from A. This is not calculated before
            : ra1 && rb0 ? angle<1>(sides, 'a', 1, -1)

            // not opposite, forming a angle, first b then a,
            // directed either both left, or both right
            : ra0 && rb1 ? angle<0>(sides, 'a', -1, 1)

            // b starts from interior of a
            : rb0 ? starts_from_middle(sides, 'B', 0, -1)

            // a starts from interior of b (#39)
            : ra0 ? starts_from_middle(sides, 'A', -1, 0)

            // b ends at interior of a, calculate direction of A from IP
            : rb1 ? b_ends_at_middle(sides)

            // a ends at interior of b
            : ra1 ? a_ends_at_middle(sides)

            // normal intersection
            : calculate_side<1>(sides, 'i', -1, -1)
            ;
    }

    template <typename Ratio>
    static inline int arrival_value(Ratio const& r_from, Ratio const& r_to)
    {
        //     a1--------->a2
        // b1----->b2
        // a departs: -1

        // a1--------->a2
        //         b1----->b2
        // a arrives: 1

        // a1--------->a2
        //     b1----->b2
        // both arrive there -> r-to = 1/1, or 0/1 (on_segment)

        // First check the TO (for arrival), then FROM (for departure)
        return r_to.in_segment() ? 1
            : r_to.on_segment() ? 0
            : r_from.on_segment() ? -1
            : -1
            ;
    }

    template <typename Ratio>
    static inline void analyze(Ratio const& r,
        int& in_segment_count,
        int& on_end_count,
        int& outside_segment_count)
    {
        if (r.on_end())
        {
            on_end_count++;
        }
        else if (r.in_segment())
        {
            in_segment_count++;
        }
        else
        {
            outside_segment_count++;
        }
    }

    static inline int arrival_from_position_value(int /*v_from*/, int v_to)
    {
        return v_to == 2 ? 1
             : v_to == 1 || v_to == 3 ? 0
             //: v_from >= 1 && v_from <= 3 ? -1
             : -1;

        // NOTE: this should be an equivalent of the above for the other order
        /* (v_from < 3 && v_to > 3) || (v_from > 3 && v_to < 3) ? 1
         : v_from == 3 || v_to == 3 ? 0
         : -1;*/
    }

    static inline void analyse_position_value(int pos_val,
                                              int & in_segment_count,
                                              int & on_end_count,
                                              int & outside_segment_count)
    {
        if ( pos_val == 1 || pos_val == 3 )
        {
            on_end_count++;
        }
        else if ( pos_val == 2 )
        {
            in_segment_count++;
        }
        else
        {
            outside_segment_count++;
        }
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
        Segment1 const& , Segment2 const& , bool opposite,
        int a1_wrt_b, int a2_wrt_b, int b1_wrt_a, int b2_wrt_a,
        Ratio const& /*ra_from_wrt_b*/, Ratio const& /*ra_to_wrt_b*/,
        Ratio const& /*rb_from_wrt_a*/, Ratio const& /*rb_to_wrt_a*/)
    {
        return_type r('c', opposite);

        // IMPORTANT: the order of conditions is different as in intersection_points.hpp
        // We assign A in 0 and B in 1
        r.arrival[0] = arrival_from_position_value(a1_wrt_b, a2_wrt_b);
        r.arrival[1] = arrival_from_position_value(b1_wrt_a, b2_wrt_a);

        // Analyse them
        int a_in_segment_count = 0;
        int a_on_end_count = 0;
        int a_outside_segment_count = 0;
        int b_in_segment_count = 0;
        int b_on_end_count = 0;
        int b_outside_segment_count = 0;
        analyse_position_value(a1_wrt_b,
            a_in_segment_count, a_on_end_count, a_outside_segment_count);
        analyse_position_value(a2_wrt_b,
            a_in_segment_count, a_on_end_count, a_outside_segment_count);
        analyse_position_value(b1_wrt_a,
            b_in_segment_count, b_on_end_count, b_outside_segment_count);
        analyse_position_value(b2_wrt_a,
            b_in_segment_count, b_on_end_count, b_outside_segment_count);

        if (a_on_end_count == 1
            && b_on_end_count == 1
            && a_outside_segment_count == 1
            && b_outside_segment_count == 1)
        {
            // This is a collinear touch
            // -------->             A (or B)
            //         <----------   B (or A)
            // We adapt the "how"
            // TODO: how was to be refactored anyway,
            if (! opposite)
            {
                r.how = 'a';
            }
            else
            {
                r.how = r.arrival[0] == 0 ? 't' : 'f';
            }
        }
        else if (a_on_end_count == 2
                 && b_on_end_count == 2)
        {
            r.how = 'e';
        }

        return r;
    }

    template <typename Segment>
    static inline return_type degenerate(Segment const& , bool)
    {
        return return_type('0', false);
    }

    template <typename Segment, typename Ratio>
    static inline return_type one_degenerate(Segment const& ,
            Ratio const& ,
            bool)
    {
        // To be decided
        return return_type('0', false);
    }

    static inline return_type disjoint()
    {
        return return_type('d', false);
    }

    static inline return_type error(std::string const&)
    {
        // Return "E" to denote error
        // This will throw an error in get_turn_info
        // TODO: change to enum or similar
        return return_type('E', false);
    }

private :

    template <std::size_t I>
    static inline return_type calculate_side(side_info const& sides,
                char how, int how_a, int how_b)
    {
        int const dir = sides.get<1, I>() == 1 ? 1 : -1;
        return return_type(sides, how, how_a, how_b, -dir, dir);
    }

    template <std::size_t I>
    static inline return_type angle(side_info const& sides,
                char how, int how_a, int how_b)
    {
        int const dir = sides.get<1, I>() == 1 ? 1 : -1;
        return return_type(sides, how, how_a, how_b, dir, dir);
    }


    static inline return_type starts_from_middle(side_info const& sides,
                char which,
                int how_a, int how_b)
    {
        // Calculate ARROW of b segment w.r.t. s1
        int dir = sides.get<1, 1>() == 1 ? 1 : -1;

        // From other perspective, then reverse
        bool const is_a = which == 'A';
        if (is_a)
        {
            dir = -dir;
        }

        return return_type(sides, 's',
            how_a,
            how_b,
            is_a ? dir : -dir,
            ! is_a ? dir : -dir);
    }



    // To be harmonized
    static inline return_type a_ends_at_middle(side_info const& sides)
    {
        // Ending at the middle, one ARRIVES, the other one is NEUTRAL
        // (because it both "arrives"  and "departs" there)
        int const dir = sides.get<1, 1>() == 1 ? 1 : -1;
        return return_type(sides, 'm', 1, 0, dir, dir);
    }


    static inline return_type b_ends_at_middle(side_info const& sides)
    {
        int const dir = sides.get<0, 1>() == 1 ? 1 : -1;
        return return_type(sides, 'm', 0, 1, dir, dir);
    }

};

}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_DIRECTION_HPP

/* direction.hpp
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
*/