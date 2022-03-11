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